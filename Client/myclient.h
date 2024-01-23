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
#include "socket_connection.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class myClient;
}
QT_END_NAMESPACE

class myClient : public QMainWindow
{
    Q_OBJECT

public:
    QString currentUserName;
    myClient(QWidget *parent = nullptr);
    ~myClient();
    //QString reading_feed_back();

public slots:

    // void readSocket();
    // //void witing_instructions(QString& instruction);

    // void discardSocket();

    // void Doing_senging_file();

    void on_pushButton_Login_clicked();

    void on_pushButton_signup_clicked();

    void on_pushButton_forgot_clicked();

private:
    //void sendFile (QTcpSocket* socket,QString fileName);
private:

    Ui::myClient *ui;
    Signup *show_sign_up_page;
    ForgotPass *show_forgot_page;
    socket_connection *socket;
    // QTcpSocket * tcpSocket;

};
#endif // MYCLIENT_H
