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
#include <QTableWidget>
#include <QHeaderView>
#include <QMessageBox>
#include <QFileDialog>
#include <QPdfWriter>
#include <QPainter>
#include <QPageSize>
#include <QMarginsF>
#include <QDate>
#include <QTime>

// ============================================
// CONSTRUCTEUR ET DESTRUCTEUR
// ============================================

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Initialiser les modules
    initialiserInterfaceRecyclage();
    chargerDonneesExemplesRecyclage();

    initialiserInterfaceConteneur();
    chargerDonneesExemplesConteneur();
}

MainWindow::~MainWindow()
{
    delete ui;
}

// ============================================
// MODULE RECYCLAGE - INITIALISATION
// ============================================

void MainWindow::initialiserInterfaceRecyclage()
{
    configurerTableauRecyclage();
}

void MainWindow::configurerTableauRecyclage()
{
    // Configuration du tableau si présent dans l'UI
    if (ui->tableWidget_recyclage) {
        ui->tableWidget_recyclage->setStyleSheet(
            "QTableWidget {"
            "    background-color: white;"
            "    border: 2px solid #E0E7EE;"
            "    border-radius: 12px;"
            "    gridline-color: #E0E7EE;"
            "    selection-background-color: #D6E9F8;"
            "    selection-color: #0A1F33;"
            "    font-size: 13px;"
            "}"
            "QTableWidget::item {"
            "    padding: 12px 8px;"
            "    color: #2A3439;"
            "    border-bottom: 1px solid #F0F4F8;"
            "}"
            "QTableWidget::item:selected {"
            "    background-color: #D6E9F8;"
            "    color: #0A1F33;"
            "}"
            "QHeaderView::section {"
            "    background-color: qlineargradient("
            "        x1:0, y1:0, x2:0, y2:1,"
            "        stop:0 #3A6EA5, stop:1 #2C5F7C"
            "    );"
            "    color: white;"
            "    padding: 12px 8px;"
            "    border: none;"
            "    font-weight: bold;"
            "    font-size: 14px;"
            "}"
            "QTableWidget::item:hover {"
            "    background-color: #EBF4FB;"
            "}"
            );

        ui->tableWidget_recyclage->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
        ui->tableWidget_recyclage->setAlternatingRowColors(true);
        ui->tableWidget_recyclage->setShowGrid(true);
        ui->tableWidget_recyclage->verticalHeader()->setDefaultSectionSize(45);
        ui->tableWidget_recyclage->setRowCount(0);
    }
}

void MainWindow::chargerDonneesExemplesRecyclage()
{
    recyclageData.clear();

    RecyclageData rec1;
    rec1.id = 1;
    rec1.materiau = "Plastique PET";
    rec1.qteEntree = 500.0;
    rec1.qteRecyclee = 450.0;
    rec1.qteRejetee = 50.0;
    rec1.taux = 90.0;
    rec1.destination = "Usine de recyclage Tunis";
    rec1.valeur = 2250.0;
    recyclageData.append(rec1);

    RecyclageData rec2;
    rec2.id = 2;
    rec2.materiau = "Carton";
    rec2.qteEntree = 800.0;
    rec2.qteRecyclee = 720.0;
    rec2.qteRejetee = 80.0;
    rec2.taux = 90.0;
    rec2.destination = "Centre de tri Manouba";
    rec2.valeur = 1440.0;
    recyclageData.append(rec2);

    RecyclageData rec3;
    rec3.id = 3;
    rec3.materiau = "Verre";
    rec3.qteEntree = 300.0;
    rec3.qteRecyclee = 285.0;
    rec3.qteRejetee = 15.0;
    rec3.taux = 95.0;
    rec3.destination = "Verrerie de Sfax";
    rec3.valeur = 1425.0;
    recyclageData.append(rec3);

    // Remplir le tableau si présent
    if (ui->tableWidget_recyclage) {
        ui->tableWidget_recyclage->setRowCount(recyclageData.size());
        for (int i = 0; i < recyclageData.size(); ++i) {
            ui->tableWidget_recyclage->setItem(i, 0, new QTableWidgetItem(QString::number(recyclageData[i].id)));
            ui->tableWidget_recyclage->setItem(i, 1, new QTableWidgetItem(recyclageData[i].materiau));
            ui->tableWidget_recyclage->setItem(i, 2, new QTableWidgetItem(QString::number(recyclageData[i].qteEntree)));
            ui->tableWidget_recyclage->setItem(i, 3, new QTableWidgetItem(QString::number(recyclageData[i].qteRecyclee)));
            ui->tableWidget_recyclage->setItem(i, 4, new QTableWidgetItem(QString::number(recyclageData[i].qteRejetee)));
            ui->tableWidget_recyclage->setItem(i, 5, new QTableWidgetItem(QString::number(recyclageData[i].taux)));
            ui->tableWidget_recyclage->setItem(i, 6, new QTableWidgetItem(recyclageData[i].destination));
            ui->tableWidget_recyclage->setItem(i, 7, new QTableWidgetItem(QString::number(recyclageData[i].valeur)));
        }
    }
}

