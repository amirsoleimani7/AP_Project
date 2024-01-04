#include "myclient.h"
#include "ui_myclient.h"

myClient::myClient(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::myClient)
{
    ui->setupUi(this);
}

myClient::~myClient()
{
    delete ui;
}

void myClient::on_pushButton_Login_clicked()
{
    QString input_user_name = ui->lineEdit_User_Name->text();
    QString input_user_pass = ui->lineEdit_Password->text();
    //the logic must be added
}

void myClient::on_pushButton_signup_clicked()
{
    show_sign_up_page = new Signup(this);
    show_sign_up_page->exec();
}

void myClient::on_pushButton_forgot_clicked()
{
    show_forgot_page = new ForgotPass(this);
    show_forgot_page->exec();
}

