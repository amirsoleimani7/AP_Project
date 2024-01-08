#include "forgotpass.h"
#include "ui_forgotpass.h"

ForgotPass::ForgotPass(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::ForgotPass)
{
    ui->setupUi(this);
}

ForgotPass::~ForgotPass()
{
    delete ui;
}


void ForgotPass::on_pushButton_clicked()
{
    if(ui->lineEdit_get_user_name->text().isEmpty() ||ui->lineEdit_get_fav_animal->text().isEmpty() ||
        ui->lineEdit_get_fav_city->text().isEmpty() || ui->lineEdit_get_fav_color->text().isEmpty()
    ){
        QMessageBox::information(this,"this","fill all the fields");
    }
    else{
        bool flag_can_change = false;
        QString user_name_input = ui->lineEdit_get_user_name->text();
        QString user_animal_input = ui->lineEdit_get_fav_animal->text();
        QString user_city_input = ui->lineEdit_get_fav_city->text();
        QString user_color_input = ui->lineEdit_get_fav_color->text();
        //we should check with the data base here
        //
        //

        if(flag_can_change){
            flag_change = true;
            ui->label_pass_status->setText("you can change your pass now");
        }

        else{
            flag_change = false;
            ui->label_pass_status->setText("you can't change your pass");
        }
    }

}
void ForgotPass::on_pushButton_change_pass_word_clicked()
{
    if(ui->lineEdit_new_pass_1->text().isEmpty() || ui->lineEdit_new_pass_2->text().isEmpty()){
        QMessageBox::information(this,"this","fill all the fields");

    }
    else{


    if(flag_change){
        QString user_new_pass_1 = ui->lineEdit_new_pass_1->text();
        QString user_new_pass_2 = ui->lineEdit_new_pass_2->text();
        if(user_new_pass_1 == user_new_pass_2){
            if(user_new_pass_1.length() > 8){
                bool flag_is_lower = false;
                bool flag_is_uppper = false;
                for(int i = 0 ;i<user_new_pass_1.length();i++){
                    if(user_new_pass_1[i].isUpper()){
                        flag_is_uppper = true;
                    }
                    if(user_new_pass_1[i].isLower()){
                        flag_is_lower = true;
                    }

                }

                if(flag_is_lower && flag_is_uppper){
                    QMessageBox::information(this,"this","name chnaged");
                    //here we should edit the data base
                    //
                    //
                    //
                }
                else{
                    QMessageBox::information(this,"this","trying again");

                }
            }
        }
        else{
            QMessageBox::information(this,"this","they should be the same");
        }
    }
    else{
        QMessageBox::information(this,"this","cant enter new pass");
        }
    }
}