// ============================================
// MODULE RECYCLAGE - SLOT AJOUTER
// ============================================

void MainWindow::on_pushButton_recyclage_ajouter_clicked()
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
    QLabel *lblId = new QLabel("🆔 ID:");
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

    QLabel *lblQteRecyclee = new QLabel("📊 Quantité recyclée (kg):");
    lblQteRecyclee->setStyleSheet(labelStyle);
    gridLayout->addWidget(lblQteRecyclee, 3, 0);
    gridLayout->addWidget(qteRecyclee, 3, 1);

    // Colonne droite
    QLabel *lblQteRejetee = new QLabel("📊 Quantité rejetée (kg):");
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

    QLabel *lblValeur = new QLabel("💰 Valeur (TND):");
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

    connect(ajouter, &QPushButton::clicked, [=]() {
        RecyclageData nouvelleOp;
        nouvelleOp.id = id->text().toInt();
        nouvelleOp.materiau = materiau->text();
        nouvelleOp.qteEntree = qteEntree->text().toDouble();
        nouvelleOp.qteRecyclee = qteRecyclee->text().toDouble();
        nouvelleOp.qteRejetee = qteRejetee->text().toDouble();
        nouvelleOp.taux = taux->text().toDouble();
        nouvelleOp.destination = destination->text();
        nouvelleOp.valeur = valeur->text().toDouble();

        recyclageData.append(nouvelleOp);

        if (ui->tableWidget_recyclage) {
            int row = ui->tableWidget_recyclage->rowCount();
            ui->tableWidget_recyclage->insertRow(row);
            ui->tableWidget_recyclage->setItem(row, 0, new QTableWidgetItem(QString::number(nouvelleOp.id)));
            ui->tableWidget_recyclage->setItem(row, 1, new QTableWidgetItem(nouvelleOp.materiau));
            ui->tableWidget_recyclage->setItem(row, 2, new QTableWidgetItem(QString::number(nouvelleOp.qteEntree)));
            ui->tableWidget_recyclage->setItem(row, 3, new QTableWidgetItem(QString::number(nouvelleOp.qteRecyclee)));
            ui->tableWidget_recyclage->setItem(row, 4, new QTableWidgetItem(QString::number(nouvelleOp.qteRejetee)));
            ui->tableWidget_recyclage->setItem(row, 5, new QTableWidgetItem(QString::number(nouvelleOp.taux)));
            ui->tableWidget_recyclage->setItem(row, 6, new QTableWidgetItem(nouvelleOp.destination));
            ui->tableWidget_recyclage->setItem(row, 7, new QTableWidgetItem(QString::number(nouvelleOp.valeur)));
        }

        QMessageBox::information(dialog, "Succès", "✓ Opération de recyclage ajoutée avec succès!");
        dialog->accept();
    });

    dialog->exec();
    delete dialog;
}

// ============================================
// MODULE RECYCLAGE - AUTRES SLOTS
// ============================================

