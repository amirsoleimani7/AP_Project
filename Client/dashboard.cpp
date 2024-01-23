#include "dashboard.h"
#include "ui_dashboard.h"

Dashboard::Dashboard(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Dashboard)
{
    ui->setupUi(this);
}

Dashboard::~Dashboard()
{
    delete ui;
}


void Dashboard::on_HomeNewPProjectBotton_clicked()
{
    ui->HomeSideStack->setCurrentWidget(ui->HomeNewPProjectPage);
}


void Dashboard::on_HomeNewOrgBotton_clicked()
{
    ui->HomeSideStack->setCurrentWidget(ui->HomeNewOrganizationPage);
}


void Dashboard::on_HomeNewPPBackBotton_clicked()
{
    ui->HomeSideStack->setCurrentWidget(ui->HomeSideMainPage);
}


void Dashboard::on_HomeNewOrgBackBotton_clicked()
{
    ui->HomeSideStack->setCurrentWidget(ui->HomeSideMainPage);
}


void Dashboard::on_OneOrgHomeBotton_clicked()
{
    ui->MainStack->setCurrentWidget(ui->Homepage);
}


void Dashboard::on_HomeProfileBackBotton_clicked()
{
    ui->HomeSideStack->setCurrentWidget(ui->HomeSideMainPage);
}


void Dashboard::on_HomeProfileBotton_clicked()
{
    ui->HomeSideStack->setCurrentWidget(ui->HomeProfilePage);
}


void Dashboard::on_OneOrgEditOrgBotton_clicked()
{
    ui->OneOrgSideStack->setCurrentWidget(ui->OneOrgEditOrgPage);
}


void Dashboard::on_OneOrgAddNewTeamBotton_clicked()
{
    ui->OneOrgSideStack->setCurrentWidget(ui->OneOrgNewTeamPage);
}


void Dashboard::on_OneOrgDeleteOrgBotton_clicked()
{
    ui->MainStack->setCurrentWidget(ui->Homepage);
}


void Dashboard::on_OrgEditPageBackBotton_clicked()
{
    ui->OneOrgSideStack->setCurrentWidget(ui->OneOrgSideMainPage);
}


void Dashboard::on_OrgNewTeamBackBotton_clicked()
{
    ui->OneOrgSideStack->setCurrentWidget(ui->OneOrgSideMainPage);
}


void Dashboard::on_oneOrgButton_4_clicked()
{
    ui->MainStack->setCurrentWidget(ui->OneOrgPage);
}


void Dashboard::on_OneTeamButton_10_clicked()
{
    ui->MainStack->setCurrentWidget(ui->TeamPage);
}


void Dashboard::on_TeamEditBotton_clicked()
{
    ui->TeamSideStack->setCurrentWidget(ui->TeamEditPage);
}


void Dashboard::on_TeamEditBackBotton_clicked()
{
    ui->TeamSideStack->setCurrentWidget(ui->TeamSideMainPage);
}


void Dashboard::on_TeamAddProject_clicked()
{
    ui->TeamSideStack->setCurrentWidget(ui->TeamAddProjectPage);
}


void Dashboard::on_TeamCreateProject_clicked()
{
    ui->TeamSideStack->setCurrentWidget(ui->TeamCreatProjectPage);
}


void Dashboard::on_TeamDeleteTeamBotton_clicked()
{
    ui->MainStack->setCurrentWidget(ui->Homepage);
}


void Dashboard::on_TeamHomeButton_clicked()
{
    ui->MainStack->setCurrentWidget(ui->Homepage);
}


void Dashboard::on_TeamAddPBackButton_clicked()
{
    ui->TeamSideStack->setCurrentWidget(ui->TeamSideMainPage);
}


void Dashboard::on_TeamCreatPBackButton_clicked()
{
    ui->TeamSideStack->setCurrentWidget(ui->TeamSideMainPage);
}

