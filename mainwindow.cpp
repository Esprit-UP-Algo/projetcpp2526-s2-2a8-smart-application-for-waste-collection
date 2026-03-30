#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPrinter>
#include <QPrintDialog>
#include <QPainter>
#include <QGraphicsDropShadowEffect>
#include <QPropertyAnimation>
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
#include <QDate>
#include <QTime>
#include <QSqlQuery>
#include <QSqlError>
#include <QButtonGroup>
#include <QHeaderView>
#include <QInputDialog>
#include <QRegularExpression>
#include <QPrinter>
#include <QTextEdit>
#include <QFileDialog>
#include <QTextDocument>
#include <QtMath>
#include <QTextBrowser>
#include <QProgressBar>
#include <QtCharts/QChartView>
#include <QtCharts/QPieSeries>
#include <QtCharts/QChart>
#include <QtWidgets/QVBoxLayout>
#include <QHBoxLayout>   // Pour QHBoxLayout
#include <QVBoxLayout>   // Si tu utilises aussi QVBoxLayout
#include <QWidget>       // Pour QWidget
#include <QString>       // Pour QString

// ================================================================
// === CONSTRUCTEUR & DESTRUCTEUR =================================
// ================================================================

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

    // Configuration initiale tableau CLIENT
    ui->tableWidget_Recyclage->setColumnCount(9);
    if (ui->tableWidget_Recyclage->columnCount() > 0)
        ui->tableWidget_Recyclage->setColumnHidden(0, true);
    ui->tableWidget_Recyclage->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableWidget_Recyclage->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableWidget_Recyclage->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tableWidget_Recyclage->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableWidget_Recyclage->verticalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);

    afficherListeClients();
    afficherCollectes();      // ← ajoute ici
    afficherConteneurs();     // ← ajoute ici
    afficherRecyclages();     // ← ajoute ici
    ui->stackedWidget->setCurrentIndex(1);
}

MainWindow::~MainWindow()
{
    delete ui;
}

// ================================================================
// === UTILITAIRES ================================================
// ================================================================

void MainWindow::showMessage(QWidget *parent, const QString &titre,
                             const QString &message, const QString &type)
{
    QDialog *msg = new QDialog(parent);
    msg->setWindowTitle(titre);
    msg->setFixedSize(440, 220);
    msg->setStyleSheet("QDialog { background-color:#1E1E2E; border-radius:14px; }");

    QVBoxLayout *layout = new QVBoxLayout(msg);
    layout->setContentsMargins(0, 0, 0, 24);
    layout->setSpacing(0);

    QString couleur = "#2C5F7C";
    QString icone   = "ℹ️";
    if (type == "success") { couleur = "#1A7A4A"; icone = "✅"; }
    if (type == "warning") { couleur = "#E67E22"; icone = "⚠️"; }
    if (type == "error")   { couleur = "#C0392B"; icone = "❌"; }

    // ── Barre titre colorée
    QWidget *header = new QWidget();
    header->setFixedHeight(62);
    header->setStyleSheet(QString(
                              "QWidget { background-color:%1;"
                              "border-top-left-radius:14px; border-top-right-radius:14px; }"
                              ).arg(couleur));
    QHBoxLayout *hLay = new QHBoxLayout(header);
    hLay->setContentsMargins(22, 0, 22, 0);
    hLay->setSpacing(10);

    QLabel *lblIco = new QLabel(icone + "  " + titre);
    lblIco->setStyleSheet(
        "font-size:15px; font-weight:bold; color:white; background:transparent;"
        );
    hLay->addWidget(lblIco);
    layout->addWidget(header);

    // ── Message
    QLabel *lblMsg = new QLabel(message);
    lblMsg->setAlignment(Qt::AlignCenter);
    lblMsg->setWordWrap(true);
    lblMsg->setStyleSheet(
        "QLabel { font-size:13px; color:#C8C8D8; background:transparent;"
        "padding:18px 28px 10px 28px; }"
        );
    layout->addWidget(lblMsg);
    layout->addStretch();

    // ── Bouton OK
    QPushButton *ok = new QPushButton("OK");
    ok->setFixedSize(110, 40);
    ok->setStyleSheet(QString(
                          "QPushButton { background-color:%1; color:white; font-size:14px;"
                          "font-weight:600; border:none; border-radius:8px; }"
                          "QPushButton:hover { opacity:0.85; }"
                          ).arg(couleur));
    connect(ok, &QPushButton::clicked, msg, &QDialog::accept);

    QHBoxLayout *btnL = new QHBoxLayout();
    btnL->addStretch();
    btnL->addWidget(ok);
    btnL->addStretch();
    layout->addLayout(btnL);

    msg->exec();
}

// ================================================================
// === SLOTS GÉNÉRAUX (NAVIGATION) ================================
// ================================================================

void MainWindow::on_mdp_clicked()         { ui->stackedWidget->setCurrentIndex(0); }
void MainWindow::on_cnx_clicked()
{
    ui->stackedWidget->setCurrentIndex(2);
    ui->stackedWidget_2->setCurrentIndex(11);
    afficherEmployes();
}
void MainWindow::on_pushButton_44_clicked() { ui->stackedWidget->setCurrentIndex(8); }
void MainWindow::on_pushButton_16_clicked() { ui->stackedWidget->setCurrentIndex(8); }
void MainWindow::on_pushButton_30_clicked() { ui->stackedWidget_2->setCurrentIndex(2); }
void MainWindow::on_retour_clicked()        { ui->stackedWidget->setCurrentIndex(1); }
void MainWindow::on_acceuil_clicked()       { ui->stackedWidget_2->setCurrentIndex(11); }
void MainWindow::on_deconnection_clicked()  { ui->stackedWidget->setCurrentIndex(1); }
void MainWindow::on_recyclage_clicked()     { ui->stackedWidget_2->setCurrentIndex(0); afficherRecyclages(); }
void MainWindow::on_CONTENEUR_clicked()     { ui->stackedWidget_2->setCurrentIndex(6); afficherConteneurs(); }
void MainWindow::on_TOURNEE_clicked()       { ui->stackedWidget_2->setCurrentIndex(9); }
void MainWindow::on_frame_20_customContextMenuRequested(const QPoint &pos) { Q_UNUSED(pos); }

// ================================================================
// === MODULE CLIENT — NAVIGATION =================================
// ================================================================

void MainWindow::on_pushButton_36_clicked()        { ui->stackedWidget_2->setCurrentIndex(4); }
void MainWindow::on_pushButton_37_clicked()
{
    ui->stackedWidget_2->setCurrentIndex(2);
    afficherListeClients();
}
void MainWindow::on_pushButton_rechercher_3_clicked() { ui->stackedWidget_2->setCurrentIndex(5); }
void MainWindow::on_conn_clicked() {}
void MainWindow::on_dec_clicked()  {}

// ================================================================
// === MODULE CLIENT — AFFICHAGE LISTE ============================
// ================================================================

// ================================================================
// === MODULE CLIENT — AFFICHAGE LISTE ============================
// ================================================================
void MainWindow::afficherListeClients()
{
    QStringList headers = {
        "🆔 ID", "👤 Nom", "👤 Prénom", "🏢 Type",
        "📍 Zone", "📞 Téléphone", "⚙️ Statut", "🏠 Adresse", "👷 CIN Employé"
    };

    ui->tableWidget_client->clear();
    ui->tableWidget_client->setColumnCount(headers.size());
    ui->tableWidget_client->setHorizontalHeaderLabels(headers);
    ui->tableWidget_client->setRowCount(0);
    ui->tableWidget_client->setSortingEnabled(false);

    // ═══════════════════════════════════════════
    //   STYLE FLAT DASHBOARD BLEU
    // ═══════════════════════════════════════════
    ui->tableWidget_client->setStyleSheet(R"(
        QTableWidget {
            background-color: #f0f4f8;
            alternate-background-color: #e8edf2;
            border: none;
            gridline-color: transparent;
            font-size: 13px;
            color: #2d3436;
        }
        QTableWidget::item {
            padding: 10px 16px;
            border: none;
            border-bottom: 1px solid #dfe6ed;
            color: #2d3436;
        }
        QTableWidget::item:selected {
            background-color: #2C5F7C;
            color: #ffffff;
        }
        QTableWidget::item:hover {
            background-color: #d6e4f0;
            color: #1B3A57;
        }
        QHeaderView::section {
            background: qlineargradient(
                x1:0, y1:0, x2:0, y2:1,
                stop:0 #2C5F7C,
                stop:1 #1B3A57
            );
            color: #ffffff;
            font-weight: bold;
            font-size: 13px;
            padding: 12px 16px;
            border: none;
            border-right: 1px solid #3A6EA5;
        }
        QScrollBar:vertical {
            background: #e8edf2;
            width: 7px;
            border-radius: 4px;
        }
        QScrollBar::handle:vertical {
            background: #2C5F7C;
            border-radius: 4px;
            min-height: 30px;
        }
        QScrollBar:horizontal {
            background: #e8edf2;
            height: 7px;
            border-radius: 4px;
        }
        QScrollBar::handle:horizontal {
            background: #2C5F7C;
            border-radius: 4px;
        }
        QScrollBar::add-line, QScrollBar::sub-line { background: none; }
    )");

    ui->tableWidget_client->setAlternatingRowColors(true);
    ui->tableWidget_client->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableWidget_client->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tableWidget_client->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableWidget_client->verticalHeader()->setVisible(false);
    ui->tableWidget_client->setShowGrid(false);

    // ═══════════════════════════════════════════
    //   REQUÊTE SQL
    // ═══════════════════════════════════════════
    QList<Client> liste = Client::getAll();
    if (liste.isEmpty() && /* vérification erreur */ false) {
        showMessage(this, "Erreur", "Impossible de charger les clients.", "error");
        return;
    }

    int row = 0;
    for (const Client &c : liste) {
        ui->tableWidget_client->insertRow(row);

        QStringList valeurs = {
            QString::number(c.getId()),
            c.getNom(),
            c.getPrenom(),
            c.getType(),
            c.getZone(),
            c.getTelephone(),
            c.getStatut(),
            c.getAdresse(),
            c.getCinEmploye()
        };

        for (int col = 0; col < 9; col++) {
            QString valeur = valeurs[col];

            if (col == 6) {
                QString s = valeur.toLower();
                if      (s == "actif")    valeur = "✅  Actif";
                else if (s == "inactif")  valeur = "❌  Inactif";
                else if (s == "suspendu") valeur = "⏸️  Suspendu";
                else                      valeur = "❓  " + valeur;
            }

            QTableWidgetItem *item = new QTableWidgetItem(valeur);

            if (col == 0) {
                ui->tableWidget_client->setItem(row, col, item);
                ui->tableWidget_client->setColumnHidden(0, true);
                continue;
            }

            item->setTextAlignment(Qt::AlignVCenter | Qt::AlignLeft);

            if (col == 1) {
                item->setFont(QFont("Segoe UI", 13, QFont::Bold));
                item->setForeground(QColor("#1B3A57"));
            }
            if (col == 6) {
                QString s = c.getStatut().toLower();
                if      (s == "actif")    item->setForeground(QColor("#1A7A4A"));
                else if (s == "inactif")  item->setForeground(QColor("#C0392B"));
                else if (s == "suspendu") item->setForeground(QColor("#E67E22"));
                item->setFont(QFont("Segoe UI", 12, QFont::Bold));
            }
            if (col == 4) item->setForeground(QColor("#2C5F7C"));

            if (row % 2 == 0) item->setBackground(QColor("#ffffff"));
            else               item->setBackground(QColor("#f0f4f8"));

            ui->tableWidget_client->setItem(row, col, item);
        }

        ui->tableWidget_client->setRowHeight(row, 44);
        ++row;
    }

    // ═══════════════════════════════════════════
    //   COLONNES
    // ═══════════════════════════════════════════
    ui->tableWidget_client->setColumnHidden(0, true);
    ui->tableWidget_client->horizontalHeader()
        ->setSectionResizeMode(QHeaderView::ResizeToContents);
    ui->tableWidget_client->horizontalHeader()->setStretchLastSection(true);
    ui->tableWidget_client->horizontalHeader()->setMinimumSectionSize(90);
    ui->tableWidget_client->setSortingEnabled(true);
}


// ================================================================
// === MODULE CLIENT — SUPPRESSION ================================
// ================================================================
void MainWindow::on_bouttonsupprimerclient_clicked()
{
    int row = ui->tableWidget_client->currentRow();
    if (row < 0) {
        showMessage(this, "Attention",
                    "⚠️ Veuillez sélectionner un client dans le tableau avant de supprimer !",
                    "warning");
        return;
    }

    // Récupère l'ID depuis la colonne 0 (cachée mais présente)
    QTableWidgetItem *idItem = ui->tableWidget_client->item(row, 0);
    if (!idItem || idItem->text().trimmed().isEmpty()) {
        showMessage(this, "Erreur", "Impossible de récupérer l'ID du client.", "error");
        return;
    }

    int idClient     = idItem->text().toInt();
    QString nomClient = ui->tableWidget_client->item(row, 1)->text()
                        + " " + ui->tableWidget_client->item(row, 2)->text();

    QMessageBox msgBox(this);
    msgBox.setWindowTitle("Confirmer la suppression");
    msgBox.setText("<b>Voulez-vous vraiment supprimer ce client ?</b>");
    msgBox.setInformativeText("👤 " + nomClient + "\n🆔 ID : " + QString::number(idClient));
    msgBox.setIcon(QMessageBox::Warning);
    msgBox.setStandardButtons(QMessageBox::StandardButtons(QMessageBox::Yes | QMessageBox::No)); // ✅
    msgBox.setDefaultButton(QMessageBox::No);
    msgBox.button(QMessageBox::Yes)->setText("🗑️ Oui, supprimer");
    msgBox.button(QMessageBox::No)->setText("✗ Annuler");

    if (msgBox.exec() == QMessageBox::Yes) {
        if (Client::supprimer(idClient)) {
            showMessage(this, "Succès", "✅ Client supprimé avec succès !", "success");
            afficherListeClients();
        } else {
            showMessage(this, "Erreur", "Impossible de supprimer ce client.", "error");
        }
    }
}


// ================================================================
// === MODULE CLIENT — MODIFICATION ===============================
// ================================================================
void MainWindow::on_bouttonmodifierclient_clicked()
{
    int row = ui->tableWidget_client->currentRow();
    if (row < 0) {
        showMessage(this, "Attention",
                    "⚠️ Veuillez sélectionner un client dans le tableau avant de modifier !",
                    "warning");
        return;
    }

    // Récupère l'ID depuis la colonne 0 (cachée mais présente)
    QTableWidgetItem *idItem = ui->tableWidget_client->item(row, 0);
    if (!idItem || idItem->text().trimmed().isEmpty()) {
        showMessage(this, "Erreur", "Impossible de récupérer l'ID du client.", "error");
        return;
    }

    afficherWidgetModifierClient(idItem->text().toInt());
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
        "border-radius:18px;"
        "background:qlineargradient(x1:0,y1:0,x2:0,y2:1,"
        "stop:0 #2C5F7C, stop:1 #1B3A57); }"
        );
    containerLayout->addWidget(titre);
    containerLayout->addSpacing(20);

    QWidget *contentWidget = new QWidget();
    contentWidget->setStyleSheet("background-color:white; border-radius:15px;");
    QGridLayout *gridLayout = new QGridLayout(contentWidget);
    gridLayout->setSpacing(15);
    gridLayout->setContentsMargins(25, 25, 25, 25);

    QString labelStyle =
        "QLabel { background-color:transparent; padding:5px;"
        "font-size:13px; font-weight:600; color:#374151; }";
    QString editStyle =
        "QLineEdit { background-color:#F9FAFB; border:1px solid #D1D5DB;"
        "border-radius:8px; padding:12px 16px; font-size:14px; color:#111827; }"
        "QLineEdit:hover { border:1px solid #2C5F7C; background-color:#FFFFFF; }"
        "QLineEdit:focus { border:2px solid #2C5F7C; background-color:#FFFFFF; padding:11px 15px; }";

    QLineEdit *nom       = new QLineEdit(); nom->setStyleSheet(editStyle);
    QLineEdit *prenom    = new QLineEdit(); prenom->setStyleSheet(editStyle);
    QLineEdit *telephone = new QLineEdit(); telephone->setStyleSheet(editStyle);
    QLineEdit *cin       = new QLineEdit(); cin->setStyleSheet(editStyle);
    QLineEdit *zone      = new QLineEdit(); zone->setStyleSheet(editStyle);
    QLineEdit *type      = new QLineEdit(); type->setStyleSheet(editStyle);
    QLineEdit *adresse   = new QLineEdit(); adresse->setStyleSheet(editStyle);
    QLineEdit *statut    = new QLineEdit(); statut->setStyleSheet(editStyle);

    QLabel *lblNom  = new QLabel(tr("👤 Nom :"));           lblNom->setStyleSheet(labelStyle);
    QLabel *lblPrn  = new QLabel(tr("👤 Prénom :"));        lblPrn->setStyleSheet(labelStyle);
    QLabel *lblTel  = new QLabel(tr("📞 Téléphone :"));     lblTel->setStyleSheet(labelStyle);
    QLabel *lblCIN  = new QLabel(tr("🆔 CIN :"));           lblCIN->setStyleSheet(labelStyle);
    QLabel *lblZone = new QLabel(tr("📍 Zone :"));          lblZone->setStyleSheet(labelStyle);
    QLabel *lblTyp  = new QLabel(tr("🏢 Type :"));          lblTyp->setStyleSheet(labelStyle);
    QLabel *lblStt  = new QLabel(tr("⚙️ Statut compte :")); lblStt->setStyleSheet(labelStyle);
    QLabel *lblAdr  = new QLabel(tr("🏠 Adresse :"));       lblAdr->setStyleSheet(labelStyle);

    gridLayout->addWidget(lblNom,  0, 0); gridLayout->addWidget(nom,      0, 1);
    gridLayout->addWidget(lblPrn,  1, 0); gridLayout->addWidget(prenom,   1, 1);
    gridLayout->addWidget(lblTel,  2, 0); gridLayout->addWidget(telephone,2, 1);
    gridLayout->addWidget(lblCIN,  0, 2); gridLayout->addWidget(cin,      0, 3);
    gridLayout->addWidget(lblZone, 1, 2); gridLayout->addWidget(zone,     1, 3);
    gridLayout->addWidget(lblTyp,  2, 2); gridLayout->addWidget(type,     2, 3);
    gridLayout->addWidget(lblStt,  3, 2); gridLayout->addWidget(statut,   3, 3);
    gridLayout->addWidget(lblAdr,  3, 0); gridLayout->addWidget(adresse,  3, 1);

    containerLayout->addWidget(contentWidget);
    containerLayout->addSpacing(15);

    QHBoxLayout *btnLayout = new QHBoxLayout();
    btnLayout->setSpacing(15);

    QPushButton *annuler = new QPushButton(tr("✗ Annuler"));
    annuler->setMinimumHeight(50);
    annuler->setStyleSheet(
        "QPushButton { background-color:#E5E7EB; color:#374151; font-size:15px;"
        "font-weight:600; border:none; border-radius:8px; padding:12px 30px; }"
        "QPushButton:hover { background-color:#D1D5DB; }"
        );

    QPushButton *enregistrer = new QPushButton(tr("✓ Enregistrer"));
    enregistrer->setMinimumHeight(50);
    enregistrer->setStyleSheet(
        "QPushButton { background:qlineargradient(x1:0,y1:0,x2:0,y2:1,"
        "stop:0 #2C5F7C, stop:1 #1B3A57); color:white; font-size:15px;"
        "font-weight:600; border:none; border-radius:8px; padding:12px 30px; }"
        "QPushButton:hover { background:qlineargradient(x1:0,y1:0,x2:0,y2:1,"
        "stop:0 #3A6EA5, stop:1 #2C5F7C); }"
        );

    btnLayout->addWidget(annuler);
    btnLayout->addWidget(enregistrer);
    containerLayout->addLayout(btnLayout);
    mainLayout->addWidget(container);

    connect(annuler, &QPushButton::clicked, dialog, &QDialog::reject);

    // Chargement des données
    Client c = Client::getById(idClient);
    if (c.getId() == 0) {
        showMessage(this, "Erreur", "Client introuvable.", "error");
        delete dialog;
        return;
    }
    nom->setText(c.getNom());
    prenom->setText(c.getPrenom());
    cin->setText(c.getCin());
    telephone->setText(c.getTelephone());
    adresse->setText(c.getAdresse());
    type->setText(c.getType());
    statut->setText(c.getStatut());
    zone->setText(c.getZone());

    connect(enregistrer, &QPushButton::clicked, this, [=]() {
        if (nom->text().trimmed().isEmpty() || prenom->text().trimmed().isEmpty() ||
            telephone->text().trimmed().isEmpty() || cin->text().trimmed().isEmpty() ||
            zone->text().trimmed().isEmpty() || type->text().trimmed().isEmpty() ||
            adresse->text().trimmed().isEmpty()) {
            showMessage(dialog, "Erreur", "Tous les champs sont obligatoires !", "error");
            return;
        }
        Client cModif(idClient,
                      nom->text().trimmed(),
                      prenom->text().trimmed(),
                      cin->text().trimmed(),
                      telephone->text().trimmed(),
                      adresse->text().trimmed(),
                      type->text().trimmed(),
                      statut->text().trimmed(),
                      zone->text().trimmed(),
                      "");  // CIN_employe non modifiable ici

        if (cModif.modifier()) {
            showMessage(dialog, "Succès", "✅ Client modifié avec succès !", "success");
            dialog->accept();
            afficherListeClients();
        } else {
            showMessage(dialog, "Erreur", "Impossible de modifier ce client.", "error");
        }
    });

    dialog->exec();
}
// ================================================================
// === MODULE CLIENT — AJOUT =====================================
// ================================================================

