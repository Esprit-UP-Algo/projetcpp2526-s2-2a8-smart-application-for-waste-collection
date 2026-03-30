#include "conteneur.h"

Conteneur::Conteneur()
    : m_id(0), m_capacite(0.0), m_typePropriete(""),
    m_adresseComplete(""), m_localisationGPS(""),
    m_accepteMenager("Non"), m_accepteRecyclable("Non"),
    m_accepteOrganique("Non"), m_accepteIndustriel("Non"),
    m_etat(""), m_dateDerniereCollecte("")
{}

Conteneur::Conteneur(int id, double capacite, const QString &typePropriete,
                     const QString &adresseComplete, const QString &localisationGPS,
                     const QString &accepteMenager, const QString &accepteRecyclable,
                     const QString &accepteOrganique, const QString &accepteIndustriel,
                     const QString &etat, const QString &dateDerniereCollecte)
    : m_id(id), m_capacite(capacite), m_typePropriete(typePropriete),
    m_adresseComplete(adresseComplete), m_localisationGPS(localisationGPS),
    m_accepteMenager(accepteMenager), m_accepteRecyclable(accepteRecyclable),
    m_accepteOrganique(accepteOrganique), m_accepteIndustriel(accepteIndustriel),
    m_etat(etat), m_dateDerniereCollecte(dateDerniereCollecte)
{}

// Getters
int     Conteneur::getId()                   const { return m_id; }
double  Conteneur::getCapacite()             const { return m_capacite; }
QString Conteneur::getTypePropriete()        const { return m_typePropriete; }
QString Conteneur::getAdresseComplete()      const { return m_adresseComplete; }
QString Conteneur::getLocalisationGPS()      const { return m_localisationGPS; }
QString Conteneur::getAccepteMenager()       const { return m_accepteMenager; }
QString Conteneur::getAccepteRecyclable()    const { return m_accepteRecyclable; }
QString Conteneur::getAccepteOrganique()     const { return m_accepteOrganique; }
QString Conteneur::getAccepteIndustriel()    const { return m_accepteIndustriel; }
QString Conteneur::getEtat()                 const { return m_etat; }
QString Conteneur::getDateDerniereCollecte() const { return m_dateDerniereCollecte; }

// Setters
void Conteneur::setId(int id)                         { m_id                   = id; }
void Conteneur::setCapacite(double v)                 { m_capacite             = v; }
void Conteneur::setTypePropriete(const QString &v)    { m_typePropriete        = v; }
void Conteneur::setAdresseComplete(const QString &v)  { m_adresseComplete      = v; }
void Conteneur::setLocalisationGPS(const QString &v)  { m_localisationGPS      = v; }
void Conteneur::setAccepteMenager(const QString &v)   { m_accepteMenager       = v; }
void Conteneur::setAccepteRecyclable(const QString &v){ m_accepteRecyclable    = v; }
void Conteneur::setAccepteOrganique(const QString &v) { m_accepteOrganique     = v; }
void Conteneur::setAccepteIndustriel(const QString &v){ m_accepteIndustriel    = v; }
void Conteneur::setEtat(const QString &v)             { m_etat                 = v; }
void Conteneur::setDateDerniereCollecte(const QString &v){ m_dateDerniereCollecte = v; }

// Validation
bool Conteneur::estValide() const
{
    return m_capacite > 0.0
           && !m_adresseComplete.trimmed().isEmpty()
           && !m_etat.trimmed().isEmpty();
}

