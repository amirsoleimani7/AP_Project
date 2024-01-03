/********************************************************************************
** Form generated from reading UI file 'myserver.ui'
**
** Created by: Qt User Interface Compiler version 6.6.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MYSERVER_H
#define UI_MYSERVER_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_myServer
{
public:
    QWidget *centralwidget;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *myServer)
    {
        if (myServer->objectName().isEmpty())
            myServer->setObjectName("myServer");
        myServer->resize(800, 600);
        centralwidget = new QWidget(myServer);
        centralwidget->setObjectName("centralwidget");
        myServer->setCentralWidget(centralwidget);
        menubar = new QMenuBar(myServer);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 800, 25));
        myServer->setMenuBar(menubar);
        statusbar = new QStatusBar(myServer);
        statusbar->setObjectName("statusbar");
        myServer->setStatusBar(statusbar);

        retranslateUi(myServer);

        QMetaObject::connectSlotsByName(myServer);
    } // setupUi

    void retranslateUi(QMainWindow *myServer)
    {
        myServer->setWindowTitle(QCoreApplication::translate("myServer", "myServer", nullptr));
    } // retranslateUi

};

namespace Ui {
    class myServer: public Ui_myServer {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MYSERVER_H
