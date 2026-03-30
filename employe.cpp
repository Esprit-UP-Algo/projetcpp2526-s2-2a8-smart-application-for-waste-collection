#include "employe.h"
#include <QSqlError>

Employe::Employe(QString cin, QString nom, QString prenom,
                 QString email, QString poste, QString telephone,
                 double salaire, QString dateEmbauche, QString service)
{
    this->cin          = cin;
    this->nom          = nom;
    this->prenom       = prenom;
    this->email        = email;
    this->poste        = poste;
    this->telephone    = telephone;
    this->salaire      = salaire;
    this->dateEmbauche = dateEmbauche;
    this->service      = service;
}

bool Employe::ajouter()
{
    QSqlQuery query;
    query.prepare(
        "INSERT INTO EMPLOYES (CIN, Nom, Prenom, Email, Poste, Telephone, "
        "Salaire, Date_embauche, Service) "
        "VALUES (:cin, :nom, :prenom, :email, :poste, :tel, :salaire, "
        "TO_DATE(:date, 'DD/MM/YYYY'), :service)"
        );
    query.bindValue(":cin",     cin);
    query.bindValue(":nom",     nom);
    query.bindValue(":prenom",  prenom);
    query.bindValue(":email",   email);
    query.bindValue(":poste",   poste);
    query.bindValue(":tel",     telephone);
    query.bindValue(":salaire", salaire);
    query.bindValue(":date",    dateEmbauche);
    query.bindValue(":service", service);
    return query.exec();
}

QSqlQueryModel* Employe::afficher()
{
    QSqlQueryModel *model = new QSqlQueryModel();
    model->setQuery(
        "SELECT CIN, Nom, Prenom, Email, Poste, Telephone, "
        "Date_embauche, Salaire, Service FROM EMPLOYES"
        );
    model->setHeaderData(0, Qt::Horizontal, "CIN");
    model->setHeaderData(1, Qt::Horizontal, "Nom");
    model->setHeaderData(2, Qt::Horizontal, "Prenom");
    model->setHeaderData(3, Qt::Horizontal, "Email");
    model->setHeaderData(4, Qt::Horizontal, "Poste");
    model->setHeaderData(5, Qt::Horizontal, "Telephone");
    model->setHeaderData(6, Qt::Horizontal, "Date Embauche");
    model->setHeaderData(7, Qt::Horizontal, "Salaire");
    model->setHeaderData(8, Qt::Horizontal, "Service");
    return model;
}

bool Employe::supprimer(QString cin)
{
    QSqlQuery query;
    query.prepare("DELETE FROM EMPLOYES WHERE CIN = :cin");
    query.bindValue(":cin", cin);
    return query.exec();
}

bool Employe::modifier(QString cin)
{
    QSqlQuery query;
    query.prepare(
        "UPDATE EMPLOYES SET "
        "Nom=:nom, Prenom=:prenom, Email=:email, Poste=:poste, "
        "Telephone=:tel, Salaire=:salaire, "
        "Date_embauche=TO_DATE(:date, 'DD/MM/YYYY'), "
        "Service=:service "
        "WHERE CIN=:cin"
        );
    query.bindValue(":nom",     nom);
    query.bindValue(":prenom",  prenom);
    query.bindValue(":email",   email);
    query.bindValue(":poste",   poste);
    query.bindValue(":tel",     telephone);
    query.bindValue(":salaire", salaire);
    query.bindValue(":date",    dateEmbauche);
    query.bindValue(":service", service);
    query.bindValue(":cin",     cin);
    return query.exec();
}
