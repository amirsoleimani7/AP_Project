#ifndef MYSERVER_H
#define MYSERVER_H

#include <QMainWindow>
#include <QtNetwork>
#include <QtGui>
#include <QtCore>
#include <QtWidgets>
#include <QDebug>
#include <Qtsql>
#include <QSqlDatabase>
#include <QFileInfo>
#include <QVector>
#include <QString>
#include <QStringList>


QT_BEGIN_NAMESPACE
namespace Ui {
class myServer;
}
QT_END_NAMESPACE

class myServer : public QMainWindow
{
    Q_OBJECT

public:
    myServer(QWidget *parent = nullptr);
    ~myServer();
private slots:
    void readSocket();
    void discardsocket();
    void newConnection();
    void addToSocketList(QTcpSocket* socket);
    void on_sendFileBTN_clicked();
    void change_user_personal_name(QString& name_in_data_base,QString &new_name_1);
    void add_person_to_data_base(QString &user_data);
    void change_user_email(QString& name_in_data_base,QString &new_email_1);
    void chnage_user_pass(QString& name_in_data_base,QString &new_pass_1);
    QString get_user_info(QString& name_in_data_base);

private:
    void sendFile (QTcpSocket* socket,QString fileName);

private:
    Ui::myServer *ui;
    QSqlDatabase mydb;
    QTcpServer *tcpServe;
    QList<QTcpSocket*> clientList;

};
#endif // MYSERVER_H
