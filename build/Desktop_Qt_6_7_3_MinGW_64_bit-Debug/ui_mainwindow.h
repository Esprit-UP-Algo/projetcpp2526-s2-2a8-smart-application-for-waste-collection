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
#include <QtWidgets/QDateEdit>
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
    QFrame *frame_8;
    QTableWidget *tableWidget_4;
    QFrame *frame_23;
    QLineEdit *lineEdit_18;
    QFrame *frame_46;
    QLabel *label_71;
    QLabel *label_78;
    QLineEdit *lineEdit_19;
    QLabel *label_80;
    QLabel *label_147;
    QLabel *label_148;
    QLineEdit *lineEdit_20;
    QLabel *label_149;
    QLabel *label_150;
    QLabel *label_151;
    QLabel *label_152;
    QLabel *label_153;
    QLabel *label_154;
    QLineEdit *lineEdit_22;
    QLabel *label_155;
    QLabel *label_156;
    QLabel *label_157;
    QLabel *label_158;
    QDateEdit *dateEdit_6;
    QLineEdit *lineEdit_42;
    QLineEdit *lineEdit_21;
    QLineEdit *lineEdit_43;
    QLabel *label_159;
    QLabel *label_160;
    QDateEdit *dateEdit_16;
    QLabel *label_161;
    QLabel *label_162;
    QLineEdit *lineEdit_44;
    QLineEdit *lineEdit_45;
    QLineEdit *lineEdit_46;
    QLabel *label_164;
    QLabel *label_165;
    QLabel *label_166;
    QLabel *label_167;
    QPushButton *pushButton_17;
    QFrame *frame_21;
    QLabel *label_16;
    QPushButton *pushButton_18;
    QPushButton *pushButton_6;
    QComboBox *comboTypePropriete_8;
    QWidget *searchBox_11;
    QLabel *label_44;
    QLabel *label_45;
    QLineEdit *lineEdit_10;
    QPushButton *pushButton_43;
    QPushButton *pushButton_44;
    QPushButton *pushButton_46;
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
        stackedWidget->setGeometry(QRect(-10, -10, 1591, 931));
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
        frame_43->setGeometry(QRect(510, 210, 801, 511));
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
        label_138->setGeometry(QRect(230, 300, 391, 351));
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
        frame_8 = new QFrame(page_3);
        frame_8->setObjectName("frame_8");
        frame_8->setEnabled(true);
        frame_8->setGeometry(QRect(300, -10, 1251, 961));
        frame_8->setMaximumSize(QSize(1500, 1500));
        frame_8->setStyleSheet(QString::fromUtf8("background-color: qlineargradient(\n"
"    spread:pad,\n"
"    x1:0, y1:0,\n"
"    x2:0, y2:1,\n"
"    stop:0 #0A1F33,\n"
"    stop:0.5 #163A5F,\n"
"    stop:1 #274C77\n"
");\n"
"\n"
""));
        frame_8->setFrameShape(QFrame::Shape::StyledPanel);
        frame_8->setFrameShadow(QFrame::Shadow::Raised);
        tableWidget_4 = new QTableWidget(frame_8);
        if (tableWidget_4->columnCount() < 11)
            tableWidget_4->setColumnCount(11);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidget_4->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWidget_4->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        tableWidget_4->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        tableWidget_4->setHorizontalHeaderItem(3, __qtablewidgetitem3);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        tableWidget_4->setHorizontalHeaderItem(4, __qtablewidgetitem4);
        QTableWidgetItem *__qtablewidgetitem5 = new QTableWidgetItem();
        tableWidget_4->setHorizontalHeaderItem(5, __qtablewidgetitem5);
        QTableWidgetItem *__qtablewidgetitem6 = new QTableWidgetItem();
        tableWidget_4->setHorizontalHeaderItem(6, __qtablewidgetitem6);
        QTableWidgetItem *__qtablewidgetitem7 = new QTableWidgetItem();
        tableWidget_4->setHorizontalHeaderItem(7, __qtablewidgetitem7);
        QTableWidgetItem *__qtablewidgetitem8 = new QTableWidgetItem();
        tableWidget_4->setHorizontalHeaderItem(8, __qtablewidgetitem8);
        QTableWidgetItem *__qtablewidgetitem9 = new QTableWidgetItem();
        tableWidget_4->setHorizontalHeaderItem(9, __qtablewidgetitem9);
        QTableWidgetItem *__qtablewidgetitem10 = new QTableWidgetItem();
        tableWidget_4->setHorizontalHeaderItem(10, __qtablewidgetitem10);
        if (tableWidget_4->rowCount() < 10)
            tableWidget_4->setRowCount(10);
        QTableWidgetItem *__qtablewidgetitem11 = new QTableWidgetItem();
        tableWidget_4->setVerticalHeaderItem(0, __qtablewidgetitem11);
        tableWidget_4->setObjectName("tableWidget_4");
        tableWidget_4->setGeometry(QRect(560, 200, 661, 681));
        tableWidget_4->setStyleSheet(QString::fromUtf8(""));
        frame_23 = new QFrame(frame_8);
        frame_23->setObjectName("frame_23");
        frame_23->setGeometry(QRect(20, 120, 521, 761));
        frame_23->setStyleSheet(QString::fromUtf8("background: white;\n"
"border-radius: 20px;\n"
"padding: 20px;\n"
""));
        frame_23->setFrameShape(QFrame::Shape::StyledPanel);
        frame_23->setFrameShadow(QFrame::Shadow::Raised);
        lineEdit_18 = new QLineEdit(frame_23);
        lineEdit_18->setObjectName("lineEdit_18");
        lineEdit_18->setGeometry(QRect(170, 90, 331, 41));
        lineEdit_18->setStyleSheet(QString::fromUtf8("QLineEdit {\n"
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
        frame_46 = new QFrame(frame_23);
        frame_46->setObjectName("frame_46");
        frame_46->setGeometry(QRect(0, 0, 521, 71));
        frame_46->setStyleSheet(QString::fromUtf8("background-color: qlineargradient(\n"
"    spread:pad,\n"
"    x1:0, y1:0,\n"
"    x2:0, y2:1,\n"
"    stop:0 #3A6EA5,\n"
"    stop:1 #1E3A5F\n"
");\n"
"\n"
""));
        frame_46->setFrameShape(QFrame::Shape::StyledPanel);
        frame_46->setFrameShadow(QFrame::Shadow::Raised);
        label_71 = new QLabel(frame_46);
        label_71->setObjectName("label_71");
        label_71->setGeometry(QRect(0, 0, 521, 71));
        QFont font9;
        font9.setPointSize(16);
        font9.setBold(true);
        font9.setItalic(false);
        label_71->setFont(font9);
        label_71->setStyleSheet(QString::fromUtf8("background-color: qlineargradient(\n"
"        x1:0, y1:0,\n"
"        x2:0, y2:1,\n"
"        stop:0 #276646,\n"
"        stop:0.5 #34885A,\n"
"        stop:1 #1B3A2F\n"
"    );"));
        label_78 = new QLabel(frame_23);
        label_78->setObjectName("label_78");
        label_78->setGeometry(QRect(0, 80, 71, 61));
        QFont font10;
        font10.setPointSize(14);
        label_78->setFont(font10);
        lineEdit_19 = new QLineEdit(frame_23);
        lineEdit_19->setObjectName("lineEdit_19");
        lineEdit_19->setGeometry(QRect(170, 140, 331, 41));
        lineEdit_19->setStyleSheet(QString::fromUtf8("QLineEdit {\n"
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
        label_80 = new QLabel(frame_23);
        label_80->setObjectName("label_80");
        label_80->setGeometry(QRect(0, 130, 71, 61));
        label_80->setFont(font10);
        label_147 = new QLabel(frame_23);
        label_147->setObjectName("label_147");
        label_147->setGeometry(QRect(50, 80, 101, 61));
        QFont font11;
        font11.setPointSize(11);
        font11.setBold(true);
        font11.setItalic(true);
        label_147->setFont(font11);
        label_147->setStyleSheet(QString::fromUtf8(" color: #0A1F33;  "));
        label_148 = new QLabel(frame_23);
        label_148->setObjectName("label_148");
        label_148->setGeometry(QRect(50, 130, 121, 61));
        label_148->setFont(font11);
        label_148->setStyleSheet(QString::fromUtf8(" color: #0A1F33;  "));
        lineEdit_20 = new QLineEdit(frame_23);
        lineEdit_20->setObjectName("lineEdit_20");
        lineEdit_20->setGeometry(QRect(170, 250, 331, 41));
        lineEdit_20->setStyleSheet(QString::fromUtf8("QLineEdit {\n"
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
        label_149 = new QLabel(frame_23);
        label_149->setObjectName("label_149");
        label_149->setGeometry(QRect(50, 190, 121, 61));
        label_149->setFont(font11);
        label_149->setStyleSheet(QString::fromUtf8(" color: #0A1F33;  "));
        label_150 = new QLabel(frame_23);
        label_150->setObjectName("label_150");
        label_150->setGeometry(QRect(0, 190, 71, 61));
        label_150->setFont(font10);
        label_151 = new QLabel(frame_23);
        label_151->setObjectName("label_151");
        label_151->setGeometry(QRect(50, 240, 141, 61));
        label_151->setFont(font11);
        label_151->setStyleSheet(QString::fromUtf8(" color: #0A1F33;  "));
        label_152 = new QLabel(frame_23);
        label_152->setObjectName("label_152");
        label_152->setGeometry(QRect(0, 230, 71, 71));
        label_152->setFont(font10);
        label_153 = new QLabel(frame_23);
        label_153->setObjectName("label_153");
        label_153->setGeometry(QRect(50, 290, 231, 61));
        label_153->setFont(font11);
        label_153->setStyleSheet(QString::fromUtf8(" color: #0A1F33;  "));
        label_154 = new QLabel(frame_23);
        label_154->setObjectName("label_154");
        label_154->setGeometry(QRect(0, 280, 71, 71));
        label_154->setFont(font10);
        lineEdit_22 = new QLineEdit(frame_23);
        lineEdit_22->setObjectName("lineEdit_22");
        lineEdit_22->setGeometry(QRect(70, 350, 151, 41));
        lineEdit_22->setStyleSheet(QString::fromUtf8("QLineEdit {\n"
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
        label_155 = new QLabel(frame_23);
        label_155->setObjectName("label_155");
        label_155->setGeometry(QRect(0, 340, 111, 61));
        label_155->setFont(font11);
        label_155->setStyleSheet(QString::fromUtf8(" color: #0A1F33;  "));
        label_156 = new QLabel(frame_23);
        label_156->setObjectName("label_156");
        label_156->setGeometry(QRect(210, 330, 71, 71));
        label_156->setFont(font10);
        label_157 = new QLabel(frame_23);
        label_157->setObjectName("label_157");
        label_157->setGeometry(QRect(40, 400, 231, 61));
        label_157->setFont(font11);
        label_157->setStyleSheet(QString::fromUtf8(" color: #0A1F33;  "));
        label_158 = new QLabel(frame_23);
        label_158->setObjectName("label_158");
        label_158->setGeometry(QRect(-10, 390, 71, 71));
        label_158->setFont(font10);
        dateEdit_6 = new QDateEdit(frame_23);
        dateEdit_6->setObjectName("dateEdit_6");
        dateEdit_6->setGeometry(QRect(260, 300, 241, 41));
        dateEdit_6->setStyleSheet(QString::fromUtf8("background-color: #F9FBFD;          /* fond clair \303\251l\303\251gant */\n"
"    border: 2px solid #3A6EA5;           /* bleu marine clair */\n"
"    border-radius: 12px;\n"
"    padding: 10px 14px;\n"
"    color: #0A1F33;                      /* texte bleu marine fonc\303\251 */\n"
"    font-size: 14px;\n"
"    font-weight: 500;"));
        lineEdit_42 = new QLineEdit(frame_23);
        lineEdit_42->setObjectName("lineEdit_42");
        lineEdit_42->setGeometry(QRect(170, 190, 331, 41));
        lineEdit_42->setStyleSheet(QString::fromUtf8("QLineEdit {\n"
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
        lineEdit_21 = new QLineEdit(frame_23);
        lineEdit_21->setObjectName("lineEdit_21");
        lineEdit_21->setGeometry(QRect(280, 350, 221, 41));
        lineEdit_21->setStyleSheet(QString::fromUtf8("QLineEdit {\n"
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
        lineEdit_43 = new QLineEdit(frame_23);
        lineEdit_43->setObjectName("lineEdit_43");
        lineEdit_43->setGeometry(QRect(230, 410, 271, 41));
        lineEdit_43->setStyleSheet(QString::fromUtf8("QLineEdit {\n"
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
        label_159 = new QLabel(frame_23);
        label_159->setObjectName("label_159");
        label_159->setGeometry(QRect(40, 510, 121, 61));
        label_159->setFont(font11);
        label_159->setStyleSheet(QString::fromUtf8(" color: #0A1F33;  "));
        label_160 = new QLabel(frame_23);
        label_160->setObjectName("label_160");
        label_160->setGeometry(QRect(40, 450, 121, 61));
        label_160->setFont(font11);
        label_160->setStyleSheet(QString::fromUtf8(" color: #0A1F33;  "));
        dateEdit_16 = new QDateEdit(frame_23);
        dateEdit_16->setObjectName("dateEdit_16");
        dateEdit_16->setGeometry(QRect(270, 570, 231, 41));
        dateEdit_16->setStyleSheet(QString::fromUtf8("background-color: #F9FBFD;          /* fond clair \303\251l\303\251gant */\n"
"    border: 2px solid #3A6EA5;           /* bleu marine clair */\n"
"    border-radius: 12px;\n"
"    padding: 10px 14px;\n"
"    color: #0A1F33;                      /* texte bleu marine fonc\303\251 */\n"
"    font-size: 14px;\n"
"    font-weight: 500;"));
        label_161 = new QLabel(frame_23);
        label_161->setObjectName("label_161");
        label_161->setGeometry(QRect(40, 620, 251, 61));
        label_161->setFont(font11);
        label_161->setStyleSheet(QString::fromUtf8(" color: #0A1F33;  "));
        label_162 = new QLabel(frame_23);
        label_162->setObjectName("label_162");
        label_162->setGeometry(QRect(40, 570, 201, 61));
        label_162->setFont(font11);
        label_162->setStyleSheet(QString::fromUtf8(" color: #0A1F33;  "));
        lineEdit_44 = new QLineEdit(frame_23);
        lineEdit_44->setObjectName("lineEdit_44");
        lineEdit_44->setGeometry(QRect(170, 460, 331, 41));
        lineEdit_44->setStyleSheet(QString::fromUtf8("QLineEdit {\n"
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
        lineEdit_45 = new QLineEdit(frame_23);
        lineEdit_45->setObjectName("lineEdit_45");
        lineEdit_45->setGeometry(QRect(170, 520, 331, 41));
        lineEdit_45->setStyleSheet(QString::fromUtf8("QLineEdit {\n"
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
        lineEdit_46 = new QLineEdit(frame_23);
        lineEdit_46->setObjectName("lineEdit_46");
        lineEdit_46->setGeometry(QRect(270, 620, 231, 41));
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
        label_164 = new QLabel(frame_23);
        label_164->setObjectName("label_164");
        label_164->setGeometry(QRect(-10, 610, 71, 81));
        label_164->setFont(font10);
        label_165 = new QLabel(frame_23);
        label_165->setObjectName("label_165");
        label_165->setGeometry(QRect(-10, 560, 71, 71));
        label_165->setFont(font10);
        label_166 = new QLabel(frame_23);
        label_166->setObjectName("label_166");
        label_166->setGeometry(QRect(-10, 500, 71, 71));
        label_166->setFont(font10);
        label_167 = new QLabel(frame_23);
        label_167->setObjectName("label_167");
        label_167->setGeometry(QRect(-10, 440, 71, 71));
        label_167->setFont(font10);
        pushButton_17 = new QPushButton(frame_23);
        pushButton_17->setObjectName("pushButton_17");
        pushButton_17->setGeometry(QRect(20, 700, 471, 51));
        QFont font12;
        font12.setWeight(QFont::DemiBold);
        font12.setItalic(false);
        pushButton_17->setFont(font12);
        pushButton_17->setStyleSheet(QString::fromUtf8("QPushButton {\n"
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
        label_153->raise();
        frame_46->raise();
        label_152->raise();
        label_154->raise();
        label_155->raise();
        label_156->raise();
        label_157->raise();
        label_158->raise();
        label_161->raise();
        lineEdit_46->raise();
        label_160->raise();
        label_150->raise();
        label_151->raise();
        label_149->raise();
        label_148->raise();
        lineEdit_18->raise();
        label_78->raise();
        lineEdit_19->raise();
        label_80->raise();
        lineEdit_20->raise();
        label_147->raise();
        lineEdit_22->raise();
        dateEdit_6->raise();
        lineEdit_42->raise();
        lineEdit_21->raise();
        label_159->raise();
        dateEdit_16->raise();
        label_162->raise();
        lineEdit_43->raise();
        lineEdit_44->raise();
        lineEdit_45->raise();
        label_164->raise();
        label_165->raise();
        label_166->raise();
        label_167->raise();
        pushButton_17->raise();
        frame_21 = new QFrame(frame_8);
        frame_21->setObjectName("frame_21");
        frame_21->setGeometry(QRect(560, 120, 661, 71));
        frame_21->setStyleSheet(QString::fromUtf8("QFrame {\n"
"    background-color: white;\n"
"    border-radius: 15px;\n"
"}\n"
"\n"
""));
        frame_21->setFrameShape(QFrame::Shape::StyledPanel);
        frame_21->setFrameShadow(QFrame::Shadow::Raised);
        label_16 = new QLabel(frame_21);
        label_16->setObjectName("label_16");
        label_16->setGeometry(QRect(10, 10, 261, 51));
        label_16->setStyleSheet(QString::fromUtf8("color: #2A3439;\n"
""));
        pushButton_18 = new QPushButton(frame_21);
        pushButton_18->setObjectName("pushButton_18");
        pushButton_18->setGeometry(QRect(290, 10, 111, 51));
        pushButton_18->setFont(font12);
        pushButton_18->setStyleSheet(QString::fromUtf8("QPushButton {\n"
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
        pushButton_6 = new QPushButton(frame_21);
        pushButton_6->setObjectName("pushButton_6");
        pushButton_6->setGeometry(QRect(410, 10, 111, 51));
        pushButton_6->setFont(font12);
        pushButton_6->setStyleSheet(QString::fromUtf8("QPushButton {\n"
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
        comboTypePropriete_8 = new QComboBox(frame_21);
        comboTypePropriete_8->addItem(QString());
        comboTypePropriete_8->addItem(QString());
        comboTypePropriete_8->addItem(QString());
        comboTypePropriete_8->addItem(QString());
        comboTypePropriete_8->addItem(QString());
        comboTypePropriete_8->addItem(QString());
        comboTypePropriete_8->addItem(QString());
        comboTypePropriete_8->addItem(QString());
        comboTypePropriete_8->addItem(QString());
        comboTypePropriete_8->setObjectName("comboTypePropriete_8");
        comboTypePropriete_8->setGeometry(QRect(530, 10, 121, 51));
        comboTypePropriete_8->setStyleSheet(QString::fromUtf8("  background-color: #F9FBFD;          /* fond clair \303\251l\303\251gant */\n"
"    border: 2px solid #3A6EA5;           /* bleu marine clair */\n"
"    border-radius: 12px;\n"
"    padding: 10px 14px;\n"
"    color: #0A1F33;                      /* texte bleu marine fonc\303\251 */\n"
"    font-size: 14px;\n"
"    font-weight: 500;"));
        searchBox_11 = new QWidget(frame_8);
        searchBox_11->setObjectName("searchBox_11");
        searchBox_11->setGeometry(QRect(20, 40, 1201, 71));
        searchBox_11->setStyleSheet(QString::fromUtf8("background: white;\n"
"border-radius: 20px;\n"
"padding: 20px;\n"
"\n"
""));
        label_44 = new QLabel(searchBox_11);
        label_44->setObjectName("label_44");
        label_44->setGeometry(QRect(70, 60, 131, 91));
        QFont font13;
        font13.setPointSize(28);
        label_44->setFont(font13);
        label_44->setStyleSheet(QString::fromUtf8("background: white;\n"
"border-radius: 20px;\n"
"padding: 20px;"));
        label_45 = new QLabel(searchBox_11);
        label_45->setObjectName("label_45");
        label_45->setGeometry(QRect(0, 0, 81, 71));
        QFont font14;
        font14.setPointSize(11);
        label_45->setFont(font14);
        label_45->setStyleSheet(QString::fromUtf8("background: white;\n"
"border-radius: 20px;\n"
"padding: 20px;"));
        lineEdit_10 = new QLineEdit(searchBox_11);
        lineEdit_10->setObjectName("lineEdit_10");
        lineEdit_10->setGeometry(QRect(50, 10, 471, 51));
        QFont font15;
        font15.setWeight(QFont::Medium);
        lineEdit_10->setFont(font15);
        lineEdit_10->setStyleSheet(QString::fromUtf8("QLineEdit {\n"
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
        pushButton_43 = new QPushButton(searchBox_11);
        pushButton_43->setObjectName("pushButton_43");
        pushButton_43->setGeometry(QRect(1030, 10, 131, 51));
        pushButton_43->setFont(font12);
        pushButton_43->setStyleSheet(QString::fromUtf8("QPushButton {\n"
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
        pushButton_44 = new QPushButton(searchBox_11);
        pushButton_44->setObjectName("pushButton_44");
        pushButton_44->setGeometry(QRect(840, 10, 131, 51));
        pushButton_44->setFont(font12);
        pushButton_44->setStyleSheet(QString::fromUtf8("QPushButton {\n"
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
        pushButton_46 = new QPushButton(searchBox_11);
        pushButton_46->setObjectName("pushButton_46");
        pushButton_46->setGeometry(QRect(650, 10, 131, 51));
        pushButton_46->setFont(font12);
        pushButton_46->setStyleSheet(QString::fromUtf8("QPushButton {\n"
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
        searchBox_7 = new QWidget(page_3);
        searchBox_7->setObjectName("searchBox_7");
        searchBox_7->setGeometry(QRect(0, 10, 311, 951));
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
        pushButton_35->setFont(font12);
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
        pushButton_36->setFont(font12);
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
        pushButton_37->setFont(font12);
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
        pushButton_38->setFont(font12);
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
        acceuil->setFont(font12);
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
        pushButton_45->setFont(font12);
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
        dec->setFont(font12);
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
        label_79->setPixmap(QPixmap(QString::fromUtf8(":/aa.png")));
        label_79->setScaledContents(true);
        stackedWidget->addWidget(page_3);
        MainWindow->setCentralWidget(centralwidget);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        stackedWidget->setCurrentIndex(2);


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
        QTableWidgetItem *___qtablewidgetitem = tableWidget_4->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("MainWindow", "nom", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidget_4->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("MainWindow", "prenom", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = tableWidget_4->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("MainWindow", "email", nullptr));
        QTableWidgetItem *___qtablewidgetitem3 = tableWidget_4->horizontalHeaderItem(3);
        ___qtablewidgetitem3->setText(QCoreApplication::translate("MainWindow", "tel", nullptr));
        QTableWidgetItem *___qtablewidgetitem4 = tableWidget_4->horizontalHeaderItem(4);
        ___qtablewidgetitem4->setText(QCoreApplication::translate("MainWindow", "date de naissance", nullptr));
        QTableWidgetItem *___qtablewidgetitem5 = tableWidget_4->horizontalHeaderItem(5);
        ___qtablewidgetitem5->setText(QCoreApplication::translate("MainWindow", "cin", nullptr));
        QTableWidgetItem *___qtablewidgetitem6 = tableWidget_4->horizontalHeaderItem(6);
        ___qtablewidgetitem6->setText(QCoreApplication::translate("MainWindow", "adresse ", nullptr));
        QTableWidgetItem *___qtablewidgetitem7 = tableWidget_4->horizontalHeaderItem(7);
        ___qtablewidgetitem7->setText(QCoreApplication::translate("MainWindow", "poste", nullptr));
        QTableWidgetItem *___qtablewidgetitem8 = tableWidget_4->horizontalHeaderItem(8);
        ___qtablewidgetitem8->setText(QCoreApplication::translate("MainWindow", "service", nullptr));
        QTableWidgetItem *___qtablewidgetitem9 = tableWidget_4->horizontalHeaderItem(9);
        ___qtablewidgetitem9->setText(QCoreApplication::translate("MainWindow", "mail", nullptr));
        QTableWidgetItem *___qtablewidgetitem10 = tableWidget_4->horizontalHeaderItem(10);
        ___qtablewidgetitem10->setText(QCoreApplication::translate("MainWindow", "salaire", nullptr));
        QTableWidgetItem *___qtablewidgetitem11 = tableWidget_4->verticalHeaderItem(0);
        ___qtablewidgetitem11->setText(QCoreApplication::translate("MainWindow", "2", nullptr));
        lineEdit_18->setText(QString());
        label_71->setText(QCoreApplication::translate("MainWindow", "\360\237\221\244 Informations Personnelles", nullptr));
        label_78->setText(QCoreApplication::translate("MainWindow", "\360\237\221\244", nullptr));
        lineEdit_19->setText(QString());
        label_80->setText(QCoreApplication::translate("MainWindow", "\360\237\221\244", nullptr));
        label_147->setText(QCoreApplication::translate("MainWindow", "Nom:", nullptr));
        label_148->setText(QCoreApplication::translate("MainWindow", "Prenom:", nullptr));
        lineEdit_20->setText(QString());
        label_149->setText(QCoreApplication::translate("MainWindow", "Email:", nullptr));
        label_150->setText(QCoreApplication::translate("MainWindow", "\360\237\223\247", nullptr));
        label_151->setText(QCoreApplication::translate("MainWindow", "T\303\251l\303\251phone:", nullptr));
        label_152->setText(QCoreApplication::translate("MainWindow", "\360\237\223\261", nullptr));
        label_153->setText(QCoreApplication::translate("MainWindow", "Date de Naissance:", nullptr));
        label_154->setText(QCoreApplication::translate("MainWindow", "\360\237\223\205", nullptr));
        lineEdit_22->setText(QString());
        label_155->setText(QCoreApplication::translate("MainWindow", "CIN:", nullptr));
        label_156->setText(QCoreApplication::translate("MainWindow", "\360\237\206\224", nullptr));
        label_157->setText(QCoreApplication::translate("MainWindow", "Adresse Compl\303\250te:", nullptr));
        label_158->setText(QCoreApplication::translate("MainWindow", "\360\237\223\215", nullptr));
        lineEdit_42->setText(QString());
        lineEdit_21->setText(QString());
        lineEdit_43->setText(QString());
        label_159->setText(QCoreApplication::translate("MainWindow", "Service:", nullptr));
        label_160->setText(QCoreApplication::translate("MainWindow", "Poste:", nullptr));
        label_161->setText(QCoreApplication::translate("MainWindow", "Salaire Mensuel (TND):", nullptr));
        label_162->setText(QCoreApplication::translate("MainWindow", "Date d'Embauche:", nullptr));
        lineEdit_44->setText(QString());
        lineEdit_45->setText(QString());
        lineEdit_46->setText(QString());
        label_164->setText(QCoreApplication::translate("MainWindow", "\360\237\222\260", nullptr));
        label_165->setText(QCoreApplication::translate("MainWindow", "\360\237\223\205", nullptr));
        label_166->setText(QCoreApplication::translate("MainWindow", "\360\237\247\221\360\237\217\273\342\200\215\360\237\222\273", nullptr));
        label_167->setText(QCoreApplication::translate("MainWindow", "\360\237\247\221\360\237\217\273\342\200\215\360\237\222\273", nullptr));
        pushButton_17->setText(QCoreApplication::translate("MainWindow", "ajouter", nullptr));
        label_16->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-size:16pt; font-weight:700;\">Liste des employ\303\251s:</span></p></body></html>", nullptr));
        pushButton_18->setText(QCoreApplication::translate("MainWindow", "modifier", nullptr));
        pushButton_6->setText(QCoreApplication::translate("MainWindow", "Supprimer", nullptr));
        comboTypePropriete_8->setItemText(0, QCoreApplication::translate("MainWindow", "trier selon", nullptr));
        comboTypePropriete_8->setItemText(1, QCoreApplication::translate("MainWindow", "service", nullptr));
        comboTypePropriete_8->setItemText(2, QCoreApplication::translate("MainWindow", "nom(A..Z)", nullptr));
        comboTypePropriete_8->setItemText(3, QCoreApplication::translate("MainWindow", "poste", nullptr));
        comboTypePropriete_8->setItemText(4, QCoreApplication::translate("MainWindow", "anciennete", nullptr));
        comboTypePropriete_8->setItemText(5, QCoreApplication::translate("MainWindow", "id", nullptr));
        comboTypePropriete_8->setItemText(6, QString());
        comboTypePropriete_8->setItemText(7, QString());
        comboTypePropriete_8->setItemText(8, QString());

        label_44->setText(QCoreApplication::translate("MainWindow", "\360\237\221\245", nullptr));
        label_45->setText(QCoreApplication::translate("MainWindow", "\360\237\224\215", nullptr));
        pushButton_43->setText(QCoreApplication::translate("MainWindow", "statistique", nullptr));
        pushButton_44->setText(QCoreApplication::translate("MainWindow", "\360\237\223\221exporter", nullptr));
        pushButton_46->setText(QCoreApplication::translate("MainWindow", "rechercher", nullptr));
        pushButton_35->setText(QCoreApplication::translate("MainWindow", "\360\237\232\233tournees", nullptr));
        pushButton_36->setText(QCoreApplication::translate("MainWindow", "\360\237\247\221\360\237\217\273\342\200\215\360\237\222\273employ\303\251s", nullptr));
        pushButton_37->setText(QCoreApplication::translate("MainWindow", "\360\237\247\221\342\200\215\360\237\247\221\342\200\215\360\237\247\222\342\200\215\360\237\247\222clients", nullptr));
        pushButton_38->setText(QCoreApplication::translate("MainWindow", "\360\237\232\256conteneurs", nullptr));
        acceuil->setText(QCoreApplication::translate("MainWindow", "\360\237\222\241acceuil", nullptr));
        pushButton_45->setText(QCoreApplication::translate("MainWindow", "\342\231\273\357\270\217recyclage", nullptr));
        dec->setText(QCoreApplication::translate("MainWindow", "\342\232\231\357\270\217deconnextion", nullptr));
        label_79->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
