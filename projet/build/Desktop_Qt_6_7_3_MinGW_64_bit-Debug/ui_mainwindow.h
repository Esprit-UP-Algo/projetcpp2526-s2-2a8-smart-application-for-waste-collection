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
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QFrame *frame;
    QFrame *frame_2;
    QWidget *widget;
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;
    QWidget *widget_7;
    QLabel *label_30;
    QWidget *widget_8;
    QLabel *label_32;
    QFrame *frame_4;
    QLabel *label_10;
    QLabel *label_11;
    QPushButton *pushButton_5;
    QPushButton *pushButton_6;
    QPushButton *pushButton_7;
    QFrame *frame_3;
    QLabel *label_4;
    QWidget *widget_2;
    QLabel *label_5;
    QWidget *widget_3;
    QLabel *label_6;
    QLabel *label_14;
    QWidget *widget_4;
    QLabel *label_7;
    QLabel *label_15;
    QWidget *widget_5;
    QLabel *label_8;
    QLabel *label_16;
    QWidget *widget_6;
    QLabel *label_9;
    QLabel *label_17;
    QFrame *frame_5;
    QLabel *label_12;
    QTableWidget *tableWidget;
    QPushButton *pushButton_8;
    QPushButton *pushButton_9;
    QPushButton *pushButton_10;
    QPushButton *pushButton_11;
    QLabel *label_13;
    QLabel *label_27;
    QLabel *label_29;
    QLabel *label_18;
    QLabel *label_19;
    QLineEdit *lineEdit_4;
    QLabel *label_24;
    QLabel *label_20;
    QLineEdit *lineEdit;
    QLineEdit *lineEdit_3;
    QLabel *label_21;
    QLabel *label_22;
    QLineEdit *lineEdit_2;
    QComboBox *comboBox;
    QLabel *label_23;
    QComboBox *comboBox_2;
    QLineEdit *lineEdit_5;
    QLabel *label_25;
    QComboBox *comboBox_4;
    QComboBox *comboBox_5;
    QFrame *frame_11;
    QPushButton *pushButton_20;
    QPushButton *pushButton_21;
    QPushButton *pushButton_22;
    QPushButton *pushButton_23;
    QPushButton *pushButton_24;
    QLabel *label_31;
    QFrame *frame_6;
    QLabel *label_33;
    QLabel *label_34;
    QLabel *label_35;
    QLabel *label_36;
    QLabel *label_37;
    QLabel *label_38;
    QLabel *label_39;
    QLabel *label_40;
    QLabel *label_41;
    QPushButton *pushButton_25;
    QPushButton *pushButton_26;
    QPushButton *pushButton_27;
    QPushButton *pushButton_28;
    QWidget *widget_9;
    QLabel *label_42;
    QComboBox *comboBox_3;
    QComboBox *comboBox_6;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(1420, 860);
        MainWindow->setStyleSheet(QString::fromUtf8("background-color: qlineargradient(\n"
"    spread:pad,\n"
"    x1:0, y1:0,\n"
"    x2:0, y2:1,\n"
"    stop:0 #0A1F33,\n"
"    stop:0.5 #163A5F,\n"
"    stop:1 #274C77\n"
");"));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        frame = new QFrame(centralwidget);
        frame->setObjectName("frame");
        frame->setGeometry(QRect(-60, -30, 1511, 891));
        frame->setFrameShape(QFrame::Shape::StyledPanel);
        frame->setFrameShadow(QFrame::Shadow::Raised);
        frame_2 = new QFrame(frame);
        frame_2->setObjectName("frame_2");
        frame_2->setGeometry(QRect(280, 40, 1201, 111));
        frame_2->setStyleSheet(QString::fromUtf8("QFrame {\n"
"    background-color: white;\n"
"    border-radius: 15px;\n"
"}\n"
""));
        frame_2->setFrameShape(QFrame::Shape::StyledPanel);
        frame_2->setFrameShadow(QFrame::Shadow::Raised);
        widget = new QWidget(frame_2);
        widget->setObjectName("widget");
        widget->setGeometry(QRect(20, 10, 100, 100));
        widget->setStyleSheet(QString::fromUtf8("background-color: #2b6cb0;\n"
"border-radius: 16px;\n"
"\n"
""));
        label = new QLabel(widget);
        label->setObjectName("label");
        label->setGeometry(QRect(10, 0, 101, 91));
        QFont font;
        font.setPointSize(36);
        label->setFont(font);
        label_2 = new QLabel(frame_2);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(180, 10, 311, 51));
        label_3 = new QLabel(frame_2);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(170, 70, 391, 31));
        widget_7 = new QWidget(frame_2);
        widget_7->setObjectName("widget_7");
        widget_7->setGeometry(QRect(800, 10, 70, 70));
        widget_7->setMinimumSize(QSize(70, 70));
        widget_7->setMaximumSize(QSize(70, 70));
        widget_7->setContextMenuPolicy(Qt::ContextMenuPolicy::NoContextMenu);
        widget_7->setStyleSheet(QString::fromUtf8("QWidget {\n"
"    background-color: #f0f4f5;\n"
"}\n"
""));
        label_30 = new QLabel(widget_7);
        label_30->setObjectName("label_30");
        label_30->setGeometry(QRect(10, 0, 63, 51));
        QFont font1;
        font1.setFamilies({QString::fromUtf8("Webdings")});
        font1.setPointSize(16);
        label_30->setFont(font1);
        widget_8 = new QWidget(frame_2);
        widget_8->setObjectName("widget_8");
        widget_8->setGeometry(QRect(930, 10, 70, 70));
        widget_8->setMinimumSize(QSize(70, 70));
        widget_8->setMaximumSize(QSize(70, 70));
        widget_8->setFocusPolicy(Qt::FocusPolicy::TabFocus);
        widget_8->setStyleSheet(QString::fromUtf8("QWidget {\n"
"    background-color: #f0f4f5;\n"
"}\n"
""));
        label_32 = new QLabel(widget_8);
        label_32->setObjectName("label_32");
        label_32->setGeometry(QRect(10, 10, 63, 51));
        QFont font2;
        font2.setPointSize(16);
        label_32->setFont(font2);
        frame_4 = new QFrame(frame);
        frame_4->setObjectName("frame_4");
        frame_4->setGeometry(QRect(280, 160, 1201, 111));
        frame_4->setStyleSheet(QString::fromUtf8("QFrame {\n"
"    background-color: white;\n"
"    border-radius: 15px;\n"
"}\n"
""));
        frame_4->setFrameShape(QFrame::Shape::StyledPanel);
        frame_4->setFrameShadow(QFrame::Shadow::Raised);
        label_10 = new QLabel(frame_4);
        label_10->setObjectName("label_10");
        label_10->setGeometry(QRect(30, 20, 63, 51));
        label_11 = new QLabel(frame_4);
        label_11->setObjectName("label_11");
        label_11->setGeometry(QRect(130, 30, 501, 41));
        pushButton_5 = new QPushButton(frame_4);
        pushButton_5->setObjectName("pushButton_5");
        pushButton_5->setGeometry(QRect(610, 30, 141, 41));
        pushButton_5->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    background-color: #2b6cb0;\n"
