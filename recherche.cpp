#include "recherche.h"

#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>

// ================================================================
// === MODULE EMPLOYE — MARYEM ====================================
// ================================================================

QSqlQueryModel* EmployeRecherche::rechercher(const QString &texte)
{
    QSqlQueryModel *model = new QSqlQueryModel();

    // Texte vide → retourne tous les employés (réinitialisation)
    if (texte.trimmed().isEmpty()) {
        model->setQuery(
            "SELECT CIN, Nom, Prenom, Email, Poste, Telephone, "
            "Date_embauche, Salaire, Service FROM EMPLOYES ORDER BY Nom"
            );
        return model;
    }

    QString motif = "%" + texte.trimmed() + "%";

    QSqlQuery q;
    q.prepare(
        "SELECT CIN, Nom, Prenom, Email, Poste, Telephone, "
        "Date_embauche, Salaire, Service FROM EMPLOYES "
        "WHERE UPPER(CIN)     LIKE UPPER(:r1) "
        "   OR UPPER(Nom)     LIKE UPPER(:r2) "
        "   OR UPPER(Prenom)  LIKE UPPER(:r3) "
        "   OR UPPER(Email)   LIKE UPPER(:r4) "
        "   OR UPPER(Poste)   LIKE UPPER(:r5) "
        "   OR UPPER(Service) LIKE UPPER(:r6)"
        );
    q.bindValue(":r1", motif);
    q.bindValue(":r2", motif);
    q.bindValue(":r3", motif);
    q.bindValue(":r4", motif);
    q.bindValue(":r5", motif);
    q.bindValue(":r6", motif);

    if (!q.exec()) {
        qDebug() << "[EmployeRecherche::rechercher] Erreur SQL:" << q.lastError().text();
        return model;
    }

    model->setQuery(std::move(q));
    return model;
}


// ================================================================
// === MODULE CLIENT — [NOM DU MEMBRE] ============================
// Implémenter ici ClientRecherche::rechercher()
// ================================================================


// ================================================================
// === MODULE CONTENEUR — [NOM DU MEMBRE] =========================
// Implémenter ici ConteneurRecherche::rechercher()
// ================================================================


// ================================================================
// === MODULE COLLECTE — [NOM DU MEMBRE] ==========================
// Implémenter ici CollecteRecherche::rechercher()
// ================================================================


// ================================================================
// === MODULE RECYCLAGE — [NOM DU MEMBRE] =========================
// Implémenter ici RecyclageRecherche::rechercher()
// ================================================================
