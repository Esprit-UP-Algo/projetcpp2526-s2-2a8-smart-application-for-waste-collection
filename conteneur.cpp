#include "conteneur.h"
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
#include <QProgressBar>

// ============================================================
// Constructeurs
// ============================================================
Conteneur::Conteneur()
    : m_id(0), m_capacite(0.0), m_typePropriete(""),
    m_adresseComplete(""), m_localisationGPS(""),
    m_accepteMenager("Non"), m_accepteRecyclable("Non"),
    m_accepteOrganique("Non"), m_accepteIndustriel("Non"),
    m_etat(""), m_dateDerniereCollecte("")
{}

Conteneur::Conteneur(int id, double capacite, const QString &typePropriete,
                     const QString &adresseComplete, const QString &localisationGPS,
                     const QString &accepteMenager, const QString &accepteRecyclable,
                     const QString &accepteOrganique, const QString &accepteIndustriel,
                     const QString &etat, const QString &dateDerniereCollecte)
    : m_id(id), m_capacite(capacite), m_typePropriete(typePropriete),
    m_adresseComplete(adresseComplete), m_localisationGPS(localisationGPS),
    m_accepteMenager(accepteMenager), m_accepteRecyclable(accepteRecyclable),
    m_accepteOrganique(accepteOrganique), m_accepteIndustriel(accepteIndustriel),
    m_etat(etat), m_dateDerniereCollecte(dateDerniereCollecte)
{}

// ============================================================
// Getters
// ============================================================
int     Conteneur::getId()                   const { return m_id; }
double  Conteneur::getCapacite()             const { return m_capacite; }
QString Conteneur::getTypePropriete()        const { return m_typePropriete; }
QString Conteneur::getAdresseComplete()      const { return m_adresseComplete; }
QString Conteneur::getLocalisationGPS()      const { return m_localisationGPS; }
QString Conteneur::getAccepteMenager()       const { return m_accepteMenager; }
QString Conteneur::getAccepteRecyclable()    const { return m_accepteRecyclable; }
QString Conteneur::getAccepteOrganique()     const { return m_accepteOrganique; }
QString Conteneur::getAccepteIndustriel()    const { return m_accepteIndustriel; }
QString Conteneur::getEtat()                 const { return m_etat; }
QString Conteneur::getDateDerniereCollecte() const { return m_dateDerniereCollecte; }

// ============================================================
// Setters
// ============================================================
void Conteneur::setId(int id)                            { m_id                   = id; }
void Conteneur::setCapacite(double v)                    { m_capacite             = v; }
void Conteneur::setTypePropriete(const QString &v)       { m_typePropriete        = v; }
void Conteneur::setAdresseComplete(const QString &v)     { m_adresseComplete      = v; }
void Conteneur::setLocalisationGPS(const QString &v)     { m_localisationGPS      = v; }
void Conteneur::setAccepteMenager(const QString &v)      { m_accepteMenager       = v; }
void Conteneur::setAccepteRecyclable(const QString &v)   { m_accepteRecyclable    = v; }
void Conteneur::setAccepteOrganique(const QString &v)    { m_accepteOrganique     = v; }
void Conteneur::setAccepteIndustriel(const QString &v)   { m_accepteIndustriel    = v; }
void Conteneur::setEtat(const QString &v)                { m_etat                 = v; }
void Conteneur::setDateDerniereCollecte(const QString &v){ m_dateDerniereCollecte = v; }

// ============================================================
// Validation
// ============================================================
bool Conteneur::estValide() const
{
    return m_capacite > 0.0
           && !m_adresseComplete.trimmed().isEmpty()
           && !m_etat.trimmed().isEmpty();
}

// ============================================================
// CRUD — ajouter
// ============================================================
bool Conteneur::ajouter()
{
    QSqlQuery queryId;
    if (!queryId.exec("SELECT NVL(MAX(ID_conteneur),0)+1 FROM CONTENEURS"))
        return false;
    if (queryId.next()) m_id = queryId.value(0).toInt();

    QSqlQuery query;
    query.prepare(
        "INSERT INTO CONTENEURS (ID_conteneur, Capacite, Type_propriete, "
        "Adresse_complete, Localisation_GPS, Accepte_menager, Accepte_recyclable, "
        "Accepte_organique, Accepte_industriel, Etat, Date_derniere_collecte) "
        "VALUES (:id, :cap, :tprop, :adr, :gps, :men, :rec, :org, :ind, "
        ":etat, TO_DATE(:date,'DD/MM/YYYY'))"
        );
    query.bindValue(":id",    m_id);
    query.bindValue(":cap",   m_capacite);
    query.bindValue(":tprop", m_typePropriete);
    query.bindValue(":adr",   m_adresseComplete);
    query.bindValue(":gps",   m_localisationGPS);
    query.bindValue(":men",   m_accepteMenager);
    query.bindValue(":rec",   m_accepteRecyclable);
    query.bindValue(":org",   m_accepteOrganique);
    query.bindValue(":ind",   m_accepteIndustriel);
    query.bindValue(":etat",  m_etat);
    query.bindValue(":date",  m_dateDerniereCollecte);
    if (!query.exec()) {
        qDebug() << "Conteneur::ajouter error:" << query.lastError().text();
        return false;
    }
    return true;
}

