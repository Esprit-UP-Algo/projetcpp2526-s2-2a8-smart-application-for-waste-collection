#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPainter>
#include <QFile>
#include <QPdfWriter>
#include <QTextDocument>
#include <QInputDialog>
#include <QRandomGenerator>
#include <QHeaderView>
#include <QProgressBar>
#include <QScrollArea>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Initialiser l'interface
    initialiserInterface();

    // Charger des données d'exemple
    chargerDonneesExemples();

    // Configurer le combobox de tri
    ui->comboTypePropriete_3->clear();
    ui->comboTypePropriete_3->addItem("📊 Trier par...");
    ui->comboTypePropriete_3->addItem("ID");
    ui->comboTypePropriete_3->addItem("Nom");
    ui->comboTypePropriete_3->addItem("Type");
    ui->comboTypePropriete_3->addItem("Zone");
    ui->comboTypePropriete_3->addItem("Statut");

    // Configurer le lineEdit de recherche
    ui->lineEdit_8->setPlaceholderText("🔍 Rechercher un client (nom, téléphone, CIN)...");
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::initialiserInterface()
{
    // Masquer le frame_46 complètement (on utilise des popups à la place)
    ui->frame_46->setVisible(false);
    ui->frame_46->setEnabled(false);

    // Configurer le tableau pour un meilleur affichage
    configurerTableau();
}

