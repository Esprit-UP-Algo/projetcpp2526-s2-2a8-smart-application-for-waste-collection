#ifndef MDP_OUBLIER_H
#define MDP_OUBLIER_H

#include <QString>

class MdpOublier
{
public:
    MdpOublier();

    static bool emailExiste(const QString &email);
    static QString genererCodeVerification();
    static bool envoyerCodeParEmail(const QString &email,
                                    const QString &code,
                                    const QString &nomEmploye);
    static bool reinitialiserMotDePasse(const QString &email,
                                        const QString &nouveauMdp);
    static QString getNomEmploye(const QString &email);
};

#endif // MDP_OUBLIER_H
