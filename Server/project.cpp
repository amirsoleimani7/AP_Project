#include "project.h"

int Project::projectIdGenerator = 1;

QString Project::getProjectName() const
{
    return projectName;
}

int Project::getProjectType() const
{
    return projectType;
}

Person Project::getProjectPerson() const
{
    return projectPerson;
}

QVector<QString> Project::getProjectTeams() const
{
    return projectTeams;
}

QVector<QString> Project::getProjectTasks() const
{
    return projectTasks;
}

int Project::getLastProjectId() const
{
    return lastProjectId;
}

void Project::setLastProjectId(int newLastProjectId)
{
    lastProjectId = newLastProjectId;
}

int Project::getProjectId() const
{
    return projectId;
}

void Project::setProjectName(const QString &newProjectName)
{
    projectName = newProjectName;
}

void Project::setProjectType(int newProjectType)
{
    projectType = newProjectType;
}

void Project::setProjectPerson(const Person &newProjectPerson)
{
    projectPerson = newProjectPerson;
}

bool Project::operator ==(const Project &other)
{
    return (projectId == other.projectId);
}

Project::Project()
{

}

Project::Project(QString PN, int PT):projectName{PN},projectType{PT},projectId{projectIdGenerator + lastProjectId}
{
    projectIdGenerator ++;
}

Project::Project(const Project &other)
{
    projectId = other.projectId;
    projectName = other.projectName;
    projectPerson = other.projectPerson;
    projectTasks = other.projectTasks;
    projectTeams = other.projectTeams;
    projectType = other.projectType;
    lastProjectId = other.lastProjectId;
}

Project::~Project()
{

}
