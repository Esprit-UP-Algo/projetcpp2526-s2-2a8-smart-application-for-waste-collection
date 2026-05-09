#include "collecte.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QTableWidget>
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
#include <QCoreApplication>
#include <QDateTime>
#include <QHeaderView>
#include <QMessageBox>

// ============================================================
// Constructeurs
// ============================================================
Collecte::Collecte()
    : m_id(0), m_dateCollecte(""), m_typeDechet(""),
    m_quantiteCollectee(0.0), m_statut(""),
    m_distanceTotale(0.0), m_observations("")
{}

Collecte::Collecte(int id, const QString &dateCollecte, const QString &typeDechet,
                   double quantiteCollectee, const QString &statut,
                   double distanceTotale, const QString &observations)
    : m_id(id), m_dateCollecte(dateCollecte), m_typeDechet(typeDechet),
    m_quantiteCollectee(quantiteCollectee), m_statut(statut),
    m_distanceTotale(distanceTotale), m_observations(observations)
{}

// ============================================================
// Getters
// ============================================================
int     Collecte::getId()                const { return m_id; }
QString Collecte::getDateCollecte()      const { return m_dateCollecte; }
QString Collecte::getTypeDechet()        const { return m_typeDechet; }
double  Collecte::getQuantiteCollectee() const { return m_quantiteCollectee; }
QString Collecte::getStatut()            const { return m_statut; }
double  Collecte::getDistanceTotale()    const { return m_distanceTotale; }
QString Collecte::getObservations()      const { return m_observations; }

// ============================================================
// Setters
// ============================================================
void Collecte::setId(int id)                     { m_id                = id; }
void Collecte::setDateCollecte(const QString &v)  { m_dateCollecte      = v; }
void Collecte::setTypeDechet(const QString &v)    { m_typeDechet        = v; }
void Collecte::setQuantiteCollectee(double v)     { m_quantiteCollectee = v; }
void Collecte::setStatut(const QString &v)        { m_statut            = v; }
void Collecte::setDistanceTotale(double v)        { m_distanceTotale    = v; }
void Collecte::setObservations(const QString &v)  { m_observations      = v; }

// ============================================================
// Validation
// ============================================================
bool Collecte::estValide() const
{
    return !m_dateCollecte.trimmed().isEmpty()
    && !m_typeDechet.trimmed().isEmpty()
        && m_quantiteCollectee > 0.0
        && !m_statut.trimmed().isEmpty();
}

// ============================================================
// CRUD — ajouter
// ============================================================
bool Collecte::ajouter()
{
    QSqlQuery queryId;
    if (!queryId.exec("SELECT NVL(MAX(ID_collecte),0)+1 FROM COLLECTES"))
        return false;
    if (queryId.next()) m_id = queryId.value(0).toInt();

    QSqlQuery query;
    query.prepare(
        "INSERT INTO COLLECTES (ID_collecte, Date_collecte, Type_dechet, "
        "Quantite_collectee, Statut, Distance_totale, Observations) "
        "VALUES (:id, TO_DATE(:date,'DD/MM/YYYY'), :type, :qte, :statut, :dist, :obs)"
        );
    query.bindValue(":id",     m_id);
    query.bindValue(":date",   m_dateCollecte);
    query.bindValue(":type",   m_typeDechet);
    query.bindValue(":qte",    m_quantiteCollectee);
    query.bindValue(":statut", m_statut);
    query.bindValue(":dist",   m_distanceTotale);
    query.bindValue(":obs",    m_observations);
    if (!query.exec()) {
        qDebug() << "Collecte::ajouter error:" << query.lastError().text();
        return false;
    }
    enregistrerHistoriqueAction("INSERT", m_id, "Date: " + m_dateCollecte + ", Type: " + m_typeDechet);
    return true;
}