// ============================================================
// CRUD — modifier
// ============================================================
bool Conteneur::modifier()
{
    QSqlQuery query;
    query.prepare(
        "UPDATE CONTENEURS SET "
        "Capacite=:cap, Type_propriete=:tprop, Adresse_complete=:adr, "
        "Localisation_GPS=:gps, Accepte_menager=:men, Accepte_recyclable=:rec, "
        "Accepte_organique=:org, Accepte_industriel=:ind, Etat=:etat, "
        "Date_derniere_collecte=TO_DATE(:date,'DD/MM/YYYY') "
        "WHERE ID_conteneur=:id"
        );
    query.bindValue(":cap",   m_capacite);
    query.bindValue(":tprop", m_typePropriete);
    query.bindValue(":adr",   m_adresseComplete);
    query.bindValue(":gps",   m_localisationGPS);
    query.bindValue(":men",   m_accepteMenager);
    query.bindValue(":rec",   m_accepteRecyclable);
    query.bindValue(":org",   m_accepteOrganique);
    query.bindValue(":ind",   m_accepteIndustriel);
    query.bindValue(":etat",  m_etat);
    query.bindValue(":date",  m_dateDerniereCollecte);
    query.bindValue(":id",    m_id);
    if (!query.exec()) {
        qDebug() << "Conteneur::modifier error:" << query.lastError().text();
        return false;
    }
    return true;
}

// ============================================================
// CRUD — supprimer
// ============================================================
bool Conteneur::supprimer(int id)
{
    QSqlQuery query;
    query.prepare("DELETE FROM CONTENEURS WHERE ID_conteneur = :id");
    query.bindValue(":id", id);
    if (!query.exec()) {
        qDebug() << "Conteneur::supprimer error:" << query.lastError().text();
        return false;
    }
    return true;
}

// ============================================================
// CRUD — getAll
// ============================================================
QList<Conteneur> Conteneur::getAll()
{
    QList<Conteneur> liste;
    QSqlQuery query;
    if (!query.exec(
            "SELECT ID_conteneur, Capacite, Type_propriete, Adresse_complete, "
            "Localisation_GPS, Accepte_menager, Accepte_recyclable, "
            "Accepte_organique, Accepte_industriel, Etat, "
            "TO_CHAR(Date_derniere_collecte,'DD/MM/YYYY') "
            "FROM CONTENEURS ORDER BY ID_conteneur"))
        return liste;

    while (query.next()) {
        Conteneur c(
            query.value(0).toInt(),
            query.value(1).toDouble(),
            query.value(2).toString(),
            query.value(3).toString(),
            query.value(4).toString(),
            query.value(5).toString(),
            query.value(6).toString(),
            query.value(7).toString(),
            query.value(8).toString(),
            query.value(9).toString(),
            query.value(10).toString()
            );
        liste.append(c);
    }
    return liste;
}

// ============================================================
// CRUD — getById
// ============================================================
Conteneur Conteneur::getById(int id)
{
    QSqlQuery query;
    query.prepare(
        "SELECT ID_conteneur, Capacite, Type_propriete, Adresse_complete, "
        "Localisation_GPS, Accepte_menager, Accepte_recyclable, "
        "Accepte_organique, Accepte_industriel, Etat, "
        "TO_CHAR(Date_derniere_collecte,'DD/MM/YYYY') "
        "FROM CONTENEURS WHERE ID_conteneur = :id"
        );
    query.bindValue(":id", id);
    if (query.exec() && query.next()) {
        return Conteneur(
            query.value(0).toInt(),
            query.value(1).toDouble(),
            query.value(2).toString(),
            query.value(3).toString(),
            query.value(4).toString(),
            query.value(5).toString(),
            query.value(6).toString(),
            query.value(7).toString(),
            query.value(8).toString(),
            query.value(9).toString(),
            query.value(10).toString()
            );
    }
    return Conteneur();
}

