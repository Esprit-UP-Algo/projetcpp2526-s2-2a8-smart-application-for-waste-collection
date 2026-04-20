#include "employe.h"
#include <QSqlError>
#include <QSqlQuery>
#include <QDebug>
#include <QTableWidgetItem>
#include <QInputDialog>
#include <QFileDialog>
#include <QMessageBox>
#include <QTextDocument>
#include <QPrinter>
#include <QFile>
#include <QTextStream>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QDialog>
#include <QLabel>
#include <QFrame>
#include <QPushButton>
#include <QDate>
#include "login.h"
#include <QProcess>
#include <QDir>
#include <QFile>
#include <QTextStream>

// ============================================================
// Constructeur paramétré
// ============================================================
Employe::Employe(QString cin, QString nom, QString prenom,
                 QString email, QString poste, QString telephone,
                 double salaire, QString dateEmbauche, QString service)
{
    this->cin          = cin;
    this->nom          = nom;
    this->prenom       = prenom;
    this->email        = email;
    this->poste        = poste;
    this->telephone    = telephone;
    this->salaire      = salaire;
    this->dateEmbauche = dateEmbauche;
    this->service      = service;
}

// ============================================================
// CRUD — ajouter
// ============================================================
bool Employe::ajouter()
{
    // 1. Générer le mot de passe
    QString mdp = Login::genererMotDePasse();

    QSqlQuery query;
    query.prepare(
        "INSERT INTO EMPLOYES (CIN, Nom, Prenom, Email, Poste, Telephone, "
        "Salaire, Date_embauche, Service, MDP) "
        "VALUES (:cin, :nom, :prenom, :email, :poste, :tel, :salaire, "
        "TO_DATE(:date, 'DD/MM/YYYY'), :service, :mdp)"
        );

    query.bindValue(":cin",     cin);
    query.bindValue(":nom",     nom);
    query.bindValue(":prenom",  prenom);
    query.bindValue(":email",   email);
    query.bindValue(":poste",   poste);
    query.bindValue(":tel",     telephone);
    query.bindValue(":salaire", salaire);
    query.bindValue(":date",    dateEmbauche);
    query.bindValue(":service", service);
    query.bindValue(":mdp",     mdp);

    if (!query.exec()) {
        qDebug() << "Employe::ajouter error:" << query.lastError().text();
        return false;
    }

    QSqlDatabase::database().commit();

    // 2. Envoyer le mot de passe par email
    Login::envoyerEmail(email, mdp, nom + " " + prenom);

    return true;
}
// ============================================================
// CRUD — afficher (lecture initiale via QSqlQueryModel)
// ============================================================
QSqlQueryModel* Employe::afficher()
{
    QSqlQueryModel *model = new QSqlQueryModel();
    model->setQuery(
        "SELECT CIN, Nom, Prenom, Email, Poste, Telephone, "
        "TO_CHAR(Date_embauche,'DD/MM/YYYY'), Salaire, Service FROM EMPLOYES ORDER BY Nom"
        );
    model->setHeaderData(0, Qt::Horizontal, "CIN");
    model->setHeaderData(1, Qt::Horizontal, "Nom");
    model->setHeaderData(2, Qt::Horizontal, "Prénom");
    model->setHeaderData(3, Qt::Horizontal, "Email");
    model->setHeaderData(4, Qt::Horizontal, "Poste");
    model->setHeaderData(5, Qt::Horizontal, "Téléphone");
    model->setHeaderData(6, Qt::Horizontal, "Date Embauche");
    model->setHeaderData(7, Qt::Horizontal, "Salaire");
    model->setHeaderData(8, Qt::Horizontal, "Service");
    return model;
}

// ============================================================
// CRUD — supprimer
// ============================================================
bool Employe::supprimer(QString cin)
{
    QSqlQuery query;
    query.prepare("DELETE FROM EMPLOYES WHERE CIN = :cin");
    query.bindValue(":cin", cin);
    if (!query.exec()) {
        qDebug() << "Employe::supprimer error:" << query.lastError().text();
        return false;
    }
    return true;
}

