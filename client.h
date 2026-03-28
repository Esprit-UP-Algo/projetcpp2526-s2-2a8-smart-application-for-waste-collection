#ifndef CLIENT_H
#define CLIENT_H

#include "qtablewidget.h"
#include <QString>
#include <QComboBox>

class Client {
public:
    Client() = default;

    // Getters
    int idClient() const { return m_idClient; }
    QString nom() const { return m_nom; }
    QString prenom() const { return m_prenom; }
    QString cin()  const { return m_cin; }
    QString telephone()   const { return m_telephone; }
    QString adresseComplete() const { return m_adresseComplete; }
    QString typeClient()  const { return m_typeClient; }
    QString statutCompte()    const { return m_statutCompte; }
    QString cinEmploye()  const { return m_cinEmploye; }
    QString zone() const { return m_zone; }

    // Setters
    void setIdClient   (int v) { m_idClient = v; }
    void setNom (const QString &v) { m_nom = v; }
    void setPrenom (const QString &v) { m_prenom = v; }
    void setCin (const QString &v) { m_cin = v; }
    void setTelephone  (const QString &v) { m_telephone = v; }
    void setAdresseComplete(const QString &v) { m_adresseComplete = v; }
    void setTypeClient (const QString &v) { m_typeClient = v; }
    void setStatutCompte   (const QString &v) { m_statutCompte = v; }
    void setCinEmploye (const QString &v) { m_cinEmploye = v; }
    void setZone  (const QString &v) { m_zone = v; }
    bool ajouter();
    bool modifier();
    bool supprimer();
    QList<Client> afficher();
    static void rechercherDansTable(QTableWidget *table, const QString &text);
    static void filtrerEtTrierTable(QTableWidget *table,
                                    const QString &statutFilter,
                                    Qt::SortOrder order);
    void exporterListe(QTableWidget* table); // fonction d'export




private:
    int m_idClient    = 0;
    QString m_nom;
    QString m_prenom;
    QString m_cin;
    QString m_telephone;
    QString m_adresseComplete;
    QString m_typeClient;
    QString m_statutCompte;
    QString m_cinEmploye;
    QString m_zone;
};

#endif // CLIENT_H
