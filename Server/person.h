#ifndef PERSON_H
#define PERSON_H
#include <iostream>
#include <QString>
#include <QVector>
//#include "organization.h"
class Person
{
private:
    static int personIdGenerator;
    int lastPersonId;
    int personId;
    QString userName;
    QString passWord;
    QString personalName;
    QString eMail;
    QString recoveryWordAnimal;
    QString recoveryWordCity;
    QString recoveryWordColor;
    QVector<QString> personOrganization;
    QVector<QString> personTeam;
    QVector<QString> personPeroject;
public:
    Person();
    Person(QString UN,QString PW,QString PN,QString EM,QString RA,QString RC,QString RCO);
    Person(const Person& other);
    virtual ~Person();
    QString getUserName() const;
    QString getPassWord() const;
    void setPassWord(const QString &newPassWord);
    QString getPersonalName() const;
    void setPersonalName(const QString &newPersonalName);
    QString getEMail() const;
    void setEMail(const QString &newEMail);
    QString getRecoveryWordAnimal() const;
    QString getRecoveryWordCity() const;
    QString getRecoveryWordColor() const;
    QVector<QString> getPersonPeroject() const;
    QVector<QString> getPersonTeam() const;
    QVector<QString> getPersonOrganization() const;
    void addProject (QString);
    void addTeam(QString);
    void addOrganization(QString);
    int getLastPersonId() const;
    void setLastPersonId(int newLastPersonId);
    int getPersonId() const;
    bool operator ==(const Person& other);
    bool operator =(const Person& other);
};

#endif // PERSON_H
