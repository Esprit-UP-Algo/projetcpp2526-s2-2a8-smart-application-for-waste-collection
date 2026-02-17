#ifndef WASTE_H
#define WASTE_H

#include <QMainWindow>
#include <QVector>

QT_BEGIN_NAMESPACE
namespace Ui { class Waste; }
QT_END_NAMESPACE

// ===============================
// STRUCTURE CLIENT
// ===============================

struct ClientData
{
    int id;
    QString nom;
    QString prenom;
    QString type;
    QString zone;
    QString telephone;
    QString statut;
    QString cin;
};

class Waste : public QMainWindow
{
    Q_OBJECT

public:
    explicit Waste(QWidget *parent = nullptr);
    ~Waste();

private slots:

    // ===== MODULE CLIENT =====
    void on_pushButton_client_ajouter_clicked();
    void on_pushButton_21_clicked();
    void on_pushButton_20_clicked();
    void on_pushButton_19_clicked();
    void on_pushButton_23_clicked();
    void on_pushButton_10_clicked();
    void on_comboTypePropriete_3_currentIndexChanged(int index);

    // ===== NAVIGATION CLIENT =====
    void on_acceuil_clicked();
    void on_pushButton_35_clicked();
    void on_pushButton_36_clicked();
    void on_pushButton_37_clicked();
    void on_pushButton_38_clicked();
    void on_pushButton_45_clicked();
    void on_dec_clicked();

    // ===== MODULE EMPLOYE =====
    void on_pushButton_clicked();
    void on_pushButton_20_emp_clicked();
    void on_pushButton_29_clicked();
    void on_pushButton_17_clicked();
    void on_pushButton_30_clicked();
    void on_pushButton_31_clicked();
    void on_cnx_clicked();
    void on_cnx1_clicked();
    void on_cnxemp_clicked();
    void on_dec_emp_clicked();
    void on_mdp_clicked();
    void on_retour_2_clicked();
    void on_acceuil_2_clicked();
    void on_pushButton_40_clicked();
    void on_pushButton_28_clicked();

    // ===== MENU EMPLOYE =====
    void on_pushButton_39_clicked();
    void on_pushButton_40_menu_clicked();
    void on_pushButton_41_clicked();
    void on_pushButton_42_clicked();
    void on_pushButton_47_clicked();
    void on_dec_2_clicked();

    // ===== ACCUEIL =====
    void on_pushButton_tournees_acc_clicked();
    void on_pushButton_employes_acc_clicked();
    void on_pushButton_clients_acc_clicked();
    void on_pushButton_conteneurs_acc_clicked();
    void on_acceuil_acc_clicked();
    void on_pushButton_recyclage_acc_clicked();
    void on_dec_acc_clicked();

private:

    Ui::Waste *ui;

    // ===== DONNEES =====
    QVector<ClientData> clientsData;

    // ===== MODULE CLIENT =====
    void initialiserInterfaceClient();
    void configurerTableauClient();
    void chargerDonneesExemplesClient();
    void afficherWidgetAjoutClient();
    void rechercherClient();
    void exporterVersPDFClient();
    void afficherWidgetStatistiquesClient();
    void afficherWidgetModificationClient();
    void supprimerClient();
    void trierTableauClient(int critere);

    // ===== MODULE EMPLOYE =====
    void initialiserInterfaceEmploye();

    // ===== MODULE CONTENEURS =====
    void ouvrirModuleConteneurs();
};
void ouvrirModuleConteneurs();

#endif // WASTE_H
