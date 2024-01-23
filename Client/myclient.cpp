#include "myclient.h"
#include <QDesktopServices>
#include "ui_myclient.h"


myClient::myClient(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::myClient)
{
    ui->setupUi(this);

    socket = new socket_connection(this);
    // tcpSocket = new QTcpSocket();

    // connect(tcpSocket,&QTcpSocket::readyRead,this, &myClient::readSocket);
    // connect(tcpSocket,&QTcpSocket::disconnected,this,&myClient::discardSocket);

    // QString IPAddress = "127.0.0.1";
    // tcpSocket->connectToHost(QHostAddress(IPAddress),43000);
    // if (tcpSocket->waitForConnected(3000))
    // {
    //     qDebug() << "client is connected";
    // }
    // else
    // {
    //     qDebug()<< "client is NOT connected:"+ tcpSocket->errorString();
    // }
}

myClient::~myClient()
{
    delete ui;
}

// QString myClient::reading_feed_back()
// {

//     QString saveFilePath = QCoreApplication::applicationDirPath() + "/" + "feedBack.txt";

//     QFile file_1(saveFilePath);
//     QString feedback = "";
//     // Open the file in ReadOnly mode
//     if (file_1.open(QIODevice::ReadOnly | QIODevice::Text)) {
//         // Create a QTextStream to read from the file
//         QTextStream in(&file_1);

//         // Read data from the file
//         while (!in.atEnd()) {
//             QString line = in.readLine();
//             feedback+=line;
//         }

//         // Close the file
//         file_1.close();

//         qDebug() << "Data has been read from the file.";
//     } else {
//         // Handle the case where the file cannot be opened
//         qDebug() << "Error opening the file for reading.";

//     }
//     //qDebug() << feedback;
//     return feedback;
// }


// //---------------
// void witing_instructions(QString& instruction)
// {
//     QString filePath = QCoreApplication::applicationDirPath() + '/' + "User.txt";
//     QFile file(filePath);

//     // Open the file in WriteOnly mode
//     if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
//             // Create a QTextStream to write to the file
//         QTextStream out(&file);

//             // Write data to the file
//         out << instruction ;

//         file.close();

//         qDebug() << "Data has been written to the file.";
//     } else {
//             // Handle the case where the file cannot be opened
//         qDebug() << "Error opening the file for writing.";
//     }
// }

// //------------
// void  myClient::readSocket()
// {

//     QByteArray DataBuffer;
//     QDataStream socketstream(tcpSocket);
//     socketstream.setVersion(QDataStream::Qt_6_6);
//     socketstream.startTransaction();
//     socketstream >> DataBuffer;
//     if (socketstream.commitTransaction() == false)
//     {
//         qDebug() <<"1th : "<<DataBuffer;
//         return;

//     }
//     QString HeaderData = DataBuffer.mid(0, 128);

//     QString fileName = HeaderData.split(',')[0].split(':')[1];
//     QString fileSize = fileName.split('.')[1];
//     QString fileExt = HeaderData.split(',')[1].split(':')[1];

//     DataBuffer = DataBuffer.mid(128);
//     if(DataBuffer == "it_isdone"){
//         QMessageBox::information(this,"this","done");
//     }

//     QString saveFilePath = QCoreApplication::applicationDirPath() + "/" + fileName;

//     QFile file(saveFilePath);
//     if (file.open(QIODevice::WriteOnly))
//     {
//         file.write(DataBuffer);
//         file.close();
//     }

//     QFile file_1(saveFilePath);
//     QString feedback = "";
//     // Open the file in ReadOnly mode
//     if (file_1.open(QIODevice::ReadOnly | QIODevice::Text)) {
//         // Create a QTextStream to read from the file
//         QTextStream in(&file_1);

//         // Read data from the file
//         while (!in.atEnd()) {
//             QString line = in.readLine();
//             feedback+=line;
//         }

//         // Close the file
//         file_1.close();

//         qDebug() << "Data has been read from the file.";
//     } else {
//         // Handle the case where the file cannot be opened
//         qDebug() << "Error opening the file for reading.";

//     }

//     qDebug() <<"2th : " <<DataBuffer;
// }
// //---------------------

// void myClient::discardSocket()
// {
//     tcpSocket->deleteLater();
// }

// void myClient::Doing_senging_file()
// {
//     if (tcpSocket)
//     {
//         if (tcpSocket->isOpen())
//         {

//             QString filePath = QCoreApplication::applicationDirPath() + '/' + "User.txt";
//             sendFile(tcpSocket,filePath);

//         }
//     }
// }

// void myClient::sendFile(QTcpSocket *socket, QString fileName)
// {
//     if (socket)
//     {
//         if(socket->isOpen())
//         {
//             QFile filedata(fileName);
//             if (filedata.open(QIODevice::ReadOnly))
//             {
//                 QFileInfo fileInfo(filedata);
//                 QString fileNameWith(fileInfo.fileName());
//                 QDataStream socketstream(socket);
//                 socketstream.setVersion(QDataStream::Qt_6_6);

//                 QByteArray header;
//                 QString str("filename:" + fileNameWith + ",filesize:" + QString::number(filedata.size()));
//                 QByteArray br = str.toUtf8();
//                 header.prepend(br);
//                 header.resize(128);
//                 QByteArray ByteFileData = filedata.readAll();
//                 ByteFileData.prepend(header);
//                 socketstream << ByteFileData;
//             }
//             else
//             {
//                 qDebug()<<"file not open";
//             }
//         }
//         else
//         {
//             qDebug()<<"clien socket not open";
//         }
//     }
//     else
//     {
//         qDebug()<<"clien socket is invalid";
//     }
// }


void delay()
{
    QTime dieTime= QTime::currentTime().addSecs(1);
    while (QTime::currentTime() < dieTime)
        QCoreApplication::processEvents(QEventLoop::AllEvents, 1);
}


void myClient::on_pushButton_Login_clicked()
{

    QString input_user_name = ui->lineEdit_User_Name->text();
    currentUserName = input_user_name;
    QString input_user_pass = ui->lineEdit_Password->text();

    QString cheack_for_user_pass  = "cheack_pass*"+input_user_name+"*"+input_user_pass+"";
    socket->witing_instructions(cheack_for_user_pass);

    delay();

    QString x = socket->reading_feed_back();
    qDebug() << x;

    // QString link = "https://chat.openai.com/";
    // QDesktopServices::openUrl(QUrl(link));

    if(x  == "Correct_pass"){
        Dashboard *show_dashboard_page = new Dashboard(this,currentUserName);
        //show_dashboard_page =
        show_dashboard_page->exec();
    }

    else{

        QMessageBox::information(this,"this",x);
    }

    // void myServer::adding_comment_to_data_base(QString &comment_data)
    // {
    //     // CREATE TABLE "comment_info_database" (
    //     //     "comment_id"	TEXT,
    //     //     "comment_value"	TEXT,
    //     //     "comment_reply"	TEXT,
    //     //     "comment_task"	TEXT,
    //     //     "comment_person"	TEXT
    //     //     )


    //the logic must be added
    //sending throw socket

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
