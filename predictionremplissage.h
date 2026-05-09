#ifndef PREDICTIONREMPLISSAGE_H
#define PREDICTIONREMPLISSAGE_H

#include <QWidget>
#include <QDialog>
#include <QString>
#include <QList>

/**
 * Données enrichies d'un conteneur pour la prédiction de remplissage.
 *
 * Nouveautés v2 :
 *  - zone              : "centre" | "residentiel" | "industriel"
 *  - facteurZone       : multiplicateur appliqué au taux journalier
 *  - facteurCapacite   : ajustement selon la taille du conteneur
 *  - tauxJournalier    : taux final utilisé pour la prédiction (pour débogage/affichage)
 */
struct ConteneurPrediction {
    int     id;
    double  capacite;               // en litres
    QString adresse;
    QString etat;
    QString typePropriete;
    QString zone;                   // ← nouveau : zone géographique

    int     joursDepuisCollecte;    // calculé depuis Date_derniere_collecte
    double  tauxRemplissageEstime;  // 0.0 → 1.0  (taux courant estimé)
    double  tauxJournalier;         // taux final utilisé (pour info dashboard)
    double  facteurZone;            // ex : 1.5 pour centre
    double  facteurCapacite;        // ex : 1.2 pour petit conteneur
    int     joursAvantPlein;        // prédiction : jours restants avant saturation
    QString niveauAlerte;           // "OK" | "Attention" | "Critique"
};

class PredictionRemplissage
{
public:
    PredictionRemplissage() = default;

    /**
     * Charge les conteneurs depuis la BD, estime leur taux de remplissage
     * et calcule la prédiction du nombre de jours avant remplissage complet.
     */
    QList<ConteneurPrediction> calculerPredictions();

    /**
     * Affiche le dashboard de prédiction dans une QDialog stylisée.
     * @param parent  Le widget parent (généralement MainWindow).
     */
    void afficherPredictions(QWidget *parent);

private:
    /**
     * Estime le taux journalier DE BASE à partir de l'historique CONSOMMER/COLLECTES.
     * Retourne une valeur entre 0.01 et 0.25 (1% à 25% par jour).
     *
     * @param idConteneur   ID du conteneur dans CONTENEURS
     * @param typePropriete Type propriété ("public", "privé", etc.) — fallback si pas d'historique
     */
    double estimer_taux_base(int idConteneur, const QString &typePropriete) const;

    /**
     * Retourne le facteur multiplicateur lié à la zone.
     *  - centre      → 1.5  (zone dense, forte utilisation)
     *  - residentiel → 1.0  (référence)
     *  - industriel  → 0.8  (flux irréguliers mais moins fréquents)
     */
    static double facteur_zone(const QString &zone);

    /**
     * Retourne le facteur lié à la capacité du conteneur.
     * Logique : un petit conteneur se remplit plus vite proportionnellement.
     *  - capacite < 100 L   → 1.30
     *  - 100 ≤ capacite < 500 → 1.10
     *  - 500 ≤ capacite < 1500 → 1.00  (référence)
     *  - capacite ≥ 1500 L  → 0.85
     */
    static double facteur_capacite(double capacite);

    /**
     * Retourne emoji + libellé court pour une zone donnée (affichage dashboard).
     */
    static QString zoneLabel(const QString &zone);

    /**
     * Retourne la couleur hexadécimale associée à une zone (badge dashboard).
     */
    static QString zoneCouleur(const QString &zone);
};

#endif // PREDICTIONREMPLISSAGE_H
