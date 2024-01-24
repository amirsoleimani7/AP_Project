#include "dashboard.h"
#include "ui_dashboard.h"

Dashboard::Dashboard(QWidget *parent, QString RefrenceUserName)
    : QDialog(parent)
    , ui(new Ui::Dashboard)
{

    ui->setupUi(this);
    socket = new socket_connection(this);
    this->CurrentUserName = RefrenceUserName;
    update_HomeOrgListLayout_bottons();
    update_HomeTeamListLayout_bottons();
    update_HomeProjectListLayout_bottons();
    qDebug() << CurrentUserName;
}

Dashboard::~Dashboard()
{
    delete ui;
}

void Dashboard::set_name_loged_in(QString& name)
{
    qDebug() << "this is name : " << name;
}


void Dashboard::update_HomeOrgListLayout_bottons()
{

    QString instruction = "get_organizations*" + CurrentUserName;
    socket->witing_instructions(instruction);
    socket->delay();
    QString feed_back =socket->reading_feed_back();
    qDebug() <<feed_back;
    QStringList list_of_organizations = feed_back.split("*");
    QVBoxLayout* existingLayout = ui->HomeOrgListLayout_organization;
    if(list_of_organizations.size() != 0){
        if (!existingLayout) {
            // If there is no existing layout, create a new one
            existingLayout = new QVBoxLayout();
            //ui->widget_dynamic->setLayout(existingLayout);
        }
        for (int i = 0;i<list_of_organizations.size()-1;i++)
        {
            QString name_of_organization = list_of_organizations[i];
            QPushButton *push_button_of_organization = new QPushButton(this);
            push_button_of_organization->setText(name_of_organization);
            existingLayout->addWidget(push_button_of_organization);
            connect(push_button_of_organization, &QPushButton::clicked, this, &Dashboard::onOrganizationButtonClicked);
        }
        existingLayout->addStretch();
    }
    else{
        existingLayout->addStretch();
    }
}


void Dashboard::update_ProjectTaskListLayout_objects()
{

    QString instruction = "get_Tasks*" + CurrentProjectName;
    socket->witing_instructions(instruction);
    socket->delay();
    QString feed_back =socket->reading_feed_back();
    qDebug() <<feed_back;
    QVector <QStringList> ListOfTasks;
    QStringList list_of_Task = feed_back.split("*");
    for(int i = 0;i<list_of_Task.size()-1;i++){
        ListOfTasks.push_back(list_of_Task[i].split("$"));
    }
    QVBoxLayout* existingLayout = ui->TasksList;
    if(ListOfTasks.size() != 0){
        for (auto index:ListOfTasks)
        {
            QCheckBox *taskCheckBox = new QCheckBox (index[0],this);
            if (index[2] == "1")
                taskCheckBox->setChecked(true);
            QHBoxLayout *Horizbox = new QHBoxLayout(this);
            QLabel *Priority = new QLabel(index[3],this);
            QLabel *Person = new QLabel(index[1],this);
            QPushButton *CommentPushButton = new QPushButton("Commment",this);
            QPushButton *EditPushButton = new QPushButton("Edit",this);
            connect(CommentPushButton, &QPushButton::clicked, this, &Dashboard::onCommentButtonClicked);
            connect(push_button_of_organization, &QPushButton::clicked, this, &Dashboard::onEditTaskButtonClicked);
            Horizbox->addWidget(Person);
            Horizbox->addWidget(Priority);
            Horizbox->addWidget(CommentPushButton);
            Horizbox->addWidget(EditPushButton);

            existingLayout->addWidget(taskCheckBox);
        }
        existingLayout->addStretch();
    }
    else{
        existingLayout->addStretch();
    }
}

