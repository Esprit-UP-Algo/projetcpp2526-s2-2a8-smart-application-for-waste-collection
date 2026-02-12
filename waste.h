#ifndef WASTE_H
#define WASTE_H

#include <QMainWindow>
#include <QStackedWidget>

// Inclusions pour le module Client
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

// Inclusions pour le module Employé
#include <QPainter>
#include <QPdfWriter>
#include <QTextDocument>
#include <QInputDialog>
#include <QRandomGenerator>
#include <QHeaderView>
#include <QProgressBar>
#include <QScrollArea>
#include <QGraphicsDropShadowEffect>
#include <QPropertyAnimation>

QT_BEGIN_NAMESPACE
namespace Ui {
class Waste;
}
QT_END_NAMESPACE

class Waste : public QMainWindow
{
    Q_OBJECT

public:
    Waste(QWidget *parent = nullptr);
    ~Waste();

private slots:
    // ============================================
    // SLOTS DU MODULE CLIENT
    // ============================================

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

    // Boutons de navigation du menu Client
    void on_acceuil_clicked();
    void on_pushButton_35_clicked();  // tournées
    void on_pushButton_36_clicked();  // employés
    void on_pushButton_37_clicked();  // clients
    void on_pushButton_38_clicked();  // conteneurs
    void on_pushButton_45_clicked();  // recyclage
    void on_dec_clicked();            // déconnexion

    // ============================================
    // SLOTS DU MODULE EMPLOYÉ
    // ============================================

    void on_pushButton_clicked();
    void on_pushButton_20_emp_clicked();  // Renommé pour éviter le conflit
    void on_pushButton_29_clicked();
    void on_pushButton_17_clicked();
    void on_pushButton_30_clicked();
    void on_pushButton_31_clicked();
    void on_cnx_clicked();
    void on_cnx1_clicked();
    void on_cnxemp_clicked();
    void on_dec_emp_clicked();            // Renommé pour éviter le conflit
    void on_mdp_clicked();
    void on_retour_2_clicked();
    void on_acceuil_2_clicked();
    void on_pushButton_40_clicked();
    void on_pushButton_28_clicked();

    // Boutons de navigation du menu Employé
    void on_pushButton_39_clicked();      // tournées
    void on_pushButton_40_menu_clicked(); // employés - renommé
    void on_pushButton_41_clicked();      // clients
    void on_pushButton_42_clicked();      // conteneurs
    void on_pushButton_47_clicked();      // recyclage
    void on_dec_2_clicked();              // déconnexion

    // Slots de navigation du module Accueil
    void on_pushButton_tournees_acc_clicked();
    void on_pushButton_employes_acc_clicked();
    void on_pushButton_clients_acc_clicked();
    void on_pushButton_conteneurs_acc_clicked();
    void on_acceuil_acc_clicked();
    void on_pushButton_recyclage_acc_clicked();
    void on_dec_acc_clicked();

private:
    Ui::Waste *ui;

    // ============================================
    // MÉTHODES PRIVÉES DU MODULE CLIENT
    // ============================================

    void initialiserInterfaceClient();
    void configurerTableauClient();
    void chargerDonneesExemplesClient();
    void afficherWidgetAjoutClient();        // Popup d'ajout
    void afficherWidgetModificationClient();
    void afficherWidgetStatistiquesClient();
    void trierTableauClient(int critere);
    void rechercherClient();
    void exporterVersPDFClient();
    void supprimerClient();

    // Variables pour stocker les données temporaires du module Client
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

    // ============================================
    // MÉTHODES PRIVÉES DU MODULE EMPLOYÉ
    // ============================================

    void initialiserInterfaceEmploye();
};

#endif // WASTE_H