// ============================================================
// CRUD — modifier
// ============================================================
bool Collecte::modifier()
{
    QSqlQuery query;
    query.prepare(
        "UPDATE COLLECTES SET "
        "Date_collecte=TO_DATE(:date,'DD/MM/YYYY'), Type_dechet=:type, "
        "Quantite_collectee=:qte, Statut=:statut, "
        "Distance_totale=:dist, Observations=:obs "
        "WHERE ID_collecte=:id"
        );
    query.bindValue(":date",   m_dateCollecte);
    query.bindValue(":type",   m_typeDechet);
    query.bindValue(":qte",    m_quantiteCollectee);
    query.bindValue(":statut", m_statut);
    query.bindValue(":dist",   m_distanceTotale);
    query.bindValue(":obs",    m_observations);
    query.bindValue(":id",     m_id);
    if (!query.exec()) {
        qDebug() << "Collecte::modifier error:" << query.lastError().text();
        return false;
    }
    enregistrerHistoriqueAction("UPDATE", m_id, "Statut: " + m_statut + ", Obs: " + m_observations);
    return true;
}

// ============================================================
// CRUD — supprimer
// ============================================================
bool Collecte::supprimer(int id)
{
    QSqlQuery query;
    query.prepare("DELETE FROM COLLECTES WHERE ID_collecte = :id");
    query.bindValue(":id", id);
    if (!query.exec()) {
        qDebug() << "Collecte::supprimer error:" << query.lastError().text();
        return false;
    }
    enregistrerHistoriqueAction("DELETE", id, "Suppression de la collecte #" + QString::number(id));
    return true;
}

// ============================================================
// CRUD — getAll
// ============================================================
QList<Collecte> Collecte::getAll()
{
    QList<Collecte> liste;
    QSqlQuery query;
    if (!query.exec(
            "SELECT ID_collecte, TO_CHAR(Date_collecte,'DD/MM/YYYY'), "
            "Type_dechet, Quantite_collectee, Statut, "
            "Distance_totale, Observations FROM COLLECTES ORDER BY ID_collecte"))
        return liste;

    while (query.next()) {
        Collecte c(
            query.value(0).toInt(),
            query.value(1).toString(),
            query.value(2).toString(),
            query.value(3).toDouble(),
            query.value(4).toString(),
            query.value(5).toDouble(),
            query.value(6).toString()
            );
        liste.append(c);
    }
    return liste;
}

// ============================================================
// CRUD — getById
// ============================================================
Collecte Collecte::getById(int id)
{
    QSqlQuery query;
    query.prepare(
        "SELECT ID_collecte, TO_CHAR(Date_collecte,'DD/MM/YYYY'), "
        "Type_dechet, Quantite_collectee, Statut, Distance_totale, Observations "
        "FROM COLLECTES WHERE ID_collecte = :id"
        );
    query.bindValue(":id", id);
    if (query.exec() && query.next()) {
        return Collecte(
            query.value(0).toInt(),
            query.value(1).toString(),
            query.value(2).toString(),
            query.value(3).toDouble(),
            query.value(4).toString(),
            query.value(5).toDouble(),
            query.value(6).toString()
            );
    }
    return Collecte();
}

// ============================================================
// Vérification FK — Architecture Modèle-Vue
// ============================================================
int Collecte::compterLiensConsommer(int id)
{
    QSqlQuery q;
    q.prepare("SELECT COUNT(*) FROM CONSOMMER WHERE ID_collecte = :id");
    q.bindValue(":id", id);
    if (q.exec() && q.next()) return q.value(0).toInt();
    return 0;
}

int Collecte::compterLiensFournir(int id)
{
    QSqlQuery q;
    q.prepare("SELECT COUNT(*) FROM FOURNIR WHERE ID_collecte = :id");
    q.bindValue(":id", id);
    if (q.exec() && q.next()) return q.value(0).toInt();
    return 0;
}

