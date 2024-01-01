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

    bool can_add_the_member = true;
    for(int i = 0;i<membersInOrganization.size();i++){
        if(membersInOrganization[i].getUserName() == givenPerson){
            can_add_the_member = false;
            qDebug() << "can not add member : " <<givenPerson <<"\n";
        }
    }

    if(can_add_the_member){
        membersInOrganization.push_back(givenPerson);
        qDebug() << "new member added : " <<givenPerson <<"\n";
    }
}


void Organization::addTeamToOrganization(const QString& givenTeam)
{

    bool can_add_the_team = true;
    for(int i = 0;i<TeamsInOrganization.size();i++){
        if(TeamsInOrganization[i].getTeamName() == givenTeam){ //a getter function for team_name
            can_add_the_team = false;
            qDebug() << "can not add team : " <<givenTeam <<"\n";
        }
    }

    if(can_add_the_team){
        TeamsInOrganization.push_back(givenTeam);
        qDebug() << "new team added : " <<givenTeam <<"\n";
    }

}

// void Organization::removeMemberFromOrganization(const QString& givenPersonToRemove)
// {

//     bool can_remove_the_member = false;
//     for(int i = 0;i<membersInOrganization.size();i++){
//         if(membersInOrganization[i].getUserName() == givenPersonToRemove){ //a getter function for getname
//             can_remove_the_member = true;
//             //qDebug() << "can not add member : " <<givenPersonToRemove <<"\n";
//         }
//     }

//     if(!can_remove_the_member){
//         for(int i = 0;i<membersInOrganization.size();i++){
//             //if(membersInOrganization[i].getUserName() == givenPersonToRemove){ //a getter function for getname
//             //membersInOrganization.remove(membersInOrganization.begin(),membersInOrganization.end(),find(givenPersonToRemove));
//         //}
//     }
//         qDebug() << "member removed : " <<givenPersonToRemove <<"\n";
//     }
//     else{
//         qDebug() << "there is no member: " <<givenPersonToRemove <<"\n";

//     }
// }

// void Organization::removeTeamFromOrganization(const QString& givenTeamToRemove)
// {

//     bool can_remove_the_team = false;
//     for(int i = 0;i<TeamsInOrganization.size();i++){
//         if(TeamsInOrganization[i].getTeamName() == givenTeamToRemove){ //a getter function for team_name
//             can_add_the_team = false;
//             qDebug() << "can not add member : " <<givenTeamToRemove <<"\n";
//         }
//     }

//     if(can_add_the_team){
//         TeamsInOrganization.push_back(givenTeamToRemove);
//         qDebug() << "new member added : " <<givenTeamToRemove <<"\n";
//     }
// }

QVector<QString> Organization::getmembersInOrganization()
{
    return membersInOrganization;

}

QVector<QString> Organization::getTeamsInOrganization()
{
    return TeamsInOrganization;
}