// ============================================================
// CRUD — modifier
// ============================================================
bool Employe::modifier(QString cin)
{
    QSqlQuery query;
    query.prepare(
        "UPDATE EMPLOYES SET "
        "Nom=:nom, Prenom=:prenom, Email=:email, Poste=:poste, "
        "Telephone=:tel, Salaire=:salaire, "
        "Date_embauche=TO_DATE(:date, 'DD/MM/YYYY'), "
        "Service=:service "
        "WHERE CIN=:cin"
        );
    query.bindValue(":nom",     nom);
    query.bindValue(":prenom",  prenom);
    query.bindValue(":email",   email);
    query.bindValue(":poste",   poste);
    query.bindValue(":tel",     telephone);
    query.bindValue(":salaire", salaire);
    query.bindValue(":date",    dateEmbauche);
    query.bindValue(":service", service);
    query.bindValue(":cin",     cin);
    if (!query.exec()) {
        qDebug() << "Employe::modifier error:" << query.lastError().text();
        return false;
    }
    return true;
}

// ============================================================
// Utilitaire — compter les clients liés (FK check)
// ============================================================
int Employe::compterClientsLies(QString cin)
{
    QSqlQuery query;
    query.prepare("SELECT COUNT(*) FROM CLIENTS WHERE CIN_employe = :cin");
    query.bindValue(":cin", cin);
    if (query.exec() && query.next())
        return query.value(0).toInt();
    return 0;
}

// ============================================================
// Utilitaire — liste CIN + Nom pour les ComboBox
// ============================================================
QList<QPair<QString,QString>> Employe::getListeCinNom()
{
    QList<QPair<QString,QString>> liste;
    QSqlQuery q;
    q.exec("SELECT CIN, Nom, Prenom FROM EMPLOYES ORDER BY Nom");
    while (q.next()) {
        QString cinEmp    = q.value(0).toString();
        QString nomComplet = q.value(1).toString() + " " + q.value(2).toString();
        liste.append(qMakePair(cinEmp, nomComplet));
    }
    return liste;
}

// ============================================================
// Recherche dans QTableWidget (comme Client)
// ============================================================
void Employe::rechercherDansTable(QTableWidget *table, const QString &text)
{
    if (!table) return;
    for (int row = 0; row < table->rowCount(); row++) {
        bool match = false;
        for (int col = 0; col < table->columnCount(); col++) {
            QTableWidgetItem *item = table->item(row, col);
            if (item && item->text().contains(text, Qt::CaseInsensitive)) {
                match = true;
                break;
            }
        }
        table->setRowHidden(row, !match);
    }
}

// ============================================================
// Tri + filtre — charge la table depuis la BD (comme Client)
// ============================================================
void Employe::loadEmployesIntoTable(QTableWidget *table,
                                    const QString &orderBy,
                                    const QString &filterService)
{
    // Protection anti-injection : liste blanche pour ORDER BY
    QStringList allowed = {
        "CIN", "Nom", "Prenom", "Email", "Poste",
        "Telephone", "Date_embauche", "Salaire", "Service"
    };
    QString safeOrder = "Nom ASC";
    for (const QString &col : allowed) {
        if (orderBy.startsWith(col, Qt::CaseInsensitive)) {
            safeOrder = orderBy;
            break;
        }
    }

    QString whereClause;
    if (!filterService.isEmpty())
        whereClause = "WHERE UPPER(Service) = UPPER('" + filterService + "')";

    QString queryStr = QString(
                           "SELECT CIN, Nom, Prenom, Email, Poste, Telephone, "
                           "TO_CHAR(Date_embauche,'DD/MM/YYYY'), Salaire, Service "
                           "FROM EMPLOYES %1 ORDER BY %2"
                           ).arg(whereClause, safeOrder);

    QSqlQuery q;
    q.exec(queryStr);

    table->setSortingEnabled(false);
    table->clearContents();
    table->setRowCount(0);

    int row = 0;
    while (q.next()) {
        table->insertRow(row);
        for (int col = 0; col < 9; col++)
            table->setItem(row, col, new QTableWidgetItem(q.value(col).toString()));
        table->setRowHeight(row, 44);
        row++;
    }
    table->setSortingEnabled(true);
}

// ============================================================
// Export liste PDF / Word (comme Client)
// ============================================================
void Employe::exporterListe(QTableWidget* table)
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

    // Générer HTML (simple comme Client)
    QString html;
    html += "<h2>Liste des Employés</h2>";
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

    QMessageBox::information(nullptr, "Export terminé", "La liste des employés a été exportée avec succès.");

}

//stat
#include <QtCharts/QChartView>
#include <QtCharts/QPieSeries>
#include <QtCharts/QChart>
#include <QtCharts/QPieSlice>

