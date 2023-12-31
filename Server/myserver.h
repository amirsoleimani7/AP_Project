#ifndef MYSERVER_H
#define MYSERVER_H

#include <QMainWindow>

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

private:
    Ui::myServer *ui;
};
#endif // MYSERVER_H
