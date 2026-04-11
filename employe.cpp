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
    QSqlQuery query;
    query.prepare(
        "INSERT INTO EMPLOYES (CIN, Nom, Prenom, Email, Poste, Telephone, "
        "Salaire, Date_embauche, Service) "
        "VALUES (:cin, :nom, :prenom, :email, :poste, :tel, :salaire, "
        "TO_DATE(:date, 'DD/MM/YYYY'), :service)"
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
    if (!query.exec()) {
        qDebug() << "Employe::ajouter error:" << query.lastError().text();
        return false;
    }
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
void Employe::exporterListe(QTableWidget *table)
{
    if (!table) return;

    QStringList options = {"PDF", "Word"};
    bool ok;
    QString choice = QInputDialog::getItem(nullptr, "Exporter la liste",
                                           "Choisir le format :", options, 0, false, &ok);
    if (!ok || choice.isEmpty()) return;

    QString filter   = (choice == "PDF") ? "*.pdf" : "*.doc";
    QString fileName = QFileDialog::getSaveFileName(nullptr, "Exporter la liste", "", filter);
    if (fileName.isEmpty()) return;

    if (choice == "PDF" && !fileName.endsWith(".pdf")) fileName += ".pdf";
    if (choice == "Word" && !fileName.endsWith(".doc")) fileName += ".doc";

    // Générer HTML
    QString html;
    html += "<html><head><meta charset='utf-8'><style>"
            "body{font-family:Arial,sans-serif;font-size:12px;}"
            "h2{text-align:center;color:#2C5F7C;}"
            "p{text-align:center;color:#555;}"
            "table{width:100%;border-collapse:collapse;margin-top:16px;}"
            "th{background:#2C5F7C;color:white;padding:8px;text-align:left;}"
            "td{border:1px solid #ddd;padding:6px;}"
            "tr:nth-child(even){background:#f2f2f2;}"
            "</style></head><body>";
    html += "<h2>Liste des Employés</h2>";
    html += "<p>Exporté le : " + QDate::currentDate().toString("dd/MM/yyyy") + "</p>";
    html += "<table><tr>";
    for (int c = 0; c < table->columnCount(); ++c)
        if (!table->isColumnHidden(c) && table->horizontalHeaderItem(c))
            html += "<th>" + table->horizontalHeaderItem(c)->text() + "</th>";
    html += "</tr>";
    for (int r = 0; r < table->rowCount(); ++r) {
        if (table->isRowHidden(r)) continue;
        html += "<tr>";
        for (int c = 0; c < table->columnCount(); ++c) {
            if (table->isColumnHidden(c)) continue;
            QTableWidgetItem *item = table->item(r, c);
            html += "<td>" + (item ? item->text() : "") + "</td>";
        }
        html += "</tr>";
    }
    html += "</table></body></html>";

    if (choice == "PDF") {
        QPrinter printer(QPrinter::HighResolution);
        printer.setOutputFormat(QPrinter::PdfFormat);
        printer.setOutputFileName(fileName);
        QTextDocument doc;
        doc.setHtml(html);
        doc.print(&printer);
    } else {
        QFile file(fileName);
        if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
            QMessageBox::critical(nullptr, "Erreur", "Impossible de créer le fichier.");
            return;
        }
        QTextStream out(&file);
        out << html;
        file.close();
    }
    QMessageBox::information(nullptr, "Export terminé",
                             "La liste des employés a été exportée avec succès.");
}