void MainWindow::configurerTableau()
{
    // Améliorer l'affichage du tableau
    ui->tableWidget_3->setStyleSheet(
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
        "        x1:0, y1:0,"
        "        x2:0, y2:1,"
        "        stop:0 #3A6EA5,"
        "        stop:1 #2C5F7C"
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

    // Ajuster les colonnes pour mieux répartir l'espace
    ui->tableWidget_3->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableWidget_3->setAlternatingRowColors(true);
    ui->tableWidget_3->setShowGrid(true);

    // Ajuster la hauteur des lignes
    ui->tableWidget_3->verticalHeader()->setDefaultSectionSize(45);

    // Vider les lignes par défaut du designer
    ui->tableWidget_3->setRowCount(0);
}

void MainWindow::chargerDonneesExemples()
{
    // Ajouter des données d'exemple
    clientsData.clear();

    ClientData client1;
    client1.id = 1;
    client1.nom = "Ben Salah";
    client1.prenom = "Ali";
    client1.type = "Résidentiel";
    client1.zone = "Tunis Centre";
    client1.telephone = "26263207";
    client1.statut = "Actif";
    client1.cin = "12345678";
    clientsData.append(client1);

    ClientData client2;
    client2.id = 2;
    client2.nom = "Monoprix";
    client2.prenom = "";
    client2.type = "Commerce";
    client2.zone = "Manouba";
    client2.telephone = "26760046";
    client2.statut = "Actif";
    client2.cin = "N/A";
    clientsData.append(client2);

    ClientData client3;
    client3.id = 3;
    client3.nom = "Trabelsi";
    client3.prenom = "Fatma";
    client3.type = "Résidentiel";
    client3.zone = "Ariana";
    client3.telephone = "98765432";
    client3.statut = "Inactif";
    client3.cin = "87654321";
    clientsData.append(client3);

    ClientData client4;
    client4.id = 4;
    client4.nom = "Carrefour";
    client4.prenom = "";
    client4.type = "Commerce";
    client4.zone = "Sousse";
    client4.telephone = "73123456";
    client4.statut = "Actif";
    client4.cin = "N/A";
    clientsData.append(client4);

    ClientData client5;
    client5.id = 5;
    client5.nom = "Hamdi";
    client5.prenom = "Mohamed";
    client5.type = "Industriel";
    client5.zone = "Ben Arous";
    client5.telephone = "71234567";
    client5.statut = "Actif";
    client5.cin = "11223344";
    clientsData.append(client5);

    ClientData client6;
    client6.id = 6;
    client6.nom = "Auchan";
    client6.prenom = "";
    client6.type = "Commerce";
    client6.zone = "Tunis Centre";
    client6.telephone = "71555666";
    client6.statut = "Actif";
    client6.cin = "N/A";
    clientsData.append(client6);

    ClientData client7;
    client7.id = 7;
    client7.nom = "Jemli";
    client7.prenom = "Sarra";
    client7.type = "Résidentiel";
    client7.zone = "La Marsa";
    client7.telephone = "22334455";
    client7.statut = "Actif";
    client7.cin = "99887766";
    clientsData.append(client7);

    // Remplir le tableau avec les données
    ui->tableWidget_3->setRowCount(clientsData.size());
    for (int i = 0; i < clientsData.size(); ++i) {
        ui->tableWidget_3->setItem(i, 0, new QTableWidgetItem(QString::number(clientsData[i].id)));
        ui->tableWidget_3->setItem(i, 1, new QTableWidgetItem(clientsData[i].nom));
        ui->tableWidget_3->setItem(i, 2, new QTableWidgetItem(clientsData[i].prenom));
        ui->tableWidget_3->setItem(i, 3, new QTableWidgetItem(clientsData[i].type));
        ui->tableWidget_3->setItem(i, 4, new QTableWidgetItem(clientsData[i].zone));
        ui->tableWidget_3->setItem(i, 5, new QTableWidgetItem(clientsData[i].telephone));
        ui->tableWidget_3->setItem(i, 6, new QTableWidgetItem(clientsData[i].statut));
    }
}

void MainWindow::on_pushButton_client_ajouter_clicked()
{
    // Afficher le widget d'ajout comme popup (comme le widget de modification)
    afficherWidgetAjout();
}

void MainWindow::afficherWidgetAjout()
{
    // Créer un dialog pour l'ajout (même style que le dialog de modification)
    QDialog *dialog = new QDialog(this);
    dialog->setWindowTitle("➕ Ajouter un Client");
    dialog->setFixedSize(650, 800);  // Taille augmentée pour plus d'espace
    dialog->setStyleSheet("QDialog { background-color: #F5F7FA; }");

    QVBoxLayout *mainLayout = new QVBoxLayout(dialog);
    mainLayout->setSpacing(0);
    mainLayout->setContentsMargins(0, 0, 0, 0);

    // Frame conteneur avec fond blanc
    QFrame *containerFrame = new QFrame(dialog);
    containerFrame->setStyleSheet("QFrame { background-color: white; border-radius: 15px; }");
    QVBoxLayout *containerLayout = new QVBoxLayout(containerFrame);
    containerLayout->setSpacing(20);
    containerLayout->setContentsMargins(30, 25, 30, 25);

    // Titre avec fond dégradé
    QLabel *titre = new QLabel("👤 Informations Personnelles", containerFrame);
    titre->setStyleSheet(
        "font-size: 20px; font-weight: bold; padding: 20px; "
        "background-color: qlineargradient(x1:0, y1:0, x2:0, y2:1, "
        "stop:0 #276646, stop:0.5 #34885A, stop:1 #1B3A2F); "
        "color: white; border-radius: 12px;"
        );
    titre->setAlignment(Qt::AlignCenter);
    titre->setMinimumHeight(60);
    containerLayout->addWidget(titre);

    // Créer un scroll area pour les champs
    QScrollArea *scrollArea = new QScrollArea(containerFrame);
    scrollArea->setWidgetResizable(true);
    scrollArea->setFrameShape(QFrame::NoFrame);
    scrollArea->setStyleSheet("QScrollArea { background-color: transparent; border: none; }");

    QWidget *scrollWidget = new QWidget();
    QVBoxLayout *scrollLayout = new QVBoxLayout(scrollWidget);
    scrollLayout->setSpacing(18);  // Espacement augmenté
    scrollLayout->setContentsMargins(10, 10, 10, 10);

    // Style pour les labels - TAILLE AUGMENTÉE
    QString labelStyle =
        "font-size: 15px; "           // Taille de police augmentée
        "color: #2A3439; "
        "font-weight: 600; "
        "padding: 8px 0px;";

    // Style pour les champs de saisie
    QString editStyle =
        "QLineEdit { "
        "    background-color: #F9FBFD; "
        "    border: 2px solid #D1DCE5; "
        "    border-radius: 10px; "
        "    padding: 14px 16px; "    // Padding augmenté
        "    font-size: 15px; "       // Taille de police augmentée
        "    color: #2A3439; "
        "    min-height: 20px; "
        "}"
        "QLineEdit:focus { "
        "    background-color: white; "
        "    border: 2px solid #3A6EA5; "
        "}";

    // Style pour les combobox
    QString comboStyle =
        "QComboBox { "
        "    background-color: #1F3B5C; "
        "    color: #EAF3FF; "
        "    border: 2px solid #3F6FA5; "
        "    border-radius: 10px; "
        "    padding: 14px 16px; "    // Padding augmenté
        "    font-size: 15px; "       // Taille de police augmentée
        "    min-height: 20px; "
        "}"
        "QComboBox::drop-down { "
        "    subcontrol-origin: padding; "
        "    subcontrol-position: top right; "
        "    width: 30px; "
        "    border-left: 2px solid #3F6FA5; "
        "}"
        "QComboBox QAbstractItemView { "
        "    background-color: #203A57; "
        "    color: #EAF3FF; "
        "    selection-background-color: #2F5F99; "
        "    selection-color: #FFFFFF; "
        "    outline: 0; "
        "    border-radius: 6px; "
        "    font-size: 14px; "
        "}";

    // Fonction helper pour ajouter un champ avec label plus grand
    auto ajouterChamp = [&](const QString &labelText, QLineEdit *&edit) {
        QLabel *lbl = new QLabel(labelText);
        lbl->setStyleSheet(labelStyle);
        lbl->setMinimumHeight(30);  // Hauteur minimale pour le label

        edit = new QLineEdit();
        edit->setStyleSheet(editStyle);
        edit->setMinimumHeight(50);  // Hauteur minimale augmentée

        scrollLayout->addWidget(lbl);
        scrollLayout->addWidget(edit);
    };

    QLineEdit *nomEdit, *prenomEdit, *zoneEdit, *telEdit, *cinEdit;

    ajouterChamp("👤 Nom du client *", nomEdit);
    ajouterChamp("👤 Prénom", prenomEdit);

    // Type de client
    QLabel *lblType = new QLabel("🏢 Type de client *");
    lblType->setStyleSheet(labelStyle);
    lblType->setMinimumHeight(30);

    QComboBox *typeCombo = new QComboBox();
    typeCombo->addItems({"Résidentiel", "Commerce", "Industriel", "Public"});
    typeCombo->setStyleSheet(comboStyle);
    typeCombo->setMinimumHeight(50);

    scrollLayout->addWidget(lblType);
    scrollLayout->addWidget(typeCombo);

    ajouterChamp("📍 Zone géographique *", zoneEdit);
    ajouterChamp("📞 Téléphone *", telEdit);
    ajouterChamp("🆔 CIN", cinEdit);

    // Statut
    QLabel *lblStatut = new QLabel("📊 Statut *");
    lblStatut->setStyleSheet(labelStyle);
    lblStatut->setMinimumHeight(30);

    QComboBox *statutCombo = new QComboBox();
    statutCombo->addItems({"Actif", "Inactif", "En attente"});
    statutCombo->setStyleSheet(comboStyle);
    statutCombo->setMinimumHeight(50);

    scrollLayout->addWidget(lblStatut);
    scrollLayout->addWidget(statutCombo);

    scrollWidget->setLayout(scrollLayout);
    scrollArea->setWidget(scrollWidget);
    containerLayout->addWidget(scrollArea);

    // Note pour les champs obligatoires
    QLabel *noteObligatoire = new QLabel("* Champs obligatoires");
    noteObligatoire->setStyleSheet("font-size: 13px; color: #6E7F91; padding: 10px; font-style: italic;");
    containerLayout->addWidget(noteObligatoire);

    // Boutons
    QHBoxLayout *buttonLayout = new QHBoxLayout();
    buttonLayout->setSpacing(20);

    QPushButton *btnValider = new QPushButton("✓ Ajouter le client");
    btnValider->setMinimumHeight(55);  // Hauteur augmentée
    btnValider->setCursor(Qt::PointingHandCursor);
    btnValider->setStyleSheet(
        "QPushButton { "
        "    background-color: qlineargradient(x1:0, y1:0, x2:0, y2:1, "
        "    stop:0 #276646, stop:0.5 #34885A, stop:1 #1B3A2F); "
        "    color: white; "
        "    font-size: 16px; "       // Taille de police augmentée
        "    font-weight: 600; "
        "    border-radius: 12px; "
        "    padding: 14px 28px; "
        "}"
        "QPushButton:hover { "
        "    background-color: qlineargradient(x1:0, y1:0, x2:0, y2:1, "
        "    stop:0 #34885A, stop:1 #276646); "
        "}"
        "QPushButton:pressed { "
        "    background-color: #1B3A2F; "
        "}"
        );

    QPushButton *btnAnnuler = new QPushButton("✗ Annuler");
    btnAnnuler->setMinimumHeight(55);  // Hauteur augmentée
    btnAnnuler->setCursor(Qt::PointingHandCursor);
    btnAnnuler->setStyleSheet(
        "QPushButton { "
        "    background-color: #E8ECF0; "
        "    color: #2A3439; "
        "    font-size: 16px; "       // Taille de police augmentée
        "    font-weight: 600; "
        "    border-radius: 12px; "
        "    padding: 14px 28px; "
        "}"
        "QPushButton:hover { "
        "    background-color: #D1DCE5; "
        "}"
        );

    buttonLayout->addWidget(btnAnnuler);
    buttonLayout->addWidget(btnValider);
    containerLayout->addLayout(buttonLayout);

    mainLayout->addWidget(containerFrame);

    // Connecter les boutons
    connect(btnValider, &QPushButton::clicked, [=]() {
        if (nomEdit->text().isEmpty() || zoneEdit->text().isEmpty() || telEdit->text().isEmpty()) {
            QMessageBox::warning(dialog, "Erreur", "Veuillez remplir tous les champs obligatoires (*)!");
            return;
        }

        // Ajouter le nouveau client
        ClientData nouveauClient;
        nouveauClient.id = clientsData.size() + 1;
        nouveauClient.nom = nomEdit->text();
        nouveauClient.prenom = prenomEdit->text();
        nouveauClient.type = typeCombo->currentText();
        nouveauClient.zone = zoneEdit->text();
        nouveauClient.telephone = telEdit->text();
        nouveauClient.cin = cinEdit->text().isEmpty() ? "N/A" : cinEdit->text();
        nouveauClient.statut = statutCombo->currentText();

        clientsData.append(nouveauClient);

        // Mettre à jour le tableau
        int row = ui->tableWidget_3->rowCount();
        ui->tableWidget_3->insertRow(row);
        ui->tableWidget_3->setItem(row, 0, new QTableWidgetItem(QString::number(nouveauClient.id)));
        ui->tableWidget_3->setItem(row, 1, new QTableWidgetItem(nouveauClient.nom));
        ui->tableWidget_3->setItem(row, 2, new QTableWidgetItem(nouveauClient.prenom));
        ui->tableWidget_3->setItem(row, 3, new QTableWidgetItem(nouveauClient.type));
        ui->tableWidget_3->setItem(row, 4, new QTableWidgetItem(nouveauClient.zone));
        ui->tableWidget_3->setItem(row, 5, new QTableWidgetItem(nouveauClient.telephone));
        ui->tableWidget_3->setItem(row, 6, new QTableWidgetItem(nouveauClient.statut));

        QMessageBox::information(dialog, "Succès", "✓ Client ajouté avec succès!");
        dialog->accept();
    });

    connect(btnAnnuler, &QPushButton::clicked, dialog, &QDialog::reject);

    dialog->exec();
    delete dialog;
}

void MainWindow::on_pushButton_21_clicked()
{
    // Bouton Rechercher - utilise lineEdit_8
    rechercherClient();
}

void MainWindow::rechercherClient()
{
    QString recherche = ui->lineEdit_8->text().trimmed().toLower();

    if (recherche.isEmpty()) {
        // Afficher toutes les lignes si la recherche est vide
        for (int row = 0; row < ui->tableWidget_3->rowCount(); ++row) {
            ui->tableWidget_3->setRowHidden(row, false);
        }
        QMessageBox::information(this, "Recherche", "Affichage de tous les clients.");
        return;
    }

    int resultatsCount = 0;

    // Parcourir le tableau et masquer les lignes qui ne correspondent pas
    for (int row = 0; row < ui->tableWidget_3->rowCount(); ++row) {
        bool match = false;

        for (int col = 0; col < ui->tableWidget_3->columnCount(); ++col) {
            QTableWidgetItem *item = ui->tableWidget_3->item(row, col);
            if (item && item->text().toLower().contains(recherche)) {
                match = true;
                break;
            }
        }

        ui->tableWidget_3->setRowHidden(row, !match);
        if (match) resultatsCount++;
    }

    if (resultatsCount == 0) {
        QMessageBox::information(this, "Recherche", "Aucun résultat trouvé.");
    } else {
        QMessageBox::information(this, "Recherche",
                                 QString("✓ %1 résultat(s) trouvé(s).").arg(resultatsCount));
    }
}

void MainWindow::on_pushButton_20_clicked()
{
    // Bouton Exporter
    exporterVersPDF();
}

void MainWindow::exporterVersPDF()
{
    QString fileName = QFileDialog::getSaveFileName(this, "Exporter en PDF",
                                                    QDir::homePath() + "/clients.pdf",
                                                    "PDF Files (*.pdf)");

    if (fileName.isEmpty())
        return;

    QPdfWriter pdfWriter(fileName);
    pdfWriter.setPageSize(QPageSize::A4);
    pdfWriter.setPageMargins(QMarginsF(20, 20, 20, 20));

    QPainter painter(&pdfWriter);

    // Titre
    QFont titleFont = painter.font();
    titleFont.setPointSize(18);
    titleFont.setBold(true);
    painter.setFont(titleFont);
    painter.drawText(100, 100, "Liste des Clients");

    // En-têtes du tableau
    QFont headerFont = painter.font();
    headerFont.setPointSize(10);
    headerFont.setBold(true);
    painter.setFont(headerFont);

    int y = 300;
    int x = 100;

    painter.drawText(x, y, "ID");
    painter.drawText(x + 100, y, "Nom");
    painter.drawText(x + 250, y, "Prénom");
    painter.drawText(x + 400, y, "Type");

    y += 50;

    // Données
    QFont dataFont = painter.font();
    dataFont.setPointSize(9);
    dataFont.setBold(false);
    painter.setFont(dataFont);

    for (int row = 0; row < ui->tableWidget_3->rowCount() && row < 20; ++row) {
        if (!ui->tableWidget_3->isRowHidden(row)) {
            painter.drawText(x, y, ui->tableWidget_3->item(row, 0) ? ui->tableWidget_3->item(row, 0)->text() : "");
            painter.drawText(x + 100, y, ui->tableWidget_3->item(row, 1) ? ui->tableWidget_3->item(row, 1)->text() : "");
            painter.drawText(x + 250, y, ui->tableWidget_3->item(row, 2) ? ui->tableWidget_3->item(row, 2)->text() : "");
            painter.drawText(x + 400, y, ui->tableWidget_3->item(row, 3) ? ui->tableWidget_3->item(row, 3)->text() : "");
            y += 40;
        }
    }

    painter.end();

    QMessageBox::information(this, "Succès", "✓ Fichier PDF exporté avec succès!");
}

void MainWindow::on_pushButton_19_clicked()
{
    // Bouton Statistique - Afficher un widget bien organisé
    afficherWidgetStatistiques();
}

void MainWindow::afficherWidgetStatistiques()
{
    // Créer un dialog pour les statistiques - TAILLE AUGMENTÉE
    QDialog *dialog = new QDialog(this);
    dialog->setWindowTitle("📊 Statistiques des Clients");
    dialog->setFixedSize(1200, 700);  // Taille augmentée
    dialog->setStyleSheet("QDialog { background-color: #F5F7FA; }");

    QHBoxLayout *mainLayout = new QHBoxLayout(dialog);
    mainLayout->setSpacing(25);
    mainLayout->setContentsMargins(25, 25, 25, 25);

    // === PARTIE GAUCHE : Vue d'ensemble ===
    QFrame *leftFrame = new QFrame(dialog);
    leftFrame->setStyleSheet(
        "QFrame { "
        "    background-color: white; "
        "    border-radius: 20px; "
        "    padding: 30px; "
        "}"
        );
    QVBoxLayout *leftLayout = new QVBoxLayout(leftFrame);
    leftLayout->setSpacing(25);
    leftLayout->setContentsMargins(30, 30, 30, 30);

    // Titre Vue d'ensemble - TAILLE AUGMENTÉE
    QLabel *titreGauche = new QLabel("📊 Vue d'ensemble", leftFrame);
    titreGauche->setStyleSheet(
        "font-size: 26px; "           // Taille augmentée
        "font-weight: bold; "
        "color: #2A3439; "
        "padding-bottom: 15px;"
        );
    titreGauche->setMinimumHeight(50);
    leftLayout->addWidget(titreGauche);

    // Calculer les statistiques réelles
    int totalClients = clientsData.size();
    int clientsActifs = 0;
    int clientsInactifs = 0;
    int clientsResidentiels = 0;
    int clientsCommerce = 0;
    int clientsIndustrie = 0;
    int clientsPublic = 0;

    for (const ClientData &client : clientsData) {
        if (client.statut == "Actif") clientsActifs++;
        else clientsInactifs++;

        if (client.type == "Résidentiel") clientsResidentiels++;
        else if (client.type == "Commerce") clientsCommerce++;
        else if (client.type == "Industriel") clientsIndustrie++;
        else if (client.type == "Public") clientsPublic++;
    }

    double tauxActif = totalClients > 0 ? (clientsActifs * 100.0 / totalClients) : 0.0;

    // Grille de statistiques 2x2
    QGridLayout *statsGrid = new QGridLayout();
    statsGrid->setSpacing(20);
    statsGrid->setContentsMargins(0, 15, 0, 0);

    // Fonction pour créer une carte statistique - TAILLES AUGMENTÉES
    auto creerCarte = [](const QString &titre, const QString &valeur,
                         const QString &detail, const QString &couleurDetail) -> QFrame* {
        QFrame *carte = new QFrame();
        carte->setStyleSheet(
            "QFrame { "
            "    background-color: #F8FAFB; "
            "    border-radius: 16px; "
            "    padding: 25px; "
            "    border: 2px solid #E8ECF0; "
            "}"
            );
        carte->setMinimumHeight(150);  // Hauteur augmentée

        QVBoxLayout *layout = new QVBoxLayout(carte);
        layout->setSpacing(12);
        layout->setContentsMargins(20, 20, 20, 20);

        QLabel *lblTitre = new QLabel(titre);
        lblTitre->setStyleSheet(
            "font-size: 14px; "       // Taille augmentée
            "color: #6E7F91; "
            "font-weight: 600; "
            "letter-spacing: 0.5px;"
            );
        lblTitre->setMinimumHeight(25);

        QLabel *lblValeur = new QLabel(valeur);
        lblValeur->setStyleSheet(
            "font-size: 42px; "       // Taille bien augmentée
            "color: #2A3439; "
            "font-weight: bold; "
            "line-height: 1.2;"
            );
        lblValeur->setMinimumHeight(50);

        QLabel *lblDetail = new QLabel(detail);
        lblDetail->setStyleSheet(
            QString("font-size: 14px; color: %1; font-weight: 600;").arg(couleurDetail)
            );
        lblDetail->setMinimumHeight(25);

        layout->addWidget(lblTitre);
        layout->addWidget(lblValeur);
        if (!detail.isEmpty()) {
            layout->addWidget(lblDetail);
        }
        layout->addStretch();

        return carte;
    };

    statsGrid->addWidget(creerCarte("TOTAL CLIENTS",
                                    QString::number(totalClients),
                                    QString("↑ %1 actifs").arg(clientsActifs),
                                    "#4CAF50"), 0, 0);
    statsGrid->addWidget(creerCarte("CLIENTS ACTIFS",
                                    QString::number(clientsActifs),
                                    QString("%1% du total").arg(tauxActif, 0, 'f', 1),
                                    "#4CAF50"), 0, 1);
    statsGrid->addWidget(creerCarte("CLIENTS INACTIFS",
                                    QString::number(clientsInactifs),
                                    "En attente de réactivation",
                                    "#FF9800"), 1, 0);
    statsGrid->addWidget(creerCarte("ZONES COUVERTES",
                                    QString::number(3),
                                    "Tunis, Ariana, Manouba",
                                    "#3A6EA5"), 1, 1);

    leftLayout->addLayout(statsGrid);
    leftLayout->addStretch();

    mainLayout->addWidget(leftFrame, 1);

    // === PARTIE DROITE : Types de Clients ===
    QFrame *rightFrame = new QFrame(dialog);
    rightFrame->setStyleSheet(
        "QFrame { "
        "    background-color: white; "
        "    border-radius: 20px; "
        "    padding: 30px; "
        "}"
        );
    QVBoxLayout *rightLayout = new QVBoxLayout(rightFrame);
    rightLayout->setSpacing(25);
    rightLayout->setContentsMargins(30, 30, 30, 30);

    // Titre Types de Clients - TAILLE AUGMENTÉE
    QLabel *titreDroite = new QLabel("📈 Répartition par Type", rightFrame);
    titreDroite->setStyleSheet(
        "font-size: 26px; "           // Taille augmentée
        "font-weight: bold; "
        "color: #2A3439; "
        "padding-bottom: 15px;"
        );
    titreDroite->setMinimumHeight(50);
    rightLayout->addWidget(titreDroite);

    // Ajout d'espacement
    rightLayout->addSpacing(20);

    // Fonction pour créer une ligne de type avec barre de progression - TAILLES AUGMENTÉES
    auto creerLigneType = [totalClients](const QString &icone, const QString &nom, int valeur,
                                         const QString &couleur) -> QFrame* {
        QFrame *ligne = new QFrame();
        ligne->setMinimumHeight(90);  // Hauteur augmentée
        QHBoxLayout *layout = new QHBoxLayout(ligne);
        layout->setContentsMargins(0, 15, 0, 15);
        layout->setSpacing(25);

        // Icône + Nom - TAILLE AUGMENTÉE
        QLabel *lblNom = new QLabel(icone + " " + nom);
        lblNom->setStyleSheet(
            "font-size: 18px; "       // Taille augmentée
            "color: #2A3439; "
            "font-weight: 600;"
            );
        lblNom->setMinimumWidth(180);
        lblNom->setMinimumHeight(35);

        // Barre de progression
        QProgressBar *progress = new QProgressBar();
        progress->setMinimum(0);
        progress->setMaximum(totalClients > 0 ? totalClients : 100);
        progress->setValue(valeur);
        progress->setTextVisible(false);
        progress->setFixedHeight(25);  // Hauteur augmentée
        progress->setStyleSheet(
            QString(
                "QProgressBar { "
                "    border: none; "
                "    background-color: #F0F4F8; "
                "    border-radius: 12px; "
                "}"
                "QProgressBar::chunk { "
                "    background-color: %1; "
                "    border-radius: 12px; "
                "}"
                ).arg(couleur)
            );

        // Pourcentage - TAILLE AUGMENTÉE
        int percentage = totalClients > 0 ? (valeur * 100 / totalClients) : 0;
        QLabel *lblPct = new QLabel(QString("%1%").arg(percentage));
        lblPct->setStyleSheet(
            QString(
                "font-size: 16px; "   // Taille augmentée
                "font-weight: bold; "
                "color: %1; "
                "padding: 8px 15px; "
                "background-color: %2; "
                "border-radius: 12px;"
                ).arg(couleur).arg(couleur + "25")
            );
        lblPct->setMinimumWidth(80);
        lblPct->setMinimumHeight(35);
        lblPct->setAlignment(Qt::AlignCenter);

        // Valeur absolue - TAILLE AUGMENTÉE
        QLabel *lblVal = new QLabel(QString::number(valeur));
        lblVal->setStyleSheet(
            "font-size: 18px; "       // Taille augmentée
            "color: #2A3439; "
            "font-weight: 700;"
            );
        lblVal->setMinimumWidth(60);
        lblVal->setMinimumHeight(35);
        lblVal->setAlignment(Qt::AlignRight | Qt::AlignVCenter);

        layout->addWidget(lblNom);
        layout->addWidget(progress, 1);
        layout->addWidget(lblPct);
        layout->addWidget(lblVal);

        return ligne;
    };

    rightLayout->addWidget(creerLigneType("🏠", "Résidentiel", clientsResidentiels, "#4CAF50"));
    rightLayout->addWidget(creerLigneType("🏪", "Commerce", clientsCommerce, "#3A6EA5"));
    rightLayout->addWidget(creerLigneType("🏭", "Industriel", clientsIndustrie, "#FF9800"));
    rightLayout->addWidget(creerLigneType("🏛️", "Public", clientsPublic, "#9C27B0"));

    rightLayout->addStretch();

    mainLayout->addWidget(rightFrame, 1);

    dialog->exec();
    delete dialog;
}

void MainWindow::on_pushButton_23_clicked()
{
    // Bouton Modifier
    afficherWidgetModification();
}

void MainWindow::afficherWidgetModification()
{
    // Récupérer la ligne sélectionnée
    int currentRow = ui->tableWidget_3->currentRow();

    if (currentRow < 0) {
        QMessageBox::warning(this, "Erreur", "Veuillez sélectionner un client à modifier!");
        return;
    }

    // Créer un dialog - TAILLE AUGMENTÉE
    QDialog *dialog = new QDialog(this);
    dialog->setWindowTitle("✏️ Modifier un Client");
    dialog->setFixedSize(650, 800);  // Taille augmentée
    dialog->setStyleSheet("QDialog { background-color: #F5F7FA; }");

    QVBoxLayout *mainLayout = new QVBoxLayout(dialog);
    mainLayout->setSpacing(0);
    mainLayout->setContentsMargins(0, 0, 0, 0);

    // Frame conteneur avec fond blanc
    QFrame *containerFrame = new QFrame(dialog);
    containerFrame->setStyleSheet("QFrame { background-color: white; border-radius: 15px; }");
    QVBoxLayout *containerLayout = new QVBoxLayout(containerFrame);
    containerLayout->setSpacing(20);
    containerLayout->setContentsMargins(30, 25, 30, 25);

    // Titre
    QLabel *titre = new QLabel("✏️ Modifier le Client", containerFrame);
    titre->setStyleSheet(
        "font-size: 20px; font-weight: bold; padding: 20px; "
        "background-color: qlineargradient(x1:0, y1:0, x2:0, y2:1, "
        "stop:0 #2C5F7C, stop:0.5 #3A6EA5, stop:1 #1B3A57); "
        "color: white; border-radius: 12px;"
        );
    titre->setAlignment(Qt::AlignCenter);
    titre->setMinimumHeight(60);
    containerLayout->addWidget(titre);

    // Créer un scroll area pour les champs
    QScrollArea *scrollArea = new QScrollArea(containerFrame);
    scrollArea->setWidgetResizable(true);
    scrollArea->setFrameShape(QFrame::NoFrame);
    scrollArea->setStyleSheet("QScrollArea { background-color: transparent; border: none; }");

    QWidget *scrollWidget = new QWidget();
    QVBoxLayout *scrollLayout = new QVBoxLayout(scrollWidget);
    scrollLayout->setSpacing(18);
    scrollLayout->setContentsMargins(10, 10, 10, 10);

    // Style pour les labels - TAILLE AUGMENTÉE
    QString labelStyle =
        "font-size: 15px; "
        "color: #2A3439; "
        "font-weight: 600; "
        "padding: 8px 0px;";

    // Style pour les champs
    QString editStyle =
        "QLineEdit { "
        "    background-color: #F9FBFD; "
        "    border: 2px solid #D1DCE5; "
        "    border-radius: 10px; "
        "    padding: 14px 16px; "
        "    font-size: 15px; "
        "    color: #2A3439; "
        "    min-height: 20px; "
        "}"
        "QLineEdit:focus { "
        "    background-color: white; "
        "    border: 2px solid #3A6EA5; "
        "}";

    QString comboStyle =
        "QComboBox { "
        "    background-color: #F9FBFD; "
        "    border: 2px solid #D1DCE5; "
        "    border-radius: 10px; "
        "    padding: 14px 16px; "
        "    font-size: 15px; "
        "    color: #2A3439; "
        "    min-height: 20px; "
        "}"
        "QComboBox:focus { "
        "    border: 2px solid #3A6EA5; "
        "}";

    // Créer les champs pré-remplis
    auto ajouterChamp = [&](const QString &labelText, const QString &valeur) -> QLineEdit* {
        QLabel *lbl = new QLabel(labelText);
        lbl->setStyleSheet(labelStyle);
        lbl->setMinimumHeight(30);

        QLineEdit *edit = new QLineEdit(valeur);
        edit->setStyleSheet(editStyle);
        edit->setMinimumHeight(50);

        scrollLayout->addWidget(lbl);
        scrollLayout->addWidget(edit);
        return edit;
    };

    QLineEdit *nomEdit = ajouterChamp("👤 Nom du client *", ui->tableWidget_3->item(currentRow, 1)->text());
    QLineEdit *prenomEdit = ajouterChamp("👤 Prénom", ui->tableWidget_3->item(currentRow, 2)->text());

    QLabel *lblType = new QLabel("🏢 Type de client *");
    lblType->setStyleSheet(labelStyle);
    lblType->setMinimumHeight(30);

    QComboBox *typeCombo = new QComboBox();
    typeCombo->addItems({"Résidentiel", "Commerce", "Industriel", "Public"});
    typeCombo->setCurrentText(ui->tableWidget_3->item(currentRow, 3)->text());
    typeCombo->setStyleSheet(comboStyle);
    typeCombo->setMinimumHeight(50);

    scrollLayout->addWidget(lblType);
    scrollLayout->addWidget(typeCombo);

    QLineEdit *zoneEdit = ajouterChamp("📍 Zone géographique *", ui->tableWidget_3->item(currentRow, 4)->text());
    QLineEdit *telEdit = ajouterChamp("📞 Téléphone *", ui->tableWidget_3->item(currentRow, 5)->text());

    QLabel *lblStatut = new QLabel("📊 Statut *");
    lblStatut->setStyleSheet(labelStyle);
    lblStatut->setMinimumHeight(30);

    QComboBox *statutCombo = new QComboBox();
    statutCombo->addItems({"Actif", "Inactif", "En attente"});
    statutCombo->setCurrentText(ui->tableWidget_3->item(currentRow, 6)->text());
    statutCombo->setStyleSheet(comboStyle);
    statutCombo->setMinimumHeight(50);

    scrollLayout->addWidget(lblStatut);
    scrollLayout->addWidget(statutCombo);

    scrollWidget->setLayout(scrollLayout);
    scrollArea->setWidget(scrollWidget);
    containerLayout->addWidget(scrollArea);

    // Boutons
    QHBoxLayout *buttonLayout = new QHBoxLayout();
    buttonLayout->setSpacing(20);

    QPushButton *btnValider = new QPushButton("✓ Enregistrer");
    btnValider->setMinimumHeight(55);
    btnValider->setCursor(Qt::PointingHandCursor);
    btnValider->setStyleSheet(
        "QPushButton { "
        "    background-color: qlineargradient(x1:0, y1:0, x2:0, y2:1, "
        "    stop:0 #2C5F7C, stop:0.5 #3A6EA5, stop:1 #1B3A57); "
        "    color: white; "
        "    font-size: 16px; "
        "    font-weight: 600; "
        "    border-radius: 12px; "
        "    padding: 14px 28px; "
        "}"
        "QPushButton:hover { "
        "    background-color: #4A86C5; "
        "}"
        );

    QPushButton *btnAnnuler = new QPushButton("✗ Annuler");
    btnAnnuler->setMinimumHeight(55);
    btnAnnuler->setCursor(Qt::PointingHandCursor);
    btnAnnuler->setStyleSheet(
        "QPushButton { "
        "    background-color: #E8ECF0; "
        "    color: #2A3439; "
        "    font-size: 16px; "
        "    font-weight: 600; "
        "    border-radius: 12px; "
        "    padding: 14px 28px; "
        "}"
        "QPushButton:hover { "
        "    background-color: #D1DCE5; "
        "}"
        );

    buttonLayout->addWidget(btnAnnuler);
    buttonLayout->addWidget(btnValider);
    containerLayout->addLayout(buttonLayout);

    mainLayout->addWidget(containerFrame);

    // Connecter les boutons
    connect(btnValider, &QPushButton::clicked, [=]() {
        // Mettre à jour le tableau
        ui->tableWidget_3->item(currentRow, 1)->setText(nomEdit->text());
        ui->tableWidget_3->item(currentRow, 2)->setText(prenomEdit->text());
        ui->tableWidget_3->item(currentRow, 3)->setText(typeCombo->currentText());
        ui->tableWidget_3->item(currentRow, 4)->setText(zoneEdit->text());
        ui->tableWidget_3->item(currentRow, 5)->setText(telEdit->text());
        ui->tableWidget_3->item(currentRow, 6)->setText(statutCombo->currentText());

        // Mettre à jour les données
        int id = ui->tableWidget_3->item(currentRow, 0)->text().toInt();
        for (int i = 0; i < clientsData.size(); ++i) {
            if (clientsData[i].id == id) {
                clientsData[i].nom = nomEdit->text();
                clientsData[i].prenom = prenomEdit->text();
                clientsData[i].type = typeCombo->currentText();
                clientsData[i].zone = zoneEdit->text();
                clientsData[i].telephone = telEdit->text();
                clientsData[i].statut = statutCombo->currentText();
                break;
            }
        }

        QMessageBox::information(dialog, "Succès", "✓ Client modifié avec succès!");
        dialog->accept();
    });

    connect(btnAnnuler, &QPushButton::clicked, dialog, &QDialog::reject);

    dialog->exec();
    delete dialog;
}

void MainWindow::on_pushButton_10_clicked()
{
    // Bouton Supprimer
    supprimerClient();
}

void MainWindow::supprimerClient()
{
    int currentRow = ui->tableWidget_3->currentRow();

    if (currentRow < 0) {
        QMessageBox::warning(this, "Erreur", "Veuillez sélectionner un client à supprimer!");
        return;
    }

    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Confirmation",
                                  "Êtes-vous sûr de vouloir supprimer ce client?",
                                  QMessageBox::Yes | QMessageBox::No);

    if (reply == QMessageBox::Yes) {
        // Supprimer de la liste
        int id = ui->tableWidget_3->item(currentRow, 0)->text().toInt();
        for (int i = 0; i < clientsData.size(); ++i) {
            if (clientsData[i].id == id) {
                clientsData.removeAt(i);
                break;
            }
        }

        // Supprimer du tableau
        ui->tableWidget_3->removeRow(currentRow);

        QMessageBox::information(this, "Succès", "✓ Client supprimé avec succès!");
    }
}

