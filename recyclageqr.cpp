#include "recyclageqr.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QLabel>
#include <QPushButton>
#include <QLineEdit>
#include <QFrame>
#include <QPixmap>
#include <QDesktopServices>
#include <QUrl>
#include <QClipboard>
#include <QApplication>
#include <QMessageBox>
#include <QFile>
#include <QTextStream>
#include <QDir>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QDebug>
#include <cmath>

// ============================================================
//  ⚙️  CONFIGURATION — À MODIFIER PAR L'UTILISATEUR
// ============================================================

// 1. Mettez l'URL de votre site Netlify ici
const QString RecyclageQR::NETLIFY_BASE_URL =
    "https://recyclage-app-amenallah.netlify.app";

// 2. Dossier où les pages HTML seront sauvegardées
//    (créez ce dossier et uploadez-le sur Netlify)
const QString RecyclageQR::HTML_OUTPUT_DIR = "C:/recyclage_pages";

// ============================================================
//  Génère l'URL publique Netlify pour un recyclage donné
// ============================================================
QString RecyclageQR::getUrlPublique(int id)
{
    return NETLIFY_BASE_URL + QString("/recyclage_%1.html").arg(id);
}

// ============================================================
//  Génère l'URL de l'image QR code via qrserver.com (API gratuite)
// ============================================================
QString RecyclageQR::getQRCodeImageUrl(int id)
{
    // qrserver.com : API publique, pas de clé nécessaire
    // Paramètres : size=200x200, couleur verte, format PNG
    QString url = NETLIFY_BASE_URL +
                  "/recyclage_" + QString::number(id) + ".html";
    QString encoded = QUrl::toPercentEncoding(url);
    return QString("https://api.qrserver.com/v1/create-qr-code/"
                   "?size=200x200&color=1B3A57&bgcolor=F0F9FF&data=%1")
        .arg(QString(encoded));
}

// ============================================================
//  Génère la page HTML complète pour un recyclage
// ============================================================
QString RecyclageQR::genererPageHTML(const Recyclage &r)
{
    double taux = 0.0;
    if (r.getQuantiteEntree() > 0)
        taux = (r.getQuantiteRecyclee() / r.getQuantiteEntree()) * 100.0;

    QString couleurStatut = "#6B7280";
    QString iconStatut    = "⏸";

    QString statut = r.getStatut().toLower();

    if (statut == "terminé")        { couleurStatut = "#10B981"; iconStatut = "✅"; }
    else if (statut == "en cours")  { couleurStatut = "#F59E0B"; iconStatut = "🔄"; }
    else if (statut == "annulé")    { couleurStatut = "#EF4444"; iconStatut = "❌"; }
    else if (statut == "en attente"){ couleurStatut = "#3B82F6"; iconStatut = "⏳"; }

    QString couleurTaux = "#EF4444";
    if (taux >= 80) couleurTaux = "#10B981";
    else if (taux >= 50) couleurTaux = "#F59E0B";

    QString html;

    html += "<!DOCTYPE html><html><head><meta charset='UTF-8'>";
    html += "<title>Recyclage</title>";

    html += "<style>";
    html += "body{font-family:Arial;background:#0F2744;color:white;padding:20px;}";
    html += ".card{background:white;color:black;padding:20px;border-radius:12px;max-width:600px;margin:auto;}";
    html += ".statut{background:" + couleurStatut + ";color:white;padding:10px;border-radius:8px;}";
    html += "</style>";

    html += "</head><body>";

    html += "<div class='card'>";
    html += "<h2>♻ Recyclage #" + QString::number(r.getId()) + "</h2>";

    html += "<p><b>Date :</b> " + r.getDateTri() + "</p>";
    html += "<p><b>Type :</b> " + r.getTypeMateriau() + "</p>";

    html += "<div class='statut'>";
    html += iconStatut + " " + r.getStatut();
    html += "</div>";

    html += "<p><b>Quantité entrée :</b> " + QString::number(r.getQuantiteEntree()) + "</p>";
    html += "<p><b>Quantité recyclée :</b> " + QString::number(r.getQuantiteRecyclee()) + "</p>";
    html += "<p><b>Quantité rejetée :</b> " + QString::number(r.getQuantiteRejetee()) + "</p>";

    html += "<p><b>Destination :</b> " + r.getDestination() + "</p>";
    html += "<p><b>Direction :</b> " + r.getDirection() + "</p>";

    html += "<h3 style='color:" + couleurTaux + "'>Taux : " + QString::number(taux, 'f', 1) + "%</h3>";

    html += "</div></body></html>";

    // ── Sauvegarde ─────────────────────
    QDir().mkpath(RecyclageQR::HTML_OUTPUT_DIR);

    QString filePath = RecyclageQR::HTML_OUTPUT_DIR +
                       QString("/recyclage_%1.html").arg(r.getId());

    QFile file(filePath);
    if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QTextStream out(&file);
        out << html;
        file.close();
        qDebug() << "✅ HTML OK :" << filePath;
    }

    return html;  // ✅ IMPORTANT
}
// ============================================================
//  Ouvre directement le dialog QR
// ============================================================
void RecyclageQR::afficherDialogQR(const Recyclage &r, QWidget *parent)
{
    RecyclageQRDialog *dlg = new RecyclageQRDialog(r, parent);
    dlg->setAttribute(Qt::WA_DeleteOnClose);
    dlg->exec();
}


