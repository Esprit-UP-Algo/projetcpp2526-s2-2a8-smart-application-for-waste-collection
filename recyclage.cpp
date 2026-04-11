#include "recyclage.h"
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

// ============================================================
// Constructeurs
// ============================================================
Recyclage::Recyclage()
    : m_id(0), m_dateTri(""), m_typeMateriau(""),
    m_quantiteEntree(0.0), m_quantiteRecyclee(0.0), m_quantiteRejetee(0.0),
    m_destination(""), m_valeurMonetaire(0.0), m_direction(""), m_statut("")
{}

Recyclage::Recyclage(int id, const QString &dateTri, const QString &typeMateriau,
                     double quantiteEntree, double quantiteRecyclee, double quantiteRejetee,
                     const QString &destination, double valeurMonetaire,
                     const QString &direction, const QString &statut)
    : m_id(id), m_dateTri(dateTri), m_typeMateriau(typeMateriau),
    m_quantiteEntree(quantiteEntree), m_quantiteRecyclee(quantiteRecyclee),
    m_quantiteRejetee(quantiteRejetee), m_destination(destination),
    m_valeurMonetaire(valeurMonetaire), m_direction(direction), m_statut(statut)
{}

// ============================================================
// Getters
// ============================================================
int     Recyclage::getId()               const { return m_id; }
QString Recyclage::getDateTri()          const { return m_dateTri; }
QString Recyclage::getTypeMateriau()     const { return m_typeMateriau; }
double  Recyclage::getQuantiteEntree()   const { return m_quantiteEntree; }
double  Recyclage::getQuantiteRecyclee() const { return m_quantiteRecyclee; }
double  Recyclage::getQuantiteRejetee()  const { return m_quantiteRejetee; }
QString Recyclage::getDestination()      const { return m_destination; }
double  Recyclage::getValeurMonetaire()  const { return m_valeurMonetaire; }
QString Recyclage::getDirection()        const { return m_direction; }
QString Recyclage::getStatut()           const { return m_statut; }

// ============================================================
// Setters
// ============================================================
void Recyclage::setId(int id)                        { m_id               = id; }
void Recyclage::setDateTri(const QString &v)         { m_dateTri          = v; }
void Recyclage::setTypeMateriau(const QString &v)    { m_typeMateriau     = v; }
void Recyclage::setQuantiteEntree(double v)          { m_quantiteEntree   = v; }
void Recyclage::setQuantiteRecyclee(double v)        { m_quantiteRecyclee = v; }
void Recyclage::setQuantiteRejetee(double v)         { m_quantiteRejetee  = v; }
void Recyclage::setDestination(const QString &v)     { m_destination      = v; }
void Recyclage::setValeurMonetaire(double v)         { m_valeurMonetaire  = v; }
void Recyclage::setDirection(const QString &v)       { m_direction        = v; }
void Recyclage::setStatut(const QString &v)          { m_statut           = v; }

// ============================================================
// Validation
// ============================================================
bool Recyclage::estValide() const
{
    return !m_dateTri.trimmed().isEmpty()
    && !m_typeMateriau.trimmed().isEmpty()
        && m_quantiteEntree > 0.0
        && !m_destination.trimmed().isEmpty()
        && !m_statut.trimmed().isEmpty();
}

// ============================================================
// CRUD — ajouter
// ============================================================
bool Recyclage::ajouter()
{
    QSqlQuery queryId;
    if (!queryId.exec("SELECT NVL(MAX(ID_recyclage),0)+1 FROM RECYCLAGES"))
        return false;
    if (queryId.next()) m_id = queryId.value(0).toInt();

    QSqlQuery query;
    query.prepare(
        "INSERT INTO RECYCLAGES (ID_recyclage, Date_tri, Type_materiau, "
        "Quantite_entree, Quantite_recyclee, Quantite_rejetee, "
        "Destination, Valeur_monetaire, Direction, Statut) "
        "VALUES (:id, TO_DATE(:date,'DD/MM/YYYY'), :type, :qte_e, "
        ":qte_r, :qte_rej, :dest, :valeur, :dir, :statut)"
        );
    query.bindValue(":id",      m_id);
    query.bindValue(":date",    m_dateTri);
    query.bindValue(":type",    m_typeMateriau);
    query.bindValue(":qte_e",   m_quantiteEntree);
    query.bindValue(":qte_r",   m_quantiteRecyclee);
    query.bindValue(":qte_rej", m_quantiteRejetee);
    query.bindValue(":dest",    m_destination);
    query.bindValue(":valeur",  m_valeurMonetaire);
    query.bindValue(":dir",     m_direction);
    query.bindValue(":statut",  m_statut);
    if (!query.exec()) {
        qDebug() << "Recyclage::ajouter error:" << query.lastError().text();
        return false;
    }
    return true;
}

