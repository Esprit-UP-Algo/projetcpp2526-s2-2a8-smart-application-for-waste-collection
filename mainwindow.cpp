#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "client.h"
#include <QRegularExpression>
#include <QRegularExpressionMatch>
#include <QtGlobal>
// Effets graphiques
#include <QGraphicsDropShadowEffect>
#include <QPropertyAnimation>

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
#include <QMessageBox>
#include <QAbstractItemView>

// Bibliothèques pour les dates et temps
#include <QDate>
#include <QTime>

// SQL / base de données
#include <QSqlQuery>
#include <QSqlError>

// Bibliothèque pour les groupes de boutons
#include <QButtonGroup>
// Bibliothèque pour le redimensionnement des colonnes/lignes des tableaux
#include <QHeaderView>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QGraphicsDropShadowEffect *glow = new QGraphicsDropShadowEffect(this);
    glow->setBlurRadius(0);
    glow->setOffset(0, 0);
    glow->setColor(QColor(0, 170, 255, 180));

    ui->frame_43->setGraphicsEffect(glow);
    QPropertyAnimation *anim = new QPropertyAnimation(glow, "blurRadius");
    anim->setStartValue(0);
    anim->setEndValue(40);
    anim->setEasingCurve(QEasingCurve::OutCubic);
    anim->start();

    // === Configuration du module CLIENT ===
    ui->tableWidget_3->setColumnCount(8);

    if (ui->tableWidget_3->columnCount() > 0)
        ui->tableWidget_3->setColumnHidden(0, true);

    ui->tableWidget_3->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableWidget_3->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableWidget_3->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tableWidget_3->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableWidget_3->verticalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);

    afficherListeClients();
    ui->stackedWidget->setCurrentIndex(1);
}

MainWindow::~MainWindow()
{
    delete ui;
}

// ===================================================
// ============== NAVIGATION =========================
// ===================================================

void MainWindow::on_pushButton_36_clicked() { ui->stackedWidget_2->setCurrentIndex(4); }
void MainWindow::on_pushButton_37_clicked() { ui->stackedWidget_2->setCurrentIndex(2); afficherListeClients(); }
void MainWindow::on_pushButton_45_clicked() { ui->stackedWidget_2->setCurrentIndex(0); }
void MainWindow::on_pushButton_17_clicked() { ui->stackedWidget_2->setCurrentIndex(3); }
void MainWindow::on_pushButton_rechercher_3_clicked() { ui->stackedWidget_2->setCurrentIndex(5); }
void MainWindow::on_frame_20_customContextMenuRequested(const QPoint &pos) { Q_UNUSED(pos); }
void MainWindow::on_mdp_clicked() { ui->stackedWidget->setCurrentIndex(0); }
void MainWindow::on_cnx_clicked() { ui->stackedWidget->setCurrentIndex(2); ui->stackedWidget_2->setCurrentIndex(11); }
void MainWindow::on_pushButton_44_clicked() { ui->stackedWidget->setCurrentIndex(8); }
void MainWindow::on_pushButton_16_clicked() { ui->stackedWidget->setCurrentIndex(8); }
void MainWindow::on_pushButton_30_clicked() { ui->stackedWidget_2->setCurrentIndex(2); }
void MainWindow::on_retour_clicked() { ui->stackedWidget->setCurrentIndex(1); }
void MainWindow::on_acceuil_clicked() { ui->stackedWidget_2->setCurrentIndex(11); }
void MainWindow::on_deconnection_clicked() { ui->stackedWidget->setCurrentIndex(1); }
void MainWindow::on_recyclage_clicked() { ui->stackedWidget_2->setCurrentIndex(0); }
void MainWindow::on_CONTENEUR_clicked() { ui->stackedWidget_2->setCurrentIndex(6); }
void MainWindow::on_TOURNEE_clicked() { ui->stackedWidget_2->setCurrentIndex(9); }
void MainWindow::on_pushButton_38_clicked() {}
void MainWindow::on_pushButton_35_clicked() {}
void MainWindow::on_pushButton_46_clicked() {}
void MainWindow::on_pushButton_clicked() {}
void MainWindow::on_pushButton_61_clicked() {}
void MainWindow::on_conn_clicked() {}
void MainWindow::on_dec_clicked() {}


// ===================================================
// ============== MODULE CLIENT ======================
// ===================================================

void MainWindow::on_pushButton_42_clicked()
{
    afficherWidgetAjoutClient();
}

void MainWindow::on_pushButton_52_clicked()
{
    int row = ui->tableWidget_3->currentRow();
    if (row < 0) {
        QMessageBox::warning(this, tr("Aucun client sélectionné"),
                             tr("Veuillez sélectionner un client dans la liste avant de modifier."));
        return;
    }

    QTableWidgetItem *idItem = ui->tableWidget_3->item(row, 0);
    if (!idItem || idItem->text().trimmed().isEmpty()) {
        QMessageBox::critical(this, tr("Erreur de sélection"),
                              tr("Impossible de récupérer l'identifiant du client sélectionné."));
        return;
    }

    afficherWidgetModifierClient(idItem->text().toInt());
}

void MainWindow::on_pushButton_60_clicked()
{
    int row = ui->tableWidget_3->currentRow();
    if (row < 0) {
        QMessageBox::warning(this, tr("Aucun client sélectionné"),
                             tr("Veuillez sélectionner un client à supprimer."));
        return;
    }

    QTableWidgetItem *idItem = ui->tableWidget_3->item(row, 0);
    if (!idItem || idItem->text().trimmed().isEmpty()) {
        QMessageBox::critical(this, tr("Erreur de sélection"),
                              tr("Impossible de récupérer l'identifiant du client sélectionné."));
        return;
    }

    auto reply = QMessageBox::question(this, tr("Confirmation de suppression"),
                                       tr("Êtes-vous sûr de vouloir supprimer ce client ?"),
                                       QMessageBox::Yes | QMessageBox::No, QMessageBox::No);
    if (reply != QMessageBox::Yes)
        return;

    // ✅ Utilisation de Client::supprimer()
    Client c;
    c.setIdClient(idItem->text().toInt());

    if (!c.supprimer()) {
        QMessageBox::critical(this, tr("Erreur lors de la suppression"),
                              tr("Impossible de supprimer le client."));
        return;
    }

    afficherListeClients();
}

