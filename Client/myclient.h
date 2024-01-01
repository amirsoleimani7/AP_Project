#ifndef MYCLIENT_H
#define MYCLIENT_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class myClient;
}
QT_END_NAMESPACE

class myClient : public QMainWindow
{
    Q_OBJECT

public:
    myClient(QWidget *parent = nullptr);
    ~myClient();

private:
    Ui::myClient *ui;
};
#endif // MYCLIENT_H
