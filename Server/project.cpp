#include "project.h"


QString Project::getProjectName() const
{
    return projectName;
}

int Project::getProjectType() const
{
    return projectType;
}

QString Project::getProjectPerson() const
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

Project::Project(QString PN, int PT):projectName{PN},projectType{PT}
{

}

Project::~Project()
{

}
