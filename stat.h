#ifndef STAT_H
#define STAT_H

#include <QWidget>
#include <QString>

// ================================================================
// === CLASSE STAT — FICHIER PARTAGÉ ==============================
// Chaque membre de l'équipe ajoute sa classe de statistiques ici.
// NE PAS modifier les méthodes des autres membres.
// ================================================================


// ================================================================
// === MODULE EMPLOYE — MARYEM ====================================
// ================================================================
class EmployeStat
{
public:
    EmployeStat() = default;

    /**
     * Calcule les statistiques des employés et affiche le dashboard
     * dans une QDialog modale.
     * @param parent  Le widget parent (généralement MainWindow).
     */
    void afficherStatistiques(QWidget *parent);

private:
    // ── Données calculées (remplies par calculer()) ───────────
    int    totalEmployes  = 0;
    int    withEmail      = 0;
    int    postesDefinis  = 0;
    int    serviceIT      = 0;
    int    serviceRH      = 0;
    int    serviceFinance = 0;
    double salaireMoyen   = 0.0;
    double salaireMax     = 0.0;
    double salaireMin     = 0.0;

    /** Exécute toutes les requêtes SQL et remplit les membres privés. */
    void calculer();
};


// ================================================================
// === MODULE CLIENT — [NOM DU MEMBRE] ============================
// Ajouter ici la classe ClientStat
// ================================================================
// class ClientStat { ... };


// ================================================================
// === MODULE CONTENEUR — [NOM DU MEMBRE] =========================
// Ajouter ici la classe ConteneurStat
// ================================================================
// class ConteneurStat { ... };


// ================================================================
// === MODULE COLLECTE — [NOM DU MEMBRE] ==========================
// Ajouter ici la classe CollecteStat
// ================================================================
// class CollecteStat { ... };


// ================================================================
// === MODULE RECYCLAGE — [NOM DU MEMBRE] =========================
// Ajouter ici la classe RecyclageStat
// ================================================================
// class RecyclageStat { ... };


#endif // STAT_H
