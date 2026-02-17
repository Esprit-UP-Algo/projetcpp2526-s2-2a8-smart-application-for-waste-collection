#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QGraphicsDropShadowEffect>
#include <QPropertyAnimation>
#include "mainwindow.h"
#include "ui_mainwindow.h"

// Bibliothèques pour les dialogues et widgets
#include <QDialog>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QFrame>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QComboBox>
#include <QDateEdit>
#include <QTimeEdit>
#include <QSpinBox>
#include <QDoubleSpinBox>
#include <QScrollArea>
#include <QScrollBar>
#include <QGroupBox>
#include <QCheckBox>
#include <QRadioButton>

// Bibliothèques pour les dates et temps
#include <QDate>
#include <QTime>

// Bibliothèques pour les effets graphiques (si vous les utilisez)
#include <QGraphicsDropShadowEffect>
#include <QPropertyAnimation>

// Bibliothèque pour les groupes de boutons
#include <QButtonGroup>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QGraphicsDropShadowEffect *glow = new QGraphicsDropShadowEffect(this);
    glow->setBlurRadius(0);
    glow->setOffset(0, 0);
    glow->setColor(QColor(0, 170, 255, 180)); // bleu lumineux

    ui->frame_43->setGraphicsEffect(glow);
    QPropertyAnimation *anim = new QPropertyAnimation(glow, "blurRadius");

    anim->setStartValue(0);
    anim->setEndValue(40);
    anim->setEasingCurve(QEasingCurve::OutCubic);
    anim->start();
    ui->stackedWidget->setCurrentIndex(1);
}
MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::on_pushButton_36_clicked()
{
    ui->stackedWidget_2->setCurrentIndex(4);

}
void MainWindow::on_pushButton_37_clicked()
{
    ui->stackedWidget_2->setCurrentIndex(2);
}
void MainWindow::on_pushButton_45_clicked()
{
    ui->stackedWidget_2->setCurrentIndex(0);
}
void MainWindow::on_pushButton_17_clicked()
{
    ui->stackedWidget_2->setCurrentIndex(3);
}

void MainWindow::on_pushButton_rechercher_3_clicked()
{
    ui->stackedWidget_2->setCurrentIndex(5);
}



void MainWindow::on_mdp_clicked()
{
     ui->stackedWidget->setCurrentIndex(0);
}


void MainWindow::on_cnx_clicked()
{
    ui->stackedWidget->setCurrentIndex(2);
    ui->stackedWidget_2->setCurrentIndex(11);
}




void MainWindow::on_pushButton_44_clicked()
{
    ui->stackedWidget->setCurrentIndex(8);
}


void MainWindow::on_pushButton_16_clicked()
{
    ui->stackedWidget->setCurrentIndex(8);
}


void MainWindow::on_pushButton_30_clicked()
{
    ui->stackedWidget_2->setCurrentIndex(2);
}


void MainWindow::on_retour_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}


void MainWindow::on_acceuil_clicked()
{
     ui->stackedWidget_2->setCurrentIndex(11);
}





void MainWindow::on_deconnection_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}


void MainWindow::on_recyclage_clicked()
{
    ui->stackedWidget_2->setCurrentIndex(0);

}







void MainWindow::on_CONTENEUR_clicked()
{

    ui->stackedWidget_2->setCurrentIndex(6);
}



void MainWindow::on_TOURNEE_clicked()
{
    ui->stackedWidget_2->setCurrentIndex(9);
}







void MainWindow::on_pushButton_38_clicked() {}
void MainWindow::on_pushButton_35_clicked() {}
void MainWindow::on_pushButton_60_clicked() {}
void MainWindow::on_pushButton_46_clicked() {}
void MainWindow::on_pushButton_clicked() {}
void MainWindow::on_pushButton_61_clicked() {}
void MainWindow::on_conn_clicked() {}

void MainWindow::on_dec_clicked() {}
void MainWindow::on_pushButton_42_clicked()
{
    afficherWidgetAjoutClient();
}

