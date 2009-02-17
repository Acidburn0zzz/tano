#include <QResource>

#include "TrayIcon.h"

TrayIcon::TrayIcon(QMenu *menu)
{
	QResource::registerResource("images.qrc");

	this->setContextMenu(menu);
	this->setIcon(QIcon(":/icons/images/tano.png"));
	this->setToolTip(tr("Tano Player"));

	connect(this, SIGNAL(activated(QSystemTrayIcon::ActivationReason)),
			this, SLOT(iconActivated(QSystemTrayIcon::ActivationReason)));

	this->show();

}

TrayIcon::~TrayIcon() {
}


void TrayIcon::iconActivated(QSystemTrayIcon::ActivationReason reason)
{
    switch (reason) {
    case QSystemTrayIcon::Trigger:
    case QSystemTrayIcon::DoubleClick:
        eRestore();
        break;
    case QSystemTrayIcon::MiddleClick:
        break;
    default:
        ;
    }
}

void TrayIcon::eRestore()
{
	emit restoreClick();
}

void TrayIcon::message(QString type)
{
	if (type == "close")
		this->showMessage(tr("Still running"), tr("Tano Player is still running.\nRight click to exit."), QSystemTrayIcon::Information, 10000);
	else if (type == "latest")
			this->showMessage(tr("Latest version"), tr("You are using the latest version of Tano Player."), QSystemTrayIcon::Information, 10000);
	else if (type.contains("svn")) {
		QStringList update;
		update = type.split(",");
		this->showMessage(tr("SVN"), tr("You are using SVN version:")+" "+update[1]+"\n" + tr("Stable version:") + " " + update[0], QSystemTrayIcon::Information, 10000);
	} else
		this->showMessage(tr("Update available"), tr("A new version of Tano Player is available!")+"\n" + tr("Version:") + " " + type, QSystemTrayIcon::Information, 10000);
}

void TrayIcon::changeToolTip(QString text)
{
	if (text != "stop")
		this->setToolTip(tr("Tano Player") + " - " + tr("Currently playing:") + " " + text);
	else
		this->setToolTip(tr("Tano Player"));
}
