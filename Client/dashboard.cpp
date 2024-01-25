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

void Dashboard::clearLayout(QLayout* layout) {

    QLayoutItem* item;
    while ((item = layout->takeAt(0)) != nullptr) {
        if (item->layout() != nullptr) {
            // Recursively clear sub-layouts
            clearLayout(item->layout());
        }
        delete item->widget();
        delete item;
    }
}

void Dashboard::set_current_organization_name(const QString& organization_name)
{
    CurrentOrganizationName = organization_name;
}

void Dashboard::set_cuurrent_team_name(const QString &team_name)
{
    CurrentTeamName = team_name;
}

void Dashboard::update_profile_of_user()
{
    QString instruction = "get_user_inf*"+CurrentUserName;
    //.arg(id, user_name, password, personal_name, email, fav_animal, fav_color, fav_city);
    socket->witing_instructions(instruction);
    socket->delay();
    QString feed_back = socket->reading_feed_back();
    QStringList fields = feed_back.split("*");
    QString user_name = fields[1];
    QString user_personal_name = fields[3];
    QString user_email =fields[4];

    ui->ProfileUserNameLabel->setText("User Name: "+user_name);
    ui->ProfileNameLabel->setText("Personal Name: "+user_personal_name);
    ui->ProfileEmailLabel->setText("Email: "+user_email);
}
void Dashboard::update_projects_of_team()
{
    clearLayout(ui->verticalLayout_projects_of_team);
    QString instruction = "get_projects_of_team*" + CurrentTeamName;
    socket->witing_instructions(instruction);
    socket->delay();

    QString feed_back =socket->reading_feed_back();
    qDebug() <<feed_back;
    QStringList list_of_projects_in_teams = feed_back.split("*");

    QVBoxLayout* existingLayout = ui->verticalLayout_projects_of_team;
    if(list_of_projects_in_teams.size() != 0){
        if (!existingLayout) {
            // If there is no existing layout, create a new one
            existingLayout = new QVBoxLayout();
            //ui->widget_dynamic->setLayout(existingLayout);
        }
        for (int i = 0;i<list_of_projects_in_teams.size()-1;i++)
        {
            if(list_of_projects_in_teams[i] != ""){
                QString name_of_member_in_team = list_of_projects_in_teams[i];
                QPushButton *push_button_of_projects_in_team = new QPushButton(this);
                push_button_of_projects_in_team->setText(name_of_member_in_team);
                existingLayout->addWidget(push_button_of_projects_in_team);
                connect(push_button_of_projects_in_team, &QPushButton::clicked, this, &Dashboard::onProjectTeamButtonClicked);
            }
        }
        existingLayout->addStretch();
    }
    else{
        existingLayout->addStretch();
    }
}


void Dashboard::onProjectTeamButtonClicked()
{
    QPushButton* senderButton = qobject_cast<QPushButton*>(sender());
    if (senderButton) {
        // Handle the button click event
        QString project_name_in_team = senderButton->text();
        //here we should go to the page of organizations with the given organization name
        qDebug() << project_name_in_team ;
    }

}
void Dashboard::update_members_of_team()
{
    clearLayout(ui->verticalLayout_members_of_team);
    QString instruction = "get_members_of_team*" + CurrentTeamName;
    socket->witing_instructions(instruction);
    socket->delay();

    QString feed_back =socket->reading_feed_back();
    qDebug() <<feed_back;
    QStringList list_of_members_in_teams = feed_back.split("*");

    QVBoxLayout* existingLayout = ui->verticalLayout_members_of_team;
    if(list_of_members_in_teams.size() != 0){
        if (!existingLayout) {
            // If there is no existing layout, create a new one
            existingLayout = new QVBoxLayout();
            //ui->widget_dynamic->setLayout(existingLayout);
        }
        for (int i = 0;i<list_of_members_in_teams.size()-1;i++)
        {
            if(list_of_members_in_teams[i] != ""){
                QString name_of_member_in_team = list_of_members_in_teams[i];
                QPushButton *push_button_of_member_in_team = new QPushButton(this);
                push_button_of_member_in_team->setText(name_of_member_in_team);
                existingLayout->addWidget(push_button_of_member_in_team);
                connect(push_button_of_member_in_team, &QPushButton::clicked, this, &Dashboard::onMemberTeamButtonClicked);
            }
        }
        existingLayout->addStretch();
    }
    else{
        existingLayout->addStretch();
    }

}