// ============================================================
// Vérification FK — Architecture Modèle-Vue
// ============================================================
int Conteneur::compterLiensConsommer(int id)
{
    QSqlQuery q;
    q.prepare("SELECT COUNT(*) FROM CONSOMMER WHERE ID_conteneur = :id");
    q.bindValue(":id", id);
    if (q.exec() && q.next()) return q.value(0).toInt();
    return 0;
}

// ============================================================
// Recherche dans QTableWidget
// ============================================================
void Conteneur::rechercherDansTable(QTableWidget *table, const QString &text)
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
void Conteneur::loadConteneursIntoTable(QTableWidget *table,
                                        const QString &orderBy,
                                        const QString &filterEtat)
{
    QStringList allowed = {"ID_conteneur", "Capacite", "Type_propriete",
                           "Adresse_complete", "Etat"};
    QString safeOrder = "ID_conteneur";
    for (const QString &col : allowed)
        if (col.compare(orderBy, Qt::CaseInsensitive) == 0) { safeOrder = col; break; }

    QString whereClause;
    if (!filterEtat.isEmpty())
        whereClause = "WHERE UPPER(Etat) = UPPER('" + filterEtat + "')";

    QString queryStr = QString(
                           "SELECT ID_conteneur, Capacite, Type_propriete, Adresse_complete, "
                           "Localisation_GPS, Accepte_menager, Accepte_recyclable, "
                           "Accepte_organique, Accepte_industriel, Etat, "
                           "TO_CHAR(Date_derniere_collecte,'DD/MM/YYYY') "
                           "FROM CONTENEURS %1 ORDER BY %2"
                           ).arg(whereClause, safeOrder);

    QSqlQuery q;
    q.exec(queryStr);

    table->setSortingEnabled(false);
    table->clearContents();
    table->setRowCount(0);

    int row = 0;
    while (q.next()) {
        table->insertRow(row);
        for (int col = 0; col < 11; col++)
            table->setItem(row, col, new QTableWidgetItem(q.value(col).toString()));
        table->setColumnHidden(0, true);
        row++;
    }
    table->setSortingEnabled(true);
}

// ============================================================
// Export liste PDF / Word
// ============================================================
void Conteneur::exporterListe(QTableWidget *table)
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
    html += "<h2>Liste des Conteneurs</h2>";
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
                             "La liste des conteneurs a été exportée avec succès.");
}

