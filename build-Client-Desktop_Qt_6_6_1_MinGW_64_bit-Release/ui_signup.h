/********************************************************************************
** Form generated from reading UI file 'signup.ui'
**
** Created by: Qt User Interface Compiler version 6.6.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SIGNUP_H
#define UI_SIGNUP_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_Signup
{
public:
    QGridLayout *gridLayout_2;
    QSpacerItem *verticalSpacer;
    QGridLayout *gridLayout;
    QPushButton *pushButton_signup;
    QSpacerItem *horizontalSpacer;
    QSpacerItem *horizontalSpacer_2;
    QHBoxLayout *horizontalLayout_2;
    QVBoxLayout *verticalLayout_4;
    QLabel *label_recoveryWordAnimal;
    QLabel *label_;
    QLabel *label_1;
    QVBoxLayout *verticalLayout;
    QLineEdit *lineEdit_recoveryWordAnimal;
    QLineEdit *lineEdit_recoveryWordCity;
    QLineEdit *lineEdit_recoveryWordColor;
    QHBoxLayout *horizontalLayout;
    QVBoxLayout *verticalLayout_3;
    QLabel *label_user_name;
    QLabel *label_personal_name;
    QLabel *label_password;
    QLabel *label_email;
    QVBoxLayout *verticalLayout_2;
    QLineEdit *lineEdit_user_name;
    QLineEdit *lineEdit_personal_name;
    QLineEdit *lineEdit_pass;
    QLineEdit *lineEdit_email;
    QSpacerItem *horizontalSpacer_5;
    QSpacerItem *horizontalSpacer_3;
    QSpacerItem *horizontalSpacer_4;
    QSpacerItem *verticalSpacer_2;

    void setupUi(QDialog *Signup)
    {
        if (Signup->objectName().isEmpty())
            Signup->setObjectName("Signup");
        Signup->resize(770, 395);
        Signup->setStyleSheet(QString::fromUtf8("QPushButton{\n"
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
        gridLayout_2 = new QGridLayout(Signup);
        gridLayout_2->setObjectName("gridLayout_2");
        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_2->addItem(verticalSpacer, 0, 1, 1, 1);

        gridLayout = new QGridLayout();
        gridLayout->setObjectName("gridLayout");
        pushButton_signup = new QPushButton(Signup);
        pushButton_signup->setObjectName("pushButton_signup");

        gridLayout->addWidget(pushButton_signup, 1, 1, 1, 1);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer, 1, 0, 1, 1);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_2, 1, 2, 1, 1);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        verticalLayout_4 = new QVBoxLayout();
        verticalLayout_4->setObjectName("verticalLayout_4");
        label_recoveryWordAnimal = new QLabel(Signup);
        label_recoveryWordAnimal->setObjectName("label_recoveryWordAnimal");

        verticalLayout_4->addWidget(label_recoveryWordAnimal);

        label_ = new QLabel(Signup);
        label_->setObjectName("label_");

        verticalLayout_4->addWidget(label_);

        label_1 = new QLabel(Signup);
        label_1->setObjectName("label_1");

        verticalLayout_4->addWidget(label_1);


        horizontalLayout_2->addLayout(verticalLayout_4);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName("verticalLayout");
        lineEdit_recoveryWordAnimal = new QLineEdit(Signup);
        lineEdit_recoveryWordAnimal->setObjectName("lineEdit_recoveryWordAnimal");
        lineEdit_recoveryWordAnimal->setMinimumSize(QSize(0, 30));

        verticalLayout->addWidget(lineEdit_recoveryWordAnimal);

        lineEdit_recoveryWordCity = new QLineEdit(Signup);
        lineEdit_recoveryWordCity->setObjectName("lineEdit_recoveryWordCity");
        lineEdit_recoveryWordCity->setMinimumSize(QSize(0, 30));

        verticalLayout->addWidget(lineEdit_recoveryWordCity);

        lineEdit_recoveryWordColor = new QLineEdit(Signup);
        lineEdit_recoveryWordColor->setObjectName("lineEdit_recoveryWordColor");
        lineEdit_recoveryWordColor->setMinimumSize(QSize(0, 30));

        verticalLayout->addWidget(lineEdit_recoveryWordColor);


        horizontalLayout_2->addLayout(verticalLayout);


        gridLayout->addLayout(horizontalLayout_2, 0, 2, 1, 1);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setObjectName("verticalLayout_3");
        label_user_name = new QLabel(Signup);
        label_user_name->setObjectName("label_user_name");

        verticalLayout_3->addWidget(label_user_name);

        label_personal_name = new QLabel(Signup);
        label_personal_name->setObjectName("label_personal_name");

        verticalLayout_3->addWidget(label_personal_name);

        label_password = new QLabel(Signup);
        label_password->setObjectName("label_password");

        verticalLayout_3->addWidget(label_password);

        label_email = new QLabel(Signup);
        label_email->setObjectName("label_email");

        verticalLayout_3->addWidget(label_email);


        horizontalLayout->addLayout(verticalLayout_3);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName("verticalLayout_2");
        lineEdit_user_name = new QLineEdit(Signup);
        lineEdit_user_name->setObjectName("lineEdit_user_name");
        lineEdit_user_name->setMinimumSize(QSize(0, 30));

        verticalLayout_2->addWidget(lineEdit_user_name);

        lineEdit_personal_name = new QLineEdit(Signup);
        lineEdit_personal_name->setObjectName("lineEdit_personal_name");
        lineEdit_personal_name->setMinimumSize(QSize(0, 30));

        verticalLayout_2->addWidget(lineEdit_personal_name);

        lineEdit_pass = new QLineEdit(Signup);
        lineEdit_pass->setObjectName("lineEdit_pass");
        lineEdit_pass->setMinimumSize(QSize(0, 30));

        verticalLayout_2->addWidget(lineEdit_pass);

        lineEdit_email = new QLineEdit(Signup);
        lineEdit_email->setObjectName("lineEdit_email");
        lineEdit_email->setMinimumSize(QSize(0, 30));

        verticalLayout_2->addWidget(lineEdit_email);


        horizontalLayout->addLayout(verticalLayout_2);


        gridLayout->addLayout(horizontalLayout, 0, 0, 1, 1);

        horizontalSpacer_5 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_5, 0, 1, 1, 1);


        gridLayout_2->addLayout(gridLayout, 1, 1, 1, 1);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer_3, 1, 0, 1, 1);

        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer_4, 1, 2, 1, 1);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_2->addItem(verticalSpacer_2, 2, 1, 1, 1);


        retranslateUi(Signup);

        QMetaObject::connectSlotsByName(Signup);
    } // setupUi

    void retranslateUi(QDialog *Signup)
    {
        Signup->setWindowTitle(QCoreApplication::translate("Signup", "Dialog", nullptr));
        pushButton_signup->setText(QCoreApplication::translate("Signup", "Sign Up", nullptr));
        label_recoveryWordAnimal->setText(QCoreApplication::translate("Signup", "Your Favorite Animal", nullptr));
        label_->setText(QCoreApplication::translate("Signup", "Your Favorite City", nullptr));
        label_1->setText(QCoreApplication::translate("Signup", "Your Favorite Color", nullptr));
        label_user_name->setText(QCoreApplication::translate("Signup", "User Name", nullptr));
        label_personal_name->setText(QCoreApplication::translate("Signup", "Personal Name", nullptr));
        label_password->setText(QCoreApplication::translate("Signup", "Password", nullptr));
        label_email->setText(QCoreApplication::translate("Signup", "Email", nullptr));
        lineEdit_user_name->setText(QString());
        lineEdit_personal_name->setText(QString());
        lineEdit_pass->setText(QString());
        lineEdit_email->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class Signup: public Ui_Signup {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SIGNUP_H
