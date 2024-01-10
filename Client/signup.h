#ifndef SIGNUP_H
#define SIGNUP_H

#include <QDialog>
#include <QMessageBox>
#include <QFile>




namespace Ui {
class Signup;
}

class Signup : public QDialog
{
    Q_OBJECT

public:
    explicit Signup(QWidget *parent = nullptr);
    ~Signup();
    void witing_instructions(QString& instruction);


private slots:
    void on_pushButton_signup_clicked();

private:
    Ui::Signup *ui;
};

#endif // SIGNUP_H