void MainWindow::on_comboTypePropriete_3_currentIndexChanged(int index)
{
    // Trier le tableau selon le critère sélectionné
    if (index > 0) { // Ignorer le premier item "Trier par..."
        trierTableau(index - 1);
    }
}

void MainWindow::trierTableau(int critere)
{
    // Trier les données
    switch (critere) {
    case 0: // Par ID
        std::sort(clientsData.begin(), clientsData.end(),
                  [](const ClientData &a, const ClientData &b) { return a.id < b.id; });
        break;
    case 1: // Par Nom
        std::sort(clientsData.begin(), clientsData.end(),
                  [](const ClientData &a, const ClientData &b) { return a.nom < b.nom; });
        break;
    case 2: // Par Type
        std::sort(clientsData.begin(), clientsData.end(),
                  [](const ClientData &a, const ClientData &b) { return a.type < b.type; });
        break;
    case 3: // Par Zone
        std::sort(clientsData.begin(), clientsData.end(),
                  [](const ClientData &a, const ClientData &b) { return a.zone < b.zone; });
        break;
    case 4: // Par Statut
        std::sort(clientsData.begin(), clientsData.end(),
                  [](const ClientData &a, const ClientData &b) { return a.statut < b.statut; });
        break;
    }

    // Mettre à jour le tableau
    ui->tableWidget_3->setRowCount(0);
    for (const ClientData &client : clientsData) {
        int row = ui->tableWidget_3->rowCount();
        ui->tableWidget_3->insertRow(row);
        ui->tableWidget_3->setItem(row, 0, new QTableWidgetItem(QString::number(client.id)));
        ui->tableWidget_3->setItem(row, 1, new QTableWidgetItem(client.nom));
        ui->tableWidget_3->setItem(row, 2, new QTableWidgetItem(client.prenom));
        ui->tableWidget_3->setItem(row, 3, new QTableWidgetItem(client.type));
        ui->tableWidget_3->setItem(row, 4, new QTableWidgetItem(client.zone));
        ui->tableWidget_3->setItem(row, 5, new QTableWidgetItem(client.telephone));
        ui->tableWidget_3->setItem(row, 6, new QTableWidgetItem(client.statut));
    }
}
