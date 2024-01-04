#ifndef MYCLIENT_H
#define MYCLIENT_H

#include <QMainWindow>
#include "signup.h"
#include "forgotpass.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class myClient;
}
QT_END_NAMESPACE

class myClient : public QMainWindow
{
    Q_OBJECT

public:
    myClient(QWidget *parent = nullptr);
    ~myClient();

private slots:
    void on_pushButton_Login_clicked();

    void on_pushButton_signup_clicked();

    void on_pushButton_forgot_clicked();

private:
    Ui::myClient *ui;
    Signup *show_sign_up_page;
    ForgotPass *show_forgot_page;
};
#endif // MYCLIENT_H