void MainWindow::on_bouttonajouterclient_clicked()
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
    container->setStyleSheet("QFrame { background-color:#F2F2F2; border-radius:20px; }");
    QVBoxLayout *containerLayout = new QVBoxLayout(container);
    containerLayout->setContentsMargins(30, 30, 30, 30);

    QLabel *titre = new QLabel("👤 Informations Client");
    titre->setAlignment(Qt::AlignCenter);
    titre->setStyleSheet(
        "QLabel { font-size:20px; font-weight:bold; color:white; padding:20px;"
        "border-radius:18px;"
        "background:qlineargradient(x1:0,y1:0,x2:0,y2:1,"
        "stop:0 #2C5F7C, stop:1 #1B3A57); }"
        );
    containerLayout->addWidget(titre);
    containerLayout->addSpacing(20);

    QWidget *contentWidget = new QWidget();
    contentWidget->setStyleSheet("background-color:white; border-radius:15px;");
    QGridLayout *gridLayout = new QGridLayout(contentWidget);
    gridLayout->setSpacing(15);
    gridLayout->setContentsMargins(25, 25, 25, 25);

    QString labelStyle =
        "QLabel { background-color:transparent; padding:5px;"
        "font-size:13px; font-weight:600; color:#374151; }";
    QString editStyle =
        "QLineEdit { background-color:#F9FAFB; border:1px solid #D1D5DB;"
        "border-radius:8px; padding:12px 16px; font-size:14px; color:#111827; }"
        "QLineEdit:hover { border:1px solid #2C5F7C; background-color:#FFFFFF; }"
        "QLineEdit:focus { border:2px solid #2C5F7C; background-color:#FFFFFF; padding:11px 15px; }";

    QLineEdit *nom        = new QLineEdit(); nom->setStyleSheet(editStyle);
    QLineEdit *prenom     = new QLineEdit(); prenom->setStyleSheet(editStyle);
    QLineEdit *telephone  = new QLineEdit(); telephone->setStyleSheet(editStyle);
    QLineEdit *cin        = new QLineEdit(); cin->setStyleSheet(editStyle);
    QLineEdit *zone       = new QLineEdit(); zone->setStyleSheet(editStyle);
    QLineEdit *type       = new QLineEdit(); type->setStyleSheet(editStyle);
    QLineEdit *adresse    = new QLineEdit(); adresse->setStyleSheet(editStyle);
    QLineEdit *cinEmploye = new QLineEdit(); cinEmploye->setStyleSheet(editStyle);
    cinEmploye->setPlaceholderText("CIN de l'employé responsable");

    QLabel *lblNom  = new QLabel("👤 Nom :");         lblNom->setStyleSheet(labelStyle);
    QLabel *lblPrn  = new QLabel("👤 Prénom :");      lblPrn->setStyleSheet(labelStyle);
    QLabel *lblTel  = new QLabel("📞 Téléphone :");   lblTel->setStyleSheet(labelStyle);
    QLabel *lblCIN  = new QLabel("🆔 CIN :");         lblCIN->setStyleSheet(labelStyle);
    QLabel *lblZone = new QLabel("📍 Zone :");        lblZone->setStyleSheet(labelStyle);
    QLabel *lblTyp  = new QLabel("🏢 Type :");        lblTyp->setStyleSheet(labelStyle);
    QLabel *lblAdr  = new QLabel("🏠 Adresse :");     lblAdr->setStyleSheet(labelStyle);
    QLabel *lblEmp  = new QLabel("👷 CIN Employé :"); lblEmp->setStyleSheet(labelStyle);

    gridLayout->addWidget(lblNom,  0, 0); gridLayout->addWidget(nom,        0, 1);
    gridLayout->addWidget(lblPrn,  1, 0); gridLayout->addWidget(prenom,     1, 1);
    gridLayout->addWidget(lblTel,  2, 0); gridLayout->addWidget(telephone,  2, 1);
    gridLayout->addWidget(lblCIN,  0, 2); gridLayout->addWidget(cin,        0, 3);
    gridLayout->addWidget(lblZone, 1, 2); gridLayout->addWidget(zone,       1, 3);
    gridLayout->addWidget(lblTyp,  2, 2); gridLayout->addWidget(type,       2, 3);
    gridLayout->addWidget(lblAdr,  3, 0); gridLayout->addWidget(adresse,    3, 1);
    gridLayout->addWidget(lblEmp,  3, 2); gridLayout->addWidget(cinEmploye, 3, 3);

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
        "QPushButton { background-color:#E5E7EB; color:#374151; font-size:15px;"
        "font-weight:600; border:none; border-radius:8px; padding:12px 30px; }"
        "QPushButton:hover { background-color:#D1D5DB; }"
        );

    QPushButton *ajouter = new QPushButton("✓ Ajouter");
    ajouter->setMinimumHeight(50);
    ajouter->setStyleSheet(
        "QPushButton { background:qlineargradient(x1:0,y1:0,x2:0,y2:1,"
        "stop:0 #2C5F7C, stop:1 #1B3A57); color:white; font-size:15px;"
        "font-weight:600; border:none; border-radius:8px; padding:12px 30px; }"
        "QPushButton:hover { background:qlineargradient(x1:0,y1:0,x2:0,y2:1,"
        "stop:0 #3A6EA5, stop:1 #2C5F7C); }"
        );

    btnLayout->addWidget(annuler);
    btnLayout->addWidget(ajouter);
    containerLayout->addLayout(btnLayout);
    mainLayout->addWidget(container);

    connect(annuler, &QPushButton::clicked, dialog, &QDialog::reject);

    connect(ajouter, &QPushButton::clicked, this, [=]() {
        if (nom->text().trimmed().isEmpty()      || prenom->text().trimmed().isEmpty()   ||
            telephone->text().trimmed().isEmpty() || cin->text().trimmed().isEmpty()      ||
            zone->text().trimmed().isEmpty()      || type->text().trimmed().isEmpty()     ||
            adresse->text().trimmed().isEmpty()   || cinEmploye->text().trimmed().isEmpty())
        {
            showMessage(dialog, "Champs manquants", "Merci de remplir tous les champs obligatoires.", "warning");
            return;
        }

        // Vérification employé via la classe Client
        if (!Client::employeExiste(cinEmploye->text().trimmed())) {
            showMessage(dialog, "Employé introuvable", "Le CIN employé saisi n'existe pas dans la base.", "warning");
            return;
        }

        // Création de l'objet Client et appel de ajouter()
        Client c(0,
                 nom->text().trimmed(),
                 prenom->text().trimmed(),
                 cin->text().trimmed(),
                 telephone->text().trimmed(),
                 adresse->text().trimmed(),
                 type->text().trimmed(),
                 "actif",
                 zone->text().trimmed(),
                 cinEmploye->text().trimmed());

        if (!c.ajouter()) {
            showMessage(dialog, "Erreur", "Impossible d'ajouter le client.", "error");
            return;
        }
        showMessage(dialog, "Succès", "✅ Client ajouté avec succès !", "success");
        dialog->accept();
        afficherListeClients();
    });

    dialog->exec();
}




// ================================================================
// === MODULE CLIENT — RECHERCHE ==================================
// ================================================================

void MainWindow::on_bouttonrechercheclient_clicked()
{
    QString recherche = ui->barrerechercheclient->text().trimmed();

    if (recherche.isEmpty()) {
        afficherListeClients();
        return;
    }

    QList<Client> liste = Client::rechercher(recherche);

    ui->tableWidget_client->setRowCount(0);
    ui->tableWidget_client->setColumnCount(9);
    ui->tableWidget_client->setColumnHidden(0, true);
    ui->tableWidget_client->setHorizontalHeaderLabels({
        "ID", "Nom", "Prenom", "Type", "Zone",
        "Telephone", "Statut", "Adresse", "CIN Employe"
    });

    int row = 0;
    for (const Client &c : liste) {
        ui->tableWidget_client->insertRow(row);
        QStringList vals = {
            QString::number(c.getId()), c.getNom(), c.getPrenom(),
            c.getType(), c.getZone(), c.getTelephone(),
            c.getStatut(), c.getAdresse(), c.getCinEmploye()
        };
        for (int col = 0; col < 9; col++)
            ui->tableWidget_client->setItem(row, col, new QTableWidgetItem(vals[col]));
        row++;
    }

    if (row == 0)
        showMessage(this, "Recherche",
                    "Aucun client trouvé pour : " + recherche, "warning");
}
// ================================================================
// === MODULE CLIENT — TRI ========================================
// ================================================================

void MainWindow::on_triclient_currentIndexChanged(int index)
{
    QStringList colonnes = {
        "", "Nom", "Prenom", "Type_client",
        "Zone", "Telephone", "Statut_compte"
    };

    if (index <= 0 || index >= colonnes.size()) {
        afficherListeClients();
        return;
    }

    QSqlQuery query;
    if (!query.exec(
            "SELECT ID_client, Nom, Prenom, Type_client, Zone, Telephone, "
            "Statut_compte, Adresse_complete, CIN_employe "
            "FROM CLIENTS ORDER BY " + colonnes[index]))
    {
        showMessage(this, "Erreur SQL", query.lastError().text(), "error");
        return;
    }

    ui->tableWidget_Recyclage->setRowCount(0);
    ui->tableWidget_Recyclage->setColumnCount(9);
    ui->tableWidget_Recyclage->setColumnHidden(0, true);
    ui->tableWidget_Recyclage->setHorizontalHeaderLabels({
        "ID", "Nom", "Prenom", "Type", "Zone",
        "Telephone", "Statut", "Adresse", "CIN Employe"
    });

    int row = 0;
    while (query.next()) {
        ui->tableWidget_Recyclage->insertRow(row);
        for (int col = 0; col < 9; col++)
            ui->tableWidget_Recyclage->setItem(row, col,
                                       new QTableWidgetItem(query.value(col).toString()));
        row++;
    }
}

// ================================================================
// === MODULE CLIENT — EXPORT PDF =================================
// ================================================================

void MainWindow::on_bouttonexporterclient_clicked()
{
    exporterClientsCSV();
}

void MainWindow::exporterClientsCSV()
{
    QSqlQuery query;
    if (!query.exec(
            "SELECT ID_client, Nom, Prenom, Type_client, Zone, "
            "Telephone, Statut_compte, Adresse_complete, CIN_employe "
            "FROM CLIENTS ORDER BY Nom"))
    {
        showMessage(this, "Erreur SQL", query.lastError().text(), "error");
        return;
    }

    QString html;
    html += "<html><head><meta charset='utf-8'><style>"
            "body{font-family:Arial;font-size:12px;}"
            "h1{text-align:center;color:#2C5F7C;}"
            "table{width:100%;border-collapse:collapse;margin-top:20px;}"
            "th{background:#2C5F7C;color:white;padding:8px;text-align:left;}"
            "td{border:1px solid #ddd;padding:6px;}"
            "tr:nth-child(even){background:#f2f2f2;}"
            "</style></head><body>";
    html += "<h1>Liste des Clients</h1>";
    html += "<p style='text-align:center;'>Exporté le : "
            + QDate::currentDate().toString("dd/MM/yyyy") + "</p>";
    html += "<table><tr><th>ID</th><th>Nom</th><th>Prenom</th><th>Type</th>"
            "<th>Zone</th><th>Telephone</th><th>Statut</th>"
            "<th>Adresse</th><th>CIN Employe</th></tr>";

    while (query.next()) {
        html += "<tr>";
        for (int col = 0; col < 9; col++)
            html += "<td>" + query.value(col).toString() + "</td>";
        html += "</tr>";
    }
    html += "</table></body></html>";

    QDialog *dlg = new QDialog(this);
    dlg->setWindowTitle("Export Clients");
    dlg->setFixedSize(900, 600);
    QVBoxLayout *layout = new QVBoxLayout(dlg);

    QTextEdit *preview = new QTextEdit();
    preview->setReadOnly(true);
    preview->setHtml(html);
    layout->addWidget(preview);

    QHBoxLayout *btnL = new QHBoxLayout();

    QPushButton *btnImprimer = new QPushButton("🖨️ Imprimer / Enregistrer PDF");
    btnImprimer->setMinimumHeight(45);
    btnImprimer->setStyleSheet(
        "QPushButton{background:#2C5F7C;color:white;font-size:14px;"
        "font-weight:600;border:none;border-radius:8px;padding:10px 25px;}"
        "QPushButton:hover{background:#3A6EA5;}");

    QPushButton *btnFermer = new QPushButton("Fermer");
    btnFermer->setMinimumHeight(45);
    btnFermer->setStyleSheet(
        "QPushButton{background:#E5E7EB;color:#374151;font-size:14px;"
        "font-weight:600;border:none;border-radius:8px;padding:10px 25px;}"
        "QPushButton:hover{background:#D1D5DB;}");

    btnL->addWidget(btnFermer);
    btnL->addWidget(btnImprimer);
    layout->addLayout(btnL);

    connect(btnFermer, &QPushButton::clicked, dlg, &QDialog::reject);
    connect(btnImprimer, &QPushButton::clicked, this, [=]() {
        QString fichier = QFileDialog::getSaveFileName(
            dlg, "Enregistrer PDF", "clients_export.pdf", "PDF (*.pdf)");
        if (!fichier.isEmpty()) {
            QPrinter printer(QPrinter::HighResolution);
            printer.setOutputFormat(QPrinter::PdfFormat);
            printer.setOutputFileName(fichier);
            QTextDocument doc;
            doc.setHtml(html);
            doc.print(static_cast<QPagedPaintDevice*>(&printer));
            showMessage(dlg, "Succès", "PDF enregistré avec succès !", "success");
        }
    });

    dlg->exec();
}

// ================================================================
// === MODULE CLIENT — STAT=================================
// ================================================================
void MainWindow::on_bouttonstatclient_clicked()
{
    // ── Fetch stats from DB ──────────────────────────────
    QSqlQuery q;

    int totalClients = 0;
    if (q.exec("SELECT COUNT(*) FROM CLIENTS") && q.next())
        totalClients = q.value(0).toInt();

    int withTelephone = 0;
    if (q.exec("SELECT COUNT(*) FROM CLIENTS WHERE Telephone IS NOT NULL") && q.next())
        withTelephone = q.value(0).toInt();

    int withAdresse = 0;
    if (q.exec("SELECT COUNT(*) FROM CLIENTS WHERE Adresse_complete IS NOT NULL") && q.next())
        withAdresse = q.value(0).toInt();

    // Compter les clients par Type_client
    int typeParticulier = 0;
    q.prepare("SELECT COUNT(*) FROM CLIENTS WHERE UPPER(Type_client) = UPPER(:t)");
    q.bindValue(":t", "Particulier");
    if (q.exec() && q.next()) typeParticulier = q.value(0).toInt();

    int typeEntreprise = 0;
    q.prepare("SELECT COUNT(*) FROM CLIENTS WHERE UPPER(Type_client) = UPPER(:t)");
    q.bindValue(":t", "Entreprise");
    if (q.exec() && q.next()) typeEntreprise = q.value(0).toInt();

    int typeAutre = 0;
    q.prepare("SELECT COUNT(*) FROM CLIENTS WHERE UPPER(Type_client) = UPPER(:t)");
    q.bindValue(":t", "Autre");
    if (q.exec() && q.next()) typeAutre = q.value(0).toInt();

    // ── Build dialog ─────────────────────────────────────
    QDialog *dlg = new QDialog(this);
    dlg->setWindowTitle("📊 Statistiques des Clients");
    dlg->setFixedSize(780, 680);
    dlg->setStyleSheet("QDialog { background-color: #F0F4F8; }");

    QVBoxLayout *mainLay = new QVBoxLayout(dlg);
    mainLay->setContentsMargins(20, 20, 20, 20);
    mainLay->setSpacing(16);

    // Title
    QLabel *title = new QLabel("📊 Tableau de Bord — Statistiques Clients");
    title->setAlignment(Qt::AlignCenter);
    title->setStyleSheet(
        "font-size:18px; font-weight:bold; color:white; padding:16px;"
        "background:qlineargradient(x1:0,y1:0,x2:1,y2:0,stop:0 #1B3A57,stop:1 #2C5F7C);"
        "border-radius:12px;"
        );
    mainLay->addWidget(title);

    // ── Row 1: KPI cards ──────────────────────────────────
    QHBoxLayout *kpiRow = new QHBoxLayout();
    kpiRow->setSpacing(12);

    auto makeKPI = [](const QString &icon, const QString &value, const QString &label, const QString &color) {
        QFrame *card = new QFrame();
        card->setFixedHeight(90);
        card->setStyleSheet(QString(
                                "QFrame { background-color:%1; border-radius:12px; }"
                                ).arg(color));
        QVBoxLayout *cl = new QVBoxLayout(card);
        cl->setContentsMargins(14, 10, 14, 10);
        cl->setSpacing(2);
        QLabel *ico = new QLabel(icon + "  " + value);
        ico->setStyleSheet("font-size:22px; font-weight:bold; color:white; background:transparent;");
        QLabel *lbl = new QLabel(label);
        lbl->setStyleSheet("font-size:11px; color:rgba(255,255,255,0.85); background:transparent;");
        cl->addWidget(ico);
        cl->addWidget(lbl);
        return card;
    };

    kpiRow->addWidget(makeKPI("👥", QString::number(totalClients), "Total clients", "#2C5F7C"));
    kpiRow->addWidget(makeKPI("📞", QString::number(withTelephone), "Téléphone défini", "#27AE60"));
    kpiRow->addWidget(makeKPI("🏠", QString::number(withAdresse), "Adresse définie", "#E67E22"));
    mainLay->addLayout(kpiRow);

    // ── Row 2: Type de clients ─────────────────────────────
    QFrame *typeCard = new QFrame();
    typeCard->setStyleSheet("QFrame { background:white; border-radius:12px; }");
    QVBoxLayout *typeLay = new QVBoxLayout(typeCard);
    typeLay->setContentsMargins(20, 14, 20, 14);
    typeLay->setSpacing(10);

    QLabel *typeTitle = new QLabel("🏷️ Répartition par Type de Client");
    typeTitle->setStyleSheet("font-size:13px; font-weight:bold; color:#374151;");
    typeLay->addWidget(typeTitle);

    struct TypeStat { QString name; int count; QString color; };
    QList<TypeStat> types = {
                             {"Particulier", typeParticulier, "#3B82F6"},
                             {"Entreprise", typeEntreprise, "#10B981"},
                             {"Autre", typeAutre, "#F59E0B"},
                             };

    QHBoxLayout *typeRow = new QHBoxLayout();
    typeRow->setSpacing(16);
    for (auto &t : types)
    {
        QFrame *tCard = new QFrame();
        tCard->setStyleSheet(QString(
                                 "QFrame { background:%1; border-radius:10px; }"
                                 ).arg(t.color));
        tCard->setFixedHeight(64);
        QVBoxLayout *tcl = new QVBoxLayout(tCard);
        tcl->setContentsMargins(12, 8, 12, 8);
        QLabel *tv = new QLabel(QString::number(t.count));
        tv->setAlignment(Qt::AlignCenter);
        tv->setStyleSheet("font-size:20px; font-weight:bold; color:white; background:transparent;");
        QLabel *tl = new QLabel(t.name);
        tl->setAlignment(Qt::AlignCenter);
        tl->setStyleSheet("font-size:11px; color:rgba(255,255,255,0.85); background:transparent;");
        tcl->addWidget(tv);
        tcl->addWidget(tl);
        typeRow->addWidget(tCard);
    }
    typeLay->addLayout(typeRow);
    mainLay->addWidget(typeCard);

    // Close button
    QPushButton *closeBtn = new QPushButton("✕  Fermer");
    closeBtn->setFixedHeight(42);
    closeBtn->setStyleSheet(
        "QPushButton { background:#2C5F7C; color:white; font-size:14px; font-weight:600;"
        "border:none; border-radius:8px; }"
        "QPushButton:hover { background:#1B3A57; }"
        );
    connect(closeBtn, &QPushButton::clicked, dlg, &QDialog::accept);
    mainLay->addWidget(closeBtn);

    dlg->exec();
}


// ================================================================
// === MODULE EMPLOYE — AFFICHAGE =================================
// ================================================================
void MainWindow::afficherEmployes()
{
    QStringList headers = {
        "🆔 CIN", "👤 Nom", "👤 Prénom", "📧 Email", "💼 Poste",
        "📞 Téléphone", "📅 Date Embauche", "💰 Salaire", "🏢 Service"
    };

    ui->tableWidget_4->clear();
    ui->tableWidget_4->setColumnCount(headers.size());
    ui->tableWidget_4->setHorizontalHeaderLabels(headers);
    ui->tableWidget_4->setRowCount(0);
    ui->tableWidget_4->setSortingEnabled(false);

    // ═══════════════════════════════════════════
    //   STYLE FLAT DASHBOARD BLEU
    // ═══════════════════════════════════════════
    ui->tableWidget_4->setStyleSheet(R"(
        QTableWidget {
            background-color: #f0f4f8;
            alternate-background-color: #e8edf2;
            border: none;
            gridline-color: transparent;
            font-size: 13px;
            color: #2d3436;
        }
        QTableWidget::item {
            padding: 10px 16px;
            border: none;
            border-bottom: 1px solid #dfe6ed;
            color: #2d3436;
        }
        QTableWidget::item:selected {
            background-color: #2C5F7C;
            color: #ffffff;
        }
        QTableWidget::item:hover {
            background-color: #d6e4f0;
            color: #1B3A57;
        }
        QHeaderView::section {
            background: qlineargradient(
                x1:0, y1:0, x2:0, y2:1,
                stop:0 #2C5F7C,
                stop:1 #1B3A57
            );
            color: #ffffff;
            font-weight: bold;
            font-size: 13px;
            padding: 12px 16px;
            border: none;
            border-right: 1px solid #3A6EA5;
        }
        QScrollBar:vertical {
            background: #e8edf2;
            width: 7px;
            border-radius: 4px;
        }
        QScrollBar::handle:vertical {
            background: #2C5F7C;
            border-radius: 4px;
            min-height: 30px;
        }
        QScrollBar:horizontal {
            background: #e8edf2;
            height: 7px;
            border-radius: 4px;
        }
        QScrollBar::handle:horizontal {
            background: #2C5F7C;
            border-radius: 4px;
        }
        QScrollBar::add-line, QScrollBar::sub-line { background: none; }
    )");

    ui->tableWidget_4->setAlternatingRowColors(true);
    ui->tableWidget_4->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableWidget_4->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tableWidget_4->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableWidget_4->verticalHeader()->setVisible(false);
    ui->tableWidget_4->setShowGrid(false);

    // ═══════════════════════════════════════════
    //   REQUÊTE SQL
    // ═══════════════════════════════════════════
    Employe e;
    QSqlQueryModel *model = e.afficher();
    // Remplissage manuel depuis le model
    for (int row = 0; row < model->rowCount(); row++) {
        ui->tableWidget_4->insertRow(row);
        for (int col = 0; col < 9; col++) {
            ui->tableWidget_4->setItem(row, col,
                                       new QTableWidgetItem(model->data(model->index(row, col)).toString()));
        }
        ui->tableWidget_4->setRowHeight(row, 44);
    }

    // ═══════════════════════════════════════════
    //   COLONNES
    // ═══════════════════════════════════════════
    ui->tableWidget_4->horizontalHeader()
        ->setSectionResizeMode(QHeaderView::ResizeToContents);
    ui->tableWidget_4->horizontalHeader()->setStretchLastSection(true);
    ui->tableWidget_4->horizontalHeader()->setMinimumSectionSize(90);
    ui->tableWidget_4->setSortingEnabled(true);
}

// ================================================================
// === MODULE EMPLOYE — AJOUT =====================================
// ================================================================

