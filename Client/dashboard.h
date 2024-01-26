#ifndef DASHBOARD_H
#define DASHBOARD_H

#include <QDialog>
#include "socket_connection.h"
#include <QString>
#include <QVector>
#include <vector>
#include <QDebug>
#include "myclient.h"
#include <custombutton.h>
namespace Ui {
class Dashboard;
}

class Dashboard : public QDialog
{
    Q_OBJECT

public:
    QString currentTask;
    QString CurrentUserName;
    QString CurrentOrganizationName;
    QString CurrentTeamName;
    QString CurrentProjectName;
    explicit Dashboard(QWidget *parent = nullptr,const QString& RefrenceUserName = "");
    ~Dashboard();
public slots:
    //explicit Dashboard(QWidget *parent = nullptr,QString RefrenceUserName = "");
public slots:
    void set_name_loged_in(QString& name);
    void clearLayout(QLayout* layout);
    void set_current_organization_name(const QString& organization_name);
    void set_cuurrent_team_name(const QString& team_name);
    void onMemberTeamButtonClicked();
    //updating HomeOrgListLayout
    void update_ProjectTaskListLayout_objects();
    void onTeamsInOrganizationButtonClicked();
    void update_HomeOrgListLayout_bottons();
    void update_HomeTeamListLayout_bottons();
    void update_HomeProjectListLayout_bottons();
    void update_projects_in_organization();
    void onProjecsInOrganizationButtonClicked();
    void add_person_to_team(QString& person_name);

    //void add_person_to_organization(QString& person_name);
    void onMemberInOrganizationButtonClicked();
    void onMemberSearchButtonClicked();
    void update_projects_of_team();
    void onProjectTeamButtonClicked();

    void onOrganizationButtonClicked();
    void onTeamButtonClicked();
    void onProjectButtonClicked();
    void onCommentButtonClicked();
    void onEditTaskButtonClicked();

    void update_teams_in_organization();
    void update_profile_of_user();

    void update_members_of_team();
    void add_person_to_organization(QString& person_name);
    void onProjectSearchButtonClicked();

    void onPersonSearchButtonClicked();
    void add_project_to_team(QString& project_name);

    void update_members_of_organization();

    void on_HomeNewPProjectBotton_clicked();

    void on_HomeNewOrgBotton_clicked();

    void on_HomeNewPPBackBotton_clicked();

    void on_HomeNewOrgBackBotton_clicked();

    void on_OneOrgHomeBotton_clicked();

    void on_HomeProfileBackBotton_clicked();

    void on_HomeProfileBotton_clicked();

    void on_OneOrgEditOrgBotton_clicked();

    void on_OneOrgAddNewTeamBotton_clicked();

    void on_OneOrgDeleteOrgBotton_clicked();

    void on_OrgEditPageBackBotton_clicked();

    void on_OrgNewTeamBackBotton_clicked();

    //void on_oneOrgButton_4_clicked();

    void on_OneTeamButton_10_clicked();

    void on_TeamEditBotton_clicked();

    void on_TeamEditBackBotton_clicked();

    void on_TeamAddProject_clicked();

    void on_TeamCreateProject_clicked();

    void on_TeamDeleteTeamBotton_clicked();

    void on_TeamHomeButton_clicked();

    void on_TeamAddPBackButton_clicked();

    void on_TeamCreatPBackButton_clicked();

    void on_SomeTeamButton_12_clicked();

    void on_ProjectNewTaskBackButton_clicked();

    void on_ProjectNewTaskButton_clicked();

    void on_ProjectHomeButton_clicked();

    void on_SomeProjectButton_17_clicked();

    void on_SomeProjectButton_2_clicked();

    void on_SomeProjectButton_14_clicked();

    void on_pushButton_clicked();

private slots:
    void on_HomeProfileChangeButton_clicked();

    void on_HomeNewPPCreatBotton_clicked();

    void on_HomeNewOrgCreatBotton_clicked();

    void on_search_for_project_clicked();

    void on_TeamChangeNameBotton_clicked();

    void on_searchForUserNameToAddToTeam_clicked();

    void on_TeamDeletingMemberBotton_clicked();

    void on_TeamChangeAdminBotton_clicked();

    void on_CreateNewTeamBotton_clicked();

    void on_OrgChangeNameBotton_clicked();

    void on_pushButton_search_for_new_member_for_org_clicked();

    void on_OrgDeleteMemberBotton_clicked();

    void on_OrgChangeOwnerBotton_clicked();

    void on_HomeOrgFilterBotton_clicked();

    void on_HomeTeamFilterBotton_clicked();

    void on_pushButton_create_new_project_clicked();

private:
    Ui::Dashboard *ui;
    socket_connection* socket;

};

#endif // DASHBOARD_H
