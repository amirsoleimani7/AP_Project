#include "team.h"


QString Team::getTeamName() const
{
    return teamName;
}

QString Team::getAdmin() const
{
    return admin;
}

void Team::setAdmin(const QString &newAdmin)
{
    admin = newAdmin;
}

QVector<QString> Team::getTeamMembers() const
{
    return teamMembers;
}

QVector<QString> Team::getTeamProjects() const
{
    return teamProjects;
}

void Team::addMember(const QString &newMember)
{
    teamMembers.push_back(newMember);
}

void Team::addProject(const QString &newProject)
{
    teamProjects.push_back(newProject);
}

void Team::setTeamName(const QString &newTeamName)
{
    teamName = newTeamName;
}

Team::Team(QString TN):teamName{TN}
{

}

Team::~Team()
{

}