void MainWindow::on_bouttonajouteremp_clicked()
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
    container->setStyleSheet("QFrame { background-color:#F2F2F2; border-radius:20px; }");
    QVBoxLayout *containerLayout = new QVBoxLayout(container);
    containerLayout->setContentsMargins(30, 30, 30, 30);

    QLabel *titre = new QLabel("👨‍💼 Informations Employé");
    titre->setAlignment(Qt::AlignCenter);
    titre->setStyleSheet(
        "QLabel { font-size:20px; font-weight:bold; color:white; padding:20px;"
        "border-radius:18px;"
        "background:qlineargradient(x1:0,y1:0,x2:0,y2:1,"
        "stop:0 #2C5F7C, stop:1 #1B3A57); }"
        );
    containerLayout->addWidget(titre);
    containerLayout->addSpacing(20);

    QScrollArea *scrollArea = new QScrollArea();
    scrollArea->setWidgetResizable(true);
    scrollArea->setFrameShape(QFrame::NoFrame);

    QWidget *scrollWidget = new QWidget();
    scrollWidget->setStyleSheet("background-color:white; border-radius:15px;");
    QVBoxLayout *scrollLayout = new QVBoxLayout(scrollWidget);
    scrollLayout->setSpacing(20);
    scrollLayout->setContentsMargins(20, 20, 20, 20);

    QString labelStyle =
        "QLabel { background-color:transparent; padding:5px;"
        "font-size:13px; font-weight:600; color:#374151; }";
    QString editStyle =
        "QLineEdit { background-color:#F9FAFB; border:1px solid #D1D5DB;"
        "border-radius:8px; padding:12px 16px; font-size:14px; color:#111827; }"
        "QLineEdit:hover { border:1px solid #2C5F7C; background-color:#FFFFFF; }"
        "QLineEdit:focus { border:2px solid #2C5F7C; background-color:#FFFFFF; padding:11px 15px; }";
    QString comboStyle =
        "QComboBox { background-color:#F9FAFB; border:1px solid #D1D5DB;"
        "border-radius:8px; padding:12px 16px; font-size:14px; color:#111827; }"
        "QComboBox:hover { border:1px solid #2C5F7C; background-color:#FFFFFF; }";
    QString dateStyle =
        "QDateEdit { background-color:#F9FAFB; border:1px solid #D1D5DB;"
        "border-radius:8px; padding:12px 16px; font-size:14px; color:#111827; }"
        "QDateEdit:hover { border:1px solid #2C5F7C; background-color:#FFFFFF; }";
    QString spinStyle =
        "QDoubleSpinBox { background-color:#F9FAFB; border:1px solid #D1D5DB;"
        "border-radius:8px; padding:12px 16px; font-size:14px; color:#111827; }"
        "QDoubleSpinBox:hover { border:1px solid #2C5F7C; background-color:#FFFFFF; }";

    auto addField = [&](QString text, QWidget *field, QString style) {
        QLabel *label = new QLabel(text);
        label->setStyleSheet(labelStyle);
        scrollLayout->addWidget(label);
        field->setStyleSheet(style);
        scrollLayout->addWidget(field);
    };

    QLineEdit *cin       = new QLineEdit();
    QLineEdit *nom       = new QLineEdit();
    QLineEdit *prenom    = new QLineEdit();
    QLineEdit *email     = new QLineEdit();
    QLineEdit *telephone = new QLineEdit();
    QLineEdit *service   = new QLineEdit();

    QComboBox *poste = new QComboBox();
    poste->addItems({"Technicien", "Administratif", "Manager", "Agent terrain"});
    poste->setStyleSheet(comboStyle);

    QDoubleSpinBox *salaire = new QDoubleSpinBox();
    salaire->setSuffix(" TND");
    salaire->setDecimals(2);
    salaire->setMinimum(0.0);
    salaire->setMaximum(99999.99);
    salaire->setValue(0.0);
    salaire->setStyleSheet(spinStyle);

    QDateEdit *dateEmbauche = new QDateEdit(QDate::currentDate());
    dateEmbauche->setDisplayFormat("dd/MM/yyyy");
    dateEmbauche->setCalendarPopup(true);
    dateEmbauche->setStyleSheet(dateStyle);

    addField("🆔 CIN * (8 chiffres)", cin, editStyle);
    addField("👤 Nom *", nom, editStyle);
    addField("👤 Prénom *", prenom, editStyle);

    QLabel *lblPoste = new QLabel("💼 Poste *");
    lblPoste->setStyleSheet(labelStyle);
    scrollLayout->addWidget(lblPoste);
    scrollLayout->addWidget(poste);

    addField("📧 Email *", email, editStyle);
    addField("📞 Téléphone * (8 chiffres)", telephone, editStyle);
    addField("🏢 Service", service, editStyle);

    QLabel *lblSalaire = new QLabel("💰 Salaire * (TND)");
    lblSalaire->setStyleSheet(labelStyle);
    scrollLayout->addWidget(lblSalaire);
    scrollLayout->addWidget(salaire);

    QLabel *lblDate = new QLabel("📅 Date d'Embauche *");
    lblDate->setStyleSheet(labelStyle);
    scrollLayout->addWidget(lblDate);
    scrollLayout->addWidget(dateEmbauche);

    scrollArea->setWidget(scrollWidget);
    containerLayout->addWidget(scrollArea);
    containerLayout->addSpacing(15);

    QLabel *note = new QLabel("* Tous les champs sont obligatoires");
    note->setStyleSheet("color:#6E7F91; font-style:italic; font-size:12px;");
    containerLayout->addWidget(note);

    QHBoxLayout *btnLayout = new QHBoxLayout();
    btnLayout->setSpacing(15);

    QPushButton *annuler = new QPushButton("✗ Annuler");
    annuler->setMinimumHeight(50);
    annuler->setStyleSheet(
        "QPushButton { background-color:#E5E7EB; color:#374151; font-size:15px;"
        "font-weight:600; border:none; border-radius:8px; padding:12px 30px; }"
        "QPushButton:hover { background-color:#D1D5DB; }"
        );

    QPushButton *ajouter = new QPushButton("✓ Ajouter l'employé");
    ajouter->setMinimumHeight(50);
    ajouter->setStyleSheet(
        "QPushButton { background:qlineargradient(x1:0,y1:0,x2:0,y2:1,"
        "stop:0 #2C5F7C, stop:1 #1B3A57); color:white; font-size:15px;"
        "font-weight:600; border:none; border-radius:8px; padding:12px 30px; }"
        "QPushButton:hover { background:qlineargradient(x1:0,y1:0,x2:0,y2:1,"
        "stop:0 #3A6EA5, stop:1 #2C5F7C); }"
        );

    btnLayout->addWidget(annuler);
    btnLayout->addWidget(ajouter);
    containerLayout->addLayout(btnLayout);
    mainLayout->addWidget(container);

    connect(annuler, &QPushButton::clicked, dialog, &QDialog::reject);

    connect(ajouter, &QPushButton::clicked, this, [=]() {
        QRegularExpression regCIN("^[0-9]{8}$");
        if (cin->text().isEmpty() || !regCIN.match(cin->text()).hasMatch()) {
            showMessage(dialog, "Erreur", "CIN invalide ! (8 chiffres obligatoires)", "error");
            return;
        }
        if (nom->text().isEmpty() || prenom->text().isEmpty() ||
            email->text().isEmpty() || telephone->text().isEmpty()) {
            showMessage(dialog, "Erreur", "Tous les champs sont obligatoires !", "error");
            return;
        }
        if (!email->text().contains("@") || !email->text().contains(".")) {
            showMessage(dialog, "Erreur", "Email invalide ! (exemple: nom@email.com)", "error");
            return;
        }
        QRegularExpression regTel("^[0-9]{8}$");
        if (!regTel.match(telephone->text()).hasMatch()) {
            showMessage(dialog, "Erreur", "Téléphone invalide ! (8 chiffres)", "error");
            return;
        }
        QRegularExpression regLettre("^[a-zA-ZÀ-ÿ ]+$");
        if (!regLettre.match(nom->text()).hasMatch()) {
            showMessage(dialog, "Erreur", "Nom invalide ! (lettres seulement)", "error");
            return;
        }
        if (!regLettre.match(prenom->text()).hasMatch()) {
            showMessage(dialog, "Erreur", "Prénom invalide ! (lettres seulement)", "error");
            return;
        }
        if (salaire->value() <= 0.0) {
            showMessage(dialog, "Erreur", "Salaire invalide ! (doit être supérieur à 0)", "error");
            return;
        }

        Employe emp(cin->text(), nom->text(), prenom->text(),
                    email->text(), poste->currentText(), telephone->text(),
                    salaire->value(), dateEmbauche->date().toString("dd/MM/yyyy"),
                    service->text());

        if (emp.ajouter()) {
            showMessage(dialog, "Succès", "✅ Employé ajouté avec succès !", "success");
            afficherEmployes();
            dialog->accept();
        } else {
            showMessage(dialog, "Erreur", "Impossible d'ajouter l'employé.", "error");
        }
    });

    ajouter->setDefault(true);
    dialog->exec();
}

// ================================================================
// === MODULE EMPLOYE — MODIFICATION ==============================
// ================================================================

void MainWindow::on_bouttonmodifieremp_clicked()
{
    afficherWidgetModifierEmploye();
}

void MainWindow::afficherWidgetModifierEmploye()
{
    int selectedRow = ui->tableWidget_4->currentRow();
    if (selectedRow < 0) {
        showMessage(this, "Attention",
                    "⚠️ Veuillez sélectionner un employé dans le tableau avant de modifier !",
                    "warning");
        return;
    }

    QString cin_actuel     = ui->tableWidget_4->item(selectedRow, 0)->text();
    QString nom_actuel     = ui->tableWidget_4->item(selectedRow, 1)->text();
    QString prenom_actuel  = ui->tableWidget_4->item(selectedRow, 2)->text();
    QString email_actuel   = ui->tableWidget_4->item(selectedRow, 3)->text();
    QString poste_actuel   = ui->tableWidget_4->item(selectedRow, 4)->text();
    QString tel_actuel     = ui->tableWidget_4->item(selectedRow, 5)->text();
    QString date_actuelle  = ui->tableWidget_4->item(selectedRow, 6)->text();
    QString salaire_actuel = ui->tableWidget_4->item(selectedRow, 7)->text();
    QString service_actuel = ui->tableWidget_4->item(selectedRow, 8)->text();

    QDialog *dialog = new QDialog(this);
    dialog->setWindowTitle("✏️ Modifier un Employé");
    dialog->setFixedSize(850, 700);
    dialog->setStyleSheet("QDialog { background-color: #EDEDED; }");

    QVBoxLayout *mainLayout = new QVBoxLayout(dialog);
    QFrame *container = new QFrame();
    container->setStyleSheet("QFrame { background-color:#F2F2F2; border-radius:20px; }");
    QVBoxLayout *containerLayout = new QVBoxLayout(container);
    containerLayout->setContentsMargins(30, 30, 30, 30);

    QLabel *titre = new QLabel("✏️ Modifier Employé — CIN : " + cin_actuel);
    titre->setAlignment(Qt::AlignCenter);
    titre->setStyleSheet(
        "QLabel { font-size:18px; font-weight:bold; color:white; padding:20px;"
        "border-radius:18px;"
        "background:qlineargradient(x1:0,y1:0,x2:0,y2:1,"
        "stop:0 #1A7A4A, stop:1 #0F4D2E); }"
        );
    containerLayout->addWidget(titre);
    containerLayout->addSpacing(20);

    QScrollArea *scrollArea = new QScrollArea();
    scrollArea->setWidgetResizable(true);
    scrollArea->setFrameShape(QFrame::NoFrame);

    QWidget *scrollWidget = new QWidget();
    scrollWidget->setStyleSheet("background-color:white; border-radius:15px;");
    QVBoxLayout *scrollLayout = new QVBoxLayout(scrollWidget);
    scrollLayout->setSpacing(20);
    scrollLayout->setContentsMargins(20, 20, 20, 20);

    QString labelStyle =
        "QLabel { background-color:transparent; padding:5px;"
        "font-size:13px; font-weight:600; color:#374151; }";
    QString editStyle =
        "QLineEdit { background-color:#F9FAFB; border:1px solid #D1D5DB;"
        "border-radius:8px; padding:12px 16px; font-size:14px; color:#111827; }"
        "QLineEdit:hover { border:1px solid #1A7A4A; background-color:#FFFFFF; }"
        "QLineEdit:focus { border:2px solid #1A7A4A; background-color:#FFFFFF; padding:11px 15px; }";
    QString comboStyle =
        "QComboBox { background-color:#F9FAFB; border:1px solid #D1D5DB;"
        "border-radius:8px; padding:12px 16px; font-size:14px; color:#111827; }"
        "QComboBox:hover { border:1px solid #1A7A4A; background-color:#FFFFFF; }";
    QString dateStyle =
        "QDateEdit { background-color:#F9FAFB; border:1px solid #D1D5DB;"
        "border-radius:8px; padding:12px 16px; font-size:14px; color:#111827; }"
        "QDateEdit:hover { border:1px solid #1A7A4A; background-color:#FFFFFF; }";
    QString spinStyle =
        "QDoubleSpinBox { background-color:#F9FAFB; border:1px solid #D1D5DB;"
        "border-radius:8px; padding:12px 16px; font-size:14px; color:#111827; }"
        "QDoubleSpinBox:hover { border:1px solid #1A7A4A; background-color:#FFFFFF; }";

    auto addField = [&](QString text, QWidget *field, QString style) {
        QLabel *label = new QLabel(text);
        label->setStyleSheet(labelStyle);
        scrollLayout->addWidget(label);
        field->setStyleSheet(style);
        scrollLayout->addWidget(field);
    };

    QLabel *lblCIN = new QLabel("🆔 CIN (non modifiable)");
    lblCIN->setStyleSheet(labelStyle);
    scrollLayout->addWidget(lblCIN);

    QLineEdit *cinDisplay = new QLineEdit(cin_actuel);
    cinDisplay->setReadOnly(true);
    cinDisplay->setStyleSheet(
        "QLineEdit { background-color:#E5E7EB; border:1px solid #D1D5DB;"
        "border-radius:8px; padding:12px 16px; font-size:14px; color:#6B7280; }"
        );
    scrollLayout->addWidget(cinDisplay);

    QLineEdit *nom       = new QLineEdit(nom_actuel);
    QLineEdit *prenom    = new QLineEdit(prenom_actuel);
    QLineEdit *email     = new QLineEdit(email_actuel);
    QLineEdit *telephone = new QLineEdit(tel_actuel);
    QLineEdit *service   = new QLineEdit(service_actuel);

    QComboBox *poste = new QComboBox();
    poste->addItems({"Technicien", "Administratif", "Manager", "Agent terrain"});
    poste->setCurrentText(poste_actuel);
    poste->setStyleSheet(comboStyle);

    QDoubleSpinBox *salaire = new QDoubleSpinBox();
    salaire->setSuffix(" TND");
    salaire->setDecimals(2);
    salaire->setMinimum(0.0);
    salaire->setMaximum(99999.99);
    salaire->setValue(salaire_actuel.toDouble());
    salaire->setStyleSheet(spinStyle);

    QDateEdit *dateEmbauche = new QDateEdit();
    dateEmbauche->setDisplayFormat("dd/MM/yyyy");
    dateEmbauche->setCalendarPopup(true);
    QDate d = QDate::fromString(date_actuelle, "dd/MM/yyyy");
    if (!d.isValid()) d = QDate::fromString(date_actuelle, "yyyy-MM-dd");
    if (!d.isValid()) d = QDate::currentDate();
    dateEmbauche->setDate(d);
    dateEmbauche->setStyleSheet(dateStyle);

    addField("👤 Nom *", nom, editStyle);
    addField("👤 Prénom *", prenom, editStyle);

    QLabel *lblPoste = new QLabel("💼 Poste *");
    lblPoste->setStyleSheet(labelStyle);
    scrollLayout->addWidget(lblPoste);
    scrollLayout->addWidget(poste);

    addField("📧 Email *", email, editStyle);
    addField("📞 Téléphone * (8 chiffres)", telephone, editStyle);
    addField("🏢 Service", service, editStyle);

    QLabel *lblSalaire = new QLabel("💰 Salaire (TND)");
    lblSalaire->setStyleSheet(labelStyle);
    scrollLayout->addWidget(lblSalaire);
    scrollLayout->addWidget(salaire);

    QLabel *lblDate = new QLabel("📅 Date d'Embauche");
    lblDate->setStyleSheet(labelStyle);
    scrollLayout->addWidget(lblDate);
    scrollLayout->addWidget(dateEmbauche);

    scrollArea->setWidget(scrollWidget);
    containerLayout->addWidget(scrollArea);
    containerLayout->addSpacing(15);

    QLabel *note = new QLabel("* Tous les champs sont obligatoires");
    note->setStyleSheet("color:#6E7F91; font-style:italic; font-size:12px;");
    containerLayout->addWidget(note);

    QHBoxLayout *btnLayout = new QHBoxLayout();
    btnLayout->setSpacing(15);

    QPushButton *annuler = new QPushButton("✗ Annuler");
    annuler->setMinimumHeight(50);
    annuler->setStyleSheet(
        "QPushButton { background-color:#E5E7EB; color:#374151; font-size:15px;"
        "font-weight:600; border:none; border-radius:8px; padding:12px 30px; }"
        "QPushButton:hover { background-color:#D1D5DB; }"
        );

    QPushButton *modifier = new QPushButton("✓ Enregistrer les modifications");
    modifier->setMinimumHeight(50);
    modifier->setStyleSheet(
        "QPushButton { background:qlineargradient(x1:0,y1:0,x2:0,y2:1,"
        "stop:0 #1A7A4A, stop:1 #0F4D2E); color:white; font-size:15px;"
        "font-weight:600; border:none; border-radius:8px; padding:12px 30px; }"
        "QPushButton:hover { background:qlineargradient(x1:0,y1:0,x2:0,y2:1,"
        "stop:0 #22A05A, stop:1 #1A7A4A); }"
        );

    btnLayout->addWidget(annuler);
    btnLayout->addWidget(modifier);
    containerLayout->addLayout(btnLayout);
    mainLayout->addWidget(container);

    connect(annuler, &QPushButton::clicked, dialog, &QDialog::reject);

    connect(modifier, &QPushButton::clicked, this, [=]() {
        if (nom->text().isEmpty() || prenom->text().isEmpty() ||
            email->text().isEmpty() || telephone->text().isEmpty()) {
            showMessage(dialog, "Erreur", "Tous les champs sont obligatoires !", "error");
            return;
        }
        if (!email->text().contains("@") || !email->text().contains(".")) {
            showMessage(dialog, "Erreur", "Email invalide !", "error");
            return;
        }
        QRegularExpression regTel("^[0-9]{8}$");
        if (!regTel.match(telephone->text()).hasMatch()) {
            showMessage(dialog, "Erreur", "Téléphone invalide ! (8 chiffres)", "error");
            return;
        }
        QRegularExpression regLettre("^[a-zA-ZÀ-ÿ ]+$");
        if (!regLettre.match(nom->text()).hasMatch()) {
            showMessage(dialog, "Erreur", "Nom invalide ! (lettres seulement)", "error");
            return;
        }
        if (!regLettre.match(prenom->text()).hasMatch()) {
            showMessage(dialog, "Erreur", "Prénom invalide ! (lettres seulement)", "error");
            return;
        }
        if (salaire->value() <= 0.0) {
            showMessage(dialog, "Erreur", "Salaire invalide ! (doit être supérieur à 0)", "error");
            return;
        }

        Employe emp;
        emp.setNom(nom->text());
        emp.setPrenom(prenom->text());
        emp.setEmail(email->text());
        emp.setPoste(poste->currentText());
        emp.setTelephone(telephone->text());
        emp.setSalaire(salaire->value());
        emp.setDateEmbauche(dateEmbauche->date().toString("dd/MM/yyyy"));
        emp.setService(service->text());

        if (emp.modifier(cin_actuel)) {
            showMessage(dialog, "Succès", "✅ Employé modifié avec succès !", "success");
            afficherEmployes();
            dialog->accept();
        } else {
            showMessage(dialog, "Erreur", "Impossible de modifier l'employé.", "error");
        }
    });

    modifier->setDefault(true);
    dialog->exec();
}

// ================================================================
// === MODULE EMPLOYE — SUPPRESSION ===============================
// ================================================================

void MainWindow::on_bouttonsupprimeremp_clicked()
{
    int selectedRow = ui->tableWidget_4->currentRow();
    if (selectedRow < 0) {
        showMessage(this, "Attention",
                    "⚠️ Veuillez sélectionner un employé dans le tableau avant de supprimer !",
                    "warning");
        return;
    }

    QString cin_choisi = ui->tableWidget_4->item(selectedRow, 0)->text();
    QString nom_choisi = ui->tableWidget_4->item(selectedRow, 1)->text()
                         + " " + ui->tableWidget_4->item(selectedRow, 2)->text();

    QSqlQuery checkFK;
    checkFK.prepare("SELECT COUNT(*) FROM CLIENTS WHERE CIN_employe = :cin");
    checkFK.bindValue(":cin", cin_choisi);
    if (checkFK.exec() && checkFK.next()) {
        if (checkFK.value(0).toInt() > 0) {
            showMessage(this, "Suppression impossible",
                        "❌ Cet employé est lié à " +
                            QString::number(checkFK.value(0).toInt()) +
                            " client(s).\nVeuillez d'abord modifier ou supprimer ces clients.",
                        "error");
            return;
        }
    }

    QDialog *confirm = new QDialog(this);
    confirm->setFixedSize(440, 220);
    confirm->setStyleSheet("QDialog { background-color:#1E1E2E; border-radius:14px; }");

    QVBoxLayout *lay = new QVBoxLayout(confirm);
    lay->setContentsMargins(0, 0, 0, 24);
    lay->setSpacing(0);

    QWidget *header = new QWidget();
    header->setFixedHeight(62);
    header->setStyleSheet(
        "QWidget { background-color:#E67E22;"
        "border-top-left-radius:14px; border-top-right-radius:14px; }"
        );
    QHBoxLayout *hLay = new QHBoxLayout(header);
    hLay->setContentsMargins(22, 0, 22, 0);
    QLabel *lblTitre = new QLabel("⚠️  Confirmer la suppression");
    lblTitre->setStyleSheet(
        "font-size:15px; font-weight:bold; color:white; background:transparent;"
        );
    hLay->addWidget(lblTitre);
    lay->addWidget(header);

    QLabel *lblMsg = new QLabel(
        "Voulez-vous vraiment supprimer :\n👤 " + nom_choisi + "\n🆔 CIN : " + cin_choisi
        );
    lblMsg->setAlignment(Qt::AlignCenter);
    lblMsg->setWordWrap(true);
    lblMsg->setStyleSheet(
        "font-size:13px; color:#C8C8D8; background:transparent;"
        "padding:16px 28px 8px 28px;"
        );
    lay->addWidget(lblMsg);
    lay->addStretch();

    QHBoxLayout *btnLay = new QHBoxLayout();
    btnLay->setSpacing(12);
    btnLay->setContentsMargins(20, 0, 20, 0);

    QPushButton *btnNon = new QPushButton("✗ Annuler");
    btnNon->setFixedHeight(40);
    btnNon->setStyleSheet(
        "QPushButton { background:#374151; color:white; font-size:13px;"
        "font-weight:600; border:none; border-radius:8px; }"
        "QPushButton:hover { background:#4B5563; }"
        );

    QPushButton *btnOui = new QPushButton("🗑️ Oui, supprimer");
    btnOui->setFixedHeight(40);
    btnOui->setStyleSheet(
        "QPushButton { background:#C0392B; color:white; font-size:13px;"
        "font-weight:600; border:none; border-radius:8px; }"
        "QPushButton:hover { background:#E74C3C; }"
        );

    btnLay->addWidget(btnNon);
    btnLay->addWidget(btnOui);
    lay->addLayout(btnLay);

    connect(btnNon, &QPushButton::clicked, confirm, &QDialog::reject);
    connect(btnOui, &QPushButton::clicked, confirm, &QDialog::accept);

    if (confirm->exec() == QDialog::Accepted) {
        Employe emp;
        if (emp.supprimer(cin_choisi)) {
            showMessage(this, "Succès", "✅ Employé supprimé avec succès !", "success");
            afficherEmployes();
        } else {
            showMessage(this, "Erreur", "Impossible de supprimer cet employé.", "error");
        }
    }
}

// ================================================================
// === MODULE EMPLOYE — RECHERCHE =================================
// ================================================================

void MainWindow::on_bouttonrechercheemp_clicked()
{
    QString recherche = ui->barrerechercheemp->text().trimmed();

    if (recherche.isEmpty()) {
        afficherEmployes();
        return;
    }

    QSqlQuery query;
    query.prepare(
        "SELECT CIN, Nom, Prenom, Email, Poste, Telephone, Date_embauche, Salaire, Service "
        "FROM EMPLOYES "
        "WHERE UPPER(CIN)     LIKE UPPER(:r1) "
        "   OR UPPER(Nom)     LIKE UPPER(:r2) "
        "   OR UPPER(Prenom)  LIKE UPPER(:r3) "
        "   OR UPPER(Email)   LIKE UPPER(:r4) "
        "   OR UPPER(Poste)   LIKE UPPER(:r5) "
        "   OR UPPER(Service) LIKE UPPER(:r6)"
        );
    QString motif = "%" + recherche + "%";
    query.bindValue(":r1", motif);
    query.bindValue(":r2", motif);
    query.bindValue(":r3", motif);
    query.bindValue(":r4", motif);
    query.bindValue(":r5", motif);
    query.bindValue(":r6", motif);

    if (!query.exec()) {
        showMessage(this, "Erreur SQL", query.lastError().text(), "error");
        return;
    }

    ui->tableWidget_4->setRowCount(0);
    ui->tableWidget_4->setColumnCount(9);
    ui->tableWidget_4->setHorizontalHeaderLabels({
        "CIN", "Nom", "Prenom", "Email", "Poste",
        "Telephone", "Date Embauche", "Salaire", "Service"
    });

    int row = 0;
    while (query.next()) {
        ui->tableWidget_4->insertRow(row);
        for (int col = 0; col < 9; col++)
            ui->tableWidget_4->setItem(row, col,
                                       new QTableWidgetItem(query.value(col).toString()));
        row++;
    }

    if (row == 0)
        showMessage(this, "Recherche",
                    "Aucun employé trouvé pour : " + recherche, "warning");
}

// ================================================================
// === MODULE EMPLOYE — TRI =======================================
// ================================================================

void MainWindow::on_trieemp_currentIndexChanged(int index)
{
    QStringList colonnes = {
        "", "CIN", "Nom", "Prenom", "Email",
        "Poste", "Telephone", "Date_embauche", "Salaire", "Service"
    };

    if (index <= 0 || index >= colonnes.size()) {
        afficherEmployes();
        return;
    }

    QSqlQuery query;
    if (!query.exec(
            "SELECT CIN, Nom, Prenom, Email, Poste, Telephone, "
            "Date_embauche, Salaire, Service FROM EMPLOYES ORDER BY "
            + colonnes[index]))
    {
        showMessage(this, "Erreur SQL", query.lastError().text(), "error");
        return;
    }

    ui->tableWidget_4->setRowCount(0);
    ui->tableWidget_4->setColumnCount(9);
    ui->tableWidget_4->setHorizontalHeaderLabels({
        "CIN", "Nom", "Prenom", "Email", "Poste",
        "Telephone", "Date Embauche", "Salaire", "Service"
    });

    int row = 0;
    while (query.next()) {
        ui->tableWidget_4->insertRow(row);
        for (int col = 0; col < 9; col++)
            ui->tableWidget_4->setItem(row, col,
                                       new QTableWidgetItem(query.value(col).toString()));
        row++;
    }
}

// ================================================================
// === MODULE EMPLOYE — EXPORT PDF ================================
// ================================================================

