#ifndef CLIENT_H
#define CLIENT_H

#include <QString>
#include <QList>
#include <QSqlQuery>
#include <QSqlError>

class Client
{
public:
    // ================================================================
    // === CONSTRUCTEURS ==============================================
    // ================================================================
    Client();
    Client(int id, const QString &nom, const QString &prenom,
           const QString &cin, const QString &telephone,
           const QString &adresse, const QString &type,
           const QString &statut, const QString &zone,
           const QString &cinEmploye);

    // ================================================================
    // === GETTERS ====================================================
    // ================================================================
    int        getId()          const;
    QString    getNom()         const;
    QString    getPrenom()      const;
    QString    getCin()         const;
    QString    getTelephone()   const;
    QString    getAdresse()     const;
    QString    getType()        const;
    QString    getStatut()      const;
    QString    getZone()        const;
    QString    getCinEmploye()  const;

    // ================================================================
    // === SETTERS ====================================================
    // ================================================================
    void setId(int id);
    void setNom(const QString &nom);
    void setPrenom(const QString &prenom);
    void setCin(const QString &cin);
    void setTelephone(const QString &telephone);
    void setAdresse(const QString &adresse);
    void setType(const QString &type);
    void setStatut(const QString &statut);
    void setZone(const QString &zone);
    void setCinEmploye(const QString &cinEmploye);

    // ================================================================
    // === MÉTHODES BASE DE DONNÉES ==================================
    // ================================================================

    // Ajouter un client dans la base
    bool ajouter();

    // Modifier un client existant (par son ID)
    bool modifier();

    // Supprimer un client par ID
    static bool supprimer(int id);

    // Récupérer tous les clients
    static QList<Client> getAll();

    // Rechercher des clients par mot-clé (nom, prénom, zone, etc.)
    static QList<Client> rechercher(const QString &motCle);

    // Récupérer un client par son ID
    static Client getById(int id);

    // Vérifier si un CIN_employe existe dans EMPLOYES
    static bool employeExiste(const QString &cinEmploye);

    // ================================================================
    // === VALIDATION =================================================
    // ================================================================
    bool estValide() const;

private:
    int     m_id;
    QString m_nom;
    QString m_prenom;
    QString m_cin;
    QString m_telephone;
    QString m_adresse;
    QString m_type;
    QString m_statut;
    QString m_zone;
    QString m_cinEmploye;
};

#endif // CLIENT_H