// ============================================================
// Recherche dans QTableWidget
// ============================================================
void Collecte::rechercherDansTable(QTableWidget *table, const QString &text)
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
// Tri + filtre — charge la table depuis la BD
// ============================================================
void Collecte::loadCollectesIntoTable(QTableWidget *table,
                                      const QString &orderBy,
                                      const QString &filterStatut)
{
    QStringList allowed = {"ID_collecte", "Date_collecte", "Type_dechet",
                           "Quantite_collectee", "Statut", "Distance_totale"};
    QString safeOrder = "ID_collecte";
    for (const QString &col : allowed)
        if (col.compare(orderBy, Qt::CaseInsensitive) == 0) { safeOrder = col; break; }

    QString whereClause;
    if (!filterStatut.isEmpty())
        whereClause = "WHERE UPPER(Statut) = UPPER('" + filterStatut + "')";

    QString queryStr = QString(
                           "SELECT ID_collecte, TO_CHAR(Date_collecte,'DD/MM/YYYY'), "
                           "Type_dechet, Quantite_collectee, Statut, Distance_totale, Observations "
                           "FROM COLLECTES %1 ORDER BY %2"
                           ).arg(whereClause, safeOrder);

    QSqlQuery q;
    q.exec(queryStr);

    table->setSortingEnabled(false);
    table->clearContents();
    table->setRowCount(0);

    int row = 0;
    while (q.next()) {
        table->insertRow(row);
        for (int col = 0; col < 7; col++)
            table->setItem(row, col, new QTableWidgetItem(q.value(col).toString()));
        table->setColumnHidden(0, true);
        row++;
    }
    table->setSortingEnabled(true);
}

