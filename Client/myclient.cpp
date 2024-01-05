#include "myclient.h"
#include "ui_myclient.h"

myClient::myClient(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::myClient)
{
    ui->setupUi(this);

    tcpSocket = new QTcpSocket();

    connect(tcpSocket,&QTcpSocket::readyRead,this, &myClient::readSocket);
    connect(tcpSocket,&QTcpSocket::disconnected,this,myClient::discardSocket);

    QString IPAddress = "127.0.0.1";
    tcpSocket->connectToHost(QHostAddress(IPAddress),43000);
    if (tcpSocket->waitForConnected(3000))
    {
        qDebug() << "client is connected";
    }
    else
    {
        qDebug()<<"client is NOT connected:"+ tcpSocket->errorString();
    }
}

myClient::~myClient()
{
    delete ui;
}

void myClient::readSocket()
{

    QByteArray DataBuffer;
    QDataStream socketstream(tcpSocket);
    socketstream.setVersion(QDataStream::Qt_6_6);
    socketstream.startTransaction();
    socketstream >> DataBuffer;
    if (socketstream.commitTransaction() == false)
    {
        return;
    }
    QString HeaderData = DataBuffer.mid(0, 128);

    QString fileName = HeaderData.split(',')[0].split(':')[1];
    QString fileSize = fileName.split('.')[1];
    QString fileExt = HeaderData.split(',')[1].split(':')[1];

    DataBuffer = DataBuffer.mid(128);

    QString saveFilePath = QCoreApplication::applicationDirPath() + "/" + fileName;

    QFile file(saveFilePath);
    if (file.open(QIODevice::WriteOnly))
    {
        file.write(DataBuffer);
        file.close();
    }

}

void myClient::discardSocket()
{
    tcpSocket->deleteLater();
}

void myClient::Doing_senging_file()
{
    if (tcpSocket)
    {
        if (tcpSocket->isOpen())
        {
            QString filePath = QFileDialog::getOpenFileName(this,"Select File",QCoreApplication::applicationDirPath(),"File (*.txt *.db)");
            sendFile(tcpSocket,filePath);
        }
    }
}

void myClient::sendFile(QTcpSocket *socket, QString fileName)
{
    if (socket)
    {
        if(socket->isOpen())
        {
            QFile filedata(fileName);
            if (filedata.open(QIODevice::ReadOnly))
            {
                QFileInfo fileInfo(filedata);
                QString fileNameWith(fileInfo.fileName());
                QDataStream socketstream(socket);
                socketstream.setVersion(QDataStream::Qt_6_6);

                QByteArray header;
                QString str("filename:" + fileNameWith + ",filesize:" + QString::number(filedata.size()));
                QByteArray br = str.toUtf8();
                header.prepend(br);
                header.resize(128);
                QByteArray ByteFileData = filedata.readAll();
                ByteFileData.prepend(header);
                socketstream << ByteFileData;
            }
            else
            {
                qDebug()<<"file not open";
            }
        }
        else
        {
            qDebug()<<"clien socket not open";
        }
    }
    else
    {
        qDebug()<<"clien socket is invalid";
    }
}


void myClient::on_pushButton_Login_clicked()
{
    Doing_senging_file();
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
