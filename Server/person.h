#ifndef PERSON_H
#define PERSON_H
#include <iostream>
#include <QString>
#include <QVector>
class Person
{
private:
    QString userName;
    QString passWord;
    QString pesonalName;
    QString eMail;
    QString recoveryWordAnimal;
    QString recoveryWordCity;
    QString recoveryWordColor;
    QVector<Organization> personOrganization;
    QVector<Team> personTeam;
    QVector<Project> personPeroject;
public:
    Person(QString UN,QString PW,QString PN,QString EM,QString RA,QString ,QString) {}
    virtual ~Person() {}
};

#endif // PERSON_H
