#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "employe.h"
#include "client.h"
#include "recyclage.h"
#include "collecte.h"
#include "conteneur.h"
#include "smsclient.h"
#include "classificationdechet.h"
#include <QMenu>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:

    // ================================================================
    // === SLOTS GÉNÉRAUX (NAVIGATION ENTRE PAGES) ====================
    // ================================================================
    void on_mdp_clicked();
    void on_cnx_clicked();
    void on_retour_clicked();
    void on_acceuil_clicked();
    void on_deconnection_clicked();
    void on_recyclage_clicked();
    void on_CONTENEUR_clicked();
    void on_TOURNEE_clicked();
    void on_pushButton_44_clicked();
    void on_pushButton_16_clicked();
    void on_pushButton_30_clicked();
    void on_frame_20_customContextMenuRequested(const QPoint &pos);

    // ================================================================
    // === MODULE CLIENT ==============================================
    // ================================================================
    void on_pushButton_36_clicked();
    void on_pushButton_37_clicked();
    void on_pushButton_rechercher_3_clicked();
    void on_conn_clicked();
    void on_dec_clicked();

    void on_btntrie_clicked();
    void on_barrerechercheclient_textChanged(const QString &text);
    void on_bouttonajouterclient_clicked();
    void on_bouttonmodifierclient_clicked();
    void on_bouttonsupprimerclient_clicked();
    void on_bouttonexporterclient_clicked();
    void on_bouttonstatclient_clicked();
    void on_btnsms_clicked();

    // ================================================================
    // === MODULE EMPLOYE =============================================
    // ================================================================
    void on_bouttonajouteremp_clicked();
    void on_bouttonmodifieremp_clicked();
    void on_bouttonsupprimeremp_clicked();
    void on_btntrieemp_clicked();
    void on_barrerechercheemp_textChanged(const QString &text);
    void on_bouttonrechercheemp_clicked();
    void on_bouttonexporteremp_clicked();
    void on_bouttonstatemp_clicked();

    // ================================================================
    // === MODULE RECYCLAGE ===========================================
    // ================================================================
    void on_bouttonajouterrecyclage_clicked();
    void on_bouttonmodifierrecyclage_clicked();
    void on_bouttonsupprimerrecyclage_clicked();
    void on_bttntrirecyclage_clicked();
    void on_barrerechercherecyclage_textChanged(const QString &text);
    void on_bouttonexporterrecyclage_clicked();
    void on_bouttonstatrecyclage_clicked();
    void on_bouttonqrrecyclage_clicked();
    void on_btnClassifier_clicked();

    // ================================================================
    // === MODULE COLLECTE ============================================
    // ================================================================
    void on_pushButton_66_clicked();
    void on_bouttonmodifiercollecte_clicked();
    void on_bouttonsupprimercollecte_clicked();
    void on_bttntricollecte_clicked();
    void on_barrerecherchecollecte_textChanged(const QString &text);
    void on_bouttonexportercollecte_clicked();
    void on_bouttonstatcollecte_clicked();

    // ================================================================
    // === MODULE CONTENEUR ===========================================
    // ================================================================
    void on_bouttonajouterconteneur_clicked();
    void on_bouttonmodifierconteneur_clicked();
    void on_bouttonsupprimerconteneur_clicked();
    void on_btntriconteneur_clicked();
    void on_barrerechercheconteneur_textChanged(const QString &text);
    void on_bouttonexporterconteneur_clicked();
    void on_bouttonstatconteneur_clicked();

    // ================================================================
    // === MODULE TOURNEE =============================================
    // ================================================================
    void on_pushButton_38_clicked();
    void on_pushButton_35_clicked();

private:
    Ui::MainWindow *ui;

    // ── Client ──────────────────────────────────────────────────────
    void afficherListeClients();
    void afficherWidgetAjoutClient();
    void afficherWidgetModifierClient(Client client);
    void exporterClientsCSV();
    void afficherStatistiquesClients();
    Client getClientSelectionne();
    SmsClientMetier *sms;

    // ── Employe ─────────────────────────────────────────────────────
    void afficherEmployes();
    void afficherWidgetAjoutEmploye();
    void afficherWidgetModifierEmploye();
    void exporterEmployesCSV();
    void afficherStatistiquesEmployes();
    Employe getEmployeSelectionne();

    // ── Recyclage ───────────────────────────────────────────────────
    void afficherRecyclages();
    void afficherWidgetAjoutRecyclage();
    void afficherWidgetModifierRecyclage(int idRecyclage);
    void lancerClassification();
    Recyclage getRecyclageSelectionne();

    // ── Collecte ────────────────────────────────────────────────────
    void afficherCollectes();
    void afficherWidgetAjoutCollecte();
    void afficherWidgetModifierCollecte(int idCollecte);
    Collecte getCollecteSelectionnee();

    // ── Conteneur ───────────────────────────────────────────────────
    void afficherConteneurs();
    void afficherWidgetAjoutConteneur();
    void afficherWidgetModifierConteneur(int idConteneur);
    Conteneur getConteneurSelectionne();

    // ── Utilitaires ─────────────────────────────────────────────────
    void showMessage(QWidget *parent, const QString &titre,
                     const QString &message, const QString &type = "info");
};

#endif // MAINWINDOW_H
