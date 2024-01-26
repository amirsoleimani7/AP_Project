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

    QFile::copy(":/data/person_database.db", "person_database.db");
    mydb_person= QSqlDatabase::addDatabase("QSQLITE","person_info_database");
    mydb_person.setDatabaseName("C:/Users/amir_1/Desktop/AP_Project/Server/person_database.db");
    mydb_person.setConnectOptions("QSQLITE_OPEN_READWRITE");

    if(!mydb_person.open()){
        qDebug() << "Error opening person database:" << mydb_person.lastError().text();
    }
    else{
        qDebug() << "Person database is open";
    }

    //for database organization
    QFile::copy(":/data/organization_database.db", "organization_database.db");
    mydb_organization = QSqlDatabase::addDatabase("QSQLITE", "organization_info_database");
    mydb_organization.setDatabaseName("C:/Users/amir_1/Desktop/AP_Project/Server/organization_database.db");

    if (!mydb_organization.open()) {
        qDebug() << "Error opening organization database:" << mydb_organization.lastError().text();
    } else {
        qDebug() << "Organization database is open";
    }

    //for database team
    QFile::copy(":/data/team_database.db", "team_database.db");
    mydb_team = QSqlDatabase::addDatabase("QSQLITE", "team_info_database");
    mydb_team.setDatabaseName("C:/Users/amir_1/Desktop/AP_Project/Server/team_database.db");

    if (!mydb_team.open()) {
        qDebug() << "Error opening team database:" << mydb_team.lastError().text();
    } else {
        qDebug() << "Team database is open";
    }

    //for database project
    QFile::copy(":/data/project_database.db", "project_database.db");
    mydb_project = QSqlDatabase::addDatabase("QSQLITE", "projet_info_databse");
    mydb_project.setDatabaseName("C:/Users/amir_1/Desktop/AP_Project/Server/project_database.db");

    if (!mydb_project.open()) {
        qDebug() << "Error opening project database:" << mydb_project.lastError().text();
    } else {
        qDebug() << "Project database is open";
    }

    //for database task
    QFile::copy(":/data/task_database.db", "task_database.db");
    mydb_task = QSqlDatabase::addDatabase("QSQLITE", "task_info_database");
    mydb_task.setDatabaseName("C:/Users/amir_1/Desktop/AP_Project/Server/task_database.db");

    if (!mydb_task.open()) {
        qDebug() << "Error opening task database:" << mydb_task.lastError().text();
    } else {
        qDebug() << "Task database is open";
    }


    //for database comment
    QFile::copy(":/data/comment_database.db", "comment_database.db");

    mydb_comment = QSqlDatabase::addDatabase("QSQLITE", "comment_info_database");
    mydb_comment.setDatabaseName("C:/Users/amir_1/Desktop/AP_Project/Server/comment_database.db");

    if (!mydb_comment.open()) {
        qDebug() << "Error opening comment database:" << mydb_comment.lastError().text();
    } else {
        qDebug() << "Comment database is open";
    }
}

void myServer::choose_funtion(QString &instruction_from_socket)
{
    QStringList fields= instruction_from_socket.split("*");

    qDebug() << "instruction is : "<< "["<<instruction_from_socket<<"]";

    QString main_instruction = fields[0];

    if(main_instruction == "cheack_pass")
    {
        check_for_pass_word(fields[1],fields[2]);
        //feedback should be handled in the actual function
    }

    if(main_instruction == "add_person"){
        add_person_to_data_base(instruction_from_socket);
        //should be handled acordingly
    }
    if(main_instruction == "get_user_inf"){
        get_user_info(fields[1]);
    }

    if(main_instruction == "change_user_pass"){
        chnage_user_pass(fields[1],fields[2]);
    }

    if(main_instruction == "get_organizations"){
        organizations_of_person(fields[1]);
    }
    if(main_instruction == "get_teams"){
        teams_of_person(fields[1]);
    }
    if(main_instruction == "get_project"){
        projects_of_person(fields[1]);
    }

    if(main_instruction == "update_person_all_at_once"){
        if(fields[2] != ""){
            change_user_personal_name_1(fields[1],fields[2]);
        }
        if(fields[3] !=""){
            change_user_email(fields[1],fields[3]);
        }
        if(fields[4] != ""){
            chnage_user_pass(fields[1],fields[4]);
        }
    }

    if(main_instruction == "add_to_personal_project"){
        add_project_to_person(fields[1],fields[2]);
        add_project_to_data_base(instruction_from_socket);
        changing_person_of_project(fields[2],fields[1]);
    }
    if(main_instruction == "add_to_organizations"){
        add_organizations_to_person(fields[2],fields[1]);
        add_organization_to_data_base(instruction_from_socket);
    }

    if(main_instruction == "get_teams_of_organization"){
        get_team_of_organization(fields[1]);
    }
    if(main_instruction == "get_projects_of_organization"){
        get_projects_of_organization(fields[1]);
    }
    if(main_instruction == "get_members_of_team"){
        getting_persons_of_team(fields[1]);
    }
    if(main_instruction == "get_projects_of_team"){
        getting_projects_of_team(fields[1]);
    }
    if(main_instruction == "delete_team_of_member"){
        remove_team_from_person(fields[1],fields[2]);
        removing_person_from_team(fields[2],fields[1]);
    }
    if(main_instruction == "search_for_projects")
    {
        search_for_projects(fields[1]);
    }
    if(main_instruction == "add_project_to_team"){
        //team rpoject
        add_project_to_team(fields[1],fields[2]);
        add_team_to_project(fields[2],fields[1]);
    }
    if(main_instruction == "change_team_name"){
        change_team_name_in_all_organizations(fields[1],fields[2]);
        change_team_name_in_all_person(fields[1],fields[2]);
        change_team_name_in_all_projects(fields[1],fields[2]);
        change_name_of_team(fields[1],fields[2]);
    }
    if(main_instruction == "add_person_to_team"){
        //team person
        add_person_to_team(fields[1],fields[2]);
        add_team_to_person(fields[2],fields[1]);
    }
    if(main_instruction == "search_for_person"){
        search_for_persons(fields[1]);
    }
    if(main_instruction == "remove_member_from_team"){
        //team person
        remove_team_from_person(fields[2],fields[1]);
        removing_person_from_team(fields[1],fields[2]);
    }
    if(main_instruction == "change_admin"){
        //    QString instruction = "change_admin*"+CurrentTeamName+"*"+CurrentUserName+"*"+new_admin;
        if(check_if_person_is_admin_of_team(fields[1],fields[2]) == "true"){
            change_admin_of_the_team(fields[1],fields[3]);

        }else{
            QString feed ="access denied";
            writing_feed_back(feed);
            on_sendFileBTN_clicked();
        }
    }

    if(main_instruction == "add_new_team_to_organization"){
        //org team
        adding_teams_to_organization(fields[1],fields[2]);

    }
    if(main_instruction =="change_name_of_organization"){
        //org old // org new;
        chnage_name_of_organization(fields[1],fields[2]);
        change_organization_name_in_all_person(fields[1],fields[2]);
    }
    if(main_instruction=="get_members_of_organization"){
        get_person_of_organization(fields[1]);
    }
    if(main_instruction == "search_for_members"){
        search_for_persons(fields[1]);
    }
    if(main_instruction == "add_person_to_organization"){
        //org person
        add_organizations_to_person(fields[2],fields[1]);
        adding_person_to_organization(fields[1],fields[2]);
    }
    if(main_instruction == "remove_member_from_organization"){
        //org member
        remove_organization_from_person(fields[2],fields[1]);
        removing_person_from_organization(fields[1],fields[2]);
    }
    if(main_instruction == "change_organization_owner"){
        //QString instruvtion = "change_organization_owner*"+CurrentOrganizationName+"*"+CurrentUserName+"*"+organization_new_owner;
        if(check_if_user_name_is_the_owner_of_org(fields[2],fields[1]) == "true"){
            qDebug() << "u have access";
            chnage_owner_of_organization(fields[1],fields[3]);
        }
        else{
            QString feed = "access denied";
            writing_feed_back(feed);
            on_sendFileBTN_clicked();
        }
    }
    if(main_instruction == "get_organizations_owed"){
        get_organization_of_person_as_owner(fields[1]);
    }
    if(main_instruction == "get_team_admin"){
        get_teams_of_person_as_admin(fields[1]);
    }
    if(main_instruction =="delete_organization_of_member"){
        //user org
        remove_organization_from_person(fields[1],fields[2]);
        removing_person_from_organization(fields[2],fields[1]);
    }
    if(main_instruction == "add_new_project_to_team"){
        //QString instruction ="add_new_project_to_team*"+CurrentTeamName+"*"+new_project_for_team;
        QString projec_to_add = "add*id*"+fields[2]+"*team";
        add_project_to_data_base(projec_to_add);
        add_project_to_team(fields[1],fields[2]);
        add_team_to_project(fields[2],fields[1]);
    }
    else{
        qDebug() << "invalid";
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
    QString fileSize = fileName.split('.')[1];
    QString fileExt = HeaderData.split(',')[1].split(':')[1];

    DataBuffer = DataBuffer.mid(128);

    qDebug() <<"data buffer is : " <<DataBuffer;

    QString saveFilePath = QCoreApplication::applicationDirPath() + "/" + fileName;

    QFile file(saveFilePath);
    if (file.open(QIODevice::WriteOnly))
    {
        file.write(DataBuffer);
        file.close();
    }

    QFile file_1(saveFilePath);
    QString instructon = "";
    // Open the file in ReadOnly mode
    if (file_1.open(QIODevice::ReadOnly | QIODevice::Text)) {
        // Create a QTextStream to read from the file
        QTextStream in(&file_1);

        // Read data from the file
        while (!in.atEnd()) {
            QString line = in.readLine();
            instructon+=line;
        }

        // Close the file
        file_1.close();

        qDebug() << "Data has been read from the file.";
    } else {
        // Handle the case where the file cannot be opened
        qDebug() << "Error opening the file for reading.";
    }
    qDebug() << instructon;
    reading_instructions_from_sokcet(instructon);
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
    connect(socket, &QTcpSocket::readyRead, this, &myServer::readSocket);
    connect(socket, &QTcpSocket::disconnected, this, &myServer::discardsocket);
    ui->textEditMasages->append("Client is connected : socket : " + QString::number(socket->socketDescriptor()));
    ui->clientListCombo->addItem(QString::number(socket->socketDescriptor()));
}



void myServer::on_sendFileBTN_clicked()
{
    QString filePath = QCoreApplication::applicationDirPath() + '/' + "feedBack.txt";

    QString receiverId = ui->clientListCombo->currentText();
    foreach (QTcpSocket* sockettemp, clientList)
    {
        if (sockettemp->socketDescriptor() == receiverId.toLongLong())
        {
            sendFile(sockettemp,filePath);
        }
    }
}

void myServer::writing_feed_back(QString &feed_back)
{

    QString filePath = QCoreApplication::applicationDirPath() + '/' + "feedBack.txt";

    QFile file(filePath);

    // Open the file in WriteOnly mode
    if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        // Create a QTextStream to write to the file
        QTextStream out(&file);

        // Write data to the file
        out << feed_back ;

        file.close();

        qDebug() << "feedback has been written to the file.";
    } else {
        // Handle the case where the file cannot be opened
        qDebug() << "error opening the file for writing.";
    }

}

void myServer::reading_instructions_from_sokcet(QString& instruction_on_socket)
{
    //QStringList fields= instruction_on_socket.split("*");
    choose_funtion(instruction_on_socket);
}


void myServer::get_organization_of_person_as_owner(QString &person_name)
{
    // Prepare the SQL query
    QString queryStr = "SELECT organization_name FROM organization_info_database WHERE organization_owner = :person_name";
    QSqlQuery query(mydb_organization);
    query.prepare(queryStr);
    query.bindValue(":person_name", person_name);

    // Execute the query
    if (query.exec())
    {
        // Collect organization names separated by '*'
        QStringList organizationNames;
        while (query.next())
        {
            organizationNames << query.value(0).toString();
        }

        // Create a single string with organization names separated by '*'
        QString owner_organizations_on_socket = organizationNames.join('*')+ "*";
        writing_feed_back(owner_organizations_on_socket);
        on_sendFileBTN_clicked();

        // Print or use the result as needed
        qDebug() << "Organizations owned by " << person_name << ": " << owner_organizations_on_socket;
    }
    else
    {
        qDebug() << "Error executing SQL query: " << query.lastError().text();
    }
}

void myServer::get_teams_of_person_as_admin(QString &person_name)
{

    QString queryStr = "SELECT team_name FROM team_info_database WHERE team_admin = :person_name";
    QSqlQuery query(mydb_team);
    query.prepare(queryStr);
    query.bindValue(":person_name", person_name);

    // Execute the query
    if (query.exec())
    {
        // Collect organization names separated by '*'
        QStringList teamNames;
        while (query.next())
        {
            teamNames << query.value(0).toString();
        }
        // Create a single string with organization names separated by '*'
        QString admin_teams_on_socket = teamNames.join('*') + "*";
        writing_feed_back(admin_teams_on_socket);
        on_sendFileBTN_clicked();

        // Print or use the result as needed
        qDebug() << "Organizations owned by " << person_name << ": " << admin_teams_on_socket;
    }
    else
    {
        qDebug() << "Error executing SQL query: " << query.lastError().text();
    }

}

QString myServer::check_if_person_is_admin_of_team(QString &team_name, QString &person_name)
{
    QString team_info = getting_info_of_team(team_name);
    QStringList info = team_info.split("*");
    QString admin = info[2];
    if(admin == person_name){
        QString feed = "true";
        return feed;
    }
    else{
        QString feed = "false";
        return feed;
    }

}




void myServer::search_for_persons(QString &person_search)
{
    qDebug() << "we are in seaerch for perosn";
    QSqlQuery query(mydb_person);
    query.prepare("SELECT * FROM person_info_database WHERE username LIKE :search");
    query.bindValue(":search", "%" + person_search + "%");

    // Execute the query
    if (query.exec())
    {
        // Initialize a QString to store the concatenated project names
        QString foundProjects;

        // Process the results, concatenate project names with a comma
        while (query.next())
        {
            QString projectName = query.value("username").toString();
            foundProjects += projectName + "*";
        }

        // Remove the trailing comma and space
        //        foundProjects = foundProjects.left(foundProjects.length() - 2);

        // Print the concatenated project names
        qDebug() << "Found persons: " << foundProjects;
        writing_feed_back(foundProjects);
        on_sendFileBTN_clicked();
    }
    else
    {
        QString feed= "";
        writing_feed_back(feed);
        on_sendFileBTN_clicked();
        // Handle query execution error
        qDebug() << "Error executing query: " << query.lastError().text();
    }

}