void MainWindow::on_pushButton_recyclage_modifier_clicked()
{
    QMessageBox::information(this, "Recyclage", "Fonction Modification - À implémenter");
}

void MainWindow::on_pushButton_recyclage_supprimer_clicked()
{
    if (ui->tableWidget_recyclage) {
        int row = ui->tableWidget_recyclage->currentRow();
        if (row >= 0) {
            ui->tableWidget_recyclage->removeRow(row);
            recyclageData.removeAt(row);
            QMessageBox::information(this, "Succès", "Opération supprimée!");
        } else {
            QMessageBox::warning(this, "Attention", "Veuillez sélectionner une ligne!");
        }
    }
}

void MainWindow::on_pushButton_recyclage_rechercher_clicked()
{
    QMessageBox::information(this, "Recyclage", "Fonction Recherche - À implémenter");
}

void MainWindow::on_pushButton_recyclage_exporter_clicked()
{
    QMessageBox::information(this, "Recyclage", "Fonction Export PDF - À implémenter");
}

void MainWindow::on_pushButton_recyclage_stats_clicked()
{
    QMessageBox::information(this, "Recyclage", "Fonction Statistiques - À implémenter");
}

void MainWindow::afficherWidgetModificationRecyclage()
{
    // À implémenter
}

void MainWindow::supprimerRecyclage()
{
    // À implémenter
}

void MainWindow::rechercherRecyclage()
{
    // À implémenter
}

void MainWindow::exporterVersPDFRecyclage()
{
    // À implémenter
}

void MainWindow::afficherWidgetStatistiquesRecyclage()
{
    // À implémenter
}

// ============================================
// MODULE CONTENEURS - INITIALISATION
// ============================================

void MainWindow::initialiserInterfaceConteneur()
{
    configurerTableauConteneur();
}

void MainWindow::configurerTableauConteneur()
{
    // Configuration du tableau si présent dans l'UI
    if (ui->tableWidget_conteneurs) {
        ui->tableWidget_conteneurs->setStyleSheet(
            "QTableWidget {"
            "    background-color: white;"
            "    border: 2px solid #E0E7EE;"
            "    border-radius: 12px;"
            "    gridline-color: #E0E7EE;"
            "    selection-background-color: #D6E9F8;"
            "    selection-color: #0A1F33;"
            "    font-size: 13px;"
            "}"
            "QTableWidget::item {"
            "    padding: 12px 8px;"
            "    color: #2A3439;"
            "    border-bottom: 1px solid #F0F4F8;"
            "}"
            "QTableWidget::item:selected {"
            "    background-color: #D6E9F8;"
            "    color: #0A1F33;"
            "}"
            "QHeaderView::section {"
            "    background-color: qlineargradient("
            "        x1:0, y1:0, x2:0, y2:1,"
            "        stop:0 #3A6EA5, stop:1 #2C5F7C"
            "    );"
            "    color: white;"
            "    padding: 12px 8px;"
            "    border: none;"
            "    font-weight: bold;"
            "    font-size: 14px;"
            "}"
            "QTableWidget::item:hover {"
            "    background-color: #EBF4FB;"
            "}"
            );

        ui->tableWidget_conteneurs->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
        ui->tableWidget_conteneurs->setAlternatingRowColors(true);
        ui->tableWidget_conteneurs->setShowGrid(true);
        ui->tableWidget_conteneurs->verticalHeader()->setDefaultSectionSize(45);
        ui->tableWidget_conteneurs->setRowCount(0);
    }
}

