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

void Dashboard::on_HamborBotton_clicked()
{
    ui->HomeSideStack->setCurrentWidget(ui->HomeOpenHamborPage);
}


void Dashboard::on_HamborBackBotton_clicked()
{
    ui->HomeSideStack->setCurrentWidget(ui->HomeCloseHamborPage);
}