void MainWindow::afficherListeClients()
{
    ui->tableWidget_3->setColumnCount(8);
    ui->tableWidget_3->setSortingEnabled(false);
    ui->tableWidget_3->clearContents();
    ui->tableWidget_3->setRowCount(0);

    // ✅ Utilisation de Client::afficher()
    Client temp;
    QList<Client> liste = temp.afficher();

    if (liste.isEmpty()) {
        ui->tableWidget_3->setSortingEnabled(true);
        return;
    }

    int row = 0;
    for (const Client &c : liste) {
        ui->tableWidget_3->insertRow(row);
        ui->tableWidget_3->setItem(row, 0, new QTableWidgetItem(QString::number(c.idClient())));
        ui->tableWidget_3->setItem(row, 1, new QTableWidgetItem(c.nom()));
        ui->tableWidget_3->setItem(row, 2, new QTableWidgetItem(c.prenom()));
        ui->tableWidget_3->setItem(row, 3, new QTableWidgetItem(c.typeClient()));
        ui->tableWidget_3->setItem(row, 4, new QTableWidgetItem(c.zone()));
        ui->tableWidget_3->setItem(row, 5, new QTableWidgetItem(c.telephone()));
        ui->tableWidget_3->setItem(row, 6, new QTableWidgetItem(c.statutCompte()));
        ui->tableWidget_3->setItem(row, 7, new QTableWidgetItem(c.adresseComplete()));
        ++row;
    }

    ui->tableWidget_3->setSortingEnabled(true);
}

void MainWindow::afficherWidgetAjoutClient()
{
    QDialog *dialog = new QDialog(this);
    dialog->setWindowTitle("+ Ajouter un Client");
    dialog->setFixedSize(850, 600);
    dialog->setStyleSheet("QDialog { background-color: #EDEDED; }");

    QVBoxLayout *mainLayout = new QVBoxLayout(dialog);

    QFrame *container = new QFrame();
    container->setStyleSheet("QFrame { background-color:#F2F2F2; border-radius:20px; }");

    QVBoxLayout *containerLayout = new QVBoxLayout(container);
    containerLayout->setContentsMargins(30, 30, 30, 30);

    QLabel *titre = new QLabel("👤 Informations Client");
    titre->setAlignment(Qt::AlignCenter);
    titre->setStyleSheet(
        "QLabel { font-size:20px; font-weight:bold; color:white; padding:20px;"
        "border-radius:18px; background:qlineargradient(x1:0,y1:0,x2:0,y2:1,"
        "stop:0 #2C5F7C, stop:1 #1B3A57); }");
    containerLayout->addWidget(titre);
    containerLayout->addSpacing(20);

    QWidget *contentWidget = new QWidget();
    contentWidget->setStyleSheet("background-color:white; border-radius:15px;");

    QGridLayout *gridLayout = new QGridLayout(contentWidget);
    gridLayout->setSpacing(15);
    gridLayout->setContentsMargins(25, 25, 25, 25);

    QString labelStyle = "QLabel { background-color:transparent; padding:5px; font-size:13px; font-weight:600; color:#374151; }";
    QString editStyle =
        "QLineEdit { background-color:#F9FAFB; border:1px solid #D1D5DB; border-radius:8px;"
        "padding:12px 16px; font-size:14px; color:#111827; }"
        "QLineEdit:hover { border:1px solid #2C5F7C; background-color:#FFFFFF; }"
        "QLineEdit:focus { border:2px solid #2C5F7C; background-color:#FFFFFF; padding:11px 15px; }";

    QLineEdit *nom      = new QLineEdit(); nom->setStyleSheet(editStyle);
    QLineEdit *prenom   = new QLineEdit(); prenom->setStyleSheet(editStyle);
    QLineEdit *telephone= new QLineEdit(); telephone->setStyleSheet(editStyle);
    QLineEdit *cin      = new QLineEdit(); cin->setStyleSheet(editStyle);
    QLineEdit *zone     = new QLineEdit(); zone->setStyleSheet(editStyle);
    QLineEdit *type     = new QLineEdit(); type->setStyleSheet(editStyle);
    QLineEdit *adresse  = new QLineEdit(); adresse->setStyleSheet(editStyle);

    auto addLabel = [&](const QString &text) {
        QLabel *l = new QLabel(text);
        l->setStyleSheet(labelStyle);
        return l;
    };

    gridLayout->addWidget(addLabel("👤 Nom:"),       0, 0); gridLayout->addWidget(nom,       0, 1);
    gridLayout->addWidget(addLabel("👤 Prenom:"),    1, 0); gridLayout->addWidget(prenom,    1, 1);
    gridLayout->addWidget(addLabel("📞 Téléphone:"), 2, 0); gridLayout->addWidget(telephone, 2, 1);
    gridLayout->addWidget(addLabel("🆔 CIN:"),       0, 2); gridLayout->addWidget(cin,       0, 3);
    gridLayout->addWidget(addLabel("📍 Zone:"),      1, 2); gridLayout->addWidget(zone,      1, 3);
    gridLayout->addWidget(addLabel("🏢 Type:"),      2, 2); gridLayout->addWidget(type,      2, 3);
    gridLayout->addWidget(addLabel("🏠 Adresse:"),   3, 0); gridLayout->addWidget(adresse,   3, 1, 1, 3);

    containerLayout->addWidget(contentWidget);
    containerLayout->addSpacing(15);

    QLabel *note = new QLabel("* Tous les champs sont obligatoires");
    note->setStyleSheet("color:#6E7F91; font-style:italic; font-size:12px;");
    containerLayout->addWidget(note);

    QHBoxLayout *btnLayout = new QHBoxLayout();
    btnLayout->setSpacing(15);

    QPushButton *annuler = new QPushButton("✗ Annuler");
    annuler->setMinimumHeight(50);
    annuler->setStyleSheet(
        "QPushButton { background-color:#E5E7EB; color:#374151; font-size:15px; font-weight:600;"
        "border:none; border-radius:8px; padding:12px 30px; }"
        "QPushButton:hover { background-color:#D1D5DB; }");

    QPushButton *ajouter = new QPushButton("✓ Ajouter");
    ajouter->setMinimumHeight(50);
    ajouter->setStyleSheet(
        "QPushButton { background:qlineargradient(x1:0,y1:0,x2:0,y2:1,stop:0 #2C5F7C,stop:1 #1B3A57);"
        "color:white; font-size:15px; font-weight:600; border:none; border-radius:8px; padding:12px 30px; }"
        "QPushButton:hover { background:qlineargradient(x1:0,y1:0,x2:0,y2:1,stop:0 #3A6EA5,stop:1 #2C5F7C); }");

    btnLayout->addWidget(annuler);
    btnLayout->addWidget(ajouter);
    containerLayout->addLayout(btnLayout);
    mainLayout->addWidget(container);

    connect(annuler, &QPushButton::clicked, dialog, &QDialog::reject);

    connect(ajouter, &QPushButton::clicked, this, [=]() {
        QString nomText      = nom->text().trimmed();
        QString prenomText   = prenom->text().trimmed();
        QString telText      = telephone->text().trimmed();
        QString cinText      = cin->text().trimmed();
        QString zoneText     = zone->text().trimmed();
        QString typeText     = type->text().trimmed();
        QString adresseText  = adresse->text().trimmed();

        // ✅ Vérifier que tous les champs sont remplis
        if (nomText.isEmpty() || prenomText.isEmpty() || telText.isEmpty() ||
            cinText.isEmpty() || zoneText.isEmpty() || typeText.isEmpty() ||
            adresseText.isEmpty())
        {
            QMessageBox::warning(dialog, tr("Champs manquants"),
                                 "<span style='color:red; font-weight:bold;'>Merci de remplir tous les champs obligatoires.</span>");
            return;
        }

        // ✅ Validation des formats avec QRegularExpression
        QRegularExpression regexNomPrenom("^[A-Za-zÀ-ÿ\\s'-]+$"); // lettres et accents
        if (!regexNomPrenom.match(nomText).hasMatch() ||
            !regexNomPrenom.match(prenomText).hasMatch())
        {
            QMessageBox::warning(dialog, tr("Nom/Prénom invalide"),
                                 "<span style='color:red;'>Le nom et le prénom doivent contenir uniquement des lettres.</span>");
            return;
        }

        QRegularExpression regexTelephone("^\\d{8,15}$"); // chiffres seulement, longueur 8-15
        if (!regexTelephone.match(telText).hasMatch())
        {
            QMessageBox::warning(dialog, tr("Téléphone invalide"),
                                 "<span style='color:red;'>Le numéro de téléphone doit contenir uniquement des chiffres (8-15).</span>");
            return;
        }

        QRegularExpression regexCIN("^[A-Z0-9]{8,12}$"); // CIN alphanumérique 8-12
        if (!regexCIN.match(cinText).hasMatch())
        {
            QMessageBox::warning(dialog, tr("CIN invalide"),
                                 "<span style='color:red;'>Le CIN doit être alphanumérique et contenir 8 à 12 caractères.</span>");
            return;
        }

        // ✅ Si tout est bon, ajouter le client
        Client c;
        c.setNom(nomText);
        c.setPrenom(prenomText);
        c.setCin(cinText);
        c.setTelephone(telText);
        c.setAdresseComplete(adresseText);
        c.setTypeClient(typeText);
        c.setStatutCompte("actif");
        c.setCinEmploye("");
        c.setZone(zoneText);

        if (!c.ajouter()) {
            QMessageBox::critical(dialog, tr("Erreur lors de l'ajout"),
                                  "<span style='color:red;'>Impossible d'ajouter le client.</span>");
            return;
        }

        dialog->accept();
        afficherListeClients();
    });
    dialog->exec();
}