void MainWindow::afficherWidgetAjoutClient()
{
    QDialog *dialog = new QDialog(this);
    dialog->setWindowTitle("+ Ajouter un Client");
    dialog->setFixedSize(850, 600);
    dialog->setStyleSheet("QDialog { background-color: #EDEDED; }");

    QVBoxLayout *mainLayout = new QVBoxLayout(dialog);

    QFrame *container = new QFrame();
    container->setStyleSheet(
        "QFrame {"
        "background-color:#F2F2F2;"
        "border-radius:20px;"
        "}"
        );

    QVBoxLayout *containerLayout = new QVBoxLayout(container);
    containerLayout->setContentsMargins(30,30,30,30);

    // ===== TITRE =====
    QLabel *titre = new QLabel("👤 Informations Client");
    titre->setAlignment(Qt::AlignCenter);
    titre->setStyleSheet(
        "QLabel {"
        "font-size:20px;"
        "font-weight:bold;"
        "color:white;"
        "padding:20px;"
        "border-radius:18px;"
        "background:qlineargradient("
        "x1:0,y1:0,x2:0,y2:1,"
        "stop:0 #2C5F7C,"
        "stop:1 #1B3A57);"
        "}"
        );

    containerLayout->addWidget(titre);
    containerLayout->addSpacing(20);

    // ===== CONTENU =====
    QWidget *contentWidget = new QWidget();
    contentWidget->setStyleSheet(
        "background-color:white;"
        "border-radius:15px;"
        );

    QGridLayout *gridLayout = new QGridLayout(contentWidget);
    gridLayout->setSpacing(15);
    gridLayout->setContentsMargins(25,25,25,25);

    // ===== STYLES =====
    QString labelStyle =
        "QLabel {"
        "background-color:transparent;"
        "padding:5px;"
        "font-size:13px;"
        "font-weight:600;"
        "color:#374151;"
        "}";

    QString editStyle =
        "QLineEdit {"
        "background-color:#F9FAFB;"
        "border:1px solid #D1D5DB;"
        "border-radius:8px;"
        "padding:12px 16px;"
        "font-size:14px;"
        "color:#111827;"
        "}"
        "QLineEdit:hover {"
        "border:1px solid #2C5F7C;"
        "background-color:#FFFFFF;"
        "}"
        "QLineEdit:focus {"
        "border:2px solid #2C5F7C;"
        "background-color:#FFFFFF;"
        "padding:11px 15px;"
        "}";

    // ===== CHAMPS CLIENT =====
    QLineEdit *nom = new QLineEdit();
    QLineEdit *prenom = new QLineEdit();
    QLineEdit *telephone = new QLineEdit();
    QLineEdit *cin = new QLineEdit();
    QLineEdit *zone = new QLineEdit();
    QLineEdit *type = new QLineEdit();
    QLineEdit *adresse = new QLineEdit();

    nom->setStyleSheet(editStyle);
    prenom->setStyleSheet(editStyle);
    telephone->setStyleSheet(editStyle);
    cin->setStyleSheet(editStyle);
    zone->setStyleSheet(editStyle);
    type->setStyleSheet(editStyle);
    adresse->setStyleSheet(editStyle);

    // Colonne gauche
    QLabel *lblNom = new QLabel("👤 Nom:");
    lblNom->setStyleSheet(labelStyle);
    gridLayout->addWidget(lblNom, 0, 0);
    gridLayout->addWidget(nom, 0, 1);

    QLabel *lblPrenom = new QLabel("👤 Prenom:");
    lblPrenom->setStyleSheet(labelStyle);
    gridLayout->addWidget(lblPrenom, 1, 0);
    gridLayout->addWidget(prenom, 1, 1);

    QLabel *lblTelephone = new QLabel("📞 Téléphone:");
    lblTelephone->setStyleSheet(labelStyle);
    gridLayout->addWidget(lblTelephone, 2, 0);
    gridLayout->addWidget(telephone, 2, 1);

    // Colonne droite
    QLabel *lblCIN = new QLabel("🆔 CIN:");
    lblCIN->setStyleSheet(labelStyle);
    gridLayout->addWidget(lblCIN, 0, 2);
    gridLayout->addWidget(cin, 0, 3);

    QLabel *lblZone = new QLabel("📍 Zone :");
    lblZone->setStyleSheet(labelStyle);
    gridLayout->addWidget(lblZone, 1, 2);
    gridLayout->addWidget(zone, 1, 3);

    QLabel *lblType = new QLabel("🏢 Type :");
    lblType->setStyleSheet(labelStyle);
    gridLayout->addWidget(lblType, 2, 2);
    gridLayout->addWidget(type, 2, 3);

    // Adresse sur toute la largeur
    QLabel *lblAdresse = new QLabel("🏠 Adresse :");
    lblAdresse->setStyleSheet(labelStyle);
    gridLayout->addWidget(lblAdresse, 3, 0);
    gridLayout->addWidget(adresse, 3, 1, 1, 3);

    containerLayout->addWidget(contentWidget);
    containerLayout->addSpacing(15);

    QLabel *note = new QLabel("* Tous les champs sont obligatoires");
    note->setStyleSheet("color:#6E7F91; font-style:italic; font-size:12px;");
    containerLayout->addWidget(note);

    // ===== BOUTONS =====
    QHBoxLayout *btnLayout = new QHBoxLayout();
    btnLayout->setSpacing(15);

    QPushButton *annuler = new QPushButton("✗ Annuler");
    annuler->setMinimumHeight(50);
    annuler->setStyleSheet(
        "QPushButton {"
        "background-color:#E5E7EB;"
        "color:#374151;"
        "font-size:15px;"
        "font-weight:600;"
        "border:none;"
        "border-radius:8px;"
        "padding:12px 30px;"
        "}"
        "QPushButton:hover { background-color:#D1D5DB; }"
        );

    QPushButton *ajouter = new QPushButton("✓ Ajouter");
    ajouter->setMinimumHeight(50);
    ajouter->setStyleSheet(
        "QPushButton {"
        "background:qlineargradient("
        "x1:0,y1:0,x2:0,y2:1,"
        "stop:0 #2C5F7C,"
        "stop:1 #1B3A57);"
        "color:white;"
        "font-size:15px;"
        "font-weight:600;"
        "border:none;"
        "border-radius:8px;"
        "padding:12px 30px;"
        "}"
        "QPushButton:hover {"
        "background:qlineargradient("
        "x1:0,y1:0,x2:0,y2:1,"
        "stop:0 #3A6EA5,"
        "stop:1 #2C5F7C);"
        "}"
        );

    btnLayout->addWidget(annuler);
    btnLayout->addWidget(ajouter);

    containerLayout->addLayout(btnLayout);
    mainLayout->addWidget(container);

    connect(annuler, &QPushButton::clicked, dialog, &QDialog::reject);

    dialog->exec();
}
void MainWindow::on_pushButton_65_clicked()
{
    afficherWidgetAjoutRecyclage();
}

