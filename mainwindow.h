#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTableWidget>
#include <QLineEdit>
#include <QComboBox>
#include <QMessageBox>
#include <QFileDialog>
#include <QTextStream>
#include <QDialog>
#include <QVBoxLayout>
#include <QLabel>
#include <QFrame>
#include <QPushButton>
#include <QGridLayout>

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
    // Slot pour le bouton Rechercher (utilise lineEdit_8)
    void on_pushButton_21_clicked();

    // Slot pour le bouton Exporter
    void on_pushButton_20_clicked();

    // Slot pour le bouton Statistique
    void on_pushButton_19_clicked();

    // Slot pour le bouton Modifier
    void on_pushButton_23_clicked();

    // Slot pour le bouton Supprimer
    void on_pushButton_10_clicked();

    // Slot pour le bouton Ajouter (dans frame_48)
    void on_pushButton_client_ajouter_clicked();

    // Slot pour le combobox de tri
    void on_comboTypePropriete_3_currentIndexChanged(int index);

private:
    Ui::MainWindow *ui;

    // Méthodes privées pour la gestion
    void initialiserInterface();
    void configurerTableau();
    void chargerDonneesExemples();
    void afficherWidgetAjout();        // Popup d'ajout
    void afficherWidgetModification();
    void afficherWidgetStatistiques();
    void trierTableau(int critere);
    void rechercherClient();
    void exporterVersPDF();
    void supprimerClient();

    // Variables pour stocker les données temporaires
    struct ClientData {
        int id;
        QString nom;
        QString prenom;
        QString type;
        QString zone;
        QString telephone;
        QString statut;
        QString cin;
    };

    QList<ClientData> clientsData;
};
#endif // MAINWINDOW_H
