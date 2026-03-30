#include "collecte.h"
#include <QMap>
#include <QDebug>

// ================================================================
// === CONSTRUCTEURS ==============================================
// ================================================================

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

// ================================================================
// === GETTERS ====================================================
// ================================================================
int     Collecte::getId()                const { return m_id; }
QString Collecte::getDateCollecte()      const { return m_dateCollecte; }
QString Collecte::getTypeDechet()        const { return m_typeDechet; }
double  Collecte::getQuantiteCollectee() const { return m_quantiteCollectee; }
QString Collecte::getStatut()            const { return m_statut; }
double  Collecte::getDistanceTotale()    const { return m_distanceTotale; }
QString Collecte::getObservations()      const { return m_observations; }

// ================================================================
// === SETTERS ====================================================
// ================================================================
void Collecte::setId(int id)                     { m_id                = id; }
void Collecte::setDateCollecte(const QString &v)  { m_dateCollecte      = v; }
void Collecte::setTypeDechet(const QString &v)    { m_typeDechet        = v; }
void Collecte::setQuantiteCollectee(double v)     { m_quantiteCollectee = v; }
void Collecte::setStatut(const QString &v)        { m_statut            = v; }
void Collecte::setDistanceTotale(double v)        { m_distanceTotale    = v; }
void Collecte::setObservations(const QString &v)  { m_observations      = v; }

// ================================================================
// === VALIDATION =================================================
// ================================================================
bool Collecte::estValide() const
{
    return !m_dateCollecte.trimmed().isEmpty()
        && !m_typeDechet.trimmed().isEmpty()
        && m_quantiteCollectee > 0.0
        && !m_statut.trimmed().isEmpty();
}

// ================================================================
// === CRUD DE BASE ===============================================
// ================================================================

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

// ================================================================
// === FONCTIONS METIER BASIQUES ==================================
// ================================================================