"    color: white;\n"
"    border-radius: 10px;\n"
"    padding: 6px 14px;\n"
"}\n"
"QPushButton:hover {\n"
"    background-color: #2c5282;\n"
"}\n"
"\n"
""));
        pushButton_6 = new QPushButton(frame_4);
        pushButton_6->setObjectName("pushButton_6");
        pushButton_6->setGeometry(QRect(790, 30, 141, 41));
        pushButton_6->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    background-color: #2b6cb0;\n"
"    color: white;\n"
"    border-radius: 10px;\n"
"    padding: 6px 14px;\n"
"}\n"
"QPushButton:hover {\n"
"    background-color: #2c5282;\n"
"}\n"
"\n"
""));
        pushButton_7 = new QPushButton(frame_4);
        pushButton_7->setObjectName("pushButton_7");
        pushButton_7->setGeometry(QRect(960, 30, 141, 41));
        pushButton_7->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    background-color: #2b6cb0;\n"
"    color: white;\n"
"    border-radius: 10px;\n"
"    padding: 6px 14px;\n"
"}\n"
"QPushButton:hover {\n"
"    background-color: #2c5282;\n"
"}\n"
"\n"
""));
        frame_3 = new QFrame(frame);
        frame_3->setObjectName("frame_3");
        frame_3->setGeometry(QRect(290, 230, 591, 311));
        frame_3->setStyleSheet(QString::fromUtf8("QFrame {\n"
"    background-color: white;\n"
"    border-radius: 15px;\n"
"}\n"
"\n"
""));
        frame_3->setFrameShape(QFrame::Shape::StyledPanel);
        frame_3->setFrameShadow(QFrame::Shadow::Raised);
        label_4 = new QLabel(frame_3);
        label_4->setObjectName("label_4");
        label_4->setGeometry(QRect(140, 0, 301, 51));
        widget_2 = new QWidget(frame_3);
        widget_2->setObjectName("widget_2");
        widget_2->setGeometry(QRect(0, 0, 81, 81));
        widget_2->setStyleSheet(QString::fromUtf8("background-color: #2b6cb0;\n"
"border-radius: 16px;\n"
"\n"
""));
        label_5 = new QLabel(widget_2);
        label_5->setObjectName("label_5");
        label_5->setGeometry(QRect(10, 0, 81, 71));
        widget_3 = new QWidget(frame_3);
        widget_3->setObjectName("widget_3");
        widget_3->setGeometry(QRect(110, 70, 191, 111));
        widget_3->setStyleSheet(QString::fromUtf8("QWidget {\n"
"    background-color: #E0E0E0;\n"
"    color: #333333;\n"
"}"));
        label_6 = new QLabel(widget_3);
        label_6->setObjectName("label_6");
        label_6->setGeometry(QRect(20, 0, 171, 31));
        label_14 = new QLabel(widget_3);
        label_14->setObjectName("label_14");
        label_14->setGeometry(QRect(60, 70, 63, 20));
        widget_4 = new QWidget(frame_3);
        widget_4->setObjectName("widget_4");
        widget_4->setGeometry(QRect(320, 70, 191, 111));
        widget_4->setStyleSheet(QString::fromUtf8("QWidget {\n"
"    background-color: #E0E0E0;\n"
"    color: #333333;\n"
"}"));
        label_7 = new QLabel(widget_4);
        label_7->setObjectName("label_7");
        label_7->setGeometry(QRect(10, 0, 191, 41));
        label_15 = new QLabel(widget_4);
        label_15->setObjectName("label_15");
        label_15->setGeometry(QRect(60, 70, 63, 20));
        widget_5 = new QWidget(frame_3);
        widget_5->setObjectName("widget_5");
        widget_5->setGeometry(QRect(110, 190, 191, 111));
        widget_5->setStyleSheet(QString::fromUtf8("QWidget {\n"
"    background-color: #E0E0E0;\n"
"    color: #333333;\n"
"}"));
        label_8 = new QLabel(widget_5);
        label_8->setObjectName("label_8");
        label_8->setGeometry(QRect(0, 0, 211, 41));
        label_16 = new QLabel(widget_5);
        label_16->setObjectName("label_16");
        label_16->setGeometry(QRect(60, 60, 63, 20));
        widget_6 = new QWidget(frame_3);
        widget_6->setObjectName("widget_6");
        widget_6->setGeometry(QRect(320, 190, 191, 111));
        widget_6->setStyleSheet(QString::fromUtf8("QWidget {\n"
"    background-color: #E0E0E0;\n"
"    color: #333333;\n"
"}"));
        label_9 = new QLabel(widget_6);
        label_9->setObjectName("label_9");
        label_9->setGeometry(QRect(20, 0, 161, 41));
        label_17 = new QLabel(widget_6);
        label_17->setObjectName("label_17");
        label_17->setGeometry(QRect(60, 60, 63, 20));
        frame_5 = new QFrame(frame);
        frame_5->setObjectName("frame_5");
        frame_5->setGeometry(QRect(310, 550, 1221, 321));
        frame_5->setStyleSheet(QString::fromUtf8("QFrame {\n"
"    background-color: white;\n"
"    border-radius: 15px;\n"
"}\n"
"\n"
""));
        frame_5->setFrameShape(QFrame::Shape::StyledPanel);
        frame_5->setFrameShadow(QFrame::Shadow::Raised);
        label_12 = new QLabel(frame_5);
        label_12->setObjectName("label_12");
        label_12->setGeometry(QRect(320, 0, 411, 41));
        tableWidget = new QTableWidget(frame_5);
        if (tableWidget->columnCount() < 7)
            tableWidget->setColumnCount(7);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(3, __qtablewidgetitem3);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(4, __qtablewidgetitem4);
        QTableWidgetItem *__qtablewidgetitem5 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(5, __qtablewidgetitem5);
        QTableWidgetItem *__qtablewidgetitem6 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(6, __qtablewidgetitem6);
        if (tableWidget->rowCount() < 3)
            tableWidget->setRowCount(3);
        QTableWidgetItem *__qtablewidgetitem7 = new QTableWidgetItem();
        tableWidget->setVerticalHeaderItem(0, __qtablewidgetitem7);
        QTableWidgetItem *__qtablewidgetitem8 = new QTableWidgetItem();
        tableWidget->setVerticalHeaderItem(1, __qtablewidgetitem8);
        QTableWidgetItem *__qtablewidgetitem9 = new QTableWidgetItem();
        tableWidget->setVerticalHeaderItem(2, __qtablewidgetitem9);
        QTableWidgetItem *__qtablewidgetitem10 = new QTableWidgetItem();
        tableWidget->setItem(0, 0, __qtablewidgetitem10);
        QTableWidgetItem *__qtablewidgetitem11 = new QTableWidgetItem();
        tableWidget->setItem(0, 1, __qtablewidgetitem11);
        QTableWidgetItem *__qtablewidgetitem12 = new QTableWidgetItem();
        tableWidget->setItem(0, 2, __qtablewidgetitem12);
        QTableWidgetItem *__qtablewidgetitem13 = new QTableWidgetItem();
        tableWidget->setItem(0, 3, __qtablewidgetitem13);
        QTableWidgetItem *__qtablewidgetitem14 = new QTableWidgetItem();
        tableWidget->setItem(0, 4, __qtablewidgetitem14);
        QTableWidgetItem *__qtablewidgetitem15 = new QTableWidgetItem();
        tableWidget->setItem(0, 5, __qtablewidgetitem15);
        QTableWidgetItem *__qtablewidgetitem16 = new QTableWidgetItem();
        tableWidget->setItem(0, 6, __qtablewidgetitem16);
        QTableWidgetItem *__qtablewidgetitem17 = new QTableWidgetItem();
        tableWidget->setItem(1, 0, __qtablewidgetitem17);
        QTableWidgetItem *__qtablewidgetitem18 = new QTableWidgetItem();
        tableWidget->setItem(1, 1, __qtablewidgetitem18);
        QTableWidgetItem *__qtablewidgetitem19 = new QTableWidgetItem();
        tableWidget->setItem(1, 2, __qtablewidgetitem19);
        QTableWidgetItem *__qtablewidgetitem20 = new QTableWidgetItem();
        tableWidget->setItem(1, 3, __qtablewidgetitem20);
        QTableWidgetItem *__qtablewidgetitem21 = new QTableWidgetItem();
        tableWidget->setItem(1, 4, __qtablewidgetitem21);
        QTableWidgetItem *__qtablewidgetitem22 = new QTableWidgetItem();
        tableWidget->setItem(1, 5, __qtablewidgetitem22);
        QTableWidgetItem *__qtablewidgetitem23 = new QTableWidgetItem();
        tableWidget->setItem(1, 6, __qtablewidgetitem23);
        tableWidget->setObjectName("tableWidget");
        tableWidget->setGeometry(QRect(320, 50, 961, 171));
        pushButton_8 = new QPushButton(frame_5);
        pushButton_8->setObjectName("pushButton_8");
        pushButton_8->setGeometry(QRect(330, 200, 121, 51));
        pushButton_8->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    background-color: #2b6cb0;\n"
