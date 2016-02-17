#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <stdio.h>
#include <stdlib.h>
#include <glib.h>
#include <glibtop.h>
#include <glibtop/cpu.h>
#include <glibtop/mem.h>
#include <glibtop/proclist.h>
#include <iostream>

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    bool flag;
    explicit MainWindow(QWidget *parent = 0);
    void updateTabs();
    void updateCpuInfo();
    void updateMemoryInfo();
    void updatePowerInfo();
    void reconfigureStepsNoHistoricalData();
    ~MainWindow();

public slots:
    void closeButtonHandler();
    void hibernateButtonHandler();
    void turnOffDisplayHandler();
    void adminModeHandler();
    void automaticModeHandler();
    void brightOkHandler();

private:
    Ui::MainWindow *ui;

private slots:
    void on_advancedOptionsButton_clicked();
};

#endif // MAINWINDOW_H
