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
}

MainWindow::~MainWindow()
{
    delete ui;
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
