#ifndef CONTENEUR_H
#define CONTENEUR_H
#include <QString>
#include <QList>
#include <QTableWidget>
#include <QWidget>
#include <QSqlQuery>
#include <QSqlError>

/**
 * Zones géographiques prédéfinies pour la prédiction de remplissage.
 * - centre      : zone urbaine dense → remplissage rapide
 * - residentiel : zone résidentielle → remplissage normal
 * - industriel  : zone industrielle  → remplissage plus lent / variable
 */
static const QStringList ZONES_DISPONIBLES = {"centre", "residentiel", "industriel"};

class Conteneur
{
public:
    Conteneur();
    Conteneur(int id, double capacite, const QString &typePropriete,
              const QString &adresseComplete, const QString &localisationGPS,
              const QString &accepteMenager, const QString &accepteRecyclable,
              const QString &accepteOrganique, const QString &accepteIndustriel,
              const QString &etat, const QString &dateDerniereCollecte,
              const QString &zone = "residentiel");   // ← nouveau paramètre (défaut sûr)

    // ── Getters ──────────────────────────────────────────────────
    int     getId()                   const;
    double  getCapacite()             const;
    QString getTypePropriete()        const;
    QString getAdresseComplete()      const;
    QString getLocalisationGPS()      const;
    QString getAccepteMenager()       const;
    QString getAccepteRecyclable()    const;
    QString getAccepteOrganique()     const;
    QString getAccepteIndustriel()    const;
    QString getEtat()                 const;
    QString getDateDerniereCollecte() const;
    QString getZone()                 const;   // ← nouveau getter

    // ── Setters ──────────────────────────────────────────────────
    void setId(int id);
    void setCapacite(double v);
    void setTypePropriete(const QString &v);
    void setAdresseComplete(const QString &v);
    void setLocalisationGPS(const QString &v);
    void setAccepteMenager(const QString &v);
    void setAccepteRecyclable(const QString &v);
    void setAccepteOrganique(const QString &v);
    void setAccepteIndustriel(const QString &v);
    void setEtat(const QString &v);
    void setDateDerniereCollecte(const QString &v);
    void setZone(const QString &v);             // ← nouveau setter

    // ── CRUD ─────────────────────────────────────────────────────
    bool ajouter();
    bool modifier();
    static bool supprimer(int id);
    static QList<Conteneur> getAll();
    static Conteneur getById(int id);

    // ── Vérification FK ──────────────────────────────────────────
    static int compterLiensConsommer(int id);

    // ── Validation ───────────────────────────────────────────────
    bool estValide() const;

    // ── Recherche dans QTableWidget ──────────────────────────────
    static void rechercherDansTable(QTableWidget *table, const QString &text);

    // ── Export liste ─────────────────────────────────────────────
    void exporterListe(QTableWidget *table);

    // ── Statistiques ─────────────────────────────────────────────
    void afficherStatistiques(QWidget *parent);

    // ── Tri + filtre dans table ───────────────────────────────────
    void loadConteneursIntoTable(QTableWidget *table,
                                 const QString &orderBy,
                                 const QString &filterEtat);

private:
    int     m_id;
    double  m_capacite;
    QString m_typePropriete;
    QString m_adresseComplete;
    QString m_localisationGPS;
    QString m_accepteMenager;
    QString m_accepteRecyclable;
    QString m_accepteOrganique;
    QString m_accepteIndustriel;
    QString m_etat;
    QString m_dateDerniereCollecte;
    QString m_zone;   // ← nouveau membre
};

#endif // CONTENEUR_H
