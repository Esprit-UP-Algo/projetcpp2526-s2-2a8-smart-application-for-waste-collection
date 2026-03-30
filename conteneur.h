#ifndef CONTENEUR_H
#define CONTENEUR_H

#include <QString>
#include <QList>
#include <QSqlQuery>
#include <QSqlError>
#ifndef CONTENEUR_H
#endif // CONTENEUR_H

class Conteneur
{
public:
    Conteneur();
    Conteneur(int id, double capacite, const QString &typePropriete,
              const QString &adresseComplete, const QString &localisationGPS,
              const QString &accepteMenager, const QString &accepteRecyclable,
              const QString &accepteOrganique, const QString &accepteIndustriel,
              const QString &etat, const QString &dateDerniereCollecte);

    // Getters
    int     getId()                    const;
    double  getCapacite()              const;
    QString getTypePropriete()         const;
    QString getAdresseComplete()       const;
    QString getLocalisationGPS()       const;
    QString getAccepteMenager()        const;
    QString getAccepteRecyclable()     const;
    QString getAccepteOrganique()      const;
    QString getAccepteIndustriel()     const;
    QString getEtat()                  const;
    QString getDateDerniereCollecte()  const;
    int totalConteneurs;
    int avecValeur;
    int avecDestination;

    // Setters
    void setId(int id);
    void setCapacite(double v);
    void setTypePropriete(const QString &v);
    void setAdresseComplete(const QString &v);
    void setLocalisationGPS(const QString &v);
    void setAccepteMenager(const QString &v);
    void setAccepteRecyclable(const QString &v);
    void setAccepteOrganique(const QString &v);
    void setAccepteIndustriel(const QString &v);
    void setEtat(const QString &v);
    void setDateDerniereCollecte(const QString &v);

    // CRUD
    bool ajouter();
    bool modifier();
    static bool supprimer(int id);
    static QList<Conteneur> getAll();
    static Conteneur getById(int id);

    // Validation
    bool estValide() const;

private:
    int     m_id;
    double  m_capacite;
    QString m_typePropriete;
    QString m_adresseComplete;
    QString m_localisationGPS;
    QString m_accepteMenager;
    QString m_accepteRecyclable;
    QString m_accepteOrganique;
    QString m_accepteIndustriel;
    QString m_etat;
    QString m_dateDerniereCollecte;
};


#endif // CONTENEUR_H
