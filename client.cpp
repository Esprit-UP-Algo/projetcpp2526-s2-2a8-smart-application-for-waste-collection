#include "client.h"

// ================================================================
// === CONSTRUCTEURS ==============================================
// ================================================================

Client::Client()
    : m_id(0), m_nom(""), m_prenom(""), m_cin(""),
    m_telephone(""), m_adresse(""), m_type(""),
    m_statut("actif"), m_zone(""), m_cinEmploye("")
{}

Client::Client(int id, const QString &nom, const QString &prenom,
               const QString &cin, const QString &telephone,
               const QString &adresse, const QString &type,
               const QString &statut, const QString &zone,
               const QString &cinEmploye)
    : m_id(id), m_nom(nom), m_prenom(prenom), m_cin(cin),
    m_telephone(telephone), m_adresse(adresse), m_type(type),
    m_statut(statut), m_zone(zone), m_cinEmploye(cinEmploye)
{}

// ================================================================
// === GETTERS ====================================================
// ================================================================

int     Client::getId()         const { return m_id; }
QString Client::getNom()        const { return m_nom; }
QString Client::getPrenom()     const { return m_prenom; }
QString Client::getCin()        const { return m_cin; }
QString Client::getTelephone()  const { return m_telephone; }
QString Client::getAdresse()    const { return m_adresse; }
QString Client::getType()       const { return m_type; }
QString Client::getStatut()     const { return m_statut; }
QString Client::getZone()       const { return m_zone; }
QString Client::getCinEmploye() const { return m_cinEmploye; }

// ================================================================
// === SETTERS ====================================================
// ================================================================

void Client::setId(int id)                      { m_id         = id; }
void Client::setNom(const QString &nom)         { m_nom        = nom; }
void Client::setPrenom(const QString &prenom)   { m_prenom     = prenom; }
void Client::setCin(const QString &cin)         { m_cin        = cin; }
void Client::setTelephone(const QString &tel)   { m_telephone  = tel; }
void Client::setAdresse(const QString &adr)     { m_adresse    = adr; }
void Client::setType(const QString &type)       { m_type       = type; }
void Client::setStatut(const QString &statut)   { m_statut     = statut; }
void Client::setZone(const QString &zone)       { m_zone       = zone; }
void Client::setCinEmploye(const QString &cin)  { m_cinEmploye = cin; }

// ================================================================
// === VALIDATION =================================================
// ================================================================

bool Client::estValide() const
{
    return !m_nom.trimmed().isEmpty()
    && !m_prenom.trimmed().isEmpty()
        && !m_cin.trimmed().isEmpty()
        && !m_telephone.trimmed().isEmpty()
        && !m_adresse.trimmed().isEmpty()
        && !m_type.trimmed().isEmpty()
        && !m_zone.trimmed().isEmpty()
        && !m_cinEmploye.trimmed().isEmpty();
}

// ================================================================
// === MÉTHODES BASE DE DONNÉES ==================================
// ================================================================

bool Client::ajouter()
{
    // Calcul du nouvel ID
    QSqlQuery queryId;
    if (!queryId.exec("SELECT NVL(MAX(ID_client),0)+1 FROM CLIENTS"))
        return false;
    int newId = 0;
    if (queryId.next())
        newId = queryId.value(0).toInt();
    m_id = newId;

    QSqlQuery query;
    query.prepare(
        "INSERT INTO CLIENTS (ID_client, Nom, Prenom, CIN, Telephone, "
        "Adresse_complete, Type_client, Statut_compte, Zone, CIN_employe) "
        "VALUES (:id, :nom, :prenom, :cin, :tel, :addr, :type, :statut, :zone, :cinemp)"
        );
    query.bindValue(":id",     m_id);
    query.bindValue(":nom",    m_nom);
    query.bindValue(":prenom", m_prenom);
    query.bindValue(":cin",    m_cin);
    query.bindValue(":tel",    m_telephone);
    query.bindValue(":addr",   m_adresse);
    query.bindValue(":type",   m_type);
    query.bindValue(":statut", m_statut.isEmpty() ? "actif" : m_statut);
    query.bindValue(":zone",   m_zone);
    query.bindValue(":cinemp", m_cinEmploye);
    return query.exec();
}

