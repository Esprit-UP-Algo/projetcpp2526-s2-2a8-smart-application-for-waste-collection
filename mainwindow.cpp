#include "mainwindow.h"
#include "qjsonarray.h"
#include "ui_mainwindow.h"
#include "employe.h"
#include "client.h"
#include "recyclage.h"
#include "collecte.h"
#include "conteneur.h"
#include "smsclient.h"
#include "login.h"
#include <QPrinter>
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
#include <QDoubleSpinBox>
#include <QScrollArea>
#include <QCheckBox>
#include <QMessageBox>
#include <QAbstractItemView>
#include <QDate>
#include <QSqlQuery>
#include <QSqlError>
#include <QHeaderView>
#include <QInputDialog>
#include <QRegularExpression>
#include <QTextDocument>
#include <QFileDialog>
#include <QMenu>
#include <QAction>
#include <QFont>
#include <QMouseEvent>
#include <QEvent>
#include <QKeyEvent>
#include <QTimer>
#include "recyclageqr.h"
#include "classificationdechet.h"   // ← ajouter cette ligne
#include "predictionremplissage.h"

// ================================================================
// === CONSTRUCTEUR & DESTRUCTEUR =================================
// ================================================================

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    // =========================
    // INIT AI
    // =========================
    qApp->installEventFilter(this);
    ui->assistant->installEventFilter(this);
    ai.setApiKey("");//api groq ma tpushish ou howa mawjoud git bich yblokik
    ai.setModel("llama-3.1-8b-instant");
    connect(ui->assistant, &QLineEdit::returnPressed,
            this, &MainWindow::handleAssistantInput);



    // ── Mode password + bouton œil ───────────────────────────────
    ui->mdp->setEchoMode(QLineEdit::Password);

    QPushButton *btnOeil = new QPushButton("👁", ui->mdp);
    btnOeil->setFixedSize(30, 30);
    btnOeil->setCursor(Qt::PointingHandCursor);
    btnOeil->setStyleSheet(
        "QPushButton { background:transparent; border:none; font-size:16px; }"
        "QPushButton:hover { color:#2C5F7C; }"
        );

    QTimer::singleShot(0, this, [=]() {
        btnOeil->move(ui->mdp->width() - 35, (ui->mdp->height() - 30) / 2);
    });

    connect(btnOeil, &QPushButton::clicked, this, [=]() {
        if (ui->mdp->echoMode() == QLineEdit::Password) {
            ui->mdp->setEchoMode(QLineEdit::Normal);
            btnOeil->setText("🙈");
        } else {
            ui->mdp->setEchoMode(QLineEdit::Password);
            btnOeil->setText("👁");
        }
    });

    // ── SMS Client ───────────────────────────────────────────────
    sms = new SmsClientMetier(this);
    connect(sms, &SmsClientMetier::smsEnvoye, this,
            [&](bool success, QString response){
                if(success)
                    QMessageBox::information(this, "SMS", "Envoyé !");
                else
                    QMessageBox::warning(this, "SMS", response);
            });



    //classification dechet
    connect(ui->btnClassifier, &QPushButton::clicked,
            this, &MainWindow::on_btnClassifier_clicked);

    // ── Animation lumineuse ──────────────────────────────────────
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

    // ── Configuration tableau Recyclage ──────────────────────────
    ui->tableWidget_Recyclage->setColumnCount(9);
    if (ui->tableWidget_Recyclage->columnCount() > 0)
        ui->tableWidget_Recyclage->setColumnHidden(0, true);
    ui->tableWidget_Recyclage->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableWidget_Recyclage->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableWidget_Recyclage->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tableWidget_Recyclage->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableWidget_Recyclage->verticalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);

    // ── Configuration tableau Client ─────────────────────────────
    ui->tableWidget_client->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableWidget_client->setSelectionMode(QAbstractItemView::SingleSelection);

    // ── Chargement initial ───────────────────────────────────────
    afficherListeClients();
    afficherEmployes();
    afficherCollectes();
    afficherConteneurs();
    afficherRecyclages();

    ui->stackedWidget->setCurrentIndex(1);
}

MainWindow::~MainWindow()
{
    delete ui;
}

// ================================================================
// === UTILITAIRE — BOÎTE DE MESSAGE PERSONNALISÉE ================
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

    QString couleur = "#2C5F7C", icone = "ℹ️";
    if (type == "success") { couleur = "#1A7A4A"; icone = "✅"; }
    if (type == "warning") { couleur = "#E67E22"; icone = "⚠️"; }
    if (type == "error")   { couleur = "#C0392B"; icone = "❌"; }

    QWidget *header = new QWidget();
    header->setFixedHeight(62);
    header->setStyleSheet(QString(
                              "QWidget { background-color:%1;"
                              "border-top-left-radius:14px; border-top-right-radius:14px; }"
                              ).arg(couleur));
    QHBoxLayout *hLay = new QHBoxLayout(header);
    hLay->setContentsMargins(22, 0, 22, 0);
    QLabel *lblIco = new QLabel(icone + "  " + titre);
    lblIco->setStyleSheet("font-size:15px; font-weight:bold; color:white; background:transparent;");
    hLay->addWidget(lblIco);
    layout->addWidget(header);

    QLabel *lblMsg = new QLabel(message);
    lblMsg->setAlignment(Qt::AlignCenter);
    lblMsg->setWordWrap(true);
    lblMsg->setStyleSheet(
        "QLabel { font-size:13px; color:#C8C8D8; background:transparent;"
        "padding:18px 28px 10px 28px; }");
    layout->addWidget(lblMsg);
    layout->addStretch();

    QPushButton *ok = new QPushButton("OK");
    ok->setFixedSize(110, 40);
    ok->setStyleSheet(QString(
                          "QPushButton { background-color:%1; color:white; font-size:14px;"
                          "font-weight:600; border:none; border-radius:8px; }"
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
// === NAVIGATION GÉNÉRALE ========================================
// ================================================================

void MainWindow::on_mdp_clicked()     { ui->stackedWidget->setCurrentIndex(0); }
void MainWindow::on_retour_clicked()  { ui->stackedWidget->setCurrentIndex(1); }
void MainWindow::on_ACCEUIL_clicked() { ui->stackedWidget_2->setCurrentIndex(11); }

void MainWindow::on_EMPLOYE_clicked()
{
    currentModule = "employe";//-----------hedhi zedtha lel ai assistant ma tna7iwhech
    ui->stackedWidget_2->setCurrentIndex(4);
    afficherEmployes();
}

void MainWindow::on_DECONNECTION_clicked()
{
    m_posteConnecte = "";
    m_nomConnecte   = "";
    m_emailConnecte = "";
    ui->adresse_email->clear();
    ui->mdp->clear();
    ui->stackedWidget->setCurrentIndex(1);
}

void MainWindow::on_CLIENT_clicked()   {
    currentModule = "client";//-----------hedhi zedtha lel ai assistant ma tna7iwhech
    ui->stackedWidget_2->setCurrentIndex(2); }



void MainWindow::on_COLLECTE_clicked() {
    currentModule = "collecte";//-----------hedhi zedtha lel ai assistant ma tna7iwhech
    ui->stackedWidget_2->setCurrentIndex(9); }



void MainWindow::on_frame_20_customContextMenuRequested(const QPoint &pos)
{
    Q_UNUSED(pos);
}

void MainWindow::on_cnx_clicked()
{
    QString email = ui->adresse_email->text().trimmed();
    QString mdp   = ui->mdp->text().trimmed();

    if (email.isEmpty() || mdp.isEmpty()) {
        showMessage(this, "Champs manquants",
                    "Veuillez saisir votre email et mot de passe.", "warning");
        return;
    }

    if (Login::verifierLogin(email, mdp)) {
        m_posteConnecte = Login::getPosteUtilisateur(email);
        m_nomConnecte   = Login::getNomUtilisateur(email);
        m_emailConnecte = email;

        ui->stackedWidget->setCurrentIndex(2);
        ui->stackedWidget_2->setCurrentIndex(11);
        afficherEmployes();
        appliquerRestrictionsPoste();

        showMessage(this, "Bienvenue",
                    "✅ Bienvenue " + m_nomConnecte +
                        "\n💼 Poste : " + m_posteConnecte, "success");
    } else {
        showMessage(this, "Erreur de connexion",
                    "❌ Email ou mot de passe incorrect.", "error");
    }
}

void MainWindow::on_RECYCLAGE_clicked()
{
    currentModule = "recyclage";//-----------hedhi zedtha lel ai assistant ma tna7iwhech
    ui->stackedWidget_2->setCurrentIndex(0);
    afficherRecyclages();
}



// ================================================================
// === MODULE CLIENT — NAVIGATION =================================
// ================================================================

void MainWindow::on_pushButton_37_clicked()
{
    ui->stackedWidget_2->setCurrentIndex(2);
    afficherListeClients();
}

// ================================================================
// === MODULE CLIENT — AFFICHAGE ==================================
// ================================================================

void MainWindow::afficherListeClients()
{
    ui->tableWidget_client->setColumnCount(10);
    QStringList headers;
    headers << "ID" << "Nom" << "Prenom" << "CIN" << "Type"
            << "Zone" << "Telephone" << "Statut" << "Adresse" << "CIN_Employe";
    ui->tableWidget_client->setHorizontalHeaderLabels(headers);
    ui->tableWidget_client->setSortingEnabled(false);
    ui->tableWidget_client->clearContents();
    ui->tableWidget_client->setRowCount(0);

    Client temp;
    QList<Client> liste = temp.afficher();

    int row = 0;
    for (const Client &c : liste) {
        ui->tableWidget_client->insertRow(row);
        ui->tableWidget_client->setItem(row, 0, new QTableWidgetItem(QString::number(c.idClient())));
        ui->tableWidget_client->setItem(row, 1, new QTableWidgetItem(c.nom()));
        ui->tableWidget_client->setItem(row, 2, new QTableWidgetItem(c.prenom()));
        ui->tableWidget_client->setItem(row, 3, new QTableWidgetItem(c.cin()));
        ui->tableWidget_client->setItem(row, 4, new QTableWidgetItem(c.typeClient()));
        ui->tableWidget_client->setItem(row, 5, new QTableWidgetItem(c.zone()));
        ui->tableWidget_client->setItem(row, 6, new QTableWidgetItem(c.telephone()));
        ui->tableWidget_client->setItem(row, 7, new QTableWidgetItem(c.statutCompte()));
        ui->tableWidget_client->setItem(row, 8, new QTableWidgetItem(c.adresseComplete()));
        ui->tableWidget_client->setItem(row, 9, new QTableWidgetItem(c.cinEmploye()));
        ui->tableWidget_client->setColumnHidden(9, true);
        ++row;
    }
    ui->tableWidget_client->setSortingEnabled(true);
}

// ================================================================
// === MODULE CLIENT — CRUD =======================================
// ================================================================

void MainWindow::on_bouttonajouterclient_clicked() { afficherWidgetAjoutClient(); }

void MainWindow::on_bouttonsupprimerclient_clicked()
{
    int row = ui->tableWidget_client->currentRow();
    if (row < 0) {
        showMessage(this, "Attention",
                    "⚠️ Veuillez sélectionner un client avant de supprimer.", "warning");
        return;
    }
    QTableWidgetItem *idItem = ui->tableWidget_client->item(row, 0);
    if (!idItem || idItem->text().trimmed().isEmpty()) {
        showMessage(this, "Erreur", "Impossible de récupérer l'identifiant.", "error");
        return;
    }
    QString nomClient = ui->tableWidget_client->item(row, 1)->text()
                        + " " + ui->tableWidget_client->item(row, 2)->text();

    QDialog *confirm = new QDialog(this);
    confirm->setFixedSize(440, 220);
    confirm->setStyleSheet("QDialog { background-color:#1E1E2E; border-radius:14px; }");
    QVBoxLayout *lay = new QVBoxLayout(confirm);
    lay->setContentsMargins(0, 0, 0, 24); lay->setSpacing(0);

    QWidget *header = new QWidget();
    header->setFixedHeight(62);
    header->setStyleSheet("QWidget { background-color:#E67E22;"
                          "border-top-left-radius:14px; border-top-right-radius:14px; }");
    QHBoxLayout *hLay = new QHBoxLayout(header);
    hLay->setContentsMargins(22, 0, 22, 0);
    QLabel *lblTitre = new QLabel("⚠️  Confirmer la suppression");
    lblTitre->setStyleSheet("font-size:15px; font-weight:bold; color:white; background:transparent;");
    hLay->addWidget(lblTitre);
    lay->addWidget(header);

    QLabel *lblMsg = new QLabel("Voulez-vous vraiment supprimer ?\n👤 " + nomClient
                                + "\n🆔 ID : " + idItem->text());
    lblMsg->setAlignment(Qt::AlignCenter);
    lblMsg->setWordWrap(true);
    lblMsg->setStyleSheet("font-size:13px; color:#C8C8D8; background:transparent; padding:16px 28px 8px 28px;");
    lay->addWidget(lblMsg);
    lay->addStretch();

    QHBoxLayout *btnLay = new QHBoxLayout();
    btnLay->setSpacing(12); btnLay->setContentsMargins(20, 0, 20, 0);
    QPushButton *btnNon = new QPushButton("✗ Annuler"); btnNon->setFixedHeight(40);
    btnNon->setStyleSheet("QPushButton { background:#374151; color:white; font-size:13px; font-weight:600; border:none; border-radius:8px; }");
    QPushButton *btnOui = new QPushButton("🗑️ Oui, supprimer"); btnOui->setFixedHeight(40);
    btnOui->setStyleSheet("QPushButton { background:#C0392B; color:white; font-size:13px; font-weight:600; border:none; border-radius:8px; }");
    btnLay->addWidget(btnNon); btnLay->addWidget(btnOui);
    lay->addLayout(btnLay);

    connect(btnNon, &QPushButton::clicked, confirm, &QDialog::reject);
    connect(btnOui, &QPushButton::clicked, confirm, &QDialog::accept);

    if (confirm->exec() == QDialog::Accepted) {
        Client c;
        c.setIdClient(idItem->text().toInt());
        if (!c.supprimer()) {
            showMessage(this, "Erreur", "Impossible de supprimer ce client.", "error");
            return;
        }
        showMessage(this, "Succès", "✅ Client supprimé avec succès !", "success");
        afficherListeClients();
    }
}
//__________IAClient__________________



//t3ess 3al nazla te3 lbutton escape

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Escape)//lahnee
    {
        if (assistantPopup && assistantPopup->isVisible())
        {
            assistantPopup->hide();
            return;
        }
    }

    QMainWindow::keyPressEvent(event);
}




//kifkif lena
bool MainWindow::eventFilter(QObject *obj, QEvent *event)
{
    if (event->type() == QEvent::KeyPress)
    {
        QKeyEvent *keyEvent = static_cast<QKeyEvent*>(event);

        if (keyEvent->key() == Qt::Key_Escape)
        {
            if (assistantPopup && assistantPopup->isVisible())
            {
                assistantPopup->hide();
                return true;
            }
        }
    }

    return QMainWindow::eventFilter(obj, event);
}

//gestion te3 lpopup hedhi ou tros fct li louta
void MainWindow::addChatMessage(const QString &who, const QString &msg)
{
    QLabel *label = new QLabel(who + ": " + msg);

    label->setWordWrap(true);
    label->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
    assistantLayout->setAlignment(Qt::AlignTop);
    assistantLayout->setSpacing(6);
    assistantLayout->setContentsMargins(8, 8, 8, 8);
    label->setStyleSheet(
        "color: white;"
        "background-color: rgba(255,255,255,30);"
        "border-radius: 8px;"
        "padding: 6px;"
        );

    assistantLayout->addWidget(label);
}


void MainWindow::showAssistantPopup()
{
    if (assistantPopup)
    {
        assistantPopup->show();
        return;
    }

    // =========================
    // CREATE POPUP
    // =========================
    assistantPopup = new QWidget(this);

    assistantPopup->setFixedSize(ui->assistant->width() + 180, 250);

    assistantPopup->setStyleSheet(
        "QWidget {"
        "   background-color: rgba(0, 40, 120, 180);"
        "   border: 2px solid #00ff66;"
        "   border-radius: 12px;"
        "}"
        );

    // Position above chatbox
    QPoint pos = ui->assistant->mapToGlobal(QPoint(0, 0));
    assistantPopup->move(pos.x(), pos.y() - assistantPopup->height() - 10);

    // =========================
    // SCROLL AREA (IMPORTANT)
    // =========================
    QScrollArea *scroll = new QScrollArea(assistantPopup);
    scroll->setWidgetResizable(true);
    scroll->setStyleSheet("border: none;");

    QWidget *container = new QWidget();
    assistantLayout = new QVBoxLayout(container);

    assistantLayout->setAlignment(Qt::AlignTop);
    assistantLayout->setSpacing(6);
    assistantLayout->setContentsMargins(8, 8, 8, 8);

    scroll->setWidget(container);

    QVBoxLayout *mainLayout = new QVBoxLayout(assistantPopup);
    mainLayout->addWidget(scroll);

    assistantPopup->setLayout(mainLayout);

    assistantPopup->show();

    // First message
    addChatMessage("AI", "Hello, I'm your assistant. Ask me about recycling.");
}

void MainWindow::handleAssistantInput()
{
    QString question = ui->assistant->text().trimmed();
    if (question.isEmpty())
        return;

    showAssistantPopup();
    addChatMessage("User", question);

    QJsonObject context;
    context["module"] = currentModule;
    context["source"] = "recycling_app";

    QTableWidget *table = getActiveTable();

    if (!table)
    {
        context["error"] = "No active table found for module";
    }
    else
    {
        QJsonObject selected = getSelectedRowData(table);

        if (!selected.isEmpty())
        {
            context["selected_row"] = selected;
        }
        else
        {
            context["table_preview"] = getTablePreview(table, 5);
        }

        context["table_name"] = table->objectName(); // VERY IMPORTANT
        context["row_count"] = table->rowCount();
        context["col_count"] = table->columnCount();
    }

    QString answer = ai.ask(question, context);

    addChatMessage("AI", answer);
    ui->assistant->clear();
}
//ta9ra les information men kol tableau
QTableWidget* MainWindow::getActiveTable()
{
    if (currentModule == "client")
        return ui->tableWidget_client;
    if (currentModule == "employe")
        return ui->tableWidget_4;
    if (currentModule == "conteneur")
        return ui->tableWidget_Conteneur;
    if (currentModule == "collecte")
        return ui->tableWidget_collecte;
    if (currentModule == "recyclage")
        return ui->tableWidget_Recyclage;

    return nullptr;
}



QJsonObject MainWindow::getSelectedRowData(QTableWidget *table)
{
    QJsonObject rowData;

    if (!table) return rowData;

    int row = table->currentRow();
    if (row < 0) return rowData;

    for (int col = 0; col < table->columnCount(); col++)
    {
        QTableWidgetItem *h = table->horizontalHeaderItem(col);
        QString header = h ? h->text() : QString("col_%1").arg(col);

        QTableWidgetItem *item = table->item(row, col);

        if (item)
            rowData[header] = item->text();
        else
            rowData[header] = "[NULL]";
    }

    return rowData;
}


QJsonArray MainWindow::getTablePreview(QTableWidget *table, int limit)
{
    QJsonArray rows;

    if (!table) return rows;

    int maxRows = qMin(limit, table->rowCount());

    for (int r = 0; r < maxRows; r++)
    {
        QJsonObject row;

        for (int c = 0; c < table->columnCount(); c++)
        {
            QTableWidgetItem *h = table->horizontalHeaderItem(c);
            QString header = h ? h->text() : QString("col_%1").arg(c);

            QTableWidgetItem *item = table->item(r, c);

            row[header] = item ? item->text() : "[NULL]";
        }

        rows.append(row);
    }

    return rows;
}





//________smsclient________
void MainWindow::on_btnsms_clicked()

