/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.7.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QWidget *searchBox_7;
    QFrame *frame_20;
    QPushButton *pushButton_35;
    QPushButton *pushButton_36;
    QPushButton *pushButton_37;
    QPushButton *pushButton_38;
    QPushButton *acceuil;
    QPushButton *pushButton_45;
    QPushButton *dec;
    QLabel *label_79;
    QFrame *frame_2;
    QWidget *searchBox_5;
    QLineEdit *lineEdit_8;
    QPushButton *pushButton_21;
    QPushButton *pushButton_20;
    QPushButton *pushButton_19;
    QFrame *frame_48;
    QLabel *label_18;
    QPushButton *pushButton_client_ajouter;
    QPushButton *pushButton_23;
    QPushButton *pushButton_10;
    QComboBox *comboTypePropriete_3;
    QTableWidget *tableWidget_3;
    QFrame *frame_46;
    QFrame *frame_47;
    QLabel *label_168;
    QLabel *label_171;
    QLineEdit *lineEdit_46;
    QLabel *label_172;
    QLineEdit *lineEdit_47;
    QLabel *label_175;
    QLineEdit *lineEdit_48;
    QLabel *label_177;
    QLineEdit *lineEdit_49;
    QLabel *label_179;
    QLineEdit *lineEdit_50;
    QLabel *label_180;
    QComboBox *comboBox_3;
    QLabel *label_181;
    QComboBox *comboBox_2;
    QPushButton *pushButton_22;
    QPushButton *pushButton_annuler_ajout;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(1682, 992);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        searchBox_7 = new QWidget(centralwidget);
        searchBox_7->setObjectName("searchBox_7");
        searchBox_7->setGeometry(QRect(0, 0, 311, 951));
        searchBox_7->setStyleSheet(QString::fromUtf8("background-color: qlineargradient(\n"
"    spread:pad,\n"
"    x1:0, y1:0,\n"
"    x2:0, y2:1,\n"
"    stop:0 #0A1F33,\n"
"    stop:0.5 #163A5F,\n"
"    stop:1 #274C77\n"
");\n"
""));
        frame_20 = new QFrame(searchBox_7);
        frame_20->setObjectName("frame_20");
        frame_20->setGeometry(QRect(40, 20, 251, 841));
        frame_20->setStyleSheet(QString::fromUtf8("  background-color: #FFFFFF; /* fond blanc */\n"
"    border-radius: 20px;       /* coins arrondis */\n"
"    border: 2px solid rgba(44, 95, 124, 0.08); /* bord gris clair */"));
        frame_20->setFrameShape(QFrame::Shape::StyledPanel);
        frame_20->setFrameShadow(QFrame::Shadow::Raised);
        pushButton_35 = new QPushButton(frame_20);
        pushButton_35->setObjectName("pushButton_35");
        pushButton_35->setGeometry(QRect(10, 510, 221, 51));
        QFont font;
        font.setWeight(QFont::DemiBold);
        font.setItalic(false);
        pushButton_35->setFont(font);
        pushButton_35->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    background-color: qlineargradient(\n"
"        x1:0, y1:0,\n"
"        x2:0, y2:1,\n"
"        stop:0 #2C5F7C,\n"
"        stop:0.5 #3A6EA5,\n"
"        stop:1 #1B3A57\n"
"    );\n"
"\n"
"    color: white;\n"
"    font-size: 14px;\n"
"    font-weight: 600;\n"
"\n"
"    border: none;\n"
"    border-radius: 14px;\n"
"\n"
"    padding: 10px 22px;\n"
"}\n"
"\n"
"/* \342\234\250 HOVER : lumi\303\250re douce */\n"
"QPushButton:hover {\n"
"    background-color: qlineargradient(\n"
"        x1:0, y1:0,\n"
"        x2:0, y2:1,\n"
"        stop:0 #3A6EA5,\n"
"        stop:0.5 #4A86C5,\n"
"        stop:1 #2C5F7C\n"
"    );\n"
"}\n"
"\n"
"/* \360\237\224\230 CLICK (pressed) */\n"
"QPushButton:pressed {\n"
"    background-color: qlineargradient(\n"
"        x1:0, y1:0,\n"
"        x2:0, y2:1,\n"
"        stop:0 #1B3A57,\n"
"        stop:1 #2C5F7C\n"
"    );\n"
"}\n"
"\n"
"/* \360\237\232\253 D\303\251sactiv\303\251 */\n"
"QPushButton:disabled {\n"
"    background-color: #C8D3DF;\n"
"    color: #6E7F91"
                        ";\n"
"}\n"
""));
        pushButton_36 = new QPushButton(frame_20);
        pushButton_36->setObjectName("pushButton_36");
        pushButton_36->setGeometry(QRect(10, 330, 221, 51));
        pushButton_36->setFont(font);
        pushButton_36->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    background-color: qlineargradient(\n"
"        x1:0, y1:0,\n"
"        x2:0, y2:1,\n"
"        stop:0 #2C5F7C,\n"
"        stop:0.5 #3A6EA5,\n"
"        stop:1 #1B3A57\n"
"    );\n"
"\n"
"    color: white;\n"
"    font-size: 14px;\n"
"    font-weight: 600;\n"
"\n"
"    border: none;\n"
"    border-radius: 14px;\n"
"\n"
"    padding: 10px 22px;\n"
"}\n"
"\n"
"/* \342\234\250 HOVER : lumi\303\250re douce */\n"
"QPushButton:hover {\n"
"    background-color: qlineargradient(\n"
"        x1:0, y1:0,\n"
"        x2:0, y2:1,\n"
"        stop:0 #3A6EA5,\n"
"        stop:0.5 #4A86C5,\n"
"        stop:1 #2C5F7C\n"
"    );\n"
"}\n"
"\n"
"/* \360\237\224\230 CLICK (pressed) */\n"
"QPushButton:pressed {\n"
"    background-color: qlineargradient(\n"
"        x1:0, y1:0,\n"
"        x2:0, y2:1,\n"
"        stop:0 #1B3A57,\n"
"        stop:1 #2C5F7C\n"
"    );\n"
"}\n"
"\n"
"/* \360\237\232\253 D\303\251sactiv\303\251 */\n"
"QPushButton:disabled {\n"
"    background-color: #C8D3DF;\n"
"    color: #6E7F91"
                        ";\n"
"}\n"
""));
        pushButton_37 = new QPushButton(frame_20);
        pushButton_37->setObjectName("pushButton_37");
        pushButton_37->setGeometry(QRect(10, 390, 221, 51));
        pushButton_37->setFont(font);
        pushButton_37->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    background-color: qlineargradient(\n"
"        x1:0, y1:0,\n"
"        x2:0, y2:1,\n"
"        stop:0 #2C5F7C,\n"
"        stop:0.5 #3A6EA5,\n"
"        stop:1 #1B3A57\n"
"    );\n"
"\n"
"    color: white;\n"
"    font-size: 14px;\n"
"    font-weight: 600;\n"
"\n"
"    border: none;\n"
"    border-radius: 14px;\n"
"\n"
"    padding: 10px 22px;\n"
"}\n"
"\n"
"/* \342\234\250 HOVER : lumi\303\250re douce */\n"
"QPushButton:hover {\n"
"    background-color: qlineargradient(\n"
"        x1:0, y1:0,\n"
"        x2:0, y2:1,\n"
"        stop:0 #3A6EA5,\n"
"        stop:0.5 #4A86C5,\n"
"        stop:1 #2C5F7C\n"
"    );\n"
"}\n"
"\n"
"/* \360\237\224\230 CLICK (pressed) */\n"
"QPushButton:pressed {\n"
"    background-color: qlineargradient(\n"
"        x1:0, y1:0,\n"
"        x2:0, y2:1,\n"
"        stop:0 #1B3A57,\n"
"        stop:1 #2C5F7C\n"
"    );\n"
"}\n"
"\n"
"/* \360\237\232\253 D\303\251sactiv\303\251 */\n"
"QPushButton:disabled {\n"
"    background-color: #C8D3DF;\n"
"    color: #6E7F91"
                        ";\n"
"}\n"
""));
        pushButton_38 = new QPushButton(frame_20);
        pushButton_38->setObjectName("pushButton_38");
        pushButton_38->setGeometry(QRect(10, 450, 221, 51));
        pushButton_38->setFont(font);
        pushButton_38->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    background-color: qlineargradient(\n"
"        x1:0, y1:0,\n"
"        x2:0, y2:1,\n"
"        stop:0 #2C5F7C,\n"
"        stop:0.5 #3A6EA5,\n"
"        stop:1 #1B3A57\n"
"    );\n"
"\n"
"    color: white;\n"
"    font-size: 14px;\n"
"    font-weight: 600;\n"
"\n"
"    border: none;\n"
"    border-radius: 14px;\n"
"\n"
"    padding: 10px 22px;\n"
"}\n"
"\n"
"/* \342\234\250 HOVER : lumi\303\250re douce */\n"
"QPushButton:hover {\n"
"    background-color: qlineargradient(\n"
"        x1:0, y1:0,\n"
"        x2:0, y2:1,\n"
"        stop:0 #3A6EA5,\n"
"        stop:0.5 #4A86C5,\n"
"        stop:1 #2C5F7C\n"
"    );\n"
"}\n"
"\n"
"/* \360\237\224\230 CLICK (pressed) */\n"
"QPushButton:pressed {\n"
"    background-color: qlineargradient(\n"
"        x1:0, y1:0,\n"
"        x2:0, y2:1,\n"
"        stop:0 #1B3A57,\n"
"        stop:1 #2C5F7C\n"
"    );\n"
"}\n"
"\n"
"/* \360\237\232\253 D\303\251sactiv\303\251 */\n"
"QPushButton:disabled {\n"
"    background-color: #C8D3DF;\n"
"    color: #6E7F91"
                        ";\n"
"}\n"
""));
        acceuil = new QPushButton(frame_20);
        acceuil->setObjectName("acceuil");
        acceuil->setGeometry(QRect(10, 270, 221, 51));
        acceuil->setFont(font);
        acceuil->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    background-color: qlineargradient(\n"
"        x1:0, y1:0,\n"
"        x2:0, y2:1,\n"
"        stop:0 #2C5F7C,\n"
"        stop:0.5 #3A6EA5,\n"
"        stop:1 #1B3A57\n"
"    );\n"
"\n"
"    color: white;\n"
"    font-size: 14px;\n"
"    font-weight: 600;\n"
"\n"
"    border: none;\n"
"    border-radius: 14px;\n"
"\n"
"    padding: 10px 22px;\n"
"}\n"
"\n"
"/* \342\234\250 HOVER : lumi\303\250re douce */\n"
"QPushButton:hover {\n"
"    background-color: qlineargradient(\n"
"        x1:0, y1:0,\n"
"        x2:0, y2:1,\n"
"        stop:0 #3A6EA5,\n"
"        stop:0.5 #4A86C5,\n"
"        stop:1 #2C5F7C\n"
"    );\n"
"}\n"
"\n"
"/* \360\237\224\230 CLICK (pressed) */\n"
"QPushButton:pressed {\n"
"    background-color: qlineargradient(\n"
"        x1:0, y1:0,\n"
"        x2:0, y2:1,\n"
"        stop:0 #1B3A57,\n"
"        stop:1 #2C5F7C\n"
"    );\n"
"}\n"
"\n"
"/* \360\237\232\253 D\303\251sactiv\303\251 */\n"
"QPushButton:disabled {\n"
"    background-color: #C8D3DF;\n"
"    color: #6E7F91"
                        ";\n"
"}\n"
""));
        pushButton_45 = new QPushButton(frame_20);
        pushButton_45->setObjectName("pushButton_45");
        pushButton_45->setGeometry(QRect(10, 570, 221, 51));
        pushButton_45->setFont(font);
        pushButton_45->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    background-color: qlineargradient(\n"
"        x1:0, y1:0,\n"
"        x2:0, y2:1,\n"
"        stop:0 #2C5F7C,\n"
"        stop:0.5 #3A6EA5,\n"
"        stop:1 #1B3A57\n"
"    );\n"
"\n"
"    color: white;\n"
"    font-size: 14px;\n"
"    font-weight: 600;\n"
"\n"
"    border: none;\n"
"    border-radius: 14px;\n"
"\n"
"    padding: 10px 22px;\n"
"}\n"
"\n"
"/* \342\234\250 HOVER : lumi\303\250re douce */\n"
"QPushButton:hover {\n"
"    background-color: qlineargradient(\n"
"        x1:0, y1:0,\n"
"        x2:0, y2:1,\n"
"        stop:0 #3A6EA5,\n"
"        stop:0.5 #4A86C5,\n"
"        stop:1 #2C5F7C\n"
"    );\n"
"}\n"
"\n"
"/* \360\237\224\230 CLICK (pressed) */\n"
"QPushButton:pressed {\n"
"    background-color: qlineargradient(\n"
"        x1:0, y1:0,\n"
"        x2:0, y2:1,\n"
"        stop:0 #1B3A57,\n"
"        stop:1 #2C5F7C\n"
"    );\n"
"}\n"
"\n"
"/* \360\237\232\253 D\303\251sactiv\303\251 */\n"
"QPushButton:disabled {\n"
"    background-color: #C8D3DF;\n"
"    color: #6E7F91"
                        ";\n"
"}\n"
""));
        dec = new QPushButton(frame_20);
        dec->setObjectName("dec");
        dec->setGeometry(QRect(10, 780, 221, 51));
        dec->setFont(font);
        dec->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    background-color: qlineargradient(\n"
"        x1:0, y1:0,\n"
"        x2:0, y2:1,\n"
"        stop:0 #2C5F7C,\n"
"        stop:0.5 #3A6EA5,\n"
"        stop:1 #1B3A57\n"
"    );\n"
"\n"
"    color: white;\n"
"    font-size: 14px;\n"
"    font-weight: 600;\n"
"\n"
"    border: none;\n"
"    border-radius: 14px;\n"
"\n"
"    padding: 10px 22px;\n"
"}\n"
"\n"
"/* \342\234\250 HOVER : lumi\303\250re douce */\n"
"QPushButton:hover {\n"
"    background-color: qlineargradient(\n"
"        x1:0, y1:0,\n"
"        x2:0, y2:1,\n"
"        stop:0 #3A6EA5,\n"
"        stop:0.5 #4A86C5,\n"
"        stop:1 #2C5F7C\n"
"    );\n"
"}\n"
"\n"
"/* \360\237\224\230 CLICK (pressed) */\n"
"QPushButton:pressed {\n"
"    background-color: qlineargradient(\n"
"        x1:0, y1:0,\n"
"        x2:0, y2:1,\n"
"        stop:0 #1B3A57,\n"
"        stop:1 #2C5F7C\n"
"    );\n"
"}\n"
"\n"
"/* \360\237\232\253 D\303\251sactiv\303\251 */\n"
"QPushButton:disabled {\n"
"    background-color: #C8D3DF;\n"
"    color: #6E7F91"
                        ";\n"
"}\n"
""));
        label_79 = new QLabel(frame_20);
        label_79->setObjectName("label_79");
        label_79->setGeometry(QRect(0, 0, 251, 271));
        label_79->setPixmap(QPixmap(QString::fromUtf8(":/images/wasteflow.png")));
        label_79->setScaledContents(true);
        frame_2 = new QFrame(centralwidget);
        frame_2->setObjectName("frame_2");
        frame_2->setGeometry(QRect(310, 0, 1281, 951));
        frame_2->setStyleSheet(QString::fromUtf8("background-color: qlineargradient(\n"
"    spread:pad,\n"
"    x1:0, y1:0,\n"
"    x2:0, y2:1,\n"
"    stop:0 #0A1F33,\n"
"    stop:0.5 #163A5F,\n"
"    stop:1 #274C77\n"
");"));
        frame_2->setFrameShape(QFrame::Shape::StyledPanel);
        frame_2->setFrameShadow(QFrame::Shadow::Raised);
        searchBox_5 = new QWidget(frame_2);
        searchBox_5->setObjectName("searchBox_5");
        searchBox_5->setGeometry(QRect(10, 20, 1201, 71));
        searchBox_5->setStyleSheet(QString::fromUtf8("background: white;\n"
"border-radius: 20px;\n"
"padding: 20px;\n"
"\n"
""));
        lineEdit_8 = new QLineEdit(searchBox_5);
        lineEdit_8->setObjectName("lineEdit_8");
        lineEdit_8->setGeometry(QRect(10, 10, 511, 51));
        QFont font1;
        font1.setWeight(QFont::Medium);
        lineEdit_8->setFont(font1);
        lineEdit_8->setStyleSheet(QString::fromUtf8("QLineEdit {\n"
"    background-color: #F9FBFD;          /* fond clair \303\251l\303\251gant */\n"
"    border: 2px solid #3A6EA5;           /* bleu marine clair */\n"
"    border-radius: 12px;\n"
"    padding: 10px 14px;\n"
"    color: #0A1F33;                      /* texte bleu marine fonc\303\251 */\n"
"    font-size: 14px;\n"
"    font-weight: 500;\n"
"}\n"
"\n"
"/* Quand le champ est s\303\251lectionn\303\251 */\n"
"QLineEdit:focus {\n"
"    background-color: white;\n"
"    border: 2px solid #1E3A5F;           /* focus plus fonc\303\251 */\n"
"}\n"
"\n"
"/* Hover */\n"
"QLineEdit:hover {\n"
"    border: 2px solid #2F5D8A;\n"
"}\n"
""));
        pushButton_21 = new QPushButton(searchBox_5);
        pushButton_21->setObjectName("pushButton_21");
        pushButton_21->setGeometry(QRect(530, 10, 131, 51));
        pushButton_21->setFont(font);
        pushButton_21->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    background-color: qlineargradient(\n"
"        x1:0, y1:0,\n"
"        x2:0, y2:1,\n"
"        stop:0 #2C5F7C,\n"
"        stop:0.5 #3A6EA5,\n"
"        stop:1 #1B3A57\n"
"    );\n"
"\n"
"    color: white;\n"
"    font-size: 14px;\n"
"    font-weight: 600;\n"
"\n"
"    border: none;\n"
"    border-radius: 14px;\n"
"\n"
"    padding: 10px 22px;\n"
"}\n"
"\n"
"/* \342\234\250 HOVER : lumi\303\250re douce */\n"
"QPushButton:hover {\n"
"    background-color: qlineargradient(\n"
"        x1:0, y1:0,\n"
"        x2:0, y2:1,\n"
"        stop:0 #3A6EA5,\n"
"        stop:0.5 #4A86C5,\n"
"        stop:1 #2C5F7C\n"
"    );\n"
"}\n"
"\n"
"/* \360\237\224\230 CLICK (pressed) */\n"
"QPushButton:pressed {\n"
"    background-color: qlineargradient(\n"
"        x1:0, y1:0,\n"
"        x2:0, y2:1,\n"
"        stop:0 #1B3A57,\n"
"        stop:1 #2C5F7C\n"
"    );\n"
"}\n"
"\n"
"/* \360\237\232\253 D\303\251sactiv\303\251 */\n"
"QPushButton:disabled {\n"
"    background-color: #C8D3DF;\n"
"    color: #6E7F91"
                        ";\n"
"}\n"
""));
        pushButton_20 = new QPushButton(searchBox_5);
        pushButton_20->setObjectName("pushButton_20");
        pushButton_20->setGeometry(QRect(920, 10, 131, 51));
        pushButton_20->setFont(font);
        pushButton_20->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    background-color: qlineargradient(\n"
"        x1:0, y1:0,\n"
"        x2:0, y2:1,\n"
"        stop:0 #2C5F7C,\n"
"        stop:0.5 #3A6EA5,\n"
"        stop:1 #1B3A57\n"
"    );\n"
"\n"
"    color: white;\n"
"    font-size: 14px;\n"
"    font-weight: 600;\n"
"\n"
"    border: none;\n"
"    border-radius: 14px;\n"
"\n"
"    padding: 10px 22px;\n"
"}\n"
"\n"
"/* \342\234\250 HOVER : lumi\303\250re douce */\n"
"QPushButton:hover {\n"
"    background-color: qlineargradient(\n"
"        x1:0, y1:0,\n"
"        x2:0, y2:1,\n"
"        stop:0 #3A6EA5,\n"
"        stop:0.5 #4A86C5,\n"
"        stop:1 #2C5F7C\n"
"    );\n"
"}\n"
"\n"
"/* \360\237\224\230 CLICK (pressed) */\n"
"QPushButton:pressed {\n"
"    background-color: qlineargradient(\n"
"        x1:0, y1:0,\n"
"        x2:0, y2:1,\n"
"        stop:0 #1B3A57,\n"
"        stop:1 #2C5F7C\n"
"    );\n"
"}\n"
"\n"
"/* \360\237\232\253 D\303\251sactiv\303\251 */\n"
"QPushButton:disabled {\n"
"    background-color: #C8D3DF;\n"
"    color: #6E7F91"
                        ";\n"
"}\n"
""));
        pushButton_19 = new QPushButton(searchBox_5);
        pushButton_19->setObjectName("pushButton_19");
        pushButton_19->setGeometry(QRect(1060, 10, 131, 51));
        pushButton_19->setFont(font);
        pushButton_19->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    background-color: qlineargradient(\n"
"        x1:0, y1:0,\n"
"        x2:0, y2:1,\n"
"        stop:0 #2C5F7C,\n"
"        stop:0.5 #3A6EA5,\n"
"        stop:1 #1B3A57\n"
"    );\n"
"\n"
"    color: white;\n"
"    font-size: 14px;\n"
"    font-weight: 600;\n"
"\n"
"    border: none;\n"
"    border-radius: 14px;\n"
"\n"
"    padding: 10px 22px;\n"
"}\n"
"\n"
"/* \342\234\250 HOVER : lumi\303\250re douce */\n"
"QPushButton:hover {\n"
"    background-color: qlineargradient(\n"
"        x1:0, y1:0,\n"
"        x2:0, y2:1,\n"
"        stop:0 #3A6EA5,\n"
"        stop:0.5 #4A86C5,\n"
"        stop:1 #2C5F7C\n"
"    );\n"
"}\n"
"\n"
"/* \360\237\224\230 CLICK (pressed) */\n"
"QPushButton:pressed {\n"
"    background-color: qlineargradient(\n"
"        x1:0, y1:0,\n"
"        x2:0, y2:1,\n"
"        stop:0 #1B3A57,\n"
"        stop:1 #2C5F7C\n"
"    );\n"
"}\n"
"\n"
"/* \360\237\232\253 D\303\251sactiv\303\251 */\n"
"QPushButton:disabled {\n"
"    background-color: #C8D3DF;\n"
"    color: #6E7F91"
                        ";\n"
"}\n"
""));
        frame_48 = new QFrame(frame_2);
        frame_48->setObjectName("frame_48");
        frame_48->setGeometry(QRect(10, 100, 1201, 71));
        frame_48->setStyleSheet(QString::fromUtf8("QFrame {\n"
"    background-color: white;\n"
"    border-radius: 15px;\n"
"}\n"
"\n"
""));
        frame_48->setFrameShape(QFrame::Shape::StyledPanel);
        frame_48->setFrameShadow(QFrame::Shadow::Raised);
        label_18 = new QLabel(frame_48);
        label_18->setObjectName("label_18");
        label_18->setGeometry(QRect(20, 10, 261, 51));
        label_18->setStyleSheet(QString::fromUtf8("color: #2A3439;\n"
""));
        pushButton_client_ajouter = new QPushButton(frame_48);
        pushButton_client_ajouter->setObjectName("pushButton_client_ajouter");
        pushButton_client_ajouter->setGeometry(QRect(570, 10, 131, 51));
        pushButton_client_ajouter->setFont(font);
        pushButton_client_ajouter->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    background-color: qlineargradient(\n"
"        x1:0, y1:0,\n"
"        x2:0, y2:1,\n"
"        stop:0 #276646,\n"
"        stop:0.5 #34885A,\n"
"        stop:1 #1B3A2F\n"
"    );\n"
"    color: white;\n"
"    font-size: 14px;\n"
"    font-weight: 600;\n"
"    border: none;\n"
"    border-radius: 14px;\n"
"    padding: 10px 22px;\n"
"}\n"
"QPushButton:hover {\n"
"    background-color: qlineargradient(\n"
"        x1:0, y1:0,\n"
"        x2:0, y2:1,\n"
"        stop:0 #34885A,\n"
"        stop:0.5 #42A56F,\n"
"        stop:1 #276646\n"
"    );\n"
"}\n"
"QPushButton:pressed {\n"
"    background-color: qlineargradient(\n"
"        x1:0, y1:0,\n"
"        x2:0, y2:1,\n"
"        stop:0 #1B3A2F,\n"
"        stop:1 #276646\n"
"    );\n"
"}\n"
""));
        pushButton_23 = new QPushButton(frame_48);
        pushButton_23->setObjectName("pushButton_23");
        pushButton_23->setGeometry(QRect(710, 10, 131, 51));
        pushButton_23->setFont(font);
        pushButton_23->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    background-color: qlineargradient(\n"
"        x1:0, y1:0,\n"
"        x2:0, y2:1,\n"
"        stop:0 #2C5F7C,\n"
"        stop:0.5 #3A6EA5,\n"
"        stop:1 #1B3A57\n"
"    );\n"
"\n"
"    color: white;\n"
"    font-size: 14px;\n"
"    font-weight: 600;\n"
"\n"
"    border: none;\n"
"    border-radius: 14px;\n"
"\n"
"    padding: 10px 22px;\n"
"}\n"
"\n"
"/* \342\234\250 HOVER : lumi\303\250re douce */\n"
"QPushButton:hover {\n"
"    background-color: qlineargradient(\n"
"        x1:0, y1:0,\n"
"        x2:0, y2:1,\n"
"        stop:0 #3A6EA5,\n"
"        stop:0.5 #4A86C5,\n"
"        stop:1 #2C5F7C\n"
"    );\n"
"}\n"
"\n"
"/* \360\237\224\230 CLICK (pressed) */\n"
"QPushButton:pressed {\n"
"    background-color: qlineargradient(\n"
"        x1:0, y1:0,\n"
"        x2:0, y2:1,\n"
"        stop:0 #1B3A57,\n"
"        stop:1 #2C5F7C\n"
"    );\n"
"}\n"
"\n"
"/* \360\237\232\253 D\303\251sactiv\303\251 */\n"
"QPushButton:disabled {\n"
"    background-color: #C8D3DF;\n"
"    color: #6E7F91"
                        ";\n"
"}\n"
""));
        pushButton_10 = new QPushButton(frame_48);
        pushButton_10->setObjectName("pushButton_10");
        pushButton_10->setGeometry(QRect(850, 10, 131, 51));
        pushButton_10->setFont(font);
        pushButton_10->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    background-color: qlineargradient(\n"
"        x1:0, y1:0,\n"
"        x2:0, y2:1,\n"
"        stop:0 #8B0000,\n"
"        stop:0.5 #A52A2A,\n"
"        stop:1 #5C0000\n"
"    );\n"
"\n"
"    color: white;\n"
"    font-size: 14px;\n"
"    font-weight: 600;\n"
"\n"
"    border: none;\n"
"    border-radius: 14px;\n"
"\n"
"    padding: 10px 22px;\n"
"}\n"
"\n"
"/* \342\234\250 HOVER : lumi\303\250re douce */\n"
"QPushButton:hover {\n"
"    background-color: qlineargradient(\n"
"        x1:0, y1:0,\n"
"        x2:0, y2:1,\n"
"        stop:0 #A52A2A,\n"
"        stop:0.5 #CD5C5C,\n"
"        stop:1 #8B0000\n"
"    );\n"
"}\n"
"\n"
"/* \360\237\224\230 CLICK (pressed) */\n"
"QPushButton:pressed {\n"
"    background-color: qlineargradient(\n"
"        x1:0, y1:0,\n"
"        x2:0, y2:1,\n"
"        stop:0 #5C0000,\n"
"        stop:1 #8B0000\n"
"    );\n"
"}\n"
"\n"
"/* \360\237\232\253 D\303\251sactiv\303\251 */\n"
"QPushButton:disabled {\n"
"    background-color: #C8D3DF;\n"
"    color: #6E7F91"
                        ";\n"
"}\n"
""));
        comboTypePropriete_3 = new QComboBox(frame_48);
        comboTypePropriete_3->addItem(QString());
        comboTypePropriete_3->addItem(QString());
        comboTypePropriete_3->addItem(QString());
        comboTypePropriete_3->addItem(QString());
        comboTypePropriete_3->addItem(QString());
        comboTypePropriete_3->addItem(QString());
        comboTypePropriete_3->setObjectName("comboTypePropriete_3");
        comboTypePropriete_3->setGeometry(QRect(1000, 10, 191, 51));
        comboTypePropriete_3->setStyleSheet(QString::fromUtf8("  background-color: #F9FBFD;          /* fond clair \303\251l\303\251gant */\n"
"    border: 2px solid #3A6EA5;           /* bleu marine clair */\n"
"    border-radius: 12px;\n"
"    padding: 10px 14px;\n"
"    color: #0A1F33;                      /* texte bleu marine fonc\303\251 */\n"
"    font-size: 14px;\n"
"    font-weight: 500;"));
        tableWidget_3 = new QTableWidget(frame_2);
        if (tableWidget_3->columnCount() < 7)
            tableWidget_3->setColumnCount(7);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidget_3->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWidget_3->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        tableWidget_3->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        tableWidget_3->setHorizontalHeaderItem(3, __qtablewidgetitem3);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        tableWidget_3->setHorizontalHeaderItem(4, __qtablewidgetitem4);
        QTableWidgetItem *__qtablewidgetitem5 = new QTableWidgetItem();
        tableWidget_3->setHorizontalHeaderItem(5, __qtablewidgetitem5);
        QTableWidgetItem *__qtablewidgetitem6 = new QTableWidgetItem();
        tableWidget_3->setHorizontalHeaderItem(6, __qtablewidgetitem6);
        tableWidget_3->setObjectName("tableWidget_3");
        tableWidget_3->setGeometry(QRect(10, 180, 1201, 761));
        tableWidget_3->setStyleSheet(QString::fromUtf8(""));
        frame_46 = new QFrame(frame_2);
        frame_46->setObjectName("frame_46");
        frame_46->setGeometry(QRect(380, 100, 521, 761));
        frame_46->setVisible(false);
        frame_46->setStyleSheet(QString::fromUtf8("background: white;\n"
"border-radius: 20px;\n"
"padding: 20px;\n"
""));
        frame_46->setFrameShape(QFrame::Shape::StyledPanel);
        frame_46->setFrameShadow(QFrame::Shadow::Raised);
        frame_47 = new QFrame(frame_46);
        frame_47->setObjectName("frame_47");
        frame_47->setGeometry(QRect(0, 0, 521, 71));
        frame_47->setStyleSheet(QString::fromUtf8("background-color: qlineargradient(\n"
"    spread:pad,\n"
"    x1:0, y1:0,\n"
"    x2:0, y2:1,\n"
"    stop:0 #3A6EA5,\n"
"    stop:1 #1E3A5F\n"
");\n"
"\n"
""));
        frame_47->setFrameShape(QFrame::Shape::StyledPanel);
        frame_47->setFrameShadow(QFrame::Shadow::Raised);
        label_168 = new QLabel(frame_47);
        label_168->setObjectName("label_168");
        label_168->setGeometry(QRect(0, 0, 521, 71));
        QFont font2;
        font2.setPointSize(16);
        font2.setBold(true);
        font2.setItalic(false);
        label_168->setFont(font2);
        label_168->setStyleSheet(QString::fromUtf8("background-color: qlineargradient(\n"
"        x1:0, y1:0,\n"
"        x2:0, y2:1,\n"
"        stop:0 #276646,\n"
"        stop:0.5 #34885A,\n"
"        stop:1 #1B3A2F\n"
"    );"));
        label_168->setAlignment(Qt::AlignmentFlag::AlignCenter);
        label_171 = new QLabel(frame_46);
        label_171->setObjectName("label_171");
        label_171->setGeometry(QRect(20, 90, 101, 31));
        QFont font3;
        font3.setPointSize(11);
        font3.setBold(true);
        font3.setItalic(true);
        label_171->setFont(font3);
        label_171->setStyleSheet(QString::fromUtf8(" color: #0A1F33;  "));
        lineEdit_46 = new QLineEdit(frame_46);
        lineEdit_46->setObjectName("lineEdit_46");
        lineEdit_46->setGeometry(QRect(140, 90, 361, 41));
        lineEdit_46->setStyleSheet(QString::fromUtf8("QLineEdit {\n"
"    background-color: #F9FBFD;          /* fond clair \303\251l\303\251gant */\n"
"    border: 2px solid #3A6EA5;           /* bleu marine clair */\n"
"    border-radius: 12px;\n"
"    padding: 10px 14px;\n"
"    color: #0A1F33;                      /* texte bleu marine fonc\303\251 */\n"
"    font-size: 14px;\n"
"    font-weight: 500;\n"
"}\n"
"\n"
"/* Quand le champ est s\303\251lectionn\303\251 */\n"
"QLineEdit:focus {\n"
"    background-color: white;\n"
"    border: 2px solid #1E3A5F;           /* focus plus fonc\303\251 */\n"
"}\n"
"\n"
"/* Hover */\n"
"QLineEdit:hover {\n"
"    border: 2px solid #2F5D8A;\n"
"}\n"
""));
        label_172 = new QLabel(frame_46);
        label_172->setObjectName("label_172");
        label_172->setGeometry(QRect(20, 140, 121, 31));
        label_172->setFont(font3);
        label_172->setStyleSheet(QString::fromUtf8(" color: #0A1F33;  "));
        lineEdit_47 = new QLineEdit(frame_46);
        lineEdit_47->setObjectName("lineEdit_47");
        lineEdit_47->setGeometry(QRect(140, 140, 361, 41));
        lineEdit_47->setStyleSheet(QString::fromUtf8("QLineEdit {\n"
"    background-color: #F9FBFD;          /* fond clair \303\251l\303\251gant */\n"
"    border: 2px solid #3A6EA5;           /* bleu marine clair */\n"
"    border-radius: 12px;\n"
"    padding: 10px 14px;\n"
"    color: #0A1F33;                      /* texte bleu marine fonc\303\251 */\n"
"    font-size: 14px;\n"
"    font-weight: 500;\n"
"}\n"
"\n"
"/* Quand le champ est s\303\251lectionn\303\251 */\n"
"QLineEdit:focus {\n"
"    background-color: white;\n"
"    border: 2px solid #1E3A5F;           /* focus plus fonc\303\251 */\n"
"}\n"
"\n"
"/* Hover */\n"
"QLineEdit:hover {\n"
"    border: 2px solid #2F5D8A;\n"
"}\n"
""));
        label_175 = new QLabel(frame_46);
        label_175->setObjectName("label_175");
        label_175->setGeometry(QRect(20, 190, 151, 31));
        label_175->setFont(font3);
        label_175->setStyleSheet(QString::fromUtf8(" color: #0A1F33;  "));
        lineEdit_48 = new QLineEdit(frame_46);
        lineEdit_48->setObjectName("lineEdit_48");
        lineEdit_48->setGeometry(QRect(140, 190, 361, 41));
        lineEdit_48->setStyleSheet(QString::fromUtf8("QLineEdit {\n"
"    background-color: #F9FBFD;          /* fond clair \303\251l\303\251gant */\n"
"    border: 2px solid #3A6EA5;           /* bleu marine clair */\n"
"    border-radius: 12px;\n"
"    padding: 10px 14px;\n"
"    color: #0A1F33;                      /* texte bleu marine fonc\303\251 */\n"
"    font-size: 14px;\n"
"    font-weight: 500;\n"
"}\n"
"\n"
"/* Quand le champ est s\303\251lectionn\303\251 */\n"
"QLineEdit:focus {\n"
"    background-color: white;\n"
"    border: 2px solid #1E3A5F;           /* focus plus fonc\303\251 */\n"
"}\n"
"\n"
"/* Hover */\n"
"QLineEdit:hover {\n"
"    border: 2px solid #2F5D8A;\n"
"}\n"
""));
        label_177 = new QLabel(frame_46);
        label_177->setObjectName("label_177");
        label_177->setGeometry(QRect(20, 240, 151, 31));
        label_177->setFont(font3);
        label_177->setStyleSheet(QString::fromUtf8(" color: #0A1F33;  "));
        lineEdit_49 = new QLineEdit(frame_46);
        lineEdit_49->setObjectName("lineEdit_49");
        lineEdit_49->setGeometry(QRect(140, 240, 361, 41));
        lineEdit_49->setStyleSheet(QString::fromUtf8("QLineEdit {\n"
"    background-color: #F9FBFD;          /* fond clair \303\251l\303\251gant */\n"
"    border: 2px solid #3A6EA5;           /* bleu marine clair */\n"
"    border-radius: 12px;\n"
"    padding: 10px 14px;\n"
"    color: #0A1F33;                      /* texte bleu marine fonc\303\251 */\n"
"    font-size: 14px;\n"
"    font-weight: 500;\n"
"}\n"
"\n"
"/* Quand le champ est s\303\251lectionn\303\251 */\n"
"QLineEdit:focus {\n"
"    background-color: white;\n"
"    border: 2px solid #1E3A5F;           /* focus plus fonc\303\251 */\n"
"}\n"
"\n"
"/* Hover */\n"
"QLineEdit:hover {\n"
"    border: 2px solid #2F5D8A;\n"
"}\n"
""));
        label_179 = new QLabel(frame_46);
        label_179->setObjectName("label_179");
        label_179->setGeometry(QRect(20, 290, 111, 31));
        label_179->setFont(font3);
        label_179->setStyleSheet(QString::fromUtf8(" color: #0A1F33;  "));
        lineEdit_50 = new QLineEdit(frame_46);
        lineEdit_50->setObjectName("lineEdit_50");
        lineEdit_50->setGeometry(QRect(140, 290, 361, 41));
        lineEdit_50->setStyleSheet(QString::fromUtf8("QLineEdit {\n"
"    background-color: #F9FBFD;          /* fond clair \303\251l\303\251gant */\n"
"    border: 2px solid #3A6EA5;           /* bleu marine clair */\n"
"    border-radius: 12px;\n"
"    padding: 10px 14px;\n"
"    color: #0A1F33;                      /* texte bleu marine fonc\303\251 */\n"
"    font-size: 14px;\n"
"    font-weight: 500;\n"
"}\n"
"\n"
"/* Quand le champ est s\303\251lectionn\303\251 */\n"
"QLineEdit:focus {\n"
"    background-color: white;\n"
"    border: 2px solid #1E3A5F;           /* focus plus fonc\303\251 */\n"
"}\n"
"\n"
"/* Hover */\n"
"QLineEdit:hover {\n"
"    border: 2px solid #2F5D8A;\n"
"}\n"
""));
        label_180 = new QLabel(frame_46);
        label_180->setObjectName("label_180");
        label_180->setGeometry(QRect(20, 340, 111, 31));
        label_180->setFont(font3);
        label_180->setStyleSheet(QString::fromUtf8(" color: #0A1F33;  "));
        comboBox_3 = new QComboBox(frame_46);
        comboBox_3->addItem(QString());
        comboBox_3->addItem(QString());
        comboBox_3->addItem(QString());
        comboBox_3->setObjectName("comboBox_3");
        comboBox_3->setGeometry(QRect(140, 340, 361, 48));
        comboBox_3->setStyleSheet(QString::fromUtf8("QComboBox {\n"
"    background-color: #1F3B5C;\n"
"    color: #EAF3FF;\n"
"    border: 1px solid #3F6FA5;\n"
"    border-radius: 6px;\n"
"    padding: 6px 10px;\n"
"    font-size: 13px;\n"
"    font-family: \"Segoe UI\";\n"
"    min-height: 34px;\n"
"}\n"
"QComboBox::drop-down {\n"
"    subcontrol-origin: padding;\n"
"    subcontrol-position: top right;\n"
"    width: 28px;\n"
"    border-left: 1px solid #3F6FA5;\n"
"}\n"
"\n"
"QComboBox::down-arrow {\n"
"    image: none;\n"
"    width: 0;\n"
"    height: 0;\n"
"    border-left: 5px solid transparent;\n"
"    border-right: 5px solid transparent;\n"
"    border-top: 6px solid #EAF3FF;\n"
"}\n"
"QComboBox QAbstractItemView {\n"
"    background-color: #203A57;\n"
"    color: #EAF3FF;\n"
"    selection-background-color: #2F5F99;\n"
"    selection-color: #FFFFFF;\n"
"    outline: 0;\n"
"    border-radius: 6px;\n"
"}\n"
""));
        label_181 = new QLabel(frame_46);
        label_181->setObjectName("label_181");
        label_181->setGeometry(QRect(20, 390, 111, 31));
        label_181->setFont(font3);
        label_181->setStyleSheet(QString::fromUtf8(" color: #0A1F33;  "));
        comboBox_2 = new QComboBox(frame_46);
        comboBox_2->addItem(QString());
        comboBox_2->addItem(QString());
        comboBox_2->addItem(QString());
        comboBox_2->addItem(QString());
        comboBox_2->setObjectName("comboBox_2");
        comboBox_2->setGeometry(QRect(140, 390, 361, 48));
        comboBox_2->setStyleSheet(QString::fromUtf8("QComboBox {\n"
"    background-color: #1F3B5C;\n"
"    color: #EAF3FF;\n"
"    border: 1px solid #3F6FA5;\n"
"    border-radius: 6px;\n"
"    padding: 6px 10px;\n"
"    font-size: 13px;\n"
"    font-family: \"Segoe UI\";\n"
"    min-height: 34px;\n"
"}\n"
"QComboBox::drop-down {\n"
"    subcontrol-origin: padding;\n"
"    subcontrol-position: top right;\n"
"    width: 28px;\n"
"    border-left: 1px solid #3F6FA5;\n"
"}\n"
"\n"
"QComboBox::down-arrow {\n"
"    image: none;\n"
"    width: 0;\n"
"    height: 0;\n"
"    border-left: 5px solid transparent;\n"
"    border-right: 5px solid transparent;\n"
"    border-top: 6px solid #EAF3FF;\n"
"}\n"
"QComboBox QAbstractItemView {\n"
"    background-color: #203A57;\n"
"    color: #EAF3FF;\n"
"    selection-background-color: #2F5F99;\n"
"    selection-color: #FFFFFF;\n"
"    outline: 0;\n"
"    border-radius: 6px;\n"
"}\n"
""));
        pushButton_22 = new QPushButton(frame_46);
        pushButton_22->setObjectName("pushButton_22");
        pushButton_22->setGeometry(QRect(40, 500, 431, 51));
        pushButton_22->setFont(font);
        pushButton_22->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    background-color: qlineargradient(\n"
"        x1:0, y1:0,\n"
"        x2:0, y2:1,\n"
"        stop:0 #2C5F7C,\n"
"        stop:0.5 #3A6EA5,\n"
"        stop:1 #1B3A57\n"
"    );\n"
"\n"
"    color: white;\n"
"    font-size: 14px;\n"
"    font-weight: 600;\n"
"\n"
"    border: none;\n"
"    border-radius: 14px;\n"
"\n"
"    padding: 10px 22px;\n"
"}\n"
"\n"
"/* \342\234\250 HOVER : lumi\303\250re douce */\n"
"QPushButton:hover {\n"
"    background-color: qlineargradient(\n"
"        x1:0, y1:0,\n"
"        x2:0, y2:1,\n"
"        stop:0 #3A6EA5,\n"
"        stop:0.5 #4A86C5,\n"
"        stop:1 #2C5F7C\n"
"    );\n"
"}\n"
"\n"
"/* \360\237\224\230 CLICK (pressed) */\n"
"QPushButton:pressed {\n"
"    background-color: qlineargradient(\n"
"        x1:0, y1:0,\n"
"        x2:0, y2:1,\n"
"        stop:0 #1B3A57,\n"
"        stop:1 #2C5F7C\n"
"    );\n"
"}\n"
"\n"
"/* \360\237\232\253 D\303\251sactiv\303\251 */\n"
"QPushButton:disabled {\n"
"    background-color: #C8D3DF;\n"
"    color: #6E7F91"
                        ";\n"
"}\n"
""));
        pushButton_annuler_ajout = new QPushButton(frame_46);
        pushButton_annuler_ajout->setObjectName("pushButton_annuler_ajout");
        pushButton_annuler_ajout->setGeometry(QRect(40, 560, 431, 51));
        pushButton_annuler_ajout->setFont(font);
        pushButton_annuler_ajout->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    background-color: #E8ECF0;\n"
