#ifndef SIGNUP_H
#define SIGNUP_H

#include <QDialog>
#include <QMessageBox>
#include <QFile>
#include "socket_connection.h"

namespace Ui {
class Signup;
}

class Signup : public QDialog
{
    Q_OBJECT

public:

    explicit Signup(QWidget *parent = nullptr);
    ~Signup();

private slots:
    void on_pushButton_signup_clicked();

private:
    Ui::Signup *ui;
    socket_connection *socket;

};

#endif // SIGNUP_H
