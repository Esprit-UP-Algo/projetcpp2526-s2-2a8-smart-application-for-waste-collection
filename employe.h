#ifndef EMPLOYE_H
#define EMPLOYE_H

#include <QString>
#include <QSqlQuery>
#include <QSqlQueryModel>

class Employe
{
private:
    QString cin;
    QString nom;
    QString prenom;
    QString email;
    QString poste;
    QString telephone;
    double  salaire;
    QString dateEmbauche;
    QString service;

public:
    Employe() : salaire(0.0) {}
    Employe(QString cin, QString nom, QString prenom,
            QString email, QString poste, QString telephone,
            double salaire, QString dateEmbauche, QString service);

    // Getters
    QString getCin()          const { return cin; }
    QString getNom()          const { return nom; }
    QString getPrenom()       const { return prenom; }
    QString getEmail()        const { return email; }
    QString getPoste()        const { return poste; }
    QString getTelephone()    const { return telephone; }
    double  getSalaire()      const { return salaire; }
    QString getDateEmbauche() const { return dateEmbauche; }
    QString getService()      const { return service; }

    // Setters
    void setCin(QString v)          { cin          = v; }
    void setNom(QString v)          { nom          = v; }
    void setPrenom(QString v)       { prenom       = v; }
    void setEmail(QString v)        { email        = v; }
    void setPoste(QString v)        { poste        = v; }
    void setTelephone(QString v)    { telephone    = v; }
    void setSalaire(double v)       { salaire      = v; }
    void setDateEmbauche(QString v) { dateEmbauche = v; }
    void setService(QString v)      { service      = v; }

    // CRUD
    bool            ajouter();
    QSqlQueryModel* afficher();
    bool            supprimer(QString cin);
    bool            modifier(QString cin);
    int  compterClientsLies(QString cin);
    QList<QPair<QString,QString>> getListeCinNom();
};

#endif // EMPLOYE_H
