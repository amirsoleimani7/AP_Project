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
    ui->HomeSideStack->setCurrentWidget(ui->HomeCloseHamborPage);
}


void Dashboard::on_HomeNewOrgBackBotton_clicked()
{
    ui->HomeSideStack->setCurrentWidget(ui->HomeCloseHamborPage);
}