void Employe::afficherStatistiques(QWidget *parent)
{
    QSqlQuery q;


        int technicien = 0;
    int manager = 0;
    int administratif = 0;
    int agentTerrain = 0;
    int autre = 0;

    // Comptage par poste
    q.prepare("SELECT COUNT(*) FROM EMPLOYES WHERE UPPER(Poste)=UPPER(:p)");
    q.bindValue(":p", "Technicien");
    if (q.exec() && q.next()) technicien = q.value(0).toInt();

    q.prepare("SELECT COUNT(*) FROM EMPLOYES WHERE UPPER(Poste)=UPPER(:p)");
    q.bindValue(":p", "Manager");
    if (q.exec() && q.next()) manager = q.value(0).toInt();

    q.prepare("SELECT COUNT(*) FROM EMPLOYES WHERE UPPER(Poste)=UPPER(:p)");
    q.bindValue(":p", "Administratif");
    if (q.exec() && q.next()) administratif = q.value(0).toInt();

    q.prepare("SELECT COUNT(*) FROM EMPLOYES WHERE UPPER(Poste)=UPPER(:p)");
    q.bindValue(":p", "Agent terrain");
    if (q.exec() && q.next()) agentTerrain = q.value(0).toInt();

    // Autres postes
    q.prepare("SELECT COUNT(*) FROM EMPLOYES WHERE Poste IS NOT NULL AND "
              "UPPER(Poste) NOT IN ('TECHNICIEN','MANAGER','ADMINISTRATIF','AGENT TERRAIN')");
    if (q.exec() && q.next()) autre = q.value(0).toInt();

    int total = technicien + manager + administratif + agentTerrain + autre;
    if (total == 0) total = 1;

    // UI
    QDialog *dlg = new QDialog(parent);
    dlg->setWindowTitle("📊 Statistiques des Employés");
    dlg->setFixedSize(780, 680);
    dlg->setStyleSheet("QDialog { background-color: #F0F4F8; }");

    QVBoxLayout *mainLay = new QVBoxLayout(dlg);
    mainLay->setContentsMargins(20,20,20,20);
    mainLay->setSpacing(16);

    QLabel *title = new QLabel("📊 Répartition des Employés par Poste");
    title->setAlignment(Qt::AlignCenter);
    title->setStyleSheet(
        "font-size:18px; font-weight:bold; color:white; padding:16px;"
        "background:qlineargradient(x1:0,y1:0,x2:1,y2:0,stop:0 #1B3A57,stop:1 #2C5F7C);"
        "border-radius:12px;"
        );
    mainLay->addWidget(title);

    // Pie chart
    QPieSeries *series = new QPieSeries();

    QPieSlice *s1 = series->append("Technicien", technicien);
    QPieSlice *s2 = series->append("Manager", manager);
    QPieSlice *s3 = series->append("Administratif", administratif);
    QPieSlice *s4 = series->append("Agent terrain", agentTerrain);
    QPieSlice *s5 = series->append("Autre", autre);

    s1->setBrush(QColor("#6366F1"));
    s2->setBrush(QColor("#14B8A6"));
    s3->setBrush(QColor("#EC4899"));
    s4->setBrush(QColor("#F97316"));
    s5->setBrush(QColor("#9CA3AF"));

    s1->setLabel(QString("Technicien %1%").arg((technicien*100.0)/total,0,'f',1));
    s2->setLabel(QString("Manager %1%").arg((manager*100.0)/total,0,'f',1));
    s3->setLabel(QString("Administratif %1%").arg((administratif*100.0)/total,0,'f',1));
    s4->setLabel(QString("Agent terrain %1%").arg((agentTerrain*100.0)/total,0,'f',1));
    s5->setLabel(QString("Autre %1%").arg((autre*100.0)/total,0,'f',1));

    s1->setLabelVisible(true);
    s2->setLabelVisible(true);
    s3->setLabelVisible(true);
    s4->setLabelVisible(true);
    s5->setLabelVisible(true);

    QObject::connect(s1, &QPieSlice::hovered, [=](bool state){ s1->setExploded(state); });
    QObject::connect(s2, &QPieSlice::hovered, [=](bool state){ s2->setExploded(state); });
    QObject::connect(s3, &QPieSlice::hovered, [=](bool state){ s3->setExploded(state); });
    QObject::connect(s4, &QPieSlice::hovered, [=](bool state){ s4->setExploded(state); });
    QObject::connect(s5, &QPieSlice::hovered, [=](bool state){ s5->setExploded(state); });

    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->setTitle("Répartition par poste");
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


