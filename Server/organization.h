#ifndef ORGANIZATION_H
#define ORGANIZATION_H

#include <iostream>
#include <QString>
#include <vector>
#include <QVector>
#include "person.h"
#include "team.h"
#include <QDebug>



class Organization
{
private:

    QString organizationName;
    static int organizationIdGenerator;
    const int organizationId;
    int lastOrganizationId;
    QVector<Person> membersInOrganization;
    QVector<Team> TeamsInOrganization;

public:

    bool operator==(const Organization& organizationGiven);

    void setlastOrganizationId(int x);
    Organization(QString organizatonName);
    QString getOrganizationName();
    void setOrganizationName(const QString& givenName);

    void addMemberToOrganization(const Person& givenPersonToAddName);
    void addTeamToOrganization(const Team& givenTeamToAddName);

    void removeMemberFromOrganization(const Person& givenPersonToRemove);
    void removeTeamFromOrganization(const Team& givenTeamToRemove);

    QVector<Person> getmembersInOrganization();
    QVector<Team> getTeamsInOrganization();

};

#endif // ORGANIZATION_H
