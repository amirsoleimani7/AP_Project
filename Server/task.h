#ifndef TASK_H
#define TASK_H
#include <QString>
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
    //date
    int priority;

public:
<<<<<<< HEAD

=======
    Task();
>>>>>>> 8116a58548394d78a41a9c898a9c3e47639dc91e
    Task(Project pro,QString TT,Person pers,int prio);
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
};

#endif // TASK_H
