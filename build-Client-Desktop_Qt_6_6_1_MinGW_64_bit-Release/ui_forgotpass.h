/********************************************************************************
** Form generated from reading UI file 'forgotpass.ui'
**
** Created by: Qt User Interface Compiler version 6.6.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FORGOTPASS_H
#define UI_FORGOTPASS_H

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

class Ui_ForgotPass
{
public:
    QGridLayout *gridLayout;
    QVBoxLayout *verticalLayout_6;
    QLabel *label_pass_status;
    QHBoxLayout *horizontalLayout_2;
    QVBoxLayout *verticalLayout_5;
    QLabel *label_new_pass;
    QLabel *label;
    QVBoxLayout *verticalLayout_4;
    QLineEdit *lineEdit_new_pass_1;
    QLineEdit *lineEdit_new_pass_2;
    QPushButton *pushButton_change_pass_word;
    QSpacerItem *horizontalSpacer;
    QVBoxLayout *verticalLayout_3;
    QHBoxLayout *horizontalLayout;
    QVBoxLayout *verticalLayout_2;
    QLabel *label_user_name;
    QLabel *label_fav_animal;
    QLabel *label_fav_city;
    QLabel *label_fav_color;
    QVBoxLayout *verticalLayout;
    QLineEdit *lineEdit_get_user_name;
    QLineEdit *lineEdit_get_fav_animal;
    QLineEdit *lineEdit_get_fav_city;
    QLineEdit *lineEdit_get_fav_color;
    QPushButton *pushButton;
    QSpacerItem *verticalSpacer;
    QSpacerItem *verticalSpacer_2;
    QSpacerItem *horizontalSpacer_2;
    QSpacerItem *horizontalSpacer_3;

    void setupUi(QDialog *ForgotPass)
    {
        if (ForgotPass->objectName().isEmpty())
            ForgotPass->setObjectName("ForgotPass");
        ForgotPass->resize(640, 368);
        ForgotPass->setStyleSheet(QString::fromUtf8("QPushButton{\n"
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
        gridLayout = new QGridLayout(ForgotPass);
        gridLayout->setObjectName("gridLayout");
        verticalLayout_6 = new QVBoxLayout();
        verticalLayout_6->setObjectName("verticalLayout_6");
        label_pass_status = new QLabel(ForgotPass);
        label_pass_status->setObjectName("label_pass_status");

        verticalLayout_6->addWidget(label_pass_status);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        verticalLayout_5 = new QVBoxLayout();
        verticalLayout_5->setObjectName("verticalLayout_5");
        label_new_pass = new QLabel(ForgotPass);
        label_new_pass->setObjectName("label_new_pass");

        verticalLayout_5->addWidget(label_new_pass);

        label = new QLabel(ForgotPass);
        label->setObjectName("label");

        verticalLayout_5->addWidget(label);


        horizontalLayout_2->addLayout(verticalLayout_5);

        verticalLayout_4 = new QVBoxLayout();
        verticalLayout_4->setObjectName("verticalLayout_4");
        lineEdit_new_pass_1 = new QLineEdit(ForgotPass);
        lineEdit_new_pass_1->setObjectName("lineEdit_new_pass_1");
        lineEdit_new_pass_1->setMinimumSize(QSize(0, 25));

        verticalLayout_4->addWidget(lineEdit_new_pass_1);

        lineEdit_new_pass_2 = new QLineEdit(ForgotPass);
        lineEdit_new_pass_2->setObjectName("lineEdit_new_pass_2");
        lineEdit_new_pass_2->setMinimumSize(QSize(0, 25));

        verticalLayout_4->addWidget(lineEdit_new_pass_2);


        horizontalLayout_2->addLayout(verticalLayout_4);


        verticalLayout_6->addLayout(horizontalLayout_2);

        pushButton_change_pass_word = new QPushButton(ForgotPass);
        pushButton_change_pass_word->setObjectName("pushButton_change_pass_word");

        verticalLayout_6->addWidget(pushButton_change_pass_word);


        gridLayout->addLayout(verticalLayout_6, 1, 3, 1, 1);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer, 1, 0, 1, 1);

        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setObjectName("verticalLayout_3");
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName("verticalLayout_2");
        label_user_name = new QLabel(ForgotPass);
        label_user_name->setObjectName("label_user_name");

        verticalLayout_2->addWidget(label_user_name);

        label_fav_animal = new QLabel(ForgotPass);
        label_fav_animal->setObjectName("label_fav_animal");
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(label_fav_animal->sizePolicy().hasHeightForWidth());
        label_fav_animal->setSizePolicy(sizePolicy);

        verticalLayout_2->addWidget(label_fav_animal);

        label_fav_city = new QLabel(ForgotPass);
        label_fav_city->setObjectName("label_fav_city");

        verticalLayout_2->addWidget(label_fav_city);

        label_fav_color = new QLabel(ForgotPass);
        label_fav_color->setObjectName("label_fav_color");

        verticalLayout_2->addWidget(label_fav_color);


        horizontalLayout->addLayout(verticalLayout_2);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName("verticalLayout");
        lineEdit_get_user_name = new QLineEdit(ForgotPass);
        lineEdit_get_user_name->setObjectName("lineEdit_get_user_name");
        QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(lineEdit_get_user_name->sizePolicy().hasHeightForWidth());
        lineEdit_get_user_name->setSizePolicy(sizePolicy1);
        lineEdit_get_user_name->setMinimumSize(QSize(0, 25));

        verticalLayout->addWidget(lineEdit_get_user_name);

        lineEdit_get_fav_animal = new QLineEdit(ForgotPass);
        lineEdit_get_fav_animal->setObjectName("lineEdit_get_fav_animal");
        sizePolicy1.setHeightForWidth(lineEdit_get_fav_animal->sizePolicy().hasHeightForWidth());
        lineEdit_get_fav_animal->setSizePolicy(sizePolicy1);
        lineEdit_get_fav_animal->setMinimumSize(QSize(0, 25));

        verticalLayout->addWidget(lineEdit_get_fav_animal);

        lineEdit_get_fav_city = new QLineEdit(ForgotPass);
        lineEdit_get_fav_city->setObjectName("lineEdit_get_fav_city");
        sizePolicy1.setHeightForWidth(lineEdit_get_fav_city->sizePolicy().hasHeightForWidth());
        lineEdit_get_fav_city->setSizePolicy(sizePolicy1);
        lineEdit_get_fav_city->setMinimumSize(QSize(0, 25));

        verticalLayout->addWidget(lineEdit_get_fav_city);

        lineEdit_get_fav_color = new QLineEdit(ForgotPass);
        lineEdit_get_fav_color->setObjectName("lineEdit_get_fav_color");
        sizePolicy1.setHeightForWidth(lineEdit_get_fav_color->sizePolicy().hasHeightForWidth());
        lineEdit_get_fav_color->setSizePolicy(sizePolicy1);
        lineEdit_get_fav_color->setMinimumSize(QSize(0, 25));

        verticalLayout->addWidget(lineEdit_get_fav_color);


        horizontalLayout->addLayout(verticalLayout);


        verticalLayout_3->addLayout(horizontalLayout);

        pushButton = new QPushButton(ForgotPass);
        pushButton->setObjectName("pushButton");

        verticalLayout_3->addWidget(pushButton);


        gridLayout->addLayout(verticalLayout_3, 1, 1, 1, 1);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout->addItem(verticalSpacer, 0, 3, 1, 1);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout->addItem(verticalSpacer_2, 2, 1, 1, 1);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_2, 1, 4, 1, 1);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_3, 1, 2, 1, 1);


        retranslateUi(ForgotPass);

        QMetaObject::connectSlotsByName(ForgotPass);
    } // setupUi

    void retranslateUi(QDialog *ForgotPass)
    {
        ForgotPass->setWindowTitle(QCoreApplication::translate("ForgotPass", "Dialog", nullptr));
        label_pass_status->setText(QCoreApplication::translate("ForgotPass", "Status", nullptr));
        label_new_pass->setText(QCoreApplication::translate("ForgotPass", "New Pass", nullptr));
        label->setText(QCoreApplication::translate("ForgotPass", "Repeat Pass", nullptr));
        pushButton_change_pass_word->setText(QCoreApplication::translate("ForgotPass", "Change pass", nullptr));
        label_user_name->setText(QCoreApplication::translate("ForgotPass", "User Name", nullptr));
        label_fav_animal->setText(QCoreApplication::translate("ForgotPass", "Fav Animal", nullptr));
        label_fav_city->setText(QCoreApplication::translate("ForgotPass", "Fav City", nullptr));
        label_fav_color->setText(QCoreApplication::translate("ForgotPass", "Fav Color", nullptr));
        pushButton->setText(QCoreApplication::translate("ForgotPass", "Check", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ForgotPass: public Ui_ForgotPass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FORGOTPASS_H