//fct recherche client


void MainWindow::on_lineEdit_13_textChanged(const QString &text)
{
    Client::rechercherDansTable(ui->tableWidget_3, text);
}
//-------------

//tri

void MainWindow::on_btntrie_clicked()
{
    QMenu *menu = new QMenu(this);

    menu->setStyleSheet(
        "QMenu{background:#FAF5F0;border:2px solid #2C5F7C;border-radius:6px;padding:8px;}"
        "QMenu::item{padding:8px 25px;color:#291C0E;border-radius:4px;}"
        "QMenu::item:selected{background:#2C5F7C;color:white;}"
        );

    QMenu *alphaMenu = menu->addMenu("🔤 Alphabétique (Nom)");
    QAction *alphaAsc  = alphaMenu->addAction("A → Z");
    QAction *alphaDesc = alphaMenu->addAction("Z → A");

    QMenu *statutMenu = menu->addMenu("⚙️ Statut Compte");
    QAction *actif   = statutMenu->addAction("Actif");
    QAction *inactif = statutMenu->addAction("Inactif");
    QAction *tous    = menu->addAction("🔄 Afficher Tous");

    connect(menu, &QMenu::triggered, this, [=](QAction *action) {

        QString orderBy   = "id_client ASC";
        QString whereClause = "";
        QString label     = "Trier";

        if (action == alphaAsc) {
            orderBy = "nom ASC, prenom ASC";
            label   = "A → Z";
        }
        else if (action == alphaDesc) {
            orderBy = "nom DESC, prenom DESC";
            label   = "Z → A";
        }
        else if (action == actif) {
            whereClause = "WHERE LOWER(statut_compte) = 'actif'";
            label       = "Statut: Actif";
        }
        else if (action == inactif) {
            whereClause = "WHERE LOWER(statut_compte) = 'inactif'";
            label       = "Statut: Inactif";
        }
        else if (action == tous) {
            label = "Trier";
        }

        // ===== REFRESH TABLE =====
        ui->tableWidget_3->setSortingEnabled(false);
        ui->tableWidget_3->clearContents();
        ui->tableWidget_3->setRowCount(0);

        QSqlQuery q;
        QString queryStr = QString(
                               "SELECT id_client, nom, prenom, type_client, zone, telephone, statut_compte, adresse_complete "
                               "FROM CLIENT %1 ORDER BY %2"
                               ).arg(whereClause, orderBy);

        if (!q.exec(queryStr)) {
            QMessageBox::critical(this, "Erreur SQL", q.lastError().text());
            return;
        }

        int row = 0;
        while (q.next()) {
            ui->tableWidget_3->insertRow(row);
            ui->tableWidget_3->setItem(row, 0, new QTableWidgetItem(q.value(0).toString())); // id
            ui->tableWidget_3->setItem(row, 1, new QTableWidgetItem(q.value(1).toString())); // nom
            ui->tableWidget_3->setItem(row, 2, new QTableWidgetItem(q.value(2).toString())); // prenom
            ui->tableWidget_3->setItem(row, 3, new QTableWidgetItem(q.value(3).toString())); // type
            ui->tableWidget_3->setItem(row, 4, new QTableWidgetItem(q.value(4).toString())); // zone
            ui->tableWidget_3->setItem(row, 5, new QTableWidgetItem(q.value(5).toString())); // telephone
            ui->tableWidget_3->setItem(row, 6, new QTableWidgetItem(q.value(6).toString())); // statut
            ui->tableWidget_3->setItem(row, 7, new QTableWidgetItem(q.value(7).toString())); // adresse
            row++;
        }

        ui->tableWidget_3->setSortingEnabled(true);
        ui->btntrie->setText(label);
    });

    menu->exec(ui->btntrie->mapToGlobal(QPoint(0, ui->btntrie->height())));
}//------


//--------------------------------
//export
//--------------------------------


void MainWindow::on_btnexport_clicked()
{
    Client client; // créer un objet Client
    client.exporterListe(ui->tableWidget_3); // passer la table pour export
}


