#ifndef RECYCLAGE_H
#define RECYCLAGE_H

#include <QString>
#include <QList>
#include <QTableWidget>
#include <QWidget>
#include <QSqlQuery>
#include <QSqlError>

class Recyclage
{
public:
    Recyclage();
    Recyclage(int id, const QString &dateTri, const QString &typeMateriau,
              double quantiteEntree, double quantiteRecyclee, double quantiteRejetee,
              const QString &destination, double valeurMonetaire,
              const QString &direction, const QString &statut);

    // Getters
    int     getId()               const;
    QString getDateTri()          const;
    QString getTypeMateriau()     const;
    double  getQuantiteEntree()   const;
    double  getQuantiteRecyclee() const;
    double  getQuantiteRejetee()  const;
    QString getDestination()      const;
    double  getValeurMonetaire()  const;
    QString getDirection()        const;
    QString getStatut()           const;

    // Setters
    void setId(int id);
    void setDateTri(const QString &v);
    void setTypeMateriau(const QString &v);
    void setQuantiteEntree(double v);
    void setQuantiteRecyclee(double v);
    void setQuantiteRejetee(double v);
    void setDestination(const QString &v);
    void setValeurMonetaire(double v);
    void setDirection(const QString &v);
    void setStatut(const QString &v);

    // CRUD
    bool ajouter();
    bool modifier();
    static bool supprimer(int id);
    static QList<Recyclage> getAll();
    static Recyclage getById(int id);

    // Validation
    bool estValide() const;

    // Recherche dans QTableWidget (comme Client)
    static void rechercherDansTable(QTableWidget *table, const QString &text);

    // Export liste
    void exporterListe(QTableWidget *table);

    // Statistiques
    void afficherStatistiques(QWidget *parent);

    // Tri + filtre dans table
    void loadRecyclagesIntoTable(QTableWidget *table,
                                 const QString &orderBy,
                                 const QString &filterStatut);

private:
    int     m_id;
    QString m_dateTri;
    QString m_typeMateriau;
    double  m_quantiteEntree;
    double  m_quantiteRecyclee;
    double  m_quantiteRejetee;
    QString m_destination;
    double  m_valeurMonetaire;
    QString m_direction;
    QString m_statut;
};

#endif // RECYCLAGE_H
