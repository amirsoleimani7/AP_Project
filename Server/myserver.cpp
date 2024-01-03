#include "myserver.h"
#include "ui_myserver.h"

myServer::myServer(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::myServer)

{
    ui->setupUi(this);
    tcpServe = new QTcpServer;
    if (tcpServe->listen(QHostAddress::AnyIPv4,43000)){
        connect(tcpServe,&QTcpServer::newConnection,this,&myServer::newConnection);
        ui->statusbar->showMessage("Tcp started");
    }
    else{
        QMessageBox::information(this, "tcp error ",tcpServe->errorString());
    }
}

myServer::~myServer()

{
    delete ui;
}

void myServer::readSocket()
{

}

void myServer::discardsocket()
{
    QTcpSocket* socket = reinterpret_cast<QTcpSocket*>(sender());
    int id = clientList.indexOf(socket);
    if (id>-1){
        clientList.removeAt(id);
    }
    ui->clientListCombo->clear();
    foreach (QTcpSocket* sockettemp, clientList) {
        ui->clientListCombo->addItem(QString::number(sockettemp->socketDescriptor()));
    }
    socket->deleteLater();
}

void myServer::newConnection()
{
    while(tcpServe->hasPendingConnections()){
        addToSocketList(tcpServe->nextPendingConnection());
    }

}

void myServer::addToSocketList(QTcpSocket *socket)
{
    clientList.append(socket);
    connect(socket,&QTcpSocket::readyRead,this, &myServer::readSocket);
    connect(socket,&QTcpSocket::disconnected,this,myServer::discardsocket);
    ui->textEditMasages->append("Client is connected : socket : " + Qstring::number(socket->socketDescriptor()));
    ui->clientListCombo->addItem(Qstring::number(socket->socketDescriptor()));
}

void myServer::on_sendFileBTN_clicked()
{

}

void myServer::sendFile(QTcpSocket *socket, QString fileName)
{

}

