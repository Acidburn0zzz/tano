#ifndef TANO_INFOBAR_H_
#define TANO_INFOBAR_H_

#include <QtGui/QWidget>
#include <QTimer>

#include <ui_InfoBar.h>

class InfoBar : public QWidget
{
    Q_OBJECT

public:
    InfoBar(QWidget *parent = 0);
    ~InfoBar();

public slots:
	void clear();
	void setInfo(QString channel, QString language);
	void setEpg(QString now, QString next);

signals:
	void open(QString);
	void refresh();

private slots:
	void scroll();

private:
    Ui::InfoBar ui;

    QTimer *timer;
    bool direction;
};

#endif // TANO_INFOBAR_H_
