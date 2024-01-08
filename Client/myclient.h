#ifndef MYCLIENT_H
#define MYCLIENT_H



#include <QMainWindow>
#include <QtNetwork>
#include <QtGui>
#include <QtCore>
#include <QtWidgets>
#include "forgotpass.h"
#include "dashboard.h"
#include <QFile>
#include <QTextStream>
#include <QDebug>
#include <QMessageBox>
#include "signup.h"


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
    QString reading_feed_back();

private slots:


    void readSocket();

    //void witing_instructions(QString& instruction);

    void discardSocket();

    void Doing_senging_file();

    void on_pushButton_Login_clicked();

    void on_pushButton_signup_clicked();

    void on_pushButton_forgot_clicked();

private:
    void sendFile (QTcpSocket* socket,QString fileName);
private:

    Ui::myClient *ui;
    Signup *show_sign_up_page;
    ForgotPass *show_forgot_page;
    Dashboard *show_dashboard_page;
    QTcpSocket * tcpSocket;
};
#endif // MYCLIENT_H
