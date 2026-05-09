#ifndef AI_H
#define AI_H

#include <QString>
#include <QJsonObject>

class AI
{
public:
    AI();

    void setApiKey(const QString &key);
    void setModel(const QString &model);

    // Main function you will use everywhere
    QString ask(const QString &question, const QJsonObject &uiContext = QJsonObject());

private:
    QString apiKey;
    QString model;

    QString callGroq(const QString &prompt);
    QString buildPrompt(const QString &question, const QJsonObject &uiContext);
};

#endif // AI_H