"    color: #2A3439;\n"
"    font-size: 14px;\n"
"    font-weight: 600;\n"
"    border: none;\n"
"    border-radius: 14px;\n"
"    padding: 10px 22px;\n"
"}\n"
"\n"
"QPushButton:hover {\n"
"    background-color: #D1DCE5;\n"
"}\n"
""));
        MainWindow->setCentralWidget(centralwidget);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        pushButton_35->setText(QCoreApplication::translate("MainWindow", "\360\237\232\233tournees", nullptr));
        pushButton_36->setText(QCoreApplication::translate("MainWindow", "\360\237\247\221\360\237\217\273\342\200\215\360\237\222\273employ\303\251s", nullptr));
        pushButton_37->setText(QCoreApplication::translate("MainWindow", "\360\237\247\221\342\200\215\360\237\247\221\342\200\215\360\237\247\222\342\200\215\360\237\247\222clients", nullptr));
        pushButton_38->setText(QCoreApplication::translate("MainWindow", "\360\237\232\256conteneurs", nullptr));
        acceuil->setText(QCoreApplication::translate("MainWindow", "\360\237\222\241acceuil", nullptr));
        pushButton_45->setText(QCoreApplication::translate("MainWindow", "\342\231\273\357\270\217recyclage", nullptr));
        dec->setText(QCoreApplication::translate("MainWindow", "\342\232\231\357\270\217deconnextion", nullptr));
        label_79->setText(QString());
        pushButton_21->setText(QCoreApplication::translate("MainWindow", "rechercher", nullptr));
        pushButton_20->setText(QCoreApplication::translate("MainWindow", "\360\237\223\221exporter", nullptr));
        pushButton_19->setText(QCoreApplication::translate("MainWindow", "statistique", nullptr));
        label_18->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-size:16pt; font-weight:700;\">\360\237\221\245 Liste des clients</span></p></body></html>", nullptr));
        pushButton_client_ajouter->setText(QCoreApplication::translate("MainWindow", "\342\236\225 Ajouter", nullptr));
        pushButton_23->setText(QCoreApplication::translate("MainWindow", "\342\234\217\357\270\217 Modifier", nullptr));
        pushButton_10->setText(QCoreApplication::translate("MainWindow", "\360\237\227\221\357\270\217 Supprimer", nullptr));
        comboTypePropriete_3->setItemText(0, QCoreApplication::translate("MainWindow", "\360\237\223\212 Trier par...", nullptr));
        comboTypePropriete_3->setItemText(1, QCoreApplication::translate("MainWindow", "ID", nullptr));
        comboTypePropriete_3->setItemText(2, QCoreApplication::translate("MainWindow", "Nom", nullptr));
        comboTypePropriete_3->setItemText(3, QCoreApplication::translate("MainWindow", "Type", nullptr));
        comboTypePropriete_3->setItemText(4, QCoreApplication::translate("MainWindow", "Zone", nullptr));
        comboTypePropriete_3->setItemText(5, QCoreApplication::translate("MainWindow", "Statut", nullptr));

        QTableWidgetItem *___qtablewidgetitem = tableWidget_3->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("MainWindow", "ID", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidget_3->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("MainWindow", "NOM", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = tableWidget_3->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("MainWindow", "PRENOM", nullptr));
        QTableWidgetItem *___qtablewidgetitem3 = tableWidget_3->horizontalHeaderItem(3);
        ___qtablewidgetitem3->setText(QCoreApplication::translate("MainWindow", "TYPE", nullptr));
        QTableWidgetItem *___qtablewidgetitem4 = tableWidget_3->horizontalHeaderItem(4);
        ___qtablewidgetitem4->setText(QCoreApplication::translate("MainWindow", "ZONE", nullptr));
        QTableWidgetItem *___qtablewidgetitem5 = tableWidget_3->horizontalHeaderItem(5);
        ___qtablewidgetitem5->setText(QCoreApplication::translate("MainWindow", "TELEPHONE", nullptr));
        QTableWidgetItem *___qtablewidgetitem6 = tableWidget_3->horizontalHeaderItem(6);
        ___qtablewidgetitem6->setText(QCoreApplication::translate("MainWindow", "STATUT", nullptr));
        label_168->setText(QCoreApplication::translate("MainWindow", "\360\237\221\244 Informations Personnelles", nullptr));
        label_171->setText(QCoreApplication::translate("MainWindow", "\360\237\221\244 Nom:", nullptr));
        lineEdit_46->setText(QString());
        label_172->setText(QCoreApplication::translate("MainWindow", "\360\237\221\244 Pr\303\251nom:", nullptr));
        lineEdit_47->setText(QString());
        label_175->setText(QCoreApplication::translate("MainWindow", "\360\237\223\236 T\303\251l\303\251phone:", nullptr));
        lineEdit_48->setText(QString());
        label_177->setText(QCoreApplication::translate("MainWindow", "\360\237\217\240 Adresse :", nullptr));
        lineEdit_49->setText(QString());
        label_179->setText(QCoreApplication::translate("MainWindow", "\360\237\206\224 CIN:", nullptr));
        lineEdit_50->setText(QString());
        label_180->setText(QCoreApplication::translate("MainWindow", "\360\237\223\215 Zone :", nullptr));
        comboBox_3->setItemText(0, QCoreApplication::translate("MainWindow", "Tunis Centre", nullptr));
        comboBox_3->setItemText(1, QCoreApplication::translate("MainWindow", "Ariana", nullptr));
        comboBox_3->setItemText(2, QCoreApplication::translate("MainWindow", "Manouba", nullptr));

        label_181->setText(QCoreApplication::translate("MainWindow", "\360\237\217\242 Type :", nullptr));
        comboBox_2->setItemText(0, QCoreApplication::translate("MainWindow", "R\303\251sidentiel", nullptr));
        comboBox_2->setItemText(1, QCoreApplication::translate("MainWindow", "Commerce", nullptr));
        comboBox_2->setItemText(2, QCoreApplication::translate("MainWindow", "Industrie", nullptr));
        comboBox_2->setItemText(3, QCoreApplication::translate("MainWindow", "Public", nullptr));

        comboBox_2->setCurrentText(QCoreApplication::translate("MainWindow", "R\303\251sidentiel", nullptr));
        pushButton_22->setText(QCoreApplication::translate("MainWindow", "\342\234\223 Valider l'ajout", nullptr));
        pushButton_annuler_ajout->setText(QCoreApplication::translate("MainWindow", "\342\234\227 Annuler", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
