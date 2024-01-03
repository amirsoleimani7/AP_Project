#ifndef TASK_H
#define TASK_H
#include <QString>
#include "project.h"
#include "person.h"

class Task
{
private:
    static int taskIdGenerator;
    const int taskId;
    int lastTaskId;
    QString taskText;
    Project taskProject;
    Person taskPerson;
    bool isDone;
    //date
    int priority;

public:
    Task(Project pro,QString TT,Person pers,int prio);
    int getTaskId() const;
    int getLastTaskId() const;
    QString getTaskText() const;
    Project getTaskProject() const;
    int getPriority() const;
    void setTaskText(const QString &newTaskText);
    void setPriority(int newPriority);
    void setTaskPerson(const Person &newTaskPerson);
    void Done();
    void UnDone();
    Person getTaskPerson() const;
    bool getIsDone() const;
};

#endif // TASK_H