"    color: white;\n"
"    border-radius: 10px;\n"
"    padding: 6px 14px;\n"
"}\n"
"QPushButton:hover {\n"
"    background-color: #2c5282;\n"
"}\n"
""));
        pushButton_9 = new QPushButton(frame_5);
        pushButton_9->setObjectName("pushButton_9");
        pushButton_9->setGeometry(QRect(500, 200, 131, 51));
        pushButton_9->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    background-color: #2b6cb0;\n"
"    color: white;\n"
"    border-radius: 10px;\n"
"    padding: 6px 14px;\n"
"}\n"
"QPushButton:hover {\n"
"    background-color: #2c5282;\n"
"}\n"
"\n"
""));
        pushButton_10 = new QPushButton(frame_5);
        pushButton_10->setObjectName("pushButton_10");
        pushButton_10->setGeometry(QRect(670, 200, 141, 51));
        pushButton_10->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    background-color: #2b6cb0;\n"
"    color: white;\n"
"    border-radius: 10px;\n"
"    padding: 6px 14px;\n"
"}\n"
"QPushButton:hover {\n"
"    background-color: #2c5282;\n"
"}\n"
""));
        pushButton_11 = new QPushButton(frame_5);
        pushButton_11->setObjectName("pushButton_11");
        pushButton_11->setGeometry(QRect(860, 200, 131, 51));
        pushButton_11->setAcceptDrops(false);
        pushButton_11->setToolTipDuration(1);
        pushButton_11->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    background-color: #2b6cb0;\n"