// ============================================================
//  RecyclageQRDialog — Implémentation
// ============================================================
RecyclageQRDialog::RecyclageQRDialog(const Recyclage &r, QWidget *parent)
    : QDialog(parent), m_recyclage(r)
{
    m_urlPublique = RecyclageQR::getUrlPublique(r.getId());
    m_nam         = new QNetworkAccessManager(this);

    setWindowTitle(QString("QR Code — Lot #%1").arg(r.getId()));
    setFixedSize(480, 600);

    setupUI();
    chargerQRCode();
}

void RecyclageQRDialog::setupUI()
{
    // ── Style global du dialog ───────────────────────────────
    setStyleSheet(R"(
        QDialog {
            background: #F0F4F8;
        }
        QLabel {
            color: #334155;
        }
        QLineEdit {
            background: white;
            border: 1px solid #CBD5E1;
            border-radius: 8px;
            padding: 8px 12px;
            font-size: 12px;
            color: #1B3A57;
            font-family: 'Courier New', monospace;
            selection-background-color: #1B3A57;
        }
        QPushButton {
            border: none;
            border-radius: 8px;
            padding: 10px 18px;
            font-size: 13px;
            font-weight: 600;
            cursor: pointer;
        }
    )");

    QVBoxLayout *mainLay = new QVBoxLayout(this);
    mainLay->setContentsMargins(24, 24, 24, 24);
    mainLay->setSpacing(16);

    // ── Titre ────────────────────────────────────────────────
    QLabel *titleLbl = new QLabel(
        QString("🔷  QR Code — Lot #%1").arg(m_recyclage.getId()));
    titleLbl->setAlignment(Qt::AlignCenter);
    titleLbl->setStyleSheet(
        "font-size:18px; font-weight:700; color:white; padding:14px;"
        "background:qlineargradient(x1:0,y1:0,x2:1,y2:0,"
        "stop:0 #0F2744,stop:1 #2C7A6C);"
        "border-radius:12px;");
    mainLay->addWidget(titleLbl);

    // ── Info rapide ──────────────────────────────────────────
    QLabel *infoLbl = new QLabel(
        QString("📦  %1  ·  %2  ·  %3")
            .arg(m_recyclage.getTypeMateriau(),
                 m_recyclage.getDateTri(),
                 m_recyclage.getStatut()));
    infoLbl->setAlignment(Qt::AlignCenter);
    infoLbl->setStyleSheet(
        "color:#475569; font-size:13px; background:white;"
        "border-radius:8px; padding:8px;");
    mainLay->addWidget(infoLbl);

    // ── Zone QR code ─────────────────────────────────────────
    QFrame *qrFrame = new QFrame();
    qrFrame->setStyleSheet(
        "QFrame { background:white; border-radius:14px; "
        "border: 2px solid #E2E8F0; }");
    qrFrame->setFixedHeight(240);

    QVBoxLayout *qrLay = new QVBoxLayout(qrFrame);
    qrLay->setAlignment(Qt::AlignCenter);

    m_qrLabel = new QLabel("⏳  Chargement du QR code...");
    m_qrLabel->setAlignment(Qt::AlignCenter);
    m_qrLabel->setStyleSheet("font-size:13px; color:#94A3B8; border:none;");
    m_qrLabel->setFixedSize(210, 210);
    qrLay->addWidget(m_qrLabel, 0, Qt::AlignCenter);

    mainLay->addWidget(qrFrame);

    // ── Statut du chargement ─────────────────────────────────
    m_statusLabel = new QLabel("📡  Connexion à l'API QR code...");
    m_statusLabel->setAlignment(Qt::AlignCenter);
    m_statusLabel->setStyleSheet("font-size:11px; color:#94A3B8;");
    mainLay->addWidget(m_statusLabel);

    // ── Lien Netlify ─────────────────────────────────────────
    QLabel *lienLbl = new QLabel("🔗  Lien public :");
    lienLbl->setStyleSheet("font-size:12px; font-weight:600; color:#475569;");
    mainLay->addWidget(lienLbl);

    m_lienEdit = new QLineEdit(m_urlPublique);
    m_lienEdit->setReadOnly(true);
    mainLay->addWidget(m_lienEdit);

    // ── Boutons ──────────────────────────────────────────────
    QHBoxLayout *btnLay = new QHBoxLayout();
    btnLay->setSpacing(10);

    m_btnOuvrir = new QPushButton("🌐  Ouvrir");
    m_btnOuvrir->setStyleSheet(
        "QPushButton{background:#1B3A57;color:white;}"
        "QPushButton:hover{background:#0F2744;}");

    m_btnCopier = new QPushButton("📋  Copier");
    m_btnCopier->setStyleSheet(
        "QPushButton{background:#2C7A6C;color:white;}"
        "QPushButton:hover{background:#1a5c50;}");

    m_btnExporter = new QPushButton("💾  Exporter HTML");
    m_btnExporter->setStyleSheet(
        "QPushButton{background:#F59E0B;color:white;}"
        "QPushButton:hover{background:#d97706;}");

    btnLay->addWidget(m_btnOuvrir);
    btnLay->addWidget(m_btnCopier);
    btnLay->addWidget(m_btnExporter);
    mainLay->addLayout(btnLay);

    m_btnFermer = new QPushButton("✕  Fermer");
    m_btnFermer->setStyleSheet(
        "QPushButton{background:#E2E8F0;color:#475569;}"
        "QPushButton:hover{background:#CBD5E1;}");
    mainLay->addWidget(m_btnFermer);

    // ── Connexions ───────────────────────────────────────────
    connect(m_btnOuvrir,   &QPushButton::clicked, this, &RecyclageQRDialog::ouvrirDansNavigateur);
    connect(m_btnCopier,   &QPushButton::clicked, this, &RecyclageQRDialog::copierLien);
    connect(m_btnExporter, &QPushButton::clicked, this, &RecyclageQRDialog::exporterHTML);
    connect(m_btnFermer,   &QPushButton::clicked, this, &QDialog::accept);
    connect(m_nam, &QNetworkAccessManager::finished,
            this, &RecyclageQRDialog::onQRCodeDownloaded);
}

