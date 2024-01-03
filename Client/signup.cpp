#include "signup.h"
#include "ui_signup.h"

Signup::Signup(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Signup)
{
    ui->setupUi(this);
}

Signup::~Signup()
{
    delete ui;
}

void Signup::on_pushButton_signup_clicked()
{
    if(ui->lineEdit_user_name->text().isEmpty() || ui->lineEdit_pass->text().isEmpty() || ui->lineEdit_personal_name->text().isEmpty()||
        ui->lineEdit_email->text().isEmpty() || ui->lineEdit_recoveryWordAnimal->text().isEmpty() || ui->lineEdit_recoveryWordColor->text().isEmpty()||
        ui->lineEdit_recoveryWordCity->text().isEmpty())
        QMessageBox::information(this,"this","fill all the fields");
    else{
        QString input_user_name = ui->lineEdit_user_name->text();
        QString input_user_pass = ui->lineEdit_pass->text();
        QString input_user_personal_name = ui->lineEdit_personal_name->text();
        QString input_user_email = ui->lineEdit_email->text();
        QString input_user_animal_recovery = ui->lineEdit_recoveryWordAnimal->text();
        QString input_user_color_recovery = ui->lineEdit_recoveryWordColor->text();
        QString input_user_city_recovery = ui->lineEdit_recoveryWordCity->text();
        if(input_user_pass.length() > 8){
            bool flag_lower_case = false;
            bool flag_upper_case = false;
            for(int i = 0;i<input_user_pass.length();i++){
                if(input_user_pass[i].isLower()){
                    flag_lower_case = true;
                }
                if(input_user_pass[i].isUpper()){
                    flag_upper_case = true;
                }
            }
            if(flag_lower_case && flag_upper_case){
                QMessageBox::information(this,"this","good");
                //here we should send it to file







            }
            else{
                QMessageBox::information(this,"this","try again");
            }
        }
        else{
            QMessageBox::information(this,"this","too short try again");
        }
    }
}

