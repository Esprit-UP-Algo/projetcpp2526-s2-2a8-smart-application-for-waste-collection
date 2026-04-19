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
    static QString getRoleUtilisateur(const QString &email);
    static QString getNomUtilisateur(const QString &email);
    static QString getPosteUtilisateur(const QString &email);
    static bool reinitialiserMdp(const QString &email, const QString &nouveauMdp);
    static QString getNomComplet(const QString &email); // si pas déjà là
};

#endif // LOGIN_H
