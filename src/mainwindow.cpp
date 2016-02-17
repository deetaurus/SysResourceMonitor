#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "powerInfo.h"
#include "advancedoptions.h"

void *threadRun(void*);

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi (this);
    updateTabs();   // initialize the GUI, draw tables in tabs
}

void MainWindow::updateTabs()
{
    QStringList list;
    pthread_t mythread;

    list << "Parameter" << "Value";   //  Menu headers for Cpu Usage table

    flag = true;

    // Set rows for cpu info
    ui->cpuStat->setRowCount(6);
    ui->cpuStat->setColumnCount(2);
    ui->cpuStat->setHorizontalHeaderLabels(list);

    // Set rows for cpu info
    ui->memStat->setRowCount(8);
    ui->memStat->setColumnCount(2);
    ui->memStat->setHorizontalHeaderLabels(list);

   // Set rows for power info
    ui->powerStat->setRowCount(2);
    ui->powerStat->setColumnCount(2);
    ui->powerStat->setHorizontalHeaderLabels(list);
    ui->powerStat->setColumnWidth(0, 150);
    ui->powerStat->setColumnWidth(1, 150);

    // Start threads here
    pthread_create( &mythread, NULL, threadRun, (void*) this);

}

void MainWindow::updateCpuInfo()
{
    /*  All CPU units are measured in jiffies which are normally 1/100th of a second
        (in which case frequency equals 100), but can also be in any other unit.
        To get seconds, divide them by frequency. */

    QStringList list1;
    QList<unsigned long> list2;

    glibtop_init();
    glibtop_cpu cpu;
    glibtop_get_cpu (&cpu);

    list1 << "Total" << "User" << "Nice" << "System" << "Idle" << "Frequency";
    list2 << cpu.total << cpu.user << cpu.nice << cpu.sys <<cpu.idle <<cpu.frequency;


    for (int r = 0, i = 0; r < ui->cpuStat->rowCount(); ++r, i++)
     {
        QString temp;

        QTableWidgetItem* item1 = new QTableWidgetItem;
        QTableWidgetItem* item2 = new QTableWidgetItem;

        item1->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEnabled);
        item1->setTextAlignment(Qt::AlignBottom|Qt::AlignLeading);
        item2->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEnabled);
        item2->setTextAlignment(Qt::AlignBottom|Qt::AlignLeading);

        item1->setText (list1.at(i));
        ui->cpuStat->setItem (r, 0, item1);

        temp = QString::number ((double) list2.at(i));

        item2->setText (temp);
        ui->cpuStat->setItem (r, 1, item2);

     }
}

void MainWindow::updateMemoryInfo()
{
    QStringList list1;
    QList<unsigned long> list2;

    glibtop_init();
    glibtop_mem mem;
    glibtop_get_mem (&mem);

    list1 << "Total" << "Used" << "Free" << "Shared" << "Buffer" << "Cached" << "User" << "Locked";
    list2 << mem.total/(1024*1024) << mem.used/(1024*1024) << mem.free/(1024*1024) << mem.shared/(1024*1024) << mem.buffer/(1024*1024) << mem.cached/(1024*1024) << mem.user/(1024*1024) << mem.locked/(1024*1024);

    for (int r = 0, i = 0; r < ui->memStat->rowCount() ; ++r, i++)
    {
        QString temp;

        QTableWidgetItem* item1 = new QTableWidgetItem;
        QTableWidgetItem* item2 = new QTableWidgetItem;

        item1->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEnabled);
        item1->setTextAlignment(Qt::AlignBottom|Qt::AlignLeading);
        item2->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEnabled);
        item2->setTextAlignment(Qt::AlignBottom|Qt::AlignLeading);

        item1->setText (list1.at(i));
        ui->memStat->setItem (r, 0, item1);

        temp = QString::number ((double) list2.at(i));
        temp.append(" MB");

        item2->setText( temp);
        ui->memStat->setItem( r, 1, item2);
    }
}

