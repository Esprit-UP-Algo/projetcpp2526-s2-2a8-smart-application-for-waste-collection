#include "exporter.h"

#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QDate>
#include <QDialog>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QTextEdit>
#include <QPushButton>
#include <QFileDialog>
#include <QTextDocument>
#include <QPrinter>
#include <QMessageBox>

// ================================================================
// === MODULE EMPLOYE — MARYEM ====================================
// ================================================================

QString EmployeExporter::construireHTML()
{
    QSqlQuery query;
    if (!query.exec(
            "SELECT CIN, Nom, Prenom, Email, Poste, Telephone, "
            "Date_embauche, Salaire, Service FROM EMPLOYES ORDER BY Nom"))
    {
        qDebug() << "[EmployeExporter::construireHTML] Erreur SQL:" << query.lastError().text();
        return QString();
    }

    QString html;
    html += "<html><head><meta charset='utf-8'><style>"
            "body { font-family:Arial,sans-serif; font-size:12px; }"
            "h1   { text-align:center; color:#2C5F7C; }"
            "p    { text-align:center; color:#555; }"
            "table { width:100%; border-collapse:collapse; margin-top:20px; }"
            "th { background-color:#2C5F7C; color:white; padding:8px; text-align:left; }"
            "td { border:1px solid #ddd; padding:6px; }"
            "tr:nth-child(even) { background-color:#f2f2f2; }"
            "</style></head><body>";

    html += "<h1>Liste des Employés</h1>";
    html += "<p>Exporté le : " + QDate::currentDate().toString("dd/MM/yyyy") + "</p>";
    html += "<table><tr>"
            "<th>CIN</th><th>Nom</th><th>Prénom</th><th>Email</th>"
            "<th>Poste</th><th>Téléphone</th><th>Date Embauche</th>"
            "<th>Salaire (DT)</th><th>Service</th></tr>";

    while (query.next()) {
        html += "<tr>";
        for (int col = 0; col < 9; col++)
            html += "<td>" + query.value(col).toString().toHtmlEscaped() + "</td>";
        html += "</tr>";
    }
    html += "</table></body></html>";
    return html;
}

void EmployeExporter::exporterPDF(QWidget *parent)
{
    QString html = construireHTML();
    if (html.isEmpty()) {
        QMessageBox::critical(parent, "Erreur",
                              "Impossible de récupérer les données des employés.");
        return;
    }

    QDialog *dlg = new QDialog(parent);
    dlg->setWindowTitle("Export Employés — Aperçu PDF");
    dlg->setFixedSize(900, 600);

    QVBoxLayout *layout = new QVBoxLayout(dlg);

    QTextEdit *preview = new QTextEdit();
    preview->setReadOnly(true);
    preview->setHtml(html);
    layout->addWidget(preview);

    QHBoxLayout *btnL = new QHBoxLayout();

    QPushButton *btnImprimer = new QPushButton("🖨️  Imprimer / Enregistrer PDF");
    btnImprimer->setMinimumHeight(45);
    btnImprimer->setStyleSheet(
        "QPushButton { background:#2C5F7C; color:white; font-size:14px;"
        "font-weight:600; border:none; border-radius:8px; padding:10px 25px; }"
        "QPushButton:hover { background:#3A6EA5; }"
        );

    QPushButton *btnFermer = new QPushButton("Fermer");
    btnFermer->setMinimumHeight(45);
    btnFermer->setStyleSheet(
        "QPushButton { background:#E5E7EB; color:#374151; font-size:14px;"
        "font-weight:600; border:none; border-radius:8px; padding:10px 25px; }"
        "QPushButton:hover { background:#D1D5DB; }"
        );

    btnL->addWidget(btnFermer);
    btnL->addWidget(btnImprimer);
    layout->addLayout(btnL);

    QObject::connect(btnFermer, &QPushButton::clicked, dlg, &QDialog::reject);

    QObject::connect(btnImprimer, &QPushButton::clicked, dlg, [=]() {
        QString fichier = QFileDialog::getSaveFileName(
            dlg, "Enregistrer PDF", "employes_export.pdf", "PDF (*.pdf)");
        if (!fichier.isEmpty()) {
            QPrinter printer(QPrinter::HighResolution);
            printer.setOutputFormat(QPrinter::PdfFormat);
            printer.setOutputFileName(fichier);

            QTextDocument doc;
            doc.setHtml(html);
            doc.print(static_cast<QPagedPaintDevice*>(&printer));

            QMessageBox::information(dlg, "Succès", "✅ PDF enregistré avec succès !");
        }
    });

    dlg->exec();
}


// ================================================================
// === MODULE CLIENT — [NOM DU MEMBRE] ============================
// Implémenter ici ClientExporter::construireHTML() et exporterPDF()
// ================================================================


// ================================================================
// === MODULE CONTENEUR — [NOM DU MEMBRE] =========================
// Implémenter ici ConteneurExporter::construireHTML() et exporterPDF()
// ================================================================


// ================================================================
// === MODULE COLLECTE — [NOM DU MEMBRE] ==========================
// Implémenter ici CollecteExporter::construireHTML() et exporterPDF()
// ================================================================


// ================================================================
// === MODULE RECYCLAGE — [NOM DU MEMBRE] =========================
// Implémenter ici RecyclageExporter::construireHTML() et exporterPDF()
// ================================================================