void MainWindow::afficherWidgetAjoutRecyclage()
{
    QDialog *dialog = new QDialog(this);
    dialog->setWindowTitle("+ Ajouter une Opération de Recyclage");
    dialog->setFixedSize(850, 650);
    dialog->setStyleSheet("QDialog { background-color: #EDEDED; }");

    QVBoxLayout *mainLayout = new QVBoxLayout(dialog);

    QFrame *container = new QFrame();
    container->setStyleSheet(
        "QFrame {"
        "background-color:#F2F2F2;"
        "border-radius:20px;"
        "}"
        );

    QVBoxLayout *containerLayout = new QVBoxLayout(container);
    containerLayout->setContentsMargins(30,30,30,30);

    // ===== TITRE =====
    QLabel *titre = new QLabel("♻️ Opération de Recyclage");
    titre->setAlignment(Qt::AlignCenter);
    titre->setStyleSheet(
        "QLabel {"
        "font-size:20px;"
        "font-weight:bold;"
        "color:white;"
        "padding:20px;"
        "border-radius:18px;"
        "background:qlineargradient("
        "x1:0,y1:0,x2:0,y2:1,"
        "stop:0 #2C5F7C,"
        "stop:1 #1B3A57);"
        "}"
        );

    containerLayout->addWidget(titre);
    containerLayout->addSpacing(20);

    // ===== CONTENU =====
    QWidget *contentWidget = new QWidget();
    contentWidget->setStyleSheet(
        "background-color:white;"
        "border-radius:15px;"
        );

    QGridLayout *gridLayout = new QGridLayout(contentWidget);
    gridLayout->setSpacing(15);
    gridLayout->setContentsMargins(25,25,25,25);

    // ===== STYLES =====
    QString labelStyle =
        "QLabel {"
        "background-color:transparent;"
        "padding:5px;"
        "font-size:13px;"
        "font-weight:600;"
        "color:#374151;"
        "}";

    QString editStyle =
        "QLineEdit {"
        "background-color:#F9FAFB;"
        "border:1px solid #D1D5DB;"
        "border-radius:8px;"
        "padding:12px 16px;"
        "font-size:14px;"
        "color:#111827;"
        "}"
        "QLineEdit:hover {"
        "border:1px solid #2C5F7C;"
        "background-color:#FFFFFF;"
        "}"
        "QLineEdit:focus {"
        "border:2px solid #2C5F7C;"
        "background-color:#FFFFFF;"
        "padding:11px 15px;"
        "}";

    // ===== CHAMPS RECYCLAGE =====
    QLineEdit *id = new QLineEdit();
    QLineEdit *materiau = new QLineEdit();
    QLineEdit *qteEntree = new QLineEdit();
    QLineEdit *qteRecyclee = new QLineEdit();
    QLineEdit *qteRejetee = new QLineEdit();
    QLineEdit *taux = new QLineEdit();
    QLineEdit *destination = new QLineEdit();
    QLineEdit *valeur = new QLineEdit();

    id->setStyleSheet(editStyle);
    materiau->setStyleSheet(editStyle);
    qteEntree->setStyleSheet(editStyle);
    qteRecyclee->setStyleSheet(editStyle);
    qteRejetee->setStyleSheet(editStyle);
    taux->setStyleSheet(editStyle);
    destination->setStyleSheet(editStyle);
    valeur->setStyleSheet(editStyle);

    // Colonne gauche
    QLabel *lblId = new QLabel("🆔 id:");
    lblId->setStyleSheet(labelStyle);
    gridLayout->addWidget(lblId, 0, 0);
    gridLayout->addWidget(id, 0, 1);

    QLabel *lblMateriau = new QLabel("📦 Matériau:");
    lblMateriau->setStyleSheet(labelStyle);
    gridLayout->addWidget(lblMateriau, 1, 0);
    gridLayout->addWidget(materiau, 1, 1);

    QLabel *lblQteEntree = new QLabel("📊 Qté Entrée:");
    lblQteEntree->setStyleSheet(labelStyle);
    gridLayout->addWidget(lblQteEntree, 2, 0);
    gridLayout->addWidget(qteEntree, 2, 1);

    QLabel *lblQteRecyclee = new QLabel("📊 Quantite_recyclee (kg):");
    lblQteRecyclee->setStyleSheet(labelStyle);
    gridLayout->addWidget(lblQteRecyclee, 3, 0);
    gridLayout->addWidget(qteRecyclee, 3, 1);

    // Colonne droite
    QLabel *lblQteRejetee = new QLabel("📊 Quantite_rejetee (kg):");
    lblQteRejetee->setStyleSheet(labelStyle);
    gridLayout->addWidget(lblQteRejetee, 0, 2);
    gridLayout->addWidget(qteRejetee, 0, 3);

    QLabel *lblTaux = new QLabel("📈 Taux (%):");
    lblTaux->setStyleSheet(labelStyle);
    gridLayout->addWidget(lblTaux, 1, 2);
    gridLayout->addWidget(taux, 1, 3);

    QLabel *lblDestination = new QLabel("📍 Destination:");
    lblDestination->setStyleSheet(labelStyle);
    gridLayout->addWidget(lblDestination, 2, 2);
    gridLayout->addWidget(destination, 2, 3);

    QLabel *lblValeur = new QLabel("💰 Valeur(TND):");
    lblValeur->setStyleSheet(labelStyle);
    gridLayout->addWidget(lblValeur, 3, 2);
    gridLayout->addWidget(valeur, 3, 3);

    containerLayout->addWidget(contentWidget);
    containerLayout->addSpacing(15);

    QLabel *note = new QLabel("* Tous les champs sont obligatoires");
    note->setStyleSheet("color:#6E7F91; font-style:italic; font-size:12px;");
    containerLayout->addWidget(note);

    // ===== BOUTONS =====
    QHBoxLayout *btnLayout = new QHBoxLayout();
    btnLayout->setSpacing(15);

    QPushButton *annuler = new QPushButton("✗ Annuler");
    annuler->setMinimumHeight(50);
    annuler->setStyleSheet(
        "QPushButton {"
        "background-color:#E5E7EB;"
        "color:#374151;"
        "font-size:15px;"
        "font-weight:600;"
        "border:none;"
        "border-radius:8px;"
        "padding:12px 30px;"
        "}"
        "QPushButton:hover { background-color:#D1D5DB; }"
        );

    QPushButton *ajouter = new QPushButton("✓ Ajouter");
    ajouter->setMinimumHeight(50);
    ajouter->setStyleSheet(
        "QPushButton {"
        "background:qlineargradient("
        "x1:0,y1:0,x2:0,y2:1,"
        "stop:0 #2C5F7C,"
        "stop:1 #1B3A57);"
        "color:white;"
        "font-size:15px;"
        "font-weight:600;"
        "border:none;"
        "border-radius:8px;"
        "padding:12px 30px;"
        "}"
        "QPushButton:hover {"
        "background:qlineargradient("
        "x1:0,y1:0,x2:0,y2:1,"
        "stop:0 #3A6EA5,"
        "stop:1 #2C5F7C);"
        "}"
        );

    btnLayout->addWidget(annuler);
    btnLayout->addWidget(ajouter);

    containerLayout->addLayout(btnLayout);
    mainLayout->addWidget(container);

    connect(annuler, &QPushButton::clicked, dialog, &QDialog::reject);

    dialog->exec();
}
void MainWindow::on_pushButton_66_clicked()
{
    afficherWidgetAjoutCollecte();
}

