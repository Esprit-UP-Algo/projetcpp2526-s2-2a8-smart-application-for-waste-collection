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
    QFrame *frame_2;
    QTableWidget *tableWidget_3;
    QFrame *frame_46;
    QLineEdit *lineEdit_46;
    QFrame *frame_47;
    QLabel *label_168;
    QLabel *label_169;
    QLineEdit *lineEdit_47;
    QLabel *label_170;
    QLabel *label_171;
    QLabel *label_172;
    QLineEdit *lineEdit_48;
    QLabel *label_175;
    QLabel *label_179;
    QPushButton *pushButton_22;
    QLabel *label_4;
    QLineEdit *lineEdit_49;
    QLabel *label_177;
    QLineEdit *lineEdit_50;
    QLabel *label_7;
    QLabel *label_180;
    QLabel *label_181;
    QLabel *label_8;
    QLabel *label_10;
    QComboBox *comboBox_3;
    QComboBox *comboBox_2;
    QLabel *label_189;
    QWidget *searchBox_5;
    QLabel *label_40;
    QLabel *label_41;
    QLineEdit *lineEdit_8;
    QPushButton *pushButton_19;
    QPushButton *pushButton_20;
    QPushButton *pushButton_21;
    QFrame *frame_48;
    QLabel *label_18;
    QPushButton *pushButton_23;
    QPushButton *pushButton_10;
    QComboBox *comboTypePropriete_3;
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
        MainWindow->resize(1682, 992);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
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
        if (tableWidget_3->rowCount() < 3)
            tableWidget_3->setRowCount(3);
        QTableWidgetItem *__qtablewidgetitem7 = new QTableWidgetItem();
        tableWidget_3->setVerticalHeaderItem(0, __qtablewidgetitem7);
        QTableWidgetItem *__qtablewidgetitem8 = new QTableWidgetItem();
        tableWidget_3->setVerticalHeaderItem(1, __qtablewidgetitem8);
        QTableWidgetItem *__qtablewidgetitem9 = new QTableWidgetItem();
        tableWidget_3->setVerticalHeaderItem(2, __qtablewidgetitem9);
        QTableWidgetItem *__qtablewidgetitem10 = new QTableWidgetItem();
        tableWidget_3->setItem(0, 0, __qtablewidgetitem10);
        QTableWidgetItem *__qtablewidgetitem11 = new QTableWidgetItem();
        tableWidget_3->setItem(0, 1, __qtablewidgetitem11);
        QTableWidgetItem *__qtablewidgetitem12 = new QTableWidgetItem();
        tableWidget_3->setItem(0, 2, __qtablewidgetitem12);
        QTableWidgetItem *__qtablewidgetitem13 = new QTableWidgetItem();
        tableWidget_3->setItem(0, 3, __qtablewidgetitem13);
        QTableWidgetItem *__qtablewidgetitem14 = new QTableWidgetItem();
        tableWidget_3->setItem(0, 4, __qtablewidgetitem14);
        QTableWidgetItem *__qtablewidgetitem15 = new QTableWidgetItem();
        tableWidget_3->setItem(0, 5, __qtablewidgetitem15);
        QTableWidgetItem *__qtablewidgetitem16 = new QTableWidgetItem();
        tableWidget_3->setItem(0, 6, __qtablewidgetitem16);
        QTableWidgetItem *__qtablewidgetitem17 = new QTableWidgetItem();
        tableWidget_3->setItem(1, 0, __qtablewidgetitem17);
        QTableWidgetItem *__qtablewidgetitem18 = new QTableWidgetItem();
        tableWidget_3->setItem(1, 1, __qtablewidgetitem18);
        QTableWidgetItem *__qtablewidgetitem19 = new QTableWidgetItem();
        tableWidget_3->setItem(1, 2, __qtablewidgetitem19);
        QTableWidgetItem *__qtablewidgetitem20 = new QTableWidgetItem();
        tableWidget_3->setItem(1, 3, __qtablewidgetitem20);
        QTableWidgetItem *__qtablewidgetitem21 = new QTableWidgetItem();
        tableWidget_3->setItem(1, 4, __qtablewidgetitem21);
        QTableWidgetItem *__qtablewidgetitem22 = new QTableWidgetItem();
        tableWidget_3->setItem(1, 5, __qtablewidgetitem22);
        QTableWidgetItem *__qtablewidgetitem23 = new QTableWidgetItem();
        tableWidget_3->setItem(1, 6, __qtablewidgetitem23);
        tableWidget_3->setObjectName("tableWidget_3");
        tableWidget_3->setGeometry(QRect(550, 180, 661, 681));
        tableWidget_3->setStyleSheet(QString::fromUtf8(""));
        frame_46 = new QFrame(frame_2);
        frame_46->setObjectName("frame_46");
        frame_46->setGeometry(QRect(10, 100, 521, 761));
        frame_46->setStyleSheet(QString::fromUtf8("background: white;\n"
"border-radius: 20px;\n"
"padding: 20px;\n"
""));
        frame_46->setFrameShape(QFrame::Shape::StyledPanel);
        frame_46->setFrameShadow(QFrame::Shadow::Raised);
        lineEdit_46 = new QLineEdit(frame_46);
        lineEdit_46->setObjectName("lineEdit_46");
        lineEdit_46->setGeometry(QRect(170, 120, 331, 41));
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
        QFont font;
        font.setPointSize(16);
        font.setBold(true);
        font.setItalic(false);
        label_168->setFont(font);
        label_168->setStyleSheet(QString::fromUtf8("background-color: qlineargradient(\n"
"        x1:0, y1:0,\n"
"        x2:0, y2:1,\n"
"        stop:0 #276646,\n"
"        stop:0.5 #34885A,\n"
"        stop:1 #1B3A2F\n"
"    );"));
        label_169 = new QLabel(frame_46);
        label_169->setObjectName("label_169");
        label_169->setGeometry(QRect(0, 110, 71, 61));
        QFont font1;
        font1.setPointSize(14);
        label_169->setFont(font1);
        lineEdit_47 = new QLineEdit(frame_46);
        lineEdit_47->setObjectName("lineEdit_47");
        lineEdit_47->setGeometry(QRect(170, 190, 331, 41));
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
        label_170 = new QLabel(frame_46);
        label_170->setObjectName("label_170");
        label_170->setGeometry(QRect(0, 170, 71, 61));
        label_170->setFont(font1);
        label_171 = new QLabel(frame_46);
        label_171->setObjectName("label_171");
        label_171->setGeometry(QRect(50, 110, 101, 61));
        QFont font2;
        font2.setPointSize(11);
        font2.setBold(true);
        font2.setItalic(true);
        label_171->setFont(font2);
        label_171->setStyleSheet(QString::fromUtf8(" color: #0A1F33;  "));
        label_172 = new QLabel(frame_46);
        label_172->setObjectName("label_172");
        label_172->setGeometry(QRect(50, 180, 121, 61));
        label_172->setFont(font2);
        label_172->setStyleSheet(QString::fromUtf8(" color: #0A1F33;  "));
        lineEdit_48 = new QLineEdit(frame_46);
        lineEdit_48->setObjectName("lineEdit_48");
        lineEdit_48->setGeometry(QRect(170, 260, 331, 41));
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
        label_175 = new QLabel(frame_46);
        label_175->setObjectName("label_175");
        label_175->setGeometry(QRect(50, 250, 151, 61));
        label_175->setFont(font2);
        label_175->setStyleSheet(QString::fromUtf8(" color: #0A1F33;  "));
        label_179 = new QLabel(frame_46);
        label_179->setObjectName("label_179");
        label_179->setGeometry(QRect(60, 410, 111, 61));
        label_179->setFont(font2);
        label_179->setStyleSheet(QString::fromUtf8(" color: #0A1F33;  "));
        pushButton_22 = new QPushButton(frame_46);
        pushButton_22->setObjectName("pushButton_22");
        pushButton_22->setGeometry(QRect(40, 700, 431, 51));
        QFont font3;
        font3.setWeight(QFont::DemiBold);
        font3.setItalic(false);
        pushButton_22->setFont(font3);
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
        label_4 = new QLabel(frame_46);
        label_4->setObjectName("label_4");
        label_4->setGeometry(QRect(0, 320, 91, 81));
        label_4->setStyleSheet(QString::fromUtf8("\n"
"color: #FFFFFF\n"
";\n"
"border: 0px;\n"
"outline: 0;\n"
"background: transparent;\n"
"\n"
""));
        lineEdit_49 = new QLineEdit(frame_46);
        lineEdit_49->setObjectName("lineEdit_49");
        lineEdit_49->setGeometry(QRect(170, 340, 331, 41));
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
        label_177 = new QLabel(frame_46);
        label_177->setObjectName("label_177");
        label_177->setGeometry(QRect(50, 330, 151, 61));
        label_177->setFont(font2);
        label_177->setStyleSheet(QString::fromUtf8(" color: #0A1F33;  "));
        lineEdit_50 = new QLineEdit(frame_46);
        lineEdit_50->setObjectName("lineEdit_50");
        lineEdit_50->setGeometry(QRect(170, 410, 331, 41));
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
        label_7 = new QLabel(frame_46);
        label_7->setObjectName("label_7");
        label_7->setGeometry(QRect(0, 230, 91, 91));
        label_7->setStyleSheet(QString::fromUtf8("\n"
"color: #FFFFFF\n"
";\n"
"border: 0px;\n"
"outline: 0;\n"
"background: transparent;\n"
"\n"
""));
        label_180 = new QLabel(frame_46);
        label_180->setObjectName("label_180");
        label_180->setGeometry(QRect(70, 490, 111, 61));
        label_180->setFont(font2);
        label_180->setStyleSheet(QString::fromUtf8(" color: #0A1F33;  "));
        label_181 = new QLabel(frame_46);
        label_181->setObjectName("label_181");
        label_181->setGeometry(QRect(70, 570, 111, 61));
        label_181->setFont(font2);
        label_181->setStyleSheet(QString::fromUtf8(" color: #0A1F33;  "));
        label_8 = new QLabel(frame_46);
        label_8->setObjectName("label_8");
        label_8->setGeometry(QRect(0, 550, 101, 101));
        label_8->setStyleSheet(QString::fromUtf8("\n"
"color: #FFFFFF\n"
";\n"
"border: 0px;\n"
"outline: 0;\n"
"background: transparent;\n"
"\n"
""));
        label_10 = new QLabel(frame_46);
        label_10->setObjectName("label_10");
        label_10->setGeometry(QRect(0, 480, 81, 71));
        label_10->setStyleSheet(QString::fromUtf8("\n"
"color: #FFFFFF\n"
";\n"
"border: 0px;\n"
"outline: 0;\n"
"background: transparent;\n"
"\n"
""));
        comboBox_3 = new QComboBox(frame_46);
        comboBox_3->addItem(QString());
        comboBox_3->addItem(QString());
        comboBox_3->addItem(QString());
        comboBox_3->setObjectName("comboBox_3");
        comboBox_3->setGeometry(QRect(170, 490, 331, 48));
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
        comboBox_2 = new QComboBox(frame_46);
        comboBox_2->addItem(QString());
        comboBox_2->addItem(QString());
        comboBox_2->addItem(QString());
        comboBox_2->addItem(QString());
        comboBox_2->setObjectName("comboBox_2");
        comboBox_2->setGeometry(QRect(170, 570, 331, 48));
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
        label_189 = new QLabel(frame_46);
        label_189->setObjectName("label_189");
        label_189->setGeometry(QRect(0, 400, 81, 71));
        label_189->setFont(font1);
        label_177->raise();
        label_172->raise();
        label_175->raise();
        lineEdit_46->raise();
        frame_47->raise();
        label_169->raise();
        lineEdit_47->raise();
        label_170->raise();
        label_171->raise();
        lineEdit_48->raise();
        label_179->raise();
        pushButton_22->raise();
        label_4->raise();
        lineEdit_49->raise();
        lineEdit_50->raise();
        label_7->raise();
        label_180->raise();
        label_181->raise();
        label_8->raise();
        label_10->raise();
        comboBox_3->raise();
        comboBox_2->raise();
        label_189->raise();
        searchBox_5 = new QWidget(frame_2);
        searchBox_5->setObjectName("searchBox_5");
        searchBox_5->setGeometry(QRect(10, 20, 1201, 71));
        searchBox_5->setStyleSheet(QString::fromUtf8("background: white;\n"
"border-radius: 20px;\n"
"padding: 20px;\n"
"\n"
""));
        label_40 = new QLabel(searchBox_5);
        label_40->setObjectName("label_40");
        label_40->setGeometry(QRect(70, 60, 131, 91));
        QFont font4;
        font4.setPointSize(28);
        label_40->setFont(font4);
        label_40->setStyleSheet(QString::fromUtf8("background: white;\n"
"border-radius: 20px;\n"
"padding: 20px;"));
        label_41 = new QLabel(searchBox_5);
        label_41->setObjectName("label_41");
        label_41->setGeometry(QRect(0, 0, 81, 71));
        QFont font5;
        font5.setPointSize(11);
        label_41->setFont(font5);
        label_41->setStyleSheet(QString::fromUtf8("background: white;\n"
"border-radius: 20px;\n"
"padding: 20px;"));
        lineEdit_8 = new QLineEdit(searchBox_5);
        lineEdit_8->setObjectName("lineEdit_8");
        lineEdit_8->setGeometry(QRect(50, 10, 471, 51));
        QFont font6;
        font6.setWeight(QFont::Medium);
        lineEdit_8->setFont(font6);
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
        pushButton_19 = new QPushButton(searchBox_5);
        pushButton_19->setObjectName("pushButton_19");
        pushButton_19->setGeometry(QRect(1030, 10, 131, 51));
        pushButton_19->setFont(font3);
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
        pushButton_20 = new QPushButton(searchBox_5);
        pushButton_20->setObjectName("pushButton_20");
        pushButton_20->setGeometry(QRect(840, 10, 131, 51));
        pushButton_20->setFont(font3);
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
        pushButton_21 = new QPushButton(searchBox_5);
        pushButton_21->setObjectName("pushButton_21");
        pushButton_21->setGeometry(QRect(650, 10, 131, 51));
        pushButton_21->setFont(font3);
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
        frame_48 = new QFrame(frame_2);
        frame_48->setObjectName("frame_48");
        frame_48->setGeometry(QRect(550, 100, 661, 71));
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
        label_18->setGeometry(QRect(10, 10, 261, 51));
        label_18->setStyleSheet(QString::fromUtf8("color: #2A3439;\n"
""));
        pushButton_23 = new QPushButton(frame_48);
        pushButton_23->setObjectName("pushButton_23");
        pushButton_23->setGeometry(QRect(240, 10, 111, 51));
        pushButton_23->setFont(font3);
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
        pushButton_10->setGeometry(QRect(360, 10, 111, 51));
        pushButton_10->setFont(font3);
        pushButton_10->setStyleSheet(QString::fromUtf8("QPushButton {\n"
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
        comboTypePropriete_3 = new QComboBox(frame_48);
        comboTypePropriete_3->addItem(QString());
        comboTypePropriete_3->addItem(QString());
        comboTypePropriete_3->addItem(QString());
        comboTypePropriete_3->addItem(QString());
        comboTypePropriete_3->setObjectName("comboTypePropriete_3");
        comboTypePropriete_3->setGeometry(QRect(490, 10, 161, 51));
        comboTypePropriete_3->setStyleSheet(QString::fromUtf8("  background-color: #F9FBFD;          /* fond clair \303\251l\303\251gant */\n"
"    border: 2px solid #3A6EA5;           /* bleu marine clair */\n"
"    border-radius: 12px;\n"
"    padding: 10px 14px;\n"
"    color: #0A1F33;                      /* texte bleu marine fonc\303\251 */\n"
"    font-size: 14px;\n"
"    font-weight: 500;"));
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
        pushButton_35->setFont(font3);
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
        pushButton_36->setFont(font3);
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
        pushButton_37->setFont(font3);
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
        pushButton_38->setFont(font3);
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
        acceuil->setFont(font3);
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
        pushButton_45->setFont(font3);
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
        dec->setFont(font3);
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
        label_79->setPixmap(QPixmap(QString::fromUtf8(":/employe/aa.png")));
        label_79->setScaledContents(true);
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
        QTableWidgetItem *___qtablewidgetitem7 = tableWidget_3->verticalHeaderItem(0);
        ___qtablewidgetitem7->setText(QCoreApplication::translate("MainWindow", "Insert Row", nullptr));
        QTableWidgetItem *___qtablewidgetitem8 = tableWidget_3->verticalHeaderItem(1);
        ___qtablewidgetitem8->setText(QCoreApplication::translate("MainWindow", "Inser Row", nullptr));
        QTableWidgetItem *___qtablewidgetitem9 = tableWidget_3->verticalHeaderItem(2);
        ___qtablewidgetitem9->setText(QCoreApplication::translate("MainWindow", "Insert Row", nullptr));

        const bool __sortingEnabled = tableWidget_3->isSortingEnabled();
        tableWidget_3->setSortingEnabled(false);
        QTableWidgetItem *___qtablewidgetitem10 = tableWidget_3->item(0, 0);
        ___qtablewidgetitem10->setText(QCoreApplication::translate("MainWindow", "1", nullptr));
        QTableWidgetItem *___qtablewidgetitem11 = tableWidget_3->item(0, 1);
        ___qtablewidgetitem11->setText(QCoreApplication::translate("MainWindow", "ali", nullptr));
        QTableWidgetItem *___qtablewidgetitem12 = tableWidget_3->item(0, 2);
        ___qtablewidgetitem12->setText(QCoreApplication::translate("MainWindow", "Ben Salah ", nullptr));
        QTableWidgetItem *___qtablewidgetitem13 = tableWidget_3->item(0, 3);
        ___qtablewidgetitem13->setText(QCoreApplication::translate("MainWindow", "R\303\251sidentiel", nullptr));
        QTableWidgetItem *___qtablewidgetitem14 = tableWidget_3->item(0, 4);
        ___qtablewidgetitem14->setText(QCoreApplication::translate("MainWindow", "Tunis Centre", nullptr));
        QTableWidgetItem *___qtablewidgetitem15 = tableWidget_3->item(0, 5);
        ___qtablewidgetitem15->setText(QCoreApplication::translate("MainWindow", "26263207", nullptr));
        QTableWidgetItem *___qtablewidgetitem16 = tableWidget_3->item(0, 6);
        ___qtablewidgetitem16->setText(QCoreApplication::translate("MainWindow", "actif", nullptr));
        QTableWidgetItem *___qtablewidgetitem17 = tableWidget_3->item(1, 0);
        ___qtablewidgetitem17->setText(QCoreApplication::translate("MainWindow", "2", nullptr));
        QTableWidgetItem *___qtablewidgetitem18 = tableWidget_3->item(1, 1);
        ___qtablewidgetitem18->setText(QCoreApplication::translate("MainWindow", "Monoprix", nullptr));
        QTableWidgetItem *___qtablewidgetitem19 = tableWidget_3->item(1, 3);
        ___qtablewidgetitem19->setText(QCoreApplication::translate("MainWindow", "Commerce", nullptr));
        QTableWidgetItem *___qtablewidgetitem20 = tableWidget_3->item(1, 4);
        ___qtablewidgetitem20->setText(QCoreApplication::translate("MainWindow", "Manouba", nullptr));
        QTableWidgetItem *___qtablewidgetitem21 = tableWidget_3->item(1, 5);
        ___qtablewidgetitem21->setText(QCoreApplication::translate("MainWindow", "26760046", nullptr));
        QTableWidgetItem *___qtablewidgetitem22 = tableWidget_3->item(1, 6);
        ___qtablewidgetitem22->setText(QCoreApplication::translate("MainWindow", "actif", nullptr));
        tableWidget_3->setSortingEnabled(__sortingEnabled);

        lineEdit_46->setText(QString());
        label_168->setText(QCoreApplication::translate("MainWindow", "\360\237\221\244 Informations Personnelles", nullptr));
        label_169->setText(QCoreApplication::translate("MainWindow", "\360\237\221\244", nullptr));
        lineEdit_47->setText(QString());
        label_170->setText(QCoreApplication::translate("MainWindow", "\360\237\221\244", nullptr));
        label_171->setText(QCoreApplication::translate("MainWindow", "Nom:", nullptr));
        label_172->setText(QCoreApplication::translate("MainWindow", "Prenom:", nullptr));
        lineEdit_48->setText(QString());
        label_175->setText(QCoreApplication::translate("MainWindow", "T\303\251l\303\251phone:", nullptr));
        label_179->setText(QCoreApplication::translate("MainWindow", "CIN:", nullptr));
        pushButton_22->setText(QCoreApplication::translate("MainWindow", "ajouter", nullptr));
        label_4->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-size:18pt;\">\360\237\217\240</span></p></body></html>", nullptr));
        lineEdit_49->setText(QString());
        label_177->setText(QCoreApplication::translate("MainWindow", "Adresse :", nullptr));
        lineEdit_50->setText(QString());
        label_7->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-size:18pt;\">\360\237\223\236 </span></p></body></html>", nullptr));
        label_180->setText(QCoreApplication::translate("MainWindow", "Zone :", nullptr));
        label_181->setText(QCoreApplication::translate("MainWindow", "Type :", nullptr));
        label_8->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-size:18pt;\">\360\237\217\242</span></p></body></html>", nullptr));
        label_10->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-size:18pt;\">\360\237\223\215</span></p></body></html>", nullptr));
        comboBox_3->setItemText(0, QCoreApplication::translate("MainWindow", "Tunis Centre", nullptr));
        comboBox_3->setItemText(1, QCoreApplication::translate("MainWindow", "Ariana", nullptr));
        comboBox_3->setItemText(2, QCoreApplication::translate("MainWindow", "Manouba", nullptr));

        comboBox_2->setItemText(0, QCoreApplication::translate("MainWindow", "R\303\251sidentiel", nullptr));
        comboBox_2->setItemText(1, QCoreApplication::translate("MainWindow", "Commerce", nullptr));
        comboBox_2->setItemText(2, QCoreApplication::translate("MainWindow", "Industrie", nullptr));
        comboBox_2->setItemText(3, QCoreApplication::translate("MainWindow", "Public", nullptr));

        comboBox_2->setCurrentText(QCoreApplication::translate("MainWindow", "R\303\251sidentiel", nullptr));
        label_189->setText(QCoreApplication::translate("MainWindow", "\360\237\206\224", nullptr));
        label_40->setText(QCoreApplication::translate("MainWindow", "\360\237\221\245", nullptr));
        label_41->setText(QCoreApplication::translate("MainWindow", "\360\237\224\215", nullptr));
        pushButton_19->setText(QCoreApplication::translate("MainWindow", "statistique", nullptr));
        pushButton_20->setText(QCoreApplication::translate("MainWindow", "\360\237\223\221exporter", nullptr));
        pushButton_21->setText(QCoreApplication::translate("MainWindow", "rechercher", nullptr));
        label_18->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-size:16pt; font-weight:700;\">Liste des clients:</span></p></body></html>", nullptr));
        pushButton_23->setText(QCoreApplication::translate("MainWindow", "modifier", nullptr));
        pushButton_10->setText(QCoreApplication::translate("MainWindow", "Supprimer", nullptr));
        comboTypePropriete_3->setItemText(0, QCoreApplication::translate("MainWindow", "trier selon", nullptr));
        comboTypePropriete_3->setItemText(1, QString());
        comboTypePropriete_3->setItemText(2, QString());
        comboTypePropriete_3->setItemText(3, QString());

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
