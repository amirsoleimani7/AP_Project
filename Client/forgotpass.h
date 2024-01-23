#ifndef FORGOTPASS_H
#define FORGOTPASS_H

#include <QDialog>
#include <QMessageBox>
#include "socket_connection.h"
#include <QString>
namespace Ui {
class ForgotPass ;
}

class ForgotPass : public QDialog
{
    Q_OBJECT

public:
    explicit ForgotPass(QWidget *parent = nullptr);
    ~ForgotPass();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_change_pass_word_clicked();

private:
    Ui::ForgotPass *ui;
    socket_connection *socket;
    bool flag_change = true;
};

#endif // FORGOTPASS_H