// 1. Trier les collectes par date (du plus récent au plus ancien)
QList<Collecte> Collecte::trierParDate()
{
    QList<Collecte> liste;
    QSqlQuery query;
    if (!query.exec(
            "SELECT ID_collecte, TO_CHAR(Date_collecte,'DD/MM/YYYY'), "
            "Type_dechet, Quantite_collectee, Statut, "
            "Distance_totale, Observations "
            "FROM COLLECTES ORDER BY Date_collecte DESC"))
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

// 2. Trier les collectes par zone (stockée dans Observations)
QList<Collecte> Collecte::trierParZone()
{
    QList<Collecte> liste;
    QSqlQuery query;
    if (!query.exec(
            "SELECT ID_collecte, TO_CHAR(Date_collecte,'DD/MM/YYYY'), "
            "Type_dechet, Quantite_collectee, Statut, "
            "Distance_totale, Observations "
            "FROM COLLECTES ORDER BY Observations ASC"))
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

// 3. Rechercher par ID
QList<Collecte> Collecte::rechercherParId(int id)
{
    QList<Collecte> liste;
    Collecte c = getById(id);
    if (c.getId() != 0)
        liste.append(c);
    return liste;
}

// 4. Rechercher par type de déchet
QList<Collecte> Collecte::rechercherParType(const QString &typeDechet)
{
    QList<Collecte> liste;
    QSqlQuery query;
    query.prepare(
        "SELECT ID_collecte, TO_CHAR(Date_collecte,'DD/MM/YYYY'), "
        "Type_dechet, Quantite_collectee, Statut, "
        "Distance_totale, Observations "
        "FROM COLLECTES WHERE UPPER(Type_dechet) LIKE UPPER(:type) "
        "ORDER BY Date_collecte DESC"
        );
    query.bindValue(":type", "%" + typeDechet + "%");

    if (!query.exec()) return liste;

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

// 5. Rechercher par mot-clé (ID ou type de déchet)
QList<Collecte> Collecte::rechercherParMotCle(const QString &motCle)
{
    QList<Collecte> liste;
    QSqlQuery query;
    QString motif = "%" + motCle + "%";

    // Essai de recherche par ID (si motCle est un nombre)
    bool isNum;
    int idTente = motCle.toInt(&isNum);
    if (isNum) {
        Collecte c = getById(idTente);
        if (c.getId() != 0) {
            liste.append(c);
            return liste;
        }
    }

    // Sinon recherche par type déchet ou statut ou observations
    query.prepare(
        "SELECT ID_collecte, TO_CHAR(Date_collecte,'DD/MM/YYYY'), "
        "Type_dechet, Quantite_collectee, Statut, "
        "Distance_totale, Observations "
        "FROM COLLECTES "
        "WHERE UPPER(Type_dechet)  LIKE UPPER(:r1) "
        "   OR UPPER(Statut)       LIKE UPPER(:r2) "
        "   OR UPPER(Observations) LIKE UPPER(:r3) "
        "ORDER BY Date_collecte DESC"
        );
    query.bindValue(":r1", motif);
    query.bindValue(":r2", motif);
    query.bindValue(":r3", motif);

    if (!query.exec()) return liste;

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

// ================================================================
// === FONCTIONS METIER INNOVANTES ================================
// ================================================================

// 6. Statistiques quantités collectées par type (pour graphique à barres)
QMap<QString, double> Collecte::statistiquesParType()
{
    QMap<QString, double> stats;
    QSqlQuery query;
    if (!query.exec(
            "SELECT Type_dechet, SUM(Quantite_collectee) "
            "FROM COLLECTES "
            "GROUP BY Type_dechet "
            "ORDER BY Type_dechet"))
        return stats;

    while (query.next()) {
        QString type = query.value(0).toString();
        double  qte  = query.value(1).toDouble();
        if (!type.isEmpty())
            stats.insert(type, qte);
    }

    // S'assurer que tous les types standards sont présents
    QStringList typesStandards = {"Ménager", "Recyclable", "Organique", "Industriel", "Mixte"};
    for (const QString &t : typesStandards) {
        if (!stats.contains(t))
            stats.insert(t, 0.0);
    }

    return stats;
}

// 7. Quantité totale collectée
double Collecte::quantiteTotale()
{
    QSqlQuery query;
    if (query.exec("SELECT NVL(SUM(Quantite_collectee), 0) FROM COLLECTES") && query.next())
        return query.value(0).toDouble();
    return 0.0;
}

// 8. Quantité maximale
double Collecte::quantiteMaximale()
{
    QSqlQuery query;
    if (query.exec("SELECT NVL(MAX(Quantite_collectee), 0) FROM COLLECTES") && query.next())
        return query.value(0).toDouble();
    return 0.0;
}

// 9. Quantité minimale
double Collecte::quantiteMinimale()
{
    QSqlQuery query;
    if (query.exec("SELECT NVL(MIN(Quantite_collectee), 0) FROM COLLECTES") && query.next())
        return query.value(0).toDouble();
    return 0.0;
}

// 10. Nombre de collectes par statut
int Collecte::nombreCollectesParStatut(const QString &statut)
{
    QSqlQuery query;
    query.prepare("SELECT COUNT(*) FROM COLLECTES WHERE UPPER(Statut) = UPPER(:s)");
    query.bindValue(":s", statut);
    if (query.exec() && query.next())
        return query.value(0).toInt();
    return 0;
}

// 11. Historique des transactions (toutes collectes triées par date desc)
QList<Collecte> Collecte::historique()
{
    QList<Collecte> liste;
    QSqlQuery query;
    if (!query.exec(
            "SELECT ID_collecte, TO_CHAR(Date_collecte,'DD/MM/YYYY HH24:MI'), "
            "Type_dechet, Quantite_collectee, Statut, "
            "Distance_totale, Observations "
            "FROM COLLECTES ORDER BY Date_collecte DESC, ID_collecte DESC"))
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

// 12. Optimisation d'itinéraire par IA (algorithme du plus proche voisin)
// Principe : minimise la distance totale en choisissant toujours
// la collecte la plus proche de la position courante (distance_totale comme proxy)
QList<int> Collecte::optimiserItineraire(const QList<int> &idsCollectes)
{
    if (idsCollectes.isEmpty()) return QList<int>();

    // Charger les collectes demandées
    QList<Collecte> collectes;
    for (int id : idsCollectes) {
        Collecte c = getById(id);
        if (c.getId() != 0)
            collectes.append(c);
    }

    if (collectes.isEmpty()) return QList<int>();

    // Algorithme du plus proche voisin (greedy nearest neighbor)
    // On utilise Distance_totale comme valeur de "position" pour estimer l'ordre
    QList<int> itineraireOptimise;
    QList<bool> visite(collectes.size(), false);

    // Point de départ : collecte avec la plus petite distance (dépôt le plus proche)
    int indexDepart = 0;
    double distMin = collectes[0].getDistanceTotale();
    for (int i = 1; i < collectes.size(); ++i) {
        if (collectes[i].getDistanceTotale() < distMin) {
            distMin = collectes[i].getDistanceTotale();
            indexDepart = i;
        }
    }

    int courant = indexDepart;
    itineraireOptimise.append(collectes[courant].getId());
    visite[courant] = true;

    // Trouver le voisin le plus proche non encore visité
    for (int etape = 1; etape < collectes.size(); ++etape) {
        double meilleureDistance = -1.0;
        int prochainIndex = -1;

        for (int j = 0; j < collectes.size(); ++j) {
            if (visite[j]) continue;

            // Différence de distance comme estimation de proximité
            double diff = qAbs(collectes[j].getDistanceTotale()
                               - collectes[courant].getDistanceTotale());

            if (meilleureDistance < 0.0 || diff < meilleureDistance) {
                meilleureDistance = diff;
                prochainIndex = j;
            }
        }

        if (prochainIndex >= 0) {
            courant = prochainIndex;
            itineraireOptimise.append(collectes[courant].getId());
            visite[courant] = true;
        }
    }

    return itineraireOptimise;
}