bool Client::modifier()
{
    QSqlQuery query;
    query.prepare(
        "UPDATE CLIENTS SET Nom=:nom, Prenom=:prenom, CIN=:cin, "
        "Telephone=:tel, Adresse_complete=:addr, Type_client=:type, "
        "Statut_compte=:statut, Zone=:zone "
        "WHERE ID_client=:id"
        );
    query.bindValue(":nom",    m_nom);
    query.bindValue(":prenom", m_prenom);
    query.bindValue(":cin",    m_cin);
    query.bindValue(":tel",    m_telephone);
    query.bindValue(":addr",   m_adresse);
    query.bindValue(":type",   m_type);
    query.bindValue(":statut", m_statut);
    query.bindValue(":zone",   m_zone);
    query.bindValue(":id",     m_id);
    return query.exec();
}

bool Client::supprimer(int id)
{
    QSqlQuery query;
    query.prepare("DELETE FROM CLIENTS WHERE ID_client = :id");
    query.bindValue(":id", id);
    return query.exec();
}

QList<Client> Client::getAll()
{
    QList<Client> liste;
    QSqlQuery query;
    if (!query.exec(
            "SELECT ID_client, Nom, Prenom, CIN, Telephone, "
            "Adresse_complete, Type_client, Statut_compte, Zone, CIN_employe "
            "FROM CLIENTS ORDER BY ID_client"))
        return liste;

    while (query.next()) {
        Client c(
            query.value(0).toInt(),
            query.value(1).toString(),
            query.value(2).toString(),
            query.value(3).toString(),
            query.value(4).toString(),
            query.value(5).toString(),
            query.value(6).toString(),
            query.value(7).toString(),
            query.value(8).toString(),
            query.value(9).toString()
            );
        liste.append(c);
    }
    return liste;
}

QList<Client> Client::rechercher(const QString &motCle)
{
    QList<Client> liste;
    QSqlQuery query;
    QString motif = "%" + motCle + "%";
    query.prepare(
        "SELECT ID_client, Nom, Prenom, CIN, Telephone, "
        "Adresse_complete, Type_client, Statut_compte, Zone, CIN_employe "
        "FROM CLIENTS "
        "WHERE UPPER(Nom)              LIKE UPPER(:r1) "
        "   OR UPPER(Prenom)           LIKE UPPER(:r2) "
        "   OR UPPER(CIN)              LIKE UPPER(:r3) "
        "   OR UPPER(Type_client)      LIKE UPPER(:r4) "
        "   OR UPPER(Zone)             LIKE UPPER(:r5) "
        "   OR UPPER(Telephone)        LIKE UPPER(:r6) "
        "   OR UPPER(Adresse_complete) LIKE UPPER(:r7)"
        );
    for (int i = 1; i <= 7; i++)
        query.bindValue(":r" + QString::number(i), motif);

    if (!query.exec()) return liste;

    while (query.next()) {
        Client c(
            query.value(0).toInt(),
            query.value(1).toString(),
            query.value(2).toString(),
            query.value(3).toString(),
            query.value(4).toString(),
            query.value(5).toString(),
            query.value(6).toString(),
            query.value(7).toString(),
            query.value(8).toString(),
            query.value(9).toString()
            );
        liste.append(c);
    }
    return liste;
}

Client Client::getById(int id)
{
    QSqlQuery query;
    query.prepare(
        "SELECT ID_client, Nom, Prenom, CIN, Telephone, "
        "Adresse_complete, Type_client, Statut_compte, Zone, CIN_employe "
        "FROM CLIENTS WHERE ID_client = :id"
        );
    query.bindValue(":id", id);
    if (query.exec() && query.next()) {
        return Client(
            query.value(0).toInt(),
            query.value(1).toString(),
            query.value(2).toString(),
            query.value(3).toString(),
            query.value(4).toString(),
            query.value(5).toString(),
            query.value(6).toString(),
            query.value(7).toString(),
            query.value(8).toString(),
            query.value(9).toString()
            );
    }
    return Client(); // client vide si non trouvé
}

bool Client::employeExiste(const QString &cinEmploye)
{
    QSqlQuery query;
    query.prepare("SELECT COUNT(*) FROM EMPLOYES WHERE CIN = :cin");
    query.bindValue(":cin", cinEmploye);
    if (query.exec() && query.next())
        return query.value(0).toInt() > 0;
    return false;
}
