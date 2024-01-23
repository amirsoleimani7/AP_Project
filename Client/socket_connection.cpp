#include "socket_connection.h"


socket_connection::socket_connection(QWidget *parent)
    : QMainWindow(parent)
{

    tcpSocket = new QTcpSocket();

    connect(tcpSocket,&QTcpSocket::readyRead,this, &socket_connection::readSocket);
    connect(tcpSocket,&QTcpSocket::disconnected,this,&socket_connection::discardSocket);

    QString IPAddress = "127.0.0.1";
    tcpSocket->connectToHost(QHostAddress(IPAddress),43000);
    if (tcpSocket->waitForConnected(3000))
    {
        qDebug() << "client is connected";
    }
    else
    {
        qDebug()<< "client is NOT connected:"+ tcpSocket->errorString();
    }
}

void socket_connection::delay()
{
    QTime dieTime= QTime::currentTime().addSecs(1);
    while (QTime::currentTime() < dieTime)
        QCoreApplication::processEvents(QEventLoop::AllEvents, 1);
}

socket_connection::~socket_connection()
{
}

QString socket_connection::reading_feed_back()
{

    QString saveFilePath = QCoreApplication::applicationDirPath() + "/" + "feedBack.txt";

    QFile file_1(saveFilePath);
    QString feedback = "";
    // Open the file in ReadOnly mode
    if (file_1.open(QIODevice::ReadOnly | QIODevice::Text)) {
        // Create a QTextStream to read from the file
        QTextStream in(&file_1);

        // Read data from the file
        while (!in.atEnd()) {
            QString line = in.readLine();
            feedback+=line;
        }

        // Close the file
        file_1.close();

        qDebug() << "Data has been read from the file.";
    } else {
        // Handle the case where the file cannot be opened
        qDebug() << "Error opening the file for reading.";

    }
    //qDebug() << feedback;
    return feedback;
}


//---------------
void socket_connection::witing_instructions(QString& instruction)
{
    QString filePath = QCoreApplication::applicationDirPath() + '/' + "User.txt";
    QFile file(filePath);

    // Open the file in WriteOnly mode
    if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        // Create a QTextStream to write to the file
        QTextStream out(&file);

        // Write data to the file
        out << instruction ;

        file.close();

        qDebug() << "Data has been written to the file.";
        Doing_senging_file();
    } else {
        // Handle the case where the file cannot be opened
        qDebug() << "Error opening the file for writing.";
    }

}

//------------
void socket_connection::readSocket()
{

    QByteArray DataBuffer;
    QDataStream socketstream(tcpSocket);
    socketstream.setVersion(QDataStream::Qt_6_6);
    socketstream.startTransaction();
    socketstream >> DataBuffer;
    if (socketstream.commitTransaction() == false)
    {
        qDebug() <<"1th : "<<DataBuffer;
        return;

    }
    QString HeaderData = DataBuffer.mid(0, 128);

    QString fileName = HeaderData.split(',')[0].split(':')[1];
    QString fileSize = fileName.split('.')[1];
    QString fileExt = HeaderData.split(',')[1].split(':')[1];

    DataBuffer = DataBuffer.mid(128);
    if(DataBuffer == "it_isdone"){
        QMessageBox::information(this,"this","done");
    }

    QString saveFilePath = QCoreApplication::applicationDirPath() + "/" + fileName;

    QFile file(saveFilePath);
    if (file.open(QIODevice::WriteOnly))
    {
        file.write(DataBuffer);
        file.close();
    }

    QFile file_1(saveFilePath);
    QString feedback = "";
    // Open the file in ReadOnly mode
    if (file_1.open(QIODevice::ReadOnly | QIODevice::Text)) {
        // Create a QTextStream to read from the file
        QTextStream in(&file_1);

        // Read data from the file
        while (!in.atEnd()) {
            QString line = in.readLine();
            feedback+=line;
        }

        // Close the file
        file_1.close();

        qDebug() << "Data has been read from the file.";
    } else {
        // Handle the case where the file cannot be opened
        qDebug() << "Error opening the file for reading.";

    }

    qDebug() <<"2th : " <<DataBuffer;
}
//---------------------

void socket_connection::discardSocket()
{
    tcpSocket->deleteLater();
}

void socket_connection::Doing_senging_file()
{
    if (tcpSocket)
    {
        if (tcpSocket->isOpen())
        {

            QString filePath = QCoreApplication::applicationDirPath() + '/' + "User.txt";
            sendFile(tcpSocket,filePath);
        }
    }
}

void socket_connection::sendFile(QTcpSocket *socket, QString fileName)
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