void Dashboard::update_HomeTeamListLayout_bottons()
{

    QString instruction = "get_teams*"+CurrentUserName;
    socket->witing_instructions(instruction);
    socket->delay();
    QString feed_back =socket->reading_feed_back();
    qDebug() <<feed_back;
    QStringList list_of_teams = feed_back.split("*");
    QVBoxLayout* existingLayout = ui->HomeTeamsListLayout_team;
    if(list_of_teams.size() != 0){
        if (!existingLayout) {
            // If there is no existing layout, create a new one
            existingLayout = new QVBoxLayout();
            //ui->widget_dynamic->setLayout(existingLayout);
        }

        for (int i = 0;i<list_of_teams.size()-1;i++)
        {
            QString name_of_team = list_of_teams[i];
            QPushButton *push_button_of_team = new QPushButton(this);
            push_button_of_team->setText(name_of_team);
            existingLayout->addWidget(push_button_of_team);
            connect(push_button_of_team, &QPushButton::clicked, this, &Dashboard::onTeamButtonClicked);
        }
        existingLayout->addStretch();
    }
    else{
        existingLayout->addStretch();
    }
}


void Dashboard::update_HomeProjectListLayout_bottons()
{

    QString instruction = "get_project*"+CurrentUserName;
    socket->witing_instructions(instruction);
    socket->delay();
    QString feed_back =socket->reading_feed_back();
    qDebug() <<feed_back;
    QStringList list_of_project = feed_back.split("*");
    QVBoxLayout* existingLayout = ui->HomePProjectsListLayout_project;
    if(list_of_project.size() != 0){
        if (!existingLayout) {
            // If there is no existing layout, create a new one
            existingLayout = new QVBoxLayout();
            //ui->widget_dynamic->setLayout(existingLayout);
        }

        for (int i = 0;i<list_of_project.size()-1;i++)
        {
            QString name_of_project = list_of_project[i];
            QPushButton *push_button_of_project = new QPushButton(this);
            push_button_of_project->setText(name_of_project);
            existingLayout->addWidget(push_button_of_project);
            connect(push_button_of_project, &QPushButton::clicked, this, &Dashboard::onProjectButtonClicked);
        }
        existingLayout->addStretch();
    }
    else{
        existingLayout->addStretch();
    }

}


void Dashboard::onOrganizationButtonClicked(){

    QPushButton* senderButton = qobject_cast<QPushButton*>(sender());
    if (senderButton) {
        // Handle the button click event
        QString organizationName = senderButton->text();
        qDebug() << organizationName;
        //here we should go to the page of organizations with the given organization name

    }
}

void Dashboard::onTeamButtonClicked()
{
    QPushButton* senderButton = qobject_cast<QPushButton*>(sender());
    if (senderButton) {
        // Handle the button click event
        QString teamName = senderButton->text();
        qDebug() << teamName;
        //here we should go to the page of organizations with the given organization name

    }
}

void Dashboard::onProjectButtonClicked(){

    QPushButton* senderButton = qobject_cast<QPushButton*>(sender());
    if (senderButton) {
        // Handle the button click event
        QString projectName = senderButton->text();
        qDebug() << projectName;
        //here we should go to the page of organizations with the given organization name

    }
}

void Dashboard::onCommentButtonClicked()
{

}

void Dashboard::onEditTaskButtonClicked()
{

}


void Dashboard::on_HomeNewPProjectBotton_clicked()
{
    ui->HomeSideStack->setCurrentWidget(ui->HomeNewPProjectPage);
}

void Dashboard::on_HomeNewOrgBotton_clicked()
{
    ui->HomeSideStack->setCurrentWidget(ui->HomeNewOrganizationPage);
}


void Dashboard::on_HomeNewPPBackBotton_clicked()
{
    ui->HomeSideStack->setCurrentWidget(ui->HomeSideMainPage);
}


void Dashboard::on_HomeNewOrgBackBotton_clicked()
{
    ui->HomeSideStack->setCurrentWidget(ui->HomeSideMainPage);
}


void Dashboard::on_OneOrgHomeBotton_clicked()
{
    ui->MainStack->setCurrentWidget(ui->Homepage);
}


