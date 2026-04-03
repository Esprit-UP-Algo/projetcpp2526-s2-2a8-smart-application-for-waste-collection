#ifndef RECHERCHE_H
#define RECHERCHE_H

#include <QString>
#include <QSqlQueryModel>

// ================================================================
// === CLASSE RECHERCHE — FICHIER PARTAGÉ =========================
// Chaque membre de l'équipe ajoute sa méthode de recherche ici.
// NE PAS modifier les méthodes des autres membres.
// ================================================================


// ================================================================
// === MODULE EMPLOYE — MARYEM ====================================
// ================================================================
class EmployeRecherche
{
public:
    EmployeRecherche() = default;

    /**
     * Recherche dans la table EMPLOYES sur tous les champs texte.
     * @param texte  Le texte saisi dans la barre de recherche.
     * @return       Un QSqlQueryModel prêt à être affiché (à delete par l'appelant).
     */
    QSqlQueryModel* rechercher(const QString &texte);
};


// ================================================================
// === MODULE CLIENT — [NOM DU MEMBRE] ============================
// Ajouter ici la classe ClientRecherche
// ================================================================
// class ClientRecherche { ... };


// ================================================================
// === MODULE CONTENEUR — [NOM DU MEMBRE] =========================
// Ajouter ici la classe ConteneurRecherche
// ================================================================
// class ConteneurRecherche { ... };


// ================================================================
// === MODULE COLLECTE — [NOM DU MEMBRE] ==========================
// Ajouter ici la classe CollecteRecherche
// ================================================================
// class CollecteRecherche { ... };


// ================================================================
// === MODULE RECYCLAGE — [NOM DU MEMBRE] =========================
// Ajouter ici la classe RecyclageRecherche
// ================================================================
// class RecyclageRecherche { ... };


#endif // RECHERCHE_H
