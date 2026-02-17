#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    // ===== Navigation et interface =====
    void on_pushButton_36_clicked();
    void on_pushButton_37_clicked();
    void on_pushButton_45_clicked();
    void on_pushButton_17_clicked();
    void on_pushButton_38_clicked();
    void on_pushButton_rechercher_3_clicked();
    void on_pushButton_35_clicked();
    void on_pushButton_16_clicked();
    void on_pushButton_60_clicked();
    void on_pushButton_46_clicked();
    void on_pushButton_clicked();
    void on_pushButton_61_clicked();
    void on_conn_clicked();
    void on_frame_20_customContextMenuRequested(const QPoint &pos);
    void on_dec_clicked();
    void on_mdp_clicked();
    void on_cnx_clicked();
    void on_pushButton_44_clicked();
    void on_pushButton_30_clicked();
    void on_retour_clicked();
    void on_acceuil_clicked();
    void on_deconnection_clicked();
    void on_recyclage_clicked();
    void on_CONTENEUR_clicked();
    void on_TOURNEE_clicked();

    // ===== Boutons d'ajout de formulaires =====
    void on_bouton_ajouter_employe_clicked();  // Employé
    void on_pushButton_42_clicked();  // Client
    void on_pushButton_65_clicked();  // Recyclage
    void on_pushButton_66_clicked();  // Collecte
    void on_pushButton_67_clicked();  // Conteneur

private:
    Ui::MainWindow *ui;

    // ===== Fonctions d'affichage des formulaires =====
    void afficherWidgetAjoutEmploye();
    void afficherWidgetAjoutClient();
    void afficherWidgetAjoutRecyclage();
    void afficherWidgetAjoutCollecte();
    void afficherWidgetAjoutConteneur();
};

#endif // MAINWINDOW_H
