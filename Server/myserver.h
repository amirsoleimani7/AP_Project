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

    //function for person ---------------- //sould work with id
    void change_user_personal_name(QString& name_in_data_base,QString &new_name_1);
    void add_person_to_data_base(QString &user_data);
    void change_user_email(QString& name_in_data_base,QString &new_email_1);
    void chnage_user_pass(QString& name_in_data_base,QString &new_pass_1);
    QString get_user_info(QString& name_in_data_base);
    bool check_for_pass_word(QString& name_in_data_base,QString& input_password);
    void add_organizations_to_person(QString& name_in_data_base,QString& organizations_name);
    void add_team_to_person(QString& name_in_data_base,QString& team_name);
    void add_project_to_person(QString& name_in_data_base,QString& project_name);
    void add_task_to_person(QString& name_in_data_base,QString& task_name);
    void remove_organization_from_person(QString& name_in_data_base,QString& organizations_name);
    void remove_team_from_person(QString& name_in_data_base,QString& team_name);
    void remove_project_from_person(QString& name_in_data_base_1,QString& project_name);
    void remove_task_from_person(QString& name_in_data_base,QString& task_name);
    QVector<QString> organizations_of_person(QString& name_in_data_base);
    QVector<QString> teams_of_person(QString& name_in_data_base);
    QVector<QString> task_of_person(QString& name_in_data_base);
    QVector<QString> projects_of_person(QString& name_in_data_base);
    //-------------------------
    //functions for organization
    void add_organization_to_data_base(QString& organization_data);
    void chnage_name_of_organization(QString& organization_id,QString& new_name_for_organization);
    void chnage_owner_of_organization(QString& organization_id,QString& new_owner_for_organization);
    void adding_teams_to_organization(QString& organization_id,QString& id_of_team_to_add);
    void adding_person_to_organization(QString& organization_id,QString& id_of_person_to_add);
    void removing_team_from_organization(QString& organization_id,QString& id_of_team_to_remove);
    void removing_person_from_organization(QString& organization_id,QString& id_of_person_to_remove);
    QString getting_info_of_organizatios(QString& organization_id);
    QVector<QString> get_team_of_organization(QString& organization_id);
    QVector<QString> get_person_of_organization(QString& organization_id);
    //--------------------------
    //team functions
    void add_team_to_data_base(QString& team_data);
    void change_name_of_team(QString& team_id,QString new_name);
    void change_admin_of_the_team(QString& team_id ,QString& new_name);
    void add_person_to_team(QString& team_id,QStrnig new_person);


private:
    void sendFile (QTcpSocket* socket,QString fileName);

private:
    Ui::myServer *ui;
    QSqlDatabase mydb_person;
    QSqlDatabase mydb_organization;
    QSqlDatabase mydb_team;

    QTcpServer *tcpServe;
    QList<QTcpSocket*> clientList;

};
#endif // MYSERVER_H