void MainWindow::afficherWidgetModifierClient(int idClient)
{
    QDialog *dialog = new QDialog(this);
    dialog->setWindowTitle(tr("Modifier un Client"));
    dialog->setFixedSize(850, 600);
    dialog->setStyleSheet("QDialog { background-color: #EDEDED; }");

    QVBoxLayout *mainLayout = new QVBoxLayout(dialog);

    QFrame *container = new QFrame();
    container->setStyleSheet("QFrame { background-color:#F2F2F2; border-radius:20px; }");

    QVBoxLayout *containerLayout = new QVBoxLayout(container);
    containerLayout->setContentsMargins(30, 30, 30, 30);

    QLabel *titre = new QLabel(tr("👤 Modifier Client"));
    titre->setAlignment(Qt::AlignCenter);
    titre->setStyleSheet(
        "QLabel { font-size:20px; font-weight:bold; color:white; padding:20px;"
        "border-radius:18px; background:qlineargradient(x1:0,y1:0,x2:0,y2:1,"
        "stop:0 #2C5F7C, stop:1 #1B3A57); }");
    containerLayout->addWidget(titre);
    containerLayout->addSpacing(20);

    QWidget *contentWidget = new QWidget();
    contentWidget->setStyleSheet("background-color:white; border-radius:15px;");

    QGridLayout *gridLayout = new QGridLayout(contentWidget);
    gridLayout->setSpacing(15);
    gridLayout->setContentsMargins(25, 25, 25, 25);

    QString labelStyle = "QLabel { background-color:transparent; padding:5px; font-size:13px; font-weight:600; color:#374151; }";
    QString editStyle =
        "QLineEdit { background-color:#F9FAFB; border:1px solid #D1D5DB; border-radius:8px;"
        "padding:12px 16px; font-size:14px; color:#111827; }"
        "QLineEdit:hover { border:1px solid #2C5F7C; background-color:#FFFFFF; }"
        "QLineEdit:focus { border:2px solid #2C5F7C; background-color:#FFFFFF; padding:11px 15px; }";

    QLineEdit *nom      = new QLineEdit(); nom->setStyleSheet(editStyle);
    QLineEdit *prenom   = new QLineEdit(); prenom->setStyleSheet(editStyle);
    QLineEdit *telephone= new QLineEdit(); telephone->setStyleSheet(editStyle);
    QLineEdit *cin      = new QLineEdit(); cin->setStyleSheet(editStyle);
    QLineEdit *zone     = new QLineEdit(); zone->setStyleSheet(editStyle);
    QLineEdit *type     = new QLineEdit(); type->setStyleSheet(editStyle);
    QLineEdit *adresse  = new QLineEdit(); adresse->setStyleSheet(editStyle);
    QLineEdit *statut   = new QLineEdit(); statut->setStyleSheet(editStyle);

    auto addLabel = [&](const QString &text) {
        QLabel *l = new QLabel(text);
        l->setStyleSheet(labelStyle);
        return l;
    };

    gridLayout->addWidget(addLabel("👤 Nom:"),             0, 0); gridLayout->addWidget(nom,       0, 1);
    gridLayout->addWidget(addLabel("👤 Prenom:"),          1, 0); gridLayout->addWidget(prenom,    1, 1);
    gridLayout->addWidget(addLabel("📞 Téléphone:"),       2, 0); gridLayout->addWidget(telephone, 2, 1);
    gridLayout->addWidget(addLabel("🆔 CIN:"),             0, 2); gridLayout->addWidget(cin,       0, 3);
    gridLayout->addWidget(addLabel("📍 Zone:"),            1, 2); gridLayout->addWidget(zone,      1, 3);
    gridLayout->addWidget(addLabel("🏢 Type:"),            2, 2); gridLayout->addWidget(type,      2, 3);
    gridLayout->addWidget(addLabel("⚙️ Statut compte:"),   3, 2); gridLayout->addWidget(statut,    3, 3);
    gridLayout->addWidget(addLabel("🏠 Adresse:"),         3, 0); gridLayout->addWidget(adresse,   3, 1);

    containerLayout->addWidget(contentWidget);
    containerLayout->addSpacing(15);

    QLabel *note = new QLabel(tr("* Tous les champs sont obligatoires"));
    note->setStyleSheet("color:#6E7F91; font-style:italic; font-size:12px;");
    containerLayout->addWidget(note);

    QHBoxLayout *btnLayout = new QHBoxLayout();
    btnLayout->setSpacing(15);

    QPushButton *annuler = new QPushButton(tr("✗ Annuler"));
    annuler->setMinimumHeight(50);
    annuler->setStyleSheet(
        "QPushButton { background-color:#E5E7EB; color:#374151; font-size:15px; font-weight:600;"
        "border:none; border-radius:8px; padding:12px 30px; }"
        "QPushButton:hover { background-color:#D1D5DB; }");

    QPushButton *enregistrer = new QPushButton(tr("✓ Enregistrer"));
    enregistrer->setMinimumHeight(50);
    enregistrer->setStyleSheet(
        "QPushButton { background:qlineargradient(x1:0,y1:0,x2:0,y2:1,stop:0 #2C5F7C,stop:1 #1B3A57);"
        "color:white; font-size:15px; font-weight:600; border:none; border-radius:8px; padding:12px 30px; }"
        "QPushButton:hover { background:qlineargradient(x1:0,y1:0,x2:0,y2:1,stop:0 #3A6EA5,stop:1 #2C5F7C); }");

    btnLayout->addWidget(annuler);
    btnLayout->addWidget(enregistrer);
    containerLayout->addLayout(btnLayout);
    mainLayout->addWidget(container);

    connect(annuler, &QPushButton::clicked, dialog, &QDialog::reject);

    // ✅ Charger les données via Client::afficher() en filtrant par ID
    Client existing;
    QList<Client> liste = existing.afficher();
    Client found;
    bool clientFound = false;
    for (const Client &c : liste) {
        if (c.idClient() == idClient) {
            found = c;
            clientFound = true;
            break;
        }
    }

    if (!clientFound) {
        QMessageBox::critical(this, tr("Client introuvable"),
                              tr("Impossible de charger les informations du client."));
        delete dialog;
        return;
    }

    // Pré-remplir les champs
    nom->setText(found.nom());
    prenom->setText(found.prenom());
    cin->setText(found.cin());
    telephone->setText(found.telephone());
    adresse->setText(found.adresseComplete());
    type->setText(found.typeClient());
    statut->setText(found.statutCompte());
    zone->setText(found.zone());

    connect(enregistrer, &QPushButton::clicked, this, [=]() {
        QString nomText      = nom->text().trimmed();
        QString prenomText   = prenom->text().trimmed();
        QString telText      = telephone->text().trimmed();
        QString cinText      = cin->text().trimmed();
        QString zoneText     = zone->text().trimmed();
        QString typeText     = type->text().trimmed();
        QString adresseText  = adresse->text().trimmed();
        QString statutText   = statut->text().trimmed();

        // ✅ Vérifier que tous les champs sont remplis
        if (nomText.isEmpty() || prenomText.isEmpty() || telText.isEmpty() ||
            cinText.isEmpty() || zoneText.isEmpty() || typeText.isEmpty() ||
            adresseText.isEmpty())
        {
            QMessageBox::warning(dialog, tr("Champs manquants"),
                                 tr("Merci de remplir tous les champs obligatoires."));
            return;
        }

        // ✅ Validation des formats avec QRegularExpression
        QRegularExpression regexNomPrenom("^[A-Za-zÀ-ÿ\\s'-]+$"); // lettres et accents
        if (!regexNomPrenom.match(nomText).hasMatch() ||
            !regexNomPrenom.match(prenomText).hasMatch())
        {
            QMessageBox::warning(dialog,
                                 tr("Nom/Prénom invalide"),
                                 "<span style='color:red; font-weight:bold;'>"
                                 "Le nom et le prénom doivent contenir uniquement des lettres."
                                 "</span>");
            return;
        }

        QRegularExpression regexTelephone("^\\d{8}$"); // chiffres seulement, longueur 8-15
        if (!regexTelephone.match(telText).hasMatch())
        {
            QMessageBox::warning(dialog, tr("Téléphone invalide"),
                                 "<span style='color:orange;'>Le numéro de téléphone doit contenir uniquement des chiffres (8-15).</span>");
            return;
        }

        QRegularExpression regexCIN("^[A-Z0-9]{8,12}$"); // CIN alphanumérique 8-12
        if (!regexCIN.match(cinText).hasMatch())
        {
            QMessageBox::warning(dialog, tr("CIN invalide"),
                                 "<span style='color:orange;'>Le numéro de cin doit contenir uniquement des chiffres (8).</span>");
            return;
        }

        // ✅ Si tout est bon, modifier le client
        Client c;
        c.setIdClient(idClient);
        c.setNom(nomText);
        c.setPrenom(prenomText);
        c.setCin(cinText);
        c.setTelephone(telText);
        c.setAdresseComplete(adresseText);
        c.setTypeClient(typeText);
        c.setStatutCompte(statutText);
        c.setCinEmploye(found.cinEmploye());
        c.setZone(zoneText);

        if (!c.modifier()) {
            QMessageBox::critical(dialog, tr("Erreur lors de la mise à jour"),
                                  tr("Impossible de mettre à jour le client."));
            return;
        }

        dialog->accept();
        afficherListeClients();
    });

    dialog->exec();
}

