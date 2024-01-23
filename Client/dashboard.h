#ifndef DASHBOARD_H
#define DASHBOARD_H

#include <QDialog>

namespace Ui {
class Dashboard;
}

class Dashboard : public QDialog
{
    Q_OBJECT

public:
    explicit Dashboard(QWidget *parent = nullptr);
    ~Dashboard();

private slots:

    void on_HomeNewPProjectBotton_clicked();

    void on_HomeNewOrgBotton_clicked();

    void on_HomeNewPPBackBotton_clicked();

    void on_HomeNewOrgBackBotton_clicked();

    void on_OneOrgHomeBotton_clicked();

    void on_HomeProfileBackBotton_clicked();

    void on_HomeProfileBotton_clicked();

    void on_OneOrgEditOrgBotton_clicked();

    void on_OneOrgAddNewTeamBotton_clicked();

    void on_OneOrgDeleteOrgBotton_clicked();

    void on_OrgEditPageBackBotton_clicked();

    void on_OrgNewTeamBackBotton_clicked();

    void on_oneOrgButton_4_clicked();

private:
    Ui::Dashboard *ui;
};

#endif // DASHBOARD_H
