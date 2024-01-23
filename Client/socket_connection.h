#ifndef SOCKET_CONNECTION_H
#define SOCKET_CONNECTION_H

#include <QString>
#include <QMainWindow>
#include <QtNetwork>
#include <QtGui>
#include <QtCore>
#include <QtWidgets>
#include <QFile>
#include <QTextStream>
#include <QDebug>
#include <QMessageBox>



class socket_connection : public QMainWindow
{
    Q_OBJECT

public:

    socket_connection(QWidget *parent = nullptr);
    ~socket_connection();
    QString reading_feed_back();

public slots:
    void delay();
    void readSocket();


    void witing_instructions(QString& instruction);

    void discardSocket();

    void Doing_senging_file();

    void sendFile (QTcpSocket* socket,QString fileName);
private:
    QTcpSocket * tcpSocket;
};

#endif // SOCKET_CONNECTION_H
