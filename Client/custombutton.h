#ifndef CUSTOMBUTTON_H
#define CUSTOMBUTTON_H
#include <QPushButton>
#include <QString>
#include <QWidget>

class CustomButton :public QPushButton
{
public:
    QString parent;
    QPushButton *Button;
    CustomButton(QWidget *Prnt,QString inParent,QString inButton);
};


#endif // CUSTOMBUTTON_H