// ============================================================
// Statistiques (comme Client::afficherStatistiques)
// ============================================================
void Employe::afficherStatistiques(QWidget *parent)
{
    QSqlQuery q;

    int total = 0;
    if (q.exec("SELECT COUNT(*) FROM EMPLOYES") && q.next())
        total = q.value(0).toInt();

    int withEmail = 0;
    if (q.exec("SELECT COUNT(*) FROM EMPLOYES WHERE Email IS NOT NULL") && q.next())
        withEmail = q.value(0).toInt();

    int postesDefinis = 0;
    if (q.exec("SELECT COUNT(*) FROM EMPLOYES WHERE Poste IS NOT NULL") && q.next())
        postesDefinis = q.value(0).toInt();

    double salaireMoyen = 0, salaireMax = 0, salaireMin = 0;
    if (q.exec("SELECT AVG(Salaire), MAX(Salaire), MIN(Salaire) FROM EMPLOYES") && q.next()) {
        salaireMoyen = q.value(0).toDouble();
        salaireMax   = q.value(1).toDouble();
        salaireMin   = q.value(2).toDouble();
    }

    // Répartition par service
    auto countService = [&](const QString &s) -> int {
        q.prepare("SELECT COUNT(*) FROM EMPLOYES WHERE UPPER(Service) = UPPER(:s)");
        q.bindValue(":s", s);
        if (q.exec() && q.next()) return q.value(0).toInt();
        return 0;
    };
    int serviceIT      = countService("IT");
    int serviceRH      = countService("RH");
    int serviceFinance = countService("Finance");

    // Répartition par poste
    auto countPoste = [&](const QString &p) -> int {
        q.prepare("SELECT COUNT(*) FROM EMPLOYES WHERE UPPER(Poste) = UPPER(:p)");
        q.bindValue(":p", p);
        if (q.exec() && q.next()) return q.value(0).toInt();
        return 0;
    };
    int technicien   = countPoste("Technicien");
    int administratif = countPoste("Administratif");
    int manager      = countPoste("Manager");
    int agentTerrain = countPoste("Agent terrain");

    // ── UI ──────────────────────────────────────────────────────
    QDialog *dlg = new QDialog(parent);
    dlg->setWindowTitle("📊 Statistiques des Employés");
    dlg->setFixedSize(780, 680);
    dlg->setStyleSheet("QDialog { background-color: #F0F4F8; }");

    QVBoxLayout *mainLay = new QVBoxLayout(dlg);
    mainLay->setContentsMargins(20, 20, 20, 20);
    mainLay->setSpacing(16);

    // Titre
    QLabel *title = new QLabel("📊 Tableau de Bord — Statistiques Employés");
    title->setAlignment(Qt::AlignCenter);
    title->setStyleSheet(
        "font-size:18px; font-weight:bold; color:white; padding:16px;"
        "background:qlineargradient(x1:0,y1:0,x2:1,y2:0,stop:0 #1B3A57,stop:1 #2C5F7C);"
        "border-radius:12px;"
        );
    mainLay->addWidget(title);

    // Fabrique KPI
    auto makeKPI = [](const QString &icon, const QString &value,
                      const QString &label, const QString &color) {
        QFrame *card = new QFrame();
        card->setFixedHeight(90);
        card->setStyleSheet(QString("QFrame { background-color:%1; border-radius:12px; }").arg(color));
        QVBoxLayout *cl = new QVBoxLayout(card);
        cl->setContentsMargins(14, 10, 14, 10); cl->setSpacing(2);
        QLabel *ico = new QLabel(icon + "  " + value);
        ico->setStyleSheet("font-size:22px; font-weight:bold; color:white; background:transparent;");
        QLabel *lbl = new QLabel(label);
        lbl->setStyleSheet("font-size:11px; color:rgba(255,255,255,0.85); background:transparent;");
        cl->addWidget(ico); cl->addWidget(lbl);
        return card;
    };

    // Ligne 1 : KPI effectif
    QHBoxLayout *kpiRow = new QHBoxLayout();
    kpiRow->setSpacing(12);
    kpiRow->addWidget(makeKPI("👥", QString::number(total),         "Total employés",  "#2C5F7C"));
    kpiRow->addWidget(makeKPI("📧", QString::number(withEmail),     "Email défini",    "#27AE60"));
    kpiRow->addWidget(makeKPI("💼", QString::number(postesDefinis), "Postes définis",  "#E67E22"));
    mainLay->addLayout(kpiRow);

    // Ligne 2 : Statistiques salaires
    QFrame *salaireCard = new QFrame();
    salaireCard->setStyleSheet("QFrame { background:white; border-radius:12px; }");
    QHBoxLayout *salLay = new QHBoxLayout(salaireCard);
    salLay->setContentsMargins(20, 14, 20, 14);

    auto makeStat = [](const QString &lbl, const QString &val) {
        QVBoxLayout *vl = new QVBoxLayout();
        QLabel *v = new QLabel(val); v->setAlignment(Qt::AlignCenter);
        v->setStyleSheet("font-size:20px; font-weight:bold; color:#2C5F7C;");
        QLabel *l = new QLabel(lbl); l->setAlignment(Qt::AlignCenter);
        l->setStyleSheet("font-size:11px; color:#6B7280;");
        vl->addWidget(v); vl->addWidget(l); return vl;
    };

    QLabel *salTitle = new QLabel("💰 Salaire (DT)");
    salTitle->setStyleSheet("font-size:13px; font-weight:bold; color:#374151;");
    salLay->addWidget(salTitle);
    salLay->addStretch();
    salLay->addLayout(makeStat("Moyenne", QString::number(salaireMoyen, 'f', 2)));
    salLay->addSpacing(30);
    salLay->addLayout(makeStat("Maximum", QString::number(salaireMax,   'f', 2)));
    salLay->addSpacing(30);
    salLay->addLayout(makeStat("Minimum", QString::number(salaireMin,   'f', 2)));
    mainLay->addWidget(salaireCard);

    // Ligne 3 : Répartition par service
    QFrame *serviceCard = new QFrame();
    serviceCard->setStyleSheet("QFrame { background:white; border-radius:12px; }");
    QVBoxLayout *serviceLay = new QVBoxLayout(serviceCard);
    serviceLay->setContentsMargins(20, 14, 20, 14); serviceLay->setSpacing(10);
    QLabel *serviceTitle = new QLabel("🏢 Répartition par Service");
    serviceTitle->setStyleSheet("font-size:13px; font-weight:bold; color:#374151;");
    serviceLay->addWidget(serviceTitle);

    struct ServiceStat { QString name; int count; QString color; };
    QList<ServiceStat> services = {
                                   {"IT",      serviceIT,      "#3B82F6"},
                                   {"RH",      serviceRH,      "#10B981"},
                                   {"Finance", serviceFinance, "#F59E0B"},
                                   };
    QHBoxLayout *serviceRow = new QHBoxLayout();
    serviceRow->setSpacing(16);
    for (auto &s : services) {
        QFrame *sCard = new QFrame();
        sCard->setStyleSheet(QString("QFrame { background:%1; border-radius:10px; }").arg(s.color));
        sCard->setFixedHeight(64);
        QVBoxLayout *scl = new QVBoxLayout(sCard);
        scl->setContentsMargins(12, 8, 12, 8);
        QLabel *sv = new QLabel(QString::number(s.count));
        sv->setAlignment(Qt::AlignCenter);
        sv->setStyleSheet("font-size:20px; font-weight:bold; color:white; background:transparent;");
        QLabel *sl = new QLabel(s.name);
        sl->setAlignment(Qt::AlignCenter);
        sl->setStyleSheet("font-size:11px; color:rgba(255,255,255,0.85); background:transparent;");
        scl->addWidget(sv); scl->addWidget(sl);
        serviceRow->addWidget(sCard);
    }
    serviceLay->addLayout(serviceRow);
    mainLay->addWidget(serviceCard);

    // Ligne 4 : Répartition par poste
    QFrame *posteCard = new QFrame();
    posteCard->setStyleSheet("QFrame { background:white; border-radius:12px; }");
    QVBoxLayout *posteLay = new QVBoxLayout(posteCard);
    posteLay->setContentsMargins(20, 14, 20, 14); posteLay->setSpacing(10);
    QLabel *posteTitle = new QLabel("💼 Répartition par Poste");
    posteTitle->setStyleSheet("font-size:13px; font-weight:bold; color:#374151;");
    posteLay->addWidget(posteTitle);

    struct PosteStat { QString name; int count; QString color; };
    QList<PosteStat> postes = {
                               {"Technicien",    technicien,    "#6366F1"},
                               {"Administratif", administratif, "#EC4899"},
                               {"Manager",       manager,       "#14B8A6"},
                               {"Agent terrain", agentTerrain,  "#F97316"},
                               };
    QHBoxLayout *posteRow = new QHBoxLayout();
    posteRow->setSpacing(12);
    for (auto &p : postes) {
        QFrame *pCard = new QFrame();
        pCard->setStyleSheet(QString("QFrame { background:%1; border-radius:10px; }").arg(p.color));
        pCard->setFixedHeight(64);
        QVBoxLayout *pcl = new QVBoxLayout(pCard);
        pcl->setContentsMargins(12, 8, 12, 8);
        QLabel *pv = new QLabel(QString::number(p.count));
        pv->setAlignment(Qt::AlignCenter);
        pv->setStyleSheet("font-size:20px; font-weight:bold; color:white; background:transparent;");
        QLabel *pl = new QLabel(p.name);
        pl->setAlignment(Qt::AlignCenter);
        pl->setStyleSheet("font-size:11px; color:rgba(255,255,255,0.85); background:transparent;");
        pcl->addWidget(pv); pcl->addWidget(pl);
        posteRow->addWidget(pCard);
    }
    posteLay->addLayout(posteRow);
    mainLay->addWidget(posteCard);

    // Bouton fermer
    QPushButton *closeBtn = new QPushButton("✕  Fermer");
    closeBtn->setFixedHeight(42);
    closeBtn->setStyleSheet(
        "QPushButton { background:#2C5F7C; color:white; font-size:14px; font-weight:600;"
        "border:none; border-radius:8px; }"
        "QPushButton:hover { background:#1B3A57; }"
        );
    QObject::connect(closeBtn, &QPushButton::clicked, dlg, &QDialog::accept);
    mainLay->addWidget(closeBtn);

    dlg->exec();
}
