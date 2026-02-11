#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QGraphicsDropShadowEffect>
#include <QPropertyAnimation>
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