// ============================================================
// CRUD — modifier
// ============================================================
bool Recyclage::modifier()
{
    QSqlQuery query;
    query.prepare(
        "UPDATE RECYCLAGES SET "
        "Date_tri=TO_DATE(:date,'DD/MM/YYYY'), Type_materiau=:type, "
        "Quantite_entree=:qte_e, Quantite_recyclee=:qte_r, "
        "Quantite_rejetee=:qte_rej, Destination=:dest, "
        "Valeur_monetaire=:valeur, Direction=:dir, Statut=:statut "
        "WHERE ID_recyclage=:id"
        );
    query.bindValue(":date",    m_dateTri);
    query.bindValue(":type",    m_typeMateriau);
    query.bindValue(":qte_e",   m_quantiteEntree);
    query.bindValue(":qte_r",   m_quantiteRecyclee);
    query.bindValue(":qte_rej", m_quantiteRejetee);
    query.bindValue(":dest",    m_destination);
    query.bindValue(":valeur",  m_valeurMonetaire);
    query.bindValue(":dir",     m_direction);
    query.bindValue(":statut",  m_statut);
    query.bindValue(":id",      m_id);
    if (!query.exec()) {
        qDebug() << "Recyclage::modifier error:" << query.lastError().text();
        return false;
    }
    return true;
}

// ============================================================
// CRUD — supprimer
// ============================================================
bool Recyclage::supprimer(int id)
{
    QSqlQuery query;
    query.prepare("DELETE FROM RECYCLAGES WHERE ID_recyclage = :id");
    query.bindValue(":id", id);
    if (!query.exec()) {
        qDebug() << "Recyclage::supprimer error:" << query.lastError().text();
        return false;
    }
    return true;
}

// ============================================================
// CRUD — getAll
// ============================================================
QList<Recyclage> Recyclage::getAll()
{
    QList<Recyclage> liste;
    QSqlQuery query;
    if (!query.exec(
            "SELECT ID_recyclage, TO_CHAR(Date_tri,'DD/MM/YYYY'), Type_materiau, "
            "Quantite_entree, Quantite_recyclee, Quantite_rejetee, "
            "Destination, Valeur_monetaire, Direction, Statut "
            "FROM RECYCLAGES ORDER BY ID_recyclage"))
        return liste;

    while (query.next()) {
        Recyclage r(
            query.value(0).toInt(),
            query.value(1).toString(),
            query.value(2).toString(),
            query.value(3).toDouble(),
            query.value(4).toDouble(),
            query.value(5).toDouble(),
            query.value(6).toString(),
            query.value(7).toDouble(),
            query.value(8).toString(),
            query.value(9).toString()
            );
        liste.append(r);
    }
    return liste;
}

// ============================================================
// CRUD — getById
// ============================================================
Recyclage Recyclage::getById(int id)
{
    QSqlQuery query;
    query.prepare(
        "SELECT ID_recyclage, TO_CHAR(Date_tri,'DD/MM/YYYY'), Type_materiau, "
        "Quantite_entree, Quantite_recyclee, Quantite_rejetee, "
        "Destination, Valeur_monetaire, Direction, Statut "
        "FROM RECYCLAGES WHERE ID_recyclage = :id"
        );
    query.bindValue(":id", id);
    if (query.exec() && query.next()) {
        return Recyclage(
            query.value(0).toInt(),
            query.value(1).toString(),
            query.value(2).toString(),
            query.value(3).toDouble(),
            query.value(4).toDouble(),
            query.value(5).toDouble(),
            query.value(6).toString(),
            query.value(7).toDouble(),
            query.value(8).toString(),
            query.value(9).toString()
            );
    }
    return Recyclage();
}

