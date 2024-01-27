#include "signup.h"
#include "ui_signup.h"

Signup::Signup(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Signup)
{
    ui->setupUi(this);
    socket = new socket_connection(this);
}

Signup::~Signup()
{
    delete ui;
}

// void Signup::witing_instructions(QString &instruction)
// {
//     QString filePath = QCoreApplication::applicationDirPath() + '/' + "User.txt";
//     QFile file(filePath);

//     // Open the file in WriteOnly mode
//     if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
//         // Create a QTextStream to write to the file
//         QTextStream out(&file);

//         // Write data to the file
//         out << instruction ;

//         file.close();

//         qDebug() << "Data has been written to the file.";
//     } else {
//         // Handle the case where the file cannot be opened
//         qDebug() << "Error opening the file for writing.";
//     }

// }

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
                QString user_to_add ="add_person*id*"+input_user_name+"*"+input_user_pass+"*"+input_user_personal_name+"*"+input_user_email+"*"+input_user_animal_recovery+"*"+input_user_color_recovery+"*"+input_user_city_recovery;
                socket->witing_instructions(user_to_add);
                socket->delay();
                QString x = socket->reading_feed_back();
                qDebug() << "feed back for signup : "<< x;
                if(x == "true_person_add"){
                    QMessageBox::information(this,"add account","person added");
                }
                else{
                    QMessageBox::information(this,"warning",x);
                }
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

