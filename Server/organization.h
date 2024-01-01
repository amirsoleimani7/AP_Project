#ifndef ORGANIZATION_H
#define ORGANIZATION_H

#include <iostream>
#include <QString>
#include <vector>
#include <QVector>

class Organization

{

private:

    QString organizationName;
    QVector<Person> membersInOrganization;
    QVector<Team> TeamsInOrganization;

public:

    Organization(QString organizatonName);
    QString getOrganizationName();
    void setOrganizationName(QString givenName);
    void addMemberToOrganization(const Person& givenPersonToAdd);
    void addTeamToOrganization(const Team& givenTeamToAdd);
    void removeMemberFromOrganization(const Person& givelPersonToRemove);
    void removeTeamFromOrganization(const Team& givenTeamToRemove);

};

#endif // ORGANIZATION_H
