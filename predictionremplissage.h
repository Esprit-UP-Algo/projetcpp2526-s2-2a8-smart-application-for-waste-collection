#ifndef PREDICTIONREMPLISSAGE_H
#define PREDICTIONREMPLISSAGE_H

#include <QWidget>
#include <QDialog>
#include <QString>
#include <QList>

/**
 * Données d'un conteneur enrichies pour la prédiction
 */
struct ConteneurPrediction {
    int     id;
    double  capacite;          // en litres
    QString adresse;
    QString etat;
    QString typePropriete;
    int     joursDepuisCollecte; // calculé depuis Date_derniere_collecte
    double  tauxRemplissageEstime; // 0.0 → 1.0
    int     joursAvantPlein;      // prédiction
    QString niveauAlerte;         // "OK", "Attention", "Critique"
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
     * Estime le taux de remplissage journalier moyen d'un conteneur
     * en se basant sur les collectes historiques dans COLLECTES.
     * Retourne un taux journalier entre 0.01 et 0.20 (1% à 20% par jour).
     */
    double estimer_taux_journalier(int idConteneur, const QString &typeDechet);
};

#endif // PREDICTIONREMPLISSAGE_H
