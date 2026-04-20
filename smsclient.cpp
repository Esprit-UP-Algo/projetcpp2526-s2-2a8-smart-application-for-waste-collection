#include "smsclient.h"
#include <QUrl>
#include <QUrlQuery>
#include <QNetworkRequest>
#include <QByteArray>
#include <QDebug>

SmsClientMetier::SmsClientMetier(QObject *parent)
    : QObject(parent)
{
    manager = new QNetworkAccessManager(this);

    connect(manager, &QNetworkAccessManager::finished,
            this, &SmsClientMetier::onReplyFinished);

    // partie li feha authentification key

}

bool SmsClientMetier::validerNumero(const QString &numero)
{
    // Tunisia format: +216XXXXXXXX
    return numero.startsWith("+216") && numero.length() == 12;
}

void SmsClientMetier::envoyerSMS(const QString &numero, const QString &message)
{
    QString num = numero;

    qDebug() << "🔵 RAW INPUT:" << num;

    num = num.trimmed();
    num.remove(" ");
    num.remove("\r");
    num.remove("\n");

    if (num.length() == 8)
        num = "+216" + num;
    else if (num.startsWith("0"))
        num = "+216" + num.mid(1);

    qDebug() << "🧹 FORMATTED:" << num;

    if (!validerNumero(num)) {
        qDebug() << "❌ FAILED VALIDATION:" << num;
        emit smsEnvoye(false, "Numéro invalide: " + num);
        return;
    }

    qDebug() << "📞 VALID NUMBER OK:" << num;

    // ---------------- TWILIO REQUEST ----------------

    QUrl url("https://api.twilio.com/2010-04-01/Accounts/" + accountSid + "/Messages.json");

    QNetworkRequest request(url);

    request.setHeader(QNetworkRequest::ContentTypeHeader,
                      "application/x-www-form-urlencoded");

    // Basic Auth
    QString auth = accountSid + ":" + authToken;
    QByteArray authHeader = "Basic " + auth.toUtf8().toBase64();
    request.setRawHeader("Authorization", authHeader);

    QUrlQuery params;
    params.addQueryItem("To", num);
    params.addQueryItem("From", fromNumber);
    params.addQueryItem("Body", message);

    QByteArray data = params.toString(QUrl::FullyEncoded).toUtf8();

    QNetworkReply *reply = manager->post(request, data);

    connect(reply, &QNetworkReply::finished, this, [=]() {
        QByteArray response = reply->readAll();

        if (reply->error() == QNetworkReply::NoError) {
            qDebug() << "✅ TWILIO SUCCESS:" << response;
            emit smsEnvoye(true, response);
        } else {
            qDebug() << "❌ TWILIO ERROR:" << reply->errorString();
            qDebug() << response;
            emit smsEnvoye(false, reply->errorString());
        }

        reply->deleteLater();
    });
}

void SmsClientMetier::onReplyFinished(QNetworkReply *reply)
{
    QByteArray response = reply->readAll();

    if (reply->error() == QNetworkReply::NoError) {
        qDebug() << "✅ SMS envoyé:" << response;
        emit smsEnvoye(true, response);
    } else {
        qDebug() << "❌ Erreur SMS:" << reply->errorString();
        emit smsEnvoye(false, reply->errorString());
    }

    reply->deleteLater();
}
