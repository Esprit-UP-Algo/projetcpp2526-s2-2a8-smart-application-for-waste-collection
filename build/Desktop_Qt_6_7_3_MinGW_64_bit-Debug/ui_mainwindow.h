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
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QStackedWidget *stackedWidget;
    QWidget *page;
    QFrame *frame_42;
    QFrame *frame_43;
    QLineEdit *lineEdit_39;
    QLineEdit *lineEdit_40;
    QLabel *label_134;
    QLabel *label_135;
    QLabel *label_136;
    QPushButton *mdp;
    QPushButton *cnxemp;
    QLabel *label_137;
    QLabel *label_138;
    QWidget *page_2;
    QFrame *frame_39;
    QFrame *frame_44;
    QLabel *label_139;
    QLabel *label_140;
    QLineEdit *lineEdit_41;
    QLabel *label_141;
    QLabel *label_142;
    QFrame *frame_45;
    QLabel *label_143;
    QLabel *label_144;
    QPushButton *pushButton_8;
    QLabel *label_145;
    QLabel *label_146;
    QPushButton *retour_2;
    QWidget *page_3;
    QWidget *page_4;
    QStackedWidget *stackedWidget_2;
    QWidget *page_5;
    QFrame *frame_9;
    QTableWidget *tableWidget_5;
    QFrame *frame_48;
    QLabel *label_19;
    QPushButton *pushButton_client_ajouter;
    QPushButton *pushButton_23;
    QPushButton *pushButton_10;
    QComboBox *comboTypePropriete_3;
    QWidget *searchBox_5;
    QLineEdit *lineEdit_8;
    QPushButton *pushButton_21;
    QPushButton *pushButton_20;
    QPushButton *pushButton_19;
    QWidget *page_6;
    QFrame *frame_10;
    QWidget *page_7;
    QFrame *frame_46;
    QLabel *label_18;
    QLabel *label_28;
    QLabel *label_31;
    QLabel *label_32;
    QFrame *frame_24;
    QLabel *label_30;
    QWidget *searchBox_8;
    QFrame *frame_22;
    QPushButton *pushButton_39;
    QPushButton *pushButton_40;
    QPushButton *pushButton_41;
    QPushButton *pushButton_42;
    QPushButton *acceuil_2;
    QPushButton *pushButton_47;
    QPushButton *dec_2;
    QLabel *label_80;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(1632, 968);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        stackedWidget = new QStackedWidget(centralwidget);
        stackedWidget->setObjectName("stackedWidget");
        stackedWidget->setGeometry(QRect(0, 0, 1631, 931));
        page = new QWidget();
        page->setObjectName("page");
        frame_42 = new QFrame(page);
        frame_42->setObjectName("frame_42");
        frame_42->setGeometry(QRect(-40, -10, 1581, 951));
        frame_42->setStyleSheet(QString::fromUtf8("background-color: qlineargradient(\n"
"    spread:pad,\n"
"    x1:0, y1:0,\n"
"    x2:0, y2:1,\n"
"    stop:0 #0A1F33,\n"
"    stop:0.5 #163A5F,\n"
"    stop:1 #274C77\n"
");"));
        frame_42->setFrameShape(QFrame::Shape::StyledPanel);
        frame_42->setFrameShadow(QFrame::Shadow::Raised);
        frame_43 = new QFrame(frame_42);
        frame_43->setObjectName("frame_43");
        frame_43->setGeometry(QRect(460, 210, 801, 511));
        frame_43->setStyleSheet(QString::fromUtf8("QFrame#frame_login {\n"
"    background: qlineargradient(\n"
"        x1:0, y1:0,\n"
"        x2:1, y2:1,\n"
"        stop:0 #0B2A3F,\n"
"        stop:0.5 #123F63,\n"
"        stop:1 #1C5D8C\n"
"    );\n"
"    border-radius: 20px;\n"
"    padding: 20px;\n"
"    border: 1px solid rgba(255,255,255,120);\n"
"}\n"
""));
        frame_43->setFrameShape(QFrame::Shape::StyledPanel);
        frame_43->setFrameShadow(QFrame::Shadow::Raised);
        lineEdit_39 = new QLineEdit(frame_43);
        lineEdit_39->setObjectName("lineEdit_39");
        lineEdit_39->setGeometry(QRect(130, 210, 551, 51));
        lineEdit_39->setStyleSheet(QString::fromUtf8("QLineEdit {\n"
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
        lineEdit_40 = new QLineEdit(frame_43);
        lineEdit_40->setObjectName("lineEdit_40");
        lineEdit_40->setGeometry(QRect(130, 320, 551, 51));
        lineEdit_40->setStyleSheet(QString::fromUtf8("QLineEdit {\n"
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
        label_134 = new QLabel(frame_43);
        label_134->setObjectName("label_134");
        label_134->setGeometry(QRect(290, 20, 431, 81));
        QFont font;
        font.setFamilies({QString::fromUtf8("Leelawadee UI")});
        font.setPointSize(24);
        font.setBold(true);
        label_134->setFont(font);
        label_134->setStyleSheet(QString::fromUtf8("color: #FFFFFF\n"
";\n"
"\n"
"border: 0px;\n"
"outline: 0;\n"
"background: transparent;\n"
""));
        label_134->setLineWidth(0);
        label_135 = new QLabel(frame_43);
        label_135->setObjectName("label_135");
        label_135->setGeometry(QRect(140, 140, 441, 101));
        QFont font1;
        font1.setFamilies({QString::fromUtf8("Leelawadee UI")});
        font1.setPointSize(11);
        font1.setBold(true);
        label_135->setFont(font1);
        label_135->setStyleSheet(QString::fromUtf8("\n"
"color: #FFFFFF\n"
";\n"
"border: 0px;\n"
"outline: 0;\n"
"background: transparent;\n"
""));
        label_136 = new QLabel(frame_43);
        label_136->setObjectName("label_136");
        label_136->setGeometry(QRect(130, 250, 441, 91));
        label_136->setFont(font1);
        label_136->setStyleSheet(QString::fromUtf8("\n"
"color: #FFFFFF\n"
";\n"
"border: 0px;\n"
"outline: 0;\n"
"background: transparent;\n"
""));
        mdp = new QPushButton(frame_43);
        mdp->setObjectName("mdp");
        mdp->setGeometry(QRect(410, 390, 221, 71));
        QFont font2;
        font2.setBold(true);
        mdp->setFont(font2);
        mdp->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    background-color: qlineargradient(\n"
"        x1:0, y1:0,\n"
"        x2:0, y2:1,\n"
"        stop:0 #1B3A2F,\n"
"        stop:0.5 #276646,\n"
"        stop:1 #1E4D36\n"
"    );\n"
"    color: white;\n"
"    font-size: 14px;\n"
"    font-weight: 700;      /* un peu plus bold pour valider */\n"
"    text-transform: uppercase;  /* donne un effet bouton d\342\200\231action */\n"
"    border: none;\n"
"    border-radius: 12px;\n"
"    padding: 10px 22px;     /* garde la m\303\252me taille */\n"
"    cursor: pointer;        /* main au survol */\n"
"    transition: all 0.2s ease-in-out; /* effet smooth hover */\n"
"}\n"
"\n"
"/* \342\234\250 Hover : lumi\303\250re douce */\n"
"QPushButton:hover {\n"
"    background-color: qlineargradient(\n"
"        x1:0, y1:0,\n"
"        x2:0, y2:1,\n"
"        stop:0 #276646,\n"
"        stop:0.5 #34885A,\n"
"        stop:1 #1B3A2F\n"
"    );\n"
"    transform: scale(1.03);  /* effet l\303\251ger au survol */\n"
"}\n"
"\n"
"/* \360\237\224\230 Click (press"
                        "ed) */\n"
"QPushButton:pressed {\n"
"    background-color: qlineargradient(\n"
"        x1:0, y1:0,\n"
"        x2:0, y2:1,\n"
"        stop:0 #1E4D36,\n"
"        stop:1 #1B3A2F\n"
"    );\n"
"    transform: scale(0.98); /* effet click */\n"
"}\n"
"\n"
"/* \360\237\232\253 D\303\251sactiv\303\251 */\n"
"QPushButton:disabled {\n"
"    background-color: #A3B7A1;\n"
"    color: #6E7F70;\n"
"    cursor: default;\n"
"}\n"
""));
        cnxemp = new QPushButton(frame_43);
        cnxemp->setObjectName("cnxemp");
        cnxemp->setGeometry(QRect(180, 390, 221, 71));
        cnxemp->setFont(font2);
        cnxemp->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    background-color: qlineargradient(\n"
"        x1:0, y1:0,\n"
"        x2:0, y2:1,\n"
"        stop:0 #1B3A2F,\n"
"        stop:0.5 #276646,\n"
"        stop:1 #1E4D36\n"
"    );\n"
"    color: white;\n"
"    font-size: 14px;\n"
"    font-weight: 700;      /* un peu plus bold pour valider */\n"
"    text-transform: uppercase;  /* donne un effet bouton d\342\200\231action */\n"
"    border: none;\n"
"    border-radius: 12px;\n"
"    padding: 10px 22px;     /* garde la m\303\252me taille */\n"
"    cursor: pointer;        /* main au survol */\n"
"    transition: all 0.2s ease-in-out; /* effet smooth hover */\n"
"}\n"
"\n"
"/* \342\234\250 Hover : lumi\303\250re douce */\n"
"QPushButton:hover {\n"
"    background-color: qlineargradient(\n"
"        x1:0, y1:0,\n"
"        x2:0, y2:1,\n"
"        stop:0 #276646,\n"
"        stop:0.5 #34885A,\n"
"        stop:1 #1B3A2F\n"
"    );\n"
"    transform: scale(1.03);  /* effet l\303\251ger au survol */\n"
"}\n"
"\n"
"/* \360\237\224\230 Click (press"
                        "ed) */\n"
"QPushButton:pressed {\n"
"    background-color: qlineargradient(\n"
"        x1:0, y1:0,\n"
"        x2:0, y2:1,\n"
"        stop:0 #1E4D36,\n"
"        stop:1 #1B3A2F\n"
"    );\n"
"    transform: scale(0.98); /* effet click */\n"
"}\n"
"\n"
"/* \360\237\232\253 D\303\251sactiv\303\251 */\n"
"QPushButton:disabled {\n"
"    background-color: #A3B7A1;\n"
"    color: #6E7F70;\n"
"    cursor: default;\n"
"}\n"
""));
        label_137 = new QLabel(frame_42);
        label_137->setObjectName("label_137");
        label_137->setGeometry(QRect(-100, 0, 1681, 1081));
        label_137->setStyleSheet(QString::fromUtf8("border: 0px;\n"
"outline: 0;\n"
"background: transparent;\n"
""));
        label_137->setPixmap(QPixmap(QString::fromUtf8(":/im2.jpg")));
        label_137->setScaledContents(true);
        label_138 = new QLabel(frame_42);
        label_138->setObjectName("label_138");
        label_138->setGeometry(QRect(170, 290, 391, 351));
        label_138->setStyleSheet(QString::fromUtf8("\n"
"border: 0px;\n"
"outline: 0;\n"
"background: transparent;\n"
""));
        label_138->setPixmap(QPixmap(QString::fromUtf8(":/aa.png")));
        label_138->setScaledContents(true);
        label_137->raise();
        frame_43->raise();
        label_138->raise();
        stackedWidget->addWidget(page);
        page_2 = new QWidget();
        page_2->setObjectName("page_2");
        frame_39 = new QFrame(page_2);
        frame_39->setObjectName("frame_39");
        frame_39->setGeometry(QRect(0, -10, 1571, 901));
        frame_39->setStyleSheet(QString::fromUtf8("background-color: qlineargradient(\n"
"    spread:pad,\n"
"    x1:0, y1:0,\n"
"    x2:0, y2:1,\n"
"    stop:0 #0A1F33,\n"
"    stop:0.5 #163A5F,\n"
"    stop:1 #274C77\n"
");"));
        frame_39->setFrameShape(QFrame::Shape::StyledPanel);
        frame_39->setFrameShadow(QFrame::Shadow::Raised);
        frame_44 = new QFrame(frame_39);
        frame_44->setObjectName("frame_44");
        frame_44->setGeometry(QRect(320, 190, 901, 631));
        frame_44->setStyleSheet(QString::fromUtf8("background: white;\n"
"border-radius: 20px;\n"
"padding: 20px;\n"
""));
        frame_44->setFrameShape(QFrame::Shape::StyledPanel);
        frame_44->setFrameShadow(QFrame::Shadow::Raised);
        label_139 = new QLabel(frame_44);
        label_139->setObjectName("label_139");
        label_139->setGeometry(QRect(280, -10, 381, 121));
        QFont font3;
        font3.setPointSize(26);
        font3.setBold(true);
        font3.setItalic(true);
        label_139->setFont(font3);
        label_139->setStyleSheet(QString::fromUtf8("color: #2A3439;\n"
""));
        label_140 = new QLabel(frame_44);
        label_140->setObjectName("label_140");
        label_140->setGeometry(QRect(320, 80, 311, 61));
        QFont font4;
        font4.setPointSize(12);
        label_140->setFont(font4);
        label_140->setStyleSheet(QString::fromUtf8("color: #2A3439;\n"
""));
        lineEdit_41 = new QLineEdit(frame_44);
        lineEdit_41->setObjectName("lineEdit_41");
        lineEdit_41->setGeometry(QRect(220, 460, 451, 51));
        lineEdit_41->setStyleSheet(QString::fromUtf8("QLineEdit {\n"
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
        label_141 = new QLabel(frame_44);
        label_141->setObjectName("label_141");
        label_141->setGeometry(QRect(210, 380, 441, 101));
        label_141->setFont(font1);
        label_141->setStyleSheet(QString::fromUtf8("color: #2A3439;\n"
""));
        label_142 = new QLabel(frame_44);
        label_142->setObjectName("label_142");
        label_142->setGeometry(QRect(150, 130, 611, 121));
        QFont font5;
        font5.setPointSize(20);
        font5.setBold(true);
        font5.setItalic(false);
        label_142->setFont(font5);
        label_142->setStyleSheet(QString::fromUtf8("color: #2A3439;\n"
""));
        frame_45 = new QFrame(frame_44);
        frame_45->setObjectName("frame_45");
        frame_45->setGeometry(QRect(10, 230, 871, 151));
        frame_45->setStyleSheet(QString::fromUtf8("background-color: qlineargradient(\n"
"    spread:pad,\n"
"    x1:0, y1:0,\n"
"    x2:0, y2:1,\n"
"    stop:0 #7FB3D5,\n"
"    stop:1 #5DADE2\n"
");\n"
"\n"
"\n"
""));
        frame_45->setFrameShape(QFrame::Shape::StyledPanel);
        frame_45->setFrameShadow(QFrame::Shadow::Raised);
        label_143 = new QLabel(frame_45);
        label_143->setObjectName("label_143");
        label_143->setGeometry(QRect(30, 0, 841, 151));
        QFont font6;
        font6.setPointSize(11);
        font6.setBold(false);
        font6.setItalic(false);
        label_143->setFont(font6);
        label_143->setStyleSheet(QString::fromUtf8(" color: #0A1F33;  "));
        label_144 = new QLabel(frame_44);
        label_144->setObjectName("label_144");
        label_144->setGeometry(QRect(210, 500, 541, 61));
        QFont font7;
        font7.setPointSize(9);
        label_144->setFont(font7);
        label_144->setStyleSheet(QString::fromUtf8("color: #2A3439;\n"
""));
        pushButton_8 = new QPushButton(frame_44);
        pushButton_8->setObjectName("pushButton_8");
        pushButton_8->setGeometry(QRect(270, 560, 371, 41));
        pushButton_8->setFont(font2);
        pushButton_8->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    background-color: qlineargradient(\n"
"        x1:0, y1:0,\n"
"        x2:0, y2:1,\n"
"        stop:0 #1B3A2F,\n"
"        stop:0.5 #276646,\n"
"        stop:1 #1E4D36\n"
"    );\n"
"    color: white;\n"
"    font-size: 14px;\n"
"    font-weight: 700;      /* un peu plus bold pour valider */\n"
"    text-transform: uppercase;  /* donne un effet bouton d\342\200\231action */\n"
"    border: none;\n"
"    border-radius: 12px;\n"
"    padding: 10px 22px;     /* garde la m\303\252me taille */\n"
"    cursor: pointer;        /* main au survol */\n"
"    transition: all 0.2s ease-in-out; /* effet smooth hover */\n"
"}\n"
"\n"
"/* \342\234\250 Hover : lumi\303\250re douce */\n"
"QPushButton:hover {\n"
"    background-color: qlineargradient(\n"
"        x1:0, y1:0,\n"
"        x2:0, y2:1,\n"
"        stop:0 #276646,\n"
"        stop:0.5 #34885A,\n"
"        stop:1 #1B3A2F\n"
"    );\n"
"    transform: scale(1.03);  /* effet l\303\251ger au survol */\n"
"}\n"
"\n"
"/* \360\237\224\230 Click (press"
                        "ed) */\n"
"QPushButton:pressed {\n"
"    background-color: qlineargradient(\n"
"        x1:0, y1:0,\n"
"        x2:0, y2:1,\n"
"        stop:0 #1E4D36,\n"
"        stop:1 #1B3A2F\n"
"    );\n"
"    transform: scale(0.98); /* effet click */\n"
"}\n"
"\n"
"/* \360\237\232\253 D\303\251sactiv\303\251 */\n"
"QPushButton:disabled {\n"
"    background-color: #A3B7A1;\n"
"    color: #6E7F70;\n"
"    cursor: default;\n"
"}\n"
""));
        label_144->raise();
        label_141->raise();
        label_139->raise();
        label_140->raise();
        lineEdit_41->raise();
        label_142->raise();
        frame_45->raise();
        pushButton_8->raise();
        label_145 = new QLabel(frame_39);
        label_145->setObjectName("label_145");
        label_145->setGeometry(QRect(710, 60, 111, 111));
        QFont font8;
        font8.setPointSize(48);
        label_145->setFont(font8);
        label_145->setStyleSheet(QString::fromUtf8("border-radius: 20px;"));
        label_146 = new QLabel(frame_39);
        label_146->setObjectName("label_146");
        label_146->setGeometry(QRect(-560, -40, 2141, 1021));
        label_146->setPixmap(QPixmap(QString::fromUtf8(":/im2.jpg")));
        label_146->setScaledContents(true);
        retour_2 = new QPushButton(frame_39);
        retour_2->setObjectName("retour_2");
        retour_2->setGeometry(QRect(1340, 780, 141, 41));
        retour_2->setFont(font2);
        retour_2->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    background-color: qlineargradient(\n"
"        x1:0, y1:0,\n"
"        x2:0, y2:1,\n"
"        stop:0 #1B3A2F,\n"
"        stop:0.5 #276646,\n"
"        stop:1 #1E4D36\n"
"    );\n"
"    color: white;\n"
"    font-size: 14px;\n"
"    font-weight: 700;      /* un peu plus bold pour valider */\n"
"    text-transform: uppercase;  /* donne un effet bouton d\342\200\231action */\n"
"    border: none;\n"
"    border-radius: 12px;\n"
"    padding: 10px 22px;     /* garde la m\303\252me taille */\n"
"    cursor: pointer;        /* main au survol */\n"
"    transition: all 0.2s ease-in-out; /* effet smooth hover */\n"
"}\n"
"\n"
"/* \342\234\250 Hover : lumi\303\250re douce */\n"
"QPushButton:hover {\n"
"    background-color: qlineargradient(\n"
"        x1:0, y1:0,\n"
"        x2:0, y2:1,\n"
"        stop:0 #276646,\n"
"        stop:0.5 #34885A,\n"
"        stop:1 #1B3A2F\n"
"    );\n"
"    transform: scale(1.03);  /* effet l\303\251ger au survol */\n"
"}\n"
"\n"
"/* \360\237\224\230 Click (press"
                        "ed) */\n"
"QPushButton:pressed {\n"
"    background-color: qlineargradient(\n"
"        x1:0, y1:0,\n"
"        x2:0, y2:1,\n"
"        stop:0 #1E4D36,\n"
"        stop:1 #1B3A2F\n"
"    );\n"
"    transform: scale(0.98); /* effet click */\n"
"}\n"
"\n"
"/* \360\237\232\253 D\303\251sactiv\303\251 */\n"
"QPushButton:disabled {\n"
"    background-color: #A3B7A1;\n"
"    color: #6E7F70;\n"
"    cursor: default;\n"
"}\n"
""));
        label_146->raise();
        frame_44->raise();
        label_145->raise();
        retour_2->raise();
        stackedWidget->addWidget(page_2);
        page_3 = new QWidget();
        page_3->setObjectName("page_3");
        stackedWidget->addWidget(page_3);
        page_4 = new QWidget();
        page_4->setObjectName("page_4");
        stackedWidget_2 = new QStackedWidget(page_4);
        stackedWidget_2->setObjectName("stackedWidget_2");
        stackedWidget_2->setGeometry(QRect(310, 0, 1281, 931));
        page_5 = new QWidget();
        page_5->setObjectName("page_5");
        frame_9 = new QFrame(page_5);
        frame_9->setObjectName("frame_9");
        frame_9->setEnabled(true);
        frame_9->setGeometry(QRect(-10, -10, 1271, 951));
        frame_9->setMaximumSize(QSize(1500, 1500));
        frame_9->setStyleSheet(QString::fromUtf8("background-color: qlineargradient(\n"
"    spread:pad,\n"
"    x1:0, y1:0,\n"
"    x2:0, y2:1,\n"
"    stop:0 #0A1F33,\n"
"    stop:0.5 #163A5F,\n"
"    stop:1 #274C77\n"
");\n"
"\n"
""));
        frame_9->setFrameShape(QFrame::Shape::StyledPanel);
        frame_9->setFrameShadow(QFrame::Shadow::Raised);
        tableWidget_5 = new QTableWidget(frame_9);
        if (tableWidget_5->columnCount() < 10)
            tableWidget_5->setColumnCount(10);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidget_5->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWidget_5->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        tableWidget_5->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        tableWidget_5->setHorizontalHeaderItem(3, __qtablewidgetitem3);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        tableWidget_5->setHorizontalHeaderItem(4, __qtablewidgetitem4);
        QTableWidgetItem *__qtablewidgetitem5 = new QTableWidgetItem();
        tableWidget_5->setHorizontalHeaderItem(5, __qtablewidgetitem5);
        QTableWidgetItem *__qtablewidgetitem6 = new QTableWidgetItem();
        tableWidget_5->setHorizontalHeaderItem(6, __qtablewidgetitem6);
        QTableWidgetItem *__qtablewidgetitem7 = new QTableWidgetItem();
        tableWidget_5->setHorizontalHeaderItem(7, __qtablewidgetitem7);
        QTableWidgetItem *__qtablewidgetitem8 = new QTableWidgetItem();
        tableWidget_5->setHorizontalHeaderItem(8, __qtablewidgetitem8);
        QTableWidgetItem *__qtablewidgetitem9 = new QTableWidgetItem();
        tableWidget_5->setHorizontalHeaderItem(9, __qtablewidgetitem9);
        if (tableWidget_5->rowCount() < 2)
            tableWidget_5->setRowCount(2);
        tableWidget_5->setObjectName("tableWidget_5");
        tableWidget_5->setGeometry(QRect(20, 220, 1181, 621));
        tableWidget_5->setStyleSheet(QString::fromUtf8("/* \342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\n"
"   TABLEAU PROFESSIONNEL - STYLE ASSORTI AUX BOUTONS\n"
"   Palette : Bleu marine (#2C5F7C, #3A6EA5, #1B3A57)\n"
"   \342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220"
                        "\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220\342\225\220 */\n"
"\n"
"/* \360\237\223\213 TABLE PRINCIPALE */\n"
"QTableWidget, QTableView {\n"
"    background-color: #FFFFFF;\n"
"    alternate-background-color: #F5F8FA;\n"
"    gridline-color: #D4E1E9;\n"
"    border: 2px solid #2C5F7C;\n"
"    border-radius: 12px;\n"
"    selection-background-color: #3A6EA5;\n"
"    selection-color: white;\n"
"    font-size: 13px;\n"
"    font-weight: 500;\n"
"}\n"
"\n"
"/* \360\237\223\214 EN-T\303\212TE (HEADER) */\n"
"QHeaderView::section {\n"
"    background-color: qline"
                        "argradient(\n"
"        x1:0, y1:0,\n"
"        x2:0, y2:1,\n"
"        stop:0 #2C5F7C,\n"
"        stop:0.5 #3A6EA5,\n"
"        stop:1 #1B3A57\n"
"    );\n"
"    color: white;\n"
"    padding: 14px 18px;\n"
"    border: none;\n"
"    border-right: 1px solid #1B3A57;\n"
"    font-weight: 600;\n"
"    font-size: 14px;\n"
"    text-align: left;\n"
"}\n"
"\n"
"QHeaderView::section:hover {\n"
"    background-color: qlineargradient(\n"
"        x1:0, y1:0,\n"
"        x2:0, y2:1,\n"
"        stop:0 #3A6EA5,\n"
"        stop:0.5 #4A86C5,\n"
"        stop:1 #2C5F7C\n"
"    );\n"
"}\n"
"\n"
"QHeaderView::section:first {\n"
"    border-top-left-radius: 10px;\n"
"}\n"
"\n"
"QHeaderView::section:last {\n"
"    border-top-right-radius: 10px;\n"
"    border-right: none;\n"
"}\n"
"\n"
"QHeaderView::section:pressed {\n"
"    background-color: qlineargradient(\n"
"        x1:0, y1:0,\n"
"        x2:0, y2:1,\n"
"        stop:0 #1B3A57,\n"
"        stop:1 #2C5F7C\n"
"    );\n"
"}\n"
"\n"
"/* \360\237\223\212 CELLULES */\n"
"QT"
                        "ableWidget::item, QTableView::item {\n"
"    padding: 12px 18px;\n"
"    border-bottom: 1px solid #E8EFF4;\n"
"    color: #1B3A57;\n"
"}\n"
"\n"
"QTableWidget::item:selected, QTableView::item:selected {\n"
"    background-color: qlineargradient(\n"
"        x1:0, y1:0,\n"
"        x2:0, y2:1,\n"
"        stop:0 #3A6EA5,\n"
"        stop:1 #2C5F7C\n"
"    );\n"
"    color: white;\n"
"    font-weight: 600;\n"
"}\n"
"\n"
"QTableWidget::item:hover, QTableView::item:hover {\n"
"    background-color: #E3EDF5;\n"
"}\n"
"\n"
"/* \360\237\223\234 SCROLLBAR VERTICALE */\n"
"QScrollBar:vertical {\n"
"    background: #F5F8FA;\n"
"    width: 14px;\n"
"    border-radius: 7px;\n"
"    margin: 0px;\n"
"}\n"
"\n"
"QScrollBar::handle:vertical {\n"
"    background-color: qlineargradient(\n"
"        x1:0, y1:0,\n"
"        x2:1, y2:0,\n"
"        stop:0 #2C5F7C,\n"
"        stop:1 #3A6EA5\n"
"    );\n"
"    border-radius: 7px;\n"
"    min-height: 30px;\n"
"}\n"
"\n"
"QScrollBar::handle:vertical:hover {\n"
"    background-color: "
                        "qlineargradient(\n"
"        x1:0, y1:0,\n"
"        x2:1, y2:0,\n"
"        stop:0 #3A6EA5,\n"
"        stop:1 #4A86C5\n"
"    );\n"
"}\n"
"\n"
"QScrollBar::handle:vertical:pressed {\n"
"    background-color: #1B3A57;\n"
"}\n"
"\n"
"QScrollBar::add-line:vertical,\n"
"QScrollBar::sub-line:vertical {\n"
"    height: 0px;\n"
"}\n"
"\n"
"QScrollBar::add-page:vertical,\n"
"QScrollBar::sub-page:vertical {\n"
"    background: none;\n"
"}\n"
"\n"
"/* \360\237\223\234 SCROLLBAR HORIZONTALE */\n"
"QScrollBar:horizontal {\n"
"    background: #F5F8FA;\n"
"    height: 14px;\n"
"    border-radius: 7px;\n"
"    margin: 0px;\n"
"}\n"
"\n"
"QScrollBar::handle:horizontal {\n"
"    background-color: qlineargradient(\n"
"        x1:0, y1:0,\n"
"        x2:0, y2:1,\n"
"        stop:0 #2C5F7C,\n"
"        stop:1 #3A6EA5\n"
"    );\n"
"    border-radius: 7px;\n"
"    min-width: 30px;\n"
"}\n"
"\n"
"QScrollBar::handle:horizontal:hover {\n"
"    background-color: qlineargradient(\n"
"        x1:0, y1:0,\n"
"        x2:0, y2:1,\n"
"  "
                        "      stop:0 #3A6EA5,\n"
"        stop:1 #4A86C5\n"
"    );\n"
"}\n"
"\n"
"QScrollBar::handle:horizontal:pressed {\n"
"    background-color: #1B3A57;\n"
"}\n"
"\n"
"QScrollBar::add-line:horizontal,\n"
"QScrollBar::sub-line:horizontal {\n"
"    width: 0px;\n"
"}\n"
"\n"
"QScrollBar::add-page:horizontal,\n"
"QScrollBar::sub-page:horizontal {\n"
"    background: none;\n"
"}\n"
"\n"
"/* \360\237\224\215 COIN (intersection scrollbars) */\n"
"QTableWidget::corner, QTableView::corner {\n"
"    background-color: qlineargradient(\n"
"        x1:0, y1:0,\n"
"        x2:0, y2:1,\n"
"        stop:0 #2C5F7C,\n"
"        stop:1 #1B3A57\n"
"    );\n"
"    border: none;\n"
"}\n"
"\n"
"/* \360\237\216\257 LIGNE ALTERN\303\211E (optionnel) */\n"
"QTableWidget::item:alternate, QTableView::item:alternate {\n"
"    background-color: #F5F8FA;\n"
"}"));
        frame_48 = new QFrame(frame_9);
        frame_48->setObjectName("frame_48");
        frame_48->setGeometry(QRect(20, 130, 1181, 71));
        frame_48->setStyleSheet(QString::fromUtf8("QFrame {\n"
"    background-color: white;\n"
"    border-radius: 15px;\n"
"}\n"
"\n"
""));
        frame_48->setFrameShape(QFrame::Shape::StyledPanel);
        frame_48->setFrameShadow(QFrame::Shadow::Raised);
        label_19 = new QLabel(frame_48);
        label_19->setObjectName("label_19");
        label_19->setGeometry(QRect(20, 10, 301, 51));
        label_19->setStyleSheet(QString::fromUtf8("color: #2A3439;\n"
""));
        pushButton_client_ajouter = new QPushButton(frame_48);
        pushButton_client_ajouter->setObjectName("pushButton_client_ajouter");
        pushButton_client_ajouter->setGeometry(QRect(570, 10, 131, 51));
        QFont font9;
        font9.setWeight(QFont::DemiBold);
        font9.setItalic(false);
        pushButton_client_ajouter->setFont(font9);
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
        pushButton_23->setFont(font9);
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
        pushButton_10->setFont(font9);
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
        comboTypePropriete_3->setGeometry(QRect(1000, 10, 171, 51));
        comboTypePropriete_3->setStyleSheet(QString::fromUtf8("  background-color: #F9FBFD;          /* fond clair \303\251l\303\251gant */\n"
"    border: 2px solid #3A6EA5;           /* bleu marine clair */\n"
"    border-radius: 12px;\n"
"    padding: 10px 14px;\n"
"    color: #0A1F33;                      /* texte bleu marine fonc\303\251 */\n"
"    font-size: 14px;\n"
"    font-weight: 500;"));
        searchBox_5 = new QWidget(frame_9);
        searchBox_5->setObjectName("searchBox_5");
        searchBox_5->setGeometry(QRect(20, 40, 1181, 71));
        searchBox_5->setStyleSheet(QString::fromUtf8("background: white;\n"
"border-radius: 20px;\n"
"padding: 20px;\n"
"\n"
""));
        lineEdit_8 = new QLineEdit(searchBox_5);
        lineEdit_8->setObjectName("lineEdit_8");
        lineEdit_8->setGeometry(QRect(10, 10, 551, 51));
        QFont font10;
        font10.setWeight(QFont::Medium);
        lineEdit_8->setFont(font10);
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
        pushButton_21->setGeometry(QRect(570, 10, 131, 51));
        pushButton_21->setFont(font9);
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
        pushButton_20->setGeometry(QRect(850, 10, 131, 51));
        pushButton_20->setFont(font9);
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
        pushButton_19->setGeometry(QRect(1000, 10, 131, 51));
        pushButton_19->setFont(font9);
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
        stackedWidget_2->addWidget(page_5);
        page_6 = new QWidget();
        page_6->setObjectName("page_6");
        frame_10 = new QFrame(page_6);
        frame_10->setObjectName("frame_10");
        frame_10->setEnabled(true);
        frame_10->setGeometry(QRect(0, -10, 1281, 961));
        frame_10->setMaximumSize(QSize(1500, 1500));
        frame_10->setStyleSheet(QString::fromUtf8("background-color: qlineargradient(\n"
"    spread:pad,\n"
"    x1:0, y1:0,\n"
"    x2:0, y2:1,\n"
"    stop:0 #0A1F33,\n"
"    stop:0.5 #163A5F,\n"
"    stop:1 #274C77\n"
");\n"
"\n"
""));
        frame_10->setFrameShape(QFrame::Shape::StyledPanel);
        frame_10->setFrameShadow(QFrame::Shadow::Raised);
        stackedWidget_2->addWidget(page_6);
        page_7 = new QWidget();
        page_7->setObjectName("page_7");
        frame_46 = new QFrame(page_7);
        frame_46->setObjectName("frame_46");
        frame_46->setGeometry(QRect(-40, 0, 1291, 1161));
        frame_46->setStyleSheet(QString::fromUtf8("background-color: qlineargradient(\n"
"    spread:pad,\n"
"    x1:0, y1:0,\n"
"    x2:0, y2:1,\n"
"    stop:0 #0A1F33,\n"
"    stop:0.5 #163A5F,\n"
"    stop:1 #274C77\n"
");"));
        frame_46->setFrameShape(QFrame::Shape::StyledPanel);
        frame_46->setFrameShadow(QFrame::Shadow::Raised);
        label_18 = new QLabel(frame_46);
        label_18->setObjectName("label_18");
        label_18->setGeometry(QRect(170, 70, 1011, 81));
        QFont font11;
        font11.setFamilies({QString::fromUtf8("Old Antic")});
        font11.setPointSize(36);
        font11.setBold(true);
        label_18->setFont(font11);
        label_18->setStyleSheet(QString::fromUtf8("\n"
"color: #FFFFFF\n"
";\n"
"border: 0px;\n"
"outline: 0;\n"
"background: transparent;\n"
""));
        label_28 = new QLabel(frame_46);
        label_28->setObjectName("label_28");
        label_28->setGeometry(QRect(400, 160, 481, 81));
        QFont font12;
        font12.setPointSize(11);
        font12.setItalic(true);
        label_28->setFont(font12);
        label_28->setStyleSheet(QString::fromUtf8("\n"
"color: #FFFFFF\n"
";\n"
"border: 0px;\n"
"outline: 0;\n"
"background: transparent;\n"
""));
        label_31 = new QLabel(frame_46);
        label_31->setObjectName("label_31");
        label_31->setGeometry(QRect(350, 740, 681, 81));
        label_31->setFont(font2);
        label_31->setStyleSheet(QString::fromUtf8("\n"
"color: #FFFFFF\n"
";\n"
"border: 0px;\n"
"outline: 0;\n"
"background: transparent;\n"
""));
        label_32 = new QLabel(frame_46);
        label_32->setObjectName("label_32");
        label_32->setGeometry(QRect(440, 260, 371, 351));
        label_32->setStyleSheet(QString::fromUtf8("\n"
"color: #FFFFFF\n"
";\n"
"border: 0px;\n"
"outline: 0;\n"
"background: transparent;\n"
""));
        label_32->setPixmap(QPixmap(QString::fromUtf8(":/Downloads/p.png")));
        label_32->setScaledContents(true);
        frame_24 = new QFrame(frame_46);
        frame_24->setObjectName("frame_24");
        frame_24->setGeometry(QRect(210, 670, 881, 71));
        frame_24->setStyleSheet(QString::fromUtf8("  background-color: #FFFFFF; /* fond blanc */\n"
"    border-radius: 20px;       /* coins arrondis */\n"
"    border: 2px solid rgba(44, 95, 124, 0.08); /* bord gris clair */"));
        frame_24->setFrameShape(QFrame::Shape::StyledPanel);
        frame_24->setFrameShadow(QFrame::Shadow::Raised);
        label_30 = new QLabel(frame_24);
        label_30->setObjectName("label_30");
        label_30->setGeometry(QRect(120, 30, 661, 20));
        QFont font13;
        font13.setPointSize(11);
        font13.setBold(true);
        font13.setItalic(true);
        label_30->setFont(font13);
        label_30->setStyleSheet(QString::fromUtf8("color: #2A3439;\n"
"\n"
";\n"
"border: 0px;\n"
"outline: 0;\n"
"background: transparent;\n"
""));
        stackedWidget_2->addWidget(page_7);
        searchBox_8 = new QWidget(page_4);
        searchBox_8->setObjectName("searchBox_8");
        searchBox_8->setGeometry(QRect(0, 0, 311, 951));
        searchBox_8->setStyleSheet(QString::fromUtf8("background-color: qlineargradient(\n"
"    spread:pad,\n"
"    x1:0, y1:0,\n"
"    x2:0, y2:1,\n"
"    stop:0 #0A1F33,\n"
"    stop:0.5 #163A5F,\n"
"    stop:1 #274C77\n"
");\n"
""));
        frame_22 = new QFrame(searchBox_8);
        frame_22->setObjectName("frame_22");
        frame_22->setGeometry(QRect(40, 20, 251, 811));
        frame_22->setStyleSheet(QString::fromUtf8("  background-color: #FFFFFF; /* fond blanc */\n"
"    border-radius: 20px;       /* coins arrondis */\n"
"    border: 2px solid rgba(44, 95, 124, 0.08); /* bord gris clair */"));
        frame_22->setFrameShape(QFrame::Shape::StyledPanel);
        frame_22->setFrameShadow(QFrame::Shadow::Raised);
        pushButton_39 = new QPushButton(frame_22);
        pushButton_39->setObjectName("pushButton_39");
        pushButton_39->setGeometry(QRect(10, 510, 221, 51));
        pushButton_39->setFont(font9);
        pushButton_39->setStyleSheet(QString::fromUtf8("QPushButton {\n"
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
        pushButton_40 = new QPushButton(frame_22);
        pushButton_40->setObjectName("pushButton_40");
        pushButton_40->setGeometry(QRect(10, 330, 221, 51));
        pushButton_40->setFont(font9);
        pushButton_40->setStyleSheet(QString::fromUtf8("QPushButton {\n"
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
        pushButton_41 = new QPushButton(frame_22);
        pushButton_41->setObjectName("pushButton_41");
        pushButton_41->setGeometry(QRect(10, 390, 221, 51));
        pushButton_41->setFont(font9);
        pushButton_41->setStyleSheet(QString::fromUtf8("QPushButton {\n"
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
        pushButton_42 = new QPushButton(frame_22);
        pushButton_42->setObjectName("pushButton_42");
        pushButton_42->setGeometry(QRect(10, 450, 221, 51));
        pushButton_42->setFont(font9);
        pushButton_42->setStyleSheet(QString::fromUtf8("QPushButton {\n"
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
        acceuil_2 = new QPushButton(frame_22);
        acceuil_2->setObjectName("acceuil_2");
        acceuil_2->setGeometry(QRect(10, 270, 221, 51));
        acceuil_2->setFont(font9);
        acceuil_2->setStyleSheet(QString::fromUtf8("QPushButton {\n"
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
        pushButton_47 = new QPushButton(frame_22);
        pushButton_47->setObjectName("pushButton_47");
        pushButton_47->setGeometry(QRect(10, 570, 221, 51));
        pushButton_47->setFont(font9);
        pushButton_47->setStyleSheet(QString::fromUtf8("QPushButton {\n"
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
        dec_2 = new QPushButton(frame_22);
        dec_2->setObjectName("dec_2");
        dec_2->setGeometry(QRect(10, 750, 221, 51));
        dec_2->setFont(font9);
        dec_2->setStyleSheet(QString::fromUtf8("QPushButton {\n"
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
        label_80 = new QLabel(frame_22);
        label_80->setObjectName("label_80");
        label_80->setGeometry(QRect(0, 0, 251, 271));
        label_80->setPixmap(QPixmap(QString::fromUtf8(":/aa.png")));
        label_80->setScaledContents(true);
        stackedWidget->addWidget(page_4);
        MainWindow->setCentralWidget(centralwidget);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        stackedWidget->setCurrentIndex(1);
        stackedWidget_2->setCurrentIndex(1);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        lineEdit_39->setText(QString());
        lineEdit_40->setText(QString());
        label_134->setText(QCoreApplication::translate("MainWindow", "connextion", nullptr));
        label_135->setText(QCoreApplication::translate("MainWindow", "Adresse email:", nullptr));
        label_136->setText(QCoreApplication::translate("MainWindow", "Mot de passe:", nullptr));
        mdp->setText(QCoreApplication::translate("MainWindow", "\342\235\214Mot de passe oublier", nullptr));
        cnxemp->setText(QCoreApplication::translate("MainWindow", "\342\234\205connextion", nullptr));
        label_137->setText(QString());
        label_138->setText(QString());
        label_139->setText(QCoreApplication::translate("MainWindow", "R\303\251cup\303\251ration", nullptr));
        label_140->setText(QCoreApplication::translate("MainWindow", "Mot de passe oubli\303\251", nullptr));
        lineEdit_41->setText(QString());
        label_141->setText(QCoreApplication::translate("MainWindow", "Adresse email:", nullptr));
        label_142->setText(QCoreApplication::translate("MainWindow", "\360\237\223\247R\303\251initialiser votre mot de passe", nullptr));
        label_143->setText(QCoreApplication::translate("MainWindow", "\342\204\271\357\270\217\n"
"Information importante\n"
"Un email contenant un lien de r\303\251initialisation sera envoy\303\251 \303\240 l'adresse associ\303\251e \303\240 votre compte. Le lien sera\n"
"valide pendant 1 heure.", nullptr));
        label_144->setText(QCoreApplication::translate("MainWindow", "Entrez l'email ou l'identifiant associ\303\251 \303\240 votre compte", nullptr));
        pushButton_8->setText(QCoreApplication::translate("MainWindow", "envoyer ", nullptr));
        label_145->setText(QCoreApplication::translate("MainWindow", "\360\237\224\220", nullptr));
        label_146->setText(QString());
        retour_2->setText(QCoreApplication::translate("MainWindow", "retour", nullptr));
        QTableWidgetItem *___qtablewidgetitem = tableWidget_5->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("MainWindow", "nom", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidget_5->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("MainWindow", "Nouvelle colonne", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = tableWidget_5->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("MainWindow", "date", nullptr));
        QTableWidgetItem *___qtablewidgetitem3 = tableWidget_5->horizontalHeaderItem(3);
        ___qtablewidgetitem3->setText(QCoreApplication::translate("MainWindow", "cin", nullptr));
        QTableWidgetItem *___qtablewidgetitem4 = tableWidget_5->horizontalHeaderItem(4);
        ___qtablewidgetitem4->setText(QCoreApplication::translate("MainWindow", "id", nullptr));
        QTableWidgetItem *___qtablewidgetitem5 = tableWidget_5->horizontalHeaderItem(5);
        ___qtablewidgetitem5->setText(QCoreApplication::translate("MainWindow", "Nouvelle colonne", nullptr));
        QTableWidgetItem *___qtablewidgetitem6 = tableWidget_5->horizontalHeaderItem(6);
        ___qtablewidgetitem6->setText(QCoreApplication::translate("MainWindow", "service", nullptr));
        QTableWidgetItem *___qtablewidgetitem7 = tableWidget_5->horizontalHeaderItem(7);
        ___qtablewidgetitem7->setText(QCoreApplication::translate("MainWindow", "prenom", nullptr));
        QTableWidgetItem *___qtablewidgetitem8 = tableWidget_5->horizontalHeaderItem(8);
        ___qtablewidgetitem8->setText(QCoreApplication::translate("MainWindow", "Nouvelle colonne", nullptr));
        QTableWidgetItem *___qtablewidgetitem9 = tableWidget_5->horizontalHeaderItem(9);
        ___qtablewidgetitem9->setText(QCoreApplication::translate("MainWindow", "mail", nullptr));
        label_19->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-size:16pt; font-weight:700;\">\360\237\221\245 Liste des employ\303\251s:</span></p></body></html>", nullptr));
        pushButton_client_ajouter->setText(QCoreApplication::translate("MainWindow", "\342\236\225 Ajouter", nullptr));
        pushButton_23->setText(QCoreApplication::translate("MainWindow", "\342\234\217\357\270\217 Modifier", nullptr));
        pushButton_10->setText(QCoreApplication::translate("MainWindow", "\360\237\227\221\357\270\217 Supprimer", nullptr));
        comboTypePropriete_3->setItemText(0, QCoreApplication::translate("MainWindow", "\360\237\223\212 Trier par...", nullptr));
        comboTypePropriete_3->setItemText(1, QCoreApplication::translate("MainWindow", "ID", nullptr));
        comboTypePropriete_3->setItemText(2, QCoreApplication::translate("MainWindow", "Nom", nullptr));
        comboTypePropriete_3->setItemText(3, QCoreApplication::translate("MainWindow", "Type", nullptr));
        comboTypePropriete_3->setItemText(4, QCoreApplication::translate("MainWindow", "Zone", nullptr));
        comboTypePropriete_3->setItemText(5, QCoreApplication::translate("MainWindow", "Statut", nullptr));

        pushButton_21->setText(QCoreApplication::translate("MainWindow", "rechercher", nullptr));
        pushButton_20->setText(QCoreApplication::translate("MainWindow", "\360\237\223\221exporter", nullptr));
        pushButton_19->setText(QCoreApplication::translate("MainWindow", "statistique", nullptr));
        label_18->setText(QCoreApplication::translate("MainWindow", "Bienvenue sur WasteFlow Smart", nullptr));
        label_28->setText(QCoreApplication::translate("MainWindow", "[ Votre Solution Intelligente de Gestion des D\303\251chets Urbains ]", nullptr));
        label_31->setText(QCoreApplication::translate("MainWindow", "Centralisez vos op\303\251rations \342\200\242 Maximisez votre efficacit\303\251 \342\200\242 Prot\303\251gez notre plan\303\250te", nullptr));
        label_32->setText(QString());
        label_30->setText(QCoreApplication::translate("MainWindow", "\"Optimisez, Analysez, Recyclez :L'Intelligence au Service de l'Environnement\"", nullptr));
        pushButton_39->setText(QCoreApplication::translate("MainWindow", "\360\237\232\233tournees", nullptr));
        pushButton_40->setText(QCoreApplication::translate("MainWindow", "\360\237\247\221\360\237\217\273\342\200\215\360\237\222\273employ\303\251s", nullptr));
        pushButton_41->setText(QCoreApplication::translate("MainWindow", "\360\237\247\221\342\200\215\360\237\247\221\342\200\215\360\237\247\222\342\200\215\360\237\247\222clients", nullptr));
        pushButton_42->setText(QCoreApplication::translate("MainWindow", "\360\237\232\256conteneurs", nullptr));
        acceuil_2->setText(QCoreApplication::translate("MainWindow", "\360\237\222\241acceuil", nullptr));
        pushButton_47->setText(QCoreApplication::translate("MainWindow", "\342\231\273\357\270\217recyclage", nullptr));
        dec_2->setText(QCoreApplication::translate("MainWindow", "\342\232\231\357\270\217deconnextion", nullptr));
        label_80->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