void MainWindow::on_bouttonexporteremp_clicked()
{
    exporterEmployesCSV();
}

void MainWindow::exporterEmployesCSV()
{
    QSqlQuery query;
    if (!query.exec(
            "SELECT CIN, Nom, Prenom, Email, Poste, Telephone, "
            "Date_embauche, Salaire, Service FROM EMPLOYES ORDER BY Nom"))
    {
        showMessage(this, "Erreur SQL", query.lastError().text(), "error");
        return;
    }

    QString html;
    html += "<html><head><meta charset='utf-8'><style>"
            "body{font-family:Arial,sans-serif;font-size:12px;}"
            "h1{text-align:center;color:#2C5F7C;}"
            "table{width:100%;border-collapse:collapse;margin-top:20px;}"
            "th{background-color:#2C5F7C;color:white;padding:8px;text-align:left;}"
            "td{border:1px solid #ddd;padding:6px;}"
            "tr:nth-child(even){background-color:#f2f2f2;}"
            "</style></head><body>";
    html += "<h1>Liste des Employés</h1>";
    html += "<p style='text-align:center;'>Exporté le : "
            + QDate::currentDate().toString("dd/MM/yyyy") + "</p>";
    html += "<table><tr>"
            "<th>CIN</th><th>Nom</th><th>Prénom</th><th>Email</th>"
            "<th>Poste</th><th>Téléphone</th><th>Date Embauche</th>"
            "<th>Salaire</th><th>Service</th></tr>";

    while (query.next()) {
        html += "<tr>";
        for (int col = 0; col < 9; col++)
            html += "<td>" + query.value(col).toString() + "</td>";
        html += "</tr>";
    }
    html += "</table></body></html>";

    QDialog *dlg = new QDialog(this);
    dlg->setWindowTitle("Export Employés");
    dlg->setFixedSize(900, 600);
    QVBoxLayout *layout = new QVBoxLayout(dlg);

    QTextEdit *preview = new QTextEdit();
    preview->setReadOnly(true);
    preview->setHtml(html);
    layout->addWidget(preview);

    QHBoxLayout *btnL = new QHBoxLayout();

    QPushButton *btnImprimer = new QPushButton("🖨️ Imprimer / Enregistrer PDF");
    btnImprimer->setMinimumHeight(45);
    btnImprimer->setStyleSheet(
        "QPushButton{background:#2C5F7C;color:white;font-size:14px;"
        "font-weight:600;border:none;border-radius:8px;padding:10px 25px;}"
        "QPushButton:hover{background:#3A6EA5;}");

    QPushButton *btnFermer = new QPushButton("Fermer");
    btnFermer->setMinimumHeight(45);
    btnFermer->setStyleSheet(
        "QPushButton{background:#E5E7EB;color:#374151;font-size:14px;"
        "font-weight:600;border:none;border-radius:8px;padding:10px 25px;}"
        "QPushButton:hover{background:#D1D5DB;}");

    btnL->addWidget(btnFermer);
    btnL->addWidget(btnImprimer);
    layout->addLayout(btnL);

    connect(btnFermer,   &QPushButton::clicked, dlg, &QDialog::reject);
    connect(btnImprimer, &QPushButton::clicked, this, [=]() {
        QString fichier = QFileDialog::getSaveFileName(
            dlg, "Enregistrer PDF", "employes_export.pdf", "PDF (*.pdf)");
        if (!fichier.isEmpty()) {
            QPrinter printer(QPrinter::HighResolution);
            printer.setOutputFormat(QPrinter::PdfFormat);
            printer.setOutputFileName(fichier);
            QTextDocument doc;
            doc.setHtml(html);
            doc.print(static_cast<QPagedPaintDevice*>(&printer));
            showMessage(dlg, "Succès", "PDF enregistré avec succès !", "success");
        }
    });

    dlg->exec();
}

// ================================================================
// === MODULE EMPLOYE — STATISTIQUES ==============================
// ================================================================
// ============================================================
//  MainWindow::afficherStatistiquesEmployes()
//  Compatible Qt5/Qt6 + Oracle (OCI) / SQLite / ODBC
//  Table : EMPLOYES(CIN, Nom, Prenom, Email, Poste,
//                   Telephone, Date_embauche, Salaire, Service)
// ============================================================



void MainWindow::on_bouttonstatemp_clicked()
{
    // ── Fetch stats from DB ──────────────────────────────
    QSqlQuery q;

    int totalEmployes = 0;
    if (q.exec("SELECT COUNT(*) FROM EMPLOYES") && q.next())
        totalEmployes = q.value(0).toInt();

    int withEmail = 0;
    if (q.exec("SELECT COUNT(*) FROM EMPLOYES WHERE Email IS NOT NULL") && q.next())
        withEmail = q.value(0).toInt();

    int postesDefinis = 0;
    if (q.exec("SELECT COUNT(*) FROM EMPLOYES WHERE Poste IS NOT NULL") && q.next())
        postesDefinis = q.value(0).toInt();

    int serviceIT = 0;
    q.prepare("SELECT COUNT(*) FROM EMPLOYES WHERE UPPER(Service) = UPPER(:s)");
    q.bindValue(":s", "IT");
    if (q.exec() && q.next()) serviceIT = q.value(0).toInt();

    int serviceRH = 0;
    q.prepare("SELECT COUNT(*) FROM EMPLOYES WHERE UPPER(Service) = UPPER(:s)");
    q.bindValue(":s", "RH");
    if (q.exec() && q.next()) serviceRH = q.value(0).toInt();

    int serviceFinance = 0;
    q.prepare("SELECT COUNT(*) FROM EMPLOYES WHERE UPPER(Service) = UPPER(:s)");
    q.bindValue(":s", "Finance");
    if (q.exec() && q.next()) serviceFinance = q.value(0).toInt();

    double salaireMoyen = 0;
    if (q.exec("SELECT AVG(Salaire) FROM EMPLOYES") && q.next())
        salaireMoyen = q.value(0).toDouble();

    double salaireMax = 0;
    if (q.exec("SELECT MAX(Salaire) FROM EMPLOYES") && q.next())
        salaireMax = q.value(0).toDouble();

    double salaireMin = 0;
    if (q.exec("SELECT MIN(Salaire) FROM EMPLOYES") && q.next())
        salaireMin = q.value(0).toDouble();

    // ── Build dialog ─────────────────────────────────────
    QDialog *dlg = new QDialog(this);
    dlg->setWindowTitle("📊 Statistiques des Employés");
    dlg->setFixedSize(780, 680);
    dlg->setStyleSheet("QDialog { background-color: #F0F4F8; }");

    QVBoxLayout *mainLay = new QVBoxLayout(dlg);
    mainLay->setContentsMargins(20, 20, 20, 20);
    mainLay->setSpacing(16);

    // Title
    QLabel *title = new QLabel("📊 Tableau de Bord — Statistiques Employés");
    title->setAlignment(Qt::AlignCenter);
    title->setStyleSheet(
        "font-size:18px; font-weight:bold; color:white; padding:16px;"
        "background:qlineargradient(x1:0,y1:0,x2:1,y2:0,stop:0 #1B3A57,stop:1 #2C5F7C);"
        "border-radius:12px;"
        );
    mainLay->addWidget(title);

    // ── Row 1: KPI cards ──────────────────────────────────
    QHBoxLayout *kpiRow = new QHBoxLayout();
    kpiRow->setSpacing(12);

    auto makeKPI = [](const QString &icon, const QString &value, const QString &label, const QString &color) {
        QFrame *card = new QFrame();
        card->setFixedHeight(90);
        card->setStyleSheet(QString(
                                "QFrame { background-color:%1; border-radius:12px; }"
                                ).arg(color));
        QVBoxLayout *cl = new QVBoxLayout(card);
        cl->setContentsMargins(14, 10, 14, 10);
        cl->setSpacing(2);
        QLabel *ico = new QLabel(icon + "  " + value);
        ico->setStyleSheet("font-size:22px; font-weight:bold; color:white; background:transparent;");
        QLabel *lbl = new QLabel(label);
        lbl->setStyleSheet("font-size:11px; color:rgba(255,255,255,0.85); background:transparent;");
        cl->addWidget(ico);
        cl->addWidget(lbl);
        return card;
    };

    kpiRow->addWidget(makeKPI("👥", QString::number(totalEmployes), "Total employés", "#2C5F7C"));
    kpiRow->addWidget(makeKPI("📧", QString::number(withEmail), "Email défini", "#27AE60"));
    kpiRow->addWidget(makeKPI("💼", QString::number(postesDefinis), "Postes définis", "#E67E22"));
    mainLay->addLayout(kpiRow);

    // ── Row 2: Salaire stats ─────────────────────────────
    QFrame *salaireCard = new QFrame();
    salaireCard->setStyleSheet("QFrame { background:white; border-radius:12px; }");
    QHBoxLayout *salLay = new QHBoxLayout(salaireCard);
    salLay->setContentsMargins(20, 14, 20, 14);

    auto makeSalStat = [](const QString &lbl, const QString &val) {
        QVBoxLayout *vl = new QVBoxLayout();
        QLabel *v = new QLabel(val);
        v->setAlignment(Qt::AlignCenter);
        v->setStyleSheet("font-size:20px; font-weight:bold; color:#2C5F7C;");
        QLabel *l = new QLabel(lbl);
        l->setAlignment(Qt::AlignCenter);
        l->setStyleSheet("font-size:11px; color:#6B7280;");
        vl->addWidget(v);
        vl->addWidget(l);
        return vl;
    };

    QLabel *salTitle = new QLabel("💰 Salaire (DT)");
    salTitle->setStyleSheet("font-size:13px; font-weight:bold; color:#374151;");
    salLay->addWidget(salTitle);
    salLay->addStretch();
    salLay->addLayout(makeSalStat("Moyenne", QString::number(salaireMoyen, 'f', 2)));
    salLay->addSpacing(30);
    salLay->addLayout(makeSalStat("Maximum", QString::number(salaireMax, 'f', 2)));
    salLay->addSpacing(30);
    salLay->addLayout(makeSalStat("Minimum", QString::number(salaireMin, 'f', 2)));
    mainLay->addWidget(salaireCard);

    // ── Row 3: Services ─────────────────────────────────
    QFrame *serviceCard = new QFrame();
    serviceCard->setStyleSheet("QFrame { background:white; border-radius:12px; }");
    QVBoxLayout *serviceLay = new QVBoxLayout(serviceCard);
    serviceLay->setContentsMargins(20, 14, 20, 14);
    serviceLay->setSpacing(10);

    QLabel *serviceTitle = new QLabel("🏢 Répartition par Service");
    serviceTitle->setStyleSheet("font-size:13px; font-weight:bold; color:#374151;");
    serviceLay->addWidget(serviceTitle);

    struct ServiceStat { QString name; int count; QString color; };
    QList<ServiceStat> services = {
                                   {"IT",      serviceIT,      "#3B82F6"},
                                   {"RH",      serviceRH,      "#10B981"},
                                   {"Finance", serviceFinance, "#F59E0B"},
                                   };

    QHBoxLayout *serviceRow = new QHBoxLayout();
    serviceRow->setSpacing(16);
    for (auto &s : services)
    {
        QFrame *sCard = new QFrame();
        sCard->setStyleSheet(QString(
                                 "QFrame { background:%1; border-radius:10px; }"
                                 ).arg(s.color));
        sCard->setFixedHeight(64);
        QVBoxLayout *scl = new QVBoxLayout(sCard);
        scl->setContentsMargins(12, 8, 12, 8);
        QLabel *sv = new QLabel(QString::number(s.count));
        sv->setAlignment(Qt::AlignCenter);
        sv->setStyleSheet("font-size:20px; font-weight:bold; color:white; background:transparent;");
        QLabel *sl = new QLabel(s.name);
        sl->setAlignment(Qt::AlignCenter);
        sl->setStyleSheet("font-size:11px; color:rgba(255,255,255,0.85); background:transparent;");
        scl->addWidget(sv);
        scl->addWidget(sl);
        serviceRow->addWidget(sCard);
    }
    serviceLay->addLayout(serviceRow);
    mainLay->addWidget(serviceCard);

    // Close button
    QPushButton *closeBtn = new QPushButton("✕  Fermer");
    closeBtn->setFixedHeight(42);
    closeBtn->setStyleSheet(
        "QPushButton { background:#2C5F7C; color:white; font-size:14px; font-weight:600;"
        "border:none; border-radius:8px; }"
        "QPushButton:hover { background:#1B3A57; }"
        );
    connect(closeBtn, &QPushButton::clicked, dlg, &QDialog::accept);
    mainLay->addWidget(closeBtn);

    dlg->exec();
}


/// ================================================================
// REMPLACE ces 3 fonctions dans ton mainwindow.cpp
// Le reste du fichier ne change PAS
// ================================================================


// ================================================================
// === MODULE RECYCLAGE — AJOUT (CORRIGÉ) =========================
// ================================================================
// CORRECTION : ID saisi manuellement → remplacé par MAX(ID)+1
// ================================================================

void MainWindow::on_bouttonajouterrecyclage_clicked()
{
    afficherWidgetAjoutRecyclage();
}

void MainWindow::afficherWidgetAjoutRecyclage()
{
    QDialog *dialog = new QDialog(this);
    dialog->setWindowTitle("+ Ajouter une Opération de Recyclage");
    dialog->setFixedSize(850, 600);
    dialog->setStyleSheet("QDialog { background-color: #EDEDED; }");

    QVBoxLayout *mainLayout = new QVBoxLayout(dialog);
    QFrame *container = new QFrame();
    container->setStyleSheet("QFrame { background-color:#F2F2F2; border-radius:20px; }");
    QVBoxLayout *containerLayout = new QVBoxLayout(container);
    containerLayout->setContentsMargins(30, 30, 30, 30);

    QLabel *titre = new QLabel("♻️ Opération de Recyclage");
    titre->setAlignment(Qt::AlignCenter);
    titre->setStyleSheet(
        "QLabel { font-size:20px; font-weight:bold; color:white; padding:20px;"
        "border-radius:18px;"
        "background:qlineargradient(x1:0,y1:0,x2:0,y2:1,"
        "stop:0 #2C5F7C, stop:1 #1B3A57); }"
        );
    containerLayout->addWidget(titre);
    containerLayout->addSpacing(20);

    QWidget *contentWidget = new QWidget();
    contentWidget->setStyleSheet("background-color:white; border-radius:15px;");
    QGridLayout *gridLayout = new QGridLayout(contentWidget);
    gridLayout->setSpacing(15);
    gridLayout->setContentsMargins(25, 25, 25, 25);

    QString labelStyle =
        "QLabel { background-color:transparent; padding:5px;"
        "font-size:13px; font-weight:600; color:#374151; }";
    QString editStyle =
        "QLineEdit, QComboBox, QDoubleSpinBox {"
        "background-color:#F9FAFB; border:1px solid #D1D5DB;"
        "border-radius:8px; padding:12px 16px; font-size:14px; color:#111827; }"
        "QLineEdit:hover, QComboBox:hover, QDoubleSpinBox:hover {"
        "border:1px solid #2C5F7C; background-color:#FFFFFF; }";

    // Champs
    QComboBox *materiau = new QComboBox();
    materiau->addItems({"Plastique", "Verre", "Métal", "Papier", "Organique", "Electronique", "Autre"});
    materiau->setStyleSheet(editStyle);

    QDoubleSpinBox *qteEntree = new QDoubleSpinBox();
    qteEntree->setSuffix(" kg"); qteEntree->setDecimals(2);
    qteEntree->setMinimum(0.0); qteEntree->setMaximum(999999.99);
    qteEntree->setStyleSheet(editStyle);

    QDoubleSpinBox *qteRecyclee = new QDoubleSpinBox();
    qteRecyclee->setSuffix(" kg"); qteRecyclee->setDecimals(2);
    qteRecyclee->setMinimum(0.0); qteRecyclee->setMaximum(999999.99);
    qteRecyclee->setStyleSheet(editStyle);

    QDoubleSpinBox *qteRejetee = new QDoubleSpinBox();
    qteRejetee->setSuffix(" kg"); qteRejetee->setDecimals(2);
    qteRejetee->setMinimum(0.0); qteRejetee->setMaximum(999999.99);
    qteRejetee->setStyleSheet(editStyle);

    QLineEdit *destination = new QLineEdit(); destination->setStyleSheet(editStyle);

    QDoubleSpinBox *valeur = new QDoubleSpinBox();
    valeur->setSuffix(" TND"); valeur->setDecimals(2);
    valeur->setMinimum(0.0); valeur->setMaximum(999999.99);
    valeur->setStyleSheet(editStyle);

    QLineEdit *direction = new QLineEdit(); direction->setStyleSheet(editStyle);
    direction->setText("Interne");

    QComboBox *statut = new QComboBox();
    statut->addItems({"En attente", "En cours", "Terminé", "Annulé"});
    statut->setStyleSheet(editStyle);

    // Labels
    QLabel *lblMat  = new QLabel("📦 Matériau :");               lblMat->setStyleSheet(labelStyle);
    QLabel *lblQteE = new QLabel("📊 Quantité entrée (kg) :");   lblQteE->setStyleSheet(labelStyle);
    QLabel *lblQteR = new QLabel("✅ Quantité recyclée (kg) :"); lblQteR->setStyleSheet(labelStyle);
    QLabel *lblQteJ = new QLabel("❌ Quantité rejetée (kg) :");  lblQteJ->setStyleSheet(labelStyle);
    QLabel *lblDest = new QLabel("📍 Destination :");            lblDest->setStyleSheet(labelStyle);
    QLabel *lblVal  = new QLabel("💰 Valeur (TND) :");           lblVal->setStyleSheet(labelStyle);
    QLabel *lblDir  = new QLabel("🏭 Direction :");              lblDir->setStyleSheet(labelStyle);
    QLabel *lblStat = new QLabel("📊 Statut :");                 lblStat->setStyleSheet(labelStyle);

    gridLayout->addWidget(lblMat,  0, 0); gridLayout->addWidget(materiau,    0, 1);
    gridLayout->addWidget(lblQteE, 1, 0); gridLayout->addWidget(qteEntree,   1, 1);
    gridLayout->addWidget(lblQteR, 2, 0); gridLayout->addWidget(qteRecyclee, 2, 1);
    gridLayout->addWidget(lblQteJ, 3, 0); gridLayout->addWidget(qteRejetee,  3, 1);
    gridLayout->addWidget(lblDest, 0, 2); gridLayout->addWidget(destination, 0, 3);
    gridLayout->addWidget(lblVal,  1, 2); gridLayout->addWidget(valeur,      1, 3);
    gridLayout->addWidget(lblDir,  2, 2); gridLayout->addWidget(direction,   2, 3);
    gridLayout->addWidget(lblStat, 3, 2); gridLayout->addWidget(statut,      3, 3);

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
        "QPushButton { background-color:#E5E7EB; color:#374151; font-size:15px;"
        "font-weight:600; border:none; border-radius:8px; padding:12px 30px; }"
        "QPushButton:hover { background-color:#D1D5DB; }"
        );

    QPushButton *ajouter = new QPushButton("✓ Ajouter");
    ajouter->setMinimumHeight(50);
    ajouter->setStyleSheet(
        "QPushButton { background:qlineargradient(x1:0,y1:0,x2:0,y2:1,"
        "stop:0 #2C5F7C, stop:1 #1B3A57); color:white; font-size:15px;"
        "font-weight:600; border:none; border-radius:8px; padding:12px 30px; }"
        "QPushButton:hover { background:qlineargradient(x1:0,y1:0,x2:0,y2:1,"
        "stop:0 #3A6EA5, stop:1 #2C5F7C); }"
        );

    btnLayout->addWidget(annuler);
    btnLayout->addWidget(ajouter);
    containerLayout->addLayout(btnLayout);
    mainLayout->addWidget(container);

    connect(annuler, &QPushButton::clicked, dialog, &QDialog::reject);

    connect(ajouter, &QPushButton::clicked, this, [=]() {
        // Validation
        if (destination->text().trimmed().isEmpty() || direction->text().trimmed().isEmpty()) {
            QMessageBox::warning(dialog, tr("Champs manquants"),
                                 tr("Merci de remplir tous les champs obligatoires."));
            return;
        }
        if (qteEntree->value() <= 0.0) {
            showMessage(dialog, "Erreur", "La quantité entrée doit être supérieure à 0 !", "error");
            return;
        }
        if (qteRecyclee->value() > qteEntree->value()) {
            showMessage(dialog, "Erreur", "La quantité recyclée ne peut pas dépasser la quantité entrée !", "error");
            return;
        }

        // ✅ Calcul automatique du prochain ID
        QSqlQuery queryId;
        queryId.exec("SELECT NVL(MAX(ID_recyclage), 0) + 1 FROM RECYCLAGES");
        int nextId = 1;
        if (queryId.next())
            nextId = queryId.value(0).toInt();

        Recyclage r(0,
                    QDate::currentDate().toString("dd/MM/yyyy"),
                    materiau->currentText(),
                    qteEntree->value(),
                    qteRecyclee->value(),
                    qteRejetee->value(),
                    destination->text().trimmed(),
                    valeur->value(),
                    direction->text().trimmed(),
                    statut->currentText());

        if (r.ajouter()) {
            showMessage(dialog, "Succès", "✅ Recyclage ajouté avec succès !", "success");
            afficherRecyclages();
            dialog->accept();
        } else {
            showMessage(dialog, "Erreur", "Impossible d'ajouter ce recyclage.", "error");
        }
    });

    dialog->exec();
}


// ================================================================
// === MODULE COLLECTE — AJOUT (CORRIGÉ) ==========================
// ================================================================
// CORRECTIONS :
//   - Nom table : COLLECTE → COLLECTES
//   - Colonnes alignées avec le vrai schéma Oracle
//   - ID calculé automatiquement avec MAX+1
//   - Champ "zone" mappé vers OBSERVATIONS (seul champ texte libre)
// ================================================================

void MainWindow::on_pushButton_66_clicked()
{
    afficherWidgetAjoutCollecte();
}

