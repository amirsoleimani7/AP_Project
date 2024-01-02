#ifndef TEAM_H
#define TEAM_H
#include <QString>
#include <QVector>

class Team
{
private:
    QString teamName;
    QString admin;
    QVector<QString> teamMembers;
    QVector<QString> teamProjects;
public:
    Team(QString TN);
    ~Team();
    QString getTeamName() const;
    QString getAdmin() const;
    void setAdmin(const QString &newAdmin);
    QVector<QString> getTeamMembers() const;
    QVector<QString> getTeamProjects() const;
    void addMember (const QString &newMember);
    void addProject (const QString &newProject);
    void setTeamName(const QString &newTeamName);
};

#endif // TEAM_H