"    color: white;\n"
"    border-radius: 10px;\n"
"    padding: 6px 14px;\n"
"}\n"
"QPushButton:hover {\n"
"    background-color: #2c5282;\n"
"}\n"
""));
        pushButton_11->setAutoExclusive(true);
        pushButton_11->setAutoRepeatDelay(302);
        pushButton_11->setAutoRepeatInterval(103);
        label_13 = new QLabel(frame_5);
        label_13->setObjectName("label_13");
        label_13->setGeometry(QRect(10, 0, 181, 41));
        label_27 = new QLabel(frame_5);
        label_27->setObjectName("label_27");
        label_27->setGeometry(QRect(120, 100, 63, 20));
        label_29 = new QLabel(frame_5);
        label_29->setObjectName("label_29");
        label_29->setGeometry(QRect(120, 150, 63, 20));
        label_18 = new QLabel(frame_5);
        label_18->setObjectName("label_18");
        label_18->setGeometry(QRect(42, 40, 61, 20));
        label_19 = new QLabel(frame_5);
        label_19->setObjectName("label_19");
        label_19->setGeometry(QRect(40, 90, 81, 16));
        lineEdit_4 = new QLineEdit(frame_5);
        lineEdit_4->setObjectName("lineEdit_4");
        lineEdit_4->setGeometry(QRect(120, 160, 151, 26));
        label_24 = new QLabel(frame_5);
        label_24->setObjectName("label_24");
        label_24->setGeometry(QRect(40, 330, 63, 20));
        label_20 = new QLabel(frame_5);
        label_20->setObjectName("label_20");
        label_20->setGeometry(QRect(40, 130, 111, 20));
        lineEdit = new QLineEdit(frame_5);
        lineEdit->setObjectName("lineEdit");
        lineEdit->setGeometry(QRect(100, 40, 151, 26));
        lineEdit_3 = new QLineEdit(frame_5);
        lineEdit_3->setObjectName("lineEdit_3");
        lineEdit_3->setGeometry(QRect(120, 130, 151, 26));
        label_21 = new QLabel(frame_5);
        label_21->setObjectName("label_21");
        label_21->setGeometry(QRect(40, 160, 63, 20));
        label_22 = new QLabel(frame_5);
        label_22->setObjectName("label_22");
        label_22->setGeometry(QRect(30, 200, 91, 20));
        lineEdit_2 = new QLineEdit(frame_5);
        lineEdit_2->setObjectName("lineEdit_2");
        lineEdit_2->setGeometry(QRect(120, 90, 151, 26));
        comboBox = new QComboBox(frame_5);
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->setObjectName("comboBox");
        comboBox->setGeometry(QRect(120, 320, 171, 31));
        comboBox->setBaseSize(QSize(0, 4));
        comboBox->setLayoutDirection(Qt::LayoutDirection::LeftToRight);
        comboBox->setAutoFillBackground(false);
        comboBox->setMaxVisibleItems(7);
        label_23 = new QLabel(frame_5);
        label_23->setObjectName("label_23");
        label_23->setGeometry(QRect(30, 240, 63, 20));
        comboBox_2 = new QComboBox(frame_5);
        comboBox_2->addItem(QString());
        comboBox_2->addItem(QString());
        comboBox_2->addItem(QString());
        comboBox_2->setObjectName("comboBox_2");
        comboBox_2->setGeometry(QRect(120, 240, 171, 31));
        lineEdit_5 = new QLineEdit(frame_5);
        lineEdit_5->setObjectName("lineEdit_5");
        lineEdit_5->setGeometry(QRect(120, 200, 151, 26));
        label_25 = new QLabel(frame_5);
        label_25->setObjectName("label_25");
        label_25->setGeometry(QRect(20, 280, 63, 20));
        comboBox_4 = new QComboBox(frame_5);
        comboBox_4->addItem(QString());
        comboBox_4->addItem(QString());
        comboBox_4->addItem(QString());
        comboBox_4->setObjectName("comboBox_4");
        comboBox_4->setGeometry(QRect(0, 50, 171, 31));
        comboBox_5 = new QComboBox(frame_5);
        comboBox_5->addItem(QString());
        comboBox_5->addItem(QString());
        comboBox_5->addItem(QString());
        comboBox_5->addItem(QString());
        comboBox_5->setObjectName("comboBox_5");
        comboBox_5->setGeometry(QRect(190, 600, 171, 31));
        comboBox_5->setBaseSize(QSize(0, 4));
        comboBox_5->setLayoutDirection(Qt::LayoutDirection::LeftToRight);
        comboBox_5->setAutoFillBackground(false);
        comboBox_5->setMaxVisibleItems(7);
        frame_11 = new QFrame(frame);
        frame_11->setObjectName("frame_11");
        frame_11->setGeometry(QRect(70, 20, 200, 831));
        frame_11->setMinimumSize(QSize(200, 200));
        frame_11->setStyleSheet(QString::fromUtf8("background-color: #1e3a8a;\n"
""));
        frame_11->setFrameShape(QFrame::Shape::StyledPanel);
        frame_11->setFrameShadow(QFrame::Shadow::Raised);
        pushButton_20 = new QPushButton(frame_11);
        pushButton_20->setObjectName("pushButton_20");
        pushButton_20->setGeometry(QRect(0, 120, 161, 81));
        QFont font3;
        pushButton_20->setFont(font3);
        pushButton_20->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    background-color: transparent;\n"
