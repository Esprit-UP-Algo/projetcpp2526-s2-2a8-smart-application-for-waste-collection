#ifndef COLLECTE_H
#define COLLECTE_H

#include <QString>
#include <QList>
#include <QSqlQuery>
#include <QSqlError>

class Collecte
{
public:
    Collecte();
    Collecte(int id, const QString &dateCollecte, const QString &typeDechet,
             double quantiteCollectee, const QString &statut,
             double distanceTotale, const QString &observations);

    // Getters
    int     getId()                 const;
    QString getDateCollecte()       const;
    QString getTypeDechet()         const;
    double  getQuantiteCollectee()  const;
    QString getStatut()             const;
    double  getDistanceTotale()     const;
    QString getObservations()       const;

    // Setters
    void setId(int id);
    void setDateCollecte(const QString &v);
    void setTypeDechet(const QString &v);
    void setQuantiteCollectee(double v);
    void setStatut(const QString &v);
    void setDistanceTotale(double v);
    void setObservations(const QString &v);

    // CRUD
    bool ajouter();
    bool modifier();
    static bool supprimer(int id);
    static QList<Collecte> getAll();
    static Collecte getById(int id);

    // Validation
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
