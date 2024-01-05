#ifndef PROJECT_H
#define PROJECT_H
#include <QString>
#include <QVector>
#include "person.h"
class Project
{
private:
    static int projectIdGenerator;
    int lastProjectId;
    int projectId;
    QString projectName;
    int projectType;
    Person projectPerson;
    QVector <QString> projectTeams;
    QVector <QString> projectTasks;

public:

    Project();
    Project(QString PN, int PT);
    Project(const Project& other);
    ~Project();
    QString getProjectName() const;
    int getProjectType() const;
    Person getProjectPerson() const;
    QVector<QString> getProjectTeams() const;
    QVector<QString> getProjectTasks() const;
    int getLastProjectId() const;
    void setLastProjectId(int newLastProjectId);
    int getProjectId() const;
    void setProjectName(const QString &newProjectName);
    void setProjectType(int newProjectType);
    void setProjectPerson(const Person &newProjectPerson);
    bool operator ==(const Project& other);
};

#endif // PROJECT_H
