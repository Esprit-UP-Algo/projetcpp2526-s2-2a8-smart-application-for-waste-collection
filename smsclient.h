#ifndef SMSCLIENTMETIER_H
#define SMSCLIENTMETIER_H

#include <QObject>
#include <QString>
#include <QNetworkAccessManager>
#include <QNetworkReply>

class SmsClientMetier : public QObject
{
    Q_OBJECT

public:
    explicit SmsClientMetier(QObject *parent = nullptr);

    void envoyerSMS(const QString &numero, const QString &message);

signals:
    void smsEnvoye(bool success, QString response);

private slots:
    void onReplyFinished(QNetworkReply *reply);

private:
    bool validerNumero(const QString &numero);

    QNetworkAccessManager *manager;

    // Twilio credentials
    QString accountSid;
    QString authToken;
    QString fromNumber;
};

#endif // SMSCLIENTMETIER_H