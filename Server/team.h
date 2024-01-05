#ifndef TEAM_H
#define TEAM_H
#include <QString>
#include <QVector>
#include "person.h"
#include "project.h"

class Team
{
private:
    static int teamIdGenerator;
    int teamId;
    int lastTeamId;
    QString teamName;
    Person admin;
    QVector<Person> teamMembers;
    QVector<Project> teamProjects;

public:
    Team(QString TN);
    Team(const Team& other);
    ~Team();
    QString getTeamName() const;
    Person getAdmin() const;
    void setAdmin(const Person &newAdmin);
    QVector<Person> getTeamMembers() const;
    QVector<Project> getTeamProjects() const;
    void addMember (const Person &newMember);
    void addProject (const Project &newProject);
    void setTeamName(const QString &newTeamName);
    bool operator ==(const Team& other);
};

#endif // TEAM_H
