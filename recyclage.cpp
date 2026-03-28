#include "recyclage.h"
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QSqlError>
#include <QVariant>
#include <QDebug>
#include <QColor>
#include <QLinearGradient>
#include <QBrush>

Recyclage::Recyclage() {}

Recyclage::Recyclage(int id,
                     QString materiau,
                     double qteEntree,
                     double qteRecyclee,
                     double qteRejetee,
                     QString destination,
                     double valeur)
{
    this->id = id;
    this->materiau = materiau;
    this->qteEntree = qteEntree;
    this->qteRecyclee = qteRecyclee;
    this->qteRejetee = qteRejetee;
    this->destination = destination;
    this->valeur = valeur;
}

bool Recyclage::ajouter()
{
    QSqlQuery query;

    query.prepare("INSERT INTO RECYCLAGES "
                  "(ID_RECYCLAGE, TYPE_MATERIAU, QUANTITE_ENTREE, "
                  "QUANTITE_RECYCLEE, QUANTITE_REJETEE, DESTINATION, VALEUR_MONETAIRE) "
                  "VALUES (:id, :materiau, :entree, :recycle, :rejet, :destination, :valeur)");

    query.bindValue(":id", id);
    query.bindValue(":materiau", materiau);
    query.bindValue(":entree", qteEntree);
    query.bindValue(":recycle", qteRecyclee);
    query.bindValue(":rejet", qteRejetee);
    query.bindValue(":destination", destination);
    query.bindValue(":valeur", valeur);

    if(!query.exec())
    {
        qDebug() << "Erreur insertion :" << query.lastError().text();
        return false;
    }

    return true;
}

QSqlQueryModel* Recyclage::afficher()
{
    QSqlQueryModel* model = new QSqlQueryModel();

    model->setQuery("SELECT ID_RECYCLAGE, TYPE_MATERIAU, "
                    "QUANTITE_ENTREE, QUANTITE_RECYCLEE, "
                    "QUANTITE_REJETEE, DESTINATION, VALEUR_MONETAIRE "
                    "FROM RECYCLAGES");

    // ✅ Noms des colonnes dans l'interface
    model->setHeaderData(0, Qt::Horizontal, "ID");
    model->setHeaderData(1, Qt::Horizontal, "Matériau");
    model->setHeaderData(2, Qt::Horizontal, "Qté Entrée");
    model->setHeaderData(3, Qt::Horizontal, "Qté Recyclée");
    model->setHeaderData(4, Qt::Horizontal, "Qté Rejetée");
    model->setHeaderData(5, Qt::Horizontal, "Destination");
    model->setHeaderData(6, Qt::Horizontal, "Valeur (TND)");
    for (int row = 0; row < model->rowCount(); ++row)
    {
        QModelIndex index = model->index(row, 0);
       model->setData(index, QBrush(QColor("#163A5F")), Qt::BackgroundRole);
    }

    return model;
}

bool Recyclage::supprimer(int id)
{
    QSqlQuery query;
    query.prepare("DELETE FROM RECYCLAGES WHERE ID_RECYCLAGE = :id");
    query.bindValue(":id", id);

    return query.exec();
}
bool Recyclage::modifier()
{
    QSqlQuery query;

    query.prepare("UPDATE RECYCLAGES SET "
                  "TYPE_MATERIAU = :materiau, "
                  "QUANTITE_ENTREE = :entree, "
                  "QUANTITE_RECYCLEE = :recycle, "
                  "QUANTITE_REJETEE = :rejet, "
                  "DESTINATION = :destination, "
                  "VALEUR_MONETAIRE = :valeur "
                  "WHERE ID_RECYCLAGE = :id");

    query.bindValue(":id", id);
    query.bindValue(":materiau", materiau);
    query.bindValue(":entree", qteEntree);
    query.bindValue(":recycle", qteRecyclee);
    query.bindValue(":rejet", qteRejetee);
    query.bindValue(":destination", destination);
    query.bindValue(":valeur", valeur);

    if(!query.exec())
    {
        qDebug() << "Erreur modification :" << query.lastError().text();
        return false;
    }

    return true;
}
