#ifndef PARAMETRES_EMPLOYE_H
#define PARAMETRES_EMPLOYE_H

#include <QWidget>

class Parametres_employe
{
public:
    Parametres_employe() {}

    static void afficher(QWidget *parent);

private:
    static void changerMotDePasse(QWidget *parent);
    static void changerEmail(QWidget *parent);
};

#endif // PARAMETRES_EMPLOYE_H
