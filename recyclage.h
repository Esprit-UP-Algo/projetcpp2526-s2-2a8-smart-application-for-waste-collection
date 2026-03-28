#ifndef RECYCLAGE_H
#define RECYCLAGE_H

#include <QString>
#include <QSqlQueryModel>

class Recyclage
{
public:
    Recyclage();
    Recyclage(int id,
              QString materiau,
              double qteEntree,
              double qteRecyclee,
              double qteRejetee,
              QString destination,
              double valeur);

    bool ajouter();
    QSqlQueryModel* afficher();
    bool supprimer(int id);
    bool modifier();
private:
    int id;
    QString materiau;
    double qteEntree;
    double qteRecyclee;
    double qteRejetee;
    QString destination;
    double valeur;
};

#endif
