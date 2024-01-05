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


QDateTime Task::getTaskDeadLine() const
{
    return taskDeadLine;
}

void Task::setTaskDeadLine(const QDateTime &newTaskDeadLine)
{
    taskDeadLine = newTaskDeadLine;

QVector<Person> Task::getPersons() const
{
    return persons;
}

void Task::setPersons(const QVector<Person> &newPersons)
{
    persons = newPersons;
}

Task::Task()
{

}

Task::Task(Project pro, QString TT,Person pers,int prio, QDateTime dat):taskId(taskIdGenerator+lastTaskId),
    taskProject(pro),taskText(TT),taskPerson(pers),priority(prio), taskDeadLine(dat)
{
    taskIdGenerator++;
    isDone = false;
}

Task::Task(const Task &other)
{
    lastTaskId = other.lastTaskId;
    taskId = other.taskId;
    taskPerson = other.taskPerson;
    taskProject = other.taskProject;
    taskText = other.taskText;
    taskDeadLine = other.taskDeadLine;
}