// ============================================================
// Statistiques
// ============================================================
void Conteneur::afficherStatistiques(QWidget *parent)
{
    QSqlQuery q;

    int total = 0;
    if (q.exec("SELECT COUNT(*) FROM CONTENEURS") && q.next())
        total = q.value(0).toInt();

    auto countEtat = [&](const QString &etat) -> int {
        q.prepare("SELECT COUNT(*) FROM CONTENEURS WHERE UPPER(Etat)=UPPER(:e)");
        q.bindValue(":e", etat);
        if (q.exec() && q.next()) return q.value(0).toInt();
        return 0;
    };
    int operationnels = countEtat("Opérationnel");
    int enMaintenance = countEtat("En maintenance");
    int horsService   = countEtat("Hors service");

    double capMoy = 0, capMax = 0, capMin = 0;
    if (q.exec("SELECT AVG(Capacite), MAX(Capacite), MIN(Capacite) FROM CONTENEURS") && q.next()) {
        capMoy = q.value(0).toDouble();
        capMax = q.value(1).toDouble();
        capMin = q.value(2).toDouble();
    }

    auto countOui = [&](const QString &col) -> int {
        if (q.exec(QString("SELECT COUNT(*) FROM CONTENEURS WHERE UPPER(%1)='OUI'").arg(col)) && q.next())
            return q.value(0).toInt();
        return 0;
    };
    int menager    = countOui("ACCEPTE_MENAGER");
    int recyclable = countOui("ACCEPTE_RECYCLABLE");
    int organique  = countOui("ACCEPTE_ORGANIQUE");
    int industriel = countOui("ACCEPTE_INDUSTRIEL");

    QDialog *dlg = new QDialog(parent);
    dlg->setWindowTitle("📊 Statistiques des Conteneurs");
    dlg->setFixedSize(780, 680);
    dlg->setStyleSheet("QDialog { background-color: #F0F4F8; }");

    QVBoxLayout *mainLay = new QVBoxLayout(dlg);
    mainLay->setContentsMargins(20, 20, 20, 20);
    mainLay->setSpacing(16);

    QLabel *title = new QLabel("📊 Tableau de Bord — Statistiques Conteneurs");
    title->setAlignment(Qt::AlignCenter);
    title->setStyleSheet(
        "font-size:18px; font-weight:bold; color:white; padding:16px;"
        "background:qlineargradient(x1:0,y1:0,x2:1,y2:0,stop:0 #1B3A57,stop:1 #2C5F7C);"
        "border-radius:12px;");
    mainLay->addWidget(title);

    QHBoxLayout *kpiRow = new QHBoxLayout();
    kpiRow->setSpacing(12);
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
    kpiRow->addWidget(makeKPI("🗑️", QString::number(total),         "Total conteneurs", "#2C5F7C"));
    kpiRow->addWidget(makeKPI("✅", QString::number(operationnels), "Opérationnels",    "#27AE60"));
    kpiRow->addWidget(makeKPI("🔧", QString::number(enMaintenance), "En maintenance",   "#E67E22"));
    kpiRow->addWidget(makeKPI("❌", QString::number(horsService),   "Hors service",     "#E74C3C"));
    mainLay->addLayout(kpiRow);

    QFrame *capCard = new QFrame();
    capCard->setStyleSheet("QFrame { background:white; border-radius:12px; }");
    QHBoxLayout *capLay = new QHBoxLayout(capCard);
    capLay->setContentsMargins(20,14,20,14);
    auto makeStat = [](const QString &lbl, const QString &val) {
        QVBoxLayout *vl = new QVBoxLayout();
        QLabel *v = new QLabel(val); v->setAlignment(Qt::AlignCenter);
        v->setStyleSheet("font-size:20px; font-weight:bold; color:#2C5F7C;");
        QLabel *l = new QLabel(lbl); l->setAlignment(Qt::AlignCenter);
        l->setStyleSheet("font-size:11px; color:#6B7280;");
        vl->addWidget(v); vl->addWidget(l); return vl;
    };
    capLay->addLayout(makeStat("Moyenne (L)", QString::number(capMoy,'f',0)));
    capLay->addSpacing(30);
    capLay->addLayout(makeStat("Maximum (L)", QString::number(capMax,'f',0)));
    capLay->addSpacing(30);
    capLay->addLayout(makeStat("Minimum (L)", QString::number(capMin,'f',0)));
    mainLay->addWidget(capCard);

    QFrame *dechetCard = new QFrame();
    dechetCard->setStyleSheet("QFrame { background:white; border-radius:12px; }");
    QVBoxLayout *dechetLay = new QVBoxLayout(dechetCard);
    dechetLay->setContentsMargins(20,14,20,14); dechetLay->setSpacing(10);
    QLabel *dechetTitle = new QLabel("♻️ Types de Déchets Acceptés");
    dechetTitle->setStyleSheet("font-size:13px; font-weight:bold; color:#374151;");
    dechetLay->addWidget(dechetTitle);

    struct DechetStat { QString name; int count; QString color; };
    QList<DechetStat> dechets = {
                                 {"Ménager",    menager,    "#3B82F6"},
                                 {"Recyclable", recyclable, "#10B981"},
                                 {"Organique",  organique,  "#F59E0B"},
                                 {"Industriel", industriel, "#EF4444"},
                                 };
    for (auto &d : dechets) {
        QHBoxLayout *row = new QHBoxLayout();
        QLabel *nameLbl = new QLabel(d.name); nameLbl->setFixedWidth(90);
        nameLbl->setStyleSheet("font-size:12px; color:#374151;");
        QProgressBar *bar = new QProgressBar();
        bar->setRange(0, total > 0 ? total : 1); bar->setValue(d.count);
        bar->setTextVisible(false); bar->setFixedHeight(16);
        bar->setStyleSheet(QString(
                               "QProgressBar{background:#E5E7EB;border-radius:8px;}"
                               "QProgressBar::chunk{background:%1;border-radius:8px;}").arg(d.color));
        QLabel *numLbl = new QLabel(QString::number(d.count) + " / " + QString::number(total));
        numLbl->setFixedWidth(70); numLbl->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
        numLbl->setStyleSheet("font-size:11px; color:#6B7280;");
        row->addWidget(nameLbl); row->addWidget(bar); row->addWidget(numLbl);
        dechetLay->addLayout(row);
    }
    mainLay->addWidget(dechetCard);

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