void MainWindow::afficherWidgetAjoutCollecte()
{
    QDialog *dialog = new QDialog(this);
    dialog->setWindowTitle("+ Ajouter une Collecte");
    dialog->setFixedSize(850, 700);
    dialog->setStyleSheet("QDialog { background-color: #EDEDED; }");

    QVBoxLayout *mainLayout = new QVBoxLayout(dialog);

    QFrame *container = new QFrame();
    container->setStyleSheet(
        "QFrame {"
        "background-color:#F2F2F2;"
        "border-radius:20px;"
        "}"
        );

    QVBoxLayout *containerLayout = new QVBoxLayout(container);
    containerLayout->setContentsMargins(30,30,30,30);

    // ===== TITRE =====
    QLabel *titre = new QLabel("🚛 Informations Collecte");
    titre->setAlignment(Qt::AlignCenter);
    titre->setStyleSheet(
        "QLabel {"
        "font-size:20px;"
        "font-weight:bold;"
        "color:white;"
        "padding:20px;"
        "border-radius:18px;"
        "background:qlineargradient("
        "x1:0,y1:0,x2:0,y2:1,"
        "stop:0 #2C5F7C,"
        "stop:1 #1B3A57);"
        "}"
        );

    containerLayout->addWidget(titre);
    containerLayout->addSpacing(20);

    // ===== CONTENU =====
    QWidget *contentWidget = new QWidget();
    contentWidget->setStyleSheet(
        "background-color:white;"
        "border-radius:15px;"
        );

    QGridLayout *gridLayout = new QGridLayout(contentWidget);
    gridLayout->setSpacing(15);
    gridLayout->setContentsMargins(25,25,25,25);

    // ===== STYLES =====
    QString labelStyle =
        "QLabel {"
        "background-color:transparent;"
        "padding:5px;"
        "font-size:13px;"
        "font-weight:600;"
        "color:#374151;"
        "}";

    QString editStyle =
        "QLineEdit, QDateEdit, QTimeEdit, QComboBox, QSpinBox, QDoubleSpinBox {"
        "background-color:#F9FAFB;"
        "border:1px solid #D1D5DB;"
        "border-radius:8px;"
        "padding:12px 16px;"
        "font-size:14px;"
        "color:#111827;"
        "}"
        "QLineEdit:hover, QDateEdit:hover, QTimeEdit:hover, QComboBox:hover, QSpinBox:hover, QDoubleSpinBox:hover {"
        "border:1px solid #2C5F7C;"
        "background-color:#FFFFFF;"
        "}"
        "QLineEdit:focus, QDateEdit:focus, QTimeEdit:focus, QComboBox:focus, QSpinBox:focus, QDoubleSpinBox:focus {"
        "border:2px solid #2C5F7C;"
        "background-color:#FFFFFF;"
        "padding:11px 15px;"
        "}";

    // ===== CHAMPS COLLECTE =====
    QLineEdit *id = new QLineEdit();
    QDateEdit *date = new QDateEdit(QDate::fromString("01/01/2000", "dd/MM/yyyy"));
    date->setDisplayFormat("dd/MM/yyyy");
    QTimeEdit *heure = new QTimeEdit(QTime(12, 0));
    heure->setDisplayFormat("hh:mm AP");
    QLineEdit *zone = new QLineEdit();

    QComboBox *type = new QComboBox();
    type->addItems({"Recyclable", "Mixte", "Organique"});

    QComboBox *status = new QComboBox();
    status->addItems({"Planifiée", "En cours", "Terminée"});

    QDoubleSpinBox *distance = new QDoubleSpinBox();
    distance->setSuffix(" Km");
    distance->setDecimals(2);
    distance->setMaximum(9999.99);

    QDoubleSpinBox *quantite = new QDoubleSpinBox();
    quantite->setSuffix(" Kg");
    quantite->setDecimals(2);
    quantite->setMaximum(9999.99);

    id->setStyleSheet(editStyle);
    date->setStyleSheet(editStyle);
    heure->setStyleSheet(editStyle);
    zone->setStyleSheet(editStyle);
    type->setStyleSheet(editStyle);
    status->setStyleSheet(editStyle);
    distance->setStyleSheet(editStyle);
    quantite->setStyleSheet(editStyle);

    // Colonne gauche
    QLabel *lblId = new QLabel("🆔 id:");
    lblId->setStyleSheet(labelStyle);
    gridLayout->addWidget(lblId, 0, 0);
    gridLayout->addWidget(id, 0, 1);

    QLabel *lblDate = new QLabel("📅 Date:");
    lblDate->setStyleSheet(labelStyle);
    gridLayout->addWidget(lblDate, 1, 0);
    gridLayout->addWidget(date, 1, 1);

    QLabel *lblHeure = new QLabel("⏰ heure:");
    lblHeure->setStyleSheet(labelStyle);
    gridLayout->addWidget(lblHeure, 2, 0);
    gridLayout->addWidget(heure, 2, 1);

    QLabel *lblZone = new QLabel("📍 zone :");
    lblZone->setStyleSheet(labelStyle);
    gridLayout->addWidget(lblZone, 3, 0);
    gridLayout->addWidget(zone, 3, 1);

    // Colonne droite
    QLabel *lblType = new QLabel("🏷️ type:");
    lblType->setStyleSheet(labelStyle);
    gridLayout->addWidget(lblType, 0, 2);
    gridLayout->addWidget(type, 0, 3);

    QLabel *lblStatus = new QLabel("📊 status :");
    lblStatus->setStyleSheet(labelStyle);
    gridLayout->addWidget(lblStatus, 1, 2);
    gridLayout->addWidget(status, 1, 3);

    QLabel *lblDistance = new QLabel("📏 distance :");
    lblDistance->setStyleSheet(labelStyle);
    gridLayout->addWidget(lblDistance, 2, 2);
    gridLayout->addWidget(distance, 2, 3);

    QLabel *lblQuantite = new QLabel("⚖️ Quantité_collecte :");
    lblQuantite->setStyleSheet(labelStyle);
    gridLayout->addWidget(lblQuantite, 3, 2);
    gridLayout->addWidget(quantite, 3, 3);

    containerLayout->addWidget(contentWidget);
    containerLayout->addSpacing(15);

    QLabel *note = new QLabel("* Tous les champs sont obligatoires");
    note->setStyleSheet("color:#6E7F91; font-style:italic; font-size:12px;");
    containerLayout->addWidget(note);

    // ===== BOUTONS =====
    QHBoxLayout *btnLayout = new QHBoxLayout();
    btnLayout->setSpacing(15);

    QPushButton *annuler = new QPushButton("✗ Annuler");
    annuler->setMinimumHeight(50);
    annuler->setStyleSheet(
        "QPushButton {"
        "background-color:#E5E7EB;"
        "color:#374151;"
        "font-size:15px;"
        "font-weight:600;"
        "border:none;"
        "border-radius:8px;"
        "padding:12px 30px;"
        "}"
        "QPushButton:hover { background-color:#D1D5DB; }"
        );

    QPushButton *ajouter = new QPushButton("✓ Ajouter");
    ajouter->setMinimumHeight(50);
    ajouter->setStyleSheet(
        "QPushButton {"
        "background:qlineargradient("
        "x1:0,y1:0,x2:0,y2:1,"
        "stop:0 #2C5F7C,"
        "stop:1 #1B3A57);"
        "color:white;"
        "font-size:15px;"
        "font-weight:600;"
        "border:none;"
        "border-radius:8px;"
        "padding:12px 30px;"
        "}"
        "QPushButton:hover {"
        "background:qlineargradient("
        "x1:0,y1:0,x2:0,y2:1,"
        "stop:0 #3A6EA5,"
        "stop:1 #2C5F7C);"
        "}"
        );

    btnLayout->addWidget(annuler);
    btnLayout->addWidget(ajouter);

    containerLayout->addLayout(btnLayout);
    mainLayout->addWidget(container);

    connect(annuler, &QPushButton::clicked, dialog, &QDialog::reject);

    dialog->exec();
}
void MainWindow::on_pushButton_67_clicked()
{
    afficherWidgetAjoutConteneur();
}

