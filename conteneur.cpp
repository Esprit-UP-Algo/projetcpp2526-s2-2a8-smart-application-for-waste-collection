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

#include <QtCharts/QChartView>
#include <QtCharts/QPieSeries>
#include <QtCharts/QChart>
#include <QtCharts/QPieSlice>

void Conteneur::afficherStatistiques(QWidget *parent)
{
    QSqlQuery q;

    // ── Comptage par état ────────────────────────────────────────
    auto countEtat = [&](const QString &etat) -> int {
        q.prepare("SELECT COUNT(*) FROM CONTENEURS WHERE UPPER(Etat)=UPPER(:e)");
        q.bindValue(":e", etat);
        if (q.exec() && q.next()) return q.value(0).toInt();
        return 0;
    };

    int operationnels = countEtat("Opérationnel");
    int enMaintenance = countEtat("En maintenance");
    int horsService   = countEtat("Hors service");

    // Autres états non couverts
    q.prepare(
        "SELECT COUNT(*) FROM CONTENEURS WHERE Etat IS NOT NULL AND "
        "UPPER(Etat) NOT IN ('OPÉRATIONNEL','EN MAINTENANCE','HORS SERVICE')"
        );
    int autre = (q.exec() && q.next()) ? q.value(0).toInt() : 0;

    int total = operationnels + enMaintenance + horsService + autre;
    if (total == 0) total = 1;

    // ── Dialogue ─────────────────────────────────────────────────
    QDialog *dlg = new QDialog(parent);
    dlg->setWindowTitle("📊 Statistiques des Conteneurs");
    dlg->setFixedSize(780, 680);
    dlg->setStyleSheet("QDialog { background-color: #F0F4F8; }");

    QVBoxLayout *mainLay = new QVBoxLayout(dlg);
    mainLay->setContentsMargins(20, 20, 20, 20);
    mainLay->setSpacing(16);

    // ── Titre ────────────────────────────────────────────────────
    QLabel *title = new QLabel("📊 Répartition des Conteneurs par État");
    title->setAlignment(Qt::AlignCenter);
    title->setStyleSheet(
        "font-size:18px; font-weight:bold; color:white; padding:16px;"
        "background:qlineargradient(x1:0,y1:0,x2:1,y2:0,stop:0 #1B3A57,stop:1 #2C5F7C);"
        "border-radius:12px;"
        );
    mainLay->addWidget(title);

    // ── Pie Series ───────────────────────────────────────────────
    QPieSeries *series = new QPieSeries();

    QPieSlice *s1 = series->append("Opérationnel",  operationnels);
    QPieSlice *s2 = series->append("En maintenance", enMaintenance);
    QPieSlice *s3 = series->append("Hors service",   horsService);
    QPieSlice *s4 = series->append("Autre",          autre);

    s1->setBrush(QColor("#27AE60"));   // vert
    s2->setBrush(QColor("#E67E22"));   // orange
    s3->setBrush(QColor("#E74C3C"));   // rouge
    s4->setBrush(QColor("#9CA3AF"));   // gris

    s1->setLabel(QString("Opérationnel %1%")
                     .arg((operationnels * 100.0) / total, 0, 'f', 1));
    s2->setLabel(QString("En maintenance %1%")
                     .arg((enMaintenance * 100.0) / total, 0, 'f', 1));
    s3->setLabel(QString("Hors service %1%")
                     .arg((horsService   * 100.0) / total, 0, 'f', 1));
    s4->setLabel(QString("Autre %1%")
                     .arg((autre         * 100.0) / total, 0, 'f', 1));

    s1->setLabelVisible(true);
    s2->setLabelVisible(true);
    s3->setLabelVisible(true);
    s4->setLabelVisible(true);

    // Hover → explode (comme Employe)
    QObject::connect(s1, &QPieSlice::hovered, [=](bool state){ s1->setExploded(state); });
    QObject::connect(s2, &QPieSlice::hovered, [=](bool state){ s2->setExploded(state); });
    QObject::connect(s3, &QPieSlice::hovered, [=](bool state){ s3->setExploded(state); });
    QObject::connect(s4, &QPieSlice::hovered, [=](bool state){ s4->setExploded(state); });

    // ── Chart ────────────────────────────────────────────────────
    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->setTitle("Répartition par état");
    chart->legend()->setAlignment(Qt::AlignBottom);
    chart->setAnimationOptions(QChart::SeriesAnimations);

    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);
    chartView->setStyleSheet("background:transparent;");

    mainLay->addWidget(chartView);

    // ── Bouton Fermer ────────────────────────────────────────────
    QPushButton *closeBtn = new QPushButton("✕  Fermer");
    closeBtn->setFixedHeight(42);
    closeBtn->setStyleSheet(
        "QPushButton{background:#2C5F7C;color:white;font-size:14px;font-weight:600;"
        "border:none;border-radius:8px;}"
        "QPushButton:hover{background:#1B3A57;}"
        );
    QObject::connect(closeBtn, &QPushButton::clicked, dlg, &QDialog::accept);
    mainLay->addWidget(closeBtn);

    dlg->exec();
}