{
    int row = ui->tableWidget_client->currentRow();

    if (row == -1) {
        QMessageBox::warning(this, "Erreur", "❌ Aucun client sélectionné !");
        return;
    }

    // 🔥 Get ONLY ID from table (safe + clean)
    const int COL_ID = 0;

    QTableWidgetItem *itemId = ui->tableWidget_client->item(row, COL_ID);

    if (!itemId) {
        QMessageBox::warning(this, "Erreur", "❌ ID client introuvable !");
        return;
    }

    int idClient = itemId->text().toInt();

    // FETCH FROM DATABASE
    QSqlQuery query;
    query.prepare("SELECT NOM, TELEPHONE FROM CLIENTS WHERE ID_CLIENT = :id");
    query.bindValue(":id", idClient);

    if (!query.exec() || !query.next()) {
        QMessageBox::critical(this, "Erreur", "❌ Client introuvable en base !");
        return;
    }

    QString nom = query.value(0).toString();
    QString numero = query.value(1).toString();

    QString message = "Bonjour " + nom + ", Nous sommes pret pour faire la collecte.";
    qDebug() << "🟢 SENDING TO SMS METIER:" << numero;

    sms->envoyerSMS(numero, message);
}


// ── RECHERCHE CLIENT ─────────────────────────────────────────────
void MainWindow::on_barrerechercheclient_textChanged(const QString &text)
{
    Client::rechercherDansTable(ui->tableWidget_client, text);
}

// ── TRI CLIENT ───────────────────────────────────────────────────
void MainWindow::on_btntrie_clicked()
{
    QMenu *menu = new QMenu(this);
    menu->setStyleSheet(
        "QMenu{background:#FAF5F0;border:2px solid #2C5F7C;border-radius:6px;padding:8px;}"
        "QMenu::item{padding:8px 25px;color:#291C0E;border-radius:4px;}"
        "QMenu::item:selected{background:#2C5F7C;color:white;}");

    QMenu *alphaMenu = menu->addMenu("🔤 Alphabétique (Nom)");
    QAction *alphaAsc  = alphaMenu->addAction("A → Z");
    QAction *alphaDesc = alphaMenu->addAction("Z → A");

    QMenu *statutMenu = menu->addMenu("⚙️ Statut Compte");
    QAction *actif   = statutMenu->addAction("Actif");
    QAction *inactif = statutMenu->addAction("Inactif");
    QAction *tous    = menu->addAction("🔄 Afficher Tous");

    connect(menu, &QMenu::triggered, this, [=](QAction *action) {
        QString orderBy    = "id_client ASC";
        QString filterType = "";
        QString label      = "Trier";

        if      (action == alphaAsc)  { orderBy = "nom ASC, prenom ASC";  label = "A → Z"; }
        else if (action == alphaDesc) { orderBy = "nom DESC, prenom DESC"; label = "Z → A"; }
        else if (action == actif)     { filterType = "actif";   label = "Statut: Actif"; }
        else if (action == inactif)   { filterType = "inactif"; label = "Statut: Inactif"; }
        else if (action == tous)      { orderBy = "id_client ASC"; label = "Trier"; }

        Client c;
        c.loadClientsIntoTable(ui->tableWidget_client, orderBy, filterType);
        ui->btntrie->setText(label);
    });

    menu->exec(ui->btntrie->mapToGlobal(QPoint(0, ui->btntrie->height())));
}

// ── EXPORT CLIENT ────────────────────────────────────────────────
void MainWindow::on_bouttonexporterclient_clicked()
{
    Client c;
    c.exporterListe(ui->tableWidget_client);
}

// ── STATISTIQUES CLIENT ──────────────────────────────────────────
void MainWindow::on_bouttonstatclient_clicked()
{
    Client c;
    c.afficherStatistiques(this);
}

