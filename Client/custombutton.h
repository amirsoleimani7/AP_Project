#ifndef CUSTOMBUTTON_H
#define CUSTOMBUTTON_H
#include <QPushButton>
#include <QString>
#include <QWidget>
class CustomButton
{
public:
    QString parent;
    QPushButton *Button;
    CustomButton(QWidget *prnt,QString task_id,QString inbotton);
};


#endif // CUSTOMBUTTON_H