void myServer::change_organization_name_in_all_person(QString &organization_old_name, QString &organization_new_name)
{
    QSqlQuery selectQuery(mydb_person);

    selectQuery.prepare("SELECT * FROM person_info_database WHERE organizations LIKE :old_organization");
    selectQuery.bindValue(":old_organization", "%" + organization_old_name + "%");

    if (selectQuery.exec()) {
        while (selectQuery.next()) {
            QString list_of_organizations = selectQuery.value("organizations").toString();
            QStringList existingOrganizations = list_of_organizations.split(",");

            if (existingOrganizations.contains(organization_old_name)) {
                // Replace old organization name with new one
                for (int i = 0; i < existingOrganizations.size(); ++i) {
                    if (existingOrganizations.at(i) == organization_old_name) {
                        existingOrganizations.replace(i, organization_new_name);
                        break;
                    }
                }

                QString updated_organizations = existingOrganizations.join(",");
                QSqlQuery updateQuery(mydb_person);
                updateQuery.prepare("UPDATE person_info_database SET organizations = :new_organizations WHERE person_id = :person_id");
                updateQuery.bindValue(":new_organizations", updated_organizations);
                updateQuery.bindValue(":person_id", selectQuery.value("person_id").toString());

                if (updateQuery.exec()) {
                    qDebug() << "Row updated successfully for person_id:" << selectQuery.value("person_id").toString();
                    // Feedback for updating the row
                } else {
                    qDebug() << "Failed to update row for person_id:" << selectQuery.value("person_id").toString() << updateQuery.lastError();
                    // Fail
                }
            }
        }
    } else {
        qDebug() << "Error in selecting records:" << selectQuery.lastError();
        // Feedback for error in selecting records
    }
}

void myServer::change_team_name_in_all_person(QString &team_old_name, QString &team_new_name)
{
    QSqlQuery selectQuery(mydb_person);
    selectQuery.prepare("SELECT * FROM person_info_database WHERE teams LIKE :old_team");
    selectQuery.bindValue(":old_team", "%" + team_old_name + "%");

    if (selectQuery.exec()) {
        while (selectQuery.next()) {
            QString list_of_teams = selectQuery.value("teams").toString();
            QStringList existingTeams = list_of_teams.split(",");

            if (existingTeams.contains(team_old_name)) {
                // Replace old team name with new one
                for (int i = 0; i < existingTeams.size(); ++i) {
                    if (existingTeams.at(i) == team_old_name) {
                        existingTeams.replace(i, team_new_name);
                        break;
                    }
                }

                QString updated_teams = existingTeams.join(",");
                QSqlQuery updateQuery(mydb_person);
                updateQuery.prepare("UPDATE person_info_database SET teams = :new_teams WHERE person_id = :person_id");
                updateQuery.bindValue(":new_teams", updated_teams);
                updateQuery.bindValue(":person_id", selectQuery.value("person_id").toString());

                if (updateQuery.exec()) {
                    qDebug() << "Row updated successfully for person_id:" << selectQuery.value("person_id").toString();
                    // Feedback for updating the row
                } else {
                    qDebug() << "Failed to update row for person_id:" << selectQuery.value("person_id").toString() << updateQuery.lastError();
                    // Fail
                }
            }
        }
    } else {
        qDebug() << "Error in selecting records:" << selectQuery.lastError();
        // Feedback for error in selecting records
    }
}

void myServer::change_task_name_in_person(QString &task_old_name, QString &task_new_name)
{
    QSqlQuery selectQuery(mydb_person);
    selectQuery.prepare("SELECT * FROM person_info_database WHERE tasks LIKE :old_task");
    selectQuery.bindValue(":old_task", "%" + task_old_name + "%");

    if (selectQuery.exec()) {
        while (selectQuery.next()) {
            QString list_of_tasks = selectQuery.value("tasks").toString();
            QStringList existingTasks = list_of_tasks.split(",");

            if (existingTasks.contains(task_old_name)) {
                // Replace old task name with new one
                for (int i = 0; i < existingTasks.size(); ++i) {
                    if (existingTasks.at(i) == task_old_name) {
                        existingTasks.replace(i, task_new_name);
                        break;
                    }
                }

                QString updated_tasks = existingTasks.join(",");
                QSqlQuery updateQuery(mydb_person);
                updateQuery.prepare("UPDATE person_info_database SET tasks = :new_tasks WHERE person_id = :person_id");
                updateQuery.bindValue(":new_tasks", updated_tasks);
                updateQuery.bindValue(":person_id", selectQuery.value("person_id").toString());

                if (updateQuery.exec()) {
                    qDebug() << "Row updated successfully for person_id:" << selectQuery.value("person_id").toString();
                    // Feedback for updating the row
                } else {
                    qDebug() << "Failed to update row for person_id:" << selectQuery.value("person_id").toString() << updateQuery.lastError();
                    // Fail
                }
            }
        }
    } else {
        qDebug() << "Error in selecting records:" << selectQuery.lastError();
        // Feedback for error in selecting records
    }
}

void myServer::change_project_name_in_all_person(QString &project_old_name, QString &project_new_name)
{
    QSqlQuery selectQuery(mydb_person);
    selectQuery.prepare("SELECT * FROM person_info_database WHERE projects LIKE :old_project");
    selectQuery.bindValue(":old_project", "%" + project_old_name + "%");

    if (selectQuery.exec()) {
        while (selectQuery.next()) {
            QString list_of_projects = selectQuery.value("projects").toString();
            QStringList existingProjects = list_of_projects.split(",");

            if (existingProjects.contains(project_old_name)) {
                // Replace old project name with new one
                for (int i = 0; i < existingProjects.size(); ++i) {
                    if (existingProjects.at(i) == project_old_name) {
                        existingProjects.replace(i, project_new_name);
                        break;
                    }
                }

                QString updated_projects = existingProjects.join(",");
                QSqlQuery updateQuery(mydb_person);
                updateQuery.prepare("UPDATE person_info_database SET projects = :new_projects WHERE person_id = :person_id");
                updateQuery.bindValue(":new_projects", updated_projects);
                updateQuery.bindValue(":person_id", selectQuery.value("person_id").toString());

                if (updateQuery.exec()) {
                    qDebug() << "Row updated successfully for person_id:" << selectQuery.value("person_id").toString();
                    // Feedback for updating the row
                } else {
                    qDebug() << "Failed to update row for person_id:" << selectQuery.value("person_id").toString() << updateQuery.lastError();
                    // Fail
                }
            }
        }
    } else {
        qDebug() << "Error in selecting records:" << selectQuery.lastError();
        // Feedback for error in selecting records
    }
}

QString myServer::check_if_user_name_is_the_owner_of_org(QString &person_name, QString &organization_name)
{
    QString org_info =  getting_info_of_organizatios(organization_name);
    QStringList info = org_info.split("*");
    QString owner = info[2];
    if(person_name == owner){
        QString x = "true";
        return x;
        qDebug() << "true";
    }
    else{
        QString y = "false";
        return y;
        qDebug() <<"false";
    }
}

void myServer::change_user_info_all_once(QString &changed_data_from_socket)
{
    //chage_all_info*user_name*personl_name*new_pass*email
    QStringList data = changed_data_from_socket.split("*");
    change_user_email(data[1],data[2]);
    chnage_user_pass(data[1],data[3]);
    change_user_personal_name_1(data[1],data[4]);

}

//----------------------------

void myServer::change_user_personal_name_1(QString &name_in_data_base, QString &new_name)
{
    QString user_name_in_data_base = name_in_data_base;

    //updating personal_name

    QSqlQuery updateQuery(mydb_person);
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

    qDebug() << "instruction in the add_person_to_data_base is: " <<user_data;
    QString data_recieved_by_socket_to_add = user_data;
    QStringList fields = data_recieved_by_socket_to_add.split("*");
    QString user_name_to_database = fields[2];

    // Check if the user already exists
    QSqlQuery checkQuery(mydb_person);
    checkQuery.prepare("SELECT * FROM person_info_database WHERE username = :user_name_given");
    checkQuery.bindValue(":user_name_given", user_name_to_database);

    qDebug() << "Number of elements in fields: " << fields.size();

    if (checkQuery.exec() && checkQuery.next()) {
        qDebug() << "User with the same username already exists in the database.";
        QString feed_b = "there is another person with the same username";
        writing_feed_back(feed_b);
    } else
    {
        // User doesn't exist, add them to the database
        QSqlQuery insertQuery(mydb_person);

        insertQuery.prepare("INSERT INTO person_info_database (username, password, personal_name, email, fav_animal, fav_color, fav_city) VALUES ( ?, ?, ?, ?, ?, ?, ?)");

        for (int i = 1; i <= 12; ++i) {
            qDebug() << "Bind Value " << i << ": " << fields.value(i);
        }

        // Bind values for the insertion
        //insertQuery.addBindValue(fields[1]); //person_id
        insertQuery.addBindValue(fields[2]); //user_name
        insertQuery.addBindValue(fields[3]); //pass
        insertQuery.addBindValue(fields[4]); //personal name
        insertQuery.addBindValue(fields[5]); //email
        insertQuery.addBindValue(fields[6]); //fav anmimal
        insertQuery.addBindValue(fields[7]);  //fav color
        insertQuery.addBindValue(fields[8]);  //fav city


        // insertQuery.addBindValue("default_org");
        // insertQuery.addBindValue("default_teams");
        // insertQuery.addBindValue("default_projects");
        // insertQuery.addBindValue("default_tasks");

        // Execute the insertion query
        if (insertQuery.exec()) {
            qDebug() << "User added successfully.";
            QString feed_b = "true_person_add";
            writing_feed_back(feed_b);
            on_sendFileBTN_clicked();
            // Sending feedback through socket that person added to the database
        } else {
            qDebug() << "Could not add user." <<insertQuery.lastError();

            QString feed_b = "could not add person";
            writing_feed_back(feed_b);
            on_sendFileBTN_clicked();
        }
    }
}


//----------------------

//------------------------
void myServer::change_user_email(QString &name_in_data_base, QString &new_email_1)
{
    // CREATE TABLE "person_info_database" (
    //     "person_id"	TEXT,
    //     "username"	TEXT,
    //     "password"	TEXT,
    //     "personal_name"	TEXT,
    //     "email"	TEXT,
    //     "fav_animal"	TEXT,
    //     "fav_color"	TEXT,
    //     "fav_city"	TEXT,
    //     "organizations"	TEXT,
    //     "teams"	TEXT,
    //     "projects"	TEXT,
    //     "tasks"	TEXT
    //     )

    QString user_name_in_data_base = name_in_data_base;
    QString new_email  = new_email_1;

    QSqlQuery updateQuery(mydb_person);
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
    QString new_pass = new_pass_1;

    QSqlQuery updateQuery(mydb_person);
    updateQuery.prepare("UPDATE person_info_database SET password = :new_pass WHERE username = :user_name_in_data_base");
    updateQuery.bindValue(":new_pass", new_pass);
    updateQuery.bindValue(":user_name_in_data_base", user_name_in_data_base);

    if (updateQuery.exec()) {
        qDebug() << "pass updated successfully.";
        QString x ="true";
        //writing_feed_back(x);
        // Feedback should be handled here
    } else {
        qDebug() << "Could not update pass." << updateQuery.lastError();
        // Feedback should be handled here
        QString x ="coudn't update pass";
        //writing_feed_back(x);
    }
}
//----------------------------------
QString myServer::get_user_info(QString& name_in_data_base)
{
    QString user_in_data_base = name_in_data_base;
    QString user_info;

    QSqlQuery selectQuery(mydb_person);
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
        writing_feed_back(user_info);
        on_sendFileBTN_clicked();
        return user_info;

    } else {
        qDebug() << "User not found or an error occurred." << selectQuery.lastError();
        QString x = "false_user_info";
        writing_feed_back(x);
        on_sendFileBTN_clicked();
    }
}

//----------------------------

// bool myServer::check_for_pass_word(QString &name_in_data_base, QString &input_password)
// {
//     QString user_pass = input_password;

//     QSqlQuery selectQuery;
//     selectQuery.prepare("SELECT * FROM person_info_database WHERE username = :name_in_data_base");
//     selectQuery.bindValue(":name_in_data_base", name_in_data_base);
//     if (selectQuery.exec() && selectQuery.next()) {
//         QString password = selectQuery.value("password").toString();
//         if(password == user_pass){
//             qDebug() << "correct\n";
//             //sending feedbacks
//             return true;

//         }
//         else{
//             qDebug() << "not correct\n";
//             //sending feedbacks
//             return false;
//         }
//     }
//     else{
//         qDebug() << "person was not found\n";
//         return false;
//         //sending feedbacks
//     }
// }

bool myServer::check_for_pass_word(QString &name_in_data_base,QString &input_password)
{
    QSqlQuery selectQuery(mydb_person);
    selectQuery.prepare("SELECT password FROM person_info_database WHERE username = :name_in_data_base");
    selectQuery.bindValue(":name_in_data_base", name_in_data_base);

    if (selectQuery.exec() && selectQuery.next()) {
        QString password = selectQuery.value("password").toString();

        if (password == input_password) {
            qDebug() << "Correct password for user: " << name_in_data_base;

            QString feed_back = "Correct_pass";
            writing_feed_back(feed_back);
            on_sendFileBTN_clicked();

            // Sending feedbacks
            return true;
        } else {
            qDebug() << "Incorrect password for user: " << name_in_data_base;

            QString feed_back = "incorrect pass";
            writing_feed_back(feed_back);
            on_sendFileBTN_clicked();
            // Sending feedbacks

            return false;
        }
    } else {
        qDebug() << "User not found: " << name_in_data_base;

        QString feed_back = "user not found";
        writing_feed_back(feed_back);
        on_sendFileBTN_clicked();

        // Sending feedbacks
        return false;
    }
}