// ── AJOUT CLIENT ─────────────────────────────────────────────────
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

    QString labelStyle =
        "QLabel { background-color:transparent; padding:5px; font-size:13px; font-weight:600; color:#374151; }";
    QString editStyle =
        "QLineEdit { background-color:#F9FAFB; border:1px solid #D1D5DB; border-radius:8px;"
        "padding:12px 16px; font-size:14px; color:#111827; }"
        "QLineEdit:focus { border:2px solid #2C5F7C; background-color:#FFFFFF; padding:11px 15px; }";
    QString comboStyle =
        "QComboBox { background-color:#F9FAFB; border:1px solid #D1D5DB; border-radius:8px;"
        "padding:12px 16px; font-size:14px; color:#111827; }"
        "QComboBox QAbstractItemView { background-color:white; color:#111827;"
        "selection-background-color:#2C5F7C; selection-color:white; }";

    QLineEdit *nom       = new QLineEdit(); nom->setStyleSheet(editStyle);
    QLineEdit *prenom    = new QLineEdit(); prenom->setStyleSheet(editStyle);
    QLineEdit *telephone = new QLineEdit(); telephone->setStyleSheet(editStyle);
    QLineEdit *cin       = new QLineEdit(); cin->setStyleSheet(editStyle);
    QLineEdit *zone      = new QLineEdit(); zone->setStyleSheet(editStyle);
    QLineEdit *adresse   = new QLineEdit(); adresse->setStyleSheet(editStyle);

    QComboBox *type = new QComboBox();
    type->setStyleSheet(comboStyle);
    type->addItems({"particulier", "entreprise", "autre"});

    QRegularExpression rxLetters("^[A-Za-zÀ-ÿ\\s'-]+$");
    QRegularExpression rxNumbers("^\\d+$");
    nom->setValidator(new QRegularExpressionValidator(rxLetters, nom));
    prenom->setValidator(new QRegularExpressionValidator(rxLetters, prenom));
    telephone->setValidator(new QRegularExpressionValidator(rxNumbers, telephone));
    cin->setValidator(new QRegularExpressionValidator(rxNumbers, cin));
    telephone->setMaxLength(8);
    cin->setMaxLength(8);

    auto addLabel = [&](const QString &text) {
        QLabel *l = new QLabel(text); l->setStyleSheet(labelStyle); return l;
    };

    gridLayout->addWidget(addLabel("👤 Nom:"),       0, 0); gridLayout->addWidget(nom,       0, 1);
    gridLayout->addWidget(addLabel("🆔 CIN:"),       0, 2); gridLayout->addWidget(cin,       0, 3);
    gridLayout->addWidget(addLabel("👤 Prenom:"),    1, 0); gridLayout->addWidget(prenom,    1, 1);
    gridLayout->addWidget(addLabel("📍 Zone:"),      1, 2); gridLayout->addWidget(zone,      1, 3);
    gridLayout->addWidget(addLabel("📞 Téléphone:"), 2, 0); gridLayout->addWidget(telephone, 2, 1);
    gridLayout->addWidget(addLabel("🏢 Type:"),      2, 2); gridLayout->addWidget(type,      2, 3);
    gridLayout->addWidget(addLabel("🏠 Adresse:"),   3, 0); gridLayout->addWidget(adresse,   3, 1, 1, 3);

    QComboBox *employe = new QComboBox();
    employe->setStyleSheet(comboStyle);
    Employe emp;
    for (auto &pair : emp.getListeCinNom())
        employe->addItem(pair.second + " (" + pair.first + ")", pair.first);
    gridLayout->addWidget(addLabel("👷 Employé:"), 4, 0);
    gridLayout->addWidget(employe, 4, 1, 1, 3);

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
        "QPushButton:hover { background-color:#D1D5DB; }");
    QPushButton *ajouter = new QPushButton("✓ Ajouter");
    ajouter->setMinimumHeight(50);
    ajouter->setStyleSheet(
        "QPushButton { background:qlineargradient(x1:0,y1:0,x2:0,y2:1,"
        "stop:0 #2C5F7C, stop:1 #1B3A57); color:white; font-size:15px;"
        "font-weight:600; border:none; border-radius:8px; padding:12px 30px; }"
        "QPushButton:hover { background:qlineargradient(x1:0,y1:0,x2:0,y2:1,"
        "stop:0 #3A6EA5, stop:1 #2C5F7C); }");
    btnLayout->addWidget(annuler);
    btnLayout->addWidget(ajouter);
    containerLayout->addLayout(btnLayout);
    mainLayout->addWidget(container);

    connect(annuler, &QPushButton::clicked, dialog, &QDialog::reject);
    connect(ajouter, &QPushButton::clicked, this, [=]() {
        if (nom->text().trimmed().isEmpty() || prenom->text().trimmed().isEmpty()
            || telephone->text().trimmed().isEmpty() || cin->text().trimmed().isEmpty()
            || zone->text().trimmed().isEmpty() || adresse->text().trimmed().isEmpty()) {
            showMessage(dialog, "Champs manquants", "Merci de remplir tous les champs.", "warning");
            return;
        }
        if (!QRegularExpression("^\\d{8}$").match(cin->text()).hasMatch()) {
            showMessage(dialog, "CIN invalide", "Le CIN doit contenir exactement 8 chiffres.", "error");
            return;
        }
        if (!QRegularExpression("^\\d{8}$").match(telephone->text()).hasMatch()) {
            showMessage(dialog, "Téléphone invalide", "Le téléphone doit contenir exactement 8 chiffres.", "error");
            return;
        }
        Client c;
        c.setNom(nom->text().trimmed());
        c.setPrenom(prenom->text().trimmed());
        c.setCin(cin->text().trimmed());
        c.setTelephone(telephone->text().trimmed());
        c.setAdresseComplete(adresse->text().trimmed());
        c.setTypeClient(type->currentText());
        c.setStatutCompte("actif");
        c.setCinEmploye(employe->currentData().toString());
        c.setZone(zone->text().trimmed());

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

// ── MODIFICATION CLIENT ──────────────────────────────────────────
void MainWindow::on_bouttonmodifierclient_clicked()
{
    int row = ui->tableWidget_client->currentRow();
    if (row < 0) {
        showMessage(this, "Attention", "⚠️ Veuillez sélectionner un client avant de modifier.", "warning");
        return;
    }
    auto getItemText = [&](int col) -> QString {
        QTableWidgetItem *item = ui->tableWidget_client->item(row, col);
        return item ? item->text().trimmed() : "";
    };
    Client c;
    c.setIdClient(getItemText(0).toInt());
    c.setNom(getItemText(1));
    c.setPrenom(getItemText(2));
    c.setCin(getItemText(3));
    c.setTypeClient(getItemText(4));
    c.setZone(getItemText(5));
    c.setTelephone(getItemText(6));
    c.setStatutCompte(getItemText(7));
    c.setAdresseComplete(getItemText(8));
    c.setCinEmploye(getItemText(9));
    afficherWidgetModifierClient(c);
}

void MainWindow::afficherWidgetModifierClient(Client client)
{
    QDialog *dialog = new QDialog(this);
    dialog->setWindowTitle("✏️ Modifier Client");
    dialog->setFixedSize(850, 600);
    dialog->setStyleSheet("QDialog { background-color: #EDEDED; }");

    QVBoxLayout *mainLayout = new QVBoxLayout(dialog);
    QFrame *container = new QFrame();
    container->setStyleSheet("QFrame { background-color:#F2F2F2; border-radius:20px; }");
    QVBoxLayout *containerLayout = new QVBoxLayout(container);
    containerLayout->setContentsMargins(30, 30, 30, 30);

    QLabel *titre = new QLabel("✏️ Modifier Informations Client");
    titre->setAlignment(Qt::AlignCenter);
    titre->setStyleSheet(
        "QLabel { font-size:20px; font-weight:bold; color:white; padding:20px;"
        "border-radius:18px; background:qlineargradient(x1:0,y1:0,x2:0,y2:1,"
        "stop:0 #1A7A4A, stop:1 #0F4D2E); }");
    containerLayout->addWidget(titre);
    containerLayout->addSpacing(20);

    QWidget *contentWidget = new QWidget();
    contentWidget->setStyleSheet("background-color:white; border-radius:15px;");
    QGridLayout *gridLayout = new QGridLayout(contentWidget);
    gridLayout->setSpacing(15);
    gridLayout->setContentsMargins(25, 25, 25, 25);

    QString labelStyle =
        "QLabel { background-color:transparent; padding:5px; font-size:13px; font-weight:600; color:#374151; }";
    QString editStyle =
        "QLineEdit { background-color:#F9FAFB; border:1px solid #D1D5DB; border-radius:8px;"
        "padding:12px 16px; font-size:14px; color:#111827; }"
        "QLineEdit:focus { border:2px solid #1A7A4A; background-color:#FFFFFF; padding:11px 15px; }";
    QString comboStyle =
        "QComboBox { background-color:#F9FAFB; border:1px solid #D1D5DB; border-radius:8px;"
        "padding:12px 16px; font-size:14px; color:#111827; }"
        "QComboBox QAbstractItemView { background-color:white; selection-background-color:#1A7A4A; selection-color:white; }";

    QLineEdit *nom       = new QLineEdit(client.nom());            nom->setStyleSheet(editStyle);
    QLineEdit *prenom    = new QLineEdit(client.prenom());         prenom->setStyleSheet(editStyle);
    QLineEdit *telephone = new QLineEdit(client.telephone());      telephone->setStyleSheet(editStyle);
    QLineEdit *cin       = new QLineEdit(client.cin());            cin->setStyleSheet(editStyle);
    QLineEdit *zone      = new QLineEdit(client.zone());           zone->setStyleSheet(editStyle);
    QLineEdit *adresse   = new QLineEdit(client.adresseComplete()); adresse->setStyleSheet(editStyle);
    QLineEdit *statut    = new QLineEdit(client.statutCompte());   statut->setStyleSheet(editStyle);

    QComboBox *type = new QComboBox(); type->setStyleSheet(comboStyle);
    type->addItems({"particulier", "entreprise", "autre"});
    int idx = type->findText(client.typeClient());
    if (idx != -1) type->setCurrentIndex(idx);

    cin->setMaxLength(8); telephone->setMaxLength(8);
    cin->setValidator(new QRegularExpressionValidator(QRegularExpression("^[0-9]+$"), cin));
    telephone->setValidator(new QRegularExpressionValidator(QRegularExpression("^[0-9]+$"), telephone));

    auto addLabel = [&](const QString &text) {
        QLabel *l = new QLabel(text); l->setStyleSheet(labelStyle); return l;
    };
    gridLayout->addWidget(addLabel("👤 Nom:"),       0, 0); gridLayout->addWidget(nom,       0, 1);
    gridLayout->addWidget(addLabel("🆔 CIN:"),       0, 2); gridLayout->addWidget(cin,       0, 3);
    gridLayout->addWidget(addLabel("👤 Prenom:"),    1, 0); gridLayout->addWidget(prenom,    1, 1);
    gridLayout->addWidget(addLabel("📍 Zone:"),      1, 2); gridLayout->addWidget(zone,      1, 3);
    gridLayout->addWidget(addLabel("📞 Téléphone:"), 2, 0); gridLayout->addWidget(telephone, 2, 1);
    gridLayout->addWidget(addLabel("🏢 Type:"),      2, 2); gridLayout->addWidget(type,      2, 3);
    gridLayout->addWidget(addLabel("🏠 Adresse:"),   3, 0); gridLayout->addWidget(adresse,   3, 1, 1, 3);
    gridLayout->addWidget(addLabel("📌 Statut:"),    4, 0); gridLayout->addWidget(statut,    4, 1);
    containerLayout->addWidget(contentWidget);
    containerLayout->addSpacing(15);

    QHBoxLayout *btnLayout = new QHBoxLayout(); btnLayout->setSpacing(15);
    QPushButton *annuler  = new QPushButton("✗ Annuler");
    annuler->setMinimumHeight(50);
    annuler->setStyleSheet("QPushButton { background-color:#E5E7EB; color:#374151; font-size:15px; font-weight:600; border:none; border-radius:8px; padding:12px 30px; }");
    QPushButton *modifier = new QPushButton("✓ Enregistrer les modifications");
    modifier->setMinimumHeight(50);
    modifier->setStyleSheet(
        "QPushButton { background:qlineargradient(x1:0,y1:0,x2:0,y2:1,"
        "stop:0 #1A7A4A, stop:1 #0F4D2E); color:white; font-size:15px;"
        "font-weight:600; border:none; border-radius:8px; padding:12px 30px; }");
    btnLayout->addWidget(annuler); btnLayout->addWidget(modifier);
    containerLayout->addLayout(btnLayout);
    mainLayout->addWidget(container);

    connect(annuler, &QPushButton::clicked, dialog, &QDialog::reject);
    connect(modifier, &QPushButton::clicked, this, [=]() {
        if (cin->text().length() != 8 || telephone->text().length() != 8) {
            showMessage(dialog, "Erreur", "CIN et Téléphone doivent contenir exactement 8 chiffres.", "error");
            return;
        }
        if (nom->text().trimmed().isEmpty() || prenom->text().trimmed().isEmpty()) {
            showMessage(dialog, "Champs manquants", "Merci de remplir tous les champs.", "warning");
            return;
        }
        Client c;
        c.setIdClient(client.idClient());
        c.setNom(nom->text().trimmed());
        c.setPrenom(prenom->text().trimmed());
        c.setCin(cin->text().trimmed());
        c.setTelephone(telephone->text().trimmed());
        c.setAdresseComplete(adresse->text().trimmed());
        c.setTypeClient(type->currentText());
        c.setZone(zone->text().trimmed());
        c.setStatutCompte(statut->text().trimmed());
        c.setCinEmploye(client.cinEmploye());

        if (!c.modifier()) {
            showMessage(dialog, "Erreur", "Impossible de modifier le client.", "error");
            return;
        }
        showMessage(dialog, "Succès", "✅ Client modifié avec succès !", "success");
        dialog->accept();
        afficherListeClients();
    });
    dialog->exec();
}

Client MainWindow::getClientSelectionne()
{
    int row = ui->tableWidget_client->currentRow();
    Client c;
    if (row < 0) return c;
    c.setIdClient(ui->tableWidget_client->item(row, 0)->text().toInt());
    return c;
}

// ================================================================
// === MODULE EMPLOYÉ — AFFICHAGE =================================
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
        }
        QTableWidget::item:selected { background-color: #2C5F7C; color: #ffffff; }
        QTableWidget::item:hover    { background-color: #d6e4f0; color: #1B3A57; }
        QHeaderView::section {
            background: qlineargradient(x1:0,y1:0,x2:0,y2:1,stop:0 #2C5F7C,stop:1 #1B3A57);
            color: #ffffff; font-weight: bold; font-size: 13px;
            padding: 12px 16px; border: none; border-right: 1px solid #3A6EA5;
        }
        QScrollBar:vertical   { background:#e8edf2; width:7px; border-radius:4px; }
        QScrollBar::handle:vertical { background:#2C5F7C; border-radius:4px; min-height:30px; }
        QScrollBar:horizontal { background:#e8edf2; height:7px; border-radius:4px; }
        QScrollBar::handle:horizontal { background:#2C5F7C; border-radius:4px; }
        QScrollBar::add-line, QScrollBar::sub-line { background: none; }
    )");

    ui->tableWidget_4->setAlternatingRowColors(true);
    ui->tableWidget_4->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableWidget_4->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tableWidget_4->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableWidget_4->verticalHeader()->setVisible(false);
    ui->tableWidget_4->setShowGrid(false);

    Employe e;
    e.loadEmployesIntoTable(ui->tableWidget_4, "Nom ASC", "");

    ui->tableWidget_4->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    ui->tableWidget_4->horizontalHeader()->setStretchLastSection(true);
    ui->tableWidget_4->horizontalHeader()->setMinimumSectionSize(90);
    ui->tableWidget_4->setSortingEnabled(true);
}

// ================================================================
// === MODULE EMPLOYÉ — TRI =======================================
// ================================================================

void MainWindow::on_btntrieemp_clicked()
{
    QMenu *menu = new QMenu(this);
    menu->setStyleSheet(
        "QMenu{background:#FAF5F0;border:2px solid #2C5F7C;border-radius:6px;padding:8px;}"
        "QMenu::item{padding:8px 25px;color:#291C0E;border-radius:4px;}"
        "QMenu::item:selected{background:#2C5F7C;color:white;}");

    QMenu *alphaMenu = menu->addMenu("🔤 Alphabétique (Nom)");
    QAction *alphaAsc  = alphaMenu->addAction("A → Z");
    QAction *alphaDesc = alphaMenu->addAction("Z → A");

    QMenu *salaireMenu = menu->addMenu("💰 Salaire");
    QAction *salaireAsc  = salaireMenu->addAction("Croissant ↑");
    QAction *salaireDesc = salaireMenu->addAction("Décroissant ↓");

    QMenu *serviceMenu = menu->addMenu("🏢 Service");
    QAction *serviceIT      = serviceMenu->addAction("IT");
    QAction *serviceRH      = serviceMenu->addAction("RH");
    QAction *serviceFinance = serviceMenu->addAction("Finance");

    QAction *tous = menu->addAction("🔄 Afficher Tous");

    connect(menu, &QMenu::triggered, this, [=](QAction *action) {
        QString orderBy       = "Nom ASC";
        QString filterService = "";
        QString label         = "Trier";

        if      (action == alphaAsc)       { orderBy = "Nom ASC, Prenom ASC";  label = "A → Z"; }
        else if (action == alphaDesc)      { orderBy = "Nom DESC, Prenom DESC"; label = "Z → A"; }
        else if (action == salaireAsc)     { orderBy = "Salaire ASC";  label = "Salaire ↑"; }
        else if (action == salaireDesc)    { orderBy = "Salaire DESC"; label = "Salaire ↓"; }
        else if (action == serviceIT)      { filterService = "IT";      label = "Service: IT"; }
        else if (action == serviceRH)      { filterService = "RH";      label = "Service: RH"; }
        else if (action == serviceFinance) { filterService = "Finance"; label = "Service: Finance"; }
        else if (action == tous)           { orderBy = "Nom ASC"; label = "Trier"; }

        Employe e;
        e.loadEmployesIntoTable(ui->tableWidget_4, orderBy, filterService);
        ui->btntrieemp->setText(label);
    });

    menu->exec(ui->btntrieemp->mapToGlobal(QPoint(0, ui->btntrieemp->height())));
}

// ================================================================
// === MODULE EMPLOYÉ — RECHERCHE =================================
// ================================================================

void MainWindow::on_barrerechercheemp_textChanged(const QString &text)
{
    Employe::rechercherDansTable(ui->tableWidget_4, text);
}

void MainWindow::on_bouttonrechercheemp_clicked()
{
    Employe::rechercherDansTable(ui->tableWidget_4, ui->barrerechercheemp->text());
}

// ================================================================
// === MODULE EMPLOYÉ — EXPORT ====================================
// ================================================================

void MainWindow::on_bouttonexporteremp_clicked()
{
    Employe e;
    e.exporterListe(ui->tableWidget_4);
}

// ================================================================
// === MODULE EMPLOYÉ — STATISTIQUES ==============================
// ================================================================

void MainWindow::on_bouttonstatemp_clicked()
{
    Employe e;
    e.afficherStatistiques(this);
}

// ================================================================
// === MODULE EMPLOYÉ — PARAMÈTRES ================================
// ================================================================

void MainWindow::on_paraemploye_clicked()
{
    Parametres_employe::afficher(this);
}

// ================================================================
// === MODULE EMPLOYÉ — AJOUT =====================================
// ================================================================

void MainWindow::on_bouttonajouteremp_clicked() { afficherWidgetAjoutEmploye(); }

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
        "border-radius:18px; background:qlineargradient(x1:0,y1:0,x2:0,y2:1,"
        "stop:0 #2C5F7C, stop:1 #1B3A57); }");
    containerLayout->addWidget(titre);
    containerLayout->addSpacing(20);

    QScrollArea *scrollArea = new QScrollArea();
    scrollArea->setWidgetResizable(true);
    scrollArea->setFrameShape(QFrame::NoFrame);
    QWidget *scrollWidget = new QWidget();
    scrollWidget->setStyleSheet("background-color:white; border-radius:15px;");
    QVBoxLayout *scrollLayout = new QVBoxLayout(scrollWidget);
    scrollLayout->setSpacing(20); scrollLayout->setContentsMargins(20, 20, 20, 20);

    QString labelStyle =
        "QLabel { background-color:transparent; padding:5px; font-size:13px; font-weight:600; color:#374151; }";
    QString editStyle =
        "QLineEdit { background-color:#F9FAFB; border:1px solid #D1D5DB; border-radius:8px;"
        "padding:12px 16px; font-size:14px; color:#111827; }"
        "QLineEdit:focus { border:2px solid #2C5F7C; background-color:#FFFFFF; padding:11px 15px; }";
    QString comboStyle =
        "QComboBox { background-color:#F9FAFB; border:1px solid #D1D5DB; border-radius:8px;"
        "padding:12px 16px; font-size:14px; color:#111827; }"
        "QComboBox:hover { border:1px solid #2C5F7C; background-color:#FFFFFF; }";
    QString spinStyle =
        "QDoubleSpinBox { background-color:#F9FAFB; border:1px solid #D1D5DB; border-radius:8px;"
        "padding:12px 16px; font-size:14px; color:#111827; }"
        "QDoubleSpinBox:hover { border:1px solid #2C5F7C; background-color:#FFFFFF; }";
    QString dateStyle =
        "QDateEdit { background-color:#F9FAFB; border:1px solid #D1D5DB; border-radius:8px;"
        "padding:12px 16px; font-size:14px; color:#111827; }"
        "QDateEdit:hover { border:1px solid #2C5F7C; background-color:#FFFFFF; }";

    auto addField = [&](const QString &text, QWidget *field) {
        QLabel *label = new QLabel(text); label->setStyleSheet(labelStyle);
        scrollLayout->addWidget(label); scrollLayout->addWidget(field);
    };

    QLineEdit *cin       = new QLineEdit(); cin->setStyleSheet(editStyle);
    QLineEdit *nom       = new QLineEdit(); nom->setStyleSheet(editStyle);
    QLineEdit *prenom    = new QLineEdit(); prenom->setStyleSheet(editStyle);
    QLineEdit *email     = new QLineEdit(); email->setStyleSheet(editStyle);
    QLineEdit *telephone = new QLineEdit(); telephone->setStyleSheet(editStyle);
    QLineEdit *service   = new QLineEdit(); service->setStyleSheet(editStyle);

    QComboBox *poste = new QComboBox();
    poste->addItems({"Technicien", "Administratif", "Manager", "Agent terrain"});
    poste->setStyleSheet(comboStyle);

    QDoubleSpinBox *salaire = new QDoubleSpinBox();
    salaire->setSuffix(" TND"); salaire->setDecimals(2);
    salaire->setMinimum(0.0); salaire->setMaximum(99999.99);
    salaire->setStyleSheet(spinStyle);

    QDateEdit *dateEmbauche = new QDateEdit(QDate::currentDate());
    dateEmbauche->setDisplayFormat("dd/MM/yyyy");
    dateEmbauche->setCalendarPopup(true);
    dateEmbauche->setStyleSheet(dateStyle);

    addField("🆔 CIN * (8 chiffres)", cin);
    addField("👤 Nom *", nom);
    addField("👤 Prénom *", prenom);
    QLabel *lblPoste = new QLabel("💼 Poste *"); lblPoste->setStyleSheet(labelStyle);
    scrollLayout->addWidget(lblPoste); scrollLayout->addWidget(poste);
    addField("📧 Email *", email);
    addField("📞 Téléphone * (8 chiffres)", telephone);
    addField("🏢 Service", service);
    QLabel *lblSalaire = new QLabel("💰 Salaire * (TND)"); lblSalaire->setStyleSheet(labelStyle);
    scrollLayout->addWidget(lblSalaire); scrollLayout->addWidget(salaire);
    QLabel *lblDate = new QLabel("📅 Date d'Embauche *"); lblDate->setStyleSheet(labelStyle);
    scrollLayout->addWidget(lblDate); scrollLayout->addWidget(dateEmbauche);

    scrollArea->setWidget(scrollWidget);
    containerLayout->addWidget(scrollArea);
    containerLayout->addSpacing(10);

    QLabel *note = new QLabel("* Tous les champs sont obligatoires");
    note->setStyleSheet("color:#6E7F91; font-style:italic; font-size:12px;");
    containerLayout->addWidget(note);

    QHBoxLayout *btnLayout = new QHBoxLayout(); btnLayout->setSpacing(15);
    QPushButton *annuler = new QPushButton("✗ Annuler");
    annuler->setMinimumHeight(50);
    annuler->setStyleSheet("QPushButton { background-color:#E5E7EB; color:#374151; font-size:15px; font-weight:600; border:none; border-radius:8px; padding:12px 30px; }");
    QPushButton *ajouter = new QPushButton("✓ Ajouter l'employé");
    ajouter->setMinimumHeight(50);
    ajouter->setStyleSheet(
        "QPushButton { background:qlineargradient(x1:0,y1:0,x2:0,y2:1,"
        "stop:0 #2C5F7C, stop:1 #1B3A57); color:white; font-size:15px;"
        "font-weight:600; border:none; border-radius:8px; padding:12px 30px; }");
    btnLayout->addWidget(annuler); btnLayout->addWidget(ajouter);
    containerLayout->addLayout(btnLayout);
    mainLayout->addWidget(container);

    connect(annuler, &QPushButton::clicked, dialog, &QDialog::reject);
    connect(ajouter, &QPushButton::clicked, this, [=]() {
        if (!QRegularExpression("^[0-9]{8}$").match(cin->text()).hasMatch()) {
            showMessage(dialog, "Erreur", "CIN invalide ! (8 chiffres obligatoires)", "error"); return;
        }
        if (nom->text().isEmpty() || prenom->text().isEmpty() || email->text().isEmpty() || telephone->text().isEmpty()) {
            showMessage(dialog, "Erreur", "Tous les champs sont obligatoires !", "error"); return;
        }
        if (!email->text().contains("@") || !email->text().contains(".")) {
            showMessage(dialog, "Erreur", "Email invalide ! (exemple: nom@email.com)", "error"); return;
        }
        if (!QRegularExpression("^[0-9]{8}$").match(telephone->text()).hasMatch()) {
            showMessage(dialog, "Erreur", "Téléphone invalide ! (8 chiffres)", "error"); return;
        }
        if (!QRegularExpression("^[a-zA-ZÀ-ÿ ]+$").match(nom->text()).hasMatch()) {
            showMessage(dialog, "Erreur", "Nom invalide ! (lettres seulement)", "error"); return;
        }
        if (salaire->value() <= 0.0) {
            showMessage(dialog, "Erreur", "Salaire invalide ! (doit être supérieur à 0)", "error"); return;
        }
        Employe emp(cin->text(), nom->text(), prenom->text(),
                    email->text(), poste->currentText(), telephone->text(),
                    salaire->value(), dateEmbauche->date().toString("dd/MM/yyyy"), service->text());
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
// === MODULE EMPLOYÉ — MODIFICATION ==============================
// ================================================================

void MainWindow::on_bouttonmodifieremp_clicked() { afficherWidgetModifierEmploye(); }

void MainWindow::afficherWidgetModifierEmploye()
{
    int selectedRow = ui->tableWidget_4->currentRow();
    if (selectedRow < 0) {
        showMessage(this, "Attention", "⚠️ Veuillez sélectionner un employé avant de modifier.", "warning");
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
        "border-radius:18px; background:qlineargradient(x1:0,y1:0,x2:0,y2:1,"
        "stop:0 #1A7A4A, stop:1 #0F4D2E); }");
    containerLayout->addWidget(titre);
    containerLayout->addSpacing(20);

    QScrollArea *scrollArea = new QScrollArea();
    scrollArea->setWidgetResizable(true); scrollArea->setFrameShape(QFrame::NoFrame);
    QWidget *scrollWidget = new QWidget();
    scrollWidget->setStyleSheet("background-color:white; border-radius:15px;");
    QVBoxLayout *scrollLayout = new QVBoxLayout(scrollWidget);
    scrollLayout->setSpacing(20); scrollLayout->setContentsMargins(20, 20, 20, 20);

    QString labelStyle = "QLabel { background-color:transparent; padding:5px; font-size:13px; font-weight:600; color:#374151; }";
    QString editStyle  =
        "QLineEdit { background-color:#F9FAFB; border:1px solid #D1D5DB; border-radius:8px; padding:12px 16px; font-size:14px; color:#111827; }"
        "QLineEdit:focus { border:2px solid #1A7A4A; background-color:#FFFFFF; padding:11px 15px; }";
    QString comboStyle = "QComboBox { background-color:#F9FAFB; border:1px solid #D1D5DB; border-radius:8px; padding:12px 16px; font-size:14px; color:#111827; }";
    QString spinStyle  = "QDoubleSpinBox { background-color:#F9FAFB; border:1px solid #D1D5DB; border-radius:8px; padding:12px 16px; font-size:14px; color:#111827; }";
    QString dateStyle  = "QDateEdit { background-color:#F9FAFB; border:1px solid #D1D5DB; border-radius:8px; padding:12px 16px; font-size:14px; color:#111827; }";

    QLabel *lblCIN = new QLabel("🆔 CIN (non modifiable)"); lblCIN->setStyleSheet(labelStyle);
    QLineEdit *cinDisplay = new QLineEdit(cin_actuel);
    cinDisplay->setReadOnly(true);
    cinDisplay->setStyleSheet("QLineEdit { background-color:#E5E7EB; border:1px solid #D1D5DB; border-radius:8px; padding:12px 16px; font-size:14px; color:#6B7280; }");
    scrollLayout->addWidget(lblCIN); scrollLayout->addWidget(cinDisplay);

    QLineEdit *nom       = new QLineEdit(nom_actuel);     nom->setStyleSheet(editStyle);
    QLineEdit *prenom    = new QLineEdit(prenom_actuel);  prenom->setStyleSheet(editStyle);
    QLineEdit *email     = new QLineEdit(email_actuel);   email->setStyleSheet(editStyle);
    QLineEdit *telephone = new QLineEdit(tel_actuel);     telephone->setStyleSheet(editStyle);
    QLineEdit *service   = new QLineEdit(service_actuel); service->setStyleSheet(editStyle);

    QComboBox *poste = new QComboBox(); poste->setStyleSheet(comboStyle);
    poste->addItems({"Technicien", "Administratif", "Manager", "Agent terrain"});
    poste->setCurrentText(poste_actuel);

    QDoubleSpinBox *salaire = new QDoubleSpinBox(); salaire->setStyleSheet(spinStyle);
    salaire->setSuffix(" TND"); salaire->setDecimals(2);
    salaire->setMinimum(0.0); salaire->setMaximum(99999.99);
    salaire->setValue(salaire_actuel.toDouble());

    QDateEdit *dateEmbauche = new QDateEdit(); dateEmbauche->setStyleSheet(dateStyle);
    dateEmbauche->setDisplayFormat("dd/MM/yyyy"); dateEmbauche->setCalendarPopup(true);
    QDate d = QDate::fromString(date_actuelle, "dd/MM/yyyy");
    if (!d.isValid()) d = QDate::fromString(date_actuelle, "yyyy-MM-dd");
    if (!d.isValid()) d = QDate::currentDate();
    dateEmbauche->setDate(d);

    auto addField = [&](const QString &text, QWidget *field) {
        QLabel *label = new QLabel(text); label->setStyleSheet(labelStyle);
        scrollLayout->addWidget(label); scrollLayout->addWidget(field);
    };
    addField("👤 Nom *", nom);
    addField("👤 Prénom *", prenom);
    QLabel *lblPoste = new QLabel("💼 Poste *"); lblPoste->setStyleSheet(labelStyle);
    scrollLayout->addWidget(lblPoste); scrollLayout->addWidget(poste);
    addField("📧 Email *", email);
    addField("📞 Téléphone * (8 chiffres)", telephone);
    addField("🏢 Service", service);
    QLabel *lblSalaire = new QLabel("💰 Salaire (TND)"); lblSalaire->setStyleSheet(labelStyle);
    scrollLayout->addWidget(lblSalaire); scrollLayout->addWidget(salaire);
    QLabel *lblDate = new QLabel("📅 Date d'Embauche"); lblDate->setStyleSheet(labelStyle);
    scrollLayout->addWidget(lblDate); scrollLayout->addWidget(dateEmbauche);

    scrollArea->setWidget(scrollWidget);
    containerLayout->addWidget(scrollArea);
    containerLayout->addSpacing(10);

    QLabel *note = new QLabel("* Tous les champs sont obligatoires");
    note->setStyleSheet("color:#6E7F91; font-style:italic; font-size:12px;");
    containerLayout->addWidget(note);

    QHBoxLayout *btnLayout = new QHBoxLayout(); btnLayout->setSpacing(15);
    QPushButton *annuler = new QPushButton("✗ Annuler");
    annuler->setMinimumHeight(50);
    annuler->setStyleSheet("QPushButton { background-color:#E5E7EB; color:#374151; font-size:15px; font-weight:600; border:none; border-radius:8px; padding:12px 30px; }");
    QPushButton *modifier = new QPushButton("✓ Enregistrer les modifications");
    modifier->setMinimumHeight(50);
    modifier->setStyleSheet(
        "QPushButton { background:qlineargradient(x1:0,y1:0,x2:0,y2:1,"
        "stop:0 #1A7A4A, stop:1 #0F4D2E); color:white; font-size:15px;"
        "font-weight:600; border:none; border-radius:8px; padding:12px 30px; }");
    btnLayout->addWidget(annuler); btnLayout->addWidget(modifier);
    containerLayout->addLayout(btnLayout);
    mainLayout->addWidget(container);

    connect(annuler, &QPushButton::clicked, dialog, &QDialog::reject);
    connect(modifier, &QPushButton::clicked, this, [=]() {
        if (nom->text().isEmpty() || prenom->text().isEmpty() || email->text().isEmpty() || telephone->text().isEmpty()) {
            showMessage(dialog, "Erreur", "Tous les champs sont obligatoires !", "error"); return;
        }
        if (!email->text().contains("@") || !email->text().contains(".")) {
            showMessage(dialog, "Erreur", "Email invalide !", "error"); return;
        }
        if (!QRegularExpression("^[0-9]{8}$").match(telephone->text()).hasMatch()) {
            showMessage(dialog, "Erreur", "Téléphone invalide ! (8 chiffres)", "error"); return;
        }
        if (salaire->value() <= 0.0) {
            showMessage(dialog, "Erreur", "Salaire invalide ! (doit être supérieur à 0)", "error"); return;
        }
        Employe emp;
        emp.setNom(nom->text()); emp.setPrenom(prenom->text());
        emp.setEmail(email->text()); emp.setPoste(poste->currentText());
        emp.setTelephone(telephone->text()); emp.setSalaire(salaire->value());
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
// === MODULE EMPLOYÉ — SUPPRESSION ===============================
// ================================================================

void MainWindow::on_bouttonsupprimeremp_clicked()
{
    int selectedRow = ui->tableWidget_4->currentRow();
    if (selectedRow < 0) {
        showMessage(this, "Attention", "⚠️ Veuillez sélectionner un employé avant de supprimer.", "warning");
        return;
    }
    QString cin_choisi = ui->tableWidget_4->item(selectedRow, 0)->text();
    QString nom_choisi = ui->tableWidget_4->item(selectedRow, 1)->text()
                         + " " + ui->tableWidget_4->item(selectedRow, 2)->text();

    Employe empCheck;
    int nbClients = empCheck.compterClientsLies(cin_choisi);
    if (nbClients > 0) {
        showMessage(this, "Suppression impossible",
                    "❌ Cet employé est lié à " + QString::number(nbClients) +
                        " client(s).\nVeuillez d'abord modifier ou supprimer ces clients.", "error");
        return;
    }

    QDialog *confirm = new QDialog(this);
    confirm->setFixedSize(440, 220);
    confirm->setStyleSheet("QDialog { background-color:#1E1E2E; border-radius:14px; }");
    QVBoxLayout *lay = new QVBoxLayout(confirm);
    lay->setContentsMargins(0, 0, 0, 24); lay->setSpacing(0);

    QWidget *header = new QWidget(); header->setFixedHeight(62);
    header->setStyleSheet("QWidget { background-color:#E67E22; border-top-left-radius:14px; border-top-right-radius:14px; }");
    QHBoxLayout *hLay = new QHBoxLayout(header); hLay->setContentsMargins(22, 0, 22, 0);
    QLabel *lblTitre = new QLabel("⚠️  Confirmer la suppression");
    lblTitre->setStyleSheet("font-size:15px; font-weight:bold; color:white; background:transparent;");
    hLay->addWidget(lblTitre); lay->addWidget(header);

    QLabel *lblMsg = new QLabel("Voulez-vous vraiment supprimer :\n👤 " + nom_choisi + "\n🆔 CIN : " + cin_choisi);
    lblMsg->setAlignment(Qt::AlignCenter); lblMsg->setWordWrap(true);
    lblMsg->setStyleSheet("font-size:13px; color:#C8C8D8; background:transparent; padding:16px 28px 8px 28px;");
    lay->addWidget(lblMsg); lay->addStretch();

    QHBoxLayout *btnLay = new QHBoxLayout(); btnLay->setSpacing(12); btnLay->setContentsMargins(20, 0, 20, 0);
    QPushButton *btnNon = new QPushButton("✗ Annuler"); btnNon->setFixedHeight(40);
    btnNon->setStyleSheet("QPushButton { background:#374151; color:white; font-size:13px; font-weight:600; border:none; border-radius:8px; }");
    QPushButton *btnOui = new QPushButton("🗑️ Oui, supprimer"); btnOui->setFixedHeight(40);
    btnOui->setStyleSheet("QPushButton { background:#C0392B; color:white; font-size:13px; font-weight:600; border:none; border-radius:8px; }");
    btnLay->addWidget(btnNon); btnLay->addWidget(btnOui); lay->addLayout(btnLay);

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

// ================================================================
// === MODULE RECYCLAGE — AFFICHAGE ================================
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

    ui->tableWidget_Recyclage->setStyleSheet(R"(
        QTableWidget { background-color:#f0f4f8; alternate-background-color:#e8edf2;
            border:none; gridline-color:transparent; font-size:13px; color:#2d3436; }
        QTableWidget::item { padding:10px 16px; border:none; border-bottom:1px solid #dfe6ed; }
        QTableWidget::item:selected { background-color:#2C5F7C; color:#ffffff; }
        QTableWidget::item:hover    { background-color:#d6e4f0; color:#1B3A57; }
        QHeaderView::section { background:qlineargradient(x1:0,y1:0,x2:0,y2:1,stop:0 #2C5F7C,stop:1 #1B3A57);
            color:#ffffff; font-weight:bold; font-size:13px; padding:12px 16px; border:none; }
    )");
    ui->tableWidget_Recyclage->setAlternatingRowColors(true);
    ui->tableWidget_Recyclage->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableWidget_Recyclage->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tableWidget_Recyclage->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableWidget_Recyclage->verticalHeader()->setVisible(false);
    ui->tableWidget_Recyclage->setShowGrid(false);

    QList<Recyclage> liste = Recyclage::getAll();
    int row = 0;
    for (const Recyclage &r : liste) {
        ui->tableWidget_Recyclage->insertRow(row);
        QStringList vals = {
            QString::number(r.getId()), r.getDateTri(), r.getTypeMateriau(),
            QString::number(r.getQuantiteEntree()),   QString::number(r.getQuantiteRecyclee()),
            QString::number(r.getQuantiteRejetee()),  r.getDestination(),
            QString::number(r.getValeurMonetaire()),  r.getDirection(), r.getStatut()
        };
        for (int col = 0; col < 10; col++) {
            QTableWidgetItem *item = new QTableWidgetItem(vals[col]);
            if (col == 0) {
                ui->tableWidget_Recyclage->setItem(row, col, item);
                ui->tableWidget_Recyclage->setColumnHidden(0, true);
                continue;
            }
            item->setTextAlignment(Qt::AlignVCenter | Qt::AlignLeft);
            ui->tableWidget_Recyclage->setItem(row, col, item);
        }
        ui->tableWidget_Recyclage->setRowHeight(row, 44);
        row++;
    }
    ui->tableWidget_Recyclage->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    ui->tableWidget_Recyclage->horizontalHeader()->setStretchLastSection(true);
    ui->tableWidget_Recyclage->setSortingEnabled(true);
}
// ================================================================
// Ajouter en tête de mainwindow.cpp :
//   #include "mdp_oublier.h"
//
// Ajouter dans mainwindow.h, section private: :
//   QString m_codeVerification;
//   QString m_emailReset;
//
// Ajouter dans mainwindow.h, section private slots: :
//   void on_mdp_oublier_clicked();
// ================================================================

void MainWindow::on_mdp_oublier_clicked()
{
    // ============================================================
    // DIALOGUE 1 — Saisie de l'email
    // ============================================================
    QDialog *dlgEmail = new QDialog(this);
    dlgEmail->setWindowTitle("Mot de passe oublié");
    dlgEmail->setFixedSize(480, 280);
    dlgEmail->setStyleSheet("QDialog { background-color:#1E1E2E; border-radius:14px; }");

    QVBoxLayout *lay1 = new QVBoxLayout(dlgEmail);
    lay1->setContentsMargins(0, 0, 0, 24);
    lay1->setSpacing(0);

    // Header
    QWidget *header1 = new QWidget();
    header1->setFixedHeight(62);
    header1->setStyleSheet("QWidget { background-color:#2C5F7C;"
                           "border-top-left-radius:14px; border-top-right-radius:14px; }");
    QHBoxLayout *hLay1 = new QHBoxLayout(header1);
    hLay1->setContentsMargins(22, 0, 22, 0);
    QLabel *lblTitre1 = new QLabel("🔑  Réinitialisation du mot de passe");
    lblTitre1->setStyleSheet("font-size:15px; font-weight:bold; color:white; background:transparent;");
    hLay1->addWidget(lblTitre1);
    lay1->addWidget(header1);

    // Corps
    QVBoxLayout *body1 = new QVBoxLayout();
    body1->setContentsMargins(28, 20, 28, 0);
    body1->setSpacing(12);

    QLabel *lblInfo = new QLabel("Saisissez votre adresse email pour recevoir\nun code de vérification.");
    lblInfo->setStyleSheet("font-size:13px; color:#C8C8D8; background:transparent;");
    lblInfo->setAlignment(Qt::AlignCenter);
    body1->addWidget(lblInfo);

    QLineEdit *editEmail = new QLineEdit();
    editEmail->setPlaceholderText("exemple@email.com");
    editEmail->setStyleSheet(
        "QLineEdit { background:#2A2A3E; border:1px solid #3A3A5C; border-radius:8px;"
        "padding:10px 14px; font-size:14px; color:white; }"
        "QLineEdit:focus { border:2px solid #2C5F7C; }");
    body1->addWidget(editEmail);
    lay1->addLayout(body1);
    lay1->addStretch();

    // Boutons
    QHBoxLayout *btnLay1 = new QHBoxLayout();
    btnLay1->setSpacing(12);
    btnLay1->setContentsMargins(28, 0, 28, 0);

    QPushButton *btnAnnuler1 = new QPushButton("✗ Annuler");
    btnAnnuler1->setFixedHeight(42);
    btnAnnuler1->setStyleSheet(
        "QPushButton { background:#374151; color:white; font-size:13px;"
        "font-weight:600; border:none; border-radius:8px; }");

    QPushButton *btnEnvoyer = new QPushButton("📧 Envoyer le code");
    btnEnvoyer->setFixedHeight(42);
    btnEnvoyer->setStyleSheet(
        "QPushButton { background:#2C5F7C; color:white; font-size:13px;"
        "font-weight:600; border:none; border-radius:8px; }"
        "QPushButton:hover { background:#3A6EA5; }");

    btnLay1->addWidget(btnAnnuler1);
    btnLay1->addWidget(btnEnvoyer);
    lay1->addLayout(btnLay1);

    connect(btnAnnuler1, &QPushButton::clicked, dlgEmail, &QDialog::reject);

    connect(btnEnvoyer, &QPushButton::clicked, this, [=]() {
        QString email = editEmail->text().trimmed();

        // Validation format
        if (email.isEmpty()) {
            showMessage(dlgEmail, "Champ vide",
                        "Veuillez saisir votre adresse email.", "warning");
            return;
        }
        if (!email.contains("@") || !email.contains(".")) {
            showMessage(dlgEmail, "Email invalide",
                        "Veuillez saisir un email valide.", "error");
            return;
        }

        // Vérification en base (requête préparée dans MdpOublier)
        if (!MdpOublier::emailExiste(email)) {
            showMessage(dlgEmail, "Employé non connu",
                        "❌ Aucun employé trouvé avec cet email.\n"
                        "Vérifiez votre adresse ou contactez l'administrateur.",
                        "error");
            return;
        }

        // Génération et envoi du code
        m_codeVerification = MdpOublier::genererCodeVerification();
        m_emailReset       = email;
        QString nom        = MdpOublier::getNomEmploye(email);

        bool envoye = MdpOublier::envoyerCodeParEmail(email, m_codeVerification, nom);
        if (!envoye) {
            showMessage(dlgEmail, "Erreur d'envoi",
                        "⚠️ Le code n'a pas pu être envoyé.\n"
                        "Vérifiez votre connexion internet.", "warning");
            return;
        }

        dlgEmail->accept();
    });

    if (dlgEmail->exec() != QDialog::Accepted)
        return;

    // ============================================================
    // DIALOGUE 2 — Saisie du code de vérification
    // ============================================================
    QDialog *dlgCode = new QDialog(this);
    dlgCode->setWindowTitle("Code de vérification");
    dlgCode->setFixedSize(480, 280);
    dlgCode->setStyleSheet("QDialog { background-color:#1E1E2E; border-radius:14px; }");

    QVBoxLayout *lay2 = new QVBoxLayout(dlgCode);
    lay2->setContentsMargins(0, 0, 0, 24);
    lay2->setSpacing(0);

    QWidget *header2 = new QWidget();
    header2->setFixedHeight(62);
    header2->setStyleSheet("QWidget { background-color:#2C5F7C;"
                           "border-top-left-radius:14px; border-top-right-radius:14px; }");
    QHBoxLayout *hLay2 = new QHBoxLayout(header2);
    hLay2->setContentsMargins(22, 0, 22, 0);
    QLabel *lblTitre2 = new QLabel("✉️  Vérification du code");
    lblTitre2->setStyleSheet("font-size:15px; font-weight:bold; color:white; background:transparent;");
    hLay2->addWidget(lblTitre2);
    lay2->addWidget(header2);

    QVBoxLayout *body2 = new QVBoxLayout();
    body2->setContentsMargins(28, 20, 28, 0);
    body2->setSpacing(12);

    QLabel *lblInfo2 = new QLabel("Un code à 4 chiffres a été envoyé à :\n" + m_emailReset);
    lblInfo2->setStyleSheet("font-size:13px; color:#C8C8D8; background:transparent;");
    lblInfo2->setAlignment(Qt::AlignCenter);
    body2->addWidget(lblInfo2);

    QLineEdit *editCode = new QLineEdit();
    editCode->setPlaceholderText("Saisir le code à 4 chiffres");
    editCode->setMaxLength(4);
    editCode->setAlignment(Qt::AlignCenter);
    editCode->setValidator(new QRegularExpressionValidator(
        QRegularExpression("^[0-9]{0,4}$"), editCode));
    editCode->setStyleSheet(
        "QLineEdit { background:#2A2A3E; border:1px solid #3A3A5C; border-radius:8px;"
        "padding:10px 14px; font-size:22px; font-weight:bold; color:white;"
        "letter-spacing:8px; }"
        "QLineEdit:focus { border:2px solid #2C5F7C; }");
    body2->addWidget(editCode);
    lay2->addLayout(body2);
    lay2->addStretch();

    QHBoxLayout *btnLay2 = new QHBoxLayout();
    btnLay2->setSpacing(12);
    btnLay2->setContentsMargins(28, 0, 28, 0);

    QPushButton *btnAnnuler2 = new QPushButton("✗ Annuler");
    btnAnnuler2->setFixedHeight(42);
    btnAnnuler2->setStyleSheet(
        "QPushButton { background:#374151; color:white; font-size:13px;"
        "font-weight:600; border:none; border-radius:8px; }");

    QPushButton *btnVerifier = new QPushButton("✓ Vérifier");
    btnVerifier->setFixedHeight(42);
    btnVerifier->setStyleSheet(
        "QPushButton { background:#2C5F7C; color:white; font-size:13px;"
        "font-weight:600; border:none; border-radius:8px; }"
        "QPushButton:hover { background:#3A6EA5; }");

    btnLay2->addWidget(btnAnnuler2);
    btnLay2->addWidget(btnVerifier);
    lay2->addLayout(btnLay2);

    connect(btnAnnuler2, &QPushButton::clicked, dlgCode, &QDialog::reject);

    connect(btnVerifier, &QPushButton::clicked, this, [=]() {
        QString codeSaisi = editCode->text().trimmed();

        if (codeSaisi.isEmpty()) {
            showMessage(dlgCode, "Champ vide",
                        "Veuillez saisir le code reçu par email.", "warning");
            return;
        }
        if (codeSaisi != m_codeVerification) {
            showMessage(dlgCode, "Code incorrect",
                        "❌ Le code saisi est incorrect.\n"
                        "Vérifiez votre email.", "error");
            editCode->clear();
            return;
        }
        dlgCode->accept();
    });

    if (dlgCode->exec() != QDialog::Accepted)
        return;

    // ============================================================
    // DIALOGUE 3 — Saisie du nouveau mot de passe
    // ============================================================
    QDialog *dlgMdp = new QDialog(this);
    dlgMdp->setWindowTitle("Nouveau mot de passe");
    dlgMdp->setFixedSize(480, 320);
    dlgMdp->setStyleSheet("QDialog { background-color:#1E1E2E; border-radius:14px; }");

    QVBoxLayout *lay3 = new QVBoxLayout(dlgMdp);
    lay3->setContentsMargins(0, 0, 0, 24);
    lay3->setSpacing(0);

    QWidget *header3 = new QWidget();
    header3->setFixedHeight(62);
    header3->setStyleSheet("QWidget { background-color:#1A7A4A;"
                           "border-top-left-radius:14px; border-top-right-radius:14px; }");
    QHBoxLayout *hLay3 = new QHBoxLayout(header3);
    hLay3->setContentsMargins(22, 0, 22, 0);
    QLabel *lblTitre3 = new QLabel("🔒  Nouveau mot de passe");
    lblTitre3->setStyleSheet("font-size:15px; font-weight:bold; color:white; background:transparent;");
    hLay3->addWidget(lblTitre3);
    lay3->addWidget(header3);

    QVBoxLayout *body3 = new QVBoxLayout();
    body3->setContentsMargins(28, 20, 28, 0);
    body3->setSpacing(12);

    QString editStyleMdp =
        "QLineEdit { background:#2A2A3E; border:1px solid #3A3A5C; border-radius:8px;"
        "padding:10px 14px; font-size:14px; color:white; }"
        "QLineEdit:focus { border:2px solid #1A7A4A; }";

    QLabel *lblNouv = new QLabel("Nouveau mot de passe");
    lblNouv->setStyleSheet("font-size:13px; color:#C8C8D8; background:transparent;");
    QLineEdit *editNouv = new QLineEdit();
    editNouv->setEchoMode(QLineEdit::Password);
    editNouv->setPlaceholderText("Minimum 6 caractères");
    editNouv->setStyleSheet(editStyleMdp);

    QLabel *lblConf = new QLabel("Confirmer le mot de passe");
    lblConf->setStyleSheet("font-size:13px; color:#C8C8D8; background:transparent;");
    QLineEdit *editConf = new QLineEdit();
    editConf->setEchoMode(QLineEdit::Password);
    editConf->setPlaceholderText("Répéter le mot de passe");
    editConf->setStyleSheet(editStyleMdp);

    body3->addWidget(lblNouv);
    body3->addWidget(editNouv);
    body3->addWidget(lblConf);
    body3->addWidget(editConf);
    lay3->addLayout(body3);
    lay3->addStretch();

    QHBoxLayout *btnLay3 = new QHBoxLayout();
    btnLay3->setSpacing(12);
    btnLay3->setContentsMargins(28, 0, 28, 0);

    QPushButton *btnAnnuler3 = new QPushButton("✗ Annuler");
    btnAnnuler3->setFixedHeight(42);
    btnAnnuler3->setStyleSheet(
        "QPushButton { background:#374151; color:white; font-size:13px;"
        "font-weight:600; border:none; border-radius:8px; }");

    QPushButton *btnSauver = new QPushButton("✓ Enregistrer");
    btnSauver->setFixedHeight(42);
    btnSauver->setStyleSheet(
        "QPushButton { background:#1A7A4A; color:white; font-size:13px;"
        "font-weight:600; border:none; border-radius:8px; }"
        "QPushButton:hover { background:#22a060; }");

    btnLay3->addWidget(btnAnnuler3);
    btnLay3->addWidget(btnSauver);
    lay3->addLayout(btnLay3);

    connect(btnAnnuler3, &QPushButton::clicked, dlgMdp, &QDialog::reject);

    connect(btnSauver, &QPushButton::clicked, this, [=]() {
        QString mdp1 = editNouv->text().trimmed();
        QString mdp2 = editConf->text().trimmed();

        if (mdp1.isEmpty() || mdp2.isEmpty()) {
            showMessage(dlgMdp, "Champs vides",
                        "Veuillez remplir les deux champs.", "warning");
            return;
        }
        if (mdp1.length() < 6) {
            showMessage(dlgMdp, "Mot de passe trop court",
                        "Le mot de passe doit contenir au moins 6 caractères.", "error");
            return;
        }
        if (mdp1 != mdp2) {
            showMessage(dlgMdp, "Mots de passe différents",
                        "❌ Les deux mots de passe ne correspondent pas.", "error");
            editConf->clear();
            return;
        }

        // Mise à jour en base (requête préparée dans MdpOublier)
        if (!MdpOublier::reinitialiserMotDePasse(m_emailReset, mdp1)) {
            showMessage(dlgMdp, "Erreur",
                        "❌ Impossible de mettre à jour le mot de passe.", "error");
            return;
        }

        // Nettoyage de l'état
        m_codeVerification = "";
        m_emailReset       = "";

        showMessage(dlgMdp, "Succès",
                    "✅ Mot de passe réinitialisé avec succès !\n"
                    "Vous pouvez maintenant vous connecter.", "success");
        dlgMdp->accept();
    });

    dlgMdp->exec();
}
// ── TRI RECYCLAGE ────────────────────────────────────────────────
void MainWindow::on_bttntrirecyclage_clicked()
{
    QMenu *menu = new QMenu(this);
    menu->setStyleSheet(
        "QMenu{background:#FAF5F0;border:2px solid #2C5F7C;border-radius:6px;padding:8px;}"
        "QMenu::item{padding:8px 25px;color:#291C0E;border-radius:4px;}"
        "QMenu::item:selected{background:#2C5F7C;color:white;}");

    QMenu *matMenu = menu->addMenu("📦 Matériau");
    QAction *matAsc  = matMenu->addAction("A → Z");
    QAction *matDesc = matMenu->addAction("Z → A");

    QMenu *statutMenu = menu->addMenu("⚙️ Statut");
    QAction *termine   = statutMenu->addAction("Terminé");
    QAction *enCours   = statutMenu->addAction("En cours");
    QAction *enAttente = statutMenu->addAction("En attente");
    QAction *annule    = statutMenu->addAction("Annulé");
    QAction *tous      = menu->addAction("🔄 Afficher Tous");

    connect(menu, &QMenu::triggered, this, [=](QAction *action) {
        QString orderBy      = "ID_recyclage";
        QString filterStatut = "";
        if      (action == matAsc)    { orderBy = "Type_materiau ASC"; }
        else if (action == matDesc)   { orderBy = "Type_materiau DESC"; }
        else if (action == termine)   { filterStatut = "Terminé"; }
        else if (action == enCours)   { filterStatut = "En cours"; }
        else if (action == enAttente) { filterStatut = "En attente"; }
        else if (action == annule)    { filterStatut = "Annulé"; }
        else if (action == tous)      { orderBy = "ID_recyclage"; }

        Recyclage r;
        r.loadRecyclagesIntoTable(ui->tableWidget_Recyclage, orderBy, filterStatut);
    });

    menu->exec(ui->bttntrirecyclage->mapToGlobal(QPoint(0, ui->bttntrirecyclage->height())));
}

// ── RECHERCHE RECYCLAGE ──────────────────────────────────────────
void MainWindow::on_barrerechercherecyclage_textChanged(const QString &text)
{
    Recyclage::rechercherDansTable(ui->tableWidget_Recyclage, text);
}

// ── EXPORT RECYCLAGE ─────────────────────────────────────────────
void MainWindow::on_bouttonexporterrecyclage_clicked()
{
    Recyclage r;
    r.exporterListe(ui->tableWidget_Recyclage);
}

// ── STATISTIQUES RECYCLAGE ───────────────────────────────────────
void MainWindow::on_bouttonstatrecyclage_clicked()
{
    Recyclage r;
    r.afficherStatistiques(this);
}

// ── AJOUT RECYCLAGE ──────────────────────────────────────────────
void MainWindow::on_bouttonajouterrecyclage_clicked() { afficherWidgetAjoutRecyclage(); }

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
        "QLabel { font-size:20px; font-weight:bold; color:white; padding:20px; border-radius:18px;"
        "background:qlineargradient(x1:0,y1:0,x2:0,y2:1,stop:0 #2C5F7C,stop:1 #1B3A57); }");
    containerLayout->addWidget(titre);
    containerLayout->addSpacing(20);

    QWidget *contentWidget = new QWidget();
    contentWidget->setStyleSheet("background-color:white; border-radius:15px;");
    QGridLayout *gridLayout = new QGridLayout(contentWidget);
    gridLayout->setSpacing(15); gridLayout->setContentsMargins(25, 25, 25, 25);

    QString labelStyle = "QLabel { background-color:transparent; padding:5px; font-size:13px; font-weight:600; color:#374151; }";
    QString editStyle  =
        "QLineEdit, QComboBox, QDoubleSpinBox { background-color:#F9FAFB; border:1px solid #D1D5DB;"
        "border-radius:8px; padding:12px 16px; font-size:14px; color:#111827; }"
        "QLineEdit:hover, QComboBox:hover, QDoubleSpinBox:hover { border:1px solid #2C5F7C; background-color:#FFFFFF; }";

    QComboBox *materiau = new QComboBox(); materiau->setStyleSheet(editStyle);
    materiau->addItems({"Plastique", "Verre", "Métal", "Papier", "Organique", "Electronique", "Autre"});

    QDoubleSpinBox *qteEntree   = new QDoubleSpinBox(); qteEntree->setSuffix(" kg");
    qteEntree->setDecimals(2); qteEntree->setMaximum(999999.99); qteEntree->setStyleSheet(editStyle);
    QDoubleSpinBox *qteRecyclee = new QDoubleSpinBox(); qteRecyclee->setSuffix(" kg");
    qteRecyclee->setDecimals(2); qteRecyclee->setMaximum(999999.99); qteRecyclee->setStyleSheet(editStyle);
    QDoubleSpinBox *qteRejetee  = new QDoubleSpinBox(); qteRejetee->setSuffix(" kg");
    qteRejetee->setDecimals(2); qteRejetee->setMaximum(999999.99); qteRejetee->setStyleSheet(editStyle);
    QLineEdit *destination = new QLineEdit(); destination->setStyleSheet(editStyle);
    QDoubleSpinBox *valeur = new QDoubleSpinBox(); valeur->setSuffix(" TND");
    valeur->setDecimals(2); valeur->setMaximum(999999.99); valeur->setStyleSheet(editStyle);
    QLineEdit *direction = new QLineEdit("Interne"); direction->setStyleSheet(editStyle);
    QComboBox *statut = new QComboBox(); statut->setStyleSheet(editStyle);
    statut->addItems({"En attente", "En cours", "Terminé", "Annulé"});

    auto addLbl = [&](const QString &t) { QLabel *l = new QLabel(t); l->setStyleSheet(labelStyle); return l; };

    gridLayout->addWidget(addLbl("📦 Matériau :"),              0, 0); gridLayout->addWidget(materiau,    0, 1);
    gridLayout->addWidget(addLbl("📊 Quantité entrée (kg) :"),  1, 0); gridLayout->addWidget(qteEntree,   1, 1);
    gridLayout->addWidget(addLbl("✅ Quantité recyclée (kg) :"),2, 0); gridLayout->addWidget(qteRecyclee, 2, 1);
    gridLayout->addWidget(addLbl("❌ Quantité rejetée (kg) :"), 3, 0); gridLayout->addWidget(qteRejetee,  3, 1);
    gridLayout->addWidget(addLbl("📍 Destination :"),           0, 2); gridLayout->addWidget(destination, 0, 3);
    gridLayout->addWidget(addLbl("💰 Valeur (TND) :"),          1, 2); gridLayout->addWidget(valeur,      1, 3);
    gridLayout->addWidget(addLbl("🏭 Direction :"),             2, 2); gridLayout->addWidget(direction,   2, 3);
    gridLayout->addWidget(addLbl("📊 Statut :"),                3, 2); gridLayout->addWidget(statut,      3, 3);

    containerLayout->addWidget(contentWidget);
    containerLayout->addSpacing(15);

    QHBoxLayout *btnLayout = new QHBoxLayout(); btnLayout->setSpacing(15);
    QPushButton *annuler = new QPushButton("✗ Annuler"); annuler->setMinimumHeight(50);
    annuler->setStyleSheet("QPushButton { background-color:#E5E7EB; color:#374151; font-size:15px; font-weight:600; border:none; border-radius:8px; padding:12px 30px; }");
    QPushButton *ajouter = new QPushButton("✓ Ajouter"); ajouter->setMinimumHeight(50);
    ajouter->setStyleSheet(
        "QPushButton { background:qlineargradient(x1:0,y1:0,x2:0,y2:1,stop:0 #2C5F7C,stop:1 #1B3A57);"
        "color:white; font-size:15px; font-weight:600; border:none; border-radius:8px; padding:12px 30px; }");
    btnLayout->addWidget(annuler); btnLayout->addWidget(ajouter);
    containerLayout->addLayout(btnLayout);
    mainLayout->addWidget(container);

    connect(annuler, &QPushButton::clicked, dialog, &QDialog::reject);
    connect(ajouter, &QPushButton::clicked, this, [=]() {
        if (destination->text().trimmed().isEmpty() || direction->text().trimmed().isEmpty()) {
            showMessage(dialog, "Champs manquants", "Merci de remplir tous les champs.", "warning"); return;
        }
        if (qteEntree->value() <= 0.0) {
            showMessage(dialog, "Erreur", "La quantité entrée doit être supérieure à 0 !", "error"); return;
        }
        if (qteRecyclee->value() > qteEntree->value()) {
            showMessage(dialog, "Erreur", "La quantité recyclée ne peut pas dépasser la quantité entrée !", "error"); return;
        }
        Recyclage r(0, QDate::currentDate().toString("dd/MM/yyyy"), materiau->currentText(),
                    qteEntree->value(), qteRecyclee->value(), qteRejetee->value(),
                    destination->text().trimmed(), valeur->value(),
                    direction->text().trimmed(), statut->currentText());
        if (r.ajouter()) {
            showMessage(dialog, "Succès", "✅ Recyclage ajouté avec succès !", "success");
            afficherRecyclages(); dialog->accept();
        } else {
            showMessage(dialog, "Erreur", "Impossible d'ajouter ce recyclage.", "error");
        }
    });
    dialog->exec();
}

// ── MODIFICATION RECYCLAGE ───────────────────────────────────────
void MainWindow::on_bouttonmodifierrecyclage_clicked()
{
    int row = ui->tableWidget_Recyclage->currentRow();
    if (row < 0) {
        showMessage(this, "Attention", "⚠️ Veuillez sélectionner un recyclage avant de modifier.", "warning"); return;
    }
    QTableWidgetItem *idItem = ui->tableWidget_Recyclage->item(row, 0);
    if (!idItem || idItem->text().trimmed().isEmpty()) {
        showMessage(this, "Erreur", "Impossible de récupérer l'ID.", "error"); return;
    }
    afficherWidgetModifierRecyclage(idItem->text().toInt());
}

void MainWindow::afficherWidgetModifierRecyclage(int idRecyclage)
{
    Recyclage r = Recyclage::getById(idRecyclage);
    if (r.getId() == 0) {
        showMessage(this, "Erreur", "Recyclage introuvable.", "error"); return;
    }

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
        "QLabel { font-size:18px; font-weight:bold; color:white; padding:20px; border-radius:18px;"
        "background:qlineargradient(x1:0,y1:0,x2:0,y2:1,stop:0 #1A7A4A,stop:1 #0F4D2E); }");
    containerLayout->addWidget(titre);
    containerLayout->addSpacing(20);

    QWidget *contentWidget = new QWidget();
    contentWidget->setStyleSheet("background-color:white; border-radius:15px;");
    QGridLayout *gridLayout = new QGridLayout(contentWidget);
    gridLayout->setSpacing(15); gridLayout->setContentsMargins(25, 25, 25, 25);

    QString labelStyle = "QLabel { background-color:transparent; padding:5px; font-size:13px; font-weight:600; color:#374151; }";
    QString editStyle  =
        "QLineEdit, QComboBox, QDoubleSpinBox, QDateEdit { background-color:#F9FAFB; border:1px solid #D1D5DB;"
        "border-radius:8px; padding:12px 16px; font-size:14px; color:#111827; }"
        "QLineEdit:hover, QComboBox:hover, QDoubleSpinBox:hover, QDateEdit:hover { border:1px solid #1A7A4A; }";

    QDateEdit *dateTri = new QDateEdit(); dateTri->setStyleSheet(editStyle);
    dateTri->setDisplayFormat("dd/MM/yyyy"); dateTri->setCalendarPopup(true);
    QDate d = QDate::fromString(r.getDateTri(), "dd/MM/yyyy");
    if (!d.isValid()) d = QDate::currentDate();
    dateTri->setDate(d);

    QComboBox *typeMateriau = new QComboBox(); typeMateriau->setStyleSheet(editStyle);
    typeMateriau->addItems({"Plastique", "Verre", "Métal", "Papier", "Organique", "Electronique", "Autre"});
    typeMateriau->setCurrentText(r.getTypeMateriau());

    QDoubleSpinBox *qteEntree   = new QDoubleSpinBox(); qteEntree->setSuffix(" kg");
    qteEntree->setDecimals(2); qteEntree->setMaximum(999999.99); qteEntree->setStyleSheet(editStyle);
    qteEntree->setValue(r.getQuantiteEntree());
    QDoubleSpinBox *qteRecyclee = new QDoubleSpinBox(); qteRecyclee->setSuffix(" kg");
    qteRecyclee->setDecimals(2); qteRecyclee->setMaximum(999999.99); qteRecyclee->setStyleSheet(editStyle);
    qteRecyclee->setValue(r.getQuantiteRecyclee());
    QDoubleSpinBox *qteRejetee  = new QDoubleSpinBox(); qteRejetee->setSuffix(" kg");
    qteRejetee->setDecimals(2); qteRejetee->setMaximum(999999.99); qteRejetee->setStyleSheet(editStyle);
    qteRejetee->setValue(r.getQuantiteRejetee());

    QLineEdit *destination = new QLineEdit(r.getDestination()); destination->setStyleSheet(editStyle);
    QDoubleSpinBox *valeur = new QDoubleSpinBox(); valeur->setSuffix(" TND");
    valeur->setDecimals(2); valeur->setMaximum(999999.99); valeur->setStyleSheet(editStyle);
    valeur->setValue(r.getValeurMonetaire());
    QLineEdit *direction = new QLineEdit(r.getDirection()); direction->setStyleSheet(editStyle);
    QComboBox *statut = new QComboBox(); statut->setStyleSheet(editStyle);
    statut->addItems({"En attente", "En cours", "Terminé", "Annulé"});
    statut->setCurrentText(r.getStatut());

    auto addLbl = [&](const QString &t) { QLabel *l = new QLabel(t); l->setStyleSheet(labelStyle); return l; };
    gridLayout->addWidget(addLbl("📅 Date de Tri :"),            0, 0); gridLayout->addWidget(dateTri,      0, 1);
    gridLayout->addWidget(addLbl("📦 Type Matériau :"),          1, 0); gridLayout->addWidget(typeMateriau, 1, 1);
    gridLayout->addWidget(addLbl("📊 Quantité Entrée (kg) :"),   2, 0); gridLayout->addWidget(qteEntree,    2, 1);
    gridLayout->addWidget(addLbl("✅ Quantité Recyclée (kg) :"), 3, 0); gridLayout->addWidget(qteRecyclee,  3, 1);
    gridLayout->addWidget(addLbl("❌ Quantité Rejetée (kg) :"),  4, 0); gridLayout->addWidget(qteRejetee,   4, 1);
    gridLayout->addWidget(addLbl("📍 Destination :"),            0, 2); gridLayout->addWidget(destination,  0, 3);
    gridLayout->addWidget(addLbl("💰 Valeur (TND) :"),           1, 2); gridLayout->addWidget(valeur,       1, 3);
    gridLayout->addWidget(addLbl("🏭 Direction :"),              2, 2); gridLayout->addWidget(direction,    2, 3);
    gridLayout->addWidget(addLbl("📊 Statut :"),                 3, 2); gridLayout->addWidget(statut,       3, 3);
    containerLayout->addWidget(contentWidget);
    containerLayout->addSpacing(15);

    QHBoxLayout *btnLayout = new QHBoxLayout(); btnLayout->setSpacing(15);
    QPushButton *annuler = new QPushButton("✗ Annuler"); annuler->setMinimumHeight(50);
    annuler->setStyleSheet("QPushButton { background-color:#E5E7EB; color:#374151; font-size:15px; font-weight:600; border:none; border-radius:8px; padding:12px 30px; }");
    QPushButton *enregistrer = new QPushButton("✓ Enregistrer"); enregistrer->setMinimumHeight(50);
    enregistrer->setStyleSheet(
        "QPushButton { background:qlineargradient(x1:0,y1:0,x2:0,y2:1,stop:0 #1A7A4A,stop:1 #0F4D2E);"
        "color:white; font-size:15px; font-weight:600; border:none; border-radius:8px; padding:12px 30px; }");
    btnLayout->addWidget(annuler); btnLayout->addWidget(enregistrer);
    containerLayout->addLayout(btnLayout);
    mainLayout->addWidget(container);

    connect(annuler, &QPushButton::clicked, dialog, &QDialog::reject);
    connect(enregistrer, &QPushButton::clicked, this, [=]() {
        if (destination->text().trimmed().isEmpty() || direction->text().trimmed().isEmpty()) {
            showMessage(dialog, "Erreur", "Tous les champs sont obligatoires !", "error"); return;
        }
        if (qteEntree->value() <= 0.0) {
            showMessage(dialog, "Erreur", "La quantité entrée doit être supérieure à 0 !", "error"); return;
        }
        if (qteRecyclee->value() > qteEntree->value()) {
            showMessage(dialog, "Erreur", "La quantité recyclée ne peut pas dépasser la quantité entrée !", "error"); return;
        }
        Recyclage rModif(idRecyclage, dateTri->date().toString("dd/MM/yyyy"),
                         typeMateriau->currentText(), qteEntree->value(),
                         qteRecyclee->value(), qteRejetee->value(),
                         destination->text().trimmed(), valeur->value(),
                         direction->text().trimmed(), statut->currentText());
        if (rModif.modifier()) {
            showMessage(dialog, "Succès", "✅ Recyclage modifié avec succès !", "success");
            dialog->accept(); afficherRecyclages();
        } else {
            showMessage(dialog, "Erreur", "Impossible de modifier ce recyclage.", "error");
        }
    });
    dialog->exec();
}

// ── SUPPRESSION RECYCLAGE ────────────────────────────────────────
void MainWindow::on_bouttonsupprimerrecyclage_clicked()
{
    int row = ui->tableWidget_Recyclage->currentRow();
    if (row < 0) {
        showMessage(this, "Attention", "⚠️ Veuillez sélectionner un recyclage avant de supprimer.", "warning"); return;
    }
    QTableWidgetItem *idItem = ui->tableWidget_Recyclage->item(row, 0);
    if (!idItem || idItem->text().trimmed().isEmpty()) {
        showMessage(this, "Erreur", "Impossible de récupérer l'ID.", "error"); return;
    }
    int idRecyclage = idItem->text().toInt();
    QString typeRecyclage = ui->tableWidget_Recyclage->item(row, 2)->text();

    if (Recyclage::compterLiensRealiser(idRecyclage) > 0) {
        showMessage(this, "Suppression impossible",
                    "❌ Ce recyclage est lié à des employé(s) dans REALISER.", "error");
        return;
    }
    if (Recyclage::compterLiensFournir(idRecyclage) > 0) {
        showMessage(this, "Suppression impossible",
                    "❌ Ce recyclage est lié à des collecte(s) dans FOURNIR.", "error");
        return;
    }

    QDialog *confirm = new QDialog(this);
    confirm->setFixedSize(440, 220);
    confirm->setStyleSheet("QDialog { background-color:#1E1E2E; border-radius:14px; }");
    QVBoxLayout *lay = new QVBoxLayout(confirm); lay->setContentsMargins(0,0,0,24); lay->setSpacing(0);
    QWidget *header = new QWidget(); header->setFixedHeight(62);
    header->setStyleSheet("QWidget { background-color:#E67E22; border-top-left-radius:14px; border-top-right-radius:14px; }");
    QHBoxLayout *hLay = new QHBoxLayout(header); hLay->setContentsMargins(22,0,22,0);
    QLabel *lblTitre = new QLabel("⚠️  Confirmer la suppression");
    lblTitre->setStyleSheet("font-size:15px; font-weight:bold; color:white; background:transparent;");
    hLay->addWidget(lblTitre); lay->addWidget(header);
    QLabel *lblMsg = new QLabel("Voulez-vous vraiment supprimer ?\n♻️ " + typeRecyclage + "\n🆔 ID : " + QString::number(idRecyclage));
    lblMsg->setAlignment(Qt::AlignCenter); lblMsg->setWordWrap(true);
    lblMsg->setStyleSheet("font-size:13px; color:#C8C8D8; background:transparent; padding:16px 28px 8px 28px;");
    lay->addWidget(lblMsg); lay->addStretch();
    QHBoxLayout *btnLay = new QHBoxLayout(); btnLay->setSpacing(12); btnLay->setContentsMargins(20,0,20,0);
    QPushButton *btnNon = new QPushButton("✗ Annuler"); btnNon->setFixedHeight(40);
    btnNon->setStyleSheet("QPushButton { background:#374151; color:white; font-size:13px; font-weight:600; border:none; border-radius:8px; }");
    QPushButton *btnOui = new QPushButton("🗑️ Oui, supprimer"); btnOui->setFixedHeight(40);
    btnOui->setStyleSheet("QPushButton { background:#C0392B; color:white; font-size:13px; font-weight:600; border:none; border-radius:8px; }");
    btnLay->addWidget(btnNon); btnLay->addWidget(btnOui); lay->addLayout(btnLay);
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

Recyclage MainWindow::getRecyclageSelectionne()
{
    int row = ui->tableWidget_Recyclage->currentRow();
    if (row < 0) return Recyclage();
    return Recyclage::getById(ui->tableWidget_Recyclage->item(row, 0)->text().toInt());
}
void MainWindow::on_bouttonqrrecyclage_clicked()
{
    QList<QTableWidgetItem*> selected = ui->tableWidget_Recyclage->selectedItems();
    if (selected.isEmpty()) {
        QMessageBox::warning(this, "Sélection requise",
                             "Veuillez sélectionner un recyclage dans la liste.");
        return;
    }
    int row = selected.first()->row();
    QTableWidgetItem *idItem = ui->tableWidget_Recyclage->item(row, 0);
    if (!idItem) return;
    int id = idItem->text().toInt();
    Recyclage r = Recyclage::getById(id);
    RecyclageQR::afficherDialogQR(r, this);
}

void MainWindow::on_btnClassifier_clicked()
{
    QString typeDechet = ui->comboTypeDechet->currentText();
    QString etat       = ui->comboEtatDechet->currentText();
    ClassificationDechet cd(typeDechet, etat);
    ResultatClassification r = cd.calculerResultat();
    QString html = ClassificationDechet::formatResultatHTML(r);
    ui->labelResultatClassif->setTextFormat(Qt::RichText);
    ui->labelResultatClassif->setWordWrap(true);
    ui->labelResultatClassif->setAlignment(Qt::AlignTop | Qt::AlignLeft);
    ui->labelResultatClassif->setMinimumHeight(200);
    ui->labelResultatClassif->setText(html);
    ui->labelResultatClassif->setVisible(true);
    ui->labelResultatClassif->repaint();
}
// ================================================================
// === MODULE COLLECTE — AFFICHAGE =================================
// ================================================================

void MainWindow::afficherCollectes()
{
    QStringList headers = {
        "🆔 ID", "📅 Date Collecte", "🗑️ Type Déchet",
        "📊 Qté Collectée (kg)", "⚙️ Statut", "📏 Distance (km)", "📝 Observations"
    };
    ui->tableWidget_collecte->clear();
    ui->tableWidget_collecte->setColumnCount(headers.size());
    ui->tableWidget_collecte->setHorizontalHeaderLabels(headers);
    ui->tableWidget_collecte->setRowCount(0);
    ui->tableWidget_collecte->setSortingEnabled(false);

    ui->tableWidget_collecte->setStyleSheet(R"(
        QTableWidget { background-color:#f0f4f8; alternate-background-color:#e8edf2;
            border:none; gridline-color:transparent; font-size:13px; color:#2d3436; }
        QTableWidget::item { padding:10px 16px; border:none; border-bottom:1px solid #dfe6ed; }
        QTableWidget::item:selected { background-color:#2C5F7C; color:#ffffff; }
        QTableWidget::item:hover    { background-color:#d6e4f0; color:#1B3A57; }
        QHeaderView::section { background:qlineargradient(x1:0,y1:0,x2:0,y2:1,stop:0 #2C5F7C,stop:1 #1B3A57);
            color:#ffffff; font-weight:bold; font-size:13px; padding:12px 16px; border:none; }
    )");
    ui->tableWidget_collecte->setAlternatingRowColors(true);
    ui->tableWidget_collecte->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableWidget_collecte->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tableWidget_collecte->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableWidget_collecte->verticalHeader()->setVisible(false);
    ui->tableWidget_collecte->setShowGrid(false);

    QList<Collecte> liste = Collecte::getAll();
    int row = 0;
    for (const Collecte &col : liste) {
        ui->tableWidget_collecte->insertRow(row);
        QStringList vals = {
            QString::number(col.getId()), col.getDateCollecte(), col.getTypeDechet(),
            QString::number(col.getQuantiteCollectee()), col.getStatut(),
            QString::number(col.getDistanceTotale()), col.getObservations()
        };
        for (int c = 0; c < 7; c++) {
            QTableWidgetItem *item = new QTableWidgetItem(vals[c]);
            if (c == 0) {
                ui->tableWidget_collecte->setItem(row, c, item);
                ui->tableWidget_collecte->setColumnHidden(0, true);
                continue;
            }
            item->setTextAlignment(Qt::AlignVCenter | Qt::AlignLeft);
            ui->tableWidget_collecte->setItem(row, c, item);
        }
        ui->tableWidget_collecte->setRowHeight(row, 44);
        row++;
    }
    ui->tableWidget_collecte->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    ui->tableWidget_collecte->horizontalHeader()->setStretchLastSection(true);
    ui->tableWidget_collecte->setSortingEnabled(true);
}

// ── TRI COLLECTE ─────────────────────────────────────────────────
void MainWindow::on_bttntricollecte_clicked()
{
    QMenu *menu = new QMenu(this);
    menu->setStyleSheet(
        "QMenu{background:#FAF5F0;border:2px solid #2C5F7C;border-radius:6px;padding:8px;}"
        "QMenu::item{padding:8px 25px;color:#291C0E;border-radius:4px;}"
        "QMenu::item:selected{background:#2C5F7C;color:white;}");

    QMenu *dateMenu = menu->addMenu("📅 Date");
    QAction *dateAsc  = dateMenu->addAction("Plus ancienne → récente");
    QAction *dateDesc = dateMenu->addAction("Plus récente → ancienne");

    QMenu *statutMenu = menu->addMenu("⚙️ Statut");
    QAction *terminee  = statutMenu->addAction("Terminée");
    QAction *enCours   = statutMenu->addAction("En cours");
    QAction *planifiee = statutMenu->addAction("Planifiée");
    QAction *annulee   = statutMenu->addAction("Annulée");
    QAction *tous      = menu->addAction("🔄 Afficher Tous");

    connect(menu, &QMenu::triggered, this, [=](QAction *action) {
        QString orderBy      = "ID_collecte";
        QString filterStatut = "";
        if      (action == dateAsc)   { orderBy = "Date_collecte ASC"; }
        else if (action == dateDesc)  { orderBy = "Date_collecte DESC"; }
        else if (action == terminee)  { filterStatut = "Terminée"; }
        else if (action == enCours)   { filterStatut = "En cours"; }
        else if (action == planifiee) { filterStatut = "Planifiée"; }
        else if (action == annulee)   { filterStatut = "Annulée"; }
        else if (action == tous)      { orderBy = "ID_collecte"; }

        Collecte c;
        c.loadCollectesIntoTable(ui->tableWidget_collecte, orderBy, filterStatut);
    });

    menu->exec(ui->bttntricollecte->mapToGlobal(QPoint(0, ui->bttntricollecte->height())));
}

// ── RECHERCHE COLLECTE ───────────────────────────────────────────
void MainWindow::on_barrerecherchecollecte_textChanged(const QString &text)
{
    Collecte::rechercherDansTable(ui->tableWidget_collecte, text);
}

// ── EXPORT COLLECTE ──────────────────────────────────────────────
void MainWindow::on_bouttonexportercollecte_clicked()
{
    Collecte c;
    c.exporterListe(ui->tableWidget_collecte);
}

// ── STATISTIQUES COLLECTE ────────────────────────────────────────
void MainWindow::on_bouttonstatcollecte_clicked()
{
    Collecte c;
    c.afficherStatistiques(this);
}

// ── AJOUT COLLECTE ───────────────────────────────────────────────
void MainWindow::on_pushButton_66_clicked() { afficherWidgetAjoutCollecte(); }

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
        "QLabel { font-size:20px; font-weight:bold; color:white; padding:20px; border-radius:18px;"
        "background:qlineargradient(x1:0,y1:0,x2:0,y2:1,stop:0 #2C5F7C,stop:1 #1B3A57); }");
    containerLayout->addWidget(titre);
    containerLayout->addSpacing(20);

    QWidget *contentWidget = new QWidget();
    contentWidget->setStyleSheet("background-color:white; border-radius:15px;");
    QGridLayout *gridLayout = new QGridLayout(contentWidget);
    gridLayout->setSpacing(15); gridLayout->setContentsMargins(25, 25, 25, 25);

    QString labelStyle = "QLabel { background-color:transparent; padding:5px; font-size:13px; font-weight:600; color:#374151; }";
    QString editStyle  =
        "QLineEdit, QDateEdit, QComboBox, QDoubleSpinBox { background-color:#F9FAFB; border:1px solid #D1D5DB;"
        "border-radius:8px; padding:12px 16px; font-size:14px; color:#111827; }"
        "QLineEdit:hover, QDateEdit:hover, QComboBox:hover, QDoubleSpinBox:hover { border:1px solid #2C5F7C; }";

    QDateEdit *date = new QDateEdit(QDate::currentDate()); date->setStyleSheet(editStyle);
    date->setDisplayFormat("dd/MM/yyyy"); date->setCalendarPopup(true);
    QComboBox *typeDechet = new QComboBox(); typeDechet->setStyleSheet(editStyle);
    typeDechet->addItems({"Ménager", "Recyclable", "Organique", "Industriel", "Mixte"});
    QDoubleSpinBox *quantite = new QDoubleSpinBox(); quantite->setSuffix(" kg");
    quantite->setDecimals(2); quantite->setMaximum(9999.99); quantite->setStyleSheet(editStyle);
    QComboBox *statut = new QComboBox(); statut->setStyleSheet(editStyle);
    statut->addItems({"Planifiée", "En cours", "Terminée"});
    QDoubleSpinBox *distance = new QDoubleSpinBox(); distance->setSuffix(" km");
    distance->setDecimals(2); distance->setMaximum(9999.99); distance->setStyleSheet(editStyle);
    QLineEdit *observations = new QLineEdit(); observations->setStyleSheet(editStyle);
    observations->setPlaceholderText("Notes, zone, remarques...");

    auto addLbl = [&](const QString &t) { QLabel *l = new QLabel(t); l->setStyleSheet(labelStyle); return l; };
    gridLayout->addWidget(addLbl("📅 Date :"),                    0, 0); gridLayout->addWidget(date,         0, 1);
    gridLayout->addWidget(addLbl("🗑️ Type de Déchet :"),         1, 0); gridLayout->addWidget(typeDechet,   1, 1);
    gridLayout->addWidget(addLbl("⚖️ Quantité collectée (kg) :"),2, 0); gridLayout->addWidget(quantite,     2, 1);
    gridLayout->addWidget(addLbl("📊 Statut :"),                  0, 2); gridLayout->addWidget(statut,       0, 3);
    gridLayout->addWidget(addLbl("📏 Distance (km) :"),           1, 2); gridLayout->addWidget(distance,     1, 3);
    gridLayout->addWidget(addLbl("📝 Observations :"),            2, 2); gridLayout->addWidget(observations, 2, 3);
    containerLayout->addWidget(contentWidget);
    containerLayout->addSpacing(15);

    QHBoxLayout *btnLayout = new QHBoxLayout(); btnLayout->setSpacing(15);
    QPushButton *annuler = new QPushButton("✗ Annuler"); annuler->setMinimumHeight(50);
    annuler->setStyleSheet("QPushButton { background-color:#E5E7EB; color:#374151; font-size:15px; font-weight:600; border:none; border-radius:8px; padding:12px 30px; }");
    QPushButton *ajouter = new QPushButton("✓ Ajouter"); ajouter->setMinimumHeight(50);
    ajouter->setStyleSheet(
        "QPushButton { background:qlineargradient(x1:0,y1:0,x2:0,y2:1,stop:0 #2C5F7C,stop:1 #1B3A57);"
        "color:white; font-size:15px; font-weight:600; border:none; border-radius:8px; padding:12px 30px; }");
    btnLayout->addWidget(annuler); btnLayout->addWidget(ajouter);
    containerLayout->addLayout(btnLayout);
    mainLayout->addWidget(container);

    connect(annuler, &QPushButton::clicked, dialog, &QDialog::reject);
    connect(ajouter, &QPushButton::clicked, this, [=]() {
        if (quantite->value() <= 0.0) {
            showMessage(dialog, "Erreur", "La quantité collectée doit être supérieure à 0 !", "error"); return;
        }
        Collecte c(0, date->date().toString("dd/MM/yyyy"), typeDechet->currentText(),
                   quantite->value(), statut->currentText(), distance->value(),
                   observations->text().trimmed());
        if (c.ajouter()) {
            showMessage(dialog, "Succès", "✅ Collecte ajoutée avec succès !", "success");
            afficherCollectes(); dialog->accept();
        } else {
            showMessage(dialog, "Erreur", "Impossible d'ajouter cette collecte.", "error");
        }
    });
    dialog->exec();
}

// ── MODIFICATION COLLECTE ────────────────────────────────────────
void MainWindow::on_bouttonmodifiercollecte_clicked()
{
    int row = ui->tableWidget_collecte->currentRow();
    if (row < 0) {
        showMessage(this, "Attention", "⚠️ Veuillez sélectionner une collecte avant de modifier.", "warning"); return;
    }
    QTableWidgetItem *idItem = ui->tableWidget_collecte->item(row, 0);
    if (!idItem || idItem->text().trimmed().isEmpty()) {
        showMessage(this, "Erreur", "Impossible de récupérer l'ID.", "error"); return;
    }
    afficherWidgetModifierCollecte(idItem->text().toInt());
}

void MainWindow::afficherWidgetModifierCollecte(int idCollecte)
{
    Collecte c = Collecte::getById(idCollecte);
    if (c.getId() == 0) {
        showMessage(this, "Erreur", "Collecte introuvable.", "error"); return;
    }

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
        "QLabel { font-size:18px; font-weight:bold; color:white; padding:20px; border-radius:18px;"
        "background:qlineargradient(x1:0,y1:0,x2:0,y2:1,stop:0 #1A7A4A,stop:1 #0F4D2E); }");
    containerLayout->addWidget(titre);
    containerLayout->addSpacing(20);

    QWidget *contentWidget = new QWidget();
    contentWidget->setStyleSheet("background-color:white; border-radius:15px;");
    QGridLayout *gridLayout = new QGridLayout(contentWidget);
    gridLayout->setSpacing(15); gridLayout->setContentsMargins(25, 25, 25, 25);

    QString labelStyle = "QLabel { background-color:transparent; padding:5px; font-size:13px; font-weight:600; color:#374151; }";
    QString editStyle  =
        "QLineEdit, QDateEdit, QComboBox, QDoubleSpinBox { background-color:#F9FAFB; border:1px solid #D1D5DB;"
        "border-radius:8px; padding:12px 16px; font-size:14px; color:#111827; }"
        "QLineEdit:hover, QDateEdit:hover, QComboBox:hover, QDoubleSpinBox:hover { border:1px solid #1A7A4A; }";

    QDateEdit *dateCollecte = new QDateEdit(); dateCollecte->setStyleSheet(editStyle);
    dateCollecte->setDisplayFormat("dd/MM/yyyy"); dateCollecte->setCalendarPopup(true);
    QDate d = QDate::fromString(c.getDateCollecte(), "dd/MM/yyyy");
    if (!d.isValid()) d = QDate::currentDate();
    dateCollecte->setDate(d);

    QComboBox *typeDechet = new QComboBox(); typeDechet->setStyleSheet(editStyle);
    typeDechet->addItems({"Ménager", "Recyclable", "Organique", "Industriel", "Mixte"});
    typeDechet->setCurrentText(c.getTypeDechet());

    QDoubleSpinBox *quantite = new QDoubleSpinBox(); quantite->setSuffix(" kg");
    quantite->setDecimals(2); quantite->setMaximum(999999.99); quantite->setStyleSheet(editStyle);
    quantite->setValue(c.getQuantiteCollectee());

    QComboBox *statut = new QComboBox(); statut->setStyleSheet(editStyle);
    statut->addItems({"Planifiée", "En cours", "Terminée", "Annulée"});
    statut->setCurrentText(c.getStatut());

    QDoubleSpinBox *distance = new QDoubleSpinBox(); distance->setSuffix(" km");
    distance->setDecimals(2); distance->setMaximum(99999.99); distance->setStyleSheet(editStyle);
    distance->setValue(c.getDistanceTotale());

    QLineEdit *observations = new QLineEdit(c.getObservations()); observations->setStyleSheet(editStyle);

    auto addLbl = [&](const QString &t) { QLabel *l = new QLabel(t); l->setStyleSheet(labelStyle); return l; };
    gridLayout->addWidget(addLbl("📅 Date de Collecte :"), 0, 0); gridLayout->addWidget(dateCollecte, 0, 1);
    gridLayout->addWidget(addLbl("🗑️ Type de Déchet :"),  1, 0); gridLayout->addWidget(typeDechet,   1, 1);
    gridLayout->addWidget(addLbl("⚖️ Quantité (kg) :"),   2, 0); gridLayout->addWidget(quantite,     2, 1);
    gridLayout->addWidget(addLbl("📊 Statut :"),           0, 2); gridLayout->addWidget(statut,       0, 3);
    gridLayout->addWidget(addLbl("📏 Distance (km) :"),    1, 2); gridLayout->addWidget(distance,     1, 3);
    gridLayout->addWidget(addLbl("📝 Observations :"),     2, 2); gridLayout->addWidget(observations, 2, 3);
    containerLayout->addWidget(contentWidget);
    containerLayout->addSpacing(15);

    QHBoxLayout *btnLayout = new QHBoxLayout(); btnLayout->setSpacing(15);
    QPushButton *annuler = new QPushButton("✗ Annuler"); annuler->setMinimumHeight(50);
    annuler->setStyleSheet("QPushButton { background-color:#E5E7EB; color:#374151; font-size:15px; font-weight:600; border:none; border-radius:8px; padding:12px 30px; }");
    QPushButton *enregistrer = new QPushButton("✓ Enregistrer"); enregistrer->setMinimumHeight(50);
    enregistrer->setStyleSheet(
        "QPushButton { background:qlineargradient(x1:0,y1:0,x2:0,y2:1,stop:0 #1A7A4A,stop:1 #0F4D2E);"
        "color:white; font-size:15px; font-weight:600; border:none; border-radius:8px; padding:12px 30px; }");
    btnLayout->addWidget(annuler); btnLayout->addWidget(enregistrer);
    containerLayout->addLayout(btnLayout);
    mainLayout->addWidget(container);

    connect(annuler, &QPushButton::clicked, dialog, &QDialog::reject);
    connect(enregistrer, &QPushButton::clicked, this, [=]() {
        if (quantite->value() <= 0.0) {
            showMessage(dialog, "Erreur", "La quantité doit être supérieure à 0 !", "error"); return;
        }
        Collecte cModif(idCollecte, dateCollecte->date().toString("dd/MM/yyyy"),
                        typeDechet->currentText(), quantite->value(),
                        statut->currentText(), distance->value(),
                        observations->text().trimmed());
        if (cModif.modifier()) {
            showMessage(dialog, "Succès", "✅ Collecte modifiée avec succès !", "success");
            dialog->accept(); afficherCollectes();
        } else {
            showMessage(dialog, "Erreur", "Impossible de modifier cette collecte.", "error");
        }
    });
    dialog->exec();
}

// ── SUPPRESSION COLLECTE ─────────────────────────────────────────
void MainWindow::on_bouttonsupprimercollecte_clicked()
{
    int row = ui->tableWidget_collecte->currentRow();
    if (row < 0) {
        showMessage(this, "Attention", "⚠️ Veuillez sélectionner une collecte avant de supprimer.", "warning"); return;
    }
    QTableWidgetItem *idItem = ui->tableWidget_collecte->item(row, 0);
    if (!idItem || idItem->text().trimmed().isEmpty()) {
        showMessage(this, "Erreur", "Impossible de récupérer l'ID.", "error"); return;
    }
    int idCollecte = idItem->text().toInt();
    QString dateCollecte = ui->tableWidget_collecte->item(row, 1)->text();

    if (Collecte::compterLiensConsommer(idCollecte) > 0) {
        showMessage(this, "Suppression impossible",
                    "❌ Cette collecte est liée à des conteneur(s) dans CONSOMMER.", "error");
        return;
    }
    if (Collecte::compterLiensFournir(idCollecte) > 0) {
        showMessage(this, "Suppression impossible",
                    "❌ Cette collecte est liée à des recyclage(s) dans FOURNIR.", "error");
        return;
    }

    QDialog *confirm = new QDialog(this);
    confirm->setFixedSize(440, 220);
    confirm->setStyleSheet("QDialog { background-color:#1E1E2E; border-radius:14px; }");
    QVBoxLayout *lay = new QVBoxLayout(confirm); lay->setContentsMargins(0,0,0,24); lay->setSpacing(0);
    QWidget *header = new QWidget(); header->setFixedHeight(62);
    header->setStyleSheet("QWidget { background-color:#E67E22; border-top-left-radius:14px; border-top-right-radius:14px; }");
    QHBoxLayout *hLay = new QHBoxLayout(header); hLay->setContentsMargins(22,0,22,0);
    QLabel *lblTitre = new QLabel("⚠️  Confirmer la suppression");
    lblTitre->setStyleSheet("font-size:15px; font-weight:bold; color:white; background:transparent;");
    hLay->addWidget(lblTitre); lay->addWidget(header);
    QLabel *lblMsg = new QLabel("Voulez-vous vraiment supprimer ?\n📅 " + dateCollecte + "\n🆔 ID : " + QString::number(idCollecte));
    lblMsg->setAlignment(Qt::AlignCenter); lblMsg->setWordWrap(true);
    lblMsg->setStyleSheet("font-size:13px; color:#C8C8D8; background:transparent; padding:16px 28px 8px 28px;");
    lay->addWidget(lblMsg); lay->addStretch();
    QHBoxLayout *btnLay = new QHBoxLayout(); btnLay->setSpacing(12); btnLay->setContentsMargins(20,0,20,0);
    QPushButton *btnNon = new QPushButton("✗ Annuler"); btnNon->setFixedHeight(40);
    btnNon->setStyleSheet("QPushButton { background:#374151; color:white; font-size:13px; font-weight:600; border:none; border-radius:8px; }");
    QPushButton *btnOui = new QPushButton("🗑️ Oui, supprimer"); btnOui->setFixedHeight(40);
    btnOui->setStyleSheet("QPushButton { background:#C0392B; color:white; font-size:13px; font-weight:600; border:none; border-radius:8px; }");
    btnLay->addWidget(btnNon); btnLay->addWidget(btnOui); lay->addLayout(btnLay);
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

Collecte MainWindow::getCollecteSelectionnee()
{
    int row = ui->tableWidget_collecte->currentRow();
    if (row < 0) return Collecte();
    return Collecte::getById(ui->tableWidget_collecte->item(row, 0)->text().toInt());
}

// ================================================================
// === MODULE CONTENEUR — AFFICHAGE ================================
// ================================================================
void MainWindow::on_CONTENEUR_clicked()
{
    currentModule = "conteneur";
    ui->stackedWidget_2->setCurrentIndex(6);
    afficherConteneurs();

    // ── Bouton Prédire — inséré une seule fois après rendu complet ──
    QTimer::singleShot(0, this, [this]() {
        // Guard: ne créer qu'une seule fois
        if (ui->bouttonstatconteneur->parentWidget()
                ->findChild<QPushButton*>("bouttonpredictionconteneur"))
            return;

        QPushButton *btnPrediction = new QPushButton("🔮 Prédire");
        btnPrediction->setObjectName("bouttonpredictionconteneur");
        btnPrediction->setCursor(Qt::PointingHandCursor);
        btnPrediction->setFixedHeight(ui->bouttonstatconteneur->height());
        btnPrediction->setMinimumWidth(120);
        btnPrediction->setStyleSheet(
            "QPushButton {"
            "  background: qlineargradient(x1:0,y1:0,x2:1,y2:0,"
            "    stop:0 #0D3349, stop:1 #1B5E82);"
            "  color: #A0D2FF; font-size: 13px; font-weight: 700;"
            "  border: 1px solid rgba(100,180,255,0.35);"
            "  border-radius: 8px; padding: 8px 18px;"
            "}"
            "QPushButton:hover {"
            "  background: qlineargradient(x1:0,y1:0,x2:1,y2:0,"
            "    stop:0 #1B4F6E, stop:1 #2C7AAA);"
            "  color: #E0F4FF;"
            "  border: 1px solid rgba(100,180,255,0.6);"
            "}"
            "QPushButton:pressed { background: #0D3349; }"
        );
        connect(btnPrediction, &QPushButton::clicked,
                this, &MainWindow::on_bouttonpredictionconteneur_clicked);

        // Insérer juste après bouttonstatconteneur dans son layout
        QWidget *parentW = ui->bouttonstatconteneur->parentWidget();
        QBoxLayout *boxL = qobject_cast<QBoxLayout*>(parentW ? parentW->layout() : nullptr);
        if (boxL) {
            int idx = boxL->indexOf(ui->bouttonstatconteneur);
            boxL->insertWidget(idx + 1, btnPrediction);
        }
    });
}
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

    ui->tableWidget_Conteneur->setStyleSheet(R"(
        QTableWidget { background-color:#f0f4f8; alternate-background-color:#e8edf2;
            border:none; gridline-color:transparent; font-size:13px; color:#2d3436; }
        QTableWidget::item { padding:10px 16px; border:none; border-bottom:1px solid #dfe6ed; }
        QTableWidget::item:selected { background-color:#2C5F7C; color:#ffffff; }
        QTableWidget::item:hover    { background-color:#d6e4f0; color:#1B3A57; }
        QHeaderView::section { background:qlineargradient(x1:0,y1:0,x2:0,y2:1,stop:0 #2C5F7C,stop:1 #1B3A57);
            color:#ffffff; font-weight:bold; padding:12px; border:none; }
    )");
    ui->tableWidget_Conteneur->setAlternatingRowColors(true);
    ui->tableWidget_Conteneur->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableWidget_Conteneur->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tableWidget_Conteneur->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableWidget_Conteneur->verticalHeader()->setVisible(false);
    ui->tableWidget_Conteneur->setShowGrid(false);

    QList<Conteneur> liste = Conteneur::getAll();
    int row = 0;
    for (const Conteneur &c : liste) {
        ui->tableWidget_Conteneur->insertRow(row);
        QStringList vals = {
            QString::number(c.getId()), QString::number(c.getCapacite()),
            c.getTypePropriete(), c.getAdresseComplete(), c.getLocalisationGPS(),
            c.getAccepteMenager(), c.getAccepteRecyclable(), c.getAccepteOrganique(),
            c.getAccepteIndustriel(), c.getEtat(), c.getDateDerniereCollecte()
        };
        for (int col = 0; col < 11; col++) {
            QTableWidgetItem *item = new QTableWidgetItem(vals[col]);
            if (col == 0) {
                ui->tableWidget_Conteneur->setItem(row, col, item);
                ui->tableWidget_Conteneur->setColumnHidden(0, true);
                continue;
            }
            item->setTextAlignment(Qt::AlignVCenter | Qt::AlignLeft);
            ui->tableWidget_Conteneur->setItem(row, col, item);
        }
        ui->tableWidget_Conteneur->setRowHeight(row, 44);
        row++;
    }
    ui->tableWidget_Conteneur->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    ui->tableWidget_Conteneur->horizontalHeader()->setStretchLastSection(true);
    ui->tableWidget_Conteneur->setSortingEnabled(true);
}

// ── TRI CONTENEUR ────────────────────────────────────────────────
void MainWindow::on_btntriconteneur_clicked()
{
    QMenu *menu = new QMenu(this);
    menu->setStyleSheet(
        "QMenu{background:#FAF5F0;border:2px solid #2C5F7C;border-radius:6px;padding:8px;}"
        "QMenu::item{padding:8px 25px;color:#291C0E;border-radius:4px;}"
        "QMenu::item:selected{background:#2C5F7C;color:white;}");

    QMenu *alphaMenu = menu->addMenu("🔤 Alphabétique (Adresse)");
    QAction *alphaAsc  = alphaMenu->addAction("A → Z");
    QAction *alphaDesc = alphaMenu->addAction("Z → A");

    QMenu *etatMenu = menu->addMenu("⚙️ État");
    QAction *operationnel = etatMenu->addAction("Opérationnel");
    QAction *maintenance  = etatMenu->addAction("En maintenance");
    QAction *horsService  = etatMenu->addAction("Hors service");
    QAction *tous         = menu->addAction("🔄 Afficher Tous");

    connect(menu, &QMenu::triggered, this, [=](QAction *action) {
        QString orderBy    = "ID_conteneur";
        QString filterEtat = "";
        if      (action == alphaAsc)     { orderBy = "Adresse_complete ASC"; }
        else if (action == alphaDesc)    { orderBy = "Adresse_complete DESC"; }
        else if (action == operationnel) { filterEtat = "Opérationnel"; }
        else if (action == maintenance)  { filterEtat = "En maintenance"; }
        else if (action == horsService)  { filterEtat = "Hors service"; }
        else if (action == tous)         { orderBy = "ID_conteneur"; }

        Conteneur c;
        c.loadConteneursIntoTable(ui->tableWidget_Conteneur, orderBy, filterEtat);
    });

    menu->exec(ui->btntriconteneur->mapToGlobal(QPoint(0, ui->btntriconteneur->height())));

}

// ── RECHERCHE CONTENEUR ──────────────────────────────────────────
void MainWindow::on_barrerechercheconteneur_textChanged(const QString &text)
{
    Conteneur::rechercherDansTable(ui->tableWidget_Conteneur, text);
}

// ── EXPORT CONTENEUR ─────────────────────────────────────────────
void MainWindow::on_bouttonexporterconteneur_clicked()
{
    Conteneur c;
    c.exporterListe(ui->tableWidget_Conteneur);
}

// ── STATISTIQUES CONTENEUR ───────────────────────────────────────
void MainWindow::on_bouttonstatconteneur_clicked()
{
    Conteneur c;
    c.afficherStatistiques(this);
}
void MainWindow::on_bouttonpredictionconteneur_clicked()
{
    PredictionRemplissage pred;
    pred.afficherPredictions(this);
}

// ── AJOUT CONTENEUR ──────────────────────────────────────────────
void MainWindow::on_bouttonajouterconteneur_clicked()
{
    QDialog *dialog = new QDialog(this);
    dialog->setWindowTitle("➕ Ajouter un Conteneur");
    dialog->setMinimumSize(520, 680);
    dialog->setStyleSheet("QDialog { background:#F8FAFC; }");

    QVBoxLayout *mainLayout = new QVBoxLayout(dialog);
    mainLayout->setContentsMargins(20, 20, 20, 20);
    mainLayout->setSpacing(12);

    // --- En-tête ---
    QWidget *header = new QWidget();
    header->setFixedHeight(56);
    header->setStyleSheet(
        "QWidget { background:qlineargradient(x1:0,y1:0,x2:1,y2:0,"
        "stop:0 #1B3A57,stop:1 #2C5F7C); border-radius:10px; }");
    QHBoxLayout *hLay = new QHBoxLayout(header);
    hLay->setContentsMargins(18, 0, 18, 0);
    QLabel *hTitre = new QLabel("🗑️  Nouveau Conteneur");
    hTitre->setStyleSheet(
        "font-size:16px; font-weight:bold; color:white; background:transparent;");
    hLay->addWidget(hTitre);
    mainLayout->addWidget(header);

    // --- Zone de défilement ---
    QScrollArea *scrollArea = new QScrollArea();
    scrollArea->setWidgetResizable(true);
    scrollArea->setFrameShape(QFrame::NoFrame);
    scrollArea->setStyleSheet("QScrollArea { background:transparent; }");

    QWidget *scrollWidget = new QWidget();
    scrollWidget->setStyleSheet("QWidget { background:transparent; }");
    QVBoxLayout *scrollLayout = new QVBoxLayout(scrollWidget);
    scrollLayout->setContentsMargins(4, 4, 4, 4);
    scrollLayout->setSpacing(6);

    // Style commun aux champs
    const QString editStyle =
        "QLineEdit, QDoubleSpinBox, QComboBox, QDateEdit {"
        "  background:#FFFFFF; border:1px solid #D1D5DB; border-radius:8px;"
        "  padding:8px 12px; font-size:13px; color:#1F2937; }"
        "QLineEdit:focus, QDoubleSpinBox:focus, QComboBox:focus, QDateEdit:focus {"
        "  border:2px solid #2C5F7C; }";
    const QString labelStyle =
        "QLabel { font-size:12px; font-weight:600; color:#374151; "
        "background:transparent; margin-top:4px; }";

    auto addLabel = [&](const QString &txt) {
        QLabel *l = new QLabel(txt); l->setStyleSheet(labelStyle);
        scrollLayout->addWidget(l);
    };

    // Capacité
    QDoubleSpinBox *capacite = new QDoubleSpinBox(); capacite->setStyleSheet(editStyle);
    capacite->setRange(1.0, 100000.0); capacite->setSuffix(" L"); capacite->setDecimals(1);
    addLabel("📦 Capacité (litres) *"); scrollLayout->addWidget(capacite);

    // Type propriété
    QComboBox *typePropriete = new QComboBox(); typePropriete->setStyleSheet(editStyle);
    typePropriete->addItems({"Public", "Privé", "Municipal", "Industriel"});
    addLabel("🏢 Type de Propriété *"); scrollLayout->addWidget(typePropriete);

    // Adresse
    QLineEdit *adresse = new QLineEdit(); adresse->setStyleSheet(editStyle);
    adresse->setPlaceholderText("Ex: 12 rue de la Liberté, Tunis");
    addLabel("📍 Adresse *"); scrollLayout->addWidget(adresse);

    // GPS
    QLineEdit *gps = new QLineEdit(); gps->setStyleSheet(editStyle);
    gps->setPlaceholderText("Ex: 36.8190, 10.1658");
    addLabel("🌐 Localisation GPS"); scrollLayout->addWidget(gps);

    // Cases à cocher — déchets acceptés
    addLabel("♻️ Types de déchets acceptés");
    QWidget *chkWidget = new QWidget();
    chkWidget->setStyleSheet("background:transparent;");
    QGridLayout *chkGrid = new QGridLayout(chkWidget);
    chkGrid->setContentsMargins(0, 4, 0, 4); chkGrid->setSpacing(8);
    QCheckBox *chkMenager    = new QCheckBox("🏠 Ménager");
    QCheckBox *chkRecyclable = new QCheckBox("♻️ Recyclable");
    QCheckBox *chkOrganique  = new QCheckBox("🌱 Organique");
    QCheckBox *chkIndustriel = new QCheckBox("🏭 Industriel");
    QString chkStyle = "QCheckBox { font-size:12px; color:#374151; background:transparent; }";
    chkMenager->setStyleSheet(chkStyle); chkRecyclable->setStyleSheet(chkStyle);
    chkOrganique->setStyleSheet(chkStyle); chkIndustriel->setStyleSheet(chkStyle);
    chkGrid->addWidget(chkMenager,    0, 0); chkGrid->addWidget(chkRecyclable, 0, 1);
    chkGrid->addWidget(chkOrganique,  1, 0); chkGrid->addWidget(chkIndustriel, 1, 1);
    scrollLayout->addWidget(chkWidget);

    // État
    QComboBox *etat = new QComboBox(); etat->setStyleSheet(editStyle);
    etat->addItems({"Opérationnel", "En maintenance", "Hors service"});
    addLabel("⚙️ État *"); scrollLayout->addWidget(etat);

    // ── NOUVEAU : Zone ───────────────────────────────────────────
    QComboBox *zone = new QComboBox(); zone->setStyleSheet(editStyle);
    zone->addItems({"centre", "residentiel", "industriel"});
    zone->setCurrentText("residentiel");   // valeur par défaut
    zone->setToolTip(
        "centre      : zone urbaine dense — remplissage ×1.5\n"
        "residentiel : zone résidentielle — référence ×1.0\n"
        "industriel  : zone industrielle  — remplissage ×0.8"
        );
    addLabel("📍 Zone géographique *"); scrollLayout->addWidget(zone);
    // ─────────────────────────────────────────────────────────────

    // Date dernière collecte
    QDateEdit *dateDC = new QDateEdit(); dateDC->setStyleSheet(editStyle);
    dateDC->setDisplayFormat("dd/MM/yyyy"); dateDC->setCalendarPopup(true);
    dateDC->setDate(QDate::currentDate());
    addLabel("📅 Date Dernière Collecte"); scrollLayout->addWidget(dateDC);

    scrollArea->setWidget(scrollWidget);
    mainLayout->addWidget(scrollArea, 1);
    mainLayout->addSpacing(8);

    // --- Boutons ---
    QHBoxLayout *btnLayout = new QHBoxLayout(); btnLayout->setSpacing(12);
    QPushButton *annuler = new QPushButton("✗ Annuler"); annuler->setMinimumHeight(48);
    annuler->setStyleSheet(
        "QPushButton { background:#E5E7EB; color:#374151; font-size:14px; "
        "font-weight:600; border:none; border-radius:8px; }");
    QPushButton *enregistrer = new QPushButton("✓ Enregistrer"); enregistrer->setMinimumHeight(48);
    enregistrer->setStyleSheet(
        "QPushButton { background:qlineargradient(x1:0,y1:0,x2:0,y2:1,"
        "stop:0 #1A7A4A,stop:1 #0F4D2E); color:white; font-size:14px; "
        "font-weight:600; border:none; border-radius:8px; }");
    btnLayout->addWidget(annuler); btnLayout->addWidget(enregistrer);
    mainLayout->addLayout(btnLayout);

    connect(annuler,     &QPushButton::clicked, dialog, &QDialog::reject);
    connect(enregistrer, &QPushButton::clicked, this,   [=]() {
        if (adresse->text().trimmed().isEmpty()) {
            showMessage(dialog, "Erreur", "L'adresse est obligatoire !", "error"); return;
        }
        if (capacite->value() <= 0.0) {
            showMessage(dialog, "Erreur", "La capacité doit être > 0 !", "error"); return;
        }
        // Construction avec le nouveau paramètre zone (12ème argument)
        Conteneur ct(0,
                     capacite->value(),
                     typePropriete->currentText(),
                     adresse->text().trimmed(),
                     gps->text().trimmed(),
                     chkMenager->isChecked()    ? "Oui" : "Non",
                     chkRecyclable->isChecked() ? "Oui" : "Non",
                     chkOrganique->isChecked()  ? "Oui" : "Non",
                     chkIndustriel->isChecked() ? "Oui" : "Non",
                     etat->currentText(),
                     dateDC->date().toString("dd/MM/yyyy"),
                     zone->currentText());    // ← zone
        if (ct.ajouter()) {
            showMessage(dialog, "Succès", "✅ Conteneur ajouté avec succès !", "success");
            dialog->accept(); afficherConteneurs();
        } else {
            showMessage(dialog, "Erreur", "Impossible d'ajouter ce conteneur.", "error");
        }
    });

    dialog->exec();
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
        "QLabel { font-size:20px; font-weight:bold; color:white; padding:20px; border-radius:18px;"
        "background:qlineargradient(x1:0,y1:0,x2:0,y2:1,stop:0 #2C5F7C,stop:1 #1B3A57); }");
    containerLayout->addWidget(titre);
    containerLayout->addSpacing(20);

    QScrollArea *scrollArea = new QScrollArea(); scrollArea->setWidgetResizable(true);
    scrollArea->setFrameShape(QFrame::NoFrame);
    QWidget *scrollWidget = new QWidget();
    scrollWidget->setStyleSheet("background-color:white; border-radius:15px;");
    QVBoxLayout *scrollLayout = new QVBoxLayout(scrollWidget);
    scrollLayout->setSpacing(20); scrollLayout->setContentsMargins(25, 25, 25, 25);

    QString labelStyle = "QLabel { background-color:transparent; padding:5px; font-size:13px; font-weight:600; color:#374151; }";
    QString editStyle  =
        "QLineEdit, QDateEdit, QDoubleSpinBox, QComboBox { background-color:#F9FAFB; border:1px solid #D1D5DB;"
        "border-radius:8px; padding:12px 16px; font-size:14px; color:#111827; }"
        "QLineEdit:hover, QDateEdit:hover, QDoubleSpinBox:hover, QComboBox:hover { border:1px solid #2C5F7C; }";
    QString checkStyle =
        "QCheckBox { font-size:14px; color:#111827; padding:8px; }"
        "QCheckBox::indicator { width:20px; height:20px; border-radius:4px; border:2px solid #D1D5DB; }"
        "QCheckBox::indicator:checked { background-color:#2C5F7C; border:2px solid #2C5F7C; }";

    auto addLabel = [&](const QString &t) {
        QLabel *l = new QLabel(t); l->setStyleSheet(labelStyle); scrollLayout->addWidget(l);
    };

    QDoubleSpinBox *capacite = new QDoubleSpinBox(); capacite->setSuffix(" L");
    capacite->setDecimals(2); capacite->setMinimum(0.0); capacite->setMaximum(999999.99);
    capacite->setStyleSheet(editStyle);
    addLabel("📦 Capacité (L) *"); scrollLayout->addWidget(capacite);

    QLineEdit *localisation = new QLineEdit(); localisation->setStyleSheet(editStyle);
    addLabel("📍 Localisation GPS *"); scrollLayout->addWidget(localisation);

    QLineEdit *adresseComplete = new QLineEdit(); adresseComplete->setStyleSheet(editStyle);
    addLabel("🏠 Adresse complète *"); scrollLayout->addWidget(adresseComplete);

    QComboBox *typePropriete = new QComboBox(); typePropriete->setStyleSheet(editStyle);
    typePropriete->addItems({"Public", "Privé", "Mixte"});
    addLabel("🏢 Type de Propriété"); scrollLayout->addWidget(typePropriete);

    addLabel("♻️ Déchets Acceptés :");
    QWidget *checkWidget = new QWidget();
    checkWidget->setStyleSheet("background-color:#F9FAFB; border-radius:8px; border:1px solid #D1D5DB;");
    QGridLayout *checkLayout = new QGridLayout(checkWidget);
    checkLayout->setContentsMargins(15, 10, 15, 10); checkLayout->setSpacing(10);

    QCheckBox *chkMenager    = new QCheckBox("🏠 Ménager");    chkMenager->setChecked(true);
    QCheckBox *chkRecyclable = new QCheckBox("♻️ Recyclable"); chkRecyclable->setChecked(true);
    QCheckBox *chkOrganique  = new QCheckBox("🌿 Organique");
    QCheckBox *chkIndustriel = new QCheckBox("🏭 Industriel");
    for (auto *chk : {chkMenager, chkRecyclable, chkOrganique, chkIndustriel}) chk->setStyleSheet(checkStyle);
    checkLayout->addWidget(chkMenager, 0, 0); checkLayout->addWidget(chkRecyclable, 0, 1);
    checkLayout->addWidget(chkOrganique, 1, 0); checkLayout->addWidget(chkIndustriel, 1, 1);
    scrollLayout->addWidget(checkWidget);

    QComboBox *etatConteneur = new QComboBox(); etatConteneur->setStyleSheet(editStyle);
    etatConteneur->addItems({"Opérationnel", "En maintenance", "Hors service"});
    addLabel("✅ État du Conteneur :"); scrollLayout->addWidget(etatConteneur);

    QDateEdit *dateDerniereCollecte = new QDateEdit(QDate::currentDate());
    dateDerniereCollecte->setStyleSheet(editStyle);
    dateDerniereCollecte->setDisplayFormat("dd/MM/yyyy"); dateDerniereCollecte->setCalendarPopup(true);
    addLabel("📅 Date Dernière Collecte :"); scrollLayout->addWidget(dateDerniereCollecte);

    scrollArea->setWidget(scrollWidget);
    containerLayout->addWidget(scrollArea);
    containerLayout->addSpacing(10);

    QHBoxLayout *btnLayout = new QHBoxLayout(); btnLayout->setSpacing(15);
    QPushButton *annuler = new QPushButton("✗ Annuler"); annuler->setMinimumHeight(50);
    annuler->setStyleSheet("QPushButton { background-color:#E5E7EB; color:#374151; font-size:15px; font-weight:600; border:none; border-radius:8px; padding:12px 30px; }");
    QPushButton *ajouter = new QPushButton("✓ Ajouter"); ajouter->setMinimumHeight(50);
    ajouter->setStyleSheet(
        "QPushButton { background:qlineargradient(x1:0,y1:0,x2:0,y2:1,stop:0 #2C5F7C,stop:1 #1B3A57);"
        "color:white; font-size:15px; font-weight:600; border:none; border-radius:8px; padding:12px 30px; }");
    btnLayout->addWidget(annuler); btnLayout->addWidget(ajouter);
    containerLayout->addLayout(btnLayout);
    mainLayout->addWidget(container);

    connect(annuler, &QPushButton::clicked, dialog, &QDialog::reject);
    connect(ajouter, &QPushButton::clicked, this, [=]() {
        if (localisation->text().trimmed().isEmpty() || adresseComplete->text().trimmed().isEmpty()) {
            showMessage(dialog, "Champs manquants", "Merci de remplir tous les champs obligatoires.", "warning"); return;
        }
        if (capacite->value() <= 0.0) {
            showMessage(dialog, "Erreur", "La capacité doit être supérieure à 0 !", "error"); return;
        }
        QString gpsText = localisation->text().trimmed();
        QStringList gpsParts = gpsText.split(',');
        if (gpsParts.size() != 2) {
            showMessage(dialog, "GPS invalide",
                        "Format attendu : latitude,longitude\nExemple : 36.7625,10.2242", "error");
            return;
        }
        bool okLat, okLng;
        double lat = gpsParts[0].toDouble(&okLat);
        double lng = gpsParts[1].toDouble(&okLng);
        if (!okLat || !okLng || lat < 30.0 || lat > 37.5 || lng < 7.5 || lng > 11.5) {
            showMessage(dialog, "GPS invalide",
                        "Coordonnées hors de la Tunisie.\nLatitude: 30-37.5, Longitude: 7.5-11.5", "error");
            return;
        }
        Conteneur ct(0, capacite->value(), typePropriete->currentText(),
                     adresseComplete->text().trimmed(), localisation->text().trimmed(),
                     chkMenager->isChecked()    ? "Oui" : "Non",
                     chkRecyclable->isChecked() ? "Oui" : "Non",
                     chkOrganique->isChecked()  ? "Oui" : "Non",
                     chkIndustriel->isChecked() ? "Oui" : "Non",
                     etatConteneur->currentText(),
                     dateDerniereCollecte->date().toString("dd/MM/yyyy"));
        if (ct.ajouter()) {
            showMessage(dialog, "Succès", "✅ Conteneur ajouté avec succès !", "success");
            afficherConteneurs(); dialog->accept();
        } else {
            showMessage(dialog, "Erreur", "Impossible d'ajouter ce conteneur.", "error");
        }
    });
    dialog->exec();
}

// ── MODIFICATION CONTENEUR ───────────────────────────────────────
void MainWindow::on_bouttonmodifierconteneur_clicked()
{
    int row = ui->tableWidget_Conteneur->currentRow();
    if (row < 0) {
        showMessage(this, "Attention",
                    "⚠️ Veuillez sélectionner un conteneur.", "warning"); return;
    }
    QTableWidgetItem *idItem = ui->tableWidget_Conteneur->item(row, 0);
    if (!idItem || idItem->text().trimmed().isEmpty()) {
        showMessage(this, "Erreur", "Impossible de récupérer l'ID.", "error"); return;
    }
    int idConteneur = idItem->text().toInt();
    Conteneur ct = Conteneur::getById(idConteneur);

    QDialog *dialog = new QDialog(this);
    dialog->setWindowTitle("✏️ Modifier le Conteneur #" + QString::number(idConteneur));
    dialog->setMinimumSize(520, 700);
    dialog->setStyleSheet("QDialog { background:#F8FAFC; }");

    QVBoxLayout *mainLayout   = new QVBoxLayout(dialog);
    QWidget     *container    = new QWidget();
    QVBoxLayout *containerLayout = new QVBoxLayout(container);
    mainLayout->setContentsMargins(20, 20, 20, 20); mainLayout->setSpacing(12);
    containerLayout->setContentsMargins(0, 0, 0, 0); containerLayout->setSpacing(12);

    QWidget *header = new QWidget(); header->setFixedHeight(56);
    header->setStyleSheet(
        "QWidget { background:qlineargradient(x1:0,y1:0,x2:1,y2:0,"
        "stop:0 #1B3A57,stop:1 #2C5F7C); border-radius:10px; }");
    QHBoxLayout *hLay = new QHBoxLayout(header);
    hLay->setContentsMargins(18, 0, 18, 0);
    QLabel *hTitre = new QLabel("✏️  Modifier Conteneur #" + QString::number(idConteneur));
    hTitre->setStyleSheet(
        "font-size:16px; font-weight:bold; color:white; background:transparent;");
    hLay->addWidget(hTitre);
    containerLayout->addWidget(header);

    QScrollArea *scrollArea = new QScrollArea();
    scrollArea->setWidgetResizable(true);
    scrollArea->setFrameShape(QFrame::NoFrame);
    QWidget *scrollWidget = new QWidget();
    QVBoxLayout *scrollLayout = new QVBoxLayout(scrollWidget);
    scrollLayout->setContentsMargins(4, 4, 4, 4); scrollLayout->setSpacing(6);

    const QString editStyle =
        "QLineEdit, QDoubleSpinBox, QComboBox, QDateEdit {"
        "  background:#FFFFFF; border:1px solid #D1D5DB; border-radius:8px;"
        "  padding:8px 12px; font-size:13px; color:#1F2937; }"
        "QLineEdit:focus, QDoubleSpinBox:focus, QComboBox:focus, QDateEdit:focus {"
        "  border:2px solid #2C5F7C; }";
    const QString labelStyle =
        "QLabel { font-size:12px; font-weight:600; color:#374151; "
        "background:transparent; margin-top:4px; }";

    auto addLabel = [&](const QString &txt) {
        QLabel *l = new QLabel(txt); l->setStyleSheet(labelStyle);
        scrollLayout->addWidget(l);
    };

    QDoubleSpinBox *capacite = new QDoubleSpinBox(); capacite->setStyleSheet(editStyle);
    capacite->setRange(1.0, 100000.0); capacite->setSuffix(" L");
    capacite->setValue(ct.getCapacite());
    addLabel("📦 Capacité (litres) *"); scrollLayout->addWidget(capacite);

    QComboBox *typePropriete = new QComboBox(); typePropriete->setStyleSheet(editStyle);
    typePropriete->addItems({"Public", "Privé", "Municipal", "Industriel"});
    typePropriete->setCurrentText(ct.getTypePropriete());
    addLabel("🏢 Type de Propriété *"); scrollLayout->addWidget(typePropriete);

    QLineEdit *adresse = new QLineEdit(ct.getAdresseComplete()); adresse->setStyleSheet(editStyle);
    addLabel("📍 Adresse *"); scrollLayout->addWidget(adresse);

    QLineEdit *gps = new QLineEdit(ct.getLocalisationGPS()); gps->setStyleSheet(editStyle);
    gps->setPlaceholderText("Ex: 36.8190, 10.1658");
    addLabel("🌐 Localisation GPS"); scrollLayout->addWidget(gps);

    addLabel("♻️ Types de déchets acceptés");
    QWidget *chkWidget = new QWidget(); chkWidget->setStyleSheet("background:transparent;");
    QGridLayout *chkGrid = new QGridLayout(chkWidget);
    chkGrid->setContentsMargins(0,4,0,4); chkGrid->setSpacing(8);
    QCheckBox *chkMenager    = new QCheckBox("🏠 Ménager");
    QCheckBox *chkRecyclable = new QCheckBox("♻️ Recyclable");
    QCheckBox *chkOrganique  = new QCheckBox("🌱 Organique");
    QCheckBox *chkIndustriel = new QCheckBox("🏭 Industriel");
    QString chkStyle = "QCheckBox { font-size:12px; color:#374151; background:transparent; }";
    chkMenager->setStyleSheet(chkStyle); chkRecyclable->setStyleSheet(chkStyle);
    chkOrganique->setStyleSheet(chkStyle); chkIndustriel->setStyleSheet(chkStyle);
    chkMenager->setChecked(ct.getAccepteMenager()    == "Oui");
    chkRecyclable->setChecked(ct.getAccepteRecyclable() == "Oui");
    chkOrganique->setChecked(ct.getAccepteOrganique()   == "Oui");
    chkIndustriel->setChecked(ct.getAccepteIndustriel() == "Oui");
    chkGrid->addWidget(chkMenager,    0, 0); chkGrid->addWidget(chkRecyclable, 0, 1);
    chkGrid->addWidget(chkOrganique,  1, 0); chkGrid->addWidget(chkIndustriel, 1, 1);
    scrollLayout->addWidget(chkWidget);

    QComboBox *etat = new QComboBox(); etat->setStyleSheet(editStyle);
    etat->addItems({"Opérationnel", "En maintenance", "Hors service"});
    etat->setCurrentText(ct.getEtat());
    addLabel("⚙️ État *"); scrollLayout->addWidget(etat);

    // ── NOUVEAU : Zone ───────────────────────────────────────────
    QComboBox *zone = new QComboBox(); zone->setStyleSheet(editStyle);
    zone->addItems({"centre", "residentiel", "industriel"});
    zone->setCurrentText(ct.getZone().isEmpty() ? "residentiel" : ct.getZone());
    zone->setToolTip(
        "centre      : zone urbaine dense — remplissage ×1.5\n"
        "residentiel : zone résidentielle — référence ×1.0\n"
        "industriel  : zone industrielle  — remplissage ×0.8"
        );
    addLabel("📍 Zone géographique *"); scrollLayout->addWidget(zone);
    // ─────────────────────────────────────────────────────────────

    QDateEdit *dateDC = new QDateEdit(); dateDC->setStyleSheet(editStyle);
    dateDC->setDisplayFormat("dd/MM/yyyy"); dateDC->setCalendarPopup(true);
    QDate dDC = QDate::fromString(ct.getDateDerniereCollecte(), "dd/MM/yyyy");
    if (!dDC.isValid()) dDC = QDate::currentDate();
    dateDC->setDate(dDC);
    addLabel("📅 Date Dernière Collecte"); scrollLayout->addWidget(dateDC);

    scrollArea->setWidget(scrollWidget);
    containerLayout->addWidget(scrollArea);
    containerLayout->addSpacing(10);

    QHBoxLayout *btnLayout = new QHBoxLayout(); btnLayout->setSpacing(15);
    QPushButton *annuler = new QPushButton("✗ Annuler"); annuler->setMinimumHeight(50);
    annuler->setStyleSheet(
        "QPushButton { background:#E5E7EB; color:#374151; font-size:15px; "
        "font-weight:600; border:none; border-radius:8px; padding:12px 30px; }");
    QPushButton *enregistrer = new QPushButton("✓ Enregistrer"); enregistrer->setMinimumHeight(50);
    enregistrer->setStyleSheet(
        "QPushButton { background:qlineargradient(x1:0,y1:0,x2:0,y2:1,"
        "stop:0 #1A7A4A,stop:1 #0F4D2E); color:white; font-size:15px; "
        "font-weight:600; border:none; border-radius:8px; padding:12px 30px; }");
    btnLayout->addWidget(annuler); btnLayout->addWidget(enregistrer);
    containerLayout->addLayout(btnLayout);
    mainLayout->addWidget(container);

    connect(annuler,     &QPushButton::clicked, dialog, &QDialog::reject);
    connect(enregistrer, &QPushButton::clicked, this,   [=]() {
        if (adresse->text().trimmed().isEmpty()) {
            showMessage(dialog, "Erreur", "L'adresse est obligatoire !", "error"); return;
        }
        if (capacite->value() <= 0.0) {
            showMessage(dialog, "Erreur", "La capacité doit être > 0 !", "error"); return;
        }
        // Construction avec le nouveau paramètre zone (12ème argument)
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
                          dateDC->date().toString("dd/MM/yyyy"),
                          zone->currentText());    // ← zone
        if (ctModif.modifier()) {
            showMessage(dialog, "Succès", "✅ Conteneur modifié avec succès !", "success");
            dialog->accept(); afficherConteneurs();
        } else {
            showMessage(dialog, "Erreur", "Impossible de modifier ce conteneur.", "error");
        }
    });

    dialog->exec();
}
// ── SUPPRESSION CONTENEUR ────────────────────────────────────────
void MainWindow::on_bouttonsupprimerconteneur_clicked()
{
    int row = ui->tableWidget_Conteneur->currentRow();
    if (row < 0) {
        showMessage(this, "Attention", "⚠️ Veuillez sélectionner un conteneur avant de supprimer.", "warning"); return;
    }
    QTableWidgetItem *idItem = ui->tableWidget_Conteneur->item(row, 0);
    if (!idItem || idItem->text().trimmed().isEmpty()) {
        showMessage(this, "Erreur", "Impossible de récupérer l'ID.", "error"); return;
    }
    int idConteneur = idItem->text().toInt();
    QString adresseConteneur = ui->tableWidget_Conteneur->item(row, 3)->text();

    if (Conteneur::compterLiensConsommer(idConteneur) > 0) {
        showMessage(this, "Suppression impossible",
                    "❌ Ce conteneur est lié à des collecte(s) dans CONSOMMER.", "error");
        return;
    }

    QDialog *confirm = new QDialog(this);
    confirm->setFixedSize(440, 220);
    confirm->setStyleSheet("QDialog { background-color:#1E1E2E; border-radius:14px; }");
    QVBoxLayout *lay = new QVBoxLayout(confirm); lay->setContentsMargins(0,0,0,24); lay->setSpacing(0);
    QWidget *header = new QWidget(); header->setFixedHeight(62);
    header->setStyleSheet("QWidget { background-color:#E67E22; border-top-left-radius:14px; border-top-right-radius:14px; }");
    QHBoxLayout *hLay = new QHBoxLayout(header); hLay->setContentsMargins(22,0,22,0);
    QLabel *lblTitre = new QLabel("⚠️  Confirmer la suppression");
    lblTitre->setStyleSheet("font-size:15px; font-weight:bold; color:white; background:transparent;");
    hLay->addWidget(lblTitre); lay->addWidget(header);
    QLabel *lblMsg = new QLabel("Voulez-vous vraiment supprimer ?\n🏠 " + adresseConteneur + "\n🆔 ID : " + QString::number(idConteneur));
    lblMsg->setAlignment(Qt::AlignCenter); lblMsg->setWordWrap(true);
    lblMsg->setStyleSheet("font-size:13px; color:#C8C8D8; background:transparent; padding:16px 28px 8px 28px;");
    lay->addWidget(lblMsg); lay->addStretch();
    QHBoxLayout *btnLay = new QHBoxLayout(); btnLay->setSpacing(12); btnLay->setContentsMargins(20,0,20,0);
    QPushButton *btnNon = new QPushButton("✗ Annuler"); btnNon->setFixedHeight(40);
    btnNon->setStyleSheet("QPushButton { background:#374151; color:white; font-size:13px; font-weight:600; border:none; border-radius:8px; }");
    QPushButton *btnOui = new QPushButton("🗑️ Oui, supprimer"); btnOui->setFixedHeight(40);
    btnOui->setStyleSheet("QPushButton { background:#C0392B; color:white; font-size:13px; font-weight:600; border:none; border-radius:8px; }");
    btnLay->addWidget(btnNon); btnLay->addWidget(btnOui); lay->addLayout(btnLay);
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

Conteneur MainWindow::getConteneurSelectionne()
{
    int row = ui->tableWidget_Conteneur->currentRow();
    if (row < 0) return Conteneur();
    return Conteneur::getById(ui->tableWidget_Conteneur->item(row, 0)->text().toInt());
}

// ── MAP ──────────────────────────────────────────────────────────
void MainWindow::on_bouttonmap_clicked()
{
    Map *mapDialog = new Map(this);
    mapDialog->exec();
    delete mapDialog;
}

// ================================================================
// === RESTRICTIONS PAR POSTE =====================================
// ================================================================

void MainWindow::appliquerRestrictionsPoste()
{
    QString poste = m_posteConnecte.toLower();

    bool voirEmploye   = false;
    bool voirClient    = false;
    bool voirCollecte  = false;
    bool voirConteneur = false;
    bool voirRecyclage = false;
    bool peutAjouter   = false;
    bool peutModifier  = false;
    bool peutSupprimer = false;

    if (poste == "admin") {
        voirEmploye = voirClient = voirCollecte = voirConteneur = voirRecyclage = true;
        peutAjouter = peutModifier = peutSupprimer = true;
    }
    else if (poste == "manager") {
        voirEmploye = voirClient = voirCollecte = voirConteneur = voirRecyclage = true;
        peutAjouter = peutModifier = true;
        peutSupprimer = false;
    }
    else if (poste == "technicien") {
        voirConteneur = voirCollecte = true;
        peutAjouter = peutModifier = peutSupprimer = true;
    }
    else if (poste == "administratif") {
        voirClient = voirRecyclage = true;
        peutAjouter = peutModifier = peutSupprimer = true;
    }
    else if (poste == "agent terrain") {
        voirCollecte = true;
        peutAjouter = peutModifier = peutSupprimer = false;
    }

    // Navigation
    ui->EMPLOYE->setVisible(voirEmploye);
    ui->CLIENT->setVisible(voirClient);
    ui->COLLECTE->setVisible(voirCollecte);
    ui->CONTENEUR->setVisible(voirConteneur);
    ui->RECYCLAGE->setVisible(voirRecyclage);
    ui->DECONNECTION->setVisible(true);
    ui->ACCEUIL->setVisible(true);

    // CRUD Employé
    ui->bouttonajouteremp->setVisible(voirEmploye && peutAjouter);
    ui->bouttonmodifieremp->setVisible(voirEmploye && peutModifier);
    ui->bouttonsupprimeremp->setVisible(voirEmploye && peutSupprimer);

    // CRUD Client
    ui->bouttonajouterclient->setVisible(voirClient && peutAjouter);
    ui->bouttonmodifierclient->setVisible(voirClient && peutModifier);
    ui->bouttonsupprimerclient->setVisible(voirClient && peutSupprimer);

    // CRUD Collecte
    ui->pushButton_66->setVisible(voirCollecte && peutAjouter);
    ui->bouttonmodifiercollecte->setVisible(voirCollecte && peutModifier);
    ui->bouttonsupprimercollecte->setVisible(voirCollecte && peutSupprimer);

    // CRUD Conteneur
    ui->bouttonajouterconteneur->setVisible(voirConteneur && peutAjouter);
    ui->bouttonmodifierconteneur->setVisible(voirConteneur && peutModifier);
    ui->bouttonsupprimerconteneur->setVisible(voirConteneur && peutSupprimer);

    // CRUD Recyclage
    ui->bouttonajouterrecyclage->setVisible(voirRecyclage && peutAjouter);
    ui->bouttonmodifierrecyclage->setVisible(voirRecyclage && peutModifier);
    ui->bouttonsupprimerrecyclage->setVisible(voirRecyclage && peutSupprimer);
}
