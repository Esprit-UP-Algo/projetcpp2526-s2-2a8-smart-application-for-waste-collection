#include "collecte.h"

Collecte::Collecte()
    : m_id(0), m_dateCollecte(""), m_typeDechet(""),
    m_quantiteCollectee(0.0), m_statut(""),
    m_distanceTotale(0.0), m_observations("")
{}

Collecte::Collecte(int id, const QString &dateCollecte, const QString &typeDechet,
                   double quantiteCollectee, const QString &statut,
                   double distanceTotale, const QString &observations)
    : m_id(id), m_dateCollecte(dateCollecte), m_typeDechet(typeDechet),
    m_quantiteCollectee(quantiteCollectee), m_statut(statut),
    m_distanceTotale(distanceTotale), m_observations(observations)
{}

// Getters
int     Collecte::getId()                const { return m_id; }
QString Collecte::getDateCollecte()      const { return m_dateCollecte; }
QString Collecte::getTypeDechet()        const { return m_typeDechet; }
double  Collecte::getQuantiteCollectee() const { return m_quantiteCollectee; }
QString Collecte::getStatut()            const { return m_statut; }
double  Collecte::getDistanceTotale()    const { return m_distanceTotale; }
QString Collecte::getObservations()      const { return m_observations; }

// Setters
void Collecte::setId(int id)                     { m_id                = id; }
void Collecte::setDateCollecte(const QString &v)  { m_dateCollecte      = v; }
void Collecte::setTypeDechet(const QString &v)    { m_typeDechet        = v; }
void Collecte::setQuantiteCollectee(double v)     { m_quantiteCollectee = v; }
void Collecte::setStatut(const QString &v)        { m_statut            = v; }
void Collecte::setDistanceTotale(double v)        { m_distanceTotale    = v; }
void Collecte::setObservations(const QString &v)  { m_observations      = v; }

// Validation
bool Collecte::estValide() const
{
    return !m_dateCollecte.trimmed().isEmpty()
    && !m_typeDechet.trimmed().isEmpty()
        && m_quantiteCollectee > 0.0
        && !m_statut.trimmed().isEmpty();
}

// CRUD
bool Collecte::ajouter()
{
    QSqlQuery queryId;
    if (!queryId.exec("SELECT NVL(MAX(ID_collecte),0)+1 FROM COLLECTES"))
        return false;
    if (queryId.next()) m_id = queryId.value(0).toInt();

    QSqlQuery query;
    query.prepare(
        "INSERT INTO COLLECTES (ID_collecte, Date_collecte, Type_dechet, "
        "Quantite_collectee, Statut, Distance_totale, Observations) "
        "VALUES (:id, TO_DATE(:date,'DD/MM/YYYY'), :type, :qte, :statut, :dist, :obs)"
        );
    query.bindValue(":id",     m_id);
    query.bindValue(":date",   m_dateCollecte);
    query.bindValue(":type",   m_typeDechet);
    query.bindValue(":qte",    m_quantiteCollectee);
    query.bindValue(":statut", m_statut);
    query.bindValue(":dist",   m_distanceTotale);
    query.bindValue(":obs",    m_observations);
    return query.exec();
}

bool Collecte::modifier()
{
    QSqlQuery query;
    query.prepare(
        "UPDATE COLLECTES SET "
        "Date_collecte=TO_DATE(:date,'DD/MM/YYYY'), Type_dechet=:type, "
        "Quantite_collectee=:qte, Statut=:statut, "
        "Distance_totale=:dist, Observations=:obs "
        "WHERE ID_collecte=:id"
        );
    query.bindValue(":date",   m_dateCollecte);
    query.bindValue(":type",   m_typeDechet);
    query.bindValue(":qte",    m_quantiteCollectee);
    query.bindValue(":statut", m_statut);
    query.bindValue(":dist",   m_distanceTotale);
    query.bindValue(":obs",    m_observations);
    query.bindValue(":id",     m_id);
    return query.exec();
}

bool Collecte::supprimer(int id)
{
    QSqlQuery query;
    query.prepare("DELETE FROM COLLECTES WHERE ID_collecte = :id");
    query.bindValue(":id", id);
    return query.exec();
}

QList<Collecte> Collecte::getAll()
{
    QList<Collecte> liste;
    QSqlQuery query;
    if (!query.exec(
            "SELECT ID_collecte, TO_CHAR(Date_collecte,'DD/MM/YYYY'), "
            "Type_dechet, Quantite_collectee, Statut, "
            "Distance_totale, Observations FROM COLLECTES ORDER BY ID_collecte"))
        return liste;

    while (query.next()) {
        Collecte c(
            query.value(0).toInt(),
            query.value(1).toString(),
            query.value(2).toString(),
            query.value(3).toDouble(),
            query.value(4).toString(),
            query.value(5).toDouble(),
            query.value(6).toString()
            );
        liste.append(c);
    }
    return liste;
}

Collecte Collecte::getById(int id)
{
    QSqlQuery query;
    query.prepare(
        "SELECT ID_collecte, TO_CHAR(Date_collecte,'DD/MM/YYYY'), "
        "Type_dechet, Quantite_collectee, Statut, Distance_totale, Observations "
        "FROM COLLECTES WHERE ID_collecte = :id"
        );
    query.bindValue(":id", id);
    if (query.exec() && query.next()) {
        return Collecte(
            query.value(0).toInt(),
            query.value(1).toString(),
            query.value(2).toString(),
            query.value(3).toDouble(),
            query.value(4).toString(),
            query.value(5).toDouble(),
            query.value(6).toString()
            );
    }
    return Collecte();
}
