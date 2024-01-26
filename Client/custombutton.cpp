#include "custombutton.h"

CustomButton::CustomButton(QWidget *Prnt, QString inParent, QString inButton):QPushButton(inButton,Prnt)
{
    this->parent = inParent;
}