void MainWindow::chargerDonneesExemplesConteneur()
{
    conteneursData.clear();

    ConteneurData cont1;
    cont1.id = 1;
    cont1.capacite = "1000 L";
    cont1.localisation = "Tunis Centre";
    cont1.adresseComplete = "Avenue Habib Bourguiba, Tunis";
    cont1.latitude = 36.8065;
    cont1.longitude = 10.1815;
    cont1.typePropriete = "Public";
    cont1.niveauRemplissage = 75;
    cont1.temperature = 22.5;
    cont1.etatConteneur = "Opérationnel";
    cont1.dateDerniereCollecte = "10/02/2026";
    cont1.typesDechet = "Plastique, Papier";
    conteneursData.append(cont1);

    ConteneurData cont2;
    cont2.id = 2;
    cont2.capacite = "1500 L";
    cont2.localisation = "Ariana";
    cont2.adresseComplete = "Centre Ville Ariana";
    cont2.latitude = 36.8625;
    cont2.longitude = 10.1956;
    cont2.typePropriete = "Public";
    cont2.niveauRemplissage = 45;
    cont2.temperature = 20.0;
    cont2.etatConteneur = "Opérationnel";
    cont2.dateDerniereCollecte = "12/02/2026";
    cont2.typesDechet = "Organique";
    conteneursData.append(cont2);

    // Remplir le tableau si présent
    if (ui->tableWidget_conteneurs) {
        ui->tableWidget_conteneurs->setRowCount(conteneursData.size());
        for (int i = 0; i < conteneursData.size(); ++i) {
            ui->tableWidget_conteneurs->setItem(i, 0, new QTableWidgetItem(QString::number(conteneursData[i].id)));
            ui->tableWidget_conteneurs->setItem(i, 1, new QTableWidgetItem(conteneursData[i].capacite));
            ui->tableWidget_conteneurs->setItem(i, 2, new QTableWidgetItem(conteneursData[i].localisation));
            ui->tableWidget_conteneurs->setItem(i, 3, new QTableWidgetItem(conteneursData[i].typePropriete));
            ui->tableWidget_conteneurs->setItem(i, 4, new QTableWidgetItem(QString::number(conteneursData[i].niveauRemplissage)));
            ui->tableWidget_conteneurs->setItem(i, 5, new QTableWidgetItem(conteneursData[i].etatConteneur));
            ui->tableWidget_conteneurs->setItem(i, 6, new QTableWidgetItem(conteneursData[i].dateDerniereCollecte));
        }
    }
}

// ============================================
// MODULE CONTENEURS - SLOT AJOUTER
// ============================================

