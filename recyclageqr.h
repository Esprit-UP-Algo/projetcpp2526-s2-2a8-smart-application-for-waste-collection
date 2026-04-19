#ifndef RECYCLAGEQR_H
#define RECYCLAGEQR_H

#include "recyclage.h"
#include <QDialog>
#include <QLabel>
#include <QPushButton>
#include <QLineEdit>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QString>
#include <QDir>

// ============================================================
//  RecyclageQR — Génère HTML + QR code pour un recyclage
// ============================================================
class RecyclageQR : public QObject
{
    Q_OBJECT

public:
    // ── Configuration ──────────────────────────────────────────
    // Mettez ici l'URL de base de votre site Netlify
    // Exemple : "https://mon-recyclage.netlify.app"
    static const QString NETLIFY_BASE_URL;

    // Dossier local où les pages HTML seront sauvegardées
    // (vous uploadez ce dossier sur Netlify)
    static const QString HTML_OUTPUT_DIR;

    // ── API principale ─────────────────────────────────────────

    // Génère le fichier HTML pour ce recyclage
    // Retourne le chemin du fichier créé
    static QString genererPageHTML(const Recyclage &r);

    // Retourne l'URL publique Netlify pour ce recyclage
    static QString getUrlPublique(int id);

    // Retourne l'URL de l'image QR code (via API qrserver.com)
    static QString getQRCodeImageUrl(int id);

    // Ouvre le dialog QR complet
    static void afficherDialogQR(const Recyclage &r, QWidget *parent = nullptr);
};


// ============================================================
//  RecyclageQRDialog — Fenêtre qui affiche le QR + lien
// ============================================================
class RecyclageQRDialog : public QDialog
{
    Q_OBJECT

public:
    explicit RecyclageQRDialog(const Recyclage &r, QWidget *parent = nullptr);

private slots:
    void onQRCodeDownloaded(QNetworkReply *reply);
    void ouvrirDansNavigateur();
    void copierLien();
    void exporterHTML();

private:
    void setupUI();
    void chargerQRCode();

    Recyclage          m_recyclage;
    QString            m_urlPublique;

    QLabel            *m_qrLabel;
    QLabel            *m_statusLabel;
    QLineEdit         *m_lienEdit;
    QPushButton       *m_btnOuvrir;
    QPushButton       *m_btnCopier;
    QPushButton       *m_btnExporter;
    QPushButton       *m_btnFermer;

    QNetworkAccessManager *m_nam;
};

#endif // RECYCLAGEQR_H
