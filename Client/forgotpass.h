#ifndef FORGOTPASS_H
#define FORGOTPASS_H

#include <QDialog>
#include <QMessageBox>
namespace Ui {
class ForgotPass;
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
    bool flag_change = false;
};

#endif // FORGOTPASS_H