// ===================================================
// ============== AUTRES MODULES =====================
// ===================================================

void MainWindow::on_pushButton_65_clicked() { afficherWidgetAjoutRecyclage(); }

void MainWindow::afficherWidgetAjoutRecyclage()
{
    QDialog *dialog = new QDialog(this);
    dialog->setWindowTitle("+ Ajouter une Opération de Recyclage");
    dialog->setFixedSize(850, 650);
    dialog->setStyleSheet("QDialog { background-color: #EDEDED; }");

    QVBoxLayout *mainLayout = new QVBoxLayout(dialog);
    QFrame *container = new QFrame();
    container->setStyleSheet("QFrame { background-color:#F2F2F2; border-radius:20px; }");
    QVBoxLayout *containerLayout = new QVBoxLayout(container);
    containerLayout->setContentsMargins(30,30,30,30);

    QLabel *titre = new QLabel("♻️ Opération de Recyclage");
    titre->setAlignment(Qt::AlignCenter);
    titre->setStyleSheet(
        "QLabel { font-size:20px; font-weight:bold; color:white; padding:20px; border-radius:18px;"
        "background:qlineargradient(x1:0,y1:0,x2:0,y2:1,stop:0 #2C5F7C,stop:1 #1B3A57); }");
    containerLayout->addWidget(titre);
    containerLayout->addSpacing(20);

    QWidget *contentWidget = new QWidget();
    contentWidget->setStyleSheet("background-color:white; border-radius:15px;");
    QGridLayout *gridLayout = new QGridLayout(contentWidget);
    gridLayout->setSpacing(15);
    gridLayout->setContentsMargins(25,25,25,25);

    QString labelStyle = "QLabel { background-color:transparent; padding:5px; font-size:13px; font-weight:600; color:#374151; }";
    QString editStyle =
        "QLineEdit { background-color:#F9FAFB; border:1px solid #D1D5DB; border-radius:8px;"
        "padding:12px 16px; font-size:14px; color:#111827; }"
        "QLineEdit:hover { border:1px solid #2C5F7C; }"
        "QLineEdit:focus { border:2px solid #2C5F7C; padding:11px 15px; }";

    QLineEdit *id         = new QLineEdit(); id->setStyleSheet(editStyle);
    QLineEdit *materiau   = new QLineEdit(); materiau->setStyleSheet(editStyle);
    QLineEdit *qteEntree  = new QLineEdit(); qteEntree->setStyleSheet(editStyle);
    QLineEdit *qteRecyclee= new QLineEdit(); qteRecyclee->setStyleSheet(editStyle);
    QLineEdit *qteRejetee = new QLineEdit(); qteRejetee->setStyleSheet(editStyle);
    QLineEdit *taux       = new QLineEdit(); taux->setStyleSheet(editStyle);
    QLineEdit *destination= new QLineEdit(); destination->setStyleSheet(editStyle);
    QLineEdit *valeur     = new QLineEdit(); valeur->setStyleSheet(editStyle);

    auto lbl = [&](const QString &t){ QLabel *l=new QLabel(t); l->setStyleSheet(labelStyle); return l; };

    gridLayout->addWidget(lbl("🆔 id:"),                    0,0); gridLayout->addWidget(id,          0,1);
    gridLayout->addWidget(lbl("📦 Matériau:"),              1,0); gridLayout->addWidget(materiau,    1,1);
    gridLayout->addWidget(lbl("📊 Qté Entrée:"),            2,0); gridLayout->addWidget(qteEntree,   2,1);
    gridLayout->addWidget(lbl("📊 Quantite_recyclee (kg):"),3,0); gridLayout->addWidget(qteRecyclee, 3,1);
    gridLayout->addWidget(lbl("📊 Quantite_rejetee (kg):"), 0,2); gridLayout->addWidget(qteRejetee,  0,3);
    gridLayout->addWidget(lbl("📈 Taux (%):"),              1,2); gridLayout->addWidget(taux,        1,3);
    gridLayout->addWidget(lbl("📍 Destination:"),           2,2); gridLayout->addWidget(destination, 2,3);
    gridLayout->addWidget(lbl("💰 Valeur(TND):"),           3,2); gridLayout->addWidget(valeur,      3,3);

    containerLayout->addWidget(contentWidget);
    containerLayout->addSpacing(15);

    QLabel *note = new QLabel("* Tous les champs sont obligatoires");
    note->setStyleSheet("color:#6E7F91; font-style:italic; font-size:12px;");
    containerLayout->addWidget(note);

    QHBoxLayout *btnLayout = new QHBoxLayout();
    QPushButton *annuler = new QPushButton("✗ Annuler");
    annuler->setMinimumHeight(50);
    annuler->setStyleSheet("QPushButton { background-color:#E5E7EB; color:#374151; font-size:15px; font-weight:600; border:none; border-radius:8px; padding:12px 30px; } QPushButton:hover { background-color:#D1D5DB; }");
    QPushButton *ajouter = new QPushButton("✓ Ajouter");
    ajouter->setMinimumHeight(50);
    ajouter->setStyleSheet("QPushButton { background:qlineargradient(x1:0,y1:0,x2:0,y2:1,stop:0 #2C5F7C,stop:1 #1B3A57); color:white; font-size:15px; font-weight:600; border:none; border-radius:8px; padding:12px 30px; }");
    btnLayout->addWidget(annuler);
    btnLayout->addWidget(ajouter);
    containerLayout->addLayout(btnLayout);
    mainLayout->addWidget(container);

    connect(annuler, &QPushButton::clicked, dialog, &QDialog::reject);
    dialog->exec();
}