// CRUD
bool Conteneur::ajouter()
{
    QSqlQuery queryId;
    if (!queryId.exec("SELECT NVL(MAX(ID_conteneur),0)+1 FROM CONTENEURS"))
        return false;
    if (queryId.next()) m_id = queryId.value(0).toInt();

    QSqlQuery query;
    query.prepare(
        "INSERT INTO CONTENEURS (ID_conteneur, Capacite, Type_propriete, "
        "Adresse_complete, Localisation_GPS, Accepte_menager, Accepte_recyclable, "
        "Accepte_organique, Accepte_industriel, Etat, Date_derniere_collecte) "
        "VALUES (:id, :cap, :tprop, :adr, :gps, :men, :rec, :org, :ind, "
        ":etat, TO_DATE(:date,'DD/MM/YYYY'))"
        );
    query.bindValue(":id",    m_id);
    query.bindValue(":cap",   m_capacite);
    query.bindValue(":tprop", m_typePropriete);
    query.bindValue(":adr",   m_adresseComplete);
    query.bindValue(":gps",   m_localisationGPS);
    query.bindValue(":men",   m_accepteMenager);
    query.bindValue(":rec",   m_accepteRecyclable);
    query.bindValue(":org",   m_accepteOrganique);
    query.bindValue(":ind",   m_accepteIndustriel);
    query.bindValue(":etat",  m_etat);
    query.bindValue(":date",  m_dateDerniereCollecte);
    return query.exec();
}

bool Conteneur::modifier()
{
    QSqlQuery query;
    query.prepare(
        "UPDATE CONTENEURS SET "
        "Capacite=:cap, Type_propriete=:tprop, Adresse_complete=:adr, "
        "Localisation_GPS=:gps, Accepte_menager=:men, Accepte_recyclable=:rec, "
        "Accepte_organique=:org, Accepte_industriel=:ind, Etat=:etat, "
        "Date_derniere_collecte=TO_DATE(:date,'DD/MM/YYYY') "
        "WHERE ID_conteneur=:id"
        );
    query.bindValue(":cap",   m_capacite);
    query.bindValue(":tprop", m_typePropriete);
    query.bindValue(":adr",   m_adresseComplete);
    query.bindValue(":gps",   m_localisationGPS);
    query.bindValue(":men",   m_accepteMenager);
    query.bindValue(":rec",   m_accepteRecyclable);
    query.bindValue(":org",   m_accepteOrganique);
    query.bindValue(":ind",   m_accepteIndustriel);
    query.bindValue(":etat",  m_etat);
    query.bindValue(":date",  m_dateDerniereCollecte);
    query.bindValue(":id",    m_id);
    return query.exec();
}

bool Conteneur::supprimer(int id)
{
    QSqlQuery query;
    query.prepare("DELETE FROM CONTENEURS WHERE ID_conteneur = :id");
    query.bindValue(":id", id);
    return query.exec();
}

QList<Conteneur> Conteneur::getAll()
{
    QList<Conteneur> liste;
    QSqlQuery query;
    if (!query.exec(
            "SELECT ID_conteneur, Capacite, Type_propriete, Adresse_complete, "
            "Localisation_GPS, Accepte_menager, Accepte_recyclable, "
            "Accepte_organique, Accepte_industriel, Etat, "
            "TO_CHAR(Date_derniere_collecte,'DD/MM/YYYY') "
            "FROM CONTENEURS ORDER BY ID_conteneur"))
        return liste;

    while (query.next()) {
        Conteneur c(
            query.value(0).toInt(),
            query.value(1).toDouble(),
            query.value(2).toString(),
            query.value(3).toString(),
            query.value(4).toString(),
            query.value(5).toString(),
            query.value(6).toString(),
            query.value(7).toString(),
            query.value(8).toString(),
            query.value(9).toString(),
            query.value(10).toString()
            );
        liste.append(c);
    }
    return liste;
}

Conteneur Conteneur::getById(int id)
{
    QSqlQuery query;
    query.prepare(
        "SELECT ID_conteneur, Capacite, Type_propriete, Adresse_complete, "
        "Localisation_GPS, Accepte_menager, Accepte_recyclable, "
        "Accepte_organique, Accepte_industriel, Etat, "
        "TO_CHAR(Date_derniere_collecte,'DD/MM/YYYY') "
        "FROM CONTENEURS WHERE ID_conteneur = :id"
        );
    query.bindValue(":id", id);
    if (query.exec() && query.next()) {
        return Conteneur(
            query.value(0).toInt(),
            query.value(1).toDouble(),
            query.value(2).toString(),
            query.value(3).toString(),
            query.value(4).toString(),
            query.value(5).toString(),
            query.value(6).toString(),
            query.value(7).toString(),
            query.value(8).toString(),
            query.value(9).toString(),
            query.value(10).toString()
            );
    }
    return Conteneur();
}



