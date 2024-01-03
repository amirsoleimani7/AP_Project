#include "team.h"


QString Team::getTeamName() const
{
    return teamName;
}

Person Team::getAdmin() const
{
    return admin;
}

void Team::setAdmin(const Person &newAdmin)
{
    admin = newAdmin;
}

QVector<Person> Team::getTeamMembers() const
{
    return teamMembers;
}

QVector<Project> Team::getTeamProjects() const
{
    return teamProjects;
}

void Team::addMember(const Person &newMember)
{
    teamMembers.push_back(newMember);
}

void Team::addProject(const Project &newProject)
{
    teamProjects.push_back(newProject);
}

void Team::setTeamName(const QString &newTeamName)
{
    teamName = newTeamName;
}

bool Team::operator ==(const Team &other)
{
    return (teamId = other.teamId);
}

Team::Team(QString TN):teamName{TN},teamId{teamIdGenerator+lastTeamId}
{
    teamIdGenerator ++;
}

Team::Team(const Team &other)
{
    teamId = other.teamId;
    teamMembers = other.teamMembers;
    teamName = other.teamName;
    teamProjects = other.teamProjects;
    lastTeamId = other.lastTeamId;
    admin = other.admin;
}

Team::~Team()
{

}
