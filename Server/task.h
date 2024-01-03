#ifndef TASK_H
#define TASK_H
#include <QString>

class Task
{
private:
    static int taskIdGenerator;
    const int taskId;
    int lastTaskId;
    QString taskText;
    Project taskProject;
    //date
    int priority;

public:
    Task();
};

#endif // TASK_H
