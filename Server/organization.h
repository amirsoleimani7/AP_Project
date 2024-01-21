#ifndef ORGANIZATION_H
#define ORGANIZATION_H

#include <iostream>
#include <QString>
#include <vector>
#include <QVector>
#include "person.h"
#include "team.h"
#include <QDebug>
#include "myserver.h"

class Organization
{
private:

    static int organizationIdGenerator;
    int lastOrganizationId;
    int organizationId;
    Person organizationOwner;
    QString organizationName;
    QVector<Person> membersInOrganization;
    QVector<Team> TeamsInOrganization;

public:

    Organization(QString organizatonName,Person& organization_owner);
    Organization(const Organization& other);

    int getLastOrganizationId() const;
    int getOrganizationId() const;
    QString getOrganizationName();
    QVector<Person> getmembersInOrganization();
    QVector<Team> getTeamsInOrganization();

    void setOrganizationName(const QString& givenName);
    void setOrganizationId(int newOrganizationId);

    void addMemberToOrganization(const Person& givenPersonToAddName);
    void addTeamToOrganization(const Team& givenTeamToAddName);

    void removeMemberFromOrganization(const Person& givenPersonToRemove);
    void removeTeamFromOrganization(const Team& givenTeamToRemove);

    bool operator==(const Organization& organizationGiven);

};

#endif // ORGANIZATION_H
