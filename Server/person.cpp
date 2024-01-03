#include "person.h"

int Person::personIdGenerator = 1;

QString Person::getUserName() const
{
    return userName;
}

QString Person::getPassWord() const
{
    return passWord;
}

void Person::setPassWord(const QString &newPassWord)
{
    passWord = newPassWord;
}

QString Person::getPersonalName() const
{
    return personalName;
}

void Person::setPersonalName(const QString &newPersonalName)
{
    personalName = newPersonalName;
}

QString Person::getEMail() const
{
    return eMail;
}

void Person::setEMail(const QString &newEMail)
{
    eMail = newEMail;
}

QString Person::getRecoveryWordAnimal() const
{
    return recoveryWordAnimal;
}

QString Person::getRecoveryWordCity() const
{
    return recoveryWordCity;
}

QString Person::getRecoveryWordColor() const
{
    return recoveryWordColor;
}

QVector<QString> Person::getPersonPeroject() const
{
    return personPeroject;
}

QVector<QString> Person::getPersonTeam() const
{
    return personTeam;
}
QVector<QString> Person::getPersonOrganization() const
{
    return personOrganization;
}

void Person::addProject(QString newProject)
{
    personPeroject.push_back(newProject);
}

void Person::addTeam(QString newTeam)
{
    personTeam.push_back(newTeam);
}

void Person::addOrganization(QString newOrganization)
{
    personOrganization.push_back(newOrganization);
}

int Person::getLastPersonId() const
{
    return lastPersonId;
}

void Person::setLastPersonId(int newLastPersonId)
{
    lastPersonId = newLastPersonId;
}

int Person::getPersonId() const
{
    return personId;
}

bool Person::operator ==(const Person &other)
{
    return(personId == other.personId);
}

bool Person::operator =(const Person &other)
{
    lastPersonId = other.lastPersonId;
    personalName = other.personalName;
    personId = other.personId;
    personOrganization = other.personOrganization;
    personPeroject = other.personPeroject;
    personTeam = other.personTeam;
    userName = other.userName;
    passWord = other.passWord;
    eMail = other.eMail;
    recoveryWordAnimal = other.recoveryWordAnimal;
    recoveryWordCity = other.recoveryWordCity;
    recoveryWordColor = other.recoveryWordColor;
}

Person::Person()
{

}

Person::Person(QString UN, QString PW, QString PN, QString EM, QString RA, QString RC, QString RCO):userName{UN},passWord{PW},
    personalName{PN},eMail{EM},recoveryWordAnimal{RA},recoveryWordCity{RC},recoveryWordColor{RCO},
    personId(personIdGenerator+lastPersonId)
{
    personIdGenerator ++;
}

Person::Person(const Person &other){
    lastPersonId = other.lastPersonId;
    personalName = other.personalName;
    personId = other.personId;
    personOrganization = other.personOrganization;
    personPeroject = other.personPeroject;
    personTeam = other.personTeam;
    userName = other.userName;
    passWord = other.passWord;
    eMail = other.eMail;
    recoveryWordAnimal = other.recoveryWordAnimal;
    recoveryWordCity = other.recoveryWordCity;
    recoveryWordColor = other.recoveryWordColor;
}

Person::~Person()
{

}
