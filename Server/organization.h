#ifndef ORGANIZATION_H
#define ORGANIZATION_H

#include <iostream>
#include <QString>
#include <vector>
#include <QVector>
#include "person.h"


class Organization

{
private:

    QString organizationName;
    QVector<QString> membersInOrganization;
    QVector<QString> TeamsInOrganization;

public:

    Organization(QString organizatonName);
    QString getOrganizationName();
    void setOrganizationName(const QString& givenName);
    void addMemberToOrganization(const QString& givenPersonToAddName);
    void addTeamToOrganization(const QString& givenTeamToAddName);
    void removeMemberFromOrganization(const QString& givenPersonToRemove);
    void removeTeamFromOrganization(const QString& givenTeamToRemove);

};

#endif // ORGANIZATION_H