"    color: white;\n"
"    text-align: left;\n"
"    padding: 10px 16px;\n"
"    font-size: 14px;\n"
"    border: none;\n"
"}\n"
"\n"
"QPushButton:hover {\n"
"    background-color: #2563eb;\n"
"}\n"
"\n"
"QPushButton:checked {\n"
"    background-color: #1d4ed8;\n"
"}\n"
""));
        pushButton_20->setCheckable(true);
        pushButton_20->setChecked(true);
        pushButton_21 = new QPushButton(frame_11);
        pushButton_21->setObjectName("pushButton_21");
        pushButton_21->setGeometry(QRect(0, 220, 161, 71));
        pushButton_21->setMaximumSize(QSize(16777215, 16777215));
        pushButton_21->setFont(font3);
        pushButton_21->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    background-color: transparent;\n"
"    color: white;\n"
"    text-align: left;\n"
"    padding: 10px 16px;\n"
"    font-size: 14px;\n"
"    border: none;\n"
"}\n"
"\n"
"QPushButton:hover {\n"
"    background-color: #2563eb;\n"
"}\n"
"\n"
"QPushButton:checked {\n"
"    background-color: #1d4ed8;\n"
"}\n"
""));
        pushButton_21->setCheckable(true);
        pushButton_21->setChecked(true);
        pushButton_21->setAutoRepeatDelay(298);
        pushButton_22 = new QPushButton(frame_11);
        pushButton_22->setObjectName("pushButton_22");
        pushButton_22->setGeometry(QRect(0, 310, 161, 71));
        pushButton_22->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    background-color: transparent;\n"
"    color: white;\n"
"    text-align: left;\n"
"    padding: 10px 16px;\n"
"    font-size: 14px;\n"
"    border: none;\n"
"}\n"
"\n"
"QPushButton:hover {\n"
"    background-color: #2563eb;\n"
"}\n"
"\n"
"QPushButton:checked {\n"
"    background-color: #1d4ed8;\n"
"}\n"
""));
        pushButton_22->setCheckable(true);
        pushButton_22->setChecked(true);
        pushButton_23 = new QPushButton(frame_11);
        pushButton_23->setObjectName("pushButton_23");
        pushButton_23->setGeometry(QRect(0, 400, 161, 71));
        pushButton_23->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    background-color: transparent;\n"
"    color: white;\n"
"    text-align: left;\n"
"    padding: 10px 16px;\n"
"    font-size: 14px;\n"
"    border: none;\n"
"}\n"
"\n"
"QPushButton:hover {\n"
"    background-color: #2563eb;\n"
"}\n"
"\n"
"QPushButton:checked {\n"
"    background-color: #1d4ed8;\n"
"}\n"
""));
        pushButton_23->setCheckable(true);
        pushButton_23->setChecked(true);
        pushButton_24 = new QPushButton(frame_11);
        pushButton_24->setObjectName("pushButton_24");
        pushButton_24->setGeometry(QRect(0, 490, 161, 71));
        pushButton_24->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    background-color: transparent;\n"
"    color: white;\n"
"    text-align: left;\n"
"    padding: 10px 16px;\n"
"    font-size: 14px;\n"
"    border: none;\n"
"}\n"
"\n"
"QPushButton:hover {\n"
"    background-color: #2563eb;\n"
"}\n"
"\n"
"QPushButton:checked {\n"
"    background-color: #1d4ed8;\n"
"}\n"
""));
        pushButton_24->setCheckable(true);
        pushButton_24->setChecked(true);
        label_31 = new QLabel(frame_11);
        label_31->setObjectName("label_31");
        label_31->setGeometry(QRect(20, 20, 161, 101));
        label_31->setMidLineWidth(-1);
        frame_6 = new QFrame(frame);
        frame_6->setObjectName("frame_6");
        frame_6->setGeometry(QRect(900, 250, 591, 291));
        frame_6->setStyleSheet(QString::fromUtf8("QFrame {\n"
"    background-color: white;\n"
"    border-radius: 16px;\n"
"}\n"
""));
        frame_6->setFrameShape(QFrame::Shape::StyledPanel);
        frame_6->setFrameShadow(QFrame::Shadow::Raised);
        label_33 = new QLabel(frame_6);
        label_33->setObjectName("label_33");
        label_33->setGeometry(QRect(100, 0, 241, 81));
        label_34 = new QLabel(frame_6);
        label_34->setObjectName("label_34");
        label_34->setGeometry(QRect(80, 80, 151, 41));
        label_34->setCursor(QCursor(Qt::CursorShape::UpArrowCursor));
        label_35 = new QLabel(frame_6);
        label_35->setObjectName("label_35");
        label_35->setGeometry(QRect(70, 130, 141, 51));
        label_36 = new QLabel(frame_6);
        label_36->setObjectName("label_36");
        label_36->setGeometry(QRect(90, 190, 141, 41));
        label_37 = new QLabel(frame_6);
        label_37->setObjectName("label_37");
        label_37->setGeometry(QRect(100, 240, 121, 51));
        label_38 = new QLabel(frame_6);
        label_38->setObjectName("label_38");
        label_38->setGeometry(QRect(10, 80, 63, 31));
        label_38->setFont(font2);
        label_39 = new QLabel(frame_6);
        label_39->setObjectName("label_39");
        label_39->setGeometry(QRect(10, 130, 63, 41));
        label_39->setFont(font2);
        label_40 = new QLabel(frame_6);
        label_40->setObjectName("label_40");
        label_40->setGeometry(QRect(10, 170, 71, 71));
        label_40->setFont(font2);
        label_41 = new QLabel(frame_6);
        label_41->setObjectName("label_41");
        label_41->setGeometry(QRect(10, 250, 63, 31));
        label_41->setFont(font2);
        pushButton_25 = new QPushButton(frame_6);
        pushButton_25->setObjectName("pushButton_25");
        pushButton_25->setGeometry(QRect(230, 90, 93, 29));
        pushButton_25->setMouseTracking(true);
        pushButton_25->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    background-color: #2b6cb0;\n"