void MainWindow::on_pushButton_66_clicked() { afficherWidgetAjoutCollecte(); }

void MainWindow::afficherWidgetAjoutCollecte()
{
    QDialog *dialog = new QDialog(this);
    dialog->setWindowTitle("+ Ajouter une Collecte");
    dialog->setFixedSize(850, 700);
    dialog->setStyleSheet("QDialog { background-color: #EDEDED; }");

    QVBoxLayout *mainLayout = new QVBoxLayout(dialog);
    QFrame *container = new QFrame();
    container->setStyleSheet("QFrame { background-color:#F2F2F2; border-radius:20px; }");
    QVBoxLayout *containerLayout = new QVBoxLayout(container);
    containerLayout->setContentsMargins(30,30,30,30);

    QLabel *titre = new QLabel("🚛 Informations Collecte");
    titre->setAlignment(Qt::AlignCenter);
    titre->setStyleSheet("QLabel { font-size:20px; font-weight:bold; color:white; padding:20px; border-radius:18px; background:qlineargradient(x1:0,y1:0,x2:0,y2:1,stop:0 #2C5F7C,stop:1 #1B3A57); }");
    containerLayout->addWidget(titre);
    containerLayout->addSpacing(20);

    QWidget *contentWidget = new QWidget();
    contentWidget->setStyleSheet("background-color:white; border-radius:15px;");
    QGridLayout *gridLayout = new QGridLayout(contentWidget);
    gridLayout->setSpacing(15);
    gridLayout->setContentsMargins(25,25,25,25);

    QString labelStyle = "QLabel { background-color:transparent; padding:5px; font-size:13px; font-weight:600; color:#374151; }";
    QString editStyle = "QLineEdit, QDateEdit, QTimeEdit, QComboBox, QSpinBox, QDoubleSpinBox { background-color:#F9FAFB; border:1px solid #D1D5DB; border-radius:8px; padding:12px 16px; font-size:14px; color:#111827; }";

    QLineEdit *id     = new QLineEdit(); id->setStyleSheet(editStyle);
    QDateEdit *date   = new QDateEdit(QDate::fromString("01/01/2000","dd/MM/yyyy")); date->setDisplayFormat("dd/MM/yyyy"); date->setStyleSheet(editStyle);
    QTimeEdit *heure  = new QTimeEdit(QTime(12,0)); heure->setDisplayFormat("hh:mm AP"); heure->setStyleSheet(editStyle);
    QLineEdit *zone   = new QLineEdit(); zone->setStyleSheet(editStyle);
    QComboBox *type   = new QComboBox(); type->addItems({"Recyclable","Mixte","Organique"}); type->setStyleSheet(editStyle);
    QComboBox *status = new QComboBox(); status->addItems({"Planifiée","En cours","Terminée"}); status->setStyleSheet(editStyle);
    QDoubleSpinBox *distance = new QDoubleSpinBox(); distance->setSuffix(" Km"); distance->setDecimals(2); distance->setMaximum(9999.99); distance->setStyleSheet(editStyle);
    QDoubleSpinBox *quantite = new QDoubleSpinBox(); quantite->setSuffix(" Kg"); quantite->setDecimals(2); quantite->setMaximum(9999.99); quantite->setStyleSheet(editStyle);

    auto lbl = [&](const QString &t){ QLabel *l=new QLabel(t); l->setStyleSheet(labelStyle); return l; };

    gridLayout->addWidget(lbl("🆔 id:"),                   0,0); gridLayout->addWidget(id,       0,1);
    gridLayout->addWidget(lbl("📅 Date:"),                  1,0); gridLayout->addWidget(date,     1,1);
    gridLayout->addWidget(lbl("⏰ heure:"),                 2,0); gridLayout->addWidget(heure,    2,1);
    gridLayout->addWidget(lbl("📍 zone:"),                  3,0); gridLayout->addWidget(zone,     3,1);
    gridLayout->addWidget(lbl("🏷️ type:"),                  0,2); gridLayout->addWidget(type,     0,3);
    gridLayout->addWidget(lbl("📊 status:"),                1,2); gridLayout->addWidget(status,   1,3);
    gridLayout->addWidget(lbl("📏 distance:"),              2,2); gridLayout->addWidget(distance, 2,3);
    gridLayout->addWidget(lbl("⚖️ Quantité_collecte:"),     3,2); gridLayout->addWidget(quantite, 3,3);

    containerLayout->addWidget(contentWidget);
    QLabel *note = new QLabel("* Tous les champs sont obligatoires");
    note->setStyleSheet("color:#6E7F91; font-style:italic; font-size:12px;");
    containerLayout->addWidget(note);

    QHBoxLayout *btnLayout = new QHBoxLayout();
    QPushButton *annuler = new QPushButton("✗ Annuler"); annuler->setMinimumHeight(50);
    annuler->setStyleSheet("QPushButton { background-color:#E5E7EB; color:#374151; font-size:15px; font-weight:600; border:none; border-radius:8px; padding:12px 30px; } QPushButton:hover { background-color:#D1D5DB; }");
    QPushButton *ajouter = new QPushButton("✓ Ajouter"); ajouter->setMinimumHeight(50);
    ajouter->setStyleSheet("QPushButton { background:qlineargradient(x1:0,y1:0,x2:0,y2:1,stop:0 #2C5F7C,stop:1 #1B3A57); color:white; font-size:15px; font-weight:600; border:none; border-radius:8px; padding:12px 30px; }");
    btnLayout->addWidget(annuler); btnLayout->addWidget(ajouter);
    containerLayout->addLayout(btnLayout);
    mainLayout->addWidget(container);

    connect(annuler, &QPushButton::clicked, dialog, &QDialog::reject);
    dialog->exec();
}

void MainWindow::on_pushButton_67_clicked() { afficherWidgetAjoutConteneur(); }

