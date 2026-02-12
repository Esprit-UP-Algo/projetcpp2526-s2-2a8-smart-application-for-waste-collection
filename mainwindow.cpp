#include "mainwindow.h"
#include "ui_mainwindow.h"
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
#include <QMessageBox>
#include <QDateEdit>
#include <QScrollArea>
#include <QScrollBar>


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
    ui->stackedWidget->setCurrentIndex(0);
}

MainWindow::~MainWindow()
{
    delete ui;
}





void MainWindow::on_cnxemp_clicked()
{
    ui->stackedWidget->setCurrentIndex(3);
    ui->stackedWidget_2->setCurrentIndex(2);
}


void MainWindow::on_dec_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}


void MainWindow::on_mdp_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}


void MainWindow::on_retour_2_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}
void MainWindow::on_pushButton_clicked() {}
void MainWindow::on_pushButton_20_clicked() {}
void MainWindow::on_pushButton_29_clicked() {}
void MainWindow::on_pushButton_17_clicked() {}
void MainWindow::on_pushButton_30_clicked() {}
void MainWindow::on_pushButton_31_clicked() {}
void MainWindow::on_cnx_clicked() {}
void MainWindow::on_cnx1_clicked() {}


void MainWindow::on_acceuil_2_clicked()
{
    ui->stackedWidget_2->setCurrentIndex(2);
}


void MainWindow::on_pushButton_40_clicked()
{
    ui->stackedWidget_2->setCurrentIndex(0);
}


void MainWindow::on_dec_2_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}


void MainWindow::on_pushButton_28_clicked()
{
    ui->stackedWidget_2->setCurrentIndex(1);
}

void MainWindow::on_pushButton_client_ajouter_clicked()
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
        "stop:0 #2F7D4F,"
        "stop:1 #1E5631);"
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

    // ===== STYLE =====
    QString labelStyle =
        "QLabel {"
        "background-color:#ECECEC;"
        "border-radius:20px;"
        "padding:10px 15px;"
        "font-size:14px;"
        "font-weight:600;"
        "color:#1F2D3D;"
        "}";

    QString editStyle =
        "QLineEdit {"
        "background-color:#E5E7EB;"
        "border:2px solid #C7CED6;"
        "border-radius:15px;"
        "padding:12px;"
        "font-size:14px;"
        "}"
        "QLineEdit:focus {"
        "border:2px solid #2F7D4F;"
        "background-color:white;"
        "}";

    QString comboStyle =
        "QComboBox {"
        "background-color:#294766;"
        "color:white;"
        "border:2px solid #3A6EA5;"
        "border-radius:15px;"
        "padding:12px;"
        "font-size:14px;"
        "}"
        "QComboBox QAbstractItemView {"
        "background-color:#203A57;"
        "color:white;"
        "selection-background-color:#2F5F99;"
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

    addField("Nom *", nom);
    addField("Prénom *", prenom);

    QLabel *lblPoste = new QLabel("Poste *");
    lblPoste->setStyleSheet(labelStyle);
    scrollLayout->addWidget(lblPoste);
    scrollLayout->addWidget(poste);

    addField("Email *", email);
    addField("Téléphone *", telephone);
    addField("CIN", cin);

    scrollArea->setWidget(scrollWidget);

    // ===== ScrollBar Style =====
    scrollArea->verticalScrollBar()->setStyleSheet(
        "QScrollBar:vertical {"
        "background:#2A2A2A;"
        "width:12px;"
        "margin:15px 0 15px 0;"
        "border-radius:6px;"
        "}"
        "QScrollBar::handle:vertical {"
        "background:#555;"
        "min-height:40px;"
        "border-radius:6px;"
        "}"
        "QScrollBar::handle:vertical:hover {"
        "background:#777;"
        "}"
        "QScrollBar::add-line:vertical,"
        "QScrollBar::sub-line:vertical {"
        "height:0px;"
        "}"
        );

    containerLayout->addWidget(scrollArea);
    containerLayout->addSpacing(15);

    QLabel *note = new QLabel("* Champs obligatoires");
    note->setStyleSheet("color:#6E7F91; font-style:italic;");
    containerLayout->addWidget(note);

    // ===== BOUTONS =====
    QHBoxLayout *btnLayout = new QHBoxLayout();
    btnLayout->setSpacing(25);

    QPushButton *annuler = new QPushButton("✗ Annuler");
    annuler->setMinimumHeight(55);
    annuler->setStyleSheet(
        "QPushButton {"
        "background-color:#D1D5DB;"
        "color:#1F2937;"
        "font-size:16px;"
        "font-weight:600;"
        "border-radius:20px;"
        "padding:15px 30px;"
        "}"
        "QPushButton:hover { background-color:#BFC6CE; }"
        );

    QPushButton *ajouter = new QPushButton("✓ Ajouter l'employé");
    ajouter->setMinimumHeight(55);
    ajouter->setStyleSheet(
        "QPushButton {"
        "background:qlineargradient("
        "x1:0,y1:0,x2:0,y2:1,"
        "stop:0 #2F7D4F,"
        "stop:1 #1E5631);"
        "color:white;"
        "font-size:16px;"
        "font-weight:600;"
        "border-radius:20px;"
        "padding:15px 30px;"
        "}"
        "QPushButton:hover { background:#2F7D4F; }"
        );

    btnLayout->addWidget(annuler);
    btnLayout->addWidget(ajouter);

    containerLayout->addLayout(btnLayout);
    mainLayout->addWidget(container);

    connect(annuler,&QPushButton::clicked,dialog,&QDialog::reject);

    dialog->exec();
}
