#include "mdp_oublier.h"
#include <QSqlQuery>
#include <QRandomGenerator>
#include <QProcess>
#include <QFile>
#include <QTextStream>
#include <QStandardPaths>
#include <QDebug>

MdpOublier::MdpOublier() {}

bool MdpOublier::emailExiste(const QString &email)
{
    if (email.trimmed().isEmpty()) return false;
    QSqlQuery q;
    q.prepare("SELECT COUNT(*) FROM EMPLOYES WHERE Email = :email");
    q.bindValue(":email", email.trimmed());
    if (q.exec() && q.next())
        return q.value(0).toInt() > 0;
    return false;
}

QString MdpOublier::genererCodeVerification()
{
    int code = QRandomGenerator::global()->bounded(1000, 9999);
    return QString::number(code);
}

QString MdpOublier::getNomEmploye(const QString &email)
{
    QSqlQuery q;
    q.prepare("SELECT Nom, Prenom FROM EMPLOYES WHERE Email = :email");
    q.bindValue(":email", email.trimmed());
    if (q.exec() && q.next())
        return q.value(0).toString() + " " + q.value(1).toString();
    return email;
}

bool MdpOublier::envoyerCodeParEmail(const QString &email,
                                     const QString &code,
                                     const QString &nomEmploye)
{
    const QString GMAIL_USER = "hafnaouimaryem44@gmail.com";
    const QString GMAIL_PASS = "sawxjnmqalzupwbd";

    QString tmpPath = QStandardPaths::writableLocation(
                          QStandardPaths::TempLocation) + "\\reset_mail.txt";

    QFile f(tmpPath);
    if (!f.open(QIODevice::WriteOnly | QIODevice::Text)) return false;

    QTextStream out(&f);
    out << "From: SmartWaste <" << GMAIL_USER << ">\r\n";
    out << "To: " << email << "\r\n";
    out << "Subject: Code de verification - Reinitialisation mot de passe\r\n";
    out << "\r\n";
    out << "Bonjour " << nomEmploye << ",\r\n\r\n";
    out << "Votre code de verification : " << code << "\r\n\r\n";
    out << "Ce code est valable pour cette session uniquement.\r\n";
    out << "Cordialement,\r\nL'equipe SmartWaste\r\n";
    f.close();

    QProcess process;
    QStringList args;
    args << "--ssl-reqd"
         << "--url" << "smtps://smtp.gmail.com:465"
         << "--user" << QString("%1:%2").arg(GMAIL_USER, GMAIL_PASS)
         << "--mail-from" << GMAIL_USER
         << "--mail-rcpt" << email.trimmed()
         << "--upload-file" << tmpPath
         << "--verbose";

    process.start("curl", args);
    process.waitForFinished(15000);
    QFile::remove(tmpPath);
    return (process.exitCode() == 0);
}

bool MdpOublier::reinitialiserMotDePasse(const QString &email,
                                         const QString &nouveauMdp)
{
    if (email.trimmed().isEmpty() || nouveauMdp.trimmed().isEmpty()) return false;
    QSqlQuery q;
    q.prepare("UPDATE EMPLOYES SET MDP = :mdp WHERE Email = :email");
    q.bindValue(":mdp",   nouveauMdp.trimmed());
    q.bindValue(":email", email.trimmed());
    return q.exec();
}