void MainWindow::afficherWidgetAjoutConteneur()
{
    QDialog *dialog = new QDialog(this);
    dialog->setWindowTitle("+ Ajouter un Conteneur");
    dialog->setFixedSize(900, 750);
    dialog->setStyleSheet("QDialog { background-color: #EDEDED; }");

    QVBoxLayout *mainLayout = new QVBoxLayout(dialog);
    QFrame *container = new QFrame();
    container->setStyleSheet("QFrame { background-color:#F2F2F2; border-radius:20px; }");
    QVBoxLayout *containerLayout = new QVBoxLayout(container);
    containerLayout->setContentsMargins(30,30,30,30);

    QLabel *titre = new QLabel("🗑️ Informations Conteneur");
    titre->setAlignment(Qt::AlignCenter);
    titre->setStyleSheet("QLabel { font-size:20px; font-weight:bold; color:white; padding:20px; border-radius:18px; background:qlineargradient(x1:0,y1:0,x2:0,y2:1,stop:0 #2C5F7C,stop:1 #1B3A57); }");
    containerLayout->addWidget(titre);
    containerLayout->addSpacing(20);

    QScrollArea *scrollArea = new QScrollArea();
    scrollArea->setWidgetResizable(true);
    scrollArea->setFrameShape(QFrame::NoFrame);
    QWidget *scrollWidget = new QWidget();
    scrollWidget->setStyleSheet("background-color:white; border-radius:15px;");
    QVBoxLayout *scrollLayout = new QVBoxLayout(scrollWidget);
    scrollLayout->setSpacing(20);
    scrollLayout->setContentsMargins(25,25,25,25);

    QString labelStyle = "QLabel { background-color:transparent; padding:5px; font-size:13px; font-weight:600; color:#374151; }";
    QString editStyle = "QLineEdit, QDateEdit, QSpinBox, QDoubleSpinBox, QComboBox { background-color:#F9FAFB; border:1px solid #D1D5DB; border-radius:8px; padding:12px 16px; font-size:14px; color:#111827; }";

    QLabel *section1 = new QLabel("📋 Informations de Base");
    section1->setStyleSheet("font-size:15px; font-weight:bold; color:#2C5F7C; padding:10px 0px;");
    scrollLayout->addWidget(section1);

    QGridLayout *grid1 = new QGridLayout();
    grid1->setSpacing(15);

    QLineEdit *capacite        = new QLineEdit(); capacite->setStyleSheet(editStyle);
    QLineEdit *localisation    = new QLineEdit(); localisation->setStyleSheet(editStyle);
    QLineEdit *adresseComplete = new QLineEdit(); adresseComplete->setStyleSheet(editStyle);
    QDoubleSpinBox *latitude   = new QDoubleSpinBox(); latitude->setDecimals(6); latitude->setRange(-90,90); latitude->setValue(48.856614); latitude->setStyleSheet(editStyle);
    QDoubleSpinBox *longitude  = new QDoubleSpinBox(); longitude->setDecimals(6); longitude->setRange(-180,180); longitude->setValue(2.352222); longitude->setStyleSheet(editStyle);
    QComboBox *typePropriete   = new QComboBox(); typePropriete->addItems({"Public","Privé","Mixte"}); typePropriete->setStyleSheet(editStyle);

    auto lbl = [&](const QString &t){ QLabel *l=new QLabel(t); l->setStyleSheet(labelStyle); return l; };

    grid1->addWidget(lbl("📦 capacité:"),        0,0); grid1->addWidget(capacite,        0,1);
    grid1->addWidget(lbl("📍 localisation:"),    1,0); grid1->addWidget(localisation,    1,1);
    grid1->addWidget(lbl("🏠 adresse complete:"),2,0); grid1->addWidget(adresseComplete, 2,1);
    grid1->addWidget(lbl("🌐 lattitude:"),       3,0); grid1->addWidget(latitude,        3,1);
    grid1->addWidget(lbl("🌐 Longitude:"),       4,0); grid1->addWidget(longitude,       4,1);
    grid1->addWidget(lbl("🏢 Type de Propriété:"),5,0); grid1->addWidget(typePropriete,  5,1);
    scrollLayout->addLayout(grid1);

    QLabel *section2 = new QLabel("📊 État et Monitoring:");
    section2->setStyleSheet("font-size:15px; font-weight:bold; color:#2C5F7C; padding:10px 0px; margin-top:10px;");
    scrollLayout->addWidget(section2);

    QGridLayout *grid2 = new QGridLayout();
    grid2->setSpacing(15);

    QSpinBox *niveauRemplissage = new QSpinBox(); niveauRemplissage->setSuffix(" %"); niveauRemplissage->setRange(0,100); niveauRemplissage->setStyleSheet(editStyle);
    QDoubleSpinBox *temperature = new QDoubleSpinBox(); temperature->setSuffix(" °C"); temperature->setDecimals(1); temperature->setValue(20.0); temperature->setStyleSheet(editStyle);
    QComboBox *etatConteneur    = new QComboBox(); etatConteneur->addItems({"Opérationnel","En maintenance","Hors service"}); etatConteneur->setStyleSheet(editStyle);
    QDateEdit *dateDerniereCollecte = new QDateEdit(QDate::fromString("01/01/2000","dd/MM/yyyy")); dateDerniereCollecte->setDisplayFormat("dd/MM/yyyy"); dateDerniereCollecte->setStyleSheet(editStyle);
    QLineEdit *typesDechet = new QLineEdit(); typesDechet->setStyleSheet(editStyle);

    grid2->addWidget(lbl("📊 Niveau de Remplissage %"),   0,0); grid2->addWidget(niveauRemplissage,     0,1);
    grid2->addWidget(lbl("🌡️ Température Interne (°C)"),  1,0); grid2->addWidget(temperature,           1,1);
    grid2->addWidget(lbl("✅ État du conteneur"),          2,0); grid2->addWidget(etatConteneur,         2,1);
    grid2->addWidget(lbl("📅 Date Dernière Collecte"),     3,0); grid2->addWidget(dateDerniereCollecte,  3,1);
    grid2->addWidget(lbl("♻️ Types de Déchets Acceptés:"), 4,0); grid2->addWidget(typesDechet,           4,1);
    scrollLayout->addLayout(grid2);

    scrollArea->setWidget(scrollWidget);
    scrollArea->verticalScrollBar()->setStyleSheet(
        "QScrollBar:vertical { background:#F3F4F6; width:10px; border-radius:5px; }"
        "QScrollBar::handle:vertical { background:#D1D5DB; border-radius:5px; min-height:30px; }"
        "QScrollBar::handle:vertical:hover { background:#9CA3AF; }"
        "QScrollBar::add-line:vertical, QScrollBar::sub-line:vertical { height:0px; }");

    containerLayout->addWidget(scrollArea);
    QLabel *note = new QLabel("* Tous les champs sont obligatoires");
    note->setStyleSheet("color:#6E7F91; font-style:italic; font-size:12px;");
    containerLayout->addWidget(note);

    QHBoxLayout *btnLayout = new QHBoxLayout();
    QPushButton *annuler = new QPushButton("✗ Annuler"); annuler->setMinimumHeight(50);
    annuler->setStyleSheet("QPushButton { background-color:#E5E7EB; color:#374151; font-size:15px; font-weight:600; border:none; border-radius:8px; padding:12px 30px; } QPushButton:hover { background-color:#D1D5DB; }");
    QPushButton *ajouter = new QPushButton("✓ Ajouter"); ajouter->setMinimumHeight(50);
    ajouter->setStyleSheet("QPushButton { background:qlineargradient(x1:0,y1:0,x2:0,y2:1,stop:0 #2C5F7C,stop:1 #1B3A57); color:white; font-size:15px; font-weight:600; border:none; border-radius:8px; padding:12px 30px; }");
    btnLayout->addWidget(annuler); btnLayout->addWidget(ajouter);
    containerLayout->addLayout(btnLayout);
    mainLayout->addWidget(container);

    connect(annuler, &QPushButton::clicked, dialog, &QDialog::reject);
    dialog->exec();
}

