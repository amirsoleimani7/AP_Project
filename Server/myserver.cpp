#include "myserver.h"
#include "ui_myserver.h"

myServer::myServer(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::myServer)

{
    ui->setupUi(this);
    tcpServe = new QTcpServer;
    if (tcpServe->listen(QHostAddress::AnyIPv4,43000))
    {
        connect(tcpServe,&QTcpServer::newConnection,this,&myServer::newConnection);
        ui->statusbar->showMessage("Tcp started");
    }
    else
    {
        QMessageBox::information(this, "tcp error ",tcpServe->errorString());
    }

    mydb= QSqlDatabase::addDatabase("QSQLITE");
    mydb.setDatabaseName("C:/Users/amir_1/Desktop/DataBase/person_database.db");

    if(!mydb.open()){
        qDebug() << ("data is no open");
    }
    else{
        qDebug() << ("data is open");
    }

}

myServer::~myServer()

{
    delete ui;
}

void myServer::readSocket()
{
    QTcpSocket *socket =reinterpret_cast<QTcpSocket*>(sender());
    QByteArray DataBuffer;
    QDataStream socketstream(socket);
    socketstream.setVersion(QDataStream::Qt_6_6);
    socketstream.startTransaction();
    socketstream >> DataBuffer;
    if (socketstream.commitTransaction() == false)
    {
        return;
    }
    QString HeaderData = DataBuffer.mid(0, 128);

    QString fileName = HeaderData.split(',')[0].split(':')[1];
    QString fileSize = fileName.split(':')[1];
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

void myServer::discardsocket()
{
    QTcpSocket* socket = reinterpret_cast<QTcpSocket*>(sender());
    int idx = clientList.indexOf(socket);
    if (idx > (-1))
    {
        clientList.removeAt(idx);
    }
    ui->clientListCombo->clear();
    foreach (QTcpSocket* sockettemp, clientList)
    {
        ui->clientListCombo->addItem(QString::number(sockettemp->socketDescriptor()));
    }
    socket->deleteLater();
}

void myServer::newConnection()
{
    while(tcpServe->hasPendingConnections())
    {
        addToSocketList(tcpServe->nextPendingConnection());
    }

}

void myServer::addToSocketList(QTcpSocket *socket)
{
    clientList.append(socket);
    connect(socket,&QTcpSocket::readyRead,this, &myServer::readSocket);
    connect(socket,&QTcpSocket::disconnected,this,myServer::discardsocket);
    ui->textEditMasages->append("Client is connected : socket : " + QString::number(socket->socketDescriptor()));
    ui->clientListCombo->addItem(QString::number(socket->socketDescriptor()));
}

void myServer::on_sendFileBTN_clicked()
{
    QString filePath = QFileDialog::getOpenFileName(this,"Select File",QCoreApplication::applicationDirPath(),"File (*.txt *.db)");
    if (ui->transferType->currentText() == "broadcast")
    {
        foreach (QTcpSocket* sockettemp, clientList)
        {
            sendFile(sockettemp,filePath);
        }
    }
    else if(ui->transferType->currentText() == "reciver")
    {
        QString receiverId = ui->clientListCombo->currentText();
        foreach (QTcpSocket* sockettemp, clientList)
        {
            if (sockettemp->socketDescriptor() == receiverId.toLongLong())
            {
            sendFile(sockettemp,filePath);
            }
        }
    }
}



void myServer::sendFile(QTcpSocket *socket, QString fileName)
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

//adding functions
void myServer::add_person_to_data_base(QString &user_data)
{
    //format should be something like
    QStringList fields = user_data.split("*");
    QString user_name_to_database = fields[1];

    // Check if the user already exists
    QSqlQuery checkQuery;
    checkQuery.prepare("SELECT * FROM person_info_database WHERE username = :user_name_given");
    checkQuery.bindValue(":user_name_given", user_name_to_database);

    if (checkQuery.exec() && checkQuery.next()) {
        qDebug() << "User with the same username already exists in the database.";
    } else {
        // User doesn't exist, add them to the database
        QSqlQuery insertQuery;

        insertQuery.prepare("INSERT INTO person_info_database (username, password, personal_name, email, fav_animal, fav_color, fav_city, organizations, teams, projects, tasks) VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?)");

        // Bind values for the insertion
        insertQuery.addBindValue(fields[1]);  // username
        insertQuery.addBindValue(fields[2]);  // password
        insertQuery.addBindValue(fields[3]);  // personal_name
        insertQuery.addBindValue(fields[4]);  // email
        insertQuery.addBindValue(fields[5]);  // fav_animal
        insertQuery.addBindValue(fields[6]);  // fav_color
        insertQuery.addBindValue(fields[7]);  // fav_city

        insertQuery.addBindValue("default_org");
        insertQuery.addBindValue("default_teams");
        insertQuery.addBindValue("default_projects");
        insertQuery.addBindValue("default_tasks");

        // Execute the insertion query
        if (insertQuery.exec()) {
            qDebug() << "User added successfully.";
            // Sending feedback through socket that person added to the database
        } else {
            qDebug() << "Could not add user." <<insertQuery.lastError();
        }
    }
}

