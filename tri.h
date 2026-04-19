#ifndef TRI_H
#define TRI_H

#include <QString>
#include <QStringList>
#include <QSqlQueryModel>

// ================================================================
// === CLASSE TRI — FICHIER PARTAGÉ ===============================
// Chaque membre de l'équipe ajoute sa méthode de tri ici.
// NE PAS modifier les méthodes des autres membres.
// ================================================================


// ================================================================
// === MODULE EMPLOYE — MARYEM ====================================
// ================================================================
class EmployeTri
{
public:
    EmployeTri() = default;

    /**
     * Retourne les employés triés par la colonne indiquée.
     * La colonne est vérifiée contre une liste blanche (anti-injection SQL).
     * @param colonne  Nom de la colonne BDD (ex: "Nom", "Salaire").
     * @return         Un QSqlQueryModel prêt à afficher (à delete par l'appelant).
     */
    QSqlQueryModel* trierPar(const QString &colonne);

    /** Liste des colonnes autorisées pour le tri (protection anti-injection). */
    static QStringList colonnesDisponibles();
};


// ================================================================
// === MODULE CLIENT — [NOM DU MEMBRE] ============================
// Ajouter ici la classe ClientTri
// ================================================================
// class ClientTri { ... };


// ================================================================
// === MODULE CONTENEUR — [NOM DU MEMBRE] =========================
// Ajouter ici la classe ConteneurTri
// ================================================================
// class ConteneurTri { ... };


// ================================================================
// === MODULE COLLECTE — [NOM DU MEMBRE] ==========================
// Ajouter ici la classe CollecteTri
// ================================================================
// class CollecteTri { ... };


// ================================================================
// === MODULE RECYCLAGE — [NOM DU MEMBRE] =========================
// Ajouter ici la classe RecyclageTri
// ================================================================
// class RecyclageTri { ... };


#endif // TRI_H
