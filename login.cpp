#include "login.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QRandomGenerator>
#include <QProcess>
#include <QFile>
#include <QTextStream>
#include <QStandardPaths>   // ← NOUVEAU

QString Login::genererMotDePasse()
{
    const QString chars = "ABCDEFGHJKLMNPQRSTUVWXYZabcdefghjkmnpqrstuvwxyz23456789";
    QString mdp;
    for (int i = 0; i < 8; i++) {
        int idx = QRandomGenerator::global()->bounded(chars.length());
        mdp += chars[idx];
    }
    return mdp;
}

bool Login::envoyerEmail(const QString &destinataire,
                         const QString &motDePasse,
                         const QString &nomEmploye)
{
    const QString GMAIL_USER = "hafnaouimaryem44@gmail.com";
    const QString GMAIL_PASS = "sawxjnmqalzupwbd";

    // Chemin temp accessible
    QString tmpPath = QStandardPaths::writableLocation(QStandardPaths::TempLocation) + "\\sm_mail.txt";
    qDebug() << "Fichier temp:" << tmpPath;

    QFile f(tmpPath);
    if (!f.open(QIODevice::WriteOnly | QIODevice::Text)) {
        qDebug() << "Impossible de créer le fichier!";
        return false;
    }
    QTextStream out(&f);
    out << "From: SmartMarket <" << GMAIL_USER << ">\r\n";
    out << "To: " << destinataire << "\r\n";
    out << "Subject: Vos identifiants SmartMarket\r\n";
    out << "\r\n";
    out << "Bonjour " << nomEmploye << ",\r\n\r\n";
    out << "Email       : " << destinataire << "\r\n";
    out << "Mot de passe: " << motDePasse << "\r\n\r\n";
    out << "Cordialement,\r\nSmartMarket\r\n";
    f.close();

    QProcess process;
    QStringList args;
    args << "--ssl-reqd"
         << "--url" << "smtps://smtp.gmail.com:465"
         << "--user" << QString("%1:%2").arg(GMAIL_USER, GMAIL_PASS)
         << "--mail-from" << GMAIL_USER
         << "--mail-rcpt" << destinataire
         << "--upload-file" << tmpPath
         << "--verbose";

    process.start("curl", args);
    process.waitForFinished(15000);

    qDebug() << "Exit code:" << process.exitCode();
    qDebug() << "STDERR:" << process.readAllStandardError();

    QFile::remove(tmpPath);
    return (process.exitCode() == 0);
}

bool Login::verifierLogin(const QString &email, const QString &mdp)
{
    const QString ADMIN_EMAIL = "admin@smartmarket.com";
    const QString ADMIN_PASS  = "admin1234";

    if (email.trimmed() == ADMIN_EMAIL && mdp.trimmed() == ADMIN_PASS)
        return true;

    QSqlQuery q;
    q.prepare("SELECT COUNT(*) FROM EMPLOYES WHERE Email = :email AND MDP = :mdp");
    q.bindValue(":email", email.trimmed());
    q.bindValue(":mdp",   mdp.trimmed());
    if (q.exec() && q.next())
        return q.value(0).toInt() > 0;
    return false;
}
QString Login::getPosteUtilisateur(const QString &email)
{
    if (email.trimmed() == "admin@smartmarket.com")
        return "admin";

    QSqlQuery q;
    q.prepare("SELECT Poste FROM EMPLOYES WHERE Email = :email");
    q.bindValue(":email", email.trimmed());
    if (q.exec() && q.next())
        return q.value(0).toString().toLower();

    return "employe";
}
//laccee
QString Login::getNomUtilisateur(const QString &email)
{
    if (email.trimmed() == "admin@smartmarket.com")
        return "Administrateur";

    QSqlQuery q;
    q.prepare("SELECT Nom, Prenom FROM EMPLOYES WHERE Email = :email");
    q.bindValue(":email", email.trimmed());
    if (q.exec() && q.next())
        return q.value(0).toString() + " " + q.value(1).toString();

    return email;
}
bool Login::reinitialiserMdp(const QString &email, const QString &nouveauMdp)
{
    QSqlQuery q;
    q.prepare("SELECT COUNT(*) FROM EMPLOYES WHERE Email = :email");
    q.bindValue(":email", email.trimmed());
    if (!q.exec() || !q.next() || q.value(0).toInt() == 0)
        return false;

    QSqlQuery update;
    update.prepare("UPDATE EMPLOYES SET MDP = :mdp WHERE Email = :email");
    update.bindValue(":mdp",   nouveauMdp.trimmed());
    update.bindValue(":email", email.trimmed());
    return update.exec();
}
