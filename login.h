#ifndef LOGIN_H
#define LOGIN_H

#include <QString>
#include <QWidget>

class Login
{
public:
    Login() {}

    static QString genererMotDePasse();
    static bool envoyerEmail(const QString &destinataire,
                             const QString &motDePasse,
                             const QString &nomEmploye);
    static bool verifierLogin(const QString &email, const QString &mdp);
};

#endif // LOGIN_H
