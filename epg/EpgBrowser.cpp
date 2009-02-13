#include <QUrl>
#include <QDebug>

#include "EpgBrowser.h"

EpgBrowser::EpgBrowser(QWidget *parent)
    : QWidget(parent)
{
	ui.setupUi(this);

	ui.actionStop->setDisabled(true);

	connect(ui.buttonGo, SIGNAL(clicked()), this, SLOT(go()));
	connect(ui.actionHome, SIGNAL(triggered()), this, SLOT(home()));
	connect(ui.actionEpg, SIGNAL(triggered()), this, SLOT(epg()));
	connect(ui.actionHelp, SIGNAL(triggered()), this, SLOT(help()));
	connect(ui.epgView, SIGNAL(urlChanged(QUrl)), this, SLOT(changeText(QUrl)));

	connect(ui.epgView, SIGNAL(loadStarted()), this, SLOT(stopStatus()));
	connect(ui.actionStop, SIGNAL(triggered()), this, SLOT(stopStatus()));
	connect(ui.epgView, SIGNAL(loadFinished(bool)), this, SLOT(stopStatusT(bool)));
}

EpgBrowser::~EpgBrowser()
{

}

void EpgBrowser::go()
{
	QString url = ui.addressLine->text();
	if (!url.contains("http://", Qt::CaseInsensitive)) {
		url.prepend("http://");
		ui.addressLine->setText(url);
	}
	ui.epgView->load(QUrl(ui.addressLine->text()));
}

void EpgBrowser::open(QString link) {
	ui.addressLine->setText(link);
	go();
	this->show();
}

void EpgBrowser::home()
{
	ui.addressLine->setText("http://tano.pfusion.co.cc");
	go();
}

void EpgBrowser::epg()
{
	ui.addressLine->setText("http://tano.pfusion.co.cc/siol/");
	go();
}

void EpgBrowser::help()
{
	ui.addressLine->setText("http://tano.pfusion.co.cc/wiki/Help:Contents");
	go();
	this->show();
}

void EpgBrowser::changeText(QUrl url)
{
	ui.addressLine->setText(url.toString());
}

void EpgBrowser::stopStatusT(bool status)
{
    if(status == true)
    	stopStatus();
}

void EpgBrowser::stopStatus()
{
    if(ui.actionStop->isEnabled() != true)
    	ui.actionStop->setEnabled(true);
    else
    	ui.actionStop->setDisabled(true);

    if(ui.actionReload->isEnabled() != true)
    	ui.actionReload->setEnabled(true);
    else
    	ui.actionReload->setDisabled(true);
}
