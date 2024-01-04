#ifndef TASK_H
#define TASK_H
#include <QString>
#include <QDateTime>
#include "project.h"
#include "person.h"

class Task
{
private:
    static int taskIdGenerator;
    int taskId;
    int lastTaskId;
    QString taskText;
    Project taskProject;
    Person taskPerson;
    bool isDone;
    QDateTime taskDeadLine;
    int priority;

public:
    Task();
    Task(Project pro,QString TT,Person pers,int prio,QDateTime dat);
    Task(const Task& other);
    int getTaskId() const;
    int getLastTaskId() const;
    QString getTaskText() const;
    Project getTaskProject() const;
    Person getTaskPerson() const;
    bool getIsDone() const;
    int getPriority() const;
    void setTaskText(const QString &newTaskText);
    void setPriority(int newPriority);
    void setTaskPerson(const Person &newTaskPerson);
    void Done();
    void UnDone();
    bool operator ==(const Task& other);
    QDateTime getTaskDeadLine() const;
    void setTaskDeadLine(const QDateTime &newTaskDeadLine);
};

#endif // TASK_H