// ============================================================
// Recherche dans QTableWidget
// ============================================================
void Recyclage::rechercherDansTable(QTableWidget *table, const QString &text)
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
void Recyclage::loadRecyclagesIntoTable(QTableWidget *table,
                                        const QString &orderBy,
                                        const QString &filterStatut)
{
    QStringList allowed = {"ID_recyclage", "Date_tri", "Type_materiau",
                           "Quantite_entree", "Quantite_recyclee",
                           "Valeur_monetaire", "Statut"};
    QString safeOrder = "ID_recyclage";
    for (const QString &col : allowed)
        if (col.compare(orderBy, Qt::CaseInsensitive) == 0) { safeOrder = col; break; }

    QString whereClause;
    if (!filterStatut.isEmpty())
        whereClause = "WHERE UPPER(Statut) = UPPER('" + filterStatut + "')";

    QString queryStr = QString(
                           "SELECT ID_recyclage, TO_CHAR(Date_tri,'DD/MM/YYYY'), Type_materiau, "
                           "Quantite_entree, Quantite_recyclee, Quantite_rejetee, "
                           "Destination, Valeur_monetaire, Direction, Statut "
                           "FROM RECYCLAGES %1 ORDER BY %2"
                           ).arg(whereClause, safeOrder);

    QSqlQuery q;
    q.exec(queryStr);

    table->setSortingEnabled(false);
    table->clearContents();
    table->setRowCount(0);

    int row = 0;
    while (q.next()) {
        table->insertRow(row);
        for (int col = 0; col < 10; col++)
            table->setItem(row, col, new QTableWidgetItem(q.value(col).toString()));
        table->setColumnHidden(0, true);
        row++;
    }
    table->setSortingEnabled(true);
}

// ============================================================
// Export liste PDF / Word
// ============================================================
void Recyclage::exporterListe(QTableWidget *table)
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
    html += "<h2>Liste des Recyclages</h2>";
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
                             "La liste des recyclages a été exportée avec succès.");
}

// ============================================================
// Statistiques
// ============================================================
void Recyclage::afficherStatistiques(QWidget *parent)
{
    QSqlQuery q;

    int total = 0;
    if (q.exec("SELECT COUNT(*) FROM RECYCLAGES") && q.next())
        total = q.value(0).toInt();

    double valeurTotale = 0;
    if (q.exec("SELECT SUM(Valeur_monetaire) FROM RECYCLAGES") && q.next())
        valeurTotale = q.value(0).toDouble();

    double qteTotale = 0;
    if (q.exec("SELECT SUM(Quantite_recyclee) FROM RECYCLAGES") && q.next())
        qteTotale = q.value(0).toDouble();

    auto countStatut = [&](const QString &s) -> int {
        q.prepare("SELECT COUNT(*) FROM RECYCLAGES WHERE UPPER(Statut)=UPPER(:s)");
        q.bindValue(":s", s);
        if (q.exec() && q.next()) return q.value(0).toInt();
        return 0;
    };
    int termine  = countStatut("Terminé");
    int enCours  = countStatut("En cours");
    int annule   = countStatut("Annulé");
    int enAttente= countStatut("En attente");

    // ── UI
    QDialog *dlg = new QDialog(parent);
    dlg->setWindowTitle("📊 Statistiques des Recyclages");
    dlg->setFixedSize(780, 620);
    dlg->setStyleSheet("QDialog { background-color: #F0F4F8; }");

    QVBoxLayout *mainLay = new QVBoxLayout(dlg);
    mainLay->setContentsMargins(20, 20, 20, 20);
    mainLay->setSpacing(16);

    QLabel *title = new QLabel("📊 Tableau de Bord — Statistiques Recyclages");
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
    kpiRow->addWidget(makeKPI("♻️", QString::number(total),                      "Total recyclages",  "#2C5F7C"));
    kpiRow->addWidget(makeKPI("💰", QString::number(valeurTotale,'f',2)+" TND",  "Valeur totale",     "#27AE60"));
    kpiRow->addWidget(makeKPI("✅", QString::number(termine),                    "Terminés",          "#10B981"));
    kpiRow->addWidget(makeKPI("⏳", QString::number(enCours),                    "En cours",          "#E67E22"));
    kpiRow->addWidget(makeKPI("❌", QString::number(annule),                     "Annulés",           "#E74C3C"));
    mainLay->addLayout(kpiRow);

    // Quantités recyclées
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
    qteLay->addLayout(makeStat("Qté Recyclée (kg)",    QString::number(qteTotale,'f',2)));
    qteLay->addSpacing(30);
    qteLay->addLayout(makeStat("En attente",            QString::number(enAttente)));
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
