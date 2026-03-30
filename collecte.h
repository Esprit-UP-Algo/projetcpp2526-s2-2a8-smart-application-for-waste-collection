#ifndef COLLECTE_H
#define COLLECTE_H

#include <QString>
#include <QList>
#include <QSqlQuery>
#include <QSqlError>

class Collecte
{
public:
    // ================================================================
    // === CONSTRUCTEURS ==============================================
    // ================================================================
    Collecte();
    Collecte(int id, const QString &dateCollecte, const QString &typeDechet,
             double quantiteCollectee, const QString &statut,
             double distanceTotale, const QString &observations);

    // ================================================================
    // === GETTERS ====================================================
    // ================================================================
    int     getId()                 const;
    QString getDateCollecte()       const;
    QString getTypeDechet()         const;
    double  getQuantiteCollectee()  const;
    QString getStatut()             const;
    double  getDistanceTotale()     const;
    QString getObservations()       const;

    // ================================================================
    // === SETTERS ====================================================
    // ================================================================
    void setId(int id);
    void setDateCollecte(const QString &v);
    void setTypeDechet(const QString &v);
    void setQuantiteCollectee(double v);
    void setStatut(const QString &v);
    void setDistanceTotale(double v);
    void setObservations(const QString &v);

    // ================================================================
    // === CRUD DE BASE ===============================================
    // ================================================================
    bool ajouter();
    bool modifier();
    static bool supprimer(int id);
    static QList<Collecte> getAll();
    static Collecte getById(int id);

    // ================================================================
    // === FONCTIONS METIER BASIQUES ==================================
    // ================================================================

    // Trier les collectes selon date ou zone (observations)
    static QList<Collecte> trierParDate();
    static QList<Collecte> trierParZone();

    // Rechercher une collecte selon ID ou type de déchet
    static QList<Collecte> rechercherParId(int id);
    static QList<Collecte> rechercherParType(const QString &typeDechet);
    static QList<Collecte> rechercherParMotCle(const QString &motCle);

    // ================================================================
    // === FONCTIONS METIER INNOVANTES ================================
    // ================================================================

    // Statistiques des quantités collectées par type (pour graphique à barres)
    // Retourne une map : type_dechet -> quantite_totale
    static QMap<QString, double> statistiquesParType();

    // Statistiques générales
    static double quantiteTotale();
    static double quantiteMaximale();
    static double quantiteMinimale();
    static int    nombreCollectesParStatut(const QString &statut);

    // Historique des transactions (toutes les collectes triées par date desc)
    static QList<Collecte> historique();

    // Optimisation d'itinéraire IA : calcul du meilleur ordre de collecte
    // minimisant la distance totale (algorithme du plus proche voisin)
    static QList<int> optimiserItineraire(const QList<int> &idsCollectes);

    // ================================================================
    // === VALIDATION =================================================
    // ================================================================
    bool estValide() const;

private:
    int     m_id;
    QString m_dateCollecte;
    QString m_typeDechet;
    double  m_quantiteCollectee;
    QString m_statut;
    double  m_distanceTotale;
    QString m_observations;
};

#endif // COLLECTE_H
