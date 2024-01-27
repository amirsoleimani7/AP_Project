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
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_myClient
{
public:
    QWidget *centralwidget;
    QGridLayout *gridLayout;
    QSpacerItem *horizontalSpacer_2;
    QSpacerItem *verticalSpacer_2;
    QSpacerItem *verticalSpacer_4;
    QSpacerItem *horizontalSpacer;
    QSpacerItem *verticalSpacer;
    QVBoxLayout *verticalLayout_4;
    QVBoxLayout *verticalLayout_3;
    QHBoxLayout *horizontalLayout;
    QVBoxLayout *verticalLayout_2;
    QLabel *label_user_name;
    QLabel *label_password;
    QVBoxLayout *verticalLayout;
    QLineEdit *lineEdit_User_Name;
    QLineEdit *lineEdit_Password;
    QPushButton *pushButton_Login;
    QSpacerItem *verticalSpacer_3;
    QHBoxLayout *horizontalLayout_4;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_forget;
    QPushButton *pushButton_forgot;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_signup;
    QPushButton *pushButton_signup;

    void setupUi(QMainWindow *myClient)
    {
        if (myClient->objectName().isEmpty())
            myClient->setObjectName("myClient");
        myClient->resize(660, 437);
        myClient->setStyleSheet(QString::fromUtf8("QPushButton{\n"
"  background-color: #3498db;\n"
"  color: #ecf0f1;\n"
"  padding: 10px 20px;\n"
"  border: none;\n"
"  border-radius: 3px;\n"
"  cursor: pointer;\n"
"  font-size: 14px;\n"
"font-weight: bold;\n"
"}\n"
"QPushButton:hover {\n"
"  background-color: #2980b9;\n"
"}\n"
"QLabel{\n"
"  font-family: 'Arial', sans-serif;\n"
"  background-color: #2c3e50;\n"
"font-weight: bold;\n"
"  color: #ecf0f1;\n"
"  padding: 10px;\n"
"  text-align: center;\n"
"  font-size: 14px;\n"
"}\n"
"QLineEdit{\n"
"  border-radius: 3px;\n"
"  border: none;\n"
"font-weight: bold;\n"
"  Hight: 20px\n"
"}\n"
"QDialog\n"
"{\n"
"background-color: #2c3e50;\n"
"font-weight: bold;\n"
"}\n"
"QMainWindow{\n"
"  background-color: #2c3e50;\n"
"}\n"
"QMessageBox{\n"
"	 background-color: #2c3e50;\n"
"font-weight: bold;\n"
"}\n"
"QCombobox{\n"
"  background-color: #2c3e50;\n"
"font-weight: bold;\n"
"  color: #ecf0f1;\n"
"  padding: 10px 20px;\n"
"  border: none;\n"
"  border-radius: 3px;\n"
"  cursor: pointer;\n"
"}"));
        centralwidget = new QWidget(myClient);
        centralwidget->setObjectName("centralwidget");
        gridLayout = new QGridLayout(centralwidget);
        gridLayout->setObjectName("gridLayout");
        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_2, 2, 2, 1, 1);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout->addItem(verticalSpacer_2, 3, 1, 1, 1);

        verticalSpacer_4 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout->addItem(verticalSpacer_4, 1, 1, 1, 1);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer, 2, 0, 1, 1);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout->addItem(verticalSpacer, 0, 1, 1, 1);

        verticalLayout_4 = new QVBoxLayout();
        verticalLayout_4->setObjectName("verticalLayout_4");
        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setObjectName("verticalLayout_3");
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName("verticalLayout_2");
        label_user_name = new QLabel(centralwidget);
        label_user_name->setObjectName("label_user_name");

        verticalLayout_2->addWidget(label_user_name);

        label_password = new QLabel(centralwidget);
        label_password->setObjectName("label_password");

        verticalLayout_2->addWidget(label_password);


        horizontalLayout->addLayout(verticalLayout_2);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName("verticalLayout");
        lineEdit_User_Name = new QLineEdit(centralwidget);
        lineEdit_User_Name->setObjectName("lineEdit_User_Name");
        lineEdit_User_Name->setMinimumSize(QSize(0, 25));
        QFont font;
        font.setFamilies({QString::fromUtf8("Arial")});
        font.setPointSize(10);
        font.setBold(true);
        lineEdit_User_Name->setFont(font);

        verticalLayout->addWidget(lineEdit_User_Name);

        lineEdit_Password = new QLineEdit(centralwidget);
        lineEdit_Password->setObjectName("lineEdit_Password");
        lineEdit_Password->setMinimumSize(QSize(0, 25));
        lineEdit_Password->setFont(font);
        lineEdit_Password->setEchoMode(QLineEdit::Password);

        verticalLayout->addWidget(lineEdit_Password);


        horizontalLayout->addLayout(verticalLayout);


        verticalLayout_3->addLayout(horizontalLayout);

        pushButton_Login = new QPushButton(centralwidget);
        pushButton_Login->setObjectName("pushButton_Login");
        QFont font1;
        font1.setBold(true);
        pushButton_Login->setFont(font1);

        verticalLayout_3->addWidget(pushButton_Login);

        verticalSpacer_3 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_3->addItem(verticalSpacer_3);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName("horizontalLayout_4");
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        label_forget = new QLabel(centralwidget);
        label_forget->setObjectName("label_forget");

        horizontalLayout_2->addWidget(label_forget);

        pushButton_forgot = new QPushButton(centralwidget);
        pushButton_forgot->setObjectName("pushButton_forgot");
        pushButton_forgot->setFont(font1);

        horizontalLayout_2->addWidget(pushButton_forgot);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName("horizontalLayout_3");
        label_signup = new QLabel(centralwidget);
        label_signup->setObjectName("label_signup");

        horizontalLayout_3->addWidget(label_signup);

        pushButton_signup = new QPushButton(centralwidget);
        pushButton_signup->setObjectName("pushButton_signup");
        pushButton_signup->setFont(font1);

        horizontalLayout_3->addWidget(pushButton_signup);


        horizontalLayout_2->addLayout(horizontalLayout_3);


        horizontalLayout_4->addLayout(horizontalLayout_2);


        verticalLayout_3->addLayout(horizontalLayout_4);


        verticalLayout_4->addLayout(verticalLayout_3);


        gridLayout->addLayout(verticalLayout_4, 2, 1, 1, 1);

        myClient->setCentralWidget(centralwidget);

        retranslateUi(myClient);

        QMetaObject::connectSlotsByName(myClient);
    } // setupUi

    void retranslateUi(QMainWindow *myClient)
    {
        myClient->setWindowTitle(QCoreApplication::translate("myClient", "myClient", nullptr));
        label_user_name->setText(QCoreApplication::translate("myClient", "User Name", nullptr));
        label_password->setText(QCoreApplication::translate("myClient", "Password", nullptr));
        pushButton_Login->setText(QCoreApplication::translate("myClient", "Login", nullptr));
#if QT_CONFIG(shortcut)
        pushButton_Login->setShortcut(QCoreApplication::translate("myClient", "Return", nullptr));
#endif // QT_CONFIG(shortcut)
        label_forget->setText(QCoreApplication::translate("myClient", " Forgot My Password :", nullptr));
        pushButton_forgot->setText(QCoreApplication::translate("myClient", "Forgot", nullptr));
        label_signup->setText(QCoreApplication::translate("myClient", "I Am New :", nullptr));
        pushButton_signup->setText(QCoreApplication::translate("myClient", "Sign up", nullptr));
    } // retranslateUi

};

namespace Ui {
    class myClient: public Ui_myClient {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MYCLIENT_H
