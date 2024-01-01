#include "organization.h"

Organization::Organization(QString organizatonName):organizationName(organizatonName)
{

}

QString Organization::getOrganizationName()
{
    return organizationName;
}

void Organization::setOrganizationName(const QString& givenName)
{
    organizationName = givenName;
}

void Organization::addMemberToOrganization(const QString& givenPerson)
{

}

void Organization::addTeamToOrganization(const QString& givenTeam)
{

}

void Organization::removeMemberFromOrganization(const QString& givenPersonToRemove)
{

}

void Organization::removeTeamFromOrganization(const QString& givenTeamToRemove)
{

}

