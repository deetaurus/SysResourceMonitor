#ifndef ADVANCEDOPTIONS_H
#define ADVANCEDOPTIONS_H

#include <QMainWindow>
#include <QtGui>
#include <time.h>

namespace Ui {
    class advancedOptions;
}

class advancedOptions : public QMainWindow
{
    Q_OBJECT

public:
    explicit advancedOptions(QWidget *parent = 0);
    ~advancedOptions();

private:
    Ui::advancedOptions *ui;

private slots:
    void on_setAutoToAdmin_accepted();
    void on_setAdminToAuto_accepted();
    void on_autoToAdmin_clicked();
    void on_adminToAuto_clicked();
};

#endif // ADVANCEDOPTIONS_H