void Dashboard::onMemberTeamButtonClicked(){

    QPushButton* senderButton = qobject_cast<QPushButton*>(sender());
    if (senderButton) {
        // Handle the button click event
        QString member_name_in_team = senderButton->text();
        //here we should go to the page of organizations with the given organization name

    }
}

void Dashboard::update_HomeOrgListLayout_bottons()
{
    clearLayout(ui->HomeOrgListLayout_organization);
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
            if(list_of_organizations[i] != ""){
                QString name_of_organization = list_of_organizations[i];
                QPushButton *push_button_of_organization = new QPushButton(this);
                push_button_of_organization->setText(name_of_organization);
                existingLayout->addWidget(push_button_of_organization);
                connect(push_button_of_organization, &QPushButton::clicked, this, &Dashboard::onOrganizationButtonClicked);
            }

        }
        existingLayout->addStretch();
    }
    else{
        existingLayout->addStretch();
    }
}

void Dashboard::update_HomeTeamListLayout_bottons()
{

    clearLayout(ui->HomeTeamsListLayout_team);
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
            if(list_of_teams[i]!=""){
                QString name_of_team = list_of_teams[i];
                QPushButton *push_button_of_team = new QPushButton(this);
                push_button_of_team->setText(name_of_team);
                existingLayout->addWidget(push_button_of_team);
                connect(push_button_of_team, &QPushButton::clicked, this, &Dashboard::onTeamButtonClicked);
            }

        }
        existingLayout->addStretch();
    }
    else{
        existingLayout->addStretch();
    }
}
void Dashboard::update_HomeProjectListLayout_bottons()
{
    clearLayout(ui->HomePProjectsListLayout_project);
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
            if(list_of_project[i]!=""){
                QString name_of_project = list_of_project[i];
                QPushButton *push_button_of_project = new QPushButton(this);
                push_button_of_project->setText(name_of_project);
                existingLayout->addWidget(push_button_of_project);
                connect(push_button_of_project, &QPushButton::clicked, this, &Dashboard::onProjectButtonClicked);
            }

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
        set_current_organization_name(organizationName);
        ui->MainStack->setCurrentWidget(ui->OneOrgPage);
        ui->OneOrgName->setText(CurrentOrganizationName);
        update_teams_in_organization();
        update_projects_in_organization();
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
        ui->TeamLabel->setText(teamName);
        set_cuurrent_team_name(teamName);
        ui->MainStack->setCurrentWidget(ui->TeamPage);
        update_members_of_team();
        update_projects_of_team();
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

void Dashboard::update_projects_in_organization(){

    clearLayout(ui->OrgProjectListLayout_layout);

    qDebug() << "current org name is :" +CurrentOrganizationName;
    QString instruction = "get_projects_of_organization*"+ CurrentOrganizationName;

    socket->witing_instructions(instruction);
    socket->delay();
    QString feed_back =socket->reading_feed_back();

    qDebug() << "feed back for teams os org : "<<feed_back;
    QStringList list_of_projects_in_organization = feed_back.split("*");
    QVBoxLayout* existingLayout = ui->OrgProjectListLayout_layout;

    if(list_of_projects_in_organization.size() != 0){
        if (!existingLayout) {
            // If there is no existing layout, create a new one
            existingLayout = new QVBoxLayout();
            //ui->widget_dynamic->setLayout(existingLayout);
        }

        for (int i = 0;i<list_of_projects_in_organization.size()-1;i++)
        {
            if(list_of_projects_in_organization[i]!=""){
                QString name_of_project_in_org = list_of_projects_in_organization[i];
                QPushButton *push_button_of_project_in_org = new QPushButton(this);
                push_button_of_project_in_org->setText(name_of_project_in_org);
                existingLayout->addWidget(push_button_of_project_in_org);
                connect(push_button_of_project_in_org, &QPushButton::clicked, this, &Dashboard::onProjecsInOrganizationButtonClicked);
            }

        }
        existingLayout->addStretch();
    }
    else{
        existingLayout->addStretch();
    }

}
void Dashboard::onProjecsInOrganizationButtonClicked(){
    QPushButton* senderButton = qobject_cast<QPushButton*>(sender());
    if (senderButton) {
        // Handle the button click event
        QString project_name_in_organization = senderButton->text();
        qDebug() << project_name_in_organization;
        //here we should go to the page of organizations with the given organization name
    }
}
void Dashboard::update_teams_in_organization()
{
    clearLayout(ui->OrgTeamsListLayout_layout);
    qDebug() << "current org name is :" +CurrentOrganizationName;
    QString instruction = "get_teams_of_organization*"+ CurrentOrganizationName;
    socket->witing_instructions(instruction);
    socket->delay();
    QString feed_back =socket->reading_feed_back();

    qDebug() << "feed back for teams os org : "<<feed_back;
    QStringList list_of_teams_in_organization = feed_back.split("*");
    QVBoxLayout* existingLayout = ui->OrgTeamsListLayout_layout;

    if(list_of_teams_in_organization.size() != 0){
        if (!existingLayout) {
            // If there is no existing layout, create a new one
            existingLayout = new QVBoxLayout();
            //ui->widget_dynamic->setLayout(existingLayout);
        }

        for (int i = 0;i<list_of_teams_in_organization.size()-1;i++)
        {
            if(list_of_teams_in_organization[i]!=""){
                QString name_of_team_in_org = list_of_teams_in_organization[i];
                QPushButton *push_button_of_team_in_org = new QPushButton(this);
                push_button_of_team_in_org->setText(name_of_team_in_org);
                existingLayout->addWidget(push_button_of_team_in_org);
                connect(push_button_of_team_in_org, &QPushButton::clicked, this, &Dashboard::onTeamsInOrganizationButtonClicked);
            }

        }
        existingLayout->addStretch();
    }
    else{
        existingLayout->addStretch();
    }

}
void Dashboard::onTeamsInOrganizationButtonClicked()
{
    QPushButton* senderButton = qobject_cast<QPushButton*>(sender());
    if (senderButton) {
        // Handle the button click event
        QString team_name_in_organization = senderButton->text();
        qDebug() << team_name_in_organization;
        //here we should go to the page of organizations with the given organization name
    }
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
    update_HomeOrgListLayout_bottons();
}


void Dashboard::on_HomeProfileBackBotton_clicked()
{
    ui->HomeSideStack->setCurrentWidget(ui->HomeSideMainPage);
}


void Dashboard::on_HomeProfileBotton_clicked()
{
    ui->HomeSideStack->setCurrentWidget(ui->HomeProfilePage);
    update_profile_of_user();
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
    QString instruction = "delete_team_of_member*"+CurrentUserName+"*"+CurrentTeamName;
    socket->witing_instructions(instruction);
    socket->delay();
    QMessageBox::information(this,"remove team","team removed");
    //update_HomeTeamListLayout_bottons();



    // update_members_of_team();
    // update_teams_in_organization();
    // update_HomeTeamListLayout_bottons();
}


void Dashboard::on_TeamHomeButton_clicked()
{
    ui->MainStack->setCurrentWidget(ui->Homepage);
    update_HomeTeamListLayout_bottons();
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


void Dashboard::on_HomeProfileChangeButton_clicked()
{
    QString new_personal_name = ui->ProfileNewNameLineEdit->text();
    QString new_email = ui->ProfileNewEmail->text();
    QString new_pass = ui->ProfileNewPassLineEdit->text();
    QString instruction = "update_person_all_at_once*"+CurrentUserName+"*"+new_personal_name+"*"+new_email+"*"+new_pass;
    socket->witing_instructions(instruction);
    socket->delay();
    QMessageBox::information(this,"this","info updated!!");
    update_profile_of_user();
}


void Dashboard::on_HomeNewPPCreatBotton_clicked()
{
    QString new_personal_project = ui->HomeNewPPNameLineEdit->text();
    QString instruction = "add_to_personal_project*"+CurrentUserName+"*"+new_personal_project+"*personal";
    socket->witing_instructions(instruction);
    socket->delay();
    QMessageBox::information(this,"this","added updated!!");
    update_HomeProjectListLayout_bottons();
}


void Dashboard::on_HomeNewOrgCreatBotton_clicked()
{
    QString new_organization_name = ui->NewOrgNameLineEdit->text();
    QString owner_name = CurrentUserName;
    QString instruction = "add_to_organizations*"+new_organization_name+"*"+owner_name;
    socket->witing_instructions(instruction);
    socket->delay();
    update_HomeOrgListLayout_bottons();
}

void Dashboard::on_search_for_project_clicked()
{
    clearLayout(ui->verticalLayout_search_for_project);
    QString search_for_project_to_add = ui->TeamAddProjectLineEdit->text();
    QString instruction ="search_for_projects*"+search_for_project_to_add;
    socket->witing_instructions(instruction);
    socket->delay();

    QString feed_back =socket->reading_feed_back();
    qDebug() <<feed_back;
    QStringList list_of_project_search_reualt = feed_back.split("*");
    QVBoxLayout* existingLayout = ui->verticalLayout_search_for_project;

    if(list_of_project_search_reualt.size() != 0){
        if (!existingLayout) {
            // If there is no existing layout, create a new one
            existingLayout = new QVBoxLayout();
            //ui->widget_dynamic->setLayout(existingLayout);
        }

        for (int i = 0;i<list_of_project_search_reualt.size()-1;i++)
        {
            if(list_of_project_search_reualt[i]!=""){

                QString name_of_project_search = list_of_project_search_reualt[i];
                QPushButton *push_button_of_project_search = new QPushButton(this);
                push_button_of_project_search->setText(name_of_project_search);
                existingLayout->addWidget(push_button_of_project_search);
                connect(push_button_of_project_search, &QPushButton::clicked, this, &Dashboard::onProjectSearchButtonClicked);
            }

        }
        existingLayout->addStretch();
    }
    else{
        existingLayout->addStretch();
    }
}

void Dashboard::add_project_to_team(QString& project_name)
{
    QString instruction = "add_project_to_team*"+CurrentTeamName+"*"+project_name;
    socket->witing_instructions(instruction);
    socket->delay();
    QMessageBox::information(this,"adding project","project added");
    update_projects_of_team();
}
void Dashboard::onProjectSearchButtonClicked(){

    QPushButton* senderButton = qobject_cast<QPushButton*>(sender());
    if (senderButton) {
        // Handle the button click event
        QString project_name_in_search = senderButton->text();
        //here we should go to the page of organizations with the given organization name
        qDebug() << project_name_in_search;
        add_project_to_team(project_name_in_search);
    }
}


void Dashboard::on_TeamChangeNameBotton_clicked()
{
    QString new_team_name = ui->TeamNewNameLineEdit->text();
    if(ui->TeamNewNameLineEdit->text().isEmpty()){
        QMessageBox::warning(this,"new name","enter a new name");
    }
    else{
        QString new_team_name = ui->TeamNewNameLineEdit->text();
        QString instruction ="change_team_name*"+CurrentTeamName+"*"+new_team_name;
        socket->witing_instructions(instruction);
        socket->delay();
        QMessageBox::information(this,"changing name","name chnaged");
    }

    //update_HomeTeamListLayout_bottons();
}

void Dashboard::on_searchForUserNameToAddToTeam_clicked()
{
    clearLayout(ui->verticalLayout_search_for_person);
    QString search_for_person_to_add = ui->TeamNewMemberLineEdit->text();
    QString instruction ="search_for_person*"+search_for_person_to_add;
    socket->witing_instructions(instruction);
    socket->delay();

    QString feed_back =socket->reading_feed_back();
    qDebug() <<feed_back;
    QStringList list_of_person_search_reualt = feed_back.split("*");
    QVBoxLayout* existingLayout = ui->verticalLayout_search_for_person;

    if(list_of_person_search_reualt.size() != 0){
        if (!existingLayout) {
            // If there is no existing layout, create a new one
            existingLayout = new QVBoxLayout();
            //ui->widget_dynamic->setLayout(existingLayout);
        }

        for (int i = 0;i<list_of_person_search_reualt.size()-1;i++)
        {
            if(list_of_person_search_reualt[i]!=""){

                QString name_of_person_search = list_of_person_search_reualt[i];
                QPushButton *push_button_of_person_search = new QPushButton(this);
                push_button_of_person_search->setText(name_of_person_search);
                existingLayout->addWidget(push_button_of_person_search);
                connect(push_button_of_person_search, &QPushButton::clicked, this, &Dashboard::onPersonSearchButtonClicked);
            }
        }
        existingLayout->addStretch();
    }
    else{
        existingLayout->addStretch();
    }
}
void Dashboard::add_person_to_team(QString& person_name)
{
    QString instruction = "add_person_to_team*"+CurrentTeamName+"*"+person_name;
    socket->witing_instructions(instruction);
    socket->delay();
    QMessageBox::information(this,"adding project","person added");
    update_members_of_team();
}


void Dashboard::onPersonSearchButtonClicked(){

    QPushButton* senderButton = qobject_cast<QPushButton*>(sender());
    if (senderButton) {
        // Handle the button click event
        QString searched_name = senderButton->text();
        qDebug() << searched_name;
        add_person_to_team(searched_name);
        //here we should go to the page of organizations with the given organization name
    }
}

void Dashboard::on_TeamDeletingMemberBotton_clicked()
{
    QString member_to_remove_from_team = ui->TeamDeletingMemberLineEdit->text();
    QString instruction = "remove_member_from_team*"+CurrentTeamName+"*"+member_to_remove_from_team;
    socket->witing_instructions(instruction);
    socket->delay();
    update_members_of_team();
}

