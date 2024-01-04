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
    ui->stackedWidget->setCurrentWidget(ui->page_6);
}


void Dashboard::on_HamborBackBotton_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->page_5);
}