void MainWindow::updatePowerInfo()
{
    struct powerStat *pst;
    QStringList list1;

    pst = (struct powerStat*) malloc( sizeof (struct powerStat*));
    pst = measurePower();

    list1 << "Time" << "Power Consumption";

    for (int r = 0, i = 0; r < ui->powerStat->rowCount(); ++r, i++)
    {
        QString temp;
        QTableWidgetItem* item1 = new QTableWidgetItem;
        QTableWidgetItem* item2 = new QTableWidgetItem;

        item1->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEnabled);
        item1->setTextAlignment(Qt::AlignBottom|Qt::AlignLeading);
        item2->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEnabled);
        item2->setTextAlignment(Qt::AlignBottom|Qt::AlignLeading);

        item1->setText (list1.at(i));
        ui->powerStat->setItem (r, 0, item1);

        if (r == 0)
            item2->setText( pst->timeInfo);
        else
        {
            if (r == 1)
            {
                temp = QString::number((float) pst->powerusage);
                temp.append (" W");
                item2->setText( temp);
            }
        }

        ui->powerStat->setItem (r, 1, item2);
    }
}

void MainWindow::reconfigureStepsNoHistoricalData()
{
    int cpuUsedNow;

    glibtop_init();
    glibtop_cpu cpu;
    glibtop_get_cpu (&cpu);

    cpuUsedNow = 100 - (int) (cpu.idle/cpu.total)*100;

    // take necessary actions
    if (cpuUsedNow <= 5)    {
        system("/etc/acpi/hibernate.sh");
    }
    else if (cpuUsedNow >= 80)   {
        system("xbacklight -set 10");
    }
    else if ((cpuUsedNow < 30) && (cpuUsedNow >= 5 ))    {
        system("xbacklight -set 30");
    }
    else if ((cpuUsedNow < 50) && (cpuUsedNow >= 30 ))    {
        system("xbacklight -set 20");
    }
    else if ((cpuUsedNow < 70) && (cpuUsedNow >= 50 ))    {
        system("xbacklight -set 30");
    }
    else if ((cpuUsedNow < 80) && (cpuUsedNow >= 70 ))    {
        system("xbacklight -set 10");
    }

}

void MainWindow::closeButtonHandler()
{
    QApplication::exit(0);
}

void MainWindow::on_advancedOptionsButton_clicked()
{
    advancedOptions *ao = new advancedOptions();

    ao->show();
}

void MainWindow::turnOffDisplayHandler()
{
    system("xset dpms force off");   // turn off display
}

void MainWindow::adminModeHandler()
{
    ui->hibernateButton->setEnabled(true);
    ui->brightEdit->setEnabled(true);
    ui->pushButton_2->setEnabled(true);
    ui->turnOffDisplay->setEnabled(true);

    flag = false;  // setting flag false for admin mode handler

    system("xbacklight -set 100");
}

void MainWindow::hibernateButtonHandler()
{
    system("/etc/acpi/hibernate.sh");
}

void MainWindow::automaticModeHandler()
{
    ui->hibernateButton->setEnabled(false);
    ui->brightEdit->setEnabled(false);
    ui->turnOffDisplay->setEnabled(false);
    ui->pushButton_2->setEnabled(false);

    flag = true;  // setting flag=true for automatic mode handler
}

void MainWindow::brightOkHandler()
{
    QString sliderValue = ui->brightEdit->text();
    QString str = "xbacklight -set ";
    std::string str2;
    str.append(sliderValue);

    str2 = str.toStdString();  // converts QString to Cpp String

    char *str3 = (char *)str2.c_str();

    system(str3);
}

void *threadRun(void *obj)
{
    MainWindow *temp = (MainWindow*) obj;

    while (true)    {
        sleep(1);

        temp->updateCpuInfo();
        temp->updateMemoryInfo();
        if (temp->flag)
            temp->reconfigureStepsNoHistoricalData();
        //temp->updatePowerInfo();
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