//----------------------
//adding organization
void myServer::add_organizations_to_person(QString &name_in_data_base, QString &organizations_name)
{
    QString user_name_in_data_base = name_in_data_base;  // Set the actual username
    QString organizations_to_add = organizations_name;

    QSqlQuery selectQuery(mydb_person);
    selectQuery.prepare("SELECT * FROM person_info_database WHERE username = :user_in_data_base");
    selectQuery.bindValue(":user_in_data_base", user_name_in_data_base);

    if (selectQuery.exec() && selectQuery.next()) {
        QString list_of_organizations = selectQuery.value("organizations").toString();

        QStringList existingOrganizations = list_of_organizations.split(",");

        if (!existingOrganizations.contains(organizations_to_add)) {
            list_of_organizations += "," + organizations_to_add;

            QSqlQuery updateQuery(mydb_person);
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
    qDebug() << "we are in the add team to person";
    QString user_name_in_data_base = name_in_data_base;  // Set the actual username
    QString team_to_add = team_name;

    QSqlQuery selectQuery(mydb_person);
    selectQuery.prepare("SELECT * FROM person_info_database WHERE username = :user_in_data_base");
    selectQuery.bindValue(":user_in_data_base", user_name_in_data_base);

    if (selectQuery.exec() && selectQuery.next()) {
        QString list_of_team = selectQuery.value("teams").toString();

        QStringList existingteam = list_of_team.split(",");

        if (!existingteam.contains(team_to_add)) {
            list_of_team += "," + team_to_add;

            QSqlQuery updateQuery(mydb_person);
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

    QSqlQuery selectQuery(mydb_person);
    selectQuery.prepare("SELECT * FROM person_info_database WHERE username = :user_in_data_base");
    selectQuery.bindValue(":user_in_data_base", user_name_in_data_base);

    if (selectQuery.exec() && selectQuery.next()) {
        QString list_of_project = selectQuery.value("projects").toString();

        QStringList existingProject = list_of_project.split(",");

        if (!existingProject.contains(project_to_add)) {
            list_of_project += "," + project_to_add;

            QSqlQuery updateQuery(mydb_person);
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

    QSqlQuery selectQuery(mydb_person);
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
            QSqlQuery updateQuery(mydb_person);
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
            //should handle the feedback


        }
    } else {
        qDebug() << "User not found or an error occurred." << selectQuery.lastError();
        //should handle the feedback

    }

}

//-------------------------------------
void myServer::remove_team_from_person(QString &name_in_data_base, QString &team_name)
{
    QString user_name_in_data_base = name_in_data_base;  // Set the actual username
    QString remove_name_team = team_name;  // Set the team to remove

    QSqlQuery selectQuery(mydb_person);
    selectQuery.prepare("SELECT * FROM person_info_database WHERE username = :user_in_data_base");
    selectQuery.bindValue(":user_in_data_base", name_in_data_base);

    if (selectQuery.exec() && selectQuery.next()) {
        QString list_of_team = selectQuery.value("teams").toString();

        QStringList existingTeam = list_of_team.split(",");

        if (existingTeam.contains(remove_name_team)) {
            existingTeam.removeAll(remove_name_team);

            QString newListOfteams = existingTeam.join(",");

            QSqlQuery updateQuery(mydb_person);
            updateQuery.prepare("UPDATE person_info_database SET teams = :new_team WHERE username = :user_in_data_base");
            updateQuery.bindValue(":new_team", newListOfteams);
            updateQuery.bindValue(":user_in_data_base", name_in_data_base);

            if (updateQuery.exec()) {
                qDebug() << "team removed successfully.";
                //handeling socket

            } else {
                qDebug() << "Failed to update row." << updateQuery.lastError();
                //handeling socket
            }
        } else {
            qDebug() << "team not found in the list.";
            //handleing socket
        }
    } else {
        qDebug() << "User not found or an error occurred." << selectQuery.lastError();
        //feed back
    }
}

//--------------------
void myServer::remove_project_from_person(QString &name_in_data_base_1, QString &project_name)
{
    QString name_in_data_base = name_in_data_base_1;  // Set the actual username
    QString remove_name_project = project_name;  // Set the organization to remove

    QSqlQuery selectQuery;
    selectQuery.prepare("SELECT * FROM person_info_database WHERE username = :user_in_data_base");
    selectQuery.bindValue(":user_in_data_base", name_in_data_base);

    if (selectQuery.exec() && selectQuery.next()) {
        QString list_of_project = selectQuery.value("projects").toString();

        QStringList existingProject = list_of_project.split(",");

        if (existingProject.contains(remove_name_project)) {
            existingProject.removeAll(remove_name_project);

            QString newListOfproject = existingProject.join(",");

            QSqlQuery updateQuery;
            updateQuery.prepare("UPDATE person_info_database SET projects = :new_project WHERE username = :user_in_data_base");
            updateQuery.bindValue(":new_project", newListOfproject);
            updateQuery.bindValue(":user_in_data_base", name_in_data_base);

            if (updateQuery.exec()) {
                qDebug() << "project removed successfully.";
                //feed back

            } else {
                qDebug() << "Failed to update row." << updateQuery.lastError();
                //feed back

            }
        } else {
            qDebug() << "project not found in the list.";
                //feed back

        }
    } else {
        qDebug() << "User not found or an error occurred." << selectQuery.lastError();
            //feed back

    }
}
//---------------------------------------
void myServer::remove_task_from_person(QString& name_in_data_base,QString& task_name){
    // QString name_in_data_base = name_in_data_base;  // Set the actual username
    QString remove_name_task = task_name;  // Set the organization to remove

    QSqlQuery selectQuery;
    selectQuery.prepare("SELECT * FROM person_info_database WHERE username = :user_in_data_base");
    selectQuery.bindValue(":user_in_data_base", name_in_data_base);

    if (selectQuery.exec() && selectQuery.next()) {
        QString list_of_tasks = selectQuery.value("tasks").toString();

        // Split the existing organizations
        QStringList existingTasks = list_of_tasks.split(",");

        // Check if the organization to remove exists
        if (existingTasks.contains(remove_name_task)) {
            // Remove the organization
            existingTasks.removeAll(remove_name_task);

            // Join the organizations back into a string
            QString newListOftasks = existingTasks.join(",");

            // Update the row with the new list of organizations
            QSqlQuery updateQuery;
            updateQuery.prepare("UPDATE person_info_database SET tasks = :new_task WHERE username = :user_in_data_base");
            updateQuery.bindValue(":new_task", newListOftasks);
            updateQuery.bindValue(":user_in_data_base", name_in_data_base);

            if (updateQuery.exec()) {
                qDebug() << "task removed successfully.";
                //should handle the feedback


            } else {
                qDebug() << "Failed to update row." << updateQuery.lastError();
                //should hande the feedback



            }
        } else {
            qDebug() << "task not found in the list.";
        }
    } else {
        qDebug() << "User not found or an error occurred." << selectQuery.lastError();
    }
}
//-----------------------------------
QVector<QString> myServer::teams_of_person(QString &name_in_data_base)
{
    //QString name_in_data_base = "";  // Set the actual username

    QSqlQuery selectQuery(mydb_person);
    selectQuery.prepare("SELECT * FROM person_info_database WHERE username = :user_in_data_base");
    selectQuery.bindValue(":user_in_data_base", name_in_data_base);

    if (selectQuery.exec() && selectQuery.next()) {
        QString teamsString = selectQuery.value("teams").toString();

        // Split the teams using the comma delimiter
        QStringList teamsList = teamsString.split(",");

        // Convert QStringList to QVector<QString>
        QVector<QString> teamsVector = teamsList.toVector();
        QString teams_to_send_on_socket;
        // Use teamsVector as needed
        for(int i = 0;i<teamsVector.size();i++){
            qDebug() <<teamsVector[i];
            teams_to_send_on_socket.append(teamsVector[i]);
            teams_to_send_on_socket.append("*");
        }

        writing_feed_back(teams_to_send_on_socket);
        on_sendFileBTN_clicked();

        //qDebug() << "Teams Vector: " << teamsVector;
        return teamsVector;

    } else {
        qDebug() << "User not found or an error occurred." << selectQuery.lastError();
        QVector<QString> err ={""};
        return err;
    }
}

//----------------------------

QVector<QString> myServer::organizations_of_person(QString &name_in_data_base)
{
    QSqlQuery selectQuery(mydb_person);
    selectQuery.prepare("SELECT * FROM person_info_database WHERE username = :user_in_data_base");
    selectQuery.bindValue(":user_in_data_base", name_in_data_base);

    if (selectQuery.exec() && selectQuery.next()) {
        QString organizationString = selectQuery.value("organizations").toString();

        // Split the teams using the comma delimiter
        QStringList organizationList = organizationString.split(",");

        // Convert QStringList to QVector<QString>
        QVector<QString> organizationVector = organizationList.toVector();

        // Use teamsVector as needed
        QString organizations_to_send = "";
        for(int i = 0;i<organizationVector.size();i++){
            qDebug() <<organizationVector[i];
            organizations_to_send.append(organizationVector[i]);
            organizations_to_send.append("*");
        }

        qDebug() << "organization Vector: " << organizationVector;

        writing_feed_back(organizations_to_send);
        on_sendFileBTN_clicked();

        return organizationVector;
        //handeling

    } else {
        qDebug() << "User not found or an error occurred." << selectQuery.lastError();
        QVector<QString> err = {""};
        return err;
    }
}


//------------------------------
QVector<QString> myServer::task_of_person(QString &name_in_data_base)
{

    QSqlQuery selectQuery;
    selectQuery.prepare("SELECT * FROM person_info_database WHERE username = :user_in_data_base");
    selectQuery.bindValue(":user_in_data_base", name_in_data_base);

    if (selectQuery.exec() && selectQuery.next()) {
        QString taskString = selectQuery.value("tasks").toString();

        // Split the teams using the comma delimiter
        QStringList taskList = taskString.split(",");

        // Convert QStringList to QVector<QString>
        QVector<QString> taskVector = taskList.toVector();

        // Use task as needed
        for(int i = 0;i<taskVector.size();i++){
            qDebug() <<taskVector[i];
        }

        qDebug() << "task  Vector: " << taskVector;

        return taskVector;

    } else {
        qDebug() << "User not found or an error occurred." << selectQuery.lastError();
        QVector<QString> err;
        return err;
    }

}

//--------------------------------------
QVector<QString> myServer::projects_of_person(QString &name_in_data_base)
{

    QSqlQuery selectQuery(mydb_person);
    selectQuery.prepare("SELECT * FROM person_info_database WHERE username = :user_in_data_base");
    selectQuery.bindValue(":user_in_data_base", name_in_data_base);

    if (selectQuery.exec() && selectQuery.next()) {
        QString projectString = selectQuery.value("projects").toString();

        // Split the teams using the comma delimiter
        QStringList projectList = projectString.split(",");

        // Convert QStringList to QVector<QString>
        QVector<QString> projectVector = projectList.toVector();
        QString project_send_to_socket;
        // Use teamsVector as needed
        for(int i = 0;i<projectVector.size();i++){
            qDebug() <<projectVector[i];
            project_send_to_socket.append(projectVector[i]);
            project_send_to_socket.append("*");
        }
        writing_feed_back(project_send_to_socket);
        on_sendFileBTN_clicked();

        qDebug() << "project  Vector: " << projectVector;
        return projectVector;

    } else {
        qDebug() << "User not found or an error occurred." << selectQuery.lastError();
        QVector<QString> err = {""};
        return err;
    }
}

void myServer::change_team_name_in_all_organizations(QString &old_team_name, QString &new_team_name)
{
    QSqlQuery selectQuery(mydb_organization);
    selectQuery.prepare("SELECT * FROM organization_info_database WHERE organization_team LIKE :old_team");
    selectQuery.bindValue(":old_team", "%" + old_team_name + "%");

    if (selectQuery.exec()) {
        while (selectQuery.next()) {
            QString list_of_teams = selectQuery.value("organization_team").toString();
            QStringList existingTeams = list_of_teams.split(",");

            if (existingTeams.contains(old_team_name)) {
                // Replace old team name with new one
                for (int i = 0; i < existingTeams.size(); ++i) {
                    if (existingTeams.at(i) == old_team_name) {
                        existingTeams.replace(i, new_team_name);
                        break;
                    }
                }

                QString updated_teams = existingTeams.join(",");
                QSqlQuery updateQuery(mydb_organization);
                updateQuery.prepare("UPDATE organization_info_database SET organization_team = :new_teams WHERE organization_id = :organization_id");
                updateQuery.bindValue(":new_teams", updated_teams);
                updateQuery.bindValue(":organization_id", selectQuery.value("organization_id").toString());

                if (updateQuery.exec()) {
                    qDebug() << "Row updated successfully for organization_id:" << selectQuery.value("organization_id").toString();
                    // Feedback for updating the row
                } else {
                    qDebug() << "Failed to update row for organization_id:" << selectQuery.value("organization_id").toString() << updateQuery.lastError();
                    // Fail
                }
            }
        }
    } else {
        qDebug() << "Error in selecting records:" << selectQuery.lastError();
        // Feedback for error in selecting records
    }
}

void myServer::change_organization_info_all_at_once(QString &changed_data_from_socket)
{
    //dont need it yet!!
}

//---------------------------------

//organization functions


void myServer::add_organization_to_data_base(QString &organization_data)
{
    QString data_recieved_by_socket_to_add_to_organization = organization_data;
    QStringList fields = data_recieved_by_socket_to_add_to_organization.split("*");
    QString id_organization_to_database = fields[1];

    QSqlQuery checkQuery(mydb_organization);

    checkQuery.prepare("SELECT * FROM organization_info_database WHERE organization_name = :id_organization_to_database");
    checkQuery.bindValue(":id_organization_to_database", id_organization_to_database);

    if (checkQuery.exec() && checkQuery.next()) {
        qDebug() << "organization with the same id already exists in the database.";

    }

    //data base structure
    // CREATE TABLE "organization_info_database" (
    //     "organization_id"	TEXT,
    //     "organization_name"	TEXT,
    //     "organization_owner"	TEXT,
    //     "organization_team"	TEXT,
    //     "organization_person"	TEXT
    //     )

    else {
        QSqlQuery insertQuery(mydb_organization);

        insertQuery.prepare("INSERT INTO organization_info_database (organization_name, organization_owner) VALUES (?, ?)");

        // Bind values for the insertion
        insertQuery.addBindValue(fields[1]); //organization_name
        insertQuery.addBindValue(fields[2]); //organization_owner

        // Execute the insertion query
        if (insertQuery.exec()) {
            qDebug() << "organization added successfully.";
            // Sending feedback through socket that organization added to the database

        }
        else {
            qDebug() << "Could not add organization." <<insertQuery.lastError();
        }
    }

}

//----------------------------
void myServer::chnage_name_of_organization(QString &organization_id, QString &new_name_for_organization)
{

    QString organization_id_in_data_base = organization_id; //it's the old name of the organization
    QString new_name  = new_name_for_organization;

    // CREATE TABLE "organization_info_database" (
    //     "organization_id"	TEXT,
    //     "organization_name"	TEXT,
    //     "organization_owner"	TEXT,
    //     "organization_team"	TEXT,
    //     "organization_person"	TEXT
    //     )

    QSqlQuery checkQuery(mydb_organization);

    checkQuery.prepare("SELECT * FROM organization_info_database WHERE organization_name = :organization_id_in_data_base");
    checkQuery.bindValue(":organization_id_in_data_base", new_name_for_organization);

    if (checkQuery.exec() && checkQuery.next()) {
        qDebug() << "organization with the same id already exists in the database.";
        //should be handeled with socket
    }
    else{
        QSqlQuery updateQuery(mydb_organization);
        updateQuery.prepare("UPDATE organization_info_database SET organization_name = :new_organization_name WHERE organization_name = :organization_id_in_data_base");
        updateQuery.bindValue(":new_organization_name", new_name);
        updateQuery.bindValue(":organization_id_in_data_base", organization_id_in_data_base);




        if (updateQuery.exec()) {
            qDebug() << "organization name updated successfully.";

            // You can add additional logic or feedback here
            //feed back should be handled here


        } else {
            qDebug() << "Could not update organization name." << updateQuery.lastError();
            // You can handle the error or provide feedback here
            //feedback should be handled here

        }
    }

}

//----------------------------
void myServer::chnage_owner_of_organization(QString &organization_id, QString &new_owner_for_organization)
{

    QString organization_id_in_data_base = organization_id;
    QString name_of_new_owner  = new_owner_for_organization;
    QSqlQuery updateQuery(mydb_organization);

    updateQuery.prepare("UPDATE organization_info_database SET organization_owner = :new_organization_owner_name WHERE organization_name = :organization_id_in_data_base");
    updateQuery.bindValue(":new_organization_owner_name", name_of_new_owner);
    updateQuery.bindValue(":organization_id_in_data_base", organization_id_in_data_base);

    if (updateQuery.exec()) {
        qDebug() << "organization owner updated successfully.";

        // You can add additional logic or feedback here
        //feed back should be handled here

    } else {
        qDebug() << "Could not update organization owner." << updateQuery.lastError();

        // You can handle the error or provide feedback here
        //feedback should be handled here
    }
}

//-----------------------------

void myServer::adding_teams_to_organization(QString &organization_id, QString &id_of_team_to_add)
{
    QString organization_id_in_data_base = organization_id;  // Set the actual username
    QString team_to_add = id_of_team_to_add;

    QSqlQuery selectQuery(mydb_organization);
    selectQuery.prepare("SELECT * FROM organization_info_database WHERE organization_name = :organization_id_in_data_base");
    selectQuery.bindValue(":organization_id_in_data_base", organization_id_in_data_base);


    if (selectQuery.exec() && selectQuery.next()) {
        QString list_of_team = selectQuery.value("organization_team").toString();

        QStringList existingteam = list_of_team.split(",");

        if (!existingteam.contains(team_to_add)) {
            list_of_team += "," + team_to_add;

            QSqlQuery updateQuery(mydb_organization);
            updateQuery.prepare("UPDATE organization_info_database SET organization_team = :new_teams WHERE organization_name = :organization_id_in_data_base");
            updateQuery.bindValue(":new_teams", list_of_team);
            updateQuery.bindValue(":organization_id_in_data_base", organization_id_in_data_base);

            if (updateQuery.exec())
            {
                qDebug() << "Row updated successfully.";
                //
            }
            else {
                qDebug() << "Failed to update row." << updateQuery.lastError();
                //should hnadle the feedback
            }
        } else {
            qDebug() << "team already exists in the list.";
            //

        }
    } else {
        qDebug() << "User not found or an error occurred." << selectQuery.lastError();
    }

}
//----------------------------------------------------

void myServer::adding_person_to_organization(QString &organization_id, QString &id_of_person_to_add)
{
    QString organization_id_in_data_base = organization_id;  // Set the actual username
    QString person_to_add = id_of_person_to_add;


    QSqlQuery selectQuery(mydb_organization);

    selectQuery.prepare("SELECT * FROM organization_info_database WHERE organization_name = :organization_id_in_data_base");
    selectQuery.bindValue(":organization_id_in_data_base", organization_id_in_data_base);


    if (selectQuery.exec() && selectQuery.next()) {
        QString list_of_person = selectQuery.value("organization_person").toString();

        QStringList existingperson = list_of_person.split(",");

        if (!existingperson.contains(person_to_add)) {
            list_of_person += "," + person_to_add;

            QSqlQuery updateQuery(mydb_organization);
            updateQuery.prepare("UPDATE organization_info_database SET organization_person = :new_person WHERE organization_name = :organization_id_in_data_base");
            updateQuery.bindValue(":new_person", list_of_person);
            updateQuery.bindValue(":organization_id_in_data_base", organization_id_in_data_base);

            if (updateQuery.exec())
            {
                qDebug() << "Row updated successfully.";
                //should handle the socket
            }
            else {
                qDebug() << "Failed to update row." << updateQuery.lastError();
                //should handle the socket


            }
        } else {
            qDebug() << "person already exists in the list.";

        }

    } else {
        qDebug() << "organization not found or an error occurred." << selectQuery.lastError();
    }
}

void myServer::adding_project_to_organization(QString &organization_id, QString &id_of_project)
{
    QString organization_id_in_data_base = organization_id;  // Set the actual username
    QString project_to_add = id_of_project;


    QSqlQuery selectQuery(mydb_organization);

    selectQuery.prepare("SELECT * FROM organization_info_database WHERE organization_name = :organization_id_in_data_base");
    selectQuery.bindValue(":organization_id_in_data_base", organization_id_in_data_base);


    if (selectQuery.exec() && selectQuery.next()) {
        QString list_of_person = selectQuery.value("organization_project").toString();

        QStringList existingperson = list_of_person.split(",");

        if (!existingperson.contains(project_to_add)) {
            list_of_person += "," + project_to_add;

            QSqlQuery updateQuery(mydb_organization);
            updateQuery.prepare("UPDATE organization_info_database SET organization_project = :new_person WHERE organization_name = :organization_id_in_data_base");
            updateQuery.bindValue(":new_person", list_of_person);
            updateQuery.bindValue(":organization_id_in_data_base", organization_id_in_data_base);

            if (updateQuery.exec())
            {
                qDebug() << "Row updated successfully.";
                //should handle the socket
            }
            else {
                qDebug() << "Failed to update row." << updateQuery.lastError();
                //should handle the socket
            }
        } else {
            qDebug() << "person already exists in the list.";

        }

    } else {
        qDebug() << "organization not found or an error occurred." << selectQuery.lastError();
    }
}

void myServer::removing_project_from_organization(QString &organization_id, QString &id_of_project_to_remove)
{
    QString organization_id_in_data_base  = organization_id;  // Set the actual username
    QString remove_project_from_organization = id_of_project_to_remove;

    QSqlQuery selectQuery(mydb_organization);
    selectQuery.prepare("SELECT * FROM organization_info_database WHERE organization_name= :organization_id_in_data_base");
    selectQuery.bindValue(":organization_id_in_data_base", organization_id_in_data_base);

    if (selectQuery.exec() && selectQuery.next()) {
        QString list_of_teams = selectQuery.value("organization_team").toString();

        // Split the existing organizations
        QStringList existingteams = list_of_teams.split(",");

        // Check if the organization to remove exists
        if (existingteams.contains(remove_project_from_organization)) {
            // Remove the organization
            existingteams.removeAll(remove_project_from_organization);

            // Join the organizations back into a string
            QString newListOfproject = existingteams.join(",");

            // Update the row with the new list of organizations
            QSqlQuery updateQuery(mydb_organization);
            updateQuery.prepare("UPDATE organization_info_database SET organization_project = :new_organization_team WHERE organization_id = :organization_id_in_data_base");
            updateQuery.bindValue(":new_organization_team", newListOfproject);
            updateQuery.bindValue(":organization_id_in_data_base", organization_id_in_data_base);

            if (updateQuery.exec()) {
                qDebug() << "project removed successfully.";
                //should handle feedback

            } else {
                qDebug() << "Failed to update row." << updateQuery.lastError();
                //should handle feedback

            }
        } else {
            qDebug() << "project not found in the list.";
                //should handle feedback

        }
    } else {
        qDebug() << "organization not found or an error occurred." << selectQuery.lastError();
    }
}

//------------------------------
void myServer::removing_team_from_organization(QString &organization_id, QString &cid_of_team_to_remove)
{
    QString organization_id_in_data_base  = organization_id;  // Set the actual username
    QString remove_team_from_organization = cid_of_team_to_remove;

    QSqlQuery selectQuery;
    selectQuery.prepare("SELECT * FROM organization_info_database WHERE organization_id = :organization_id_in_data_base");
    selectQuery.bindValue(":organization_id_in_data_base", organization_id_in_data_base);

    if (selectQuery.exec() && selectQuery.next()) {
        QString list_of_teams = selectQuery.value("organization_team").toString();

        // Split the existing organizations
        QStringList existingteams = list_of_teams.split(",");

        // Check if the organization to remove exists
        if (existingteams.contains(remove_team_from_organization)) {
            // Remove the organization
            existingteams.removeAll(remove_team_from_organization);

            // Join the organizations back into a string
            QString newListOfproject = existingteams.join(",");

            // Update the row with the new list of organizations
            QSqlQuery updateQuery;
            updateQuery.prepare("UPDATE organization_info_database SET organization_team = :new_organization_team WHERE organization_id = :organization_id_in_data_base");
            updateQuery.bindValue(":new_organization_team", newListOfproject);
            updateQuery.bindValue(":organization_id_in_data_base", organization_id_in_data_base);

            if (updateQuery.exec()) {
                qDebug() << "project removed successfully.";
                //should handle feedback

            } else {
                qDebug() << "Failed to update row." << updateQuery.lastError();
                //should handle feedback

            }
        } else {
            qDebug() << "project not found in the list.";
                //should handle feedback

        }
    } else {
        qDebug() << "organization not found or an error occurred." << selectQuery.lastError();
    }
}
//-----------------------
void myServer::removing_person_from_organization(QString& organization_id,QString& id_of_person_to_remove)
{
    QString organization_id_in_data_base = organization_id;  // Set the actual username
    QString remove_person_from_organization = id_of_person_to_remove;

    QSqlQuery selectQuery(mydb_organization);
    selectQuery.prepare("SELECT * FROM organization_info_database WHERE organization_name = :organization_id_in_data_base");
    selectQuery.bindValue(":organization_id_in_data_base", organization_id_in_data_base);

    if (selectQuery.exec() && selectQuery.next()) {
        QString list_of_person = selectQuery.value("organization_person").toString();

        // Split the existing organizations
        QStringList existingperson = list_of_person.split(",");

        // Check if the organization to remove exists
        if (existingperson.contains(remove_person_from_organization)) {
            // Remove the organization
            existingperson.removeAll(remove_person_from_organization);

            // Join the organizations back into a string
            QString newListOfperson = existingperson.join(",");

            // Update the row with the new list of organizations
            QSqlQuery updateQuery(mydb_organization);
            updateQuery.prepare("UPDATE organization_info_database SET organization_person = :new_organization_person WHERE organization_name = :organization_id_in_data_base");
            updateQuery.bindValue(":new_organization_person", newListOfperson);
            updateQuery.bindValue(":organization_id_in_data_base", organization_id_in_data_base);

            if (updateQuery.exec()) {
                qDebug() << "person removed successfully.";
            } else {
                qDebug() << "Failed to update row." << updateQuery.lastError();
            }
        } else {
            qDebug() << "person not found in the list.";
        }
    } else {
        qDebug() << "organization not found or an error occurred." << selectQuery.lastError();
    }
}
//

QString myServer::getting_info_of_organizatios(QString &organization_id)
{

    QString organization_info;

    QSqlQuery selectQuery(mydb_organization);
    selectQuery.prepare("SELECT * FROM organization_info_database WHERE organization_name = :organization_id_in_data_base");
    selectQuery.bindValue(":organization_id_in_data_base", organization_id);

    if (selectQuery.exec() && selectQuery.next()) {
        // Retrieve values from the query result

        QString id = selectQuery.value("organization_id").toString();
        QString name = selectQuery.value("organization_name").toString();
        QString owner = selectQuery.value("organization_owner").toString();
        QString teams = selectQuery.value("organization_team").toString();
        QString persons = selectQuery.value("organization_person").toString();


        // Construct user_info string in the desired format
        organization_info = QString("%1*%2*%3*%4*%5")
                                .arg(id, name, owner, teams, persons);

        qDebug() << organization_info;
        return organization_info;
        //socket_handle


    }
    else {
        QString err;
        return err;
        qDebug() << "organization not found or an error occurred." << selectQuery.lastError();
    }
}
//-------------------------------

QVector<QString> myServer::get_team_of_organization(QString &organization_id)
{
    //getting teams
    qDebug() << "org name" <<organization_id;
    qDebug() << "we are in getting teams";
    QSqlQuery selectQuery(mydb_organization);
    selectQuery.prepare("SELECT * FROM organization_info_database WHERE organization_name = :organization_id_in_data_base");
    selectQuery.bindValue(":organization_id_in_data_base", organization_id);

    if (selectQuery.exec() && selectQuery.next()) {
        QString teamsString = selectQuery.value("organization_team").toString();

        // Split the teams using the comma delimiter
        QStringList teamList = teamsString.split(",");

        // Convert QStringList to QVector<QString>
        QVector<QString> teamVector = teamList.toVector();
        QString teams_to_send_on_socket;
        // Use teamsVector as needed
        for(int i = 0;i<teamVector.size();i++){
            qDebug() <<teamVector[i];
            teams_to_send_on_socket.append(teamVector[i]);
            teams_to_send_on_socket.append("*");
        }
        qDebug() << "feed back of get teams of org is :" <<teams_to_send_on_socket;

        writing_feed_back(teams_to_send_on_socket);
        on_sendFileBTN_clicked();

        qDebug() << "team  Vector: " << teamVector;
        return  teamVector;

    } else {
        qDebug() << "organization not found or an error occurred." << selectQuery.lastError();
        QVector<QString> errorVector;
        errorVector.append("Error: Organization not found or an error occurred.");

        // Write feedback and handle the error gracefully
        QString feed = "";
        writing_feed_back(feed);
        on_sendFileBTN_clicked();

        return errorVector;
    }
}


//-------------------------------
QVector<QString> myServer::get_person_of_organization(QString &organization_id)
{

    QSqlQuery selectQuery(mydb_organization);
    selectQuery.prepare("SELECT * FROM organization_info_database WHERE organization_name = :organization_id_in_data_base");
    selectQuery.bindValue(":organization_id_in_data_base", organization_id);

    if (selectQuery.exec() && selectQuery.next()) {
        QString personString = selectQuery.value("organization_person").toString();

        // Split the teams using the comma delimiter
        QStringList personList = personString.split(",");

        // Convert QStringList to QVector<QString>
        QVector<QString> personVector = personList.toVector();
        QString members_fly_on_sokcet;
        // Use teamsVector as needed
        for(int i = 0;i<personVector.size();i++){
            qDebug() <<personVector[i];
            members_fly_on_sokcet.append(personVector[i]);
            members_fly_on_sokcet.append("*");
        }
        writing_feed_back(members_fly_on_sokcet);
        on_sendFileBTN_clicked();

        qDebug() << "person  Vector: " << personVector;
        return personVector;

    } else {
        qDebug() << "organization not found or an error occurred." << selectQuery.lastError();
        QVector<QString> err ={""};
        return err;
    }
}

QVector<QString> myServer::get_projects_of_organization(QString &organization_id)
{

    QSqlQuery selectQuery(mydb_organization);
    selectQuery.prepare("SELECT * FROM organization_info_database WHERE organization_name = :organization_id_in_data_base");
    selectQuery.bindValue(":organization_id_in_data_base", organization_id);

    if (selectQuery.exec() && selectQuery.next()) {
        QString personString = selectQuery.value("organization_project").toString();

        // Split the teams using the comma delimiter
        QStringList personList = personString.split(",");

        // Convert QStringList to QVector<QString>
        QVector<QString> personVector = personList.toVector();
        QString project_on_socket;
        // Use teamsVector as needed
        for(int i = 0;i<personVector.size();i++){
            qDebug() <<personVector[i];
            project_on_socket.append(personVector[i]);
            project_on_socket.append("*");
        }
        writing_feed_back(project_on_socket);
        on_sendFileBTN_clicked();
        qDebug() << "project  Vector: " << personVector;
        return personVector;

    } else {
        qDebug() << "organization not found or an error occurred." << selectQuery.lastError();
        QVector<QString> err = {""};
        return err;
    }

}

void myServer::change_project_name_in_all_teams(QString &old_project_name, QString &new_project_name)
{
    QSqlQuery selectQuery(mydb_team);
    selectQuery.prepare("SELECT * FROM team_info_database WHERE team_projects LIKE :old_project");
    selectQuery.bindValue(":old_project", "%" + old_project_name + "%");

    if (selectQuery.exec()) {
        while (selectQuery.next()) {
            QString list_of_projects = selectQuery.value("team_projects").toString();
            QStringList existingProjects = list_of_projects.split(",");

            if (existingProjects.contains(old_project_name)) {
                // Replace old project name with new one
                for (int i = 0; i < existingProjects.size(); ++i) {
                    if (existingProjects.at(i) == old_project_name) {
                        existingProjects.replace(i, new_project_name);
                        break;
                    }
                }

                QString updated_projects = existingProjects.join(",");
                QSqlQuery updateQuery(mydb_team);
                updateQuery.prepare("UPDATE team_info_database SET team_projects = :new_projects WHERE team_id = :team_id");
                updateQuery.bindValue(":new_projects", updated_projects);
                updateQuery.bindValue(":team_id", selectQuery.value("team_id").toString());

                if (updateQuery.exec()) {
                    qDebug() << "Row updated successfully for team_id:" << selectQuery.value("team_id").toString();
                    // Feedback for updating the row
                } else {
                    qDebug() << "Failed to update row for team_id:" << selectQuery.value("team_id").toString() << updateQuery.lastError();
                    // Fail
                }
            }
        }
    } else {
        qDebug() << "Error in selecting records:" << selectQuery.lastError();
        // Feedback for error in selecting records
    }
}


//-------------------------------
//team function

void myServer::add_team_to_data_base(QString &team_data)
{

    QString data_recieved_by_socket_to_add_to_team = team_data;

    QStringList fields = data_recieved_by_socket_to_add_to_team.split("*");
    QString id_team_to_database = fields[1];

    QSqlQuery checkQuery;

    checkQuery.prepare("SELECT * FROM team_info_database WHERE team_id = :id_team_to_database");
    checkQuery.bindValue(":id_team_to_database", id_team_to_database);

    if (checkQuery.exec() && checkQuery.next()) {
        qDebug() << "team with the same id already exists in the database.";
    }

    else {

        QSqlQuery insertQuery;

        insertQuery.prepare("INSERT INTO team_info_database (team_id,team_name, team_admin, team_persons,team_projects) VALUES (?, ?, ?, ?, ?)");

        // Bind values for the insertion
        insertQuery.addBindValue(fields[1]); //team_id
        insertQuery.addBindValue(fields[2]); //team_name
        insertQuery.addBindValue(fields[3]); //team_admin
        insertQuery.addBindValue(fields[4]); //team_persons
        insertQuery.addBindValue(fields[5]); //team_projects


        // Execute the insertion query
        if (insertQuery.exec()) {
            qDebug() << "team added successfully.";
            // Sending feedback through socket that organization added to the database

        }
        else {
            qDebug() << "Could not add team." <<insertQuery.lastError();
        }
    }
}

//------------------------------

void myServer::change_name_of_team(QString &team_id, QString new_name)
{
    QString team_id_in_data_base = team_id; //it is the old name not the id

    QSqlQuery checkQuery(mydb_team);

    // CREATE TABLE "team_info_database" (
    //     "team_id"	TEXT,
    //     "team_name"	TEXT,
    //     "team_admin"	TEXT,
    //     "team_persons"	TEXT,
    //     "team_projects"	TEXT
    //     )

    checkQuery.prepare("SELECT * FROM team_info_database WHERE team_name = :team_id_in_data_base");
    checkQuery.bindValue(":team_id_in_data_base", new_name);

    if (checkQuery.exec() && checkQuery.next()) {
        qDebug() << "team with the same id already exists in the database.";
        //should be handled through socket!!

    }
    else{
        QSqlQuery updateQuery(mydb_team);
        updateQuery.prepare("UPDATE team_info_database SET team_name = :new_team_name WHERE team_name = :team_id_in_data_base");
        updateQuery.bindValue(":new_team_name", new_name);
        updateQuery.bindValue(":team_id_in_data_base", team_id_in_data_base);

        if (updateQuery.exec()) {
            qDebug() << "team name updated successfully.";

            // You can add additional logic or feedback here
            //feed back should be handled here

        } else {
            qDebug() << "Could not update team name." << updateQuery.lastError();
            // You can handle the error or provide feedback here
            //feedback should be handled here
        }
    }
}


//------------------------------
void myServer::change_admin_of_the_team(QString &team_id, QString &new_name)
{
    QString team_id_in_data_base = team_id;
    QString new_admin  = new_name;

    QSqlQuery updateQuery(mydb_team);
    updateQuery.prepare("UPDATE team_info_database SET team_admin = :new_team_admin WHERE team_name = :team_id_in_data_base");
    updateQuery.bindValue(":new_team_admin", new_admin);
    updateQuery.bindValue(":team_id_in_data_base", team_id_in_data_base);

    if (updateQuery.exec()) {
        qDebug() << "team admin updated successfully.";

        // You can add additional logic or feedback here
        //feed back should be handled here

    } else {
        qDebug() << "Could not update team admin." << updateQuery.lastError();
        // You can handle the error or provide feedback here
        //feedback should be handled here
    }
}
//----------------------------------------
void myServer::add_person_to_team(QString &team_id, QString& new_person)
{
    QString team_id_in_data_base = team_id;  // Set the actual username
    QString person_to_add = new_person;

    QSqlQuery selectQuery(mydb_team);

    selectQuery.prepare("SELECT * FROM team_info_database WHERE team_name = :team_id_in_data_base");
    selectQuery.bindValue(":team_id_in_data_base", team_id_in_data_base);


    if (selectQuery.exec() && selectQuery.next()) {

        QString list_of_person = selectQuery.value("team_persons").toString();

        QStringList existingperson = list_of_person.split(",");

        if (!existingperson.contains(person_to_add)) {
            list_of_person += "," + person_to_add;

            QSqlQuery updateQuery(mydb_team);
            updateQuery.prepare("UPDATE team_info_database SET team_persons = :new_person WHERE team_name = :team_id_in_data_base");
            updateQuery.bindValue(":new_person", list_of_person);
            updateQuery.bindValue(":team_id_in_data_base", team_id_in_data_base);

            if (updateQuery.exec())
            {
                qDebug() << "Row updated successfully.";
            }
            else {
                qDebug() << "Failed to update row." << updateQuery.lastError();
            }
        } else {
            qDebug() << "person already exists in the list.";
        }

    } else {
        qDebug() << "team not found or an error occurred." << selectQuery.lastError();
    }
}

//--------------------------------------
void myServer::add_project_to_team(QString team_id, QString &new_project)
{
    QString team_id_in_data_base = team_id;  // Set the actual username
    QString project_to_add = new_project;

    QSqlQuery selectQuery(mydb_team);

    selectQuery.prepare("SELECT * FROM team_info_database WHERE team_name = :team_id_in_data_base");
    selectQuery.bindValue(":team_id_in_data_base", team_id_in_data_base);


    if (selectQuery.exec() && selectQuery.next()) {

        QString list_of_project = selectQuery.value("team_projects").toString();

        QStringList existingprojects = list_of_project.split(",");

        if (!existingprojects.contains(project_to_add)) {
            list_of_project += "," + project_to_add;

            QSqlQuery updateQuery(mydb_team);
            updateQuery.prepare("UPDATE team_info_database SET team_projects = :new_project WHERE team_name = :team_id_in_data_base");
            updateQuery.bindValue(":new_project", list_of_project);
            updateQuery.bindValue(":team_id_in_data_base", team_id_in_data_base);

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
        qDebug() << "team not found or an error occurred." << selectQuery.lastError();
    }

}
//----------------------------

void myServer::removing_person_from_team(QString &team_id, QString &person_id_to_remove)
{
    QString team_id_in_data_base = team_id;  // Set the actual username
    QString remove_person_from_team = person_id_to_remove;

    // CREATE TABLE "team_info_database" (
    //     "team_id"	TEXT,
    //     "team_name"	TEXT,
    //     "team_admin"	TEXT,
    //     "team_persons"	TEXT,
    //     "team_projects"	TEXT
    //     )

    QSqlQuery selectQuery(mydb_team);
    selectQuery.prepare("SELECT * FROM team_info_database WHERE team_name = :team_id_in_data_base");
    selectQuery.bindValue(":team_id_in_data_base", team_id_in_data_base);

    if (selectQuery.exec() && selectQuery.next()) {
        QString list_of_person = selectQuery.value("team_persons").toString();

        // Split the existing organizations
        QStringList existingperson = list_of_person.split(",");

        // Check if the organization to remove exists
        if (existingperson.contains(remove_person_from_team)) {
            // Remove the organization
            existingperson.removeAll(remove_person_from_team);

            // Join the organizations back into a string
            QString newListOfperson = existingperson.join(",");

            // Update the row with the new list of organizations
            QSqlQuery updateQuery(mydb_team);
            updateQuery.prepare("UPDATE team_info_database SET team_persons = :new_team_person WHERE team_name = :team_id_in_data_base");
            updateQuery.bindValue(":new_team_person", newListOfperson);
            updateQuery.bindValue(":team_id_in_data_base", team_id_in_data_base);

            if (updateQuery.exec()) {
                qDebug() << "person removed successfully.";
            } else {
                qDebug() << "Failed to update row." << updateQuery.lastError();
            }
        } else {
            qDebug() << "person not found in the list.";
        }
    } else {
        qDebug() << "organization not found or an error occurred." << selectQuery.lastError();
    }

}

//-----------------------------------------
void myServer::removing_project_from_team(QString &team_id, QString &project_id_to_remove)
{
    QString team_id_in_data_base = team_id;  // Set the actual username
    QString remove_project_from_team = project_id_to_remove ;

    // CREATE TABLE "team_info_database" (
    //     "team_id"	TEXT,
    //     "team_name"	TEXT,
    //     "team_admin"	TEXT,
    //     "team_persons"	TEXT,
    //     "team_projects"	TEXT
    //     )

    QSqlQuery selectQuery;
    selectQuery.prepare("SELECT * FROM team_info_database WHERE team_id = :team_id_in_data_base");
    selectQuery.bindValue(":team_id_in_data_base", team_id_in_data_base);

    if (selectQuery.exec() && selectQuery.next()) {
        QString list_of_projects = selectQuery.value("team_projects").toString();

        // Split the existing organizations
        QStringList existingprojects = list_of_projects.split(",");

        // Check if the organization to remove exists
        if (existingprojects.contains(remove_project_from_team)) {
            // Remove the organization
            existingprojects.removeAll(remove_project_from_team);

            // Join the organizations back into a string
            QString newListOfprojects = existingprojects.join(",");

            // Update the row with the new list of organizations
            QSqlQuery updateQuery;
            updateQuery.prepare("UPDATE team_info_database SET team_projects = :new_team_projects WHERE team_id = :team_id_in_data_base");
            updateQuery.bindValue(":new_team_projects", newListOfprojects);
            updateQuery.bindValue(":team_id_in_data_base", team_id_in_data_base);

            if (updateQuery.exec()) {
                qDebug() << "project removed successfully.";
            } else {
                qDebug() << "Failed to update row." << updateQuery.lastError();
            }
        } else {
            qDebug() << "project not found in the list.";
        }
    } else {
        qDebug() << "organization not found or an error occurred." << selectQuery.lastError();
    }

}
//--------------------------

QVector<QString> myServer::getting_persons_of_team(QString team_id)
{
    QString team_id_in_data_base = team_id;  // Set the actual username

    // CREATE TABLE "team_info_database" (
    //     "team_id"	TEXT,
    //     "team_name"	TEXT,
    //     "team_admin"	TEXT,
    //     "team_persons"	TEXT,
    //     "team_projects"	TEXT
    //     )

    QSqlQuery selectQuery(mydb_team);
    selectQuery.prepare("SELECT * FROM team_info_database WHERE team_name = :team_id_in_data_base");
    selectQuery.bindValue(":team_id_in_data_base", team_id_in_data_base);

    if (selectQuery.exec() && selectQuery.next()) {

        QString personString = selectQuery.value("team_persons").toString();

        // Split the teams using the comma delimiter
        QStringList personList = personString.split(",");

        // Convert QStringList to QVector<QString>
        QVector<QString> personVector = personList.toVector();
        QString members_of_socket;
        // Use teamsVector as needed
        for(int i = 0;i<personVector.size();i++){
            qDebug() <<personVector[i];
            members_of_socket.append(personVector[i]);
            members_of_socket.append("*");

        }
        writing_feed_back(members_of_socket);
        on_sendFileBTN_clicked();
        qDebug() << "person  Vector: " << personVector;
        return personVector;

    } else {
        qDebug() << "team not found or an error occurred." << selectQuery.lastError();
        QVector<QString> err = {""};
        QString err1 = "";
        writing_feed_back(err1);
        on_sendFileBTN_clicked();
        return err;
    }


}

//-------------------------------------
QVector<QString> myServer::getting_projects_of_team(QString team_id)
{
    QString team_id_in_data_base = team_id;  // Set the actual username

    // CREATE TABLE "team_info_database" (
    //     "team_id"	TEXT,
    //     "team_name"	TEXT,
    //     "team_admin"	TEXT,
    //     "team_persons"	TEXT,
    //     "team_projects"	TEXT
    //     )

    QSqlQuery selectQuery(mydb_team);
    selectQuery.prepare("SELECT * FROM team_info_database WHERE team_name = :team_id_in_data_base");
    selectQuery.bindValue(":team_id_in_data_base", team_id_in_data_base);

    if (selectQuery.exec() && selectQuery.next()) {

        QString personprojects = selectQuery.value("team_projects").toString();

        // Split the teams using the comma delimiter
        QStringList projectList = personprojects.split(",");

        // Convert QStringList to QVector<QString>
        QVector<QString> projectVector = projectList.toVector();
        QString projects_of_team;
        // Use teamsVector as needed
        for(int i = 0;i<projectVector.size();i++){
            qDebug() <<projectVector[i];
            projects_of_team.append(projectVector[i]);
            projects_of_team.append("*");
        }
        writing_feed_back(projects_of_team);
        on_sendFileBTN_clicked();

        qDebug() << "project  Vector: " << projectVector;
        return projectVector;

    } else {
        qDebug() << "team not found or an error occurred." << selectQuery.lastError();
        QVector<QString> x = {""};
        QString feed = "";
        writing_feed_back(feed);
        on_sendFileBTN_clicked();
        return x;
    }
}

//---------------------------

QString myServer::getting_info_of_team(QString team_id)
{

    // CREATE TABLE "team_info_database" (
    //     "team_id"	TEXT,
    //     "team_name"	TEXT,
    //     "team_admin"	TEXT,
    //     "team_persons"	TEXT,
    //     "team_projects"	TEXT
    //     )

    QString team_id_in_data_base = team_id;
    QString team_info;

    QSqlQuery selectQuery(mydb_team);
    selectQuery.prepare("SELECT * FROM team_info_database WHERE team_name = :team_id_in_data_base");
    selectQuery.bindValue(":team_id_in_data_base", team_id_in_data_base);

    if (selectQuery.exec() && selectQuery.next()) {
        // Retrieve values from the query result

        QString id = selectQuery.value("team_id").toString();
        QString name = selectQuery.value("team_name").toString();
        QString admin = selectQuery.value("team_admin").toString();
        QString person = selectQuery.value("team_persons").toString();
        QString projects = selectQuery.value("team_projects").toString();


        // Construct user_info string in the desired format
        team_info = QString("%1*%2*%3*%4*%5")
                        .arg(id, name, admin, person, projects);

        qDebug() << team_info;
        return team_info;
        //socket_handle

    }
    else {
        qDebug() << "organization not found or an error occurred." << selectQuery.lastError();
        QString err = "";
        return err;
    }
}

void myServer::change_team_name_in_all_projects(QString &old_team_name, QString &new_team_name)
{
    QSqlQuery selectQuery(mydb_project);
    selectQuery.prepare("SELECT * FROM project_info_database WHERE project_teams LIKE :old_team");
    selectQuery.bindValue(":old_team", "%" + old_team_name + "%");

    if (selectQuery.exec()) {
        while (selectQuery.next()) {
            QString list_of_teams = selectQuery.value("project_teams").toString();
            QStringList existingTeams = list_of_teams.split(",");

            if (existingTeams.contains(old_team_name)) {
                // Replace old team name with new one
                for (int i = 0; i < existingTeams.size(); ++i) {
                    if (existingTeams.at(i) == old_team_name) {
                        existingTeams.replace(i, new_team_name);
                        break;
                    }
                }

                QString updated_teams = existingTeams.join(",");
                QSqlQuery updateQuery(mydb_project);
                updateQuery.prepare("UPDATE project_info_database SET project_teams = :new_teams WHERE project_id = :project_id");
                updateQuery.bindValue(":new_teams", updated_teams);
                updateQuery.bindValue(":project_id", selectQuery.value("project_id").toString());

                if (updateQuery.exec()) {
                    qDebug() << "Row updated successfully for project_id:" << selectQuery.value("project_id").toString();
                    // Feedback for updating the row
                } else {
                    qDebug() << "Failed to update row for project_id:" << selectQuery.value("project_id").toString() << updateQuery.lastError();
                    // Fail
                }
            }
        }
    } else {
        qDebug() << "Error in selecting records:" << selectQuery.lastError();
        // Feedback for error in selecting records
    }
}

void myServer::change_task_name_in_all_projects(QString &old_task_name, QString &new_task_name)
{
    QSqlQuery selectQuery(mydb_project);
    selectQuery.prepare("SELECT * FROM project_info_database WHERE project_tasks LIKE :old_task");
    selectQuery.bindValue(":old_task", "%" + old_task_name + "%");

    if (selectQuery.exec()) {
        while (selectQuery.next()) {
            QString list_of_tasks = selectQuery.value("project_tasks").toString();
            QStringList existingTasks = list_of_tasks.split(",");

            if (existingTasks.contains(old_task_name)) {
                // Replace old task name with new one
                for (int i = 0; i < existingTasks.size(); ++i) {
                    if (existingTasks.at(i) == old_task_name) {
                        existingTasks.replace(i, new_task_name);
                        break;
                    }
                }

                QString updated_tasks = existingTasks.join(",");
                QSqlQuery updateQuery(mydb_project);
                updateQuery.prepare("UPDATE project_info_database SET project_tasks = :new_tasks WHERE project_id = :project_id");
                updateQuery.bindValue(":new_tasks", updated_tasks);
                updateQuery.bindValue(":project_id", selectQuery.value("project_id").toString());

                if (updateQuery.exec()) {
                    qDebug() << "Row updated successfully for project_id:" << selectQuery.value("project_id").toString();
                    // Feedback for updating the row
                } else {
                    qDebug() << "Failed to update row for project_id:" << selectQuery.value("project_id").toString() << updateQuery.lastError();
                    // Fail
                }
            }
        }
    } else {
        qDebug() << "Error in selecting records:" << selectQuery.lastError();
        // Feedback for error in selecting records
    }
}

void myServer::search_for_projects(QString &project_search)
{
    qDebug() << "we are in seaerch for project";
    QSqlQuery query(mydb_project);
    query.prepare("SELECT * FROM project_info_database WHERE project_name LIKE :search");
    query.bindValue(":search", "%" + project_search + "%");

    // Execute the query
    if (query.exec())
    {
        // Initialize a QString to store the concatenated project names
        QString foundProjects;

        // Process the results, concatenate project names with a comma
        while (query.next())
        {
            QString projectName = query.value("project_name").toString();
            foundProjects += projectName + "*";
        }

        // Remove the trailing comma and space
        //        foundProjects = foundProjects.left(foundProjects.length() - 2);

        // Print the concatenated project names
        qDebug() << "Found projects: " << foundProjects;
        writing_feed_back(foundProjects);
        on_sendFileBTN_clicked();
    }
    else
    {
        QString feed= "";
        writing_feed_back(feed);
        on_sendFileBTN_clicked();
        // Handle query execution error
        qDebug() << "Error executing query: " << query.lastError().text();
    }
}

void myServer::archive_task(QString &project_id, QString &task_id)
{
    QSqlQuery query(mydb_project);

    // Fetch the current value of "project_tasks" for the given project_id
    query.prepare("SELECT project_tasks FROM project_info_database WHERE project_name = :project_id");
    query.bindValue(":project_id", project_id);

    if (query.exec() && query.next()) {
        QString currentTasks = query.value(0).toString();

        // Check if the task is already archived
        if (currentTasks.contains(task_id + "$")) {
            qDebug() << "Task is already archived.";
            return;  // Do nothing if the task is already archived
        }

        // Find and replace the task_id with the archived version
        currentTasks.replace(task_id, task_id + "$");

        // Update the "project_tasks" column in the database with the modified value
        query.prepare("UPDATE project_info_database SET project_tasks = :newTasks WHERE project_name = :project_id");
        query.bindValue(":newTasks", currentTasks);
        query.bindValue(":project_id", project_id);

        if (!query.exec()) {
            // Handle errors if necessary
            qDebug() << "Error updating project_tasks:" << query.lastError().text();
        }
        else{
            qDebug() << "task archived!!";
        }
    } else {
        // Handle errors if necessary
        qDebug() << "Error fetching project_tasks:" << query.lastError().text();
    }
}

void myServer::unarchive_task(QString &project_id, QString task_id)
{
    QSqlQuery query(mydb_project);
    // Fetch the current value of "project_tasks" for the given project_id
    query.prepare("SELECT project_tasks FROM project_info_database WHERE project_name = :project_id");
    query.bindValue(":project_id", project_id);

    if (query.exec() && query.next()) {
        QString currentTasks = query.value(0).toString();

        // Check if the task is already unarchived
        if (!currentTasks.contains(task_id + "$")) {
            qDebug() << "Task is not archived.";
            return;  // Do nothing if the task is not archived
        }

        // Find and replace the archived version of task_id with the original version
        currentTasks.replace(task_id + "$", task_id);

        // Update the "project_tasks" column in the database with the modified value
        query.prepare("UPDATE project_info_database SET project_tasks = :newTasks WHERE project_name = :project_id");
        query.bindValue(":newTasks", currentTasks);
        query.bindValue(":project_id", project_id);

        if (!query.exec()) {
            // Handle errors if necessary
            qDebug() << "Error updating project_tasks:" << query.lastError().text();
        } else {
            qDebug() << "Task unarchived!";
        }
    } else {
        // Handle errors if necessary
        qDebug() << "Error fetching project_tasks:" << query.lastError().text();
    }
}
//-------------------------------

//project functions

void myServer::add_project_to_data_base(QString &project_data)
{
    qDebug() << "add project to data base";
    QString data_recieved_by_socket_to_add_to_project = project_data;
    QStringList fields = data_recieved_by_socket_to_add_to_project.split("*");

    // CREATE TABLE "project_info_database" (
    //     "project_id"	TEXT,
    //     "project_name"	TEXT,
    //     "project_type"	TEXT,
    //     "project_person"	TEXT,
    //     "project_teams"	TEXT,
    //     "project_tasks"	TEXT
    // )

    QString id_project_to_database = fields[1];

    QSqlQuery checkQuery(mydb_project);

    checkQuery.prepare("SELECT * FROM project_info_database WHERE project_name = :id_project_to_database");
    checkQuery.bindValue(":id_project_to_database", id_project_to_database);

    if (checkQuery.exec() && checkQuery.next()) {
        qDebug() << "project with the same id already exists in the database.";
        //handeling the

    }
    else {
        QSqlQuery insertQuery(mydb_project);

        insertQuery.prepare("INSERT INTO project_info_database (project_name,project_type) VALUES (?,?)");

        // Bind values for the insertion
        //insertQuery.addBindValue(fields[1]); // project_id
        insertQuery.addBindValue(fields[2]); // project_name
        insertQuery.addBindValue(fields[3]); // project_type

        // Execute the insertion query

        if (insertQuery.exec()) {
            qDebug() << "project added successfully.";
            // Sending feedback through socket that organization added to the database

        } else {
            qDebug() << "Could not add project." << insertQuery.lastError();
        }
    }
}

//------------------------
void myServer::changing_name_of_project(QString &project_id, QString &new_project_name)
{
    QString project_id_in_data_base = project_id; //it is essentialy the old name
    QString new_project_name_in_data  = new_project_name;

    // CREATE TABLE "project_info_database" (
    //     "project_id"	TEXT,
    //     "project_name"	TEXT,
    //     "project_type"	TEXT,
    //     "project_person"	TEXT,
    //     "project_teams"	TEXT,
    //     "project_tasks"	TEXT
    // )

    QSqlQuery checkQuery(mydb_project);

    checkQuery.prepare("SELECT * FROM project_info_database WHERE project_name = :id_project_to_database");
    checkQuery.bindValue(":id_project_to_database", new_project_name);

    if (checkQuery.exec() && checkQuery.next()) {
        qDebug() << "project with the same id already exists in the database.";
        //handeling the socket

    }
    else{

        QSqlQuery updateQuery(mydb_project);
        updateQuery.prepare("UPDATE project_info_database SET project_name = :new_project_name_in_data WHERE project_name = :project_id_in_data_base");
        updateQuery.bindValue(":new_project_name_in_data", new_project_name_in_data);
        updateQuery.bindValue(":project_id_in_data_base", project_id_in_data_base);

        if (updateQuery.exec()) {
            qDebug() << "Project name updated successfully.";
            // You can add additional logic or feedback here
            //feed back should be handled here

        } else {
            qDebug() << "Could not update personal name." << updateQuery.lastError();
            // You can handle the error or provide feedback here
            //feedback should be handled here
        }
    }
}

//---------------------------
void myServer::changing_type_of_project(QString &project_id, QString &new_project_type)
{
    QString project_id_in_data_base = project_id;
    QString new_project_type_in_data  = new_project_type;

    // CREATE TABLE "project_info_database" (
    //     "project_id"	TEXT,
    //     "project_name"	TEXT,
    //     "project_type"	TEXT,
    //     "project_person"	TEXT,
    //     "project_teams"	TEXT,
    //     "project_tasks"	TEXT
    // )

    QSqlQuery updateQuery;
    updateQuery.prepare("UPDATE project_info_database SET project_type = :new_project_type_in_data WHERE project_id = :project_id_in_data_base");
    updateQuery.bindValue(":new_project_type_in_data", new_project_type_in_data);
    updateQuery.bindValue(":project_id_in_data_base", project_id_in_data_base);

    if (updateQuery.exec()) {
        qDebug() << "Project type updated successfully.";
        // You can add additional logic or feedback here
        //feed back should be handled here

    } else {
        qDebug() << "Could not update personal type." << updateQuery.lastError();
        // You can handle the error or provide feedback here
        //feedback should be handled here
    }
}

//--------------------
void myServer::changing_person_of_project(QString &project_id, QString &id_of_person)
{
    QString project_id_in_data_base = project_id;
    QString new_project_person_in_data  = id_of_person;

    // CREATE TABLE "project_info_database" (
    //     "project_id"	TEXT,
    //     "project_name"	TEXT,
    //     "project_type"	TEXT,
    //     "project_person"	TEXT,
    //     "project_teams"	TEXT,
    //     "project_tasks"	TEXT
    // )

    QSqlQuery updateQuery(mydb_project);
    updateQuery.prepare("UPDATE project_info_database SET project_person = :new_project_person_in_data WHERE project_name = :project_id_in_data_base");
    updateQuery.bindValue(":new_project_person_in_data", new_project_person_in_data);
    updateQuery.bindValue(":project_id_in_data_base", project_id_in_data_base);

    if (updateQuery.exec()) {
        qDebug() << "Project person updated successfully.";
        // You can add additional logic or feedback here
        //feed back should be handled here

    } else {
        qDebug() << "Could not update personal person." << updateQuery.lastError();
        // You can handle the error or provide feedback here
        //feedback should be handled here
    }
}

//----------------------------------
void myServer::add_team_to_project(QString &project_id, QString &new_team_to_add)
{
    QString project_id_in_data_base = project_id;  // Set the actual username
    QString team_to_add = new_team_to_add;

    QSqlQuery selectQuery(mydb_project);
    selectQuery.prepare("SELECT * FROM project_info_database WHERE project_name = :project_id_in_data_base");
    selectQuery.bindValue(":project_id_in_data_base", project_id_in_data_base);

    // CREATE TABLE "project_info_database" (
    //     "project_id"	TEXT,
    //     "project_name"	TEXT,
    //     "project_type"	TEXT,
    //     "project_person"	TEXT,
    //     "project_teams"	TEXT,
    //     "project_tasks"	TEXT
    // )


    if (selectQuery.exec() && selectQuery.next()) {

        QString list_of_team = selectQuery.value("project_teams").toString();

        QStringList existingteam = list_of_team.split(",");

        if (!existingteam.contains(team_to_add)) {
            list_of_team += "," + team_to_add;

            QSqlQuery updateQuery(mydb_project);
            updateQuery.prepare("UPDATE project_info_database SET project_teams = :new_teams_in_project WHERE project_name = :project_id_in_data_base");
            updateQuery.bindValue(":new_teams_in_project", list_of_team);
            updateQuery.bindValue(":project_id_in_data_base", project_id_in_data_base);

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

//------------------------------

void myServer::add_task_to_project(QString &project_id, QString &new_task_to_add)
{
    QString project_id_in_data_base = project_id;  // Set the actual username
    QString task_to_add = new_task_to_add;

    QSqlQuery selectQuery;
    selectQuery.prepare("SELECT * FROM project_info_database WHERE project_id = :project_id_in_data_base");
    selectQuery.bindValue(":project_id_in_data_base", project_id_in_data_base);

    // CREATE TABLE "project_info_database" (
    //     "project_id"	TEXT,
    //     "project_name"	TEXT,
    //     "project_type"	TEXT,
    //     "project_person"	TEXT,
    //     "project_teams"	TEXT,
    //     "project_tasks"	TEXT
    // )

    if (selectQuery.exec() && selectQuery.next()) {

        QString list_of_tasks = selectQuery.value("project_tasks").toString();

        QStringList existingtasks = list_of_tasks.split(",");

        if (!existingtasks.contains(task_to_add)) {
            list_of_tasks += "," + task_to_add;

            QSqlQuery updateQuery;
            updateQuery.prepare("UPDATE project_info_database SET project_tasks = :new_task_in_project WHERE project_id = :project_id_in_data_base");
            updateQuery.bindValue(":new_task_in_project", list_of_tasks);
            updateQuery.bindValue(":project_id_in_data_base", project_id_in_data_base);

            if (updateQuery.exec())
            {
                qDebug() << "Row updated successfully.";
                //feedback



            }
            else {
                qDebug() << "Failed to update row." << updateQuery.lastError();
                //feedback


            }
        } else {
            qDebug() << "tasks already exists in the list.";
            //feedback

        }

    } else {
        qDebug() << "team not found or an error occurred." << selectQuery.lastError();
    }
}

//------------------------
void myServer::remove_team_from_project(QString &project_id, QString &team_id_to_remove)
{
    QString project_id_in_data_base = project_id;  // Set the actual username
    QString remove_team_from_project = team_id_to_remove;

    // CREATE TABLE "project_info_database" (

    //     "project_id"	TEXT,
    //     "project_name"	TEXT,
    //     "project_type"	TEXT,
    //     "project_person"	TEXT,
    //     "project_teams"	TEXT,
    //     "project_tasks"	TEXT
    // )


    QSqlQuery selectQuery;
    selectQuery.prepare("SELECT * FROM project_info_database WHERE project_id = :project_id_in_data_base");
    selectQuery.bindValue(":project_id_in_data_base", project_id_in_data_base);

    if (selectQuery.exec() && selectQuery.next()) {
        QString list_of_teams = selectQuery.value("project_teams").toString();

        // Split the existing organizations
        QStringList existingteam = list_of_teams.split(",");

        // Check if the organization to remove exists
        if (existingteam.contains(remove_team_from_project)) {
            // Remove the organization
            existingteam.removeAll(remove_team_from_project);

            // Join the organizations back into a string
            QString newListOfteam = existingteam.join(",");

            // Update the row with the new list of organizations
            QSqlQuery updateQuery;
            updateQuery.prepare("UPDATE project_info_database SET project_teams = :new_team_project WHERE project_id = :project_id_in_data_base");
            updateQuery.bindValue(":new_team_project", newListOfteam);
            updateQuery.bindValue(":project_id_in_data_base", project_id_in_data_base);

            if (updateQuery.exec()) {
                qDebug() << "team removed successfully.";
            } else {
                qDebug() << "Failed to update row." << updateQuery.lastError();
            }
        } else {
            qDebug() << "team not found in the list.";
        }
    } else {
        qDebug() << "project not found or an error occurred." << selectQuery.lastError();
    }
}
//--------------------------

void myServer::remove_task_from_project(QString &project_id, QString &tasks_id_to_remove)
{
    QString project_id_in_data_base = "3";  // Set the actual username
    QString remove_tasks_from_project = "project_tasks";

    // CREATE TABLE "project_info_database" (
    //     "project_id"	TEXT,
    //     "project_name"	TEXT,
    //     "project_type"	TEXT,
    //     "project_person"	TEXT,
    //     "project_teams"	TEXT,
    //     "project_tasks"	TEXT
    // )

    QSqlQuery selectQuery;

    selectQuery.prepare("SELECT * FROM project_info_database WHERE project_id = :project_id_in_data_base");
    selectQuery.bindValue(":project_id_in_data_base", project_id_in_data_base);

    if (selectQuery.exec() && selectQuery.next()) {
        QString list_of_tasks = selectQuery.value("project_tasks").toString();

        // Split the existing organizations
        QStringList existingtasks = list_of_tasks.split(",");

        // Check if the organization to remove exists
        if (existingtasks.contains(remove_tasks_from_project)) {
            // Remove the organization
            existingtasks.removeAll(remove_tasks_from_project);

            // Join the organizations back into a string
            QString newListOftasks = existingtasks.join(",");

            // Update the row with the new list of organizations
            QSqlQuery updateQuery;
            updateQuery.prepare("UPDATE project_info_database SET project_tasks = :new_tasks_project WHERE project_id = :project_id_in_data_base");
            updateQuery.bindValue(":new_tasks_project", newListOftasks);
            updateQuery.bindValue(":project_id_in_data_base", project_id_in_data_base);

            if (updateQuery.exec()) {
                qDebug() << "task removed successfully.";
            } else {
                qDebug() << "Failed to update row." << updateQuery.lastError();
            }
        } else {
            qDebug() << "task not found in the list.";
        }
    } else {
        qDebug() << "project not found or an error occurred." << selectQuery.lastError();
    }
}


//------------------------------
QString myServer::getting_info_of_project(QString &project_id)
{

    // CREATE TABLE "project_info_database" (
    //     "project_id"	TEXT,
    //     "project_name"	TEXT,
    //     "project_type"	TEXT,
    //     "project_person"	TEXT,
    //     "project_teams"	TEXT,
    //     "project_tasks"	TEXT
    // )

    QString project_id_in_data_base = project_id;
    QString project_info;

    QSqlQuery selectQuery;
    selectQuery.prepare("SELECT * FROM project_info_database WHERE project_id = :project_id_in_data_base");
    selectQuery.bindValue(":project_id_in_data_base", project_id_in_data_base);

    if (selectQuery.exec() && selectQuery.next()) {
        // Retrieve values from the query result

        QString id = selectQuery.value("project_id").toString();
        QString name = selectQuery.value("project_name").toString();
        QString type = selectQuery.value("project_type").toString();
        QString person = selectQuery.value("project_person").toString();
        QString teams = selectQuery.value("project_teams").toString();
        QString tasks = selectQuery.value("project_tasks").toString();

        // Construct user_info string in the desired format
        project_info = QString("%1*%2*%3*%4*%5*%6")
                           .arg(id, name, type, person, teams,tasks);

        qDebug() << project_info;
        return project_info;
        //return team_info;
        //socket_handle
    }
    else {
        qDebug() << "organization not found or an error occurred." << selectQuery.lastError();
    }
}

//----------------------------------
QVector<QString> myServer::getting_teams_of_project(QString &project_id)
{
    QString project_id_in_data_base = project_id;  // Set the actual username

    // CREATE TABLE "project_info_database" (
    //     "project_id"	TEXT,
    //     "project_name"	TEXT,
    //     "project_type"	TEXT,
    //     "project_person"	TEXT,
    //     "project_teams"	TEXT,
    //     "project_tasks"	TEXT
    // )

    QSqlQuery selectQuery;
    selectQuery.prepare("SELECT * FROM project_info_database WHERE project_id = :project_id_in_data_base");
    selectQuery.bindValue(":project_id_in_data_base", project_id_in_data_base);

    if (selectQuery.exec() && selectQuery.next()) {

        QString teamsString = selectQuery.value("project_teams").toString();

        // Split the teams using the comma delimiter
        QStringList teamList = teamsString.split(",");

        // Convert QStringList to QVector<QString>
        QVector<QString> teamsVector = teamList.toVector();

        // Use teamsVector as needed
        for(int i = 0;i<teamsVector.size();i++){
            qDebug() <<teamsVector[i];
        }

        qDebug() << "teams  Vector: " << teamsVector;
        return teamsVector;

    } else {
        qDebug() << "project not found or an error occurred." << selectQuery.lastError();
        QVector<QString> err ={""};
        return err;
    }
}
//--------------------
QVector<QString> myServer::getting_tasks_of_project(QString &project_id)
{

    QString project_id_in_data_base = project_id;  // Set the actual username

    // CREATE TABLE "project_info_database" (
    //     "project_id"	TEXT,
    //     "project_name"	TEXT,
    //     "project_type"	TEXT,
    //     "project_person"	TEXT,
    //     "project_teams"	TEXT,
    //     "project_tasks"	TEXT
    // )

    QSqlQuery selectQuery;
    selectQuery.prepare("SELECT * FROM project_info_database WHERE project_id = :project_id_in_data_base");
    selectQuery.bindValue(":project_id_in_data_base", project_id_in_data_base);

    if (selectQuery.exec() && selectQuery.next()) {

        QString tasksString = selectQuery.value("project_tasks").toString();

        // Split the teams using the comma delimiter
        QStringList taskList = tasksString.split(",");

        // Convert QStringList to QVector<QString>
        QVector<QString> tasksVector = taskList.toVector();

        // Use teamsVector as needed
        for(int i = 0;i<tasksVector.size();i++){
            qDebug() <<tasksVector[i];
        }

        qDebug() << "teams  Vector: " << tasksVector;
        return tasksVector;

    } else {
        qDebug() << "project not found or an error occurred." << selectQuery.lastError();
        QVector<QString> err = {""};
        return err;
    }
}

//------------------------
//tasks functions
void myServer::add_task_to_data_task(QString &task_data)
{

    // CREATE TABLE "tasks_info_database" (
    //     "tasks_id"	TEXT,
    //     "task_text"	TEXT,
    //     "task_project"	TEXT,
    //     "task_person"	TEXT,
    //     "tasks_persons"	TEXT,
    //     "tasks_isdone"	TEXT
    //     "task_priority"	INTEGER,
    //     "task_date"	TEXT)

    QString data_recieved_by_socket_to_add_to_task =  task_data;
    QStringList fields = data_recieved_by_socket_to_add_to_task.split("*");
    QString id_task_to_database = fields[1];

    QSqlQuery checkQuery;

    checkQuery.prepare("SELECT * FROM tasks_info_database WHERE tasks_id = :id_task_to_database");
    checkQuery.bindValue(":id_task_to_database", id_task_to_database);

    if (checkQuery.exec() && checkQuery.next()) {
        qDebug() << "task with the same id already exists in the database.";
    }
    else {

        QSqlQuery insertQuery;

        insertQuery.prepare("INSERT INTO tasks_info_database (tasks_id,task_text, task_project, task_person,tasks_persons,tasks_isdone,task_priority,task_date) VALUES (?, ?, ?, ?,?,?, ?,?)");

        // Bind values for the insertion
        insertQuery.addBindValue(fields[1]); //tasks_id
        insertQuery.addBindValue(fields[2]); //task_text
        insertQuery.addBindValue(fields[3]); //task_project
        insertQuery.addBindValue(fields[4]); //task_person
        insertQuery.addBindValue(fields[5]); //tasks_persons
        insertQuery.addBindValue(fields[6]); //tasks_isdone
        insertQuery.addBindValue(fields[7]); //task_priority
        insertQuery.addBindValue(fields[8]); //task_priority

        // Execute the insertion query
        if (insertQuery.exec()) {
            qDebug() << "task added successfully.";
            // Sending feedback through socket that organization added to the database

        }
        else {
            qDebug() << "Could not add task." <<insertQuery.lastError();
        }
    }
}

void myServer::changing_task_id(QString &task_id, QString &task_new_id)
{

    QString task_id_in_data_base = task_id;


    // CREATE TABLE "tasks_info_database" (
    //     "tasks_id"	TEXT,
    //     "task_text"	TEXT,
    //     "task_project"	TEXT,
    //     "task_person"	TEXT,
    //     "tasks_persons"	TEXT,
    //     "tasks_isdone"	TEXT
    //     "task_priority"	INTEGER,
    //     "task_date"	TEXT)

    QSqlQuery checkQuery(mydb_task);

    checkQuery.prepare("SELECT * FROM tasks_info_database WHERE tasks_id = :id_task_to_database");
    checkQuery.bindValue(":id_task_to_database", task_new_id);

    if (checkQuery.exec() && checkQuery.next()) {
        qDebug() << "task with the same id already exists in the database.";
    }


    else{

        QSqlQuery updateQuery(mydb_task);
        updateQuery.prepare("UPDATE tasks_info_database SET task_id = :new_task_text WHERE tasks_id = :task_id_in_data_base");
        updateQuery.bindValue(":new_task_text", task_new_id);
        updateQuery.bindValue(":task_id_in_data_base", task_id_in_data_base);

        if (updateQuery.exec()) {
            qDebug() << "tasks text updated successfully.";
            // You can add additional logic or feedback here
            //feed back should be handled here

        } else {
            qDebug() << "Could not update  task text." << updateQuery.lastError();
            // You can handle the error or provide feedback here
            //feedback should be handled here
        }

    }

}

//--------------------------------
void myServer::changing_text_of_task(QString &task_id, QString &new_text)
{
    QString task_id_in_data_base = task_id;
    QString new_task_text  = new_text;


    // CREATE TABLE "tasks_info_database" (
    //     "tasks_id"	TEXT,
    //     "task_text"	TEXT,
    //     "task_project"	TEXT,
    //     "task_person"	TEXT,
    //     "tasks_persons"	TEXT,
    //     "tasks_isdone"	TEXT
    //     "task_priority"	INTEGER,
    //     "task_date"	TEXT)

    QSqlQuery checkQuery(mydb_task);

    checkQuery.prepare("SELECT * FROM tasks_info_database WHERE task_text = :id_task_to_database");
    checkQuery.bindValue(":id_task_to_database", new_text);

    if (checkQuery.exec() && checkQuery.next()) {
        qDebug() << "task with the same id already exists in the database.";
    }
    else{

        QSqlQuery updateQuery;
        updateQuery.prepare("UPDATE tasks_info_database SET task_text = :new_task_text WHERE tasks_id = :task_id_in_data_base");
        updateQuery.bindValue(":new_task_text", new_task_text);
        updateQuery.bindValue(":task_id_in_data_base", task_id_in_data_base);

        if (updateQuery.exec()) {
            qDebug() << "tasks text updated successfully.";
            // You can add additional logic or feedback here
            //feed back should be handled here

        } else {
            qDebug() << "Could not update  task text." << updateQuery.lastError();
            // You can handle the error or provide feedback here
            //feedback should be handled here
        }

    }

}

void myServer::changing_project_of_task(QString &task_id, QString &new_project)
{
    QString task_id_in_data_base = task_id;
    QString new_project_id  = new_project;

    // CREATE TABLE "tasks_info_database" (
    //     "tasks_id"	TEXT,
    //     "task_text"	TEXT,
    //     "task_project"	TEXT,
    //     "task_person"	TEXT,
    //     "tasks_persons"	TEXT,
    //     "tasks_isdone"	TEXT
    //     , "task_priority"	INTEGER)

    QSqlQuery updateQuery;
    updateQuery.prepare("UPDATE tasks_info_database SET task_project = :new_task_project WHERE tasks_id = :task_id_in_data_base");
    updateQuery.bindValue(":new_task_project", new_project_id);
    updateQuery.bindValue(":task_id_in_data_base", task_id_in_data_base);

    if (updateQuery.exec()) {
        qDebug() << "tasks project updated successfully.";
        // You can add additional logic or feedback here
        //feed back should be handled here

    } else {
        qDebug() << "Could not update  task project." << updateQuery.lastError();
        // You can handle the error or provide feedback here
        //feedback should be handled here
    }

}
//----------------------------------

void myServer::adding_person_to_task(QString &task_id, QString &person_to_add)
{
    QString task_id_in_data_base =task_id ;  // Set the actual username

    QSqlQuery selectQuery;
    selectQuery.prepare("SELECT * FROM tasks_info_database WHERE tasks_id = :task_id_in_data_base");
    selectQuery.bindValue(":task_id_in_data_base", task_id_in_data_base);

    // CREATE TABLE "tasks_info_database" (
    //     "tasks_id"	TEXT,
    //     "task_text"	TEXT,
    //     "task_project"	TEXT,
    //     "task_person"	TEXT,
    //     "tasks_persons"	TEXT,
    //     "tasks_isdone"	TEXT
    //     , "task_priority"	INTEGER)


    if (selectQuery.exec() && selectQuery.next()) {

        QString list_of_persons = selectQuery.value("tasks_persons").toString();

        QStringList existingperson = list_of_persons.split(",");

        if (!existingperson.contains(person_to_add)) {
            list_of_persons += "," + person_to_add;

            QSqlQuery updateQuery;
            updateQuery.prepare("UPDATE tasks_info_database SET tasks_persons = :new_tasks_persons WHERE tasks_id = :task_id_in_data_base");
            updateQuery.bindValue(":new_tasks_persons", list_of_persons);
            updateQuery.bindValue(":task_id_in_data_base", task_id_in_data_base);

            if (updateQuery.exec())
            {
                qDebug() << "Row updated successfully.";
            }
            else {
                qDebug() << "Failed to update row." << updateQuery.lastError();
            }
        } else {
            qDebug() << "person already exists in the list.";
        }

    } else {
        qDebug() << "task not found or an error occurred." << selectQuery.lastError();
    }
}

//-------------------------------
void myServer::changing_is_done_of_task(QString &task_id, QString &new_id_done)
{

    QString task_id_in_data_base = task_id;
    QString new_is_done  = new_id_done;


    // CREATE TABLE "tasks_info_database" (
    //     "tasks_id"	TEXT,
    //     "task_text"	TEXT,
    //     "task_project"	TEXT,
    //     "task_person"	TEXT,
    //     "tasks_persons"	TEXT,
    //     "tasks_isdone"	TEXT
    //     , "task_priority"	INTEGER)

    QSqlQuery updateQuery;
    updateQuery.prepare("UPDATE tasks_info_database SET tasks_isdone = :new_is_done WHERE tasks_id = :task_id_in_data_base");
    updateQuery.bindValue(":new_is_done", new_is_done);
    updateQuery.bindValue(":task_id_in_data_base", task_id_in_data_base);

    if (updateQuery.exec()) {
        qDebug() << "tasks isdone updated successfully.";
        // You can add additional logic or feedback here
        //feed back should be handled here

    } else {
        qDebug() << "Could not update  task isdone." << updateQuery.lastError();
        // You can handle the error or provide feedback here
        //feedback should be handled here
    }



}
//-------------------


void myServer::changing_priority_of_task(QString &task_id, QString &new_priority)
{
    QString task_id_in_data_base =task_id;
    QString new_task_priority  = new_priority;


    // CREATE TABLE "tasks_info_database" (
    //     "tasks_id"	TEXT,
    //     "task_text"	TEXT,
    //     "task_project"	TEXT,
    //     "task_person"	TEXT,
    //     "tasks_persons"	TEXT,
    //     "tasks_isdone"	TEXT
    //     , "task_priority"	INTEGER)

    QSqlQuery updateQuery;
    updateQuery.prepare("UPDATE tasks_info_database SET task_priority = :new_task_priority WHERE tasks_id = :task_id_in_data_base");
    updateQuery.bindValue(":new_task_priority", new_task_priority);
    updateQuery.bindValue(":task_id_in_data_base", task_id_in_data_base);

    if (updateQuery.exec()) {
        qDebug() << "tasks priority updated successfully.";
        // You can add additional logic or feedback here
        //feed back should be handled here

    } else {
        qDebug() << "Could not update  task priority." << updateQuery.lastError();
        // You can handle the error or provide feedback here
        //feedback should be handled here
    }
}


void myServer::chaning_date_of_task(QString& task_name,QString &new_task_date)
{
    QString task_id_in_data_base = task_name;


    // CREATE TABLE "tasks_info_database" (
    //     "tasks_id"	TEXT,
    //     "task_text"	TEXT,
    //     "task_project"	TEXT,
    //     "task_person"	TEXT,
    //     "tasks_persons"	TEXT,
    //     "tasks_isdone"	TEXT
    //     , "task_priority"	INTEGER)

    QSqlQuery updateQuery;
    updateQuery.prepare("UPDATE tasks_info_database SET task_date = :new_task_date WHERE tasks_id = :task_id_in_data_base");
    updateQuery.bindValue(":new_task_date", new_task_date);
    updateQuery.bindValue(":task_id_in_data_base", task_id_in_data_base);

    if (updateQuery.exec()) {
        qDebug() << "tasks date updated successfully.";
        // You can add additional logic or feedback here
        //feed back should be handled here

    } else {
        qDebug() << "Could not update  task date." << updateQuery.lastError();
        // You can handle the error or provide feedback here
        //feedback should be handled here
    }

}

//-----------------------------
QString myServer::getting_info_of_tasks(QString &task_id)
{
    // CREATE TABLE "tasks_info_database" (
    //     "tasks_id"	TEXT,
    //     "task_text"	TEXT,
    //     "task_project"	TEXT,
    //     "task_person"	TEXT,
    //     "tasks_persons"	TEXT,
    //     "tasks_isdone"	TEXT
    //     , "task_priority"	INTEGER)

    QString task_id_in_data_base = task_id;
    QString task_info;

    QSqlQuery selectQuery(mydb_task);
    selectQuery.prepare("SELECT * FROM tasks_info_database WHERE tasks_id = :task_id_in_data_base");
    selectQuery.bindValue(":task_id_in_data_base", task_id_in_data_base);

    if (selectQuery.exec() && selectQuery.next()) {
        // Retrieve values from the query result

        QString id = selectQuery.value("tasks_id").toString();
        QString text = selectQuery.value("task_text").toString();
        QString project = selectQuery.value("task_project").toString();
        QString person = selectQuery.value("task_person").toString();
        QString persons = selectQuery.value("tasks_persons").toString();
        QString is_done = selectQuery.value("tasks_isdone").toString();
        QString priority = selectQuery.value("task_priority").toString();
        QString date = selectQuery.value("task_date").toString();

        // Construct user_info string in the desired format
        task_info = QString("%1*%2*%3*%4*%5*%6*%7*%8")
                        .arg(id, text, project, person, persons,is_done,priority,date);

        qDebug() << task_info;
        return task_info;
        //socket_handle
    }
    else {
        qDebug() << "organization not found or an error occurred." << selectQuery.lastError();
    }
}
//----------------------------

void myServer::removing_person_from_task(QString &task_id, QString &person_id)
{

    QString task_id_in_data_base_1 = task_id;  // Set the actual username
    QString remove_person_from_task = person_id;

    // CREATE TABLE "tasks_info_database" (
    //     "tasks_id"	TEXT,
    //     "task_text"	TEXT,
    //     "task_project"	TEXT,
    //     "task_person"	TEXT,
    //     "tasks_persons"	TEXT,
    //     "tasks_isdone"	TEXT
    //     , "task_priority"	INTEGER)


    QSqlQuery selectQuery;

    selectQuery.prepare("SELECT * FROM tasks_info_database WHERE tasks_id = :task_id_in_data_base");
    selectQuery.bindValue(":task_id_in_data_base", task_id_in_data_base_1);

    if (selectQuery.exec() && selectQuery.next()) {
        QString list_of_persons = selectQuery.value("tasks_persons").toString();

        // Split the existing organizations
        QStringList existingpersons = list_of_persons.split(",");

        // Check if the organization to remove exists
        if (existingpersons.contains(remove_person_from_task)) {
            // Remove the organization
            existingpersons.removeAll(remove_person_from_task);

            // Join the organizations back into a string
            QString newListOfperson = existingpersons.join(",");

            // Update the row with the new list of organizations
            QSqlQuery updateQuery;
            updateQuery.prepare("UPDATE tasks_info_database SET tasks_persons = :new_tasks_persons WHERE tasks_id = :task_id_in_data_base_1");
            updateQuery.bindValue(":new_tasks_persons", newListOfperson);
            updateQuery.bindValue(":task_id_in_data_base_1", task_id_in_data_base_1);

            if (updateQuery.exec()) {
                qDebug() << "person removed successfully.";
            } else {
                qDebug() << "Failed to update row." << updateQuery.lastError();
            }
        } else {
            qDebug() << "person not found in the list.";
        }
    } else {
        qDebug() << "task not found or an error occurred." << selectQuery.lastError();
    }

}
//---------------------------
QVector<QString> myServer::getting_persons_of_task(QString &task_id)
{
    QString tasks_id_in_data_base = task_id;  // Set the actual username

    // CREATE TABLE "tasks_info_database" (
    //     "tasks_id"	TEXT,
    //     "task_text"	TEXT,
    //     "task_project"	TEXT,
    //     "task_person"	TEXT,
    //     "tasks_persons"	TEXT,
    //     "tasks_isdone"	TEXT
    //     , "task_priority"	INTEGER)

    QSqlQuery selectQuery;
    selectQuery.prepare("SELECT * FROM tasks_info_database WHERE tasks_id = :tasks_id_in_data_base");
    selectQuery.bindValue(":tasks_id_in_data_base", tasks_id_in_data_base);

    if (selectQuery.exec() && selectQuery.next()) {

        QString personString = selectQuery.value("tasks_persons").toString();

        // Split the teams using the comma delimiter
        QStringList personList = personString.split(",");

        // Convert QStringList to QVector<QString>
        QVector<QString> personVector = personList.toVector();

        // Use teamsVector as needed
        for(int i = 0;i<personVector.size();i++){
            qDebug() <<personVector[i];
        }

        qDebug() << "persons  Vector: " << personVector;
        return personVector;

    } else {
        qDebug() << "task not found or an error occurred." << selectQuery.lastError();
        QVector<QString> err = {""};
        return err;
    }
}

//----------------------------
void myServer::adding_comment_to_data_base(QString &comment_data)
{
    // CREATE TABLE "comment_info_database" (
    //     "comment_id"	TEXT,
    //     "comment_value"	TEXT,
    //     "comment_reply"	TEXT,
    //     "comment_task"	TEXT,
    //     "comment_person"	TEXT
    //     )

    QString data_recieved_by_socket_to_add_to_comment = comment_data;
    QStringList fields = data_recieved_by_socket_to_add_to_comment.split("*");
    QString id_comment_to_database = fields[1];

    QSqlQuery checkQuery;

    checkQuery.prepare("SELECT * FROM comment_info_database WHERE comment_id = :id_comment_to_database");
    checkQuery.bindValue(":id_comment_to_database", id_comment_to_database);

    if (checkQuery.exec() && checkQuery.next()) {
        qDebug() << "comment with the same id already exists in the database.";
    }

    else {

        QSqlQuery insertQuery;

        insertQuery.prepare("INSERT INTO comment_info_database (comment_id,comment_value, comment_reply, comment_task,comment_person) VALUES (?, ?, ?, ? , ?)");

        // Bind values for the insertion
        insertQuery.addBindValue(fields[1]); //comment_id
        insertQuery.addBindValue(fields[2]); //comment_value
        insertQuery.addBindValue(fields[3]); //comment_reply
        insertQuery.addBindValue(fields[4]); //comment_task
        insertQuery.addBindValue(fields[5]); //comment_person

        // Execute the insertion query
        if (insertQuery.exec()) {
            qDebug() << "comment added successfully.";
            // Sending feedback through socket that organization added to the database
        }
        else {
            qDebug() << "Could not add comment." <<insertQuery.lastError();
        }
    }
}

void myServer::chnaging_comment_id(QString &comment_id, QString &new_comment_id)
{


    //     "comment_id"	TEXT,
    //     "comment_value"	TEXT,
    //     "comment_reply"	TEXT,
    //     "comment_task"	TEXT,
    //     "comment_person"	TEXT
    //     )

    QSqlQuery checkQuery(mydb_comment);

    checkQuery.prepare("SELECT * FROM comment_info_database WHERE comment_id = :id_comment_to_database");
    checkQuery.bindValue(":id_comment_to_database", new_comment_id);

    if (checkQuery.exec() && checkQuery.next()) {
        qDebug() << "comment with the same id already exists in the database.";
        //feed back ....

    }


    else{

        QSqlQuery updateQuery;
        updateQuery.prepare("UPDATE comment_info_database SET comment_id = :new_comment_id WHERE comment_id = :commment_id_in_data_base");
        updateQuery.bindValue(":new_comment_id", new_comment_id);
        updateQuery.bindValue(":commment_id_in_data_base", comment_id);

        if (updateQuery.exec()) {
            qDebug() << "comment value updated successfully.";
            // You can add additional logic or feedback here
            //feed back should be handled here

        } else {
            qDebug() << "Could not update  comment value." << updateQuery.lastError();
            // You can handle the error or provide feedback here
            //feedback should be handled here
        }
    }


}

//---------------------
void myServer::changing_comment_value(QString &comment_id, QString &new_comment_value)
{
    // CREATE TABLE "comment_info_database" (
    //     "comment_id"	TEXT,
    //     "comment_value"	TEXT,
    //     "comment_reply"	TEXT,
    //     "comment_task"	TEXT,
    //     "comment_person"	TEXT
    //     )

    QString commment_id_in_data_base = comment_id;

    QSqlQuery updateQuery;
    updateQuery.prepare("UPDATE comment_info_database SET comment_value = :new_comment_value WHERE comment_id = :commment_id_in_data_base");
    updateQuery.bindValue(":new_comment_value", new_comment_value);
    updateQuery.bindValue(":commment_id_in_data_base", commment_id_in_data_base);

    if (updateQuery.exec()) {
        qDebug() << "comment value updated successfully.";
        // You can add additional logic or feedback here
        //feed back should be handled here

    } else {
        qDebug() << "Could not update  comment value." << updateQuery.lastError();
        // You can handle the error or provide feedback here
        //feedback should be handled here
    }

}

//-------------------------

void myServer::changing_comment_reply(QString &comment_id, QString &new_comment_reply)
{
    // CREATE TABLE "comment_info_database" (
    //     "comment_id"	TEXT,
    //     "comment_value"	TEXT,
    //     "comment_reply"	TEXT,
    //     "comment_task"	TEXT,
    //     "comment_person"	TEXT
    //     )

    QString commment_id_in_data_base = comment_id;

    QSqlQuery updateQuery;
    updateQuery.prepare("UPDATE comment_info_database SET comment_reply = :new_comment_reply WHERE comment_id = :commment_id_in_data_base");
    updateQuery.bindValue(":new_comment_reply", new_comment_reply);
    updateQuery.bindValue(":commment_id_in_data_base", commment_id_in_data_base);

    if (updateQuery.exec()) {
        qDebug() << "comment reply updated successfully.";
        // You can add additional logic or feedback here
        //feed back should be handled here

    } else {
        qDebug() << "Could not update  comment reply." << updateQuery.lastError();
        // You can handle the error or provide feedback here
        //feedback should be handled here
    }
}

//-------------------------
void myServer::chnaing_comment_task(QString &comment_id, QString &new_comment_task)
{
    // CREATE TABLE "comment_info_database" (
    //     "comment_id"	TEXT,
    //     "comment_value"	TEXT,
    //     "comment_reply"	TEXT,
    //     "comment_task"	TEXT,
    //     "comment_person"	TEXT
    //     )

    QString commment_id_in_data_base = comment_id;

    QSqlQuery updateQuery;
    updateQuery.prepare("UPDATE comment_info_database SET comment_task = :new_comment_task WHERE comment_id = :commment_id_in_data_base");
    updateQuery.bindValue(":new_comment_task", new_comment_task);
    updateQuery.bindValue(":commment_id_in_data_base", commment_id_in_data_base);

    if (updateQuery.exec()) {
        qDebug() << "comment task updated successfully.";
        // You can add additional logic or feedback here
        //feed back should be handled here

    } else {
        qDebug() << "Could not update  comment task." << updateQuery.lastError();
        // You can handle the error or provide feedback here
        //feedback should be handled here
    }

}
//-----------------------------
void myServer::chnaing_comment_person(QString &comment_id, QString &new_comment_person)
{
    // CREATE TABLE "comment_info_database" (
    //     "comment_id"	TEXT,
    //     "comment_value"	TEXT,
    //     "comment_reply"	TEXT,
    //     "comment_task"	TEXT,
    //     "comment_person"	TEXT
    //     )

    QString commment_id_in_data_base = comment_id;

    QSqlQuery updateQuery;
    updateQuery.prepare("UPDATE comment_info_database SET comment_person = :new_comment_person WHERE comment_id = :commment_id_in_data_base");
    updateQuery.bindValue(":new_comment_person", new_comment_person);
    updateQuery.bindValue(":commment_id_in_data_base", commment_id_in_data_base);

    if (updateQuery.exec()) {
        qDebug() << "comment person updated successfully.";
        // You can add additional logic or feedback here
        //feed back should be handled here

    } else {
        qDebug() << "Could not update  comment person." << updateQuery.lastError();
        // You can handle the error or provide feedback here
        //feedback should be handled here
    }
}

//-------------------------------------
QString myServer::getting_info_of_comment(QString &comment_id)
{
    // CREATE TABLE "comment_info_database" (
    //     "comment_id"	TEXT,
    //     "comment_value"	TEXT,
    //     "comment_reply"	TEXT,
    //     "comment_task"	TEXT,
    //     "comment_person"	TEXT
    //     )

    QString comment_id_in_data_base = comment_id;
    QString comment_info;

    QSqlQuery selectQuery(mydb_comment);
    selectQuery.prepare("SELECT * FROM comment_info_database WHERE comment_id = :comment_id_in_data_base");
    selectQuery.bindValue(":comment_id_in_data_base", comment_id_in_data_base);

    if (selectQuery.exec() && selectQuery.next()) {
        // Retrieve values from the query result

        QString id = selectQuery.value("comment_id").toString();
        QString value = selectQuery.value("comment_value").toString();
        QString reply = selectQuery.value("comment_reply").toString();
        QString task = selectQuery.value("comment_task").toString();
        QString person = selectQuery.value("comment_person").toString();

        // Construct user_info string in the desired format
        comment_info = QString("%1*%2*%3*%4*%5")
                           .arg(id, value, reply, task, person);

        qDebug() << comment_info;
        return comment_info;
        //return team_info;
        //socket_handle
    }
    else {
        qDebug() << "comment not found or an error occurred." << selectQuery.lastError();
        QString err = "";
        return err;
    }
}
