#include "task.h"

int Task::taskIdGenerator = 1;
int Task::getTaskId() const
{
    return taskId;
}

int Task::getLastTaskId() const
{
    return lastTaskId;
}

QString Task::getTaskText() const
{
    return taskText;
}

Project Task::getTaskProject() const
{
    return taskProject;
}

int Task::getPriority() const
{
    return priority;
}

void Task::setTaskText(const QString &newTaskText)
{
    taskText = newTaskText;
}

void Task::setPriority(int newPriority)
{
    priority = newPriority;
}

void Task::setTaskPerson(const Person &newTaskPerson)
{
    taskPerson = newTaskPerson;
}

void Task::Done()
{
    isDone = true;
}

void Task::UnDone()
{
    isDone = false;
}

bool Task::operator ==(const Task &other)
{
    return (taskId == other.taskId);
}

Person Task::getTaskPerson() const
{
    return taskPerson;
}

bool Task::getIsDone() const
{
    return isDone;
}

Task::Task(Project pro, QString TT,Person pers,int prio):taskId(taskIdGenerator+lastTaskId),taskProject(pro),taskText(TT),taskPerson(pers),priority(prio)
{
    taskIdGenerator++;
    isDone = false;
}

Task::Task(const Task &other)
{
    taskId = other.taskId;
    taskPerson = other.taskPerson;
    taskProject = other.taskProject;
    taskText = other.taskText;
}