void MainWindow::afficherWidgetAjoutCollecte()
{
    QDialog *dialog = new QDialog(this);
    dialog->setWindowTitle("+ Ajouter une Collecte");
    dialog->setFixedSize(850, 650);
    dialog->setStyleSheet("QDialog { background-color: #EDEDED; }");

    QVBoxLayout *mainLayout = new QVBoxLayout(dialog);
    QFrame *container = new QFrame();
    container->setStyleSheet("QFrame { background-color:#F2F2F2; border-radius:20px; }");
    QVBoxLayout *containerLayout = new QVBoxLayout(container);
    containerLayout->setContentsMargins(30, 30, 30, 30);

    QLabel *titre = new QLabel("🚛 Informations Collecte");
    titre->setAlignment(Qt::AlignCenter);
    titre->setStyleSheet(
        "QLabel { font-size:20px; font-weight:bold; color:white; padding:20px;"
        "border-radius:18px;"
        "background:qlineargradient(x1:0,y1:0,x2:0,y2:1,"
        "stop:0 #2C5F7C, stop:1 #1B3A57); }"
        );
    containerLayout->addWidget(titre);
    containerLayout->addSpacing(20);

    QWidget *contentWidget = new QWidget();
    contentWidget->setStyleSheet("background-color:white; border-radius:15px;");
    QGridLayout *gridLayout = new QGridLayout(contentWidget);
    gridLayout->setSpacing(15);
    gridLayout->setContentsMargins(25, 25, 25, 25);

    QString labelStyle =
        "QLabel { background-color:transparent; padding:5px;"
        "font-size:13px; font-weight:600; color:#374151; }";
    QString editStyle =
        "QLineEdit, QDateEdit, QComboBox, QDoubleSpinBox {"
        "background-color:#F9FAFB; border:1px solid #D1D5DB;"
        "border-radius:8px; padding:12px 16px; font-size:14px; color:#111827; }"
        "QLineEdit:hover, QDateEdit:hover, QComboBox:hover, QDoubleSpinBox:hover {"
        "border:1px solid #2C5F7C; background-color:#FFFFFF; }";

    // Champs
    QDateEdit *date = new QDateEdit(QDate::currentDate());
    date->setDisplayFormat("dd/MM/yyyy");
    date->setCalendarPopup(true);
    date->setStyleSheet(editStyle);

    QComboBox *typeDechet = new QComboBox();
    typeDechet->addItems({"Ménager", "Recyclable", "Organique", "Industriel", "Mixte"});
    typeDechet->setStyleSheet(editStyle);

    QDoubleSpinBox *quantite = new QDoubleSpinBox();
    quantite->setSuffix(" kg"); quantite->setDecimals(2);
    quantite->setMaximum(9999.99);
    quantite->setStyleSheet(editStyle);

    QComboBox *statut = new QComboBox();
    statut->addItems({"Planifiée", "En cours", "Terminée"});
    statut->setStyleSheet(editStyle);

    QDoubleSpinBox *distance = new QDoubleSpinBox();
    distance->setSuffix(" km"); distance->setDecimals(2);
    distance->setMaximum(9999.99);
    distance->setStyleSheet(editStyle);

    QLineEdit *observations = new QLineEdit();
    observations->setPlaceholderText("Notes, zone, remarques...");
    observations->setStyleSheet(editStyle);

    // Labels
    QLabel *lblDate = new QLabel("📅 Date :");                   lblDate->setStyleSheet(labelStyle);
    QLabel *lblType = new QLabel("🗑️ Type de Déchet :");         lblType->setStyleSheet(labelStyle);
    QLabel *lblQte  = new QLabel("⚖️ Quantité collectée (kg) :"); lblQte->setStyleSheet(labelStyle);
    QLabel *lblStat = new QLabel("📊 Statut :");                  lblStat->setStyleSheet(labelStyle);
    QLabel *lblDist = new QLabel("📏 Distance (km) :");           lblDist->setStyleSheet(labelStyle);
    QLabel *lblObs  = new QLabel("📝 Observations :");            lblObs->setStyleSheet(labelStyle);

    gridLayout->addWidget(lblDate, 0, 0); gridLayout->addWidget(date,         0, 1);
    gridLayout->addWidget(lblType, 1, 0); gridLayout->addWidget(typeDechet,   1, 1);
    gridLayout->addWidget(lblQte,  2, 0); gridLayout->addWidget(quantite,     2, 1);
    gridLayout->addWidget(lblStat, 0, 2); gridLayout->addWidget(statut,       0, 3);
    gridLayout->addWidget(lblDist, 1, 2); gridLayout->addWidget(distance,     1, 3);
    gridLayout->addWidget(lblObs,  2, 2); gridLayout->addWidget(observations, 2, 3);

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
        "QPushButton { background-color:#E5E7EB; color:#374151; font-size:15px;"
        "font-weight:600; border:none; border-radius:8px; padding:12px 30px; }"
        "QPushButton:hover { background-color:#D1D5DB; }"
        );

    QPushButton *ajouter = new QPushButton("✓ Ajouter");
    ajouter->setMinimumHeight(50);
    ajouter->setStyleSheet(
        "QPushButton { background:qlineargradient(x1:0,y1:0,x2:0,y2:1,"
        "stop:0 #2C5F7C, stop:1 #1B3A57); color:white; font-size:15px;"
        "font-weight:600; border:none; border-radius:8px; padding:12px 30px; }"
        "QPushButton:hover { background:qlineargradient(x1:0,y1:0,x2:0,y2:1,"
        "stop:0 #3A6EA5, stop:1 #2C5F7C); }"
        );

    btnLayout->addWidget(annuler);
    btnLayout->addWidget(ajouter);
    containerLayout->addLayout(btnLayout);
    mainLayout->addWidget(container);

    connect(annuler, &QPushButton::clicked, dialog, &QDialog::reject);

    connect(ajouter, &QPushButton::clicked, this, [=]() {
        // Validation
        if (quantite->value() <= 0.0) {
            showMessage(dialog, "Erreur", "La quantité collectée doit être supérieure à 0 !", "error");
            return;
        }
        Collecte c(0,
                   date->date().toString("dd/MM/yyyy"),
                   typeDechet->currentText(),
                   quantite->value(),
                   statut->currentText(),
                   distance->value(),
                   observations->text().trimmed());

        if (c.ajouter()) {
            showMessage(dialog, "Succès", "✅ Collecte ajoutée avec succès !", "success");
            afficherCollectes();
            dialog->accept();
        } else {
            showMessage(dialog, "Erreur", "Impossible d'ajouter cette collecte.", "error");
        }
    });

    dialog->exec();
}


// ================================================================
// === MODULE CONTENEUR — AJOUT (CORRIGÉ) =========================
// ================================================================
// CORRECTIONS :
//   - Colonnes alignées avec le vrai schéma Oracle (CONTENEURS)
//   - ID calculé automatiquement avec MAX+1
// ================================================================

void MainWindow::on_bouttonajouterconteneur_clicked()
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
    container->setStyleSheet("QFrame { background-color:#F2F2F2; border-radius:20px; }");
    QVBoxLayout *containerLayout = new QVBoxLayout(container);
    containerLayout->setContentsMargins(30, 30, 30, 30);

    QLabel *titre = new QLabel("🗑️ Informations Conteneur");
    titre->setAlignment(Qt::AlignCenter);
    titre->setStyleSheet(
        "QLabel { font-size:20px; font-weight:bold; color:white; padding:20px;"
        "border-radius:18px;"
        "background:qlineargradient(x1:0,y1:0,x2:0,y2:1,"
        "stop:0 #2C5F7C, stop:1 #1B3A57); }"
        );
    containerLayout->addWidget(titre);
    containerLayout->addSpacing(20);

    QScrollArea *scrollArea = new QScrollArea();
    scrollArea->setWidgetResizable(true);
    scrollArea->setFrameShape(QFrame::NoFrame);

    QWidget *scrollWidget = new QWidget();
    scrollWidget->setStyleSheet("background-color:white; border-radius:15px;");
    QVBoxLayout *scrollLayout = new QVBoxLayout(scrollWidget);
    scrollLayout->setSpacing(20);
    scrollLayout->setContentsMargins(25, 25, 25, 25);

    QString labelStyle =
        "QLabel { background-color:transparent; padding:5px;"
        "font-size:13px; font-weight:600; color:#374151; }";
    QString editStyle =
        "QLineEdit, QDateEdit, QSpinBox, QDoubleSpinBox, QComboBox {"
        "background-color:#F9FAFB; border:1px solid #D1D5DB;"
        "border-radius:8px; padding:12px 16px; font-size:14px; color:#111827; }"
        "QLineEdit:hover, QDateEdit:hover, QSpinBox:hover, QDoubleSpinBox:hover, QComboBox:hover {"
        "border:1px solid #2C5F7C; background-color:#FFFFFF; }";

    // ── Section 1 : Informations de base
    QLabel *section1 = new QLabel("📋 Informations de Base");
    section1->setStyleSheet("font-size:15px; font-weight:bold; color:#2C5F7C; padding:10px 0px;");
    scrollLayout->addWidget(section1);

    QGridLayout *grid1 = new QGridLayout();
    grid1->setSpacing(15);

    QDoubleSpinBox *capacite = new QDoubleSpinBox();
    capacite->setSuffix(" L"); capacite->setDecimals(2);
    capacite->setMinimum(0.0); capacite->setMaximum(999999.99);
    capacite->setStyleSheet(editStyle);

    QLineEdit *localisation    = new QLineEdit(); localisation->setStyleSheet(editStyle);
    QLineEdit *adresseComplete = new QLineEdit(); adresseComplete->setStyleSheet(editStyle);

    QComboBox *typePropriete = new QComboBox();
    typePropriete->addItems({"Public", "Privé", "Mixte"});
    typePropriete->setStyleSheet(editStyle);

    QLabel *lblCap   = new QLabel("📦 Capacité (L) *");        lblCap->setStyleSheet(labelStyle);
    QLabel *lblLoc   = new QLabel("📍 Localisation GPS *");    lblLoc->setStyleSheet(labelStyle);
    QLabel *lblAdr   = new QLabel("🏠 Adresse complète *");    lblAdr->setStyleSheet(labelStyle);
    QLabel *lblTProp = new QLabel("🏢 Type de Propriété");     lblTProp->setStyleSheet(labelStyle);

    grid1->addWidget(lblCap,   0, 0); grid1->addWidget(capacite,       0, 1);
    grid1->addWidget(lblLoc,   1, 0); grid1->addWidget(localisation,   1, 1);
    grid1->addWidget(lblAdr,   2, 0); grid1->addWidget(adresseComplete,2, 1);
    grid1->addWidget(lblTProp, 3, 0); grid1->addWidget(typePropriete,  3, 1);
    scrollLayout->addLayout(grid1);

    // ── Section 2 : Types de déchets acceptés
    QLabel *section2 = new QLabel("♻️ Déchets Acceptés :");
    section2->setStyleSheet("font-size:15px; font-weight:bold; color:#2C5F7C; padding:10px 0px;");
    scrollLayout->addWidget(section2);

    QString checkStyle =
        "QComboBox { background-color:#F9FAFB; border:1px solid #D1D5DB;"
        "border-radius:8px; padding:12px 16px; font-size:14px; color:#111827; }"
        "QComboBox:hover { border:1px solid #2C5F7C; background-color:#FFFFFF; }";

    QWidget *checkWidget = new QWidget();
    checkWidget->setStyleSheet("background-color:#F9FAFB; border-radius:8px; border:1px solid #D1D5DB;");
    QGridLayout *checkLayout = new QGridLayout(checkWidget);
    checkLayout->setContentsMargins(15, 10, 15, 10);
    checkLayout->setSpacing(10);

    QCheckBox *chkMenager    = new QCheckBox("🏠 Ménager");
    QCheckBox *chkRecyclable = new QCheckBox("♻️ Recyclable");
    QCheckBox *chkOrganique  = new QCheckBox("🌿 Organique");
    QCheckBox *chkIndustriel = new QCheckBox("🏭 Industriel");

    // Par défaut : Ménager et Recyclable cochés
    chkMenager->setChecked(true);
    chkRecyclable->setChecked(true);

    QString chkStyleSheet =
        "QCheckBox { font-size:14px; color:#111827; padding:8px; }"
        "QCheckBox::indicator { width:20px; height:20px; border-radius:4px; border:2px solid #D1D5DB; }"
        "QCheckBox::indicator:checked { background-color:#2C5F7C; border:2px solid #2C5F7C; }";
    for (QCheckBox *chk : {chkMenager, chkRecyclable, chkOrganique, chkIndustriel})
        chk->setStyleSheet(chkStyleSheet);

    checkLayout->addWidget(chkMenager,    0, 0);
    checkLayout->addWidget(chkRecyclable, 0, 1);
    checkLayout->addWidget(chkOrganique,  1, 0);
    checkLayout->addWidget(chkIndustriel, 1, 1);
    scrollLayout->addWidget(checkWidget);

    // ── Section 3 : État et monitoring
    QLabel *section3 = new QLabel("📊 État et Monitoring :");
    section3->setStyleSheet("font-size:15px; font-weight:bold; color:#2C5F7C; padding:10px 0px;");
    scrollLayout->addWidget(section3);

    QGridLayout *grid2 = new QGridLayout();
    grid2->setSpacing(15);

    QComboBox *etatConteneur = new QComboBox();
    etatConteneur->addItems({"Opérationnel", "En maintenance", "Hors service"});
    etatConteneur->setStyleSheet(editStyle);

    QDateEdit *dateDerniereCollecte = new QDateEdit(QDate::currentDate());
    dateDerniereCollecte->setDisplayFormat("dd/MM/yyyy");
    dateDerniereCollecte->setCalendarPopup(true);
    dateDerniereCollecte->setStyleSheet(editStyle);

    QLabel *lblEtat = new QLabel("✅ État du Conteneur :"); lblEtat->setStyleSheet(labelStyle);
    QLabel *lblDCol = new QLabel("📅 Date Dernière Collecte :"); lblDCol->setStyleSheet(labelStyle);

    grid2->addWidget(lblEtat, 0, 0); grid2->addWidget(etatConteneur,        0, 1);
    grid2->addWidget(lblDCol, 1, 0); grid2->addWidget(dateDerniereCollecte, 1, 1);
    scrollLayout->addLayout(grid2);

    scrollArea->setWidget(scrollWidget);
    containerLayout->addWidget(scrollArea);
    containerLayout->addSpacing(15);

    QLabel *note = new QLabel("* Tous les champs sont obligatoires");
    note->setStyleSheet("color:#6E7F91; font-style:italic; font-size:12px;");
    containerLayout->addWidget(note);

    QHBoxLayout *btnLayout = new QHBoxLayout();
    btnLayout->setSpacing(15);

    QPushButton *annuler = new QPushButton("✗ Annuler");
    annuler->setMinimumHeight(50);
    annuler->setStyleSheet(
        "QPushButton { background-color:#E5E7EB; color:#374151; font-size:15px;"
        "font-weight:600; border:none; border-radius:8px; padding:12px 30px; }"
        "QPushButton:hover { background-color:#D1D5DB; }"
        );

    QPushButton *ajouter = new QPushButton("✓ Ajouter");
    ajouter->setMinimumHeight(50);
    ajouter->setStyleSheet(
        "QPushButton { background:qlineargradient(x1:0,y1:0,x2:0,y2:1,"
        "stop:0 #2C5F7C, stop:1 #1B3A57); color:white; font-size:15px;"
        "font-weight:600; border:none; border-radius:8px; padding:12px 30px; }"
        "QPushButton:hover { background:qlineargradient(x1:0,y1:0,x2:0,y2:1,"
        "stop:0 #3A6EA5, stop:1 #2C5F7C); }"
        );

    btnLayout->addWidget(annuler);
    btnLayout->addWidget(ajouter);
    containerLayout->addLayout(btnLayout);
    mainLayout->addWidget(container);

    connect(annuler, &QPushButton::clicked, dialog, &QDialog::reject);

    connect(ajouter, &QPushButton::clicked, this, [=]() {
        // Validation
        if (localisation->text().trimmed().isEmpty() || adresseComplete->text().trimmed().isEmpty()) {
            showMessage(dialog, "Champs manquants", "Merci de remplir tous les champs obligatoires.", "warning");
            return;
        }
        if (capacite->value() <= 0.0) {
            showMessage(dialog, "Erreur", "La capacité doit être supérieure à 0 !", "error");
            return;
        }

        Conteneur ct(0,
                     capacite->value(),
                     typePropriete->currentText(),
                     adresseComplete->text().trimmed(),
                     localisation->text().trimmed(),
                     chkMenager->isChecked()    ? "Oui" : "Non",
                     chkRecyclable->isChecked() ? "Oui" : "Non",
                     chkOrganique->isChecked()  ? "Oui" : "Non",
                     chkIndustriel->isChecked() ? "Oui" : "Non",
                     etatConteneur->currentText(),
                     dateDerniereCollecte->date().toString("dd/MM/yyyy"));

        if (ct.ajouter()) {
            showMessage(dialog, "Succès", "✅ Conteneur ajouté avec succès !", "success");
            afficherConteneurs();
            dialog->accept();
        } else {
            showMessage(dialog, "Erreur", "Impossible d'ajouter ce conteneur.", "error");
        }
    });

    dialog->exec();
}


// ================================================================
// REMPLACE ces 6 fonctions dans ton mainwindow.cpp :
//   - on_bouttonmodifiercollecte_clicked()
//   - afficherWidgetModifierCollecte()
//   - on_bouttonsupprimercollecte_clicked()
//   - on_bouttonmodifierconteneur_clicked()
//   - afficherWidgetModifierConteneur()
//   - on_bouttonsupprimerconteneur_clicked()
//   - on_bouttonmodifierrecyclage_clicked()
//   - afficherWidgetModifierRecyclage()
//   - on_bouttonsupprimerrecyclage_clicked()
// ================================================================


// ================================================================
// === MODULE COLLECTE — SUPPRESSION ==============================
// ================================================================
void MainWindow::on_bouttonsupprimercollecte_clicked()
{
    int row = ui->tableWidget_collecte->currentRow();
    if (row < 0) {
        showMessage(this, "Attention",
                    "⚠️ Veuillez sélectionner une collecte dans le tableau avant de supprimer !",
                    "warning");
        return;
    }

    // Récupère l'ID depuis la colonne 0 (cachée mais présente)
    QTableWidgetItem *idItem = ui->tableWidget_collecte->item(row, 0);
    if (!idItem || idItem->text().trimmed().isEmpty()) {
        showMessage(this, "Erreur", "Impossible de récupérer l'ID de la collecte.", "error");
        return;
    }

    int idCollecte = idItem->text().toInt();
    QString dateCollecte = ui->tableWidget_collecte->item(row, 1)->text();

    // Vérification FK → CONSOMMER
    QSqlQuery checkFK1;
    checkFK1.prepare("SELECT COUNT(*) FROM CONSOMMER WHERE ID_collecte = :id");
    checkFK1.bindValue(":id", idCollecte);
    if (checkFK1.exec() && checkFK1.next()) {
        if (checkFK1.value(0).toInt() > 0) {
            showMessage(this, "Suppression impossible",
                        "❌ Cette collecte est liée à " +
                            QString::number(checkFK1.value(0).toInt()) +
                            " conteneur(s) dans CONSOMMER.\nVeuillez d'abord supprimer ces liens.",
                        "error");
            return;
        }
    }

    // Vérification FK → FOURNIR
    QSqlQuery checkFK2;
    checkFK2.prepare("SELECT COUNT(*) FROM FOURNIR WHERE ID_collecte = :id");
    checkFK2.bindValue(":id", idCollecte);
    if (checkFK2.exec() && checkFK2.next()) {
        if (checkFK2.value(0).toInt() > 0) {
            showMessage(this, "Suppression impossible",
                        "❌ Cette collecte est liée à " +
                            QString::number(checkFK2.value(0).toInt()) +
                            " recyclage(s) dans FOURNIR.\nVeuillez d'abord supprimer ces liens.",
                        "error");
            return;
        }
    }

    QDialog *confirm = new QDialog(this);
    confirm->setFixedSize(440, 220);
    confirm->setStyleSheet("QDialog { background-color:#1E1E2E; border-radius:14px; }");

    QVBoxLayout *lay = new QVBoxLayout(confirm);
    lay->setContentsMargins(0, 0, 0, 24);
    lay->setSpacing(0);

    QWidget *header = new QWidget();
    header->setFixedHeight(62);
    header->setStyleSheet(
        "QWidget { background-color:#E67E22;"
        "border-top-left-radius:14px; border-top-right-radius:14px; }"
        );
    QHBoxLayout *hLay = new QHBoxLayout(header);
    hLay->setContentsMargins(22, 0, 22, 0);
    QLabel *lblTitre = new QLabel("⚠️  Confirmer la suppression");
    lblTitre->setStyleSheet(
        "font-size:15px; font-weight:bold; color:white; background:transparent;"
        );
    hLay->addWidget(lblTitre);
    lay->addWidget(header);

    QLabel *lblMsg = new QLabel(
        "Voulez-vous vraiment supprimer cette collecte ?\n📅 Date : " + dateCollecte +
        "\n🆔 ID : " + QString::number(idCollecte)
        );
    lblMsg->setAlignment(Qt::AlignCenter);
    lblMsg->setWordWrap(true);
    lblMsg->setStyleSheet(
        "font-size:13px; color:#C8C8D8; background:transparent;"
        "padding:16px 28px 8px 28px;"
        );
    lay->addWidget(lblMsg);
    lay->addStretch();

    QHBoxLayout *btnLay = new QHBoxLayout();
    btnLay->setSpacing(12);
    btnLay->setContentsMargins(20, 0, 20, 0);

    QPushButton *btnNon = new QPushButton("✗ Annuler");
    btnNon->setFixedHeight(40);
    btnNon->setStyleSheet(
        "QPushButton { background:#374151; color:white; font-size:13px;"
        "font-weight:600; border:none; border-radius:8px; }"
        "QPushButton:hover { background:#4B5563; }"
        );

    QPushButton *btnOui = new QPushButton("🗑️ Oui, supprimer");
    btnOui->setFixedHeight(40);
    btnOui->setStyleSheet(
        "QPushButton { background:#C0392B; color:white; font-size:13px;"
        "font-weight:600; border:none; border-radius:8px; }"
        "QPushButton:hover { background:#E74C3C; }"
        );

    btnLay->addWidget(btnNon);
    btnLay->addWidget(btnOui);
    lay->addLayout(btnLay);

    connect(btnNon, &QPushButton::clicked, confirm, &QDialog::reject);
    connect(btnOui, &QPushButton::clicked, confirm, &QDialog::accept);

    if (confirm->exec() == QDialog::Accepted) {
        if (Collecte::supprimer(idCollecte)) {
            showMessage(this, "Succès", "✅ Collecte supprimée avec succès !", "success");
            afficherCollectes();
        } else {
            showMessage(this, "Erreur", "Impossible de supprimer cette collecte.", "error");
        }
    }
}


// ================================================================
// === MODULE COLLECTE — MODIFICATION =============================
// ================================================================
void MainWindow::on_bouttonmodifiercollecte_clicked()
{
    int row = ui->tableWidget_collecte->currentRow();
    if (row < 0) {
        showMessage(this, "Attention",
                    "⚠️ Veuillez sélectionner une collecte dans le tableau avant de modifier !",
                    "warning");
        return;
    }

    QTableWidgetItem *idItem = ui->tableWidget_collecte->item(row, 0);
    if (!idItem || idItem->text().trimmed().isEmpty()) {
        showMessage(this, "Erreur", "Impossible de récupérer l'ID de la collecte.", "error");
        return;
    }

    afficherWidgetModifierCollecte(idItem->text().toInt());
}

