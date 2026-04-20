#include "ai.h"

#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QEventLoop>

#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>

#include <QString>

// ===============================
// CONFIG
// ===============================
static const QString GROQ_URL =
    "https://api.groq.com/openai/v1/chat/completions";


// ===============================
// CONSTRUCTOR
// ===============================
AI::AI()
{
    model = "llama-3.1-8b-instant";
}


// ===============================
// SET API KEY
// ===============================
void AI::setApiKey(const QString &key)
{
    apiKey = key;
}


// ===============================
// SET MODEL (OPTIONAL)
// ===============================
void AI::setModel(const QString &m)
{
    model = m;
}


// ===============================
// BUILD PROMPT (CORE INTELLIGENCE)
// ===============================
QString AI::buildPrompt(const QString &question, const QJsonObject &uiContext)
{
    QString prompt;

    prompt += "You are a smart recycling assistant inside a desktop application.\n";
    prompt += "Your job is to help users correctly recycle items based on context.\n";
    prompt += "Be clear, practical, and short.\n\n";

    if (!uiContext.isEmpty()) {
        prompt += "APPLICATION CONTEXT (JSON):\n";

        QJsonDocument doc(uiContext);
        prompt += doc.toJson(QJsonDocument::Compact) + "\n\n";
    }

    prompt += "USER QUESTION:\n";
    prompt += question;

    return prompt;
}


// ===============================
// GROQ API CALL (SYNC)
// ===============================
QString AI::callGroq(const QString &prompt)
{
    if (apiKey.isEmpty()) {
        return "Error: API key not set";
    }

    QNetworkAccessManager manager;

    // ✅ FIX: split QUrl construction (avoids Qt/MSVC bug)
    QUrl url(GROQ_URL);
    QNetworkRequest request(url);

    // ✅ FIX: use raw header (more stable in Qt 6)
    request.setRawHeader("Content-Type", "application/json");

    request.setRawHeader(
        "Authorization",
        QString("Bearer " + apiKey).toUtf8()
        );

    // ===============================
    // Build JSON body
    // ===============================
    QJsonObject body;
    body["model"] = model;

    QJsonArray messages;

    QJsonObject systemMsg;
    systemMsg["role"] = "system";
    systemMsg["content"] = prompt;

    messages.append(systemMsg);

    body["messages"] = messages;

    // ===============================
    // Send request
    // ===============================
    QNetworkReply *reply = manager.post(
        request,
        QJsonDocument(body).toJson()
        );

    // ===============================
    // Wait for response (blocking)
    // ===============================
    QEventLoop loop;
    QObject::connect(reply, &QNetworkReply::finished,
                     &loop, &QEventLoop::quit);
    loop.exec();

    // ===============================
    // Read response
    // ===============================
    QByteArray responseData = reply->readAll();
    reply->deleteLater();

    // ===============================
    // Parse JSON
    // ===============================
    QJsonDocument doc = QJsonDocument::fromJson(responseData);
    QJsonObject root = doc.object();

    if (!root.contains("choices")) {
        return "Error: invalid response from Groq";
    }

    QString result = root["choices"]
                         .toArray()
                         .first()
                         .toObject()
                             ["message"]
                         .toObject()
                             ["content"]
                         .toString();

    return result;
}


// ===============================
// MAIN FUNCTION (WHAT YOU USE)
// ===============================
QString AI::ask(const QString &question, const QJsonObject &uiContext)
{
    QString prompt = buildPrompt(question, uiContext);
    return callGroq(prompt);
}