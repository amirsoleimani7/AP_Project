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

void myServer::change_user_personal_name(QString &name_in_data_base, QString &new_name_1)
{

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
//---------------
//adding person to function
void myServer::add_person_to_data_base(QString &user_data)
{

    //format should be something like {id*username*personal_name*.....}
    QStringList fields = user_data.split("*");
    QString user_name_to_database = fields[2];

    // Check if the user already exists
    QSqlQuery checkQuery;
    checkQuery.prepare("SELECT * FROM person_info_database WHERE username = :user_name_given");
    checkQuery.bindValue(":user_name_given", user_name_to_database);

    if (checkQuery.exec() && checkQuery.next()) {
        qDebug() << "User with the same username already exists in the database.";
    } else {
        // User doesn't exist, add them to the database
        QSqlQuery insertQuery;

        insertQuery.prepare("INSERT INTO person_info_database (username, password, personal_name, email, fav_animal, fav_color, fav_city, organizations, teams, projects, tasks) VALUES (?, ? , ?, ?, ?, ?, ?, ?, ?, ?, ?, ?)");

        // Bind values for the insertion
        insertQuery.addBindValue(fields[1]);  // id
        insertQuery.addBindValue(fields[2]);  // username
        insertQuery.addBindValue(fields[3]);  // pass
        insertQuery.addBindValue(fields[4]);  // personalname
        insertQuery.addBindValue(fields[5]);  // email
        insertQuery.addBindValue(fields[6]);  // fav_animal
        insertQuery.addBindValue(fields[7]);  // fav_color
        insertQuery.addBindValue(fields[8]);  // fav_city


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


//----------------------
void change_user_personal_name(QString& name_in_data_base,QString &new_name_1)
{
    QString user_name_in_data_base = name_in_data_base;
    QString new_name  = new_name_1;

    //updating personal_name

    QSqlQuery updateQuery;
    updateQuery.prepare("UPDATE person_info_database SET personal_name = :new_name WHERE username = :user_name_in_data_base");
    updateQuery.bindValue(":new_name", new_name);
    updateQuery.bindValue(":user_name_in_data_base", user_name_in_data_base);

    if (updateQuery.exec()) {
        qDebug() << "Personal name updated successfully.";
        //feed back should be handled here


    } else {
        qDebug() << "Could not update personal name." << updateQuery.lastError();
        //feedback should be handled here
    }


}
//------------------------
void myServer::change_user_email(QString &name_in_data_base, QString &new_email_1)
{
    QString user_name_in_data_base = name_in_data_base;
    QString new_email  = new_email_1;

    QSqlQuery updateQuery;
    updateQuery.prepare("UPDATE person_info_database SET email = :new_email WHERE username = :user_name_in_data_base");
    updateQuery.bindValue(":new_email", new_email);
    updateQuery.bindValue(":user_name_in_data_base", user_name_in_data_base);

    if (updateQuery.exec()) {
        qDebug() << "email  updated successfully.";
        //feed back should be handled here




    } else {
        qDebug() << "Could not update email." << updateQuery.lastError();
        //feedback should be handled here


    }



}
//-------------------------------
void myServer::chnage_user_pass(QString &name_in_data_base, QString &new_pass_1)
{
    QString user_name_in_data_base = name_in_data_base;
    QString new_pass  = new_pass_1;

    QSqlQuery updateQuery;
    updateQuery.prepare("UPDATE person_info_database SET password = :new_pass WHERE username = :user_name_in_data_base");
    updateQuery.bindValue(":new_pass", new_pass);
    updateQuery.bindValue(":user_name_in_data_base", user_name_in_data_base);

    if (updateQuery.exec()) {
        qDebug() << "pass  updated successfully.";
        //feed back should be handled here


    } else {
        qDebug() << "Could not update pass." << updateQuery.lastError();
        //feedback should be handled here
    }
}
//----------------------------------
QString myServer::get_user_info(QString& name_in_data_base)
{
    QString user_in_data_base = name_in_data_base;
    QString user_info;

    QSqlQuery selectQuery;
    selectQuery.prepare("SELECT * FROM person_info_database WHERE username = :user_in_data_base");
    selectQuery.bindValue(":user_in_data_base", user_in_data_base);

    if (selectQuery.exec() && selectQuery.next()) {

        QString id = selectQuery.value("person_id").toString();
        QString user_name = selectQuery.value("username").toString();
        QString password = selectQuery.value("password").toString();
        QString personal_name = selectQuery.value("personal_name").toString();
        QString email = selectQuery.value("email").toString();
        QString fav_animal = selectQuery.value("fav_animal").toString();
        QString fav_color = selectQuery.value("fav_color").toString();
        QString fav_city = selectQuery.value("fav_city").toString();

        user_info = QString("%1*%2*%3*%4*%5*%6*%7*%8")
                        .arg(id, user_name, password, personal_name, email, fav_animal, fav_color, fav_city);

        qDebug() << user_info;
        return user_info;

    } else {
        qDebug() << "User not found or an error occurred." << selectQuery.lastError();
    }
}

//----------------------------

QString myServer::check_for_pass_word(QString &name_in_data_base, QString &input_password)
{
    QString user_name = name_in_data_base;
    QString user_pass = input_password;

    QSqlQuery selectQuery;
    selectQuery.prepare("SELECT * FROM person_info_database WHERE username = :user_in_data_base");
    selectQuery.bindValue(":user_in_data_base", user_name);
    if (selectQuery.exec() && selectQuery.next()) {
        QString password = selectQuery.value("password").toString();
        if(password == user_pass){
            qDebug() << "correct\n";
            //sending feedbacks


        }
        else{
            qDebug() << "not correct\n";
            //sending feedbacks

        }
    }
    else{
        qDebug() << "person was not found\n";
        //sending feedbacks
    }
}

//----------------------
//adding organization
void myServer::add_organizations_to_person(QString &name_in_data_base, QString &organizations_name)
{
    QString user_name_in_data_base = name_in_data_base;  // Set the actual username
    QString organizations_to_add = organizations_name;

    QSqlQuery selectQuery;
    selectQuery.prepare("SELECT * FROM person_info_database WHERE username = :user_in_data_base");
    selectQuery.bindValue(":user_in_data_base", user_name_in_data_base);

    if (selectQuery.exec() && selectQuery.next()) {
        QString list_of_organizations = selectQuery.value("organizations").toString();

        QStringList existingOrganizations = list_of_organizations.split(",");

        if (!existingOrganizations.contains(organizations_to_add)) {
            list_of_organizations += "," + organizations_to_add;

            QSqlQuery updateQuery;
            updateQuery.prepare("UPDATE person_info_database SET organizations = :new_organizations WHERE username = :user_in_data_base");
            updateQuery.bindValue(":new_organizations", list_of_organizations);
            updateQuery.bindValue(":user_in_data_base", user_name_in_data_base);
            if (updateQuery.exec()) {
                qDebug() << "Row updated successfully.";
                //feed back for updating the row



            } else {
                qDebug() << "Failed to update row." << updateQuery.lastError();
                //fail


            }
        } else {
            qDebug() << "Organization already exists in the list.";
            //organizations already exits


        }
    } else {
        qDebug() << "User not found or an error occurred." << selectQuery.lastError();
        //feedback for user not existing


    }
}

//-------------------------

void myServer::add_team_to_person(QString &name_in_data_base, QString &team_name)
{
    QString user_name_in_data_base = name_in_data_base;  // Set the actual username
    QString team_to_add = team_name;

    QSqlQuery selectQuery;
    selectQuery.prepare("SELECT * FROM person_info_database WHERE username = :user_in_data_base");
    selectQuery.bindValue(":user_in_data_base", user_name_in_data_base);

    if (selectQuery.exec() && selectQuery.next()) {
        QString list_of_team = selectQuery.value("teams").toString();

        QStringList existingteam = list_of_team.split(",");

        if (!existingteam.contains(team_to_add)) {
            list_of_team += "," + team_to_add;

            QSqlQuery updateQuery;
            updateQuery.prepare("UPDATE person_info_database SET teams = :new_teams WHERE username = :user_in_data_base");
            updateQuery.bindValue(":new_teams", list_of_team);
            updateQuery.bindValue(":user_in_data_base", user_name_in_data_base);

            if (updateQuery.exec())
            {
                qDebug() << "Row updated successfully.";
            }
            else {
                qDebug() << "Failed to update row." << updateQuery.lastError();
            }
        } else {
            qDebug() << "team already exists in the list.";
        }
    } else {
        qDebug() << "User not found or an error occurred." << selectQuery.lastError();
    }
}


//---------------------------------
void myServer::add_project_to_person(QString &name_in_data_base, QString &project_name)
{
    QString user_name_in_data_base = name_in_data_base;  // Set the actual username
    QString project_to_add = project_name;

    QSqlQuery selectQuery;
    selectQuery.prepare("SELECT * FROM person_info_database WHERE username = :user_in_data_base");
    selectQuery.bindValue(":user_in_data_base", user_name_in_data_base);

    if (selectQuery.exec() && selectQuery.next()) {
        QString list_of_project = selectQuery.value("projects").toString();

        QStringList existingProject = list_of_project.split(",");

        if (!existingProject.contains(project_to_add)) {
            list_of_project += "," + project_to_add;

            QSqlQuery updateQuery;
            updateQuery.prepare("UPDATE person_info_database SET projects = :new_project WHERE username = :user_in_data_base");
            updateQuery.bindValue(":new_project", list_of_project);
            updateQuery.bindValue(":user_in_data_base", user_name_in_data_base);

            if (updateQuery.exec())
            {
                qDebug() << "Row updated successfully.";
            }
            else {
                qDebug() << "Failed to update row." << updateQuery.lastError();
            }
        } else {
            qDebug() << "project already exists in the list.";
        }
    } else {
        qDebug() << "User not found or an error occurred." << selectQuery.lastError();
    }
}


//---------------------------------
void myServer::add_task_to_person(QString &name_in_data_base, QString &task_name)
{
    QString user_name_in_data_base = name_in_data_base;  // Set the actual username
    QString task_to_add = task_name;

    QSqlQuery selectQuery;
    selectQuery.prepare("SELECT * FROM person_info_database WHERE username = :user_in_data_base");
    selectQuery.bindValue(":user_in_data_base", user_name_in_data_base);

    if (selectQuery.exec() && selectQuery.next()) {
        QString list_of_task = selectQuery.value("tasks").toString();

        QStringList existingTask = list_of_task.split(",");

        if (!existingTask.contains(task_to_add)) {
            list_of_task += "," + task_to_add;

            QSqlQuery updateQuery;
            updateQuery.prepare("UPDATE person_info_database SET tasks = :new_task WHERE username = :user_in_data_base");
            updateQuery.bindValue(":new_task", list_of_task);
            updateQuery.bindValue(":user_in_data_base", user_name_in_data_base);

            if (updateQuery.exec())
            {
                qDebug() << "Row updated successfully.";
            }
            else {
                qDebug() << "Failed to update row." << updateQuery.lastError();
            }
        } else {
            qDebug() << "task already exists in the list.";
        }
    } else {
        qDebug() << "User not found or an error occurred." << selectQuery.lastError();
    }
}


//-----------------------------------------

void myServer::remove_organization_from_person(QString &name_in_data_base, QString &organizations_name)
{
    QString user_name_in_data_base = name_in_data_base;  // Set the actual username
    QString remove_name_organization = organizations_name;  // Set the organization to remove

    QSqlQuery selectQuery;
    selectQuery.prepare("SELECT * FROM person_info_database WHERE username = :user_in_data_base");
    selectQuery.bindValue(":user_in_data_base", name_in_data_base);

    if (selectQuery.exec() && selectQuery.next()) {
        QString list_of_organizations = selectQuery.value("organizations").toString();

        // Split the existing organizations
        QStringList existingOrganizations = list_of_organizations.split(",");

        // Check if the organization to remove exists
        if (existingOrganizations.contains(remove_name_organization)) {
            // Remove the organization
            existingOrganizations.removeAll(remove_name_organization);

            // Join the organizations back into a string
            QString newListOfOrganizations = existingOrganizations.join(",");

            // Update the row with the new list of organizations
            QSqlQuery updateQuery;
            updateQuery.prepare("UPDATE person_info_database SET organizations = :new_organizations WHERE username = :user_in_data_base");
            updateQuery.bindValue(":new_organizations", newListOfOrganizations);
            updateQuery.bindValue(":user_in_data_base", name_in_data_base);

            if (updateQuery.exec()) {
                qDebug() << "Organization removed successfully.";
                //should hande feedback



            } else {
                qDebug() << "Failed to update row." << updateQuery.lastError();

                //should handle feedback
            }
        } else {
            qDebug() << "Organization not found in the list.";
        }
    } else {
        qDebug() << "User not found or an error occurred." << selectQuery.lastError();
    }

}
//-------------------------------------