void MainWindow::afficherWidgetModifierCollecte(int idCollecte)
{
    QDialog *dialog = new QDialog(this);
    dialog->setWindowTitle("✏️ Modifier une Collecte");
    dialog->setFixedSize(850, 600);
    dialog->setStyleSheet("QDialog { background-color: #EDEDED; }");

    QVBoxLayout *mainLayout = new QVBoxLayout(dialog);
    QFrame *container = new QFrame();
    container->setStyleSheet("QFrame { background-color:#F2F2F2; border-radius:20px; }");
    QVBoxLayout *containerLayout = new QVBoxLayout(container);
    containerLayout->setContentsMargins(30, 30, 30, 30);

    QLabel *titre = new QLabel("🚛 Modifier Collecte — ID : " + QString::number(idCollecte));
    titre->setAlignment(Qt::AlignCenter);
    titre->setStyleSheet(
        "QLabel { font-size:18px; font-weight:bold; color:white; padding:20px;"
        "border-radius:18px;"
        "background:qlineargradient(x1:0,y1:0,x2:0,y2:1,"
        "stop:0 #1A7A4A, stop:1 #0F4D2E); }"
        );
    containerLayout->addWidget(titre);
    containerLayout->addSpacing(20);

    QWidget *contentWidget = new QWidget();
    contentWidget->setStyleSheet("background-color:white; border-radius:15px;");
    QGridLayout *gridLayout = new QGridLayout(contentWidget);
    gridLayout->setSpacing(15);
    gridLayout->setContentsMargins(25, 25, 25, 25);

    QString labelStyle =
        "QLabel { background-color:transparent; padding:5px;"
        "font-size:13px; font-weight:600; color:#374151; }";
    QString editStyle =
        "QLineEdit, QDateEdit, QComboBox, QDoubleSpinBox {"
        "background-color:#F9FAFB; border:1px solid #D1D5DB;"
        "border-radius:8px; padding:12px 16px; font-size:14px; color:#111827; }"
        "QLineEdit:hover, QDateEdit:hover, QComboBox:hover, QDoubleSpinBox:hover {"
        "border:1px solid #1A7A4A; background-color:#FFFFFF; }"
        "QLineEdit:focus, QDateEdit:focus, QComboBox:focus, QDoubleSpinBox:focus {"
        "border:2px solid #1A7A4A; background-color:#FFFFFF; }";

    QDateEdit *dateCollecte = new QDateEdit(QDate::currentDate());
    dateCollecte->setDisplayFormat("dd/MM/yyyy");
    dateCollecte->setCalendarPopup(true);
    dateCollecte->setStyleSheet(editStyle);

    QComboBox *typeDechet = new QComboBox();
    typeDechet->addItems({"Ménager", "Recyclable", "Organique", "Industriel", "Mixte"});
    typeDechet->setStyleSheet(editStyle);

    QDoubleSpinBox *quantite = new QDoubleSpinBox();
    quantite->setSuffix(" kg"); quantite->setDecimals(2);
    quantite->setMinimum(0.0); quantite->setMaximum(999999.99);
    quantite->setStyleSheet(editStyle);

    QComboBox *statut = new QComboBox();
    statut->addItems({"Planifiée", "En cours", "Terminée", "Annulée"});
    statut->setStyleSheet(editStyle);

    QDoubleSpinBox *distance = new QDoubleSpinBox();
    distance->setSuffix(" km"); distance->setDecimals(2);
    distance->setMinimum(0.0); distance->setMaximum(99999.99);
    distance->setStyleSheet(editStyle);

    QLineEdit *observations = new QLineEdit();
    observations->setStyleSheet(editStyle);

    QLabel *lblDate = new QLabel("📅 Date de Collecte :"); lblDate->setStyleSheet(labelStyle);
    QLabel *lblType = new QLabel("🗑️ Type de Déchet :"); lblType->setStyleSheet(labelStyle);
    QLabel *lblQte  = new QLabel("⚖️ Quantité (kg) :"); lblQte->setStyleSheet(labelStyle);
    QLabel *lblStat = new QLabel("📊 Statut :"); lblStat->setStyleSheet(labelStyle);
    QLabel *lblDist = new QLabel("📏 Distance (km) :"); lblDist->setStyleSheet(labelStyle);
    QLabel *lblObs  = new QLabel("📝 Observations :"); lblObs->setStyleSheet(labelStyle);

    gridLayout->addWidget(lblDate, 0, 0); gridLayout->addWidget(dateCollecte, 0, 1);
    gridLayout->addWidget(lblType, 1, 0); gridLayout->addWidget(typeDechet,   1, 1);
    gridLayout->addWidget(lblQte,  2, 0); gridLayout->addWidget(quantite,     2, 1);
    gridLayout->addWidget(lblStat, 0, 2); gridLayout->addWidget(statut,       0, 3);
    gridLayout->addWidget(lblDist, 1, 2); gridLayout->addWidget(distance,     1, 3);
    gridLayout->addWidget(lblObs,  2, 2); gridLayout->addWidget(observations, 2, 3);

    containerLayout->addWidget(contentWidget);
    containerLayout->addSpacing(15);

    QHBoxLayout *btnLayout = new QHBoxLayout();
    btnLayout->setSpacing(15);

    QPushButton *annuler = new QPushButton("✗ Annuler");
    annuler->setMinimumHeight(50);
    annuler->setStyleSheet(
        "QPushButton { background-color:#E5E7EB; color:#374151; font-size:15px;"
        "font-weight:600; border:none; border-radius:8px; padding:12px 30px; }"
        "QPushButton:hover { background-color:#D1D5DB; }"
        );

    QPushButton *enregistrer = new QPushButton("✓ Enregistrer");
    enregistrer->setMinimumHeight(50);
    enregistrer->setStyleSheet(
        "QPushButton { background:qlineargradient(x1:0,y1:0,x2:0,y2:1,"
        "stop:0 #1A7A4A, stop:1 #0F4D2E); color:white; font-size:15px;"
        "font-weight:600; border:none; border-radius:8px; padding:12px 30px; }"
        "QPushButton:hover { background:qlineargradient(x1:0,y1:0,x2:0,y2:1,"
        "stop:0 #22A05A, stop:1 #1A7A4A); }"
        );

    btnLayout->addWidget(annuler);
    btnLayout->addWidget(enregistrer);
    containerLayout->addLayout(btnLayout);
    mainLayout->addWidget(container);

    connect(annuler, &QPushButton::clicked, dialog, &QDialog::reject);

    // Chargement des données depuis la DB
    Collecte c = Collecte::getById(idCollecte);
    if (c.getId() == 0) {
        showMessage(this, "Erreur", "Collecte introuvable.", "error");
        delete dialog;
        return;
    }

    QDate d = QDate::fromString(c.getDateCollecte(), "dd/MM/yyyy");
    if (!d.isValid()) d = QDate::currentDate();
    dateCollecte->setDate(d);
    typeDechet->setCurrentText(c.getTypeDechet());
    quantite->setValue(c.getQuantiteCollectee());
    statut->setCurrentText(c.getStatut());
    distance->setValue(c.getDistanceTotale());
    observations->setText(c.getObservations());

    connect(enregistrer, &QPushButton::clicked, this, [=]() {
        if (quantite->value() <= 0.0) {
            showMessage(dialog, "Erreur", "La quantité doit être supérieure à 0 !", "error");
            return;
        }

        Collecte cModif(idCollecte,
                        dateCollecte->date().toString("dd/MM/yyyy"),
                        typeDechet->currentText(),
                        quantite->value(),
                        statut->currentText(),
                        distance->value(),
                        observations->text().trimmed());

        if (cModif.modifier()) {
            showMessage(dialog, "Succès", "✅ Collecte modifiée avec succès !", "success");
            dialog->accept();
            afficherCollectes();
        } else {
            showMessage(dialog, "Erreur", "Impossible de modifier cette collecte.", "error");
        }
    });

    dialog->exec();
}


// ================================================================
// === MODULE CONTENEUR — SUPPRESSION =============================
// ================================================================
void MainWindow::on_bouttonsupprimerconteneur_clicked()
{
    int row = ui->tableWidget_Conteneur->currentRow();
    if (row < 0) {
        showMessage(this, "Attention",
                    "⚠️ Veuillez sélectionner un conteneur dans le tableau avant de supprimer !",
                    "warning");
        return;
    }

    QTableWidgetItem *idItem = ui->tableWidget_Conteneur->item(row, 0);
    if (!idItem || idItem->text().trimmed().isEmpty()) {
        showMessage(this, "Erreur", "Impossible de récupérer l'ID du conteneur.", "error");
        return;
    }

    int idConteneur = idItem->text().toInt();
    QString adresseConteneur = ui->tableWidget_Conteneur->item(row, 3)->text();

    // Vérification FK → CONSOMMER
    QSqlQuery checkFK;
    checkFK.prepare("SELECT COUNT(*) FROM CONSOMMER WHERE ID_conteneur = :id");
    checkFK.bindValue(":id", idConteneur);
    if (checkFK.exec() && checkFK.next()) {
        if (checkFK.value(0).toInt() > 0) {
            showMessage(this, "Suppression impossible",
                        "❌ Ce conteneur est lié à " +
                            QString::number(checkFK.value(0).toInt()) +
                            " collecte(s) dans CONSOMMER.\nVeuillez d'abord supprimer ces liens.",
                        "error");
            return;
        }
    }

    QDialog *confirm = new QDialog(this);
    confirm->setFixedSize(440, 220);
    confirm->setStyleSheet("QDialog { background-color:#1E1E2E; border-radius:14px; }");

    QVBoxLayout *lay = new QVBoxLayout(confirm);
    lay->setContentsMargins(0, 0, 0, 24);
    lay->setSpacing(0);

    QWidget *header = new QWidget();
    header->setFixedHeight(62);
    header->setStyleSheet(
        "QWidget { background-color:#E67E22;"
        "border-top-left-radius:14px; border-top-right-radius:14px; }"
        );
    QHBoxLayout *hLay = new QHBoxLayout(header);
    hLay->setContentsMargins(22, 0, 22, 0);
    QLabel *lblTitre = new QLabel("⚠️  Confirmer la suppression");
    lblTitre->setStyleSheet(
        "font-size:15px; font-weight:bold; color:white; background:transparent;"
        );
    hLay->addWidget(lblTitre);
    lay->addWidget(header);

    QLabel *lblMsg = new QLabel(
        "Voulez-vous vraiment supprimer ce conteneur ?\n🏠 Adresse : " + adresseConteneur +
        "\n🆔 ID : " + QString::number(idConteneur)
        );
    lblMsg->setAlignment(Qt::AlignCenter);
    lblMsg->setWordWrap(true);
    lblMsg->setStyleSheet(
        "font-size:13px; color:#C8C8D8; background:transparent;"
        "padding:16px 28px 8px 28px;"
        );
    lay->addWidget(lblMsg);
    lay->addStretch();

    QHBoxLayout *btnLay = new QHBoxLayout();
    btnLay->setSpacing(12);
    btnLay->setContentsMargins(20, 0, 20, 0);

    QPushButton *btnNon = new QPushButton("✗ Annuler");
    btnNon->setFixedHeight(40);
    btnNon->setStyleSheet(
        "QPushButton { background:#374151; color:white; font-size:13px;"
        "font-weight:600; border:none; border-radius:8px; }"
        "QPushButton:hover { background:#4B5563; }"
        );

    QPushButton *btnOui = new QPushButton("🗑️ Oui, supprimer");
    btnOui->setFixedHeight(40);
    btnOui->setStyleSheet(
        "QPushButton { background:#C0392B; color:white; font-size:13px;"
        "font-weight:600; border:none; border-radius:8px; }"
        "QPushButton:hover { background:#E74C3C; }"
        );

    btnLay->addWidget(btnNon);
    btnLay->addWidget(btnOui);
    lay->addLayout(btnLay);

    connect(btnNon, &QPushButton::clicked, confirm, &QDialog::reject);
    connect(btnOui, &QPushButton::clicked, confirm, &QDialog::accept);

    if (confirm->exec() == QDialog::Accepted) {
        if (Conteneur::supprimer(idConteneur)) {
            showMessage(this, "Succès", "✅ Conteneur supprimé avec succès !", "success");
            afficherConteneurs();
        } else {
            showMessage(this, "Erreur", "Impossible de supprimer ce conteneur.", "error");
        }
    }

}


// ================================================================
// === MODULE CONTENEUR — MODIFICATION ============================
// ================================================================
void MainWindow::on_bouttonmodifierconteneur_clicked()
{
    int row = ui->tableWidget_Conteneur->currentRow();
    if (row < 0) {
        showMessage(this, "Attention",
                    "⚠️ Veuillez sélectionner un conteneur dans le tableau avant de modifier !",
                    "warning");
        return;
    }

    QTableWidgetItem *idItem = ui->tableWidget_Conteneur->item(row, 0);
    if (!idItem || idItem->text().trimmed().isEmpty()) {
        showMessage(this, "Erreur", "Impossible de récupérer l'ID du conteneur.", "error");
        return;
    }

    afficherWidgetModifierConteneur(idItem->text().toInt());
}

void MainWindow::afficherWidgetModifierConteneur(int idConteneur)
{
    QDialog *dialog = new QDialog(this);
    dialog->setWindowTitle("✏️ Modifier un Conteneur");
    dialog->setFixedSize(850, 650);
    dialog->setStyleSheet("QDialog { background-color: #EDEDED; }");

    QVBoxLayout *mainLayout = new QVBoxLayout(dialog);
    QFrame *container = new QFrame();
    container->setStyleSheet("QFrame { background-color:#F2F2F2; border-radius:20px; }");
    QVBoxLayout *containerLayout = new QVBoxLayout(container);
    containerLayout->setContentsMargins(30, 30, 30, 30);

    QLabel *titre = new QLabel("🗑️ Modifier Conteneur — ID : " + QString::number(idConteneur));
    titre->setAlignment(Qt::AlignCenter);
    titre->setStyleSheet(
        "QLabel { font-size:18px; font-weight:bold; color:white; padding:20px;"
        "border-radius:18px;"
        "background:qlineargradient(x1:0,y1:0,x2:0,y2:1,"
        "stop:0 #1A7A4A, stop:1 #0F4D2E); }"
        );
    containerLayout->addWidget(titre);
    containerLayout->addSpacing(20);

    QScrollArea *scrollArea = new QScrollArea();
    scrollArea->setWidgetResizable(true);
    scrollArea->setFrameShape(QFrame::NoFrame);

    QWidget *scrollWidget = new QWidget();
    scrollWidget->setStyleSheet("background-color:white; border-radius:15px;");
    QVBoxLayout *scrollLayout = new QVBoxLayout(scrollWidget);
    scrollLayout->setSpacing(20);
    scrollLayout->setContentsMargins(25, 25, 25, 25);

    QString labelStyle =
        "QLabel { background-color:transparent; padding:5px;"
        "font-size:13px; font-weight:600; color:#374151; }";
    QString editStyle =
        "QLineEdit, QDateEdit, QComboBox, QDoubleSpinBox {"
        "background-color:#F9FAFB; border:1px solid #D1D5DB;"
        "border-radius:8px; padding:12px 16px; font-size:14px; color:#111827; }"
        "QLineEdit:hover, QDateEdit:hover, QComboBox:hover, QDoubleSpinBox:hover {"
        "border:1px solid #1A7A4A; background-color:#FFFFFF; }"
        "QLineEdit:focus, QDateEdit:focus {"
        "border:2px solid #1A7A4A; background-color:#FFFFFF; padding:11px 15px; }";
    QString checkStyle =
        "QCheckBox { font-size:14px; color:#111827; padding:8px; }"
        "QCheckBox::indicator { width:20px; height:20px; border-radius:4px; border:2px solid #D1D5DB; }"
        "QCheckBox::indicator:checked { background-color:#1A7A4A; border:2px solid #1A7A4A; }";

    // Capacité
    QDoubleSpinBox *capacite = new QDoubleSpinBox();
    capacite->setSuffix(" L"); capacite->setDecimals(2);
    capacite->setMinimum(0.0); capacite->setMaximum(999999.99);
    capacite->setStyleSheet(editStyle);
    QLabel *lblCap = new QLabel("📦 Capacité (L) *"); lblCap->setStyleSheet(labelStyle);
    scrollLayout->addWidget(lblCap);
    scrollLayout->addWidget(capacite);

    // Type propriété
    QComboBox *typePropriete = new QComboBox();
    typePropriete->addItems({"Public", "Privé", "Mixte"});
    typePropriete->setStyleSheet(editStyle);
    QLabel *lblTypeProp = new QLabel("🏢 Type de Propriété *"); lblTypeProp->setStyleSheet(labelStyle);
    scrollLayout->addWidget(lblTypeProp);
    scrollLayout->addWidget(typePropriete);

    // Adresse
    QLineEdit *adresse = new QLineEdit(); adresse->setStyleSheet(editStyle);
    QLabel *lblAdr = new QLabel("🏠 Adresse Complète *"); lblAdr->setStyleSheet(labelStyle);
    scrollLayout->addWidget(lblAdr);
    scrollLayout->addWidget(adresse);

    // GPS
    QLineEdit *gps = new QLineEdit(); gps->setStyleSheet(editStyle);
    QLabel *lblGps = new QLabel("📍 Localisation GPS"); lblGps->setStyleSheet(labelStyle);
    scrollLayout->addWidget(lblGps);
    scrollLayout->addWidget(gps);

    // Checkboxes déchets
    QLabel *lblChk = new QLabel("♻️ Types de Déchets Acceptés"); lblChk->setStyleSheet(labelStyle);
    scrollLayout->addWidget(lblChk);

    QWidget *checkWidget = new QWidget();
    checkWidget->setStyleSheet("background-color:#F9FAFB; border-radius:8px; border:1px solid #D1D5DB;");
    QGridLayout *checkLayout = new QGridLayout(checkWidget);
    checkLayout->setContentsMargins(15, 10, 15, 10);
    checkLayout->setSpacing(10);

    QCheckBox *chkMenager    = new QCheckBox("🏠 Ménager");
    QCheckBox *chkRecyclable = new QCheckBox("♻️ Recyclable");
    QCheckBox *chkOrganique  = new QCheckBox("🌿 Organique");
    QCheckBox *chkIndustriel = new QCheckBox("🏭 Industriel");

    for (QCheckBox *chk : {chkMenager, chkRecyclable, chkOrganique, chkIndustriel})
        chk->setStyleSheet(checkStyle);

    checkLayout->addWidget(chkMenager,    0, 0);
    checkLayout->addWidget(chkRecyclable, 0, 1);
    checkLayout->addWidget(chkOrganique,  1, 0);
    checkLayout->addWidget(chkIndustriel, 1, 1);
    scrollLayout->addWidget(checkWidget);

    // État
    QComboBox *etat = new QComboBox();
    etat->addItems({"Opérationnel", "En maintenance", "Hors service"});
    etat->setStyleSheet(editStyle);
    QLabel *lblEtat = new QLabel("⚙️ État *"); lblEtat->setStyleSheet(labelStyle);
    scrollLayout->addWidget(lblEtat);
    scrollLayout->addWidget(etat);

    // Date dernière collecte
    QDateEdit *dateDC = new QDateEdit(QDate::currentDate());
    dateDC->setDisplayFormat("dd/MM/yyyy");
    dateDC->setCalendarPopup(true);
    dateDC->setStyleSheet(editStyle);
    QLabel *lblDateDC = new QLabel("📅 Date Dernière Collecte"); lblDateDC->setStyleSheet(labelStyle);
    scrollLayout->addWidget(lblDateDC);
    scrollLayout->addWidget(dateDC);

    scrollArea->setWidget(scrollWidget);
    containerLayout->addWidget(scrollArea);
    containerLayout->addSpacing(15);

    QHBoxLayout *btnLayout = new QHBoxLayout();
    btnLayout->setSpacing(15);

    QPushButton *annuler = new QPushButton("✗ Annuler");
    annuler->setMinimumHeight(50);
    annuler->setStyleSheet(
        "QPushButton { background-color:#E5E7EB; color:#374151; font-size:15px;"
        "font-weight:600; border:none; border-radius:8px; padding:12px 30px; }"
        "QPushButton:hover { background-color:#D1D5DB; }"
        );

    QPushButton *enregistrer = new QPushButton("✓ Enregistrer");
    enregistrer->setMinimumHeight(50);
    enregistrer->setStyleSheet(
        "QPushButton { background:qlineargradient(x1:0,y1:0,x2:0,y2:1,"
        "stop:0 #1A7A4A, stop:1 #0F4D2E); color:white; font-size:15px;"
        "font-weight:600; border:none; border-radius:8px; padding:12px 30px; }"
        "QPushButton:hover { background:qlineargradient(x1:0,y1:0,x2:0,y2:1,"
        "stop:0 #22A05A, stop:1 #1A7A4A); }"
        );

    btnLayout->addWidget(annuler);
    btnLayout->addWidget(enregistrer);
    containerLayout->addLayout(btnLayout);
    mainLayout->addWidget(container);

    connect(annuler, &QPushButton::clicked, dialog, &QDialog::reject);

    Conteneur ct = Conteneur::getById(idConteneur);
    if (ct.getId() == 0) {
        showMessage(this, "Erreur", "Conteneur introuvable.", "error");
        delete dialog;
        return;
    }

    capacite->setValue(ct.getCapacite());
    typePropriete->setCurrentText(ct.getTypePropriete());
    adresse->setText(ct.getAdresseComplete());
    gps->setText(ct.getLocalisationGPS());

    auto isOui = [](const QString &v) {
        return v.toLower() == "oui" || v == "1" || v.toLower() == "true";
    };
    chkMenager->setChecked(isOui(ct.getAccepteMenager()));
    chkRecyclable->setChecked(isOui(ct.getAccepteRecyclable()));
    chkOrganique->setChecked(isOui(ct.getAccepteOrganique()));
    chkIndustriel->setChecked(isOui(ct.getAccepteIndustriel()));

    etat->setCurrentText(ct.getEtat());

    QDate dDC = QDate::fromString(ct.getDateDerniereCollecte(), "dd/MM/yyyy");
    if (!dDC.isValid()) dDC = QDate::currentDate();
    dateDC->setDate(dDC);

    connect(enregistrer, &QPushButton::clicked, this, [=]() {
        if (adresse->text().trimmed().isEmpty()) {
            showMessage(dialog, "Erreur", "L'adresse est obligatoire !", "error");
            return;
        }
        if (capacite->value() <= 0.0) {
            showMessage(dialog, "Erreur", "La capacité doit être supérieure à 0 !", "error");
            return;
        }

        Conteneur ctModif(idConteneur,
                          capacite->value(),
                          typePropriete->currentText(),
                          adresse->text().trimmed(),
                          gps->text().trimmed(),
                          chkMenager->isChecked()    ? "Oui" : "Non",
                          chkRecyclable->isChecked() ? "Oui" : "Non",
                          chkOrganique->isChecked()  ? "Oui" : "Non",
                          chkIndustriel->isChecked() ? "Oui" : "Non",
                          etat->currentText(),
                          dateDC->date().toString("dd/MM/yyyy"));

        if (ctModif.modifier()) {
            showMessage(dialog, "Succès", "✅ Conteneur modifié avec succès !", "success");
            dialog->accept();
            afficherConteneurs();
        } else {
            showMessage(dialog, "Erreur", "Impossible de modifier ce conteneur.", "error");
        }
    });

    dialog->exec();
}


// ================================================================
// === MODULE RECYCLAGE — SUPPRESSION =============================
// ================================================================
void MainWindow::on_bouttonsupprimerrecyclage_clicked()
{
    int row = ui->tableWidget_Recyclage->currentRow();
    if (row < 0) {
        showMessage(this, "Attention",
                    "⚠️ Veuillez sélectionner un recyclage dans le tableau avant de supprimer !",
                    "warning");
        return;
    }

    QTableWidgetItem *idItem = ui->tableWidget_Recyclage->item(row, 0);
    if (!idItem || idItem->text().trimmed().isEmpty()) {
        showMessage(this, "Erreur", "Impossible de récupérer l'ID du recyclage.", "error");
        return;
    }

    int idRecyclage = idItem->text().toInt();
    QString typeRecyclage = ui->tableWidget_Recyclage->item(row, 2)->text();

    // Vérification FK → REALISER
    QSqlQuery checkFK1;
    checkFK1.prepare("SELECT COUNT(*) FROM REALISER WHERE ID_recyclage = :id");
    checkFK1.bindValue(":id", idRecyclage);
    if (checkFK1.exec() && checkFK1.next()) {
        if (checkFK1.value(0).toInt() > 0) {
            showMessage(this, "Suppression impossible",
                        "❌ Ce recyclage est lié à " +
                            QString::number(checkFK1.value(0).toInt()) +
                            " employé(s) dans REALISER.\nVeuillez d'abord supprimer ces liens.",
                        "error");
            return;
        }
    }

    // Vérification FK → FOURNIR
    QSqlQuery checkFK2;
    checkFK2.prepare("SELECT COUNT(*) FROM FOURNIR WHERE ID_recyclage = :id");
    checkFK2.bindValue(":id", idRecyclage);
    if (checkFK2.exec() && checkFK2.next()) {
        if (checkFK2.value(0).toInt() > 0) {
            showMessage(this, "Suppression impossible",
                        "❌ Ce recyclage est lié à " +
                            QString::number(checkFK2.value(0).toInt()) +
                            " collecte(s) dans FOURNIR.\nVeuillez d'abord supprimer ces liens.",
                        "error");
            return;
        }
    }

    QDialog *confirm = new QDialog(this);
    confirm->setFixedSize(440, 220);
    confirm->setStyleSheet("QDialog { background-color:#1E1E2E; border-radius:14px; }");

    QVBoxLayout *lay = new QVBoxLayout(confirm);
    lay->setContentsMargins(0, 0, 0, 24);
    lay->setSpacing(0);

    QWidget *header = new QWidget();
    header->setFixedHeight(62);
    header->setStyleSheet(
        "QWidget { background-color:#E67E22;"
        "border-top-left-radius:14px; border-top-right-radius:14px; }"
        );
    QHBoxLayout *hLay = new QHBoxLayout(header);
    hLay->setContentsMargins(22, 0, 22, 0);
    QLabel *lblTitre = new QLabel("⚠️  Confirmer la suppression");
    lblTitre->setStyleSheet(
        "font-size:15px; font-weight:bold; color:white; background:transparent;"
        );
    hLay->addWidget(lblTitre);
    lay->addWidget(header);

    QLabel *lblMsg = new QLabel(
        "Voulez-vous vraiment supprimer ce recyclage ?\n♻️ Matériau : " + typeRecyclage +
        "\n🆔 ID : " + QString::number(idRecyclage)
        );
    lblMsg->setAlignment(Qt::AlignCenter);
    lblMsg->setWordWrap(true);
    lblMsg->setStyleSheet(
        "font-size:13px; color:#C8C8D8; background:transparent;"
        "padding:16px 28px 8px 28px;"
        );
    lay->addWidget(lblMsg);
    lay->addStretch();

    QHBoxLayout *btnLay = new QHBoxLayout();
    btnLay->setSpacing(12);
    btnLay->setContentsMargins(20, 0, 20, 0);

    QPushButton *btnNon = new QPushButton("✗ Annuler");
    btnNon->setFixedHeight(40);
    btnNon->setStyleSheet(
        "QPushButton { background:#374151; color:white; font-size:13px;"
        "font-weight:600; border:none; border-radius:8px; }"
        "QPushButton:hover { background:#4B5563; }"
        );

    QPushButton *btnOui = new QPushButton("🗑️ Oui, supprimer");
    btnOui->setFixedHeight(40);
    btnOui->setStyleSheet(
        "QPushButton { background:#C0392B; color:white; font-size:13px;"
        "font-weight:600; border:none; border-radius:8px; }"
        "QPushButton:hover { background:#E74C3C; }"
        );

    btnLay->addWidget(btnNon);
    btnLay->addWidget(btnOui);
    lay->addLayout(btnLay);

    connect(btnNon, &QPushButton::clicked, confirm, &QDialog::reject);
    connect(btnOui, &QPushButton::clicked, confirm, &QDialog::accept);

    if (confirm->exec() == QDialog::Accepted) {
        if (Recyclage::supprimer(idRecyclage)) {
            showMessage(this, "Succès", "✅ Recyclage supprimé avec succès !", "success");
            afficherRecyclages();
        } else {
            showMessage(this, "Erreur", "Impossible de supprimer ce recyclage.", "error");
        }
    }

}