void MainWindow::on_bouton_ajouter_employe_clicked() { afficherWidgetAjoutEmploye(); }

void MainWindow::afficherWidgetAjoutEmploye()
{
    QDialog *dialog = new QDialog(this);
    dialog->setWindowTitle("+ Ajouter un Employé");
    dialog->setFixedSize(850, 700);
    dialog->setStyleSheet("QDialog { background-color: #EDEDED; }");

    QVBoxLayout *mainLayout = new QVBoxLayout(dialog);
    QFrame *container = new QFrame();
    container->setStyleSheet("QFrame { background-color:#F2F2F2; border-radius:20px; }");
    QVBoxLayout *containerLayout = new QVBoxLayout(container);
    containerLayout->setContentsMargins(30,30,30,30);

    QLabel *titre = new QLabel("👨‍💼 Informations Employé");
    titre->setAlignment(Qt::AlignCenter);
    titre->setStyleSheet("QLabel { font-size:20px; font-weight:bold; color:white; padding:20px; border-radius:18px; background:qlineargradient(x1:0,y1:0,x2:0,y2:1,stop:0 #2C5F7C,stop:1 #1B3A57); }");
    containerLayout->addWidget(titre);
    containerLayout->addSpacing(20);

    QScrollArea *scrollArea = new QScrollArea();
    scrollArea->setWidgetResizable(true);
    scrollArea->setFrameShape(QFrame::NoFrame);
    QWidget *scrollWidget = new QWidget();
    scrollWidget->setStyleSheet("background-color:white; border-radius:15px;");
    QVBoxLayout *scrollLayout = new QVBoxLayout(scrollWidget);
    scrollLayout->setSpacing(20);
    scrollLayout->setContentsMargins(20,20,20,20);

    QString labelStyle = "QLabel { background-color:transparent; padding:5px; font-size:13px; font-weight:600; color:#374151; }";
    QString editStyle  = "QLineEdit { background-color:#F9FAFB; border:1px solid #D1D5DB; border-radius:8px; padding:12px 16px; font-size:14px; color:#111827; } QLineEdit:hover { border:1px solid #2C5F7C; } QLineEdit:focus { border:2px solid #2C5F7C; padding:11px 15px; }";
    QString comboStyle = "QComboBox { background-color:#F9FAFB; border:1px solid #D1D5DB; border-radius:8px; padding:12px 16px; font-size:14px; color:#111827; } QComboBox:hover { border:1px solid #2C5F7C; }";

    QLineEdit *nom      = new QLineEdit(); nom->setStyleSheet(editStyle);
    QLineEdit *prenom   = new QLineEdit(); prenom->setStyleSheet(editStyle);
    QLineEdit *email    = new QLineEdit(); email->setStyleSheet(editStyle);
    QLineEdit *telephone= new QLineEdit(); telephone->setStyleSheet(editStyle);
    QLineEdit *cin      = new QLineEdit(); cin->setStyleSheet(editStyle);
    QComboBox *poste    = new QComboBox(); poste->addItems({"Technicien","Administratif","Manager","Agent terrain"}); poste->setStyleSheet(comboStyle);

    auto addField = [&](const QString &text, QWidget *field) {
        QLabel *label = new QLabel(text); label->setStyleSheet(labelStyle);
        scrollLayout->addWidget(label);
        scrollLayout->addWidget(field);
    };

    addField("👤 Nom *",       nom);
    addField("👤 Prénom *",    prenom);
    QLabel *lblPoste = new QLabel("💼 Poste *"); lblPoste->setStyleSheet(labelStyle);
    scrollLayout->addWidget(lblPoste); scrollLayout->addWidget(poste);
    addField("📧 Email *",     email);
    addField("📞 Téléphone *", telephone);
    addField("🆔 CIN",         cin);

    scrollArea->setWidget(scrollWidget);
    scrollArea->verticalScrollBar()->setStyleSheet(
        "QScrollBar:vertical { background:#F3F4F6; width:10px; border-radius:5px; }"
        "QScrollBar::handle:vertical { background:#D1D5DB; border-radius:5px; min-height:30px; }"
        "QScrollBar::handle:vertical:hover { background:#9CA3AF; }"
        "QScrollBar::add-line:vertical, QScrollBar::sub-line:vertical { height:0px; }");

    containerLayout->addWidget(scrollArea);
    QLabel *note = new QLabel("* Champs obligatoires");
    note->setStyleSheet("color:#6E7F91; font-style:italic; font-size:12px;");
    containerLayout->addWidget(note);

    QHBoxLayout *btnLayout = new QHBoxLayout();
    QPushButton *annuler = new QPushButton("✗ Annuler"); annuler->setMinimumHeight(50);
    annuler->setStyleSheet("QPushButton { background-color:#E5E7EB; color:#374151; font-size:15px; font-weight:600; border:none; border-radius:8px; padding:12px 30px; } QPushButton:hover { background-color:#D1D5DB; }");
    QPushButton *ajouter = new QPushButton("✓ Ajouter l'employé"); ajouter->setMinimumHeight(50);
    ajouter->setStyleSheet("QPushButton { background:qlineargradient(x1:0,y1:0,x2:0,y2:1,stop:0 #2C5F7C,stop:1 #1B3A57); color:white; font-size:15px; font-weight:600; border:none; border-radius:8px; padding:12px 30px; }");
    btnLayout->addWidget(annuler); btnLayout->addWidget(ajouter);
    containerLayout->addLayout(btnLayout);
    mainLayout->addWidget(container);

    connect(annuler, &QPushButton::clicked, dialog, &QDialog::reject);
    dialog->exec();
}
