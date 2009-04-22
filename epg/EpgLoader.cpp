#include "EpgLoader.h"

#include <QtDebug>
#include <QTime>

EpgLoader::EpgLoader()
{
	init = false;
	setHost("www.siol.net");
	codec = QTextCodec::codecForName("UTF-8");
	edit = new QTextEdit();
    epgInit();
}

EpgLoader::~EpgLoader()
{

}

void EpgLoader::getEpg(QString epgP)
{
	epgGet = epgP;
	epgFull = epgP  + "&flag=" + epgFlag;

	if(init)
		epg();
}

void EpgLoader::reload()
{
    epg();
}

void EpgLoader::stop()
{
	disconnect(this, SIGNAL(done(bool)), this, SLOT(epgPrint()));
}

void EpgLoader::epgInit()
{
	get("/tv-spored.aspx");
	connect(this, SIGNAL(done(bool)), this, SLOT(epgInitDone()));
}

void EpgLoader::epgInitDone()
{
	int n = 0;
	QByteArray httpResponse = readAll();

	epgValue = codec->toUnicode(httpResponse);

	n = epgValue.indexOf("flag=",epgValue.indexOf("channels"));

	for(int i=n+5;i<=n+25;i++)
		epgFlag.append(epgValue.at(i));

	disconnect(this, SIGNAL(done(bool)), this, SLOT(epgInitDone()));

	init = true;
	getEpg(epgGet);
}

void EpgLoader::epg()
{
	get(epgFull);

	connect(this, SIGNAL(done(bool)), this, SLOT(epgPrint()));
}

void EpgLoader::epgPrint()
{
	int n = 0;
	QByteArray httpResponse = readAll();

	epgValue = codec->toUnicode(httpResponse);

	if(!epgValue.contains("schedule_title")) {
		disconnect(this, SIGNAL(done(bool)), this, SLOT(epgPrint()));
		return;
	}

	//Main EPG
	n = epgValue.indexOf("<dl class=\"listB\">");
	epgValue.remove(0,n);
	n = epgValue.indexOf("</dl>");
	epgValue.remove(n,epgValue.size()-1-n);

	//Changes
	epgValue.replace("<table class=\"schedule\">", ": ");
	epgValue.replace("<a", ";<a");
	epgValue.replace("</a>", ";");
	epgValue.replace("	","");
	epgValue.replace(" href=\"",">");

	edit->setHtml(epgValue);
	epgValue = edit->toPlainText();
	edit->setText("");

	epgValue.replace("\n","");
	epgValue.replace("\">",";");
	epgValue.replace("tv-spored.aspx", "http://www.siol.net/tv-spored.aspx");
	epgValue.replace(";: ",";");
	epgValue.replace(".2009: ", ".2009:;");
	epgValue.remove(epgValue.size()-1,1);

	disconnect(this, SIGNAL(done(bool)), this, SLOT(epgPrint()));

	epgList = epgValue.split(";");
	emit epgDone(epgList);
}