// ================================================================
// === MODULE RECYCLAGE — MODIFICATION ============================
// ================================================================
void MainWindow::on_bouttonmodifierrecyclage_clicked()
{
    int row = ui->tableWidget_Recyclage->currentRow();
    if (row < 0) {
        showMessage(this, "Attention",
                    "⚠️ Veuillez sélectionner un recyclage dans le tableau avant de modifier !",
                    "warning");
        return;
    }

    QTableWidgetItem *idItem = ui->tableWidget_Recyclage->item(row, 0);
    if (!idItem || idItem->text().trimmed().isEmpty()) {
        showMessage(this, "Erreur", "Impossible de récupérer l'ID du recyclage.", "error");
        return;
    }

    afficherWidgetModifierRecyclage(idItem->text().toInt());
}

void MainWindow::afficherWidgetModifierRecyclage(int idRecyclage)
{
    QDialog *dialog = new QDialog(this);
    dialog->setWindowTitle("✏️ Modifier un Recyclage");
    dialog->setFixedSize(850, 600);
    dialog->setStyleSheet("QDialog { background-color: #EDEDED; }");

    QVBoxLayout *mainLayout = new QVBoxLayout(dialog);
    QFrame *container = new QFrame();
    container->setStyleSheet("QFrame { background-color:#F2F2F2; border-radius:20px; }");
    QVBoxLayout *containerLayout = new QVBoxLayout(container);
    containerLayout->setContentsMargins(30, 30, 30, 30);

    QLabel *titre = new QLabel("♻️ Modifier Recyclage — ID : " + QString::number(idRecyclage));
    titre->setAlignment(Qt::AlignCenter);
    titre->setStyleSheet(
        "QLabel { font-size:18px; font-weight:bold; color:white; padding:20px;"
        "border-radius:18px;"
        "background:qlineargradient(x1:0,y1:0,x2:0,y2:1,"
        "stop:0 #1A7A4A, stop:1 #0F4D2E); }"
        );
    containerLayout->addWidget(titre);
    containerLayout->addSpacing(20);

    QWidget *contentWidget = new QWidget();
    contentWidget->setStyleSheet("background-color:white; border-radius:15px;");
    QGridLayout *gridLayout = new QGridLayout(contentWidget);
    gridLayout->setSpacing(15);
    gridLayout->setContentsMargins(25, 25, 25, 25);

    QString labelStyle =
        "QLabel { background-color:transparent; padding:5px;"
        "font-size:13px; font-weight:600; color:#374151; }";
    QString editStyle =
        "QLineEdit, QComboBox, QDoubleSpinBox, QDateEdit {"
        "background-color:#F9FAFB; border:1px solid #D1D5DB;"
        "border-radius:8px; padding:12px 16px; font-size:14px; color:#111827; }"
        "QLineEdit:hover, QComboBox:hover, QDoubleSpinBox:hover, QDateEdit:hover {"
        "border:1px solid #1A7A4A; background-color:#FFFFFF; }"
        "QLineEdit:focus, QDateEdit:focus {"
        "border:2px solid #1A7A4A; background-color:#FFFFFF; padding:11px 15px; }";

    QDateEdit *dateTri = new QDateEdit(QDate::currentDate());
    dateTri->setDisplayFormat("dd/MM/yyyy");
    dateTri->setCalendarPopup(true);
    dateTri->setStyleSheet(editStyle);

    QComboBox *typeMateriau = new QComboBox();
    typeMateriau->addItems({"Plastique", "Verre", "Métal", "Papier", "Organique", "Electronique", "Autre"});
    typeMateriau->setStyleSheet(editStyle);

    QDoubleSpinBox *qteEntree = new QDoubleSpinBox();
    qteEntree->setSuffix(" kg"); qteEntree->setDecimals(2);
    qteEntree->setMinimum(0.0); qteEntree->setMaximum(999999.99);
    qteEntree->setStyleSheet(editStyle);

    QDoubleSpinBox *qteRecyclee = new QDoubleSpinBox();
    qteRecyclee->setSuffix(" kg"); qteRecyclee->setDecimals(2);
    qteRecyclee->setMinimum(0.0); qteRecyclee->setMaximum(999999.99);
    qteRecyclee->setStyleSheet(editStyle);

    QDoubleSpinBox *qteRejetee = new QDoubleSpinBox();
    qteRejetee->setSuffix(" kg"); qteRejetee->setDecimals(2);
    qteRejetee->setMinimum(0.0); qteRejetee->setMaximum(999999.99);
    qteRejetee->setStyleSheet(editStyle);

    QLineEdit *destination = new QLineEdit(); destination->setStyleSheet(editStyle);

    QDoubleSpinBox *valeur = new QDoubleSpinBox();
    valeur->setSuffix(" TND"); valeur->setDecimals(2);
    valeur->setMinimum(0.0); valeur->setMaximum(999999.99);
    valeur->setStyleSheet(editStyle);

    QLineEdit *direction = new QLineEdit(); direction->setStyleSheet(editStyle);

    QComboBox *statut = new QComboBox();
    statut->addItems({"En attente", "En cours", "Terminé", "Annulé"});
    statut->setStyleSheet(editStyle);

    QLabel *lblDate  = new QLabel("📅 Date de Tri :");             lblDate->setStyleSheet(labelStyle);
    QLabel *lblMat   = new QLabel("📦 Type Matériau :");           lblMat->setStyleSheet(labelStyle);
    QLabel *lblQteE  = new QLabel("📊 Quantité Entrée (kg) :");    lblQteE->setStyleSheet(labelStyle);
    QLabel *lblQteR  = new QLabel("✅ Quantité Recyclée (kg) :");  lblQteR->setStyleSheet(labelStyle);
    QLabel *lblQteJ  = new QLabel("❌ Quantité Rejetée (kg) :");   lblQteJ->setStyleSheet(labelStyle);
    QLabel *lblDest  = new QLabel("📍 Destination :");             lblDest->setStyleSheet(labelStyle);
    QLabel *lblVal   = new QLabel("💰 Valeur (TND) :");            lblVal->setStyleSheet(labelStyle);
    QLabel *lblDir   = new QLabel("🏭 Direction :");               lblDir->setStyleSheet(labelStyle);
    QLabel *lblStat  = new QLabel("📊 Statut :");                  lblStat->setStyleSheet(labelStyle);

    gridLayout->addWidget(lblDate,  0, 0); gridLayout->addWidget(dateTri,     0, 1);
    gridLayout->addWidget(lblMat,   1, 0); gridLayout->addWidget(typeMateriau,1, 1);
    gridLayout->addWidget(lblQteE,  2, 0); gridLayout->addWidget(qteEntree,   2, 1);
    gridLayout->addWidget(lblQteR,  3, 0); gridLayout->addWidget(qteRecyclee, 3, 1);
    gridLayout->addWidget(lblQteJ,  4, 0); gridLayout->addWidget(qteRejetee,  4, 1);
    gridLayout->addWidget(lblDest,  0, 2); gridLayout->addWidget(destination, 0, 3);
    gridLayout->addWidget(lblVal,   1, 2); gridLayout->addWidget(valeur,      1, 3);
    gridLayout->addWidget(lblDir,   2, 2); gridLayout->addWidget(direction,   2, 3);
    gridLayout->addWidget(lblStat,  3, 2); gridLayout->addWidget(statut,      3, 3);

    containerLayout->addWidget(contentWidget);
    containerLayout->addSpacing(15);

    QHBoxLayout *btnLayout = new QHBoxLayout();
    btnLayout->setSpacing(15);

    QPushButton *annuler = new QPushButton("✗ Annuler");
    annuler->setMinimumHeight(50);
    annuler->setStyleSheet(
        "QPushButton { background-color:#E5E7EB; color:#374151; font-size:15px;"
        "font-weight:600; border:none; border-radius:8px; padding:12px 30px; }"
        "QPushButton:hover { background-color:#D1D5DB; }"
        );

    QPushButton *enregistrer = new QPushButton("✓ Enregistrer");
    enregistrer->setMinimumHeight(50);
    enregistrer->setStyleSheet(
        "QPushButton { background:qlineargradient(x1:0,y1:0,x2:0,y2:1,"
        "stop:0 #1A7A4A, stop:1 #0F4D2E); color:white; font-size:15px;"
        "font-weight:600; border:none; border-radius:8px; padding:12px 30px; }"
        "QPushButton:hover { background:qlineargradient(x1:0,y1:0,x2:0,y2:1,"
        "stop:0 #22A05A, stop:1 #1A7A4A); }"
        );

    btnLayout->addWidget(annuler);
    btnLayout->addWidget(enregistrer);
    containerLayout->addLayout(btnLayout);
    mainLayout->addWidget(container);

    connect(annuler, &QPushButton::clicked, dialog, &QDialog::reject);

    Recyclage r = Recyclage::getById(idRecyclage);
    if (r.getId() == 0) {
        showMessage(this, "Erreur", "Recyclage introuvable.", "error");
        delete dialog;
        return;
    }

    QDate dTri = QDate::fromString(r.getDateTri(), "dd/MM/yyyy");
    if (!dTri.isValid()) dTri = QDate::currentDate();
    dateTri->setDate(dTri);
    typeMateriau->setCurrentText(r.getTypeMateriau());
    qteEntree->setValue(r.getQuantiteEntree());
    qteRecyclee->setValue(r.getQuantiteRecyclee());
    qteRejetee->setValue(r.getQuantiteRejetee());
    destination->setText(r.getDestination());
    valeur->setValue(r.getValeurMonetaire());
    direction->setText(r.getDirection());
    statut->setCurrentText(r.getStatut());

    connect(enregistrer, &QPushButton::clicked, this, [=]() {
        if (destination->text().trimmed().isEmpty() || direction->text().trimmed().isEmpty()) {
            showMessage(dialog, "Erreur", "Tous les champs sont obligatoires !", "error");
            return;
        }
        if (qteEntree->value() <= 0.0) {
            showMessage(dialog, "Erreur", "La quantité entrée doit être supérieure à 0 !", "error");
            return;
        }
        if (qteRecyclee->value() > qteEntree->value()) {
            showMessage(dialog, "Erreur", "La quantité recyclée ne peut pas dépasser la quantité entrée !", "error");
            return;
        }
        if (qteRejetee->value() > qteEntree->value()) {
            showMessage(dialog, "Erreur", "La quantité rejetée ne peut pas dépasser la quantité entrée !", "error");
            return;
        }

        Recyclage rModif(idRecyclage,
                         dateTri->date().toString("dd/MM/yyyy"),
                         typeMateriau->currentText(),
                         qteEntree->value(),
                         qteRecyclee->value(),
                         qteRejetee->value(),
                         destination->text().trimmed(),
                         valeur->value(),
                         direction->text().trimmed(),
                         statut->currentText());

        if (rModif.modifier()) {
            showMessage(dialog, "Succès", "✅ Recyclage modifié avec succès !", "success");
            dialog->accept();
            afficherRecyclages();
        } else {
            showMessage(dialog, "Erreur", "Impossible de modifier ce recyclage.", "error");
        }
    });

    dialog->exec();
}
// ================================================================
// === AFFICHER CONTENEURS ========================================
// ================================================================

void MainWindow::afficherConteneurs()
{
    QStringList headers = {
        "🆔 ID", "📦 Capacité", "🏢 Type Propriété", "📍 Adresse", "🌍 GPS",
        "🗑️ Ménager", "♻️ Recyclable", "🌿 Organique", "🏭 Industriel",
        "⚙️ État", "📅 Dernière Collecte"
    };

    ui->tableWidget_Conteneur->clear();
    ui->tableWidget_Conteneur->setColumnCount(headers.size());
    ui->tableWidget_Conteneur->setHorizontalHeaderLabels(headers);
    ui->tableWidget_Conteneur->setRowCount(0);
    ui->tableWidget_Conteneur->setSortingEnabled(false);

    // 🎨 STYLE MODERNE
    ui->tableWidget_Conteneur->setStyleSheet(R"(
        QTableWidget {
            background-color: #f0f4f8;
            alternate-background-color: #e8edf2;
            border: none;
            gridline-color: transparent;
            font-size: 13px;
            color: #2d3436;
        }
        QTableWidget::item {
            padding: 10px 16px;
            border: none;
            border-bottom: 1px solid #dfe6ed;
        }
        QTableWidget::item:selected {
            background-color: #2C5F7C;
            color: #ffffff;
        }
        QTableWidget::item:hover {
            background-color: #d6e4f0;
            color: #1B3A57;
        }
        QHeaderView::section {
            background: qlineargradient(
                x1:0, y1:0, x2:0, y2:1,
                stop:0 #2C5F7C,
                stop:1 #1B3A57
            );
            color: #ffffff;
            font-weight: bold;
            padding: 12px;
            border: none;
        }
    )");

    ui->tableWidget_Conteneur->setAlternatingRowColors(true);
    ui->tableWidget_Conteneur->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableWidget_Conteneur->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tableWidget_Conteneur->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableWidget_Conteneur->verticalHeader()->setVisible(false);
    ui->tableWidget_Conteneur->setShowGrid(false);

    QList<Conteneur> liste = Conteneur::getAll();

    int row = 0;
    for (const Conteneur &c : liste)
    {
        ui->tableWidget_Conteneur->insertRow(row);

        QStringList vals = {
            QString::number(c.getId()),
            QString::number(c.getCapacite()),
            c.getTypePropriete(),
            c.getAdresseComplete(),
            c.getLocalisationGPS(),
            c.getAccepteMenager(),
            c.getAccepteRecyclable(),
            c.getAccepteOrganique(),
            c.getAccepteIndustriel(),
            c.getEtat(),
            c.getDateDerniereCollecte()
        };

        for (int col = 0; col < 11; col++)
        {
            QString valeur = vals[col];

            if (col == 9) {
                QString s = valeur.toLower();
                if (s == "plein") valeur = "🔴 Plein";
                else if (s == "vide") valeur = "🟢 Vide";
                else if (s == "en maintenance") valeur = "🟡 Maintenance";
                else valeur = "❓ " + valeur;
            }

            QTableWidgetItem *item = new QTableWidgetItem(valeur);

            if (col == 0) {
                ui->tableWidget_Conteneur->setItem(row, col, item);
                ui->tableWidget_Conteneur->setColumnHidden(0, true);
                continue;
            }

            item->setTextAlignment(Qt::AlignVCenter | Qt::AlignLeft);

            if (col == 2) {
                item->setFont(QFont("Segoe UI", 13, QFont::Bold));
                item->setForeground(QColor(27,58,87));
            }

            if (col == 9) {
                QString s = c.getEtat().toLower();
                if (s == "plein") item->setForeground(QColor(192,57,43));
                else if (s == "vide") item->setForeground(QColor(26,122,74));
                else item->setForeground(QColor(230,126,34));
                item->setFont(QFont("Segoe UI", 12, QFont::Bold));
            }

            if (row % 2 == 0) item->setBackground(QColor(255,255,255));
            else               item->setBackground(QColor(240,244,248));

            ui->tableWidget_Conteneur->setItem(row, col, item);
        }

        ui->tableWidget_Conteneur->setRowHeight(row, 44);
        row++;
    }

    // 🔹 FINAL
    ui->tableWidget_Conteneur->horizontalHeader()
        ->setSectionResizeMode(QHeaderView::ResizeToContents);

    ui->tableWidget_Conteneur->horizontalHeader()->setStretchLastSection(true);
    ui->tableWidget_Conteneur->setSortingEnabled(true);
}


// ================================================================
// === AFFICHER RECYCLAGES ========================================
// ================================================================

void MainWindow::afficherRecyclages()
{
    QStringList headers = {
        "🆔 ID", "📅 Date Tri", "♻️ Type Matériau", "📥 Qté Entrée",
        "🔄 Qté Recyclée", "❌ Qté Rejetée", "📍 Destination",
        "💰 Valeur (TND)", "➡️ Direction", "⚙️ Statut"
    };

    ui->tableWidget_Recyclage->clear();
    ui->tableWidget_Recyclage->setColumnCount(headers.size());
    ui->tableWidget_Recyclage->setHorizontalHeaderLabels(headers);
    ui->tableWidget_Recyclage->setRowCount(0);
    ui->tableWidget_Recyclage->setSortingEnabled(false);

    // 🎨 STYLE (copié du client)
    ui->tableWidget_Recyclage->setStyleSheet(R"(
        QTableWidget {
            background-color: #f0f4f8;
            alternate-background-color: #e8edf2;
            border: none;
            gridline-color: transparent;
            font-size: 13px;
            color: #2d3436;
        }
        QTableWidget::item {
            padding: 10px 16px;
            border: none;
            border-bottom: 1px solid #dfe6ed;
        }
        QTableWidget::item:selected {
            background-color: #2C5F7C;
            color: #ffffff;
        }
        QTableWidget::item:hover {
            background-color: #d6e4f0;
            color: #1B3A57;
        }
        QHeaderView::section {
            background: qlineargradient(
                x1:0, y1:0, x2:0, y2:1,
                stop:0 #2C5F7C,
                stop:1 #1B3A57
            );
            color: #ffffff;
            font-weight: bold;
            font-size: 13px;
            padding: 12px 16px;
            border: none;
        }
    )");

    ui->tableWidget_Recyclage->setAlternatingRowColors(true);
    ui->tableWidget_Recyclage->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableWidget_Recyclage->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tableWidget_Recyclage->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableWidget_Recyclage->verticalHeader()->setVisible(false);
    ui->tableWidget_Recyclage->setShowGrid(false);

    QList<Recyclage> liste = Recyclage::getAll();

    int row = 0;
    for (const Recyclage &r : liste)
    {
        ui->tableWidget_Recyclage->insertRow(row);

        QStringList vals = {
            QString::number(r.getId()),
            r.getDateTri(),
            r.getTypeMateriau(),
            QString::number(r.getQuantiteEntree()),
            QString::number(r.getQuantiteRecyclee()),
            QString::number(r.getQuantiteRejetee()),
            r.getDestination(),
            QString::number(r.getValeurMonetaire()),
            r.getDirection(),
            r.getStatut()
        };

        for (int col = 0; col < 10; col++)
        {
            QString valeur = vals[col];

            if (col == 9) {
                QString s = valeur.toLower();
                if      (s == "valide")     valeur = "✅ Valide";
                else if (s == "refuse")     valeur = "❌ Refusé";
                else if (s == "en attente") valeur = "⏳ En attente";
                else valeur = "❓ " + valeur;
            }

            QTableWidgetItem *item = new QTableWidgetItem(valeur);

            if (col == 0) {
                ui->tableWidget_Recyclage->setItem(row, col, item);
                ui->tableWidget_Recyclage->setColumnHidden(0, true);
                continue;
            }

            item->setTextAlignment(Qt::AlignVCenter | Qt::AlignLeft);

            if (col == 2) {
                item->setFont(QFont("Segoe UI", 13, QFont::Bold));
                item->setForeground(QColor(27,58,87));
            }

            if (col == 9) {
                QString s = r.getStatut().toLower();
                if (s == "valide") item->setForeground(QColor(26,122,74));
                else if (s == "refuse") item->setForeground(QColor(192,57,43));
                else item->setForeground(QColor(230,126,34));
                item->setFont(QFont("Segoe UI", 12, QFont::Bold));
            }

            if (row % 2 == 0) item->setBackground(QColor(255,255,255));
            else               item->setBackground(QColor(240,244,248));

            ui->tableWidget_Recyclage->setItem(row, col, item);
        }

        ui->tableWidget_Recyclage->setRowHeight(row, 44);
        row++;
    }

    // 🔹 CONFIG FINALE
    ui->tableWidget_Recyclage->horizontalHeader()
        ->setSectionResizeMode(QHeaderView::ResizeToContents);

    ui->tableWidget_Recyclage->horizontalHeader()->setStretchLastSection(true);
    ui->tableWidget_Recyclage->setSortingEnabled(true);
}
// ================================================================
// === RECYCLAGES=====STAT ========================================
// ================================================================
void MainWindow::on_bouttonstatrecyclage_clicked()
{
    QSqlQuery q;

    // Totaux
    int totalRecyclages = 0;
    if (q.exec("SELECT COUNT(*) FROM RECYCLAGES") && q.next())
        totalRecyclages = q.value(0).toInt();

    double valeurTotale = 0;
    if (q.exec("SELECT SUM(Valeur_monetaire) FROM RECYCLAGES") && q.next())
        valeurTotale = q.value(0).toDouble();

    double quantiteTotale = 0;
    if (q.exec("SELECT SUM(Quantite_recyclee) FROM RECYCLAGES") && q.next())
        quantiteTotale = q.value(0).toDouble();

    double quantiteRejet = 0;
    if (q.exec("SELECT SUM(Quantite_rejetee) FROM RECYCLAGES") && q.next())
        quantiteRejet = q.value(0).toDouble();

    // Statut
    int statutTermine = 0;
    q.prepare("SELECT COUNT(*) FROM RECYCLAGES WHERE UPPER(STATUT)=UPPER(:s)");
    q.bindValue(":s", "Terminé");
    if (q.exec() && q.next()) statutTermine = q.value(0).toInt();

    int statutEnCours = 0;
    q.prepare("SELECT COUNT(*) FROM RECYCLAGES WHERE UPPER(STATUT)=UPPER(:s)");
    q.bindValue(":s", "En cours");
    if (q.exec() && q.next()) statutEnCours = q.value(0).toInt();

    int statutAnnule = 0;
    q.prepare("SELECT COUNT(*) FROM RECYCLAGES WHERE UPPER(STATUT)=UPPER(:s)");
    q.bindValue(":s", "Annulé");
    if (q.exec() && q.next()) statutAnnule = q.value(0).toInt();

    // ── Création du dialogue
    QDialog *dlg = new QDialog(this);
    dlg->setWindowTitle("📊 Statistiques des Recyclages");
    dlg->setFixedSize(780, 680);
    dlg->setStyleSheet("QDialog { background-color: #F0F4F8; }");

    QVBoxLayout *mainLay = new QVBoxLayout(dlg);
    mainLay->setContentsMargins(20, 20, 20, 20);
    mainLay->setSpacing(16);

    QLabel *title = new QLabel("📊 Tableau de Bord — Statistiques Recyclages");
    title->setAlignment(Qt::AlignCenter);
    title->setStyleSheet(
        "font-size:18px; font-weight:bold; color:white; padding:16px;"
        "background:qlineargradient(x1:0,y1:0,x2:1,y2:0,stop:0 #1B3A57,stop:1 #2C5F7C);"
        "border-radius:12px;"
        );
    mainLay->addWidget(title);

    // ── KPI cards
    QHBoxLayout *kpiRow = new QHBoxLayout();
    kpiRow->setSpacing(12);

    auto makeKPI = [](const QString &icon, const QString &value, const QString &label, const QString &color) {
        QFrame *card = new QFrame();
        card->setFixedHeight(90);
        card->setStyleSheet(QString("QFrame { background-color:%1; border-radius:12px; }").arg(color));
        QVBoxLayout *cl = new QVBoxLayout(card);
        cl->setContentsMargins(14, 10, 14, 10);
        cl->setSpacing(2);
        QLabel *ico = new QLabel(icon + "  " + value);
        ico->setStyleSheet("font-size:22px; font-weight:bold; color:white;");
        QLabel *lbl = new QLabel(label);
        lbl->setStyleSheet("font-size:11px; color:rgba(255,255,255,0.85);");
        cl->addWidget(ico);
        cl->addWidget(lbl);
        return card;
    };

    kpiRow->addWidget(makeKPI("♻️", QString::number(totalRecyclages), "Total Recyclages", "#2C5F7C"));
    kpiRow->addWidget(makeKPI("💰", QString::number(valeurTotale, 'f', 2), "Valeur totale", "#27AE60"));
    kpiRow->addWidget(makeKPI("✅", QString::number(statutTermine), "Terminés", "#10B981"));
    kpiRow->addWidget(makeKPI("⏳", QString::number(statutEnCours), "En cours", "#E67E22"));
    kpiRow->addWidget(makeKPI("❌", QString::number(statutAnnule), "Annulés", "#E74C3C"));
    mainLay->addLayout(kpiRow);

    // Close button
    QPushButton *closeBtn = new QPushButton("✕  Fermer");
    closeBtn->setFixedHeight(42);
    closeBtn->setStyleSheet(
        "QPushButton { background:#2C5F7C; color:white; font-size:14px; font-weight:600;"
        "border:none; border-radius:8px; }"
        "QPushButton:hover { background:#1B3A57; }"
        );
    connect(closeBtn, &QPushButton::clicked, dlg, &QDialog::accept);
    mainLay->addWidget(closeBtn);

    dlg->exec();
}