"    color: white;\n"
"    border-radius: 10px;\n"
"    padding: 8px 16px;\n"
"    font-weight: bold;\n"
"    border: none;\n"
"}\n"
""));
        pushButton_26 = new QPushButton(frame_6);
        pushButton_26->setObjectName("pushButton_26");
        pushButton_26->setGeometry(QRect(230, 140, 93, 29));
        pushButton_26->setMouseTracking(true);
        pushButton_26->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    background-color: #2b6cb0;\n"
"    color: white;\n"
"    border-radius: 10px;\n"
"    padding: 8px 16px;\n"
"    font-weight: bold;\n"
"    border: none;\n"
"}\n"
""));
        pushButton_27 = new QPushButton(frame_6);
        pushButton_27->setObjectName("pushButton_27");
        pushButton_27->setGeometry(QRect(230, 200, 93, 29));
        pushButton_27->setMouseTracking(true);
        pushButton_27->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    background-color: #2b6cb0;\n"
"    color: white;\n"
"    border-radius: 10px;\n"
"    padding: 8px 16px;\n"
"    font-weight: bold;\n"
"    border: none;\n"
"}\n"
""));
        pushButton_28 = new QPushButton(frame_6);
        pushButton_28->setObjectName("pushButton_28");
        pushButton_28->setGeometry(QRect(220, 250, 93, 29));
        pushButton_28->setMouseTracking(true);
        pushButton_28->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    background-color: #2b6cb0;\n"
