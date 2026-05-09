#include "rfidcontroller.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QDateTime>

RfidController::RfidController(QObject *parent)
    : QObject(parent)
{
    m_serial = new QSerialPort(this);
    connect(m_serial, &QSerialPort::readyRead,
            this,     &RfidController::onDonneesRecues);
}

RfidController::~RfidController()
{
    deconnecterPort();
}

// ── Connexion port série ──────────────────────────────────────────
bool RfidController::connecterPort(const QString &portName, int baudRate)
{
    m_serial->setPortName(portName);
    m_serial->setBaudRate(baudRate);
    m_serial->setDataBits(QSerialPort::Data8);
    m_serial->setParity(QSerialPort::NoParity);
    m_serial->setStopBits(QSerialPort::OneStop);
    m_serial->setFlowControl(QSerialPort::NoFlowControl);

    if (!m_serial->open(QIODevice::ReadWrite)) {
        emit erreurPort("Impossible d'ouvrir " + portName +
                        " : " + m_serial->errorString());
        return false;
    }

    emit portConnecte(portName);
    qDebug() << "Port ouvert:" << portName;
    return true;
}

void RfidController::deconnecterPort()
{
    if (m_serial->isOpen())
        m_serial->close();
}

bool RfidController::estConnecte() const
{
    return m_serial->isOpen();
}

// ── Connexion base Oracle ─────────────────────────────────────────
bool RfidController::connecterBase(const QString &host,
                                   const QString &port,
                                   const QString &sid,
                                   const QString &user,
                                   const QString &password)
{
    m_db = QSqlDatabase::addDatabase("QOCI", "rfid_db");
    m_db.setHostName(host);
    m_db.setPort(port.toInt());
    m_db.setDatabaseName(sid);   // SID ou Service Name
    m_db.setUserName(user);
    m_db.setPassword(password);

    if (!m_db.open()) {
        qDebug() << "Erreur Oracle DB:" << m_db.lastError().text();
        return false;
    }

    qDebug() << "Connecté à Oracle:" << host << sid;
    return true;
}

// ── Lecture données série ─────────────────────────────────────────
void RfidController::onDonneesRecues()
{
    m_buffer += QString::fromUtf8(m_serial->readAll());

    while (m_buffer.contains('\n')) {
        int idx = m_buffer.indexOf('\n');
        QString ligne = m_buffer.left(idx).trimmed();
        m_buffer = m_buffer.mid(idx + 1);

        qDebug() << "Arduino →" << ligne;
        emit messageRecu(ligne);

        if (ligne.startsWith("UID:")) {
            QString uid = ligne.mid(4).trimmed().toUpper();
            ResultatAcces res;
            res.uid = uid;

            if (verifierUID(uid, res)) {
                envoyerReponse("Y\n");
            } else {
                envoyerReponse("N\n");
            }

            // Logger l'accès dans Oracle
            QSqlQuery log(m_db);
            log.prepare(
                "INSERT INTO logs_acces (uid_rfid, nom, autorise, horodatage) "
                "VALUES (:uid, :nom, :autorise, :horodatage)"
                );
            log.bindValue(":uid",       uid);
            log.bindValue(":nom",       res.nomUtilisateur.isEmpty()
                                      ? "Inconnu"
                                      : res.nomUtilisateur);
            log.bindValue(":autorise",  res.autorise ? 1 : 0);
            log.bindValue(":horodatage", QDateTime::currentDateTime()
                                             .toString("yyyy-MM-dd hh:mm:ss"));
            if (!log.exec())
                qDebug() << "Log erreur:" << log.lastError().text();

            emit accesDetecte(res);
        }
    }
}

// ── Vérification UID dans Oracle ──────────────────────────────────
bool RfidController::verifierUID(const QString &uid, ResultatAcces &res)
{
    QSqlQuery q(m_db);
    // UPPER() des deux côtés pour comparaison case-insensitive
    q.prepare(
        "SELECT nom, role_utilisateur, actif "
        "FROM utilisateurs_rfid "
        "WHERE UPPER(uid_rfid) = UPPER(:uid)"
        );
    q.bindValue(":uid", uid);
    q.exec();

    if (q.next()) {
        int actif = q.value(2).toInt();
        if (actif == 1) {
            res.autorise       = true;
            res.nomUtilisateur = q.value(0).toString();
            res.message        = "Accès autorisé — " + res.nomUtilisateur +
                          " (" + q.value(1).toString() + ")";
            return true;
        } else {
            res.autorise       = false;
            res.nomUtilisateur = q.value(0).toString();
            res.message        = "Badge désactivé — " + res.nomUtilisateur;
            return false;
        }
    }

    res.autorise       = false;
    res.nomUtilisateur = "";
    res.message        = "UID inconnu : " + uid;
    return false;
}

// ── Envoyer réponse à Arduino ─────────────────────────────────────
void RfidController::envoyerReponse(const QString &reponse)
{
    if (m_serial->isOpen()) {
        m_serial->write(reponse.toUtf8());
        m_serial->flush();
        qDebug() << "Qt → Arduino:" << reponse.trimmed();
    }
}

// ── Ajouter un utilisateur (MERGE = INSERT OR REPLACE en Oracle) ──
bool RfidController::ajouterUID(const QString &uid,
                                const QString &nom,
                                const QString &role)
{
    QSqlQuery q(m_db);
    q.prepare(
        "MERGE INTO utilisateurs_rfid u "
        "USING (SELECT UPPER(:uid) AS uid_rfid FROM dual) src "
        "ON (u.uid_rfid = src.uid_rfid) "
        "WHEN MATCHED THEN "
        "  UPDATE SET nom = :nom, role_utilisateur = :role, actif = 1 "
        "WHEN NOT MATCHED THEN "
        "  INSERT (uid_rfid, nom, role_utilisateur, actif, date_ajout) "
        "  VALUES (UPPER(:uid2), :nom2, :role2, 1, "
        "          TO_CHAR(SYSDATE, 'YYYY-MM-DD'))"
        );
    q.bindValue(":uid",   uid);
    q.bindValue(":nom",   nom);
    q.bindValue(":role",  role);
    q.bindValue(":uid2",  uid);
    q.bindValue(":nom2",  nom);
    q.bindValue(":role2", role);
    return q.exec();
}

// ── Supprimer un utilisateur ──────────────────────────────────────
bool RfidController::supprimerUID(const QString &uid)
{
    QSqlQuery q(m_db);
    q.prepare("DELETE FROM utilisateurs_rfid WHERE UPPER(uid_rfid) = UPPER(:uid)");
    q.bindValue(":uid", uid);
    return q.exec();
}

// ── Récupérer tous les utilisateurs ──────────────────────────────
QList<QStringList> RfidController::getTousLesUtilisateurs()
{
    QList<QStringList> liste;
    QSqlQuery q(m_db);
    q.exec("SELECT uid_rfid, nom, role_utilisateur, actif, date_ajout "
           "FROM utilisateurs_rfid ORDER BY id");
    while (q.next()) {
        QStringList row;
        row << q.value(0).toString()
            << q.value(1).toString()
            << q.value(2).toString()
            << (q.value(3).toInt() ? "Actif" : "Désactivé")
            << q.value(4).toString();
        liste.append(row);
    }
    return liste;
}