void Dashboard::on_HomeProfileBackBotton_clicked()
{
    ui->HomeSideStack->setCurrentWidget(ui->HomeSideMainPage);
}


void Dashboard::on_HomeProfileBotton_clicked()
{
    ui->HomeSideStack->setCurrentWidget(ui->HomeProfilePage);
}


void Dashboard::on_OneOrgEditOrgBotton_clicked()
{
    ui->OneOrgSideStack->setCurrentWidget(ui->OneOrgEditOrgPage);
}


void Dashboard::on_OneOrgAddNewTeamBotton_clicked()
{
    ui->OneOrgSideStack->setCurrentWidget(ui->OneOrgNewTeamPage);
}


void Dashboard::on_OneOrgDeleteOrgBotton_clicked()
{
    ui->MainStack->setCurrentWidget(ui->Homepage);
}


void Dashboard::on_OrgEditPageBackBotton_clicked()
{
    ui->OneOrgSideStack->setCurrentWidget(ui->OneOrgSideMainPage);
}


void Dashboard::on_OrgNewTeamBackBotton_clicked()
{
    ui->OneOrgSideStack->setCurrentWidget(ui->OneOrgSideMainPage);
}


// void Dashboard::on_oneOrgButton_4_clicked()
// {
//     ui->MainStack->setCurrentWidget(ui->OneOrgPage);
// }


void Dashboard::on_OneTeamButton_10_clicked()
{
    ui->MainStack->setCurrentWidget(ui->TeamPage);
}


void Dashboard::on_TeamEditBotton_clicked()
{
    ui->TeamSideStack->setCurrentWidget(ui->TeamEditPage);
}


void Dashboard::on_TeamEditBackBotton_clicked()
{
    ui->TeamSideStack->setCurrentWidget(ui->TeamSideMainPage);
}


void Dashboard::on_TeamAddProject_clicked()
{
    ui->TeamSideStack->setCurrentWidget(ui->TeamAddProjectPage);
}


void Dashboard::on_TeamCreateProject_clicked()
{
    ui->TeamSideStack->setCurrentWidget(ui->TeamCreatProjectPage);
}


void Dashboard::on_TeamDeleteTeamBotton_clicked()
{
    ui->MainStack->setCurrentWidget(ui->Homepage);
}


void Dashboard::on_TeamHomeButton_clicked()
{
    ui->MainStack->setCurrentWidget(ui->Homepage);
}


void Dashboard::on_TeamAddPBackButton_clicked()
{
    ui->TeamSideStack->setCurrentWidget(ui->TeamSideMainPage);
}


void Dashboard::on_TeamCreatPBackButton_clicked()
{
    ui->TeamSideStack->setCurrentWidget(ui->TeamSideMainPage);
}


void Dashboard::on_SomeTeamButton_12_clicked()
{
    ui->MainStack->setCurrentWidget(ui->TeamPage);
}


void Dashboard::on_ProjectNewTaskBackButton_clicked()
{
    ui->ProjectSideStack->setCurrentWidget(ui->ProjectSideMainPage);
}


void Dashboard::on_ProjectNewTaskButton_clicked()
{
    ui->ProjectSideStack->setCurrentWidget(ui->ProjectNewTaskPage);
}


void Dashboard::on_ProjectHomeButton_clicked()
{
    ui->MainStack->setCurrentWidget(ui->Homepage);
}


void Dashboard::on_SomeProjectButton_17_clicked()
{
    ui->MainStack->setCurrentWidget(ui->ProjectPage);
}


void Dashboard::on_SomeProjectButton_2_clicked()
{
    ui->MainStack->setCurrentWidget(ui->ProjectPage);
}


void Dashboard::on_SomeProjectButton_14_clicked()
{
    ui->MainStack->setCurrentWidget(ui->ProjectPage);
}


void Dashboard::on_pushButton_clicked()
{
   // update_HomeOrgListLayout_bottons();
}

