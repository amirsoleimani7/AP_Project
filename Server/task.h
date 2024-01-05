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
    QVector<Person> persons;
    bool isDone;
    //date
    int priority;

public:
    Task();
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
    QVector<Person> getPersons() const;
    void setPersons(const QVector<Person> &newPersons);
};

#endif // TASK_H
