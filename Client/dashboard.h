#ifndef DASHBOARD_H
#define DASHBOARD_H

#include <QDialog>
#include "socket_connection.h"
#include <QString>
#include <QVector>
#include <vector>
#include <QDebug>
#include "myclient.h"
namespace Ui {
class Dashboard;
}

class Dashboard : public QDialog
{
    Q_OBJECT

public:
    QString CurrentUserName;
    explicit Dashboard(QWidget *parent = nullptr,QString RefrenceUserName = "");
    ~Dashboard();
public slots:
    void set_name_loged_in(QString& name);
    void clearLayout(QLayout* layout);
    //updating HomeOrgListLayout
    void update_HomeOrgListLayout_bottons();
    void update_HomeTeamListLayout_bottons();
    void update_HomeProjectListLayout_bottons();

    void onOrganizationButtonClicked();
    void onTeamButtonClicked();
    void onProjectButtonClicked();


    void update_profile_of_user();

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

private:
    Ui::Dashboard *ui;
    socket_connection* socket;
    QString name_looged_in;

};

#endif // DASHBOARD_H
