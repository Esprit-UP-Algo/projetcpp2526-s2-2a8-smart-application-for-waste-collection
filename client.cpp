#include "client.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QTableWidget>
#include <QTableWidgetItem>
#include <QComboBox>
#include <QFileDialog>
#include <QMessageBox>
#include <QTextDocument>
#include <QPrinter>
#include <QFile>
#include <QTextStream>
#include <QInputDialog>

bool Client::ajouter() {
    QSqlQuery q;
    q.prepare("INSERT INTO CLIENT (NOM, PRENOM, CIN, TELEPHONE, "
              "ADRESSE_COMPLETE, TYPE_CLIENT, STATUT_COMPTE, CIN_EMPLOYE, ZONE) "
              "VALUES (:nom, :prenom, :cin, :tel, :adr, :type, :statut, :emp, :zone)");
    q.bindValue(":nom",    m_nom);
    q.bindValue(":prenom", m_prenom);
    q.bindValue(":cin",    m_cin);
    q.bindValue(":tel",    m_telephone);
    q.bindValue(":adr",    m_adresseComplete);
    q.bindValue(":type",   m_typeClient);
    q.bindValue(":statut", m_statutCompte);
    q.bindValue(":emp",    m_cinEmploye);
    q.bindValue(":zone",   m_zone);
    if (!q.exec()) {
        qDebug() << "Ajouter error:" << q.lastError().text();
        return false;
    }
    return true;
}

bool Client::modifier() {
    QSqlQuery q;
    q.prepare("UPDATE CLIENT SET "
              "NOM=:nom, PRENOM=:prenom, CIN=:cin, TELEPHONE=:tel, "
              "ADRESSE_COMPLETE=:adr, TYPE_CLIENT=:type, "
              "STATUT_COMPTE=:statut, CIN_EMPLOYE=:emp, ZONE=:zone "
              "WHERE ID_CLIENT=:id");
    q.bindValue(":nom",    m_nom);
    q.bindValue(":prenom", m_prenom);
    q.bindValue(":cin",    m_cin);
    q.bindValue(":tel",    m_telephone);
    q.bindValue(":adr",    m_adresseComplete);
    q.bindValue(":type",   m_typeClient);
    q.bindValue(":statut", m_statutCompte);
    q.bindValue(":emp",    m_cinEmploye);
    q.bindValue(":zone",   m_zone);
    q.bindValue(":id",     m_idClient);
    if (!q.exec()) {
        qDebug() << "Modifier error:" << q.lastError().text();
        return false;
    }
    return true;
}

bool Client::supprimer() {
    QSqlQuery q;
    q.prepare("DELETE FROM CLIENT WHERE ID_CLIENT = :id");
    q.bindValue(":id", m_idClient);
    if (!q.exec()) {
        qDebug() << "Supprimer error:" << q.lastError().text();
        return false;
    }
    return true;
}

QList<Client> Client::afficher() {
    QList<Client> list;
    QSqlQuery q("SELECT * FROM CLIENT");
    while (q.next()) {
        Client c;
        c.setIdClient       (q.value("ID_CLIENT").toInt());
        c.setNom            (q.value("NOM").toString());
        c.setPrenom         (q.value("PRENOM").toString());
        c.setCin            (q.value("CIN").toString());
        c.setTelephone      (q.value("TELEPHONE").toString());
        c.setAdresseComplete(q.value("ADRESSE_COMPLETE").toString());
        c.setTypeClient     (q.value("TYPE_CLIENT").toString());
        c.setStatutCompte   (q.value("STATUT_COMPTE").toString());
        c.setCinEmploye     (q.value("CIN_EMPLOYE").toString());
        c.setZone           (q.value("ZONE").toString());
        list << c;
    }
    return list;
}



//fct recherche




void Client::rechercherDansTable(QTableWidget *table, const QString &text)
{
    if (!table) return;

    for (int row = 0; row < table->rowCount(); row++)
    {
        bool match = false;

        for (int col = 0; col < table->columnCount(); col++)
        {
            QTableWidgetItem *item = table->item(row, col);

            if (item && item->text().contains(text, Qt::CaseInsensitive))
            {
                match = true;
                break;
            }
        }

        table->setRowHidden(row, !match);
    }
}



//tri




void Client::filtrerEtTrierTable(QTableWidget *table,
                                 const QString &statutFilter,
                                 Qt::SortOrder order)
{
    if (!table) return;

    // 1️⃣ Filter by status (STATUT_COMPTE column = 7)
    for (int row = 0; row < table->rowCount(); row++)
    {
        QTableWidgetItem *item = table->item(row, 7);
        if (!item) continue;

        bool match = (statutFilter == "Tous" || item->text() == statutFilter);
        table->setRowHidden(row, !match);
    }

    // 2️⃣ Sort alphabetically by NOM (column 0)
    table->setSortingEnabled(true);
    table->sortItems(0, order);
}


void Client::exporterListe(QTableWidget* table)
{
    if (!table) return;

    // Choix du format
    QStringList options = {"PDF", "Word"};
    bool ok;
    QString choice = QInputDialog::getItem(nullptr, "Exporter la liste", "Choisir le format :", options, 0, false, &ok);
    if (!ok || choice.isEmpty()) return;

    QString filter = (choice == "PDF") ? "*.pdf" : "*.doc";
    QString fileName = QFileDialog::getSaveFileName(nullptr, "Exporter la liste", "", filter);
    if (fileName.isEmpty()) return;

    if (choice == "PDF" && !fileName.endsWith(".pdf")) fileName += ".pdf";
    if (choice == "Word" && !fileName.endsWith(".doc")) fileName += ".doc";

    // Générer HTML à partir de la table
    QString html;
    html += "<h2>Liste des Clients</h2>";
    html += "<table border='1' cellspacing='0' cellpadding='4'>";
    html += "<tr>";
    for (int c = 0; c < table->columnCount(); ++c)
        html += "<th>" + table->horizontalHeaderItem(c)->text() + "</th>";
    html += "</tr>";
    for (int r = 0; r < table->rowCount(); ++r) {
        html += "<tr>";
        for (int c = 0; c < table->columnCount(); ++c) {
            QTableWidgetItem *item = table->item(r, c);
            html += "<td>" + QString(item ? item->text() : "") + "</td>";
        }
        html += "</tr>";
    }
    html += "</table>";

    // Exporter
    if (choice == "PDF") {
        QPrinter printer(QPrinter::HighResolution);
        printer.setOutputFormat(QPrinter::PdfFormat);
        printer.setOutputFileName(fileName);
        QTextDocument doc;
        doc.setHtml(html);
        doc.print(&printer);
    } else { // Word
        QFile file(fileName);
        if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
            QMessageBox::critical(nullptr, "Erreur", "Impossible de créer le fichier Word.");
            return;
        }
        QTextStream out(&file);
        out << html;
        file.close();
    }

    QMessageBox::information(nullptr, "Export terminé", "La liste des clients a été exportée avec succès.");
}


