/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.10.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *DownloadBin;
    QWidget *centralwidget;
    QWidget *widget;
    QPushButton *connectToPort;
    QLabel *label;
    QComboBox *comboBox;
    QLabel *label_2;
    QLineEdit *lineStatus;
    QLineEdit *lineIndicate;
    QPushButton *buttonLoad;
    QPushButton *buttonStart;
    QPushButton *pushButton_3;
    QLineEdit *lineEdit;
    QLabel *label_3;
    QMenuBar *menubar;
    QMenu *menu;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(800, 600);
        DownloadBin = new QAction(MainWindow);
        DownloadBin->setObjectName("DownloadBin");
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        widget = new QWidget(centralwidget);
        widget->setObjectName("widget");
        widget->setGeometry(QRect(0, 10, 471, 151));
        connectToPort = new QPushButton(widget);
        connectToPort->setObjectName("connectToPort");
        connectToPort->setGeometry(QRect(20, 80, 121, 24));
        label = new QLabel(widget);
        label->setObjectName("label");
        label->setGeometry(QRect(20, 20, 51, 16));
        comboBox = new QComboBox(widget);
        comboBox->setObjectName("comboBox");
        comboBox->setGeometry(QRect(20, 50, 121, 24));
        label_2 = new QLabel(widget);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(20, 120, 71, 16));
        lineStatus = new QLineEdit(widget);
        lineStatus->setObjectName("lineStatus");
        lineStatus->setGeometry(QRect(60, 20, 81, 21));
        lineIndicate = new QLineEdit(widget);
        lineIndicate->setObjectName("lineIndicate");
        lineIndicate->setGeometry(QRect(90, 120, 51, 20));
        buttonLoad = new QPushButton(widget);
        buttonLoad->setObjectName("buttonLoad");
        buttonLoad->setGeometry(QRect(370, 50, 80, 24));
        buttonStart = new QPushButton(widget);
        buttonStart->setObjectName("buttonStart");
        buttonStart->setGeometry(QRect(370, 80, 80, 24));
        pushButton_3 = new QPushButton(widget);
        pushButton_3->setObjectName("pushButton_3");
        pushButton_3->setGeometry(QRect(370, 110, 80, 24));
        lineEdit = new QLineEdit(widget);
        lineEdit->setObjectName("lineEdit");
        lineEdit->setGeometry(QRect(370, 20, 81, 24));
        label_3 = new QLabel(widget);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(180, 60, 49, 16));
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 800, 21));
        menu = new QMenu(menubar);
        menu->setObjectName("menu");
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        menubar->addAction(menu->menuAction());
        menu->addAction(DownloadBin);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        DownloadBin->setText(QCoreApplication::translate("MainWindow", "\320\227\320\260\320\263\321\200\321\203\320\267\320\270\321\202\321\214 \320\261\320\270\320\275\320\260\321\200\320\275\321\213\320\271 \321\204\320\260\320\271\320\273", nullptr));
        connectToPort->setText(QCoreApplication::translate("MainWindow", "\320\237\320\276\320\264\320\272\320\273\321\216\321\207\320\270\321\202\321\214\321\201\321\217", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "\320\241\321\202\320\260\321\202\321\203\321\201:", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindow", "\320\230\320\275\320\264\320\270\320\272\320\260\321\202\320\276\321\200:", nullptr));
        buttonLoad->setText(QCoreApplication::translate("MainWindow", "LOAD", nullptr));
        buttonStart->setText(QCoreApplication::translate("MainWindow", "START", nullptr));
        pushButton_3->setText(QCoreApplication::translate("MainWindow", "END", nullptr));
        lineEdit->setText(QCoreApplication::translate("MainWindow", " \320\243\320\277\321\200\320\260\320\262\320\273\320\265\320\275\320\270\320\265", nullptr));
        label_3->setText(QString());
        menu->setTitle(QCoreApplication::translate("MainWindow", "\320\244\320\260\320\271\320\273", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
