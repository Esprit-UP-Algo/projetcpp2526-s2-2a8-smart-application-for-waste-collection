#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVector>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

// ===============================
// STRUCTURE RECYCLAGE
// ===============================
struct RecyclageData
{
    int id;
    QString materiau;
    double qteEntree;
    double qteRecyclee;
    double qteRejetee;
    double taux;
    QString destination;
    double valeur;
};

// ===============================
// STRUCTURE CONTENEUR
// ===============================
struct ConteneurData
{
    int id;
    QString capacite;
    QString localisation;
    QString adresseComplete;
    double latitude;
    double longitude;
    QString typePropriete;
    int niveauRemplissage;
    double temperature;
    QString etatConteneur;
    QString dateDerniereCollecte;
    QString typesDechet;
};

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    // ===== MODULE RECYCLAGE =====
    void on_pushButton_recyclage_ajouter_clicked();
    void on_pushButton_recyclage_modifier_clicked();
    void on_pushButton_recyclage_supprimer_clicked();
    void on_pushButton_recyclage_rechercher_clicked();
    void on_pushButton_recyclage_exporter_clicked();
    void on_pushButton_recyclage_stats_clicked();

    // ===== MODULE CONTENEURS =====
    void on_pushButton_conteneur_ajouter_clicked();
    void on_pushButton_conteneur_modifier_clicked();
    void on_pushButton_conteneur_supprimer_clicked();
    void on_pushButton_conteneur_rechercher_clicked();
    void on_pushButton_conteneur_exporter_clicked();
    void on_pushButton_conteneur_stats_clicked();

private:
    Ui::MainWindow *ui;

    // ===== DONNEES =====
    QVector<RecyclageData> recyclageData;
    QVector<ConteneurData> conteneursData;

    // ===== MODULE RECYCLAGE =====
    void initialiserInterfaceRecyclage();
    void configurerTableauRecyclage();
    void chargerDonneesExemplesRecyclage();
    void afficherWidgetAjoutRecyclage();
    void afficherWidgetModificationRecyclage();
    void supprimerRecyclage();
    void rechercherRecyclage();
    void exporterVersPDFRecyclage();
    void afficherWidgetStatistiquesRecyclage();

    // ===== MODULE CONTENEURS =====
    void initialiserInterfaceConteneur();
    void configurerTableauConteneur();
    void chargerDonneesExemplesConteneur();
    void afficherWidgetAjoutConteneur();
    void afficherWidgetModificationConteneur();
    void supprimerConteneur();
    void rechercherConteneur();
    void exporterVersPDFConteneur();
    void afficherWidgetStatistiquesConteneur();
};

#endif // MAINWINDOW_H
