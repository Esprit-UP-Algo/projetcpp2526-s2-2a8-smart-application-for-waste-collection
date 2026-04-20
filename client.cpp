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
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QDialog>
#include <QLabel>
#include <QFrame>
#include <QPushButton>
#include <QWidget>
#include <QDialog>
#include <QPushButton>
#include <QPropertyAnimation>
#include <QtCharts/QPieSlice>
#include <QtCharts/QChartView>
#include <QtCharts/QPieSeries>
#include <QtCharts/QChart>
#include <QtCharts/QPieSlice>
#include <QTimer>
bool Client::ajouter() {
    QSqlQuery q;
    q.prepare("INSERT INTO CLIENTS (NOM, PRENOM, CIN, TELEPHONE, "
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
    q.prepare("UPDATE CLIENTS SET "
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
        qDebug() << "=== DEBUG MODIFIER CLIENT ===";
        qDebug() << "ID:" << m_idClient;
        qDebug() << "CIN_EMPLOYE:" << m_cinEmploye;
        qDebug() << "ECHEC:" << q.lastError().text();
        return false;
    }
    return true;
}

bool Client::supprimer() {
    QSqlQuery q;
    q.prepare("DELETE FROM CLIENTS WHERE ID_CLIENT = :id");
    q.bindValue(":id", m_idClient);
    if (!q.exec()) {
        qDebug() << "Supprimer error:" << q.lastError().text();
        return false;
    }
    return true;
}

QList<Client> Client::afficher() {
    QList<Client> list;
    QSqlQuery q("SELECT ID_CLIENT, NOM, PRENOM, CIN, TELEPHONE, "
                "ADRESSE_COMPLETE, TYPE_CLIENT, STATUT_COMPTE, CIN_EMPLOYE, ZONE "
                "FROM CLIENTS");
    while (q.next()) {
        Client c;
        c.setIdClient       (q.value(0).toInt());   // ID_CLIENT
        c.setNom            (q.value(1).toString()); // NOM
        c.setPrenom         (q.value(2).toString()); // PRENOM
        c.setCin            (q.value(3).toString()); // CIN
        c.setTelephone      (q.value(4).toString()); // TELEPHONE
        c.setAdresseComplete(q.value(5).toString()); // ADRESSE_COMPLETE
        c.setTypeClient     (q.value(6).toString()); // TYPE_CLIENT
        c.setStatutCompte   (q.value(7).toString()); // STATUT_COMPTE
        c.setCinEmploye     (q.value(8).toString()); // CIN_EMPLOYE
        c.setZone           (q.value(9).toString()); // ZONE
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


void Client::loadClientsIntoTable(QTableWidget *table,
                                  const QString &orderBy,
                                  const QString &filterType)
{
    QSqlQuery q;

    QString whereClause;

    if (filterType == "actif")
        whereClause = "WHERE LOWER(statut_compte) = 'actif'";
    else if (filterType == "inactif")
        whereClause = "WHERE LOWER(statut_compte) = 'inactif'";
    else
        whereClause = "";

    QString queryStr = QString(
                           "SELECT id_client, nom, prenom, cin, type_client, zone, telephone, statut_compte, adresse_complete, cin_employe "
                           "FROM CLIENTS %1 ORDER BY %2"
                           ).arg(whereClause, orderBy);

    q.exec(queryStr);

    table->setSortingEnabled(false);
    table->clearContents();
    table->setRowCount(0);

    int row = 0;
    while (q.next()) {
        table->insertRow(row);

        table->setItem(row, 0, new QTableWidgetItem(q.value(0).toString())); // ID
        table->setItem(row, 1, new QTableWidgetItem(q.value(1).toString())); // Nom
        table->setItem(row, 2, new QTableWidgetItem(q.value(2).toString())); // Prenom
        table->setItem(row, 3, new QTableWidgetItem(q.value(3).toString())); // CIN
        table->setItem(row, 4, new QTableWidgetItem(q.value(4).toString())); // Type
        table->setItem(row, 5, new QTableWidgetItem(q.value(5).toString())); // Zone
        table->setItem(row, 6, new QTableWidgetItem(q.value(6).toString())); // Telephone
        table->setItem(row, 7, new QTableWidgetItem(q.value(7).toString())); // Statut
        table->setItem(row, 8, new QTableWidgetItem(q.value(8).toString())); // Adresse
        table->setItem(row, 9, new QTableWidgetItem(q.value(9).toString())); // CIN_EMPLOYE
        table->setColumnHidden(9, true);

        row++;
    }

    table->setSortingEnabled(true);
}

// Exporter
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





//stat

#include <QtCharts/QChartView>
#include <QtCharts/QPieSeries>
#include <QtCharts/QChart>
#include <QtCharts/QPieSlice>

void Client::afficherStatistiques(QWidget *parent)
{
    QSqlQuery q;

    int typeParticulier = 0;
    int typeEntreprise = 0;
    int typeAutre = 0;

    q.prepare("SELECT COUNT(*) FROM CLIENTS WHERE UPPER(Type_client)=UPPER(:t)");
    q.bindValue(":t", "Particulier");
    if (q.exec() && q.next()) typeParticulier = q.value(0).toInt();

    q.prepare("SELECT COUNT(*) FROM CLIENTS WHERE UPPER(Type_client)=UPPER(:t)");
    q.bindValue(":t", "Entreprise");
    if (q.exec() && q.next()) typeEntreprise = q.value(0).toInt();

    q.prepare("SELECT COUNT(*) FROM CLIENTS WHERE UPPER(Type_client)=UPPER(:t)");
    q.bindValue(":t", "Autre");
    if (q.exec() && q.next()) typeAutre = q.value(0).toInt();

    int total = typeParticulier + typeEntreprise + typeAutre;
    if (total == 0) total = 1;

    QDialog *dlg = new QDialog(parent);
    dlg->setWindowTitle("📊 Statistiques des Clients");
    dlg->setFixedSize(780, 680);
    dlg->setStyleSheet("QDialog { background-color: #F0F4F8; }");

    QVBoxLayout *mainLay = new QVBoxLayout(dlg);
    mainLay->setContentsMargins(20, 20, 20, 20);
    mainLay->setSpacing(16);

    QLabel *title = new QLabel("📊 Répartition des Types de Clients");
    title->setAlignment(Qt::AlignCenter);
    title->setStyleSheet(
        "font-size:18px; font-weight:bold; color:white; padding:16px;"
        "background:qlineargradient(x1:0,y1:0,x2:1,y2:0,stop:0 #1B3A57,stop:1 #2C5F7C);"
        "border-radius:12px;"
        );
    mainLay->addWidget(title);

    QPieSeries *series = new QPieSeries();

    QPieSlice *particulier = series->append("Particulier", typeParticulier);
    QPieSlice *entreprise  = series->append("Entreprise", typeEntreprise);
    QPieSlice *autre       = series->append("Autre", typeAutre);

    particulier->setBrush(QColor("#3B82F6"));
    entreprise->setBrush(QColor("#10B981"));
    autre->setBrush(QColor("#F59E0B"));

    particulier->setLabel(QString("Particulier %1%").arg((typeParticulier * 100.0) / total, 0, 'f', 1));
    entreprise->setLabel(QString("Entreprise %1%").arg((typeEntreprise * 100.0) / total, 0, 'f', 1));
    autre->setLabel(QString("Autre %1%").arg((typeAutre * 100.0) / total, 0, 'f', 1));

    particulier->setLabelVisible(true);
    entreprise->setLabelVisible(true);
    autre->setLabelVisible(true);

    QObject::connect(particulier, &QPieSlice::hovered, [=](bool state){
        particulier->setExploded(state);
    });

    QObject::connect(entreprise, &QPieSlice::hovered, [=](bool state){
        entreprise->setExploded(state);
    });

    QObject::connect(autre, &QPieSlice::hovered, [=](bool state){
        autre->setExploded(state);
    });

    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->setTitle("Types de clients");
    chart->legend()->setAlignment(Qt::AlignBottom);
    chart->setAnimationOptions(QChart::SeriesAnimations);

    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);
    chartView->setStyleSheet("background:transparent;");

    mainLay->addWidget(chartView);

    QPushButton *closeBtn = new QPushButton("✕  Fermer");
    QObject::connect(closeBtn, &QPushButton::clicked, dlg, &QDialog::accept);
    mainLay->addWidget(closeBtn);

    dlg->exec();
}
