#ifndef MYSERVER_H
#define MYSERVER_H

#include <QMainWindow>
#include <QtNetwork>
#include <QtGui>
#include <QtCore>
#include <QtWidgets>


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

private:
    void sendFile (QTcpSocket* socket,QString fileName);

private:
    Ui::myServer *ui;

    QTcpServer *tcpServe;
    QList<QTcpSocket> clientList;

};
#endif // MYSERVER_H