"    color: white;\n"
"    border-radius: 10px;\n"
"    padding: 8px 16px;\n"
"    font-weight: bold;\n"
"    border: none;\n"
"}\n"
""));
        widget_9 = new QWidget(frame_6);
        widget_9->setObjectName("widget_9");
        widget_9->setGeometry(QRect(10, 0, 70, 71));
        widget_9->setMinimumSize(QSize(70, 70));
        widget_9->setMaximumSize(QSize(70, 71));
        widget_9->setToolTipDuration(9);
        widget_9->setStyleSheet(QString::fromUtf8("  background-color: #2b6cb0;\n"
"    border-radius: 16px;"));
        label_42 = new QLabel(widget_9);
        label_42->setObjectName("label_42");
        label_42->setGeometry(QRect(10, 0, 51, 71));
        QFont font4;
        font4.setPointSize(24);
        label_42->setFont(font4);
        comboBox_3 = new QComboBox(centralwidget);
        comboBox_3->addItem(QString());
        comboBox_3->addItem(QString());
        comboBox_3->addItem(QString());
        comboBox_3->addItem(QString());
        comboBox_3->setObjectName("comboBox_3");
        comboBox_3->setGeometry(QRect(310, 790, 171, 31));
        comboBox_3->setBaseSize(QSize(0, 4));
        comboBox_3->setLayoutDirection(Qt::LayoutDirection::LeftToRight);
        comboBox_3->setAutoFillBackground(false);
        comboBox_3->setMaxVisibleItems(7);
        comboBox_6 = new QComboBox(centralwidget);
        comboBox_6->addItem(QString());
        comboBox_6->addItem(QString());
        comboBox_6->addItem(QString());
        comboBox_6->addItem(QString());
        comboBox_6->setObjectName("comboBox_6");
        comboBox_6->setGeometry(QRect(420, 780, 171, 31));
        comboBox_6->setBaseSize(QSize(0, 4));
        comboBox_6->setLayoutDirection(Qt::LayoutDirection::LeftToRight);
        comboBox_6->setAutoFillBackground(false);
        comboBox_6->setMaxVisibleItems(7);
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 1420, 26));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "\360\237\217\242", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-size:20pt; font-weight:700;\">Gestion des Clients</span></p></body></html>", nullptr));
        label_3->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-size:14pt; color:#1472ff;\">[ MODULE.CLIENTS / SUPERVISION ]</span></p></body></html>", nullptr));
        label_30->setText(QCoreApplication::translate("MainWindow", "\360\237\222\254", nullptr));
        label_32->setText(QCoreApplication::translate("MainWindow", "\360\237\223\261", nullptr));
        label_10->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-size:20pt;\">\360\237\224\215</span></p></body></html>", nullptr));
        label_11->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-size:16pt; color:#c8c3c5;\">Rechercher par CIN, adresse ou zone</span></p></body></html>", nullptr));
        pushButton_5->setText(QCoreApplication::translate("MainWindow", "Filter", nullptr));
        pushButton_6->setText(QCoreApplication::translate("MainWindow", "Exporter", nullptr));
        pushButton_7->setText(QCoreApplication::translate("MainWindow", "+ Nouveau client", nullptr));
        label_4->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-size:20pt; font-weight:700;\">Vue ensemble</span></p></body></html>", nullptr));
        label_5->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-size:28pt;\">\360\237\223\212</span></p></body></html>", nullptr));
        label_6->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-size:14pt; font-weight:700; color:#ffffff;\">Total Clients</span></p></body></html>", nullptr));
        label_14->setText(QCoreApplication::translate("MainWindow", "TextLabel", nullptr));
        label_7->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-size:14pt; font-weight:700; color:#ffffff;\">Clients actifs</span></p></body></html>", nullptr));
        label_15->setText(QCoreApplication::translate("MainWindow", "TextLabel", nullptr));
        label_8->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-size:14pt; font-weight:700; color:#ffffff;\">Conteneurs Li\303\251s</span></p></body></html>", nullptr));
        label_16->setText(QCoreApplication::translate("MainWindow", "TextLabel", nullptr));
        label_9->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-size:14pt; font-weight:700; color:#ffffff;\">Zone Ouverte</span></p></body></html>", nullptr));
        label_17->setText(QCoreApplication::translate("MainWindow", "TextLabel", nullptr));
        label_12->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-size:16pt; font-weight:700;\">\360\237\221\244 Gestion des Clients</span></p></body></html>", nullptr));
        QTableWidgetItem *___qtablewidgetitem = tableWidget->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("MainWindow", "ID", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidget->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("MainWindow", "NOM", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = tableWidget->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("MainWindow", "PRENOM", nullptr));
        QTableWidgetItem *___qtablewidgetitem3 = tableWidget->horizontalHeaderItem(3);
        ___qtablewidgetitem3->setText(QCoreApplication::translate("MainWindow", "TYPE", nullptr));
        QTableWidgetItem *___qtablewidgetitem4 = tableWidget->horizontalHeaderItem(4);
        ___qtablewidgetitem4->setText(QCoreApplication::translate("MainWindow", "ZONE", nullptr));
        QTableWidgetItem *___qtablewidgetitem5 = tableWidget->horizontalHeaderItem(5);
        ___qtablewidgetitem5->setText(QCoreApplication::translate("MainWindow", "TELEPHONE", nullptr));
        QTableWidgetItem *___qtablewidgetitem6 = tableWidget->horizontalHeaderItem(6);
        ___qtablewidgetitem6->setText(QCoreApplication::translate("MainWindow", "STATUT", nullptr));

        const bool __sortingEnabled = tableWidget->isSortingEnabled();
        tableWidget->setSortingEnabled(false);
        QTableWidgetItem *___qtablewidgetitem7 = tableWidget->item(0, 0);
        ___qtablewidgetitem7->setText(QCoreApplication::translate("MainWindow", "1", nullptr));
        QTableWidgetItem *___qtablewidgetitem8 = tableWidget->item(0, 1);
        ___qtablewidgetitem8->setText(QCoreApplication::translate("MainWindow", "ali", nullptr));
        QTableWidgetItem *___qtablewidgetitem9 = tableWidget->item(0, 2);
        ___qtablewidgetitem9->setText(QCoreApplication::translate("MainWindow", "Ben Salah ", nullptr));
        QTableWidgetItem *___qtablewidgetitem10 = tableWidget->item(0, 3);
        ___qtablewidgetitem10->setText(QCoreApplication::translate("MainWindow", "R\303\251sidentiel", nullptr));
        QTableWidgetItem *___qtablewidgetitem11 = tableWidget->item(0, 4);
        ___qtablewidgetitem11->setText(QCoreApplication::translate("MainWindow", "Tunis Centre", nullptr));
        QTableWidgetItem *___qtablewidgetitem12 = tableWidget->item(0, 5);
        ___qtablewidgetitem12->setText(QCoreApplication::translate("MainWindow", "26263207", nullptr));
        QTableWidgetItem *___qtablewidgetitem13 = tableWidget->item(0, 6);
        ___qtablewidgetitem13->setText(QCoreApplication::translate("MainWindow", "actif", nullptr));
        QTableWidgetItem *___qtablewidgetitem14 = tableWidget->item(1, 0);
        ___qtablewidgetitem14->setText(QCoreApplication::translate("MainWindow", "2", nullptr));
        QTableWidgetItem *___qtablewidgetitem15 = tableWidget->item(1, 1);
        ___qtablewidgetitem15->setText(QCoreApplication::translate("MainWindow", "Monoprix", nullptr));
        QTableWidgetItem *___qtablewidgetitem16 = tableWidget->item(1, 3);
        ___qtablewidgetitem16->setText(QCoreApplication::translate("MainWindow", "Commerce", nullptr));
        QTableWidgetItem *___qtablewidgetitem17 = tableWidget->item(1, 4);
        ___qtablewidgetitem17->setText(QCoreApplication::translate("MainWindow", "Manouba", nullptr));
        QTableWidgetItem *___qtablewidgetitem18 = tableWidget->item(1, 5);
        ___qtablewidgetitem18->setText(QCoreApplication::translate("MainWindow", "26760046", nullptr));
        QTableWidgetItem *___qtablewidgetitem19 = tableWidget->item(1, 6);
        ___qtablewidgetitem19->setText(QCoreApplication::translate("MainWindow", "actif", nullptr));
        tableWidget->setSortingEnabled(__sortingEnabled);

        pushButton_8->setText(QCoreApplication::translate("MainWindow", "\342\236\225 Ajouter", nullptr));
        pushButton_9->setText(QCoreApplication::translate("MainWindow", "\342\234\217 Modifier", nullptr));
        pushButton_10->setText(QCoreApplication::translate("MainWindow", "\360\237\227\221 Supprimer", nullptr));
        pushButton_11->setText(QCoreApplication::translate("MainWindow", "\360\237\247\271 Vider", nullptr));
        label_13->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-size:14pt; font-weight:700; color:#0000ff;\"> Formulaire :</span></p><p><br/></p></body></html>", nullptr));
        label_27->setText(QString());
        label_29->setText(QString());
        label_18->setText(QCoreApplication::translate("MainWindow", "Nom :", nullptr));
        label_19->setText(QCoreApplication::translate("MainWindow", "Prenom :", nullptr));
        label_24->setText(QCoreApplication::translate("MainWindow", "Type :", nullptr));
        label_20->setText(QCoreApplication::translate("MainWindow", "Adresse :", nullptr));
        label_21->setText(QCoreApplication::translate("MainWindow", "CIN :", nullptr));
        label_22->setText(QCoreApplication::translate("MainWindow", "Telephone :", nullptr));
        comboBox->setItemText(0, QCoreApplication::translate("MainWindow", "R\303\251sidentiel", nullptr));
        comboBox->setItemText(1, QCoreApplication::translate("MainWindow", "Commerce", nullptr));
        comboBox->setItemText(2, QCoreApplication::translate("MainWindow", "Industrie", nullptr));
        comboBox->setItemText(3, QCoreApplication::translate("MainWindow", "Public\n"
"", nullptr));

        comboBox->setCurrentText(QCoreApplication::translate("MainWindow", "R\303\251sidentiel", nullptr));
        label_23->setText(QCoreApplication::translate("MainWindow", "Zone :", nullptr));
        comboBox_2->setItemText(0, QCoreApplication::translate("MainWindow", "Tunis Centre", nullptr));
        comboBox_2->setItemText(1, QCoreApplication::translate("MainWindow", "Ariana", nullptr));
        comboBox_2->setItemText(2, QCoreApplication::translate("MainWindow", "Manouba", nullptr));

        label_25->setText(QCoreApplication::translate("MainWindow", "Type :", nullptr));
        comboBox_4->setItemText(0, QCoreApplication::translate("MainWindow", "Tunis Centre", nullptr));
        comboBox_4->setItemText(1, QCoreApplication::translate("MainWindow", "Ariana", nullptr));
        comboBox_4->setItemText(2, QCoreApplication::translate("MainWindow", "Manouba", nullptr));

        comboBox_5->setItemText(0, QCoreApplication::translate("MainWindow", "R\303\251sidentiel", nullptr));
        comboBox_5->setItemText(1, QCoreApplication::translate("MainWindow", "Commerce", nullptr));
        comboBox_5->setItemText(2, QCoreApplication::translate("MainWindow", "Industrie", nullptr));
        comboBox_5->setItemText(3, QCoreApplication::translate("MainWindow", "Public\n"
"", nullptr));

        comboBox_5->setCurrentText(QCoreApplication::translate("MainWindow", "R\303\251sidentiel", nullptr));
        pushButton_20->setText(QCoreApplication::translate("MainWindow", "\360\237\221\267 Employ\303\251", nullptr));
        pushButton_21->setText(QCoreApplication::translate("MainWindow", "\360\237\221\244 Clients", nullptr));
        pushButton_22->setText(QCoreApplication::translate("MainWindow", "\342\231\273\357\270\217 Recyclage", nullptr));
        pushButton_23->setText(QCoreApplication::translate("MainWindow", "\360\237\227\221 Conteneur", nullptr));
        pushButton_24->setText(QCoreApplication::translate("MainWindow", "\360\237\223\246 Collectes", nullptr));
        label_31->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-size:18pt; font-weight:700; color:#00aa00;\">Wasteflow</span></p></body></html>", nullptr));
        label_33->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-size:20pt; font-weight:700; color:#000000;\">Type de Clients</span></p></body></html>", nullptr));
        label_34->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-size:16pt; color:#000000;\">Residentiel</span></p></body></html>", nullptr));
        label_35->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-size:16pt; color:#000000;\">Commerce</span></p></body></html>", nullptr));
        label_36->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-size:16pt; color:#000000;\">Industrie</span></p></body></html>", nullptr));
        label_37->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-size:16pt; color:#000000;\">Public</span></p></body></html>", nullptr));
        label_38->setText(QCoreApplication::translate("MainWindow", "\360\237\217\240", nullptr));
        label_39->setText(QCoreApplication::translate("MainWindow", "\360\237\217\252", nullptr));
        label_40->setText(QCoreApplication::translate("MainWindow", "\360\237\217\255", nullptr));
        label_41->setText(QCoreApplication::translate("MainWindow", "\360\237\217\233\357\270\217", nullptr));
        pushButton_25->setText(QCoreApplication::translate("MainWindow", "Cocher", nullptr));
        pushButton_26->setText(QCoreApplication::translate("MainWindow", "Cocher", nullptr));
        pushButton_27->setText(QCoreApplication::translate("MainWindow", "Cocher", nullptr));
        pushButton_28->setText(QCoreApplication::translate("MainWindow", "Cocher", nullptr));
        label_42->setText(QCoreApplication::translate("MainWindow", "\360\237\223\210", nullptr));
        comboBox_3->setItemText(0, QCoreApplication::translate("MainWindow", "R\303\251sidentiel", nullptr));
        comboBox_3->setItemText(1, QCoreApplication::translate("MainWindow", "Commerce", nullptr));
        comboBox_3->setItemText(2, QCoreApplication::translate("MainWindow", "Industrie", nullptr));
        comboBox_3->setItemText(3, QCoreApplication::translate("MainWindow", "Public\n"
"", nullptr));

        comboBox_3->setCurrentText(QCoreApplication::translate("MainWindow", "R\303\251sidentiel", nullptr));
        comboBox_6->setItemText(0, QCoreApplication::translate("MainWindow", "R\303\251sidentiel", nullptr));
        comboBox_6->setItemText(1, QCoreApplication::translate("MainWindow", "Commerce", nullptr));
        comboBox_6->setItemText(2, QCoreApplication::translate("MainWindow", "Industrie", nullptr));
        comboBox_6->setItemText(3, QCoreApplication::translate("MainWindow", "Public\n"
"", nullptr));

        comboBox_6->setCurrentText(QCoreApplication::translate("MainWindow", "R\303\251sidentiel", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