void MainWindow::afficherWidgetAjoutConteneur()
{
    QDialog *dialog = new QDialog(this);
    dialog->setWindowTitle("+ Ajouter un Conteneur");
    dialog->setFixedSize(900, 750);
    dialog->setStyleSheet("QDialog { background-color: #EDEDED; }");

    QVBoxLayout *mainLayout = new QVBoxLayout(dialog);

    QFrame *container = new QFrame();
    container->setStyleSheet(
        "QFrame {"
        "background-color:#F2F2F2;"
        "border-radius:20px;"
        "}"
        );

    QVBoxLayout *containerLayout = new QVBoxLayout(container);
    containerLayout->setContentsMargins(30,30,30,30);

    // ===== TITRE =====
    QLabel *titre = new QLabel("🗑️ Informations Conteneur");
    titre->setAlignment(Qt::AlignCenter);
    titre->setStyleSheet(
        "QLabel {"
        "font-size:20px;"
        "font-weight:bold;"
        "color:white;"
        "padding:20px;"
        "border-radius:18px;"
        "background:qlineargradient("
        "x1:0,y1:0,x2:0,y2:1,"
        "stop:0 #2C5F7C,"
        "stop:1 #1B3A57);"
        "}"
        );

    containerLayout->addWidget(titre);
    containerLayout->addSpacing(20);

    // ===== SCROLL AREA =====
    QScrollArea *scrollArea = new QScrollArea();
    scrollArea->setWidgetResizable(true);
    scrollArea->setFrameShape(QFrame::NoFrame);

    QWidget *scrollWidget = new QWidget();
    scrollWidget->setStyleSheet(
        "background-color:white;"
        "border-radius:15px;"
        );

    QVBoxLayout *scrollLayout = new QVBoxLayout(scrollWidget);
    scrollLayout->setSpacing(20);
    scrollLayout->setContentsMargins(25,25,25,25);

    // ===== STYLES =====
    QString labelStyle =
        "QLabel {"
        "background-color:transparent;"
        "padding:5px;"
        "font-size:13px;"
        "font-weight:600;"
        "color:#374151;"
        "}";

    QString editStyle =
        "QLineEdit, QDateEdit, QSpinBox, QDoubleSpinBox, QComboBox {"
        "background-color:#F9FAFB;"
        "border:1px solid #D1D5DB;"
        "border-radius:8px;"
        "padding:12px 16px;"
        "font-size:14px;"
        "color:#111827;"
        "}"
        "QLineEdit:hover, QDateEdit:hover, QSpinBox:hover, QDoubleSpinBox:hover, QComboBox:hover {"
        "border:1px solid #2C5F7C;"
        "background-color:#FFFFFF;"
        "}"
        "QLineEdit:focus, QDateEdit:focus, QSpinBox:focus, QDoubleSpinBox:focus, QComboBox:focus {"
        "border:2px solid #2C5F7C;"
        "background-color:#FFFFFF;"
        "padding:11px 15px;"
        "}";

    // ===== SECTION 1: Informations de base =====
    QLabel *section1 = new QLabel("📋 Informations de Base");
    section1->setStyleSheet(
        "font-size:15px;"
        "font-weight:bold;"
        "color:#2C5F7C;"
        "padding:10px 0px;"
        );
    scrollLayout->addWidget(section1);

    QGridLayout *grid1 = new QGridLayout();
    grid1->setSpacing(15);

    QLineEdit *capacite = new QLineEdit();
    QLineEdit *localisation = new QLineEdit();
    QLineEdit *adresseComplete = new QLineEdit();
    QDoubleSpinBox *latitude = new QDoubleSpinBox();
    latitude->setDecimals(6);
    latitude->setRange(-90, 90);
    latitude->setValue(48.856614);
    QDoubleSpinBox *longitude = new QDoubleSpinBox();
    longitude->setDecimals(6);
    longitude->setRange(-180, 180);
    longitude->setValue(2.352222);
    QComboBox *typePropriete = new QComboBox();
    typePropriete->addItems({"Public", "Privé", "Mixte"});

    capacite->setStyleSheet(editStyle);
    localisation->setStyleSheet(editStyle);
    adresseComplete->setStyleSheet(editStyle);
    latitude->setStyleSheet(editStyle);
    longitude->setStyleSheet(editStyle);
    typePropriete->setStyleSheet(editStyle);

    QLabel *lblCapacite = new QLabel("📦 capacité:");
    lblCapacite->setStyleSheet(labelStyle);
    grid1->addWidget(lblCapacite, 0, 0);
    grid1->addWidget(capacite, 0, 1);

    QLabel *lblLocalisation = new QLabel("📍 localisation:");
    lblLocalisation->setStyleSheet(labelStyle);
    grid1->addWidget(lblLocalisation, 1, 0);
    grid1->addWidget(localisation, 1, 1);

    QLabel *lblAdresse = new QLabel("🏠 adresse complete:");
    lblAdresse->setStyleSheet(labelStyle);
    grid1->addWidget(lblAdresse, 2, 0);
    grid1->addWidget(adresseComplete, 2, 1);

    QLabel *lblLatitude = new QLabel("🌐 lattitude:");
    lblLatitude->setStyleSheet(labelStyle);
    grid1->addWidget(lblLatitude, 3, 0);
    grid1->addWidget(latitude, 3, 1);

    QLabel *lblLongitude = new QLabel("🌐 Longitude:");
    lblLongitude->setStyleSheet(labelStyle);
    grid1->addWidget(lblLongitude, 4, 0);
    grid1->addWidget(longitude, 4, 1);

    QLabel *lblTypePropriete = new QLabel("🏢 Type de Propriété :");
    lblTypePropriete->setStyleSheet(labelStyle);
    grid1->addWidget(lblTypePropriete, 5, 0);
    grid1->addWidget(typePropriete, 5, 1);

    scrollLayout->addLayout(grid1);

    // ===== SECTION 2: État et Monitoring =====
    QLabel *section2 = new QLabel("📊 État et Monitoring:");
    section2->setStyleSheet(
        "font-size:15px;"
        "font-weight:bold;"
        "color:#2C5F7C;"
        "padding:10px 0px;"
        "margin-top:10px;"
        );
    scrollLayout->addWidget(section2);

    QGridLayout *grid2 = new QGridLayout();
    grid2->setSpacing(15);

    QSpinBox *niveauRemplissage = new QSpinBox();
    niveauRemplissage->setSuffix(" %");
    niveauRemplissage->setRange(0, 100);

    QDoubleSpinBox *temperature = new QDoubleSpinBox();
    temperature->setSuffix(" °C");
    temperature->setDecimals(1);
    temperature->setValue(20.0);

    QComboBox *etatConteneur = new QComboBox();
    etatConteneur->addItems({"Opérationnel", "En maintenance", "Hors service"});

    QDateEdit *dateDerniereCollecte = new QDateEdit(QDate::fromString("01/01/2000", "dd/MM/yyyy"));
    dateDerniereCollecte->setDisplayFormat("dd/MM/yyyy");

    QLineEdit *typesDechet = new QLineEdit();

    niveauRemplissage->setStyleSheet(editStyle);
    temperature->setStyleSheet(editStyle);
    etatConteneur->setStyleSheet(editStyle);
    dateDerniereCollecte->setStyleSheet(editStyle);
    typesDechet->setStyleSheet(editStyle);

    QLabel *lblNiveau = new QLabel("📊 Niveau de Remplissage %");
    lblNiveau->setStyleSheet(labelStyle);
    grid2->addWidget(lblNiveau, 0, 0);
    grid2->addWidget(niveauRemplissage, 0, 1);

    QLabel *lblTemp1 = new QLabel("🌡️ Température Interne (°C)");
    lblTemp1->setStyleSheet(labelStyle);
    grid2->addWidget(lblTemp1, 1, 0);
    grid2->addWidget(temperature, 1, 1);

    QLabel *lblEtat = new QLabel("✅ Température Interne (°C)");
    lblEtat->setStyleSheet(labelStyle);
    grid2->addWidget(lblEtat, 2, 0);
    grid2->addWidget(etatConteneur, 2, 1);

    QLabel *lblDate = new QLabel("📅 Date Dernière Collecte");
    lblDate->setStyleSheet(labelStyle);
    grid2->addWidget(lblDate, 3, 0);
    grid2->addWidget(dateDerniereCollecte, 3, 1);

    QLabel *lblTypes = new QLabel("♻️ Types de Déchets Acceptés:");
    lblTypes->setStyleSheet(labelStyle);
    grid2->addWidget(lblTypes, 4, 0);
    grid2->addWidget(typesDechet, 4, 1);

    scrollLayout->addLayout(grid2);

    scrollArea->setWidget(scrollWidget);

    // ===== ScrollBar Style =====
    scrollArea->verticalScrollBar()->setStyleSheet(
        "QScrollBar:vertical {"
        "background:#F3F4F6;"
        "width:10px;"
        "border-radius:5px;"
        "}"
        "QScrollBar::handle:vertical {"
        "background:#D1D5DB;"
        "border-radius:5px;"
        "min-height:30px;"
        "}"
        "QScrollBar::handle:vertical:hover {"
        "background:#9CA3AF;"
        "}"
        "QScrollBar::add-line:vertical,"
        "QScrollBar::sub-line:vertical {"
        "height:0px;"
        "}"
        );

    containerLayout->addWidget(scrollArea);
    containerLayout->addSpacing(15);

    QLabel *note = new QLabel("* Tous les champs sont obligatoires");
    note->setStyleSheet("color:#6E7F91; font-style:italic; font-size:12px;");
    containerLayout->addWidget(note);

    // ===== BOUTONS =====
    QHBoxLayout *btnLayout = new QHBoxLayout();
    btnLayout->setSpacing(15);

    QPushButton *annuler = new QPushButton("✗ Annuler");
    annuler->setMinimumHeight(50);
    annuler->setStyleSheet(
        "QPushButton {"
        "background-color:#E5E7EB;"
        "color:#374151;"
        "font-size:15px;"
        "font-weight:600;"
        "border:none;"
        "border-radius:8px;"
        "padding:12px 30px;"
        "}"
        "QPushButton:hover { background-color:#D1D5DB; }"
        );

    QPushButton *ajouter = new QPushButton("✓ Ajouter");
    ajouter->setMinimumHeight(50);
    ajouter->setStyleSheet(
        "QPushButton {"
        "background:qlineargradient("
        "x1:0,y1:0,x2:0,y2:1,"
        "stop:0 #2C5F7C,"
        "stop:1 #1B3A57);"
        "color:white;"
        "font-size:15px;"
        "font-weight:600;"
        "border:none;"
        "border-radius:8px;"
        "padding:12px 30px;"
        "}"
        "QPushButton:hover {"
        "background:qlineargradient("
        "x1:0,y1:0,x2:0,y2:1,"
        "stop:0 #3A6EA5,"
        "stop:1 #2C5F7C);"
        "}"
        );

    btnLayout->addWidget(annuler);
    btnLayout->addWidget(ajouter);

    containerLayout->addLayout(btnLayout);
    mainLayout->addWidget(container);

    connect(annuler, &QPushButton::clicked, dialog, &QDialog::reject);

    dialog->exec();
}
void MainWindow::on_bouton_ajouter_employe_clicked()  // ← Ajoutez "void MainWindow::"
{
    afficherWidgetAjoutEmploye();
}

