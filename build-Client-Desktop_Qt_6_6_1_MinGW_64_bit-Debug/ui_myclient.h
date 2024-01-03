/********************************************************************************
** Form generated from reading UI file 'myclient.ui'
**
** Created by: Qt User Interface Compiler version 6.6.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MYCLIENT_H
#define UI_MYCLIENT_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_myClient
{
public:
    QWidget *centralwidget;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *myClient)
    {
        if (myClient->objectName().isEmpty())
            myClient->setObjectName("myClient");
        myClient->resize(800, 600);
        centralwidget = new QWidget(myClient);
        centralwidget->setObjectName("centralwidget");
        myClient->setCentralWidget(centralwidget);
        menubar = new QMenuBar(myClient);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 800, 25));
        myClient->setMenuBar(menubar);
        statusbar = new QStatusBar(myClient);
        statusbar->setObjectName("statusbar");
        myClient->setStatusBar(statusbar);

        retranslateUi(myClient);

        QMetaObject::connectSlotsByName(myClient);
    } // setupUi

    void retranslateUi(QMainWindow *myClient)
    {
        myClient->setWindowTitle(QCoreApplication::translate("myClient", "myClient", nullptr));
    } // retranslateUi

};

namespace Ui {
    class myClient: public Ui_myClient {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MYCLIENT_H
