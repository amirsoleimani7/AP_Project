#include "myserver.h"
#include "ui_myserver.h"

myServer::myServer(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::myServer)

{
    ui->setupUi(this);
}

//commect added
//commecnt 2 on branch amir
myServer::~myServer()

{
    delete ui;
}

