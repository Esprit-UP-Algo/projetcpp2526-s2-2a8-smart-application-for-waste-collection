#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "employe.h"
#include "client.h"
#include "recyclage.h"
#include "collecte.h"
#include "conteneur.h"
#include "smsclient.h"
#include <QMenu>
#include "map.h"
#include "parametres_employe.h"
#include "mdp_oublier.h"
#include "ai.h"
#include "predictionremplissage.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
protected:
    bool eventFilter(QObject *obj, QEvent *event) override;
    void keyPressEvent(QKeyEvent *event) override;

private slots:

    // ================================================================
    // === NAVIGATION =================================================
    // ================================================================
    void on_mdp_clicked();
    void on_cnx_clicked();
    void on_retour_clicked();
    void on_ACCEUIL_clicked();
    void on_DECONNECTION_clicked();
    void on_RECYCLAGE_clicked();
    void on_CONTENEUR_clicked();
    void on_COLLECTE_clicked();
    void on_EMPLOYE_clicked();
    void on_CLIENT_clicked();
    void on_mdp_oublier_clicked();
    void on_frame_20_customContextMenuRequested(const QPoint &pos);
    void on_btnClassifier_clicked();


    // ================================================================
    // === MODULE CLIENT ==============================================
    // ================================================================
    void on_pushButton_37_clicked();
    void on_btntrie_clicked();
    void on_barrerechercheclient_textChanged(const QString &text);
    void on_bouttonajouterclient_clicked();
    void on_bouttonmodifierclient_clicked();
    void on_bouttonsupprimerclient_clicked();
    void on_bouttonexporterclient_clicked();
    void on_bouttonstatclient_clicked();
    void on_btnsms_clicked();
    void handleAssistantInput();
    void showAssistantPopup();
    void addChatMessage(const QString &who, const QString &msg);



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
    void on_paraemploye_clicked();

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
    void on_bouttonmap_clicked();

    void on_bouttonpredictionconteneur_clicked();

private:
    Ui::MainWindow *ui;

    // ── Client ──────────────────────────────────────────────────────
    void afficherListeClients();
    void afficherWidgetAjoutClient();
    void afficherWidgetModifierClient(Client client);
    Client getClientSelectionne();
    SmsClientMetier *sms;
    AI ai;
    QWidget *assistantPopup = nullptr;
    QVBoxLayout *assistantLayout = nullptr;
    QString currentModule = "accueil";
    QJsonObject getSelectedRowData(QTableWidget *table);
    QJsonArray getTablePreview(QTableWidget *table, int limit = 5);
    QTableWidget* getActiveTable();

    // ── Employe ─────────────────────────────────────────────────────
    void afficherEmployes();
    void afficherWidgetAjoutEmploye();
    void afficherWidgetModifierEmploye();
    Employe getEmployeSelectionne();
    QString m_posteConnecte;
    QString m_nomConnecte;
    QString m_emailConnecte;
    void appliquerRestrictionsPoste();
    QString m_codeVerification;
    QString m_emailReset;
    // ── Recyclage ───────────────────────────────────────────────────
    void afficherRecyclages();
    void afficherWidgetAjoutRecyclage();
    void afficherWidgetModifierRecyclage(int idRecyclage);
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
