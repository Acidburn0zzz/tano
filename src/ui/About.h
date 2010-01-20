#ifndef TANO_ABOUT_H_
#define TANO_ABOUT_H_

#include <QtGui/QDialog>
#include <ui_About.h>

class About : public QDialog
{
    Q_OBJECT
public:
    About(QWidget *parent = 0, QString version = "Unknown");
    ~About();

private:
    Ui::About ui;
    QString qt;
};

#endif // TANO_ABOUT_H
