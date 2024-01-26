#include "custombutton.h"

CustomButton::CustomButton(QWidget *prnt,QString task_id,QString inbotton):{
    Button = new QPushButton(inbotton,prnt);
    this->parent = task_id;
}
