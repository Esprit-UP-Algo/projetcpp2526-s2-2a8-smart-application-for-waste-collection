#include "recyclage.h"

Recyclage::Recyclage()
    : m_id(0), m_dateTri(""), m_typeMateriau(""),
    m_quantiteEntree(0.0), m_quantiteRecyclee(0.0), m_quantiteRejetee(0.0),
    m_destination(""), m_valeurMonetaire(0.0), m_direction(""), m_statut("")
{}

Recyclage::Recyclage(int id, const QString &dateTri, const QString &typeMateriau,
                     double quantiteEntree, double quantiteRecyclee, double quantiteRejetee,
                     const QString &destination, double valeurMonetaire,
                     const QString &direction, const QString &statut)
    : m_id(id), m_dateTri(dateTri), m_typeMateriau(typeMateriau),
    m_quantiteEntree(quantiteEntree), m_quantiteRecyclee(quantiteRecyclee),
    m_quantiteRejetee(quantiteRejetee), m_destination(destination),
    m_valeurMonetaire(valeurMonetaire), m_direction(direction), m_statut(statut)
{}

// Getters
int     Recyclage::getId()               const { return m_id; }
QString Recyclage::getDateTri()          const { return m_dateTri; }
QString Recyclage::getTypeMateriau()     const { return m_typeMateriau; }
double  Recyclage::getQuantiteEntree()   const { return m_quantiteEntree; }
double  Recyclage::getQuantiteRecyclee() const { return m_quantiteRecyclee; }
double  Recyclage::getQuantiteRejetee()  const { return m_quantiteRejetee; }
QString Recyclage::getDestination()      const { return m_destination; }
double  Recyclage::getValeurMonetaire()  const { return m_valeurMonetaire; }
QString Recyclage::getDirection()        const { return m_direction; }
QString Recyclage::getStatut()           const { return m_statut; }

// Setters
void Recyclage::setId(int id)                        { m_id               = id; }
void Recyclage::setDateTri(const QString &v)         { m_dateTri          = v; }
void Recyclage::setTypeMateriau(const QString &v)    { m_typeMateriau     = v; }
void Recyclage::setQuantiteEntree(double v)          { m_quantiteEntree   = v; }
void Recyclage::setQuantiteRecyclee(double v)        { m_quantiteRecyclee = v; }
void Recyclage::setQuantiteRejetee(double v)         { m_quantiteRejetee  = v; }
void Recyclage::setDestination(const QString &v)     { m_destination      = v; }
void Recyclage::setValeurMonetaire(double v)         { m_valeurMonetaire  = v; }
void Recyclage::setDirection(const QString &v)       { m_direction        = v; }
void Recyclage::setStatut(const QString &v)          { m_statut           = v; }

// Validation
bool Recyclage::estValide() const
{
    return !m_dateTri.trimmed().isEmpty()
    && !m_typeMateriau.trimmed().isEmpty()
        && m_quantiteEntree > 0.0
        && !m_destination.trimmed().isEmpty()
        && !m_statut.trimmed().isEmpty();
}

// CRUD
bool Recyclage::ajouter()
{
    QSqlQuery queryId;
    if (!queryId.exec("SELECT NVL(MAX(ID_recyclage),0)+1 FROM RECYCLAGES"))
        return false;
    if (queryId.next()) m_id = queryId.value(0).toInt();

    QSqlQuery query;
    query.prepare(
        "INSERT INTO RECYCLAGES (ID_recyclage, Date_tri, Type_materiau, "
        "Quantite_entree, Quantite_recyclee, Quantite_rejetee, "
        "Destination, Valeur_monetaire, Direction, Statut) "
        "VALUES (:id, TO_DATE(:date,'DD/MM/YYYY'), :type, :qte_e, "
        ":qte_r, :qte_rej, :dest, :valeur, :dir, :statut)"
        );
    query.bindValue(":id",     m_id);
    query.bindValue(":date",   m_dateTri);
    query.bindValue(":type",   m_typeMateriau);
    query.bindValue(":qte_e",  m_quantiteEntree);
    query.bindValue(":qte_r",  m_quantiteRecyclee);
    query.bindValue(":qte_rej",m_quantiteRejetee);
    query.bindValue(":dest",   m_destination);
    query.bindValue(":valeur", m_valeurMonetaire);
    query.bindValue(":dir",    m_direction);
    query.bindValue(":statut", m_statut);
    return query.exec();
}

bool Recyclage::modifier()
{
    QSqlQuery query;
    query.prepare(
        "UPDATE RECYCLAGES SET "
        "Date_tri=TO_DATE(:date,'DD/MM/YYYY'), Type_materiau=:type, "
        "Quantite_entree=:qte_e, Quantite_recyclee=:qte_r, "
        "Quantite_rejetee=:qte_rej, Destination=:dest, "
        "Valeur_monetaire=:valeur, Direction=:dir, Statut=:statut "
        "WHERE ID_recyclage=:id"
        );
    query.bindValue(":date",   m_dateTri);
    query.bindValue(":type",   m_typeMateriau);
    query.bindValue(":qte_e",  m_quantiteEntree);
    query.bindValue(":qte_r",  m_quantiteRecyclee);
    query.bindValue(":qte_rej",m_quantiteRejetee);
    query.bindValue(":dest",   m_destination);
    query.bindValue(":valeur", m_valeurMonetaire);
    query.bindValue(":dir",    m_direction);
    query.bindValue(":statut", m_statut);
    query.bindValue(":id",     m_id);
    return query.exec();
}

bool Recyclage::supprimer(int id)
{
    QSqlQuery query;
    query.prepare("DELETE FROM RECYCLAGES WHERE ID_recyclage = :id");
    query.bindValue(":id", id);
    return query.exec();
}

QList<Recyclage> Recyclage::getAll()
{
    QList<Recyclage> liste;
    QSqlQuery query;
    if (!query.exec(
            "SELECT ID_recyclage, TO_CHAR(Date_tri,'DD/MM/YYYY'), Type_materiau, "
            "Quantite_entree, Quantite_recyclee, Quantite_rejetee, "
            "Destination, Valeur_monetaire, Direction, Statut "
            "FROM RECYCLAGES ORDER BY ID_recyclage"))
        return liste;

    while (query.next()) {
        Recyclage r(
            query.value(0).toInt(),
            query.value(1).toString(),
            query.value(2).toString(),
            query.value(3).toDouble(),
            query.value(4).toDouble(),
            query.value(5).toDouble(),
            query.value(6).toString(),
            query.value(7).toDouble(),
            query.value(8).toString(),
            query.value(9).toString()
            );
        liste.append(r);
    }
    return liste;
}

Recyclage Recyclage::getById(int id)
{
    QSqlQuery query;
    query.prepare(
        "SELECT ID_recyclage, TO_CHAR(Date_tri,'DD/MM/YYYY'), Type_materiau, "
        "Quantite_entree, Quantite_recyclee, Quantite_rejetee, "
        "Destination, Valeur_monetaire, Direction, Statut "
        "FROM RECYCLAGES WHERE ID_recyclage = :id"
        );
    query.bindValue(":id", id);
    if (query.exec() && query.next()) {
        return Recyclage(
            query.value(0).toInt(),
            query.value(1).toString(),
            query.value(2).toString(),
            query.value(3).toDouble(),
            query.value(4).toDouble(),
            query.value(5).toDouble(),
            query.value(6).toString(),
            query.value(7).toDouble(),
            query.value(8).toString(),
            query.value(9).toString()
            );
    }
    return Recyclage();
}
