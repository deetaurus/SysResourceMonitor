#include "advancedoptions.h"
#include "ui_advancedoptions.h"

advancedOptions::advancedOptions(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::advancedOptions)
{
    ui->setupUi(this);
}

advancedOptions::~advancedOptions()
{
    delete ui;
}

void advancedOptions::on_adminToAuto_clicked()
{
    // Enable own components and disable other componenets
    ui->label_4->setEnabled(false);
    ui->label_5->setEnabled(false);
    ui->setAutoToAdmin->setEnabled(false);
    ui->autoToAdminDateEdit->setEnabled(false);
    ui->autoToAdminTimeEdit->setEnabled(false);

    ui->label_2->setEnabled(true);
    ui->label_3->setEnabled(true);
    ui->setAdminToAuto->setEnabled(true);
    ui->adminToAutoDateEdit->setEnabled(true);
    ui->adminToAutoTimeEdit->setEnabled(true);
}

void advancedOptions::on_autoToAdmin_clicked()
{
    // Enable own components and disable other componenets
    ui->label_2->setEnabled(false);
    ui->label_3->setEnabled(false);
    ui->setAdminToAuto->setEnabled(false);
    ui->adminToAutoDateEdit->setEnabled(false);
    ui->adminToAutoTimeEdit->setEnabled(false);

    ui->label_4->setEnabled(true);
    ui->label_5->setEnabled(true);
    ui->setAutoToAdmin->setEnabled(true);
    ui->autoToAdminDateEdit->setEnabled(true);
    ui->autoToAdminTimeEdit->setEnabled(true);
}

void advancedOptions::on_setAdminToAuto_accepted()
{
    QDialog dialog;
    QDate dateNow, userSetDate;
    QTime timeNow, userSetTime;

    // Current date and time
    dateNow.currentDate();
    timeNow.currentTime();

    userSetTime = ui->adminToAutoTimeEdit->time();
    userSetDate = ui->adminToAutoDateEdit->date();

    dialog.setGeometry(300,300,300,150);
    dialog.setWindowTitle(dateNow.toString("hh:mm:ss"));



    dialog.exec();
}

void advancedOptions::on_setAutoToAdmin_accepted()
{

}
