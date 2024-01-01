#include "myclient.h"
#include "ui_myclient.h"

myClient::myClient(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::myClient)
{
    ui->setupUi(this);
}

myClient::~myClient()
{
    delete ui;
}
