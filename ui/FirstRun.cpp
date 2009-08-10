#include <QtGui>
#include <QResource>

#include "FirstRun.h"
#include "../Common.h"

FirstRun::FirstRun(QWidget *parent)
    : QWizard(parent)
{
	QResource::registerResource("images.qrc");

    setPage(Page_Intro, new IntroPage);
    setPage(Page_Settings, new SettingsPage);
    setPage(Page_Conclusion, new ConclusionPage);

    setStartId(Page_Intro);

#ifndef Q_WS_MAC
    setWizardStyle(ModernStyle);
#endif

    setPixmap(QWizard::LogoPixmap, QPixmap(":/icons/images/tano-small.png"));
    setWindowTitle(tr("First Run Wizard"));
}

IntroPage::IntroPage(QWidget *parent)
    : QWizardPage(parent)
{
	QString version = Common::version();

    setTitle(tr("Welcome"));
    setPixmap(QWizard::WatermarkPixmap, QPixmap(":/icons/images/wizard.bmp"));

    topLabel = new QLabel(tr("This wizard will help you set basic settings for your copy of <i>Tano</i>."));
    topLabel->setWordWrap(true);

    if(Common::settings()->value("version", version).toString() != version) {
    	versionLabel = new QLabel(tr("You previously used version %1 of <i>Tano</i>. Please re-set your settings.").arg(Common::settings()->value("version", version).toString()));
    	versionLabel->setWordWrap(true);
    } else
    	versionLabel = new QLabel("");

    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(topLabel);
    layout->addWidget(versionLabel);
    setLayout(layout);
}

int IntroPage::nextId() const
{
    return FirstRun::Page_Settings;
}

SettingsPage::SettingsPage(QWidget *parent)
    : QWizardPage(parent)
{
     setTitle(tr("Set <i>Tano</i>"));
     setSubTitle(tr("Please select your IP TV provider with playlist and other settings."));

     playlist = new QLineEdit;
     type = new QLineEdit;

     sessionLabel = new QLabel(tr("Set your session store settings:"));
     siol = new QLabel("SiOL");
     t2 = new QLabel("T-2");

     siolRadio = new QRadioButton(tr("SiOL Full"));
     T2Radio = new QRadioButton(tr("T-2 Categorised"));
     T2RadioFull = new QRadioButton(tr("T-2 Full"));
     sessionBox = new QCheckBox(tr("Enable Session store"));

     connect(siolRadio, SIGNAL(clicked()), this, SLOT(setPlaylist()));
     connect(T2Radio, SIGNAL(clicked()), this, SLOT(setPlaylist()));
     connect(T2RadioFull, SIGNAL(clicked()), this, SLOT(setPlaylist()));

     QVBoxLayout *layout = new QVBoxLayout;
     layout->addWidget(siol);
     layout->addWidget(siolRadio);
     layout->addWidget(t2);
     layout->addWidget(T2Radio);
     layout->addWidget(T2RadioFull);
     layout->insertSpacerItem(5,new QSpacerItem(10,10,QSizePolicy::Expanding,QSizePolicy::Expanding));
     layout->addWidget(sessionLabel);
     layout->addWidget(sessionBox);
     setLayout(layout);

     registerField("playlist*", playlist);
     registerField("type*", type);
     registerField("session", sessionBox);
}

int SettingsPage::nextId() const
{
	return FirstRun::Page_Conclusion;
}

void SettingsPage::setPlaylist()
{
	if(siolRadio->isChecked()) {
		playlist->setText("playlists/siol.xml");
		type->setText(siolRadio->text());
	} else if(T2Radio->isChecked()) {
		playlist->setText("playlists/t-2-cat.xml");
		type->setText(T2Radio->text());
	} else if(T2RadioFull->isChecked()) {
		playlist->setText("playlists/t-2-full.xml");
		type->setText(T2RadioFull->text());
	}
}

ConclusionPage::ConclusionPage(QWidget *parent)
    : QWizardPage(parent)
{
    setTitle(tr("Complete Wizard"));
    setPixmap(QWizard::WatermarkPixmap, QPixmap(":/icons/images/wizard.bmp"));

    settings = Common::settings();

    topLabel = new QLabel(tr("Thank you for using <i>Tano</i>."));
    topLabel->setWordWrap(true);

    license = new License(this);

    agreeCheckBox = new QCheckBox(tr("I agree to the terms of the GNU General Public License"));

    registerField("agree*", agreeCheckBox);

    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(topLabel);
    layout->insertSpacerItem(1,new QSpacerItem(10,10,QSizePolicy::Expanding,QSizePolicy::Expanding));
    layout->addWidget(license);
    layout->addWidget(agreeCheckBox);
    setLayout(layout);
}

int ConclusionPage::nextId() const
{
	settings->setValue("version",Common::version());
	settings->setValue("registered",true);
	settings->setValue("playlist",field("playlist").toString());
	settings->setValue("session",field("session").toBool());

    return -1;
}