// ── Télécharge le QR code depuis qrserver.com ────────────────
void RecyclageQRDialog::chargerQRCode()
{
    QString apiUrl = RecyclageQR::getQRCodeImageUrl(m_recyclage.getId());

    m_nam->get(QNetworkRequest(QUrl(apiUrl)));  // ✅ SOLUTION
}
// ── Reçoit et affiche l'image QR ─────────────────────────────
void RecyclageQRDialog::onQRCodeDownloaded(QNetworkReply *reply)
{
    reply->deleteLater();

    if (reply->error() != QNetworkReply::NoError) {
        m_qrLabel->setText("❌  Erreur réseau.\nVérifiez votre connexion.");
        m_statusLabel->setText("Erreur : " + reply->errorString());
        m_statusLabel->setStyleSheet("font-size:11px; color:#EF4444;");
        return;
    }

    QByteArray data = reply->readAll();
    QPixmap pixmap;
    if (pixmap.loadFromData(data, "PNG")) {
        m_qrLabel->setPixmap(
            pixmap.scaled(200, 200, Qt::KeepAspectRatio, Qt::SmoothTransformation));
        m_qrLabel->setText("");
        m_statusLabel->setText("✅  QR code prêt — Scannez pour accéder au lot");
        m_statusLabel->setStyleSheet("font-size:11px; color:#10B981;");
    } else {
        m_qrLabel->setText("❌  Impossible d'afficher l'image.");
        m_statusLabel->setStyleSheet("font-size:11px; color:#EF4444;");
    }
}

// ── Ouvre le lien dans le navigateur ─────────────────────────
void RecyclageQRDialog::ouvrirDansNavigateur()
{
    QDesktopServices::openUrl(QUrl(m_urlPublique));
}

// ── Copie le lien dans le presse-papier ──────────────────────
void RecyclageQRDialog::copierLien()
{
    QApplication::clipboard()->setText(m_urlPublique);
    m_statusLabel->setText("✅  Lien copié dans le presse-papiers !");
    m_statusLabel->setStyleSheet("font-size:11px; color:#10B981;");
}

// ── Génère et exporte la page HTML ───────────────────────────
void RecyclageQRDialog::exporterHTML()
{
    QString html = RecyclageQR::genererPageHTML(m_recyclage);
    qDebug() << "HTML = " << html;

    QString filePath = "C:/recyclage_pages/recyclage_"
                       + QString::number(m_recyclage.getId())
                       + ".html";

    QFile file(filePath);

    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QMessageBox::critical(this, "Erreur", "Impossible de créer le fichier !");
        return;
    }

    QTextStream out(&file);
    out << html;

    file.close();

    QMessageBox::information(this, "Succès", "HTML généré ici:\n" + filePath);
}