void MainWindow::afficherWidgetAjoutEmploye()
{
    QDialog *dialog = new QDialog(this);
    dialog->setWindowTitle("+ Ajouter un Employé");
    dialog->setFixedSize(850, 700);
    dialog->setStyleSheet("QDialog { background-color: #EDEDED; }");

    QVBoxLayout *mainLayout = new QVBoxLayout(dialog);

    QFrame *container = new QFrame();
    container->setStyleSheet(
        "QFrame {"
        "background-color:#F2F2F2;"
        "border-radius:20px;"
        "}"
        );

    QVBoxLayout *containerLayout = new QVBoxLayout(container);
    containerLayout->setContentsMargins(30,30,30,30);

    // ===== TITRE =====
    QLabel *titre = new QLabel("👨‍💼 Informations Employé");
    titre->setAlignment(Qt::AlignCenter);
    titre->setStyleSheet(
        "QLabel {"
        "font-size:20px;"
        "font-weight:bold;"
        "color:white;"
        "padding:20px;"
        "border-radius:18px;"
        "background:qlineargradient("
        "x1:0,y1:0,x2:0,y2:1,"
        "stop:0 #2C5F7C,"
        "stop:1 #1B3A57);"
        "}"
        );

    containerLayout->addWidget(titre);
    containerLayout->addSpacing(20);

    // ===== SCROLL AREA =====
    QScrollArea *scrollArea = new QScrollArea();
    scrollArea->setWidgetResizable(true);
    scrollArea->setFrameShape(QFrame::NoFrame);

    QWidget *scrollWidget = new QWidget();
    scrollWidget->setStyleSheet(
        "background-color:white;"
        "border-radius:15px;"
        );

    QVBoxLayout *scrollLayout = new QVBoxLayout(scrollWidget);
    scrollLayout->setSpacing(20);
    scrollLayout->setContentsMargins(20,20,20,20);

    // ===== STYLES =====
    QString labelStyle =
        "QLabel {"
        "background-color:transparent;"
        "padding:5px;"
        "font-size:13px;"
        "font-weight:600;"
        "color:#374151;"
        "}";

    QString editStyle =
        "QLineEdit {"
        "background-color:#F9FAFB;"
        "border:1px solid #D1D5DB;"
        "border-radius:8px;"
        "padding:12px 16px;"
        "font-size:14px;"
        "color:#111827;"
        "}"
        "QLineEdit:hover {"
        "border:1px solid #2C5F7C;"
        "background-color:#FFFFFF;"
        "}"
        "QLineEdit:focus {"
        "border:2px solid #2C5F7C;"
        "background-color:#FFFFFF;"
        "padding:11px 15px;"
        "}";

    QString comboStyle =
        "QComboBox {"
        "background-color:#F9FAFB;"
        "border:1px solid #D1D5DB;"
        "border-radius:8px;"
        "padding:12px 16px;"
        "font-size:14px;"
        "color:#111827;"
        "}"
        "QComboBox:hover {"
        "border:1px solid #2C5F7C;"
        "background-color:#FFFFFF;"
        "}"
        "QComboBox:focus {"
        "border:2px solid #2C5F7C;"
        "background-color:#FFFFFF;"
        "}"
        "QComboBox QAbstractItemView {"
        "background-color:#FFFFFF;"
        "border:1px solid #D1D5DB;"
        "border-radius:8px;"
        "selection-background-color:#3A6EA5;"
        "selection-color:white;"
        "}";

    auto addField = [&](QString text, QWidget *field)
    {
        QLabel *label = new QLabel(text);
        label->setStyleSheet(labelStyle);
        scrollLayout->addWidget(label);

        field->setStyleSheet(editStyle);
        scrollLayout->addWidget(field);
    };

    // ===== CHAMPS EMPLOYÉ =====
    QLineEdit *nom = new QLineEdit();
    QLineEdit *prenom = new QLineEdit();
    QLineEdit *email = new QLineEdit();
    QLineEdit *telephone = new QLineEdit();
    QLineEdit *cin = new QLineEdit();

    QComboBox *poste = new QComboBox();
    poste->addItems({"Technicien","Administratif","Manager","Agent terrain"});
    poste->setStyleSheet(comboStyle);

    addField("👤 Nom *", nom);
    addField("👤 Prénom *", prenom);

    QLabel *lblPoste = new QLabel("💼 Poste *");
    lblPoste->setStyleSheet(labelStyle);
    scrollLayout->addWidget(lblPoste);
    scrollLayout->addWidget(poste);

    addField("📧 Email *", email);
    addField("📞 Téléphone *", telephone);
    addField("🆔 CIN", cin);

    scrollArea->setWidget(scrollWidget);

    // ===== ScrollBar Style =====
    scrollArea->verticalScrollBar()->setStyleSheet(
        "QScrollBar:vertical {"
        "background:#F3F4F6;"
        "width:10px;"
        "border-radius:5px;"
        "}"
        "QScrollBar::handle:vertical {"
        "background:#D1D5DB;"
        "border-radius:5px;"
        "min-height:30px;"
        "}"
        "QScrollBar::handle:vertical:hover {"
        "background:#9CA3AF;"
        "}"
        "QScrollBar::add-line:vertical,"
        "QScrollBar::sub-line:vertical {"
        "height:0px;"
        "}"
        );

    containerLayout->addWidget(scrollArea);
    containerLayout->addSpacing(15);

    QLabel *note = new QLabel("* Champs obligatoires");
    note->setStyleSheet("color:#6E7F91; font-style:italic; font-size:12px;");
    containerLayout->addWidget(note);

    // ===== BOUTONS =====
    QHBoxLayout *btnLayout = new QHBoxLayout();
    btnLayout->setSpacing(15);

    QPushButton *annuler = new QPushButton("✗ Annuler");
    annuler->setMinimumHeight(50);
    annuler->setStyleSheet(
        "QPushButton {"
        "background-color:#E5E7EB;"
        "color:#374151;"
        "font-size:15px;"
        "font-weight:600;"
        "border:none;"
        "border-radius:8px;"
        "padding:12px 30px;"
        "}"
        "QPushButton:hover { background-color:#D1D5DB; }"
        );

    QPushButton *ajouter = new QPushButton("✓ Ajouter l'employé");
    ajouter->setMinimumHeight(50);
    ajouter->setStyleSheet(
        "QPushButton {"
        "background:qlineargradient("
        "x1:0,y1:0,x2:0,y2:1,"
        "stop:0 #2C5F7C,"
        "stop:1 #1B3A57);"
        "color:white;"
        "font-size:15px;"
        "font-weight:600;"
        "border:none;"
        "border-radius:8px;"
        "padding:12px 30px;"
        "}"
        "QPushButton:hover {"
        "background:qlineargradient("
        "x1:0,y1:0,x2:0,y2:1,"
        "stop:0 #3A6EA5,"
        "stop:1 #2C5F7C);"
        "}"
        );

    btnLayout->addWidget(annuler);
    btnLayout->addWidget(ajouter);

    containerLayout->addLayout(btnLayout);
    mainLayout->addWidget(container);

    connect(annuler, &QPushButton::clicked, dialog, &QDialog::reject);

    dialog->exec();
}
