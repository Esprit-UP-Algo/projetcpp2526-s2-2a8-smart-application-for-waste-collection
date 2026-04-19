#ifndef EXPORTER_H
#define EXPORTER_H

#include <QWidget>
#include <QString>

// ================================================================
// === CLASSE EXPORTER — FICHIER PARTAGÉ ==========================
// Chaque membre de l'équipe ajoute sa classe d'export ici.
// NE PAS modifier les méthodes des autres membres.
// ================================================================


// ================================================================
// === MODULE EMPLOYE — MARYEM ====================================
// ================================================================
class EmployeExporter
{
public:
    EmployeExporter() = default;

    /**
     * Affiche un aperçu HTML de la liste des employés et permet
     * de l'enregistrer en PDF via une boîte de dialogue.
     * @param parent  Le widget parent (généralement MainWindow).
     */
    void exporterPDF(QWidget *parent);

private:
    /** Construit le code HTML complet de la liste des employés. */
    QString construireHTML();
};


// ================================================================
// === MODULE CLIENT — [NOM DU MEMBRE] ============================
// Ajouter ici la classe ClientExporter
// ================================================================
// class ClientExporter { ... };


// ================================================================
// === MODULE CONTENEUR — [NOM DU MEMBRE] =========================
// Ajouter ici la classe ConteneurExporter
// ================================================================
// class ConteneurExporter { ... };


// ================================================================
// === MODULE COLLECTE — [NOM DU MEMBRE] ==========================
// Ajouter ici la classe CollecteExporter
// ================================================================
// class CollecteExporter { ... };


// ================================================================
// === MODULE RECYCLAGE — [NOM DU MEMBRE] =========================
// Ajouter ici la classe RecyclageExporter
// ================================================================
// class RecyclageExporter { ... };


#endif // EXPORTER_H
