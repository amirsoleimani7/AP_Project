#ifndef PROJECT_H
#define PROJECT_H
#include <QString>
#include <QVector>

class Project
{
private:
    QString projectName;
    int projectType;
    QString projectPerson;
    QVector <QString> projectTeams;
    QVector <QString> projectTasks;
public:
    Project(QString PN, int PT);
    ~Project();
    QString getProjectName() const;
    int getProjectType() const;
    QString getProjectPerson() const;
    QVector<QString> getProjectTeams() const;
    QVector<QString> getProjectTasks() const;
};

#endif // PROJECT_H
