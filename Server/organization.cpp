#include "organization.h"
#include "person.h"

int Organization::organizationIdGenerator = 1;

void Organization::setlastOrganizationId(int x)
{
    lastOrganizationId = x;
}

Organization::Organization(QString organizatonName):organizationId(organizationIdGenerator+lastOrganizationId),organizationName(organizatonName)
{
    organizationIdGenerator++;
}

QString Organization::getOrganizationName()
{
    return organizationName;
}

void Organization::setOrganizationName(const QString& givenName)
{
    organizationName = givenName;
}

void Organization::addMemberToOrganization(const Person& givenPerson)
{

    bool can_add_the_member = true;

    for(int i = 0;i<membersInOrganization.size();i++){
        if(membersInOrganization[i] == givenPerson){
            can_add_the_member = false;
            qDebug() << "can not add member : " << givenPerson.getUserName() <<"\n";
        }
    }

    if(can_add_the_member){
        membersInOrganization.push_back(givenPerson);
        qDebug() << "new member added : " << givenPerson.getUserName() <<"\n";
    }
}


void Organization::addTeamToOrganization(const Team& givenTeam)
{

    bool can_add_the_team = true;
    for(int i = 0;i<TeamsInOrganization.size();i++){
        if(TeamsInOrganization[i] == givenTeam){ //a getter function for team_name
            can_add_the_team = false;
            qDebug() << "can not add team : " << givenTeam.getTeamName() <<"\n";
        }
    }

    if(can_add_the_team){
        TeamsInOrganization.push_back(givenTeam);
        qDebug() << "new team added : " << givenTeam.getTeamMembers() <<"\n";
    }

}

void Organization::removeMemberFromOrganization(const Person& givenPersonToRemove)
{

    bool can_remove_the_member = false;
    for(int i = 0;i<membersInOrganization.size();i++){
        if(membersInOrganization[i] == givenPersonToRemove){ //a getter function for getname
            can_remove_the_member = true;
        }
    }

    if(!can_remove_the_member){
        for(int i = 0;i<membersInOrganization.size();i++){
            if(membersInOrganization[i]. == givenPersonToRemove){ //a getter function for getname
                membersInOrganization.erase(membersInOrganization.begin()+i); //not sure to use erase or remove
                qDebug() << "member removed : " << givenPersonToRemove.getUserName() <<"\n";
            }
        }
    }

    else{
        qDebug() << "there is no member: " << givenPersonToRemove.getUserName() <<"\n";
    }
}

void Organization::removeTeamFromOrganization(const Team& givenTeamToRemove)
{


    bool can_remove_the_team = false;
    for(int i = 0;i<TeamsInOrganization.size();i++){
        if(TeamsInOrganization[i] == givenTeamToRemove){ //a getter function for getname
            can_remove_the_team = true;
        }
    }

    if(!can_remove_the_team){
        for(int i = 0;i<TeamsInOrganization.size();i++){
            if(TeamsInOrganization[i] == givenTeamToRemove){ //a getter function for getname
                TeamsInOrganization.erase(TeamsInOrganization.begin()+i); //not sure to use erase or remove
                qDebug() << "team removed : " << givenTeamToRemove.getTeamName() <<"\n";
            }
        }
    }

    else{
        qDebug() << "there is no team : " << givenTeamToRemove.getTeamName() <<"\n";
    }

}

QVector<Person> Organization::getmembersInOrganization()
{
    return membersInOrganization;

}

QVector<Team> Organization::getTeamsInOrganization()
{
    return TeamsInOrganization;
}

