#include "tri.h"

#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>

// ================================================================
// === MODULE EMPLOYE — MARYEM ====================================
// ================================================================

QStringList EmployeTri::colonnesDisponibles()
{
    return {
        "CIN", "Nom", "Prenom", "Email",
        "Poste", "Telephone", "Date_embauche", "Salaire", "Service"
    };
}

QSqlQueryModel* EmployeTri::trierPar(const QString &colonne)
{
    QSqlQueryModel *model = new QSqlQueryModel();

    // Protection anti-injection SQL par liste blanche
    QString colVerifiee = "Nom"; // valeur par défaut
    if (colonnesDisponibles().contains(colonne, Qt::CaseSensitive))
        colVerifiee = colonne;
    else
        qDebug() << "[EmployeTri::trierPar] Colonne non autorisée :"
                 << colonne << "→ tri par défaut (Nom)";

    // ORDER BY ne supporte pas les bindValue → protection garantie par liste blanche
    model->setQuery(
        "SELECT CIN, Nom, Prenom, Email, Poste, Telephone, "
        "Date_embauche, Salaire, Service FROM EMPLOYES ORDER BY "
        + colVerifiee
        );

    if (model->lastError().isValid())
        qDebug() << "[EmployeTri::trierPar] Erreur SQL:" << model->lastError().text();

    return model;
}


// ================================================================
// === MODULE CLIENT — [NOM DU MEMBRE] ============================
// Implémenter ici ClientTri::trierPar() et colonnesDisponibles()
// ================================================================


// ================================================================
// === MODULE CONTENEUR — [NOM DU MEMBRE] =========================
// Implémenter ici ConteneurTri::trierPar() et colonnesDisponibles()
// ================================================================


// ================================================================
// === MODULE COLLECTE — [NOM DU MEMBRE] ==========================
// Implémenter ici CollecteTri::trierPar() et colonnesDisponibles()
// ================================================================


// ================================================================
// === MODULE RECYCLAGE — [NOM DU MEMBRE] =========================
// Implémenter ici RecyclageTri::trierPar() et colonnesDisponibles()
// ================================================================