void MainWindow::on_pushButton_conteneur_ajouter_clicked()
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
    latitude->setValue(36.8065);
    QDoubleSpinBox *longitude = new QDoubleSpinBox();
    longitude->setDecimals(6);
    longitude->setRange(-180, 180);
    longitude->setValue(10.1815);
    QComboBox *typePropriete = new QComboBox();
    typePropriete->addItems({"Public", "Privé", "Mixte"});

    capacite->setStyleSheet(editStyle);
    localisation->setStyleSheet(editStyle);
    adresseComplete->setStyleSheet(editStyle);
    latitude->setStyleSheet(editStyle);
    longitude->setStyleSheet(editStyle);
    typePropriete->setStyleSheet(editStyle);

    QLabel *lblCapacite = new QLabel("📦 Capacité:");
    lblCapacite->setStyleSheet(labelStyle);
    grid1->addWidget(lblCapacite, 0, 0);
    grid1->addWidget(capacite, 0, 1);

    QLabel *lblLocalisation = new QLabel("📍 Localisation:");
    lblLocalisation->setStyleSheet(labelStyle);
    grid1->addWidget(lblLocalisation, 1, 0);
    grid1->addWidget(localisation, 1, 1);

    QLabel *lblAdresse = new QLabel("🏠 Adresse complète:");
    lblAdresse->setStyleSheet(labelStyle);
    grid1->addWidget(lblAdresse, 2, 0);
    grid1->addWidget(adresseComplete, 2, 1);

    QLabel *lblLatitude = new QLabel("🌍 Latitude:");
    lblLatitude->setStyleSheet(labelStyle);
    grid1->addWidget(lblLatitude, 3, 0);
    grid1->addWidget(latitude, 3, 1);

    QLabel *lblLongitude = new QLabel("🌍 Longitude:");
    lblLongitude->setStyleSheet(labelStyle);
    grid1->addWidget(lblLongitude, 4, 0);
    grid1->addWidget(longitude, 4, 1);

    QLabel *lblTypePropriete = new QLabel("🏢 Type de Propriété:");
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

    QDateEdit *dateDerniereCollecte = new QDateEdit(QDate::currentDate());
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

    QLabel *lblEtat = new QLabel("✅ État du Conteneur");
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

    connect(ajouter, &QPushButton::clicked, [=]() {
        ConteneurData nouveauCont;
        nouveauCont.id = conteneursData.size() + 1;
        nouveauCont.capacite = capacite->text();
        nouveauCont.localisation = localisation->text();
        nouveauCont.adresseComplete = adresseComplete->text();
        nouveauCont.latitude = latitude->value();
        nouveauCont.longitude = longitude->value();
        nouveauCont.typePropriete = typePropriete->currentText();
        nouveauCont.niveauRemplissage = niveauRemplissage->value();
        nouveauCont.temperature = temperature->value();
        nouveauCont.etatConteneur = etatConteneur->currentText();
        nouveauCont.dateDerniereCollecte = dateDerniereCollecte->date().toString("dd/MM/yyyy");
        nouveauCont.typesDechet = typesDechet->text();

        conteneursData.append(nouveauCont);

        if (ui->tableWidget_conteneurs) {
            int row = ui->tableWidget_conteneurs->rowCount();
            ui->tableWidget_conteneurs->insertRow(row);
            ui->tableWidget_conteneurs->setItem(row, 0, new QTableWidgetItem(QString::number(nouveauCont.id)));
            ui->tableWidget_conteneurs->setItem(row, 1, new QTableWidgetItem(nouveauCont.capacite));
            ui->tableWidget_conteneurs->setItem(row, 2, new QTableWidgetItem(nouveauCont.localisation));
            ui->tableWidget_conteneurs->setItem(row, 3, new QTableWidgetItem(nouveauCont.typePropriete));
            ui->tableWidget_conteneurs->setItem(row, 4, new QTableWidgetItem(QString::number(nouveauCont.niveauRemplissage)));
            ui->tableWidget_conteneurs->setItem(row, 5, new QTableWidgetItem(nouveauCont.etatConteneur));
            ui->tableWidget_conteneurs->setItem(row, 6, new QTableWidgetItem(nouveauCont.dateDerniereCollecte));
        }

        QMessageBox::information(dialog, "Succès", "✓ Conteneur ajouté avec succès!");
        dialog->accept();
    });

    dialog->exec();
    delete dialog;
}

// ============================================
// MODULE CONTENEURS - AUTRES SLOTS
// ============================================

void MainWindow::on_pushButton_conteneur_modifier_clicked()
{
    QMessageBox::information(this, "Conteneurs", "Fonction Modification - À implémenter");
}

void MainWindow::on_pushButton_conteneur_supprimer_clicked()
{
    if (ui->tableWidget_conteneurs) {
        int row = ui->tableWidget_conteneurs->currentRow();
        if (row >= 0) {
            ui->tableWidget_conteneurs->removeRow(row);
            conteneursData.removeAt(row);
            QMessageBox::information(this, "Succès", "Conteneur supprimé!");
        } else {
            QMessageBox::warning(this, "Attention", "Veuillez sélectionner une ligne!");
        }
    }
}

void MainWindow::on_pushButton_conteneur_rechercher_clicked()
{
    QMessageBox::information(this, "Conteneurs", "Fonction Recherche - À implémenter");
}

void MainWindow::on_pushButton_conteneur_exporter_clicked()
{
    QMessageBox::information(this, "Conteneurs", "Fonction Export PDF - À implémenter");
}

void MainWindow::on_pushButton_conteneur_stats_clicked()
{
    QMessageBox::information(this, "Conteneurs", "Fonction Statistiques - À implémenter");
}

void MainWindow::afficherWidgetModificationConteneur()
{
    // À implémenter
}

void MainWindow::supprimerConteneur()
{
    // À implémenter
}

void MainWindow::rechercherConteneur()
{
    // À implémenter
}

void MainWindow::exporterVersPDFConteneur()
{
    // À implémenter
}

void MainWindow::afficherWidgetStatistiquesConteneur()
{
    // À implémenter
}