// ============================================================
// Export liste PDF / Word
// ============================================================
void Collecte::exporterListe(QTableWidget *table)
{
    if (!table) return;

    QStringList options = {"PDF", "Word"};
    bool ok;
    QString choice = QInputDialog::getItem(nullptr, "Exporter la liste",
                                           "Choisir le format :", options, 0, false, &ok);
    if (!ok || choice.isEmpty()) return;

    QString filter = (choice == "PDF") ? "*.pdf" : "*.doc";
    QString fileName = QFileDialog::getSaveFileName(nullptr, "Exporter la liste", "", filter);
    if (fileName.isEmpty()) return;

    if (choice == "PDF" && !fileName.endsWith(".pdf")) fileName += ".pdf";
    if (choice == "Word" && !fileName.endsWith(".doc")) fileName += ".doc";

    QString html;
    html += "<h2>Liste des Collectes</h2>";
    html += "<table border='1' cellspacing='0' cellpadding='4'><tr>";
    for (int c = 0; c < table->columnCount(); ++c)
        if (!table->isColumnHidden(c))
            html += "<th>" + table->horizontalHeaderItem(c)->text() + "</th>";
    html += "</tr>";
    for (int r = 0; r < table->rowCount(); ++r) {
        html += "<tr>";
        for (int c = 0; c < table->columnCount(); ++c) {
            if (table->isColumnHidden(c)) continue;
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
                             "La liste des collectes a été exportée avec succès.");
}

// ============================================================
// Statistiques
// ============================================================
void Collecte::afficherStatistiques(QWidget *parent)
{
    QSqlQuery q;

    int total = 0;
    if (q.exec("SELECT COUNT(*) FROM COLLECTES") && q.next())
        total = q.value(0).toInt();

    auto countStatut = [&](const QString &s) -> int {
        q.prepare("SELECT COUNT(*) FROM COLLECTES WHERE UPPER(Statut)=UPPER(:s)");
        q.bindValue(":s", s);
        if (q.exec() && q.next()) return q.value(0).toInt();
        return 0;
    };
    int terminee  = countStatut("Terminée");
    int enCours   = countStatut("En cours");
    int annulee   = countStatut("Annulée");
    int planifiee = countStatut("Planifiée");

    double qteTotal = 0, qteMax = 0, qteMin = 0;
    if (q.exec("SELECT SUM(Quantite_collectee), MAX(Quantite_collectee), MIN(Quantite_collectee) FROM COLLECTES") && q.next()) {
        qteTotal = q.value(0).toDouble();
        qteMax   = q.value(1).toDouble();
        qteMin   = q.value(2).toDouble();
    }

    QDialog *dlg = new QDialog(parent);
    dlg->setWindowTitle("📊 Statistiques des Collectes");
    dlg->setFixedSize(780, 620);
    dlg->setStyleSheet("QDialog { background-color: #F0F4F8; }");

    QVBoxLayout *mainLay = new QVBoxLayout(dlg);
    mainLay->setContentsMargins(20, 20, 20, 20);
    mainLay->setSpacing(16);

    QLabel *title = new QLabel("📊 Tableau de Bord — Statistiques Collectes");
    title->setAlignment(Qt::AlignCenter);
    title->setStyleSheet(
        "font-size:18px; font-weight:bold; color:white; padding:16px;"
        "background:qlineargradient(x1:0,y1:0,x2:1,y2:0,stop:0 #1B3A57,stop:1 #2C5F7C);"
        "border-radius:12px;");
    mainLay->addWidget(title);

    auto makeKPI = [](const QString &icon, const QString &value,
                      const QString &label, const QString &color) {
        QFrame *card = new QFrame();
        card->setFixedHeight(90);
        card->setStyleSheet(QString("QFrame { background-color:%1; border-radius:12px; }").arg(color));
        QVBoxLayout *cl = new QVBoxLayout(card);
        cl->setContentsMargins(14,10,14,10); cl->setSpacing(2);
        QLabel *ico = new QLabel(icon + "  " + value);
        ico->setStyleSheet("font-size:22px; font-weight:bold; color:white; background:transparent;");
        QLabel *lbl = new QLabel(label);
        lbl->setStyleSheet("font-size:11px; color:rgba(255,255,255,0.85); background:transparent;");
        cl->addWidget(ico); cl->addWidget(lbl);
        return card;
    };

    QHBoxLayout *kpiRow = new QHBoxLayout();
    kpiRow->setSpacing(12);
    kpiRow->addWidget(makeKPI("🗑️", QString::number(total),    "Total collectes", "#2C5F7C"));
    kpiRow->addWidget(makeKPI("✅", QString::number(terminee), "Terminées",       "#27AE60"));
    kpiRow->addWidget(makeKPI("⏳", QString::number(enCours),  "En cours",        "#E67E22"));
    kpiRow->addWidget(makeKPI("📅", QString::number(planifiee),"Planifiées",      "#3B82F6"));
    kpiRow->addWidget(makeKPI("❌", QString::number(annulee),  "Annulées",        "#E74C3C"));
    mainLay->addLayout(kpiRow);

    QFrame *qteCard = new QFrame();
    qteCard->setStyleSheet("QFrame { background:white; border-radius:12px; }");
    QHBoxLayout *qteLay = new QHBoxLayout(qteCard);
    qteLay->setContentsMargins(20,14,20,14);
    auto makeStat = [](const QString &lbl, const QString &val) {
        QVBoxLayout *vl = new QVBoxLayout();
        QLabel *v = new QLabel(val); v->setAlignment(Qt::AlignCenter);
        v->setStyleSheet("font-size:20px; font-weight:bold; color:#2C5F7C;");
        QLabel *l = new QLabel(lbl); l->setAlignment(Qt::AlignCenter);
        l->setStyleSheet("font-size:11px; color:#6B7280;");
        vl->addWidget(v); vl->addWidget(l); return vl;
    };
    qteLay->addLayout(makeStat("Total (kg)",   QString::number(qteTotal,'f',2)));
    qteLay->addSpacing(30);
    qteLay->addLayout(makeStat("Maximum (kg)", QString::number(qteMax,'f',2)));
    qteLay->addSpacing(30);
    qteLay->addLayout(makeStat("Minimum (kg)", QString::number(qteMin,'f',2)));
    mainLay->addWidget(qteCard);

    QPushButton *closeBtn = new QPushButton("✕  Fermer");
    closeBtn->setFixedHeight(42);
    closeBtn->setStyleSheet(
        "QPushButton{background:#2C5F7C;color:white;font-size:14px;font-weight:600;"
        "border:none;border-radius:8px;}"
        "QPushButton:hover{background:#1B3A57;}");
    QObject::connect(closeBtn, &QPushButton::clicked, dlg, &QDialog::accept);
    mainLay->addWidget(closeBtn);

    dlg->exec();
}

// ============================================================
// Historique des Actions
// ============================================================

void Collecte::enregistrerHistoriqueAction(const QString &action, int id, const QString &details)
{
    // On force le chemin vers le dossier du projet pour que l'utilisateur le trouve facilement
    QString path = "C:/Projets/FF/HistoriqueBD.txt"; 
    QFile file(path);
    if (file.open(QIODevice::Append | QIODevice::Text)) {
        QTextStream out(&file);
        QString timestamp = QDateTime::currentDateTime().toString("dd/MM/yyyy HH:mm:ss");
        out << timestamp << " | " << action << " | ID : " << id << " | " << details << "\n";
        file.close();
        QMessageBox::information(nullptr, "Historique", "Action enregistrée dans l'historique avec succès !");
    } else {
        qDebug() << "Failed to open history file for writing:" << path << file.errorString();
    }
}

void Collecte::afficherHistorique(QTableWidget *table)
{
    Q_UNUSED(table); 

    QDialog *dlg = new QDialog();
    dlg->setWindowTitle("📜 Historique des Actions (Collecte)");
    dlg->setMinimumSize(900, 500);
    dlg->setStyleSheet("QDialog { background-color: #F8FAFC; }");

    QVBoxLayout *layout = new QVBoxLayout(dlg);
    
    QLabel *title = new QLabel("📋 Journal des opérations effectuées");
    title->setStyleSheet("font-size:16px; font-weight:bold; color:#1B3A57; margin-bottom:10px;");
    layout->addWidget(title);

    QTableWidget *hTable = new QTableWidget();
    hTable->setColumnCount(4);
    hTable->setHorizontalHeaderLabels({"📅 Date & Heure", "⚡ Action", "🆔 ID", "📝 Détails"});
    hTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    hTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    hTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    hTable->setStyleSheet(R"(
        QTableWidget { background-color: white; border: 1px solid #E2E8F0; border-radius: 8px; }
        QHeaderView::section { background-color: #F1F5F9; font-weight: bold; padding: 8px; border: none; border-bottom: 2px solid #CBD5E1; }
    )");

    QString path = "C:/Projets/FF/HistoriqueBD.txt";
    QFile file(path);
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream in(&file);
        int row = 0;
        while (!in.atEnd()) {
            QString line = in.readLine();
            QStringList parts = line.split(" | ");
            if (parts.size() >= 4) {
                hTable->insertRow(row);
                for (int i = 0; i < 4; i++) {
                    QString val = parts[i];
                    if (i == 2) val.replace("ID : ", ""); // Nettoyer pour l'affichage si on veut juste le chiffre, ou laisser tel quel
                    QTableWidgetItem *item = new QTableWidgetItem(val);
                    if (i == 1) { // Colonne Action
                        QString action = parts[i].trimmed().toUpper();
                        if (action == "INSERT") item->setBackground(QColor("#D1FAE5"));
                        else if (action == "UPDATE") item->setBackground(QColor("#FEF3C7"));
                        else if (action == "DELETE") item->setBackground(QColor("#FEE2E2"));
                    }
                    hTable->setItem(row, i, item);
                }
                row++;
            }
        }
        file.close();
    }

    layout->addWidget(hTable);

    QPushButton *closeBtn = new QPushButton("Fermer");
    closeBtn->setFixedWidth(120);
    closeBtn->setStyleSheet("QPushButton { background-color: #1B3A57; color: white; padding: 8px; border-radius: 5px; }");
    QObject::connect(closeBtn, &QPushButton::clicked, dlg, &QDialog::accept);
    
    QHBoxLayout *btnLay = new QHBoxLayout();
    btnLay->addStretch();
    btnLay->addWidget(closeBtn);
    layout->addLayout(btnLay);

    dlg->exec();
    delete dlg;
}
