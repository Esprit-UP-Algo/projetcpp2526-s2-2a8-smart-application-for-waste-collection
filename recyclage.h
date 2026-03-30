#ifndef RECYCLAGE_H
#define RECYCLAGE_H

#include <QString>
#include <QList>
#include <QSqlQuery>
#include <QSqlError>

class Recyclage
{
public:
    // Constructeurs
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
    void setDateTri(const QString &dateTri);
    void setTypeMateriau(const QString &type);
    void setQuantiteEntree(double v);
    void setQuantiteRecyclee(double v);
    void setQuantiteRejetee(double v);
    void setDestination(const QString &dest);
    void setValeurMonetaire(double v);
    void setDirection(const QString &dir);
    void setStatut(const QString &statut);

    // CRUD
    bool ajouter();
    bool modifier();
    static bool supprimer(int id);
    static QList<Recyclage> getAll();
    static Recyclage getById(int id);

    // Validation
    bool estValide() const;

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
