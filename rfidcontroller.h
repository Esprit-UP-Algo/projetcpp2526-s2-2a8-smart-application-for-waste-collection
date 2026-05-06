#ifndef RFIDCONTROLLER_H
#define RFIDCONTROLLER_H

#include <QObject>
#include <QSerialPort>
#include <QSqlDatabase>
#include <QString>
#include <QTimer>

struct ResultatAcces {
    QString uid;
    bool    autorise;
    QString nomUtilisateur;
    QString message;
};

class RfidController : public QObject
{
    Q_OBJECT

public:
    explicit RfidController(QObject *parent = nullptr);
    ~RfidController();

    // Connexion au port série (ex: "COM3" ou "/dev/ttyUSB0")
    bool connecterPort(const QString &portName, int baudRate = 9600);
    void deconnecterPort();

    // Connexion à la base SQLite
    bool connecterBase(const QString &cheminDB);

    // Gestion des UIDs autorisés
    bool ajouterUID(const QString &uid, const QString &nom, const QString &role);
    bool supprimerUID(const QString &uid);
    QList<QStringList> getTousLesUtilisateurs();

    bool estConnecte() const;

signals:
    void accesDetecte(ResultatAcces resultat);
    void portConnecte(const QString &port);
    void erreurPort(const QString &erreur);
    void messageRecu(const QString &msg);

private slots:
    void onDonneesRecues();

private:
    bool        verifierUID(const QString &uid, ResultatAcces &res);
    void        envoyerReponse(const QString &reponse);
    bool        initialiserBase();

    QSerialPort   *m_serial;
    QSqlDatabase   m_db;
    QString        m_buffer;
};

#endif // RFIDCONTROLLER_H
