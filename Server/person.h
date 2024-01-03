#ifndef PERSON_H
#define PERSON_H
#include <iostream>
#include <QString>
#include <QVector>
// #include "organization.h"
class Person
{
private:
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
    Person(QString UN,QString PW,QString PN,QString EM,QString RA,QString RC,QString RCO);
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
};

#endif // PERSON_H