void MainWindow::afficherCollectes()
{
    // ── En-têtes colonnes
    QStringList headers = {
        "🆔 ID", "📅 Date Collecte", "🗑️ Type Déchet",
        "📊 Qté Collectée (kg)", "⚙️ Statut",
        "📏 Distance (km)", "📝 Observations"
    };

    // ── Initialisation tableau
    ui->tableWidget_collecte->clear();
    ui->tableWidget_collecte->setColumnCount(headers.size());
    ui->tableWidget_collecte->setHorizontalHeaderLabels(headers);
    ui->tableWidget_collecte->setRowCount(0);
    ui->tableWidget_collecte->setSortingEnabled(false);

    // ── Style Dashboard Bleu
    ui->tableWidget_collecte->setStyleSheet(R"(
        QTableWidget {
            background-color: #f0f4f8;
            alternate-background-color: #e8edf2;
            border: none;
            gridline-color: transparent;
            font-size: 13px;
            color: #2d3436;
        }
        QTableWidget::item {
            padding: 10px 16px;
            border: none;
            border-bottom: 1px solid #dfe6ed;
        }
        QTableWidget::item:selected {
            background-color: #2C5F7C;
            color: #ffffff;
        }
        QTableWidget::item:hover {
            background-color: #d6e4f0;
            color: #1B3A57;
        }
        QHeaderView::section {
            background: qlineargradient(
                x1:0,y1:0,x2:0,y2:1,
                stop:0 #2C5F7C,
                stop:1 #1B3A57
            );
            color: #ffffff;
            font-weight: bold;
            font-size: 13px;
            padding: 12px 16px;
            border: none;
            border-right: 1px solid #3A6EA5;
        }
        QScrollBar:vertical {
            background: #e8edf2;
            width: 7px;
            border-radius: 4px;
        }
        QScrollBar::handle:vertical {
            background: #2C5F7C;
            border-radius: 4px;
            min-height: 30px;
        }
        QScrollBar:horizontal {
            background: #e8edf2;
            height: 7px;
            border-radius: 4px;
        }
        QScrollBar::handle:horizontal {
            background: #2C5F7C;
            border-radius: 4px;
        }
        QScrollBar::add-line, QScrollBar::sub-line { background: none; }
    )");

    ui->tableWidget_collecte->setAlternatingRowColors(true);
    ui->tableWidget_collecte->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableWidget_collecte->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tableWidget_collecte->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableWidget_collecte->verticalHeader()->setVisible(false);
    ui->tableWidget_collecte->setShowGrid(false);

    // ── Récupération via la classe Collecte (PAS de SQL ici)
    QList<Collecte> liste = Collecte::getAll();

    // ── Remplissage du tableau
    int row = 0;
    for (const Collecte &col : liste)
    {
        ui->tableWidget_collecte->insertRow(row);

        QStringList vals = {
            QString::number(col.getId()),
            col.getDateCollecte(),
            col.getTypeDechet(),
            QString::number(col.getQuantiteCollectee()),
            col.getStatut(),
            QString::number(col.getDistanceTotale()),
            col.getObservations()
        };

        for (int c = 0; c < 7; c++)
        {
            QString valeur = vals[c];

            // Badge Statut colonne 4
            if (c == 4) {
                QString s = valeur.toLower();
                if      (s == "terminee") valeur = "✅ Terminée";
                else if (s == "en cours") valeur = "⏳ En cours";
                else if (s == "annulee")  valeur = "❌ Annulée";
                else                      valeur = "❓ " + valeur;
            }

            QTableWidgetItem *item = new QTableWidgetItem(valeur);
            item->setTextAlignment(Qt::AlignVCenter | Qt::AlignLeft);

            // ID caché colonne 0
            if (c == 0) {
                ui->tableWidget_collecte->setItem(row, c, item);
                ui->tableWidget_collecte->setColumnHidden(0, true);
                continue;
            }

            // Style Type Déchet colonne 2
            if (c == 2) {
                item->setForeground(QColor("#1B3A57"));
                item->setFont(QFont("Segoe UI", 12, QFont::Bold));
            }

            // Style Statut colonne 4
            if (c == 4) {
                QString s = col.getStatut().toLower();
                if      (s == "terminee") item->setForeground(QColor("#1A7A4A"));
                else if (s == "en cours") item->setForeground(QColor("#E67E22"));
                else if (s == "annulee")  item->setForeground(QColor("#C0392B"));
                item->setFont(QFont("Segoe UI", 12, QFont::Bold));
            }

            // Lignes alternées
            if (row % 2 == 0) item->setBackground(QColor("#ffffff"));
            else               item->setBackground(QColor("#f0f4f8"));

            ui->tableWidget_collecte->setItem(row, c, item);
        }

        ui->tableWidget_collecte->setRowHeight(row, 44);
        row++;
    }

    // ── Ajustement des colonnes
    ui->tableWidget_collecte->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    ui->tableWidget_collecte->horizontalHeader()->setStretchLastSection(true);
    ui->tableWidget_collecte->horizontalHeader()->setMinimumSectionSize(90);
    ui->tableWidget_collecte->setSortingEnabled(true);
}
// ================================================================
// ===  COLLECTES STAT =========================================
// ================================================================
void MainWindow::on_bouttonstatcollecte_clicked()
{
    QSqlQuery q;

    // ── Totaux et états
    int totalCollectes = 0;
    if (q.exec("SELECT COUNT(*) FROM COLLECTES") && q.next())
        totalCollectes = q.value(0).toInt();

    int statutTerminee = 0;
    q.prepare("SELECT COUNT(*) FROM COLLECTES WHERE UPPER(STATUT)=UPPER(:s)");
    q.bindValue(":s", "Terminée");
    if (q.exec() && q.next()) statutTerminee = q.value(0).toInt();

    int statutEnCours = 0;
    q.prepare("SELECT COUNT(*) FROM COLLECTES WHERE UPPER(STATUT)=UPPER(:s)");
    q.bindValue(":s", "En cours");
    if (q.exec() && q.next()) statutEnCours = q.value(0).toInt();

    int statutAnnulee = 0;
    q.prepare("SELECT COUNT(*) FROM COLLECTES WHERE UPPER(STATUT)=UPPER(:s)");
    q.bindValue(":s", "Annulée");
    if (q.exec() && q.next()) statutAnnulee = q.value(0).toInt();

    double quantiteTotale = 0;
    if (q.exec("SELECT SUM(Quantite_collectee) FROM COLLECTES") && q.next())
        quantiteTotale = q.value(0).toDouble();

    double quantiteMax = 0;
    if (q.exec("SELECT MAX(Quantite_collectee) FROM COLLECTES") && q.next())
        quantiteMax = q.value(0).toDouble();

    double quantiteMin = 0;
    if (q.exec("SELECT MIN(Quantite_collectee) FROM COLLECTES") && q.next())
        quantiteMin = q.value(0).toDouble();

    // ── Création du dialogue
    QDialog *dlg = new QDialog(this);
    dlg->setWindowTitle("📊 Statistiques des Collectes");
    dlg->setFixedSize(780, 680);
    dlg->setStyleSheet("QDialog { background-color: #F0F4F8; }");

    QVBoxLayout *mainLay = new QVBoxLayout(dlg);
    mainLay->setContentsMargins(20, 20, 20, 20);
    mainLay->setSpacing(16);

    // Title
    QLabel *title = new QLabel("📊 Tableau de Bord — Statistiques Collectes");
    title->setAlignment(Qt::AlignCenter);
    title->setStyleSheet(
        "font-size:18px; font-weight:bold; color:white; padding:16px;"
        "background:qlineargradient(x1:0,y1:0,x2:1,y2:0,stop:0 #1B3A57,stop:1 #2C5F7C);"
        "border-radius:12px;"
        );
    mainLay->addWidget(title);

    // ── KPI cards
    QHBoxLayout *kpiRow = new QHBoxLayout();
    kpiRow->setSpacing(12);

    auto makeKPI = [](const QString &icon, const QString &value, const QString &label, const QString &color) {
        QFrame *card = new QFrame();
        card->setFixedHeight(90);
        card->setStyleSheet(QString("QFrame { background-color:%1; border-radius:12px; }").arg(color));
        QVBoxLayout *cl = new QVBoxLayout(card);
        cl->setContentsMargins(14, 10, 14, 10);
        cl->setSpacing(2);
        QLabel *ico = new QLabel(icon + "  " + value);
        ico->setStyleSheet("font-size:22px; font-weight:bold; color:white; background:transparent;");
        QLabel *lbl = new QLabel(label);
        lbl->setStyleSheet("font-size:11px; color:rgba(255,255,255,0.85); background:transparent;");
        cl->addWidget(ico);
        cl->addWidget(lbl);
        return card;
    };

    kpiRow->addWidget(makeKPI("🗑️", QString::number(totalCollectes), "Total Collectes", "#2C5F7C"));
    kpiRow->addWidget(makeKPI("✅", QString::number(statutTerminee), "Terminées", "#27AE60"));
    kpiRow->addWidget(makeKPI("⏳", QString::number(statutEnCours), "En cours", "#E67E22"));
    kpiRow->addWidget(makeKPI("❌", QString::number(statutAnnulee), "Annulées", "#E74C3C"));
    mainLay->addLayout(kpiRow);

    // ── Row: Quantité collectée
    QFrame *quantCard = new QFrame();
    quantCard->setStyleSheet("QFrame { background:white; border-radius:12px; }");
    QHBoxLayout *quantLay = new QHBoxLayout(quantCard);
    quantLay->setContentsMargins(20, 14, 20, 14);

    auto makeStat = [](const QString &lbl, const QString &val) {
        QVBoxLayout *vl = new QVBoxLayout();
        QLabel *v = new QLabel(val);
        v->setAlignment(Qt::AlignCenter);
        v->setStyleSheet("font-size:20px; font-weight:bold; color:#2C5F7C;");
        QLabel *l = new QLabel(lbl);
        l->setAlignment(Qt::AlignCenter);
        l->setStyleSheet("font-size:11px; color:#6B7280;");
        vl->addWidget(v);
        vl->addWidget(l);
        return vl;
    };

    quantLay->addLayout(makeStat("Total (kg)", QString::number(quantiteTotale, 'f', 2)));
    quantLay->addSpacing(30);
    quantLay->addLayout(makeStat("Maximum (kg)", QString::number(quantiteMax, 'f', 2)));
    quantLay->addSpacing(30);
    quantLay->addLayout(makeStat("Minimum (kg)", QString::number(quantiteMin, 'f', 2)));
    mainLay->addWidget(quantCard);

    // Close button
    QPushButton *closeBtn = new QPushButton("✕  Fermer");
    closeBtn->setFixedHeight(42);
    closeBtn->setStyleSheet(
        "QPushButton { background:#2C5F7C; color:white; font-size:14px; font-weight:600;"
        "border:none; border-radius:8px; }"
        "QPushButton:hover { background:#1B3A57; }"
        );
    connect(closeBtn, &QPushButton::clicked, dlg, &QDialog::accept);
    mainLay->addWidget(closeBtn);

    dlg->exec();
}



// ================================================================
// === MODULE CONTENEUR — STAT ====================================
// ================================================================
void MainWindow::on_bouttonstatconteneur_clicked()
{
    // ── Fetch stats from DB ──────────────────────────────
    QSqlQuery q;

    // Total conteneurs
    int totalConteneurs = 0;
    if (q.exec("SELECT COUNT(*) FROM CONTENEURS") && q.next())
        totalConteneurs = q.value(0).toInt();

    // État des conteneurs
    auto countEtat = [&](const QString &etat) -> int {
        q.prepare("SELECT COUNT(*) FROM CONTENEURS WHERE UPPER(ETAT)=UPPER(:e)");
        q.bindValue(":e", etat);
        if (q.exec() && q.next()) return q.value(0).toInt();
        return 0;
    };

    int operationnels = countEtat("Opérationnel");
    int enMaintenance = countEtat("En maintenance");
    int horsService = countEtat("Hors service");

    // Capacités
    double capaciteMoyenne = 0, capaciteMax = 0, capaciteMin = 0;
    if (q.exec("SELECT AVG(CAPACITE), MAX(CAPACITE), MIN(CAPACITE) FROM CONTENEURS") && q.next()) {
        capaciteMoyenne = q.value(0).toDouble();
        capaciteMax = q.value(1).toDouble();
        capaciteMin = q.value(2).toDouble();
    }

    // Déchets acceptés
    auto countOui = [&](const QString &col) -> int {
        if (q.exec(QString("SELECT COUNT(*) FROM CONTENEURS WHERE UPPER(%1)='OUI'").arg(col)) && q.next())
            return q.value(0).toInt();
        return 0;
    };
    int accepteMenager = countOui("ACCEPTE_MENAGER");
    int accepteRecyclable = countOui("ACCEPTE_RECYCLABLE");
    int accepteOrganique = countOui("ACCEPTE_ORGANIQUE");
    int accepteIndustriel = countOui("ACCEPTE_INDUSTRIEL");

    // Type de propriété
    auto countType = [&](const QString &type) -> int {
        q.prepare("SELECT COUNT(*) FROM CONTENEURS WHERE UPPER(TYPE_PROPRIETE)=UPPER(:t)");
        q.bindValue(":t", type);
        if (q.exec() && q.next()) return q.value(0).toInt();
        return 0;
    };
    int publicCount = countType("Public");
    int priveCount = countType("Privé");
    int mixteCount = countType("Mixte");

    // ── Build dialog ─────────────────────────────────────
    QDialog *dlg = new QDialog(this);
    dlg->setWindowTitle("📊 Statistiques des Conteneurs");
    dlg->setFixedSize(780, 680);
    dlg->setStyleSheet("QDialog { background-color: #F0F4F8; }");

    QVBoxLayout *mainLay = new QVBoxLayout(dlg);
    mainLay->setContentsMargins(20, 20, 20, 20);
    mainLay->setSpacing(16);

    // Title
    QLabel *title = new QLabel("📊 Tableau de Bord — Statistiques Conteneurs");
    title->setAlignment(Qt::AlignCenter);
    title->setStyleSheet(
        "font-size:18px; font-weight:bold; color:white; padding:16px;"
        "background:qlineargradient(x1:0,y1:0,x2:1,y2:0,stop:0 #1B3A57,stop:1 #2C5F7C);"
        "border-radius:12px;"
        );
    mainLay->addWidget(title);

    // ── Row 1: KPI cards ──────────────────────────────────
    QHBoxLayout *kpiRow = new QHBoxLayout();
    kpiRow->setSpacing(12);

    auto makeKPI = [](const QString &icon, const QString &value, const QString &label, const QString &color) {
        QFrame *card = new QFrame();
        card->setFixedHeight(90);
        card->setStyleSheet(QString("QFrame { background-color:%1; border-radius:12px; }").arg(color));
        QVBoxLayout *cl = new QVBoxLayout(card);
        cl->setContentsMargins(14, 10, 14, 10);
        cl->setSpacing(2);
        QLabel *ico = new QLabel(icon + "  " + value);
        ico->setStyleSheet("font-size:22px; font-weight:bold; color:white; background:transparent;");
        QLabel *lbl = new QLabel(label);
        lbl->setStyleSheet("font-size:11px; color:rgba(255,255,255,0.85); background:transparent;");
        cl->addWidget(ico);
        cl->addWidget(lbl);
        return card;
    };

    kpiRow->addWidget(makeKPI("🗑️", QString::number(totalConteneurs), "Total conteneurs", "#2C5F7C"));
    kpiRow->addWidget(makeKPI("✅", QString::number(operationnels),  "Opérationnels",     "#27AE60"));
    kpiRow->addWidget(makeKPI("🔧", QString::number(enMaintenance), "En maintenance",    "#E67E22"));
    kpiRow->addWidget(makeKPI("❌", QString::number(horsService),   "Hors service",      "#E74C3C"));
    mainLay->addLayout(kpiRow);

    // ── Row 2: Capacités ─────────────────────────────
    QFrame *capCard = new QFrame();
    capCard->setStyleSheet("QFrame { background:white; border-radius:12px; }");
    QHBoxLayout *capLay = new QHBoxLayout(capCard);
    capLay->setContentsMargins(20, 14, 20, 14);

    auto makeCapStat = [](const QString &lbl, const QString &val) {
        QVBoxLayout *vl = new QVBoxLayout();
        QLabel *v = new QLabel(val);
        v->setAlignment(Qt::AlignCenter);
        v->setStyleSheet("font-size:20px; font-weight:bold; color:#2C5F7C;");
        QLabel *l = new QLabel(lbl);
        l->setAlignment(Qt::AlignCenter);
        l->setStyleSheet("font-size:11px; color:#6B7280;");
        vl->addWidget(v);
        vl->addWidget(l);
        return vl;
    };

    capLay->addLayout(makeCapStat("Moyenne", QString::number(capaciteMoyenne, 'f', 0) + " L"));
    capLay->addSpacing(30);
    capLay->addLayout(makeCapStat("Maximum", QString::number(capaciteMax, 'f', 0) + " L"));
    capLay->addSpacing(30);
    capLay->addLayout(makeCapStat("Minimum", QString::number(capaciteMin, 'f', 0) + " L"));
    mainLay->addWidget(capCard);

    // ── Row 3: Déchets acceptés ─────────────────────
    QFrame *dechetCard = new QFrame();
    dechetCard->setStyleSheet("QFrame { background:white; border-radius:12px; }");
    QVBoxLayout *dechetLay = new QVBoxLayout(dechetCard);
    dechetLay->setContentsMargins(20, 14, 20, 14);
    dechetLay->setSpacing(10);

    QLabel *dechetTitle = new QLabel("♻️ Types de Déchets Acceptés");
    dechetTitle->setStyleSheet("font-size:13px; font-weight:bold; color:#374151;");
    dechetLay->addWidget(dechetTitle);

    struct DechetStat { QString name; int count; QString color; };
    QList<DechetStat> dechets = {
                                 {"Ménager",    accepteMenager,    "#3B82F6"},
                                 {"Recyclable", accepteRecyclable, "#10B981"},
                                 {"Organique",  accepteOrganique,  "#F59E0B"},
                                 {"Industriel", accepteIndustriel, "#EF4444"},
                                 };

    for (auto &d : dechets)
    {
        QHBoxLayout *row = new QHBoxLayout();
        QLabel *nameLbl = new QLabel(d.name);
        nameLbl->setFixedWidth(90);
        nameLbl->setStyleSheet("font-size:12px; color:#374151;");

        QProgressBar *bar = new QProgressBar();
        bar->setRange(0, totalConteneurs > 0 ? totalConteneurs : 1);
        bar->setValue(d.count);
        bar->setTextVisible(false);
        bar->setFixedHeight(16);
        bar->setStyleSheet(QString(
                               "QProgressBar { background:#E5E7EB; border-radius:8px; }"
                               "QProgressBar::chunk { background:%1; border-radius:8px; }"
                               ).arg(d.color));

        QLabel *numLbl = new QLabel(QString::number(d.count) + " / " + QString::number(totalConteneurs));
        numLbl->setFixedWidth(70);
        numLbl->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
        numLbl->setStyleSheet("font-size:11px; color:#6B7280;");

        row->addWidget(nameLbl);
        row->addWidget(bar);
        row->addWidget(numLbl);
        dechetLay->addLayout(row);
    }
    mainLay->addWidget(dechetCard);

    // ── Row 4: Type de propriété ─────────────────────
    QFrame *propCard = new QFrame();
    propCard->setStyleSheet("QFrame { background:white; border-radius:12px; }");
    QVBoxLayout *propLay = new QVBoxLayout(propCard);
    propLay->setContentsMargins(20, 14, 20, 14);
    propLay->setSpacing(10);

    QLabel *propTitle = new QLabel("🏢 Répartition par Type de Propriété");
    propTitle->setStyleSheet("font-size:13px; font-weight:bold; color:#374151;");
    propLay->addWidget(propTitle);

    struct PropStat { QString name; int count; QString color; };
    QList<PropStat> props = {
                             {"Public", publicCount, "#6366F1"},
                             {"Privé",  priveCount,  "#EC4899"},
                             {"Mixte",  mixteCount,  "#14B8A6"},
                             };

    QHBoxLayout *propRow = new QHBoxLayout();
    propRow->setSpacing(16);
    for (auto &p : props)
    {
        QFrame *pCard = new QFrame();
        pCard->setStyleSheet(QString("QFrame { background:%1; border-radius:10px; }").arg(p.color));
        pCard->setFixedHeight(64);
        QVBoxLayout *pcl = new QVBoxLayout(pCard);
        pcl->setContentsMargins(12, 8, 12, 8);
        QLabel *pv = new QLabel(QString::number(p.count));
        pv->setAlignment(Qt::AlignCenter);
        pv->setStyleSheet("font-size:20px; font-weight:bold; color:white;");
        QLabel *pl = new QLabel(p.name);
        pl->setAlignment(Qt::AlignCenter);
        pl->setStyleSheet("font-size:11px; color:rgba(255,255,255,0.85);");
        pcl->addWidget(pv);
        pcl->addWidget(pl);
        propRow->addWidget(pCard);
    }
    propLay->addLayout(propRow);
    mainLay->addWidget(propCard);

    // Close button
    QPushButton *closeBtn = new QPushButton("✕  Fermer");
    closeBtn->setFixedHeight(42);
    closeBtn->setStyleSheet(
        "QPushButton { background:#2C5F7C; color:white; font-size:14px; font-weight:600;"
        "border:none; border-radius:8px; }"
        "QPushButton:hover { background:#1B3A57; }"
        );
    connect(closeBtn, &QPushButton::clicked, dlg, &QDialog::accept);
    mainLay->addWidget(closeBtn);

    dlg->exec();
}



// ================================================================
// === MODULE RECYCLAGE — STAT =============================
// ================================================================



Recyclage MainWindow::getRecyclageSelectionne()
{
    int row = ui->tableWidget_Recyclage->currentRow();
    if (row < 0) return Recyclage();
    return Recyclage::getById(
        ui->tableWidget_Recyclage->item(row, 0)->text().toInt()
        );
}

Collecte MainWindow::getCollecteSelectionnee()
{
    int row = ui->tableWidget_collecte->currentRow();
    if (row < 0) return Collecte();
    return Collecte::getById(
        ui->tableWidget_collecte->item(row, 0)->text().toInt()
        );
}

Conteneur MainWindow::getConteneurSelectionne()
{
    int row = ui->tableWidget_Conteneur->currentRow();
    if (row < 0) return Conteneur();
    return Conteneur::getById(
        ui->tableWidget_Conteneur->item(row, 0)->text().toInt()
        );
}
Client MainWindow::getClientSelectionne()
{
    int row = ui->tableWidget_client->currentRow();
    if (row < 0) return Client();
    return Client::getById(
        ui->tableWidget_client->item(row, 0)->text().toInt()
        );
}

Employe MainWindow::getEmployeSelectionne()
{
    int row = ui->tableWidget_4->currentRow();
    if (row < 0) return Employe();

    Employe e;
    e.setCin(ui->tableWidget_4->item(row, 0)->text());
    e.setNom(ui->tableWidget_4->item(row, 1)->text());
    e.setPrenom(ui->tableWidget_4->item(row, 2)->text());
    e.setEmail(ui->tableWidget_4->item(row, 3)->text());
    e.setPoste(ui->tableWidget_4->item(row, 4)->text());
    e.setTelephone(ui->tableWidget_4->item(row, 5)->text());
    e.setDateEmbauche(ui->tableWidget_4->item(row, 6)->text());
    e.setSalaire(ui->tableWidget_4->item(row, 7)->text().toDouble());
    e.setService(ui->tableWidget_4->item(row, 8)->text());
    return e;
}
