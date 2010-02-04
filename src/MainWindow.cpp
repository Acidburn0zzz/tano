#include <QFileDialog>
#include <QDesktopWidget>
#include <QInputDialog>
#include <QMessageBox>
#include <QDir>
#include <QSettings>
#include <QSplashScreen>
#include <QDebug>
#include <QBitmap>
#include "MainWindow.h"
#include "Common.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
	QPixmap pixmap(":/icons/images/splash.png");
	QSplashScreen *splash = new QSplashScreen(pixmap);
	splash->setMask(pixmap.mask());
	splash->show();

	ui.setupUi(this);
	ui.toolBarOsd->addWidget(ui.controlsWidget);

#if VLC_TRUNK
	ui.menuDeinterlacing->setEnabled(true);
#endif

	settings = Common::settings();

	backend = new VlcInstance(Common::libvlcArgs(), ui.videoWidget->getWinId());
	backend->init();

	controller = new VlcControl();
	flags = this->windowFlags();

	update = new Updates();
	epg = new Epg();
	epgShow = new EpgShow();
	select = 0;

	editor = new EditPlaylist(this);

	time = new Time();
	timers = new TimersManager(time);

	createSettings();
	createMenus();
	createConnections();
	createShortcuts();
	createSession();

	if(settings->value("updates",true).toBool())
		update->getUpdates();

	splash->close();
	delete splash;
}

MainWindow::~MainWindow()
{
	if(sessionEnabled) {
		QSettings session(QSettings::IniFormat, QSettings::UserScope, "Tano", "Settings");
		session.beginGroup("Session");
        session.setValue("volume", ui.volumeSlider->volume());
		session.setValue("channel", ui.channelNumber->value());
		session.endGroup();
	}
}

void MainWindow::exit()
{
	int ret;
	if(ui.recorder->isRecording()) {
		ret = QMessageBox::warning(this, tr("Tano"),
								   tr("Do you want to exit Tano?\nThis will stop recording in progress."),
								   QMessageBox::Close | QMessageBox::Cancel,
								   QMessageBox::Close);
	} else {
		ret = QMessageBox::Close;
	}

	switch (ret) {
		case QMessageBox::Close:
			ui.recorder->stop();
			qApp->quit();
			break;
		case QMessageBox::Cancel:
			break;
		default:
			break;
	}
}

void MainWindow::closeEvent(QCloseEvent *event)
{
	if(settings->value("tray",false).toBool()) {
		tray();
		event->ignore();
	}
}

void MainWindow::createSettings()
{
	sessionEnabled = settings->value("session", true).toBool();
	defaultP = settings->value("playlist","playlists/siol-mpeg2.m3u").toString();

	openPlaylist(true);

	settings->beginGroup("GUI");
	if(settings->value("lite",false).toBool()) {
		lite();
	} else {
		isLite = false;
	}
	if(settings->value("ontop",false).toBool()) {
		ui.actionTop->trigger();
		top();
	}
	if(settings->value("OSD",true).toBool()) {
		osdEnabled = true;
		osd = new Osd();
		createOsd();
	} else {
		osdEnabled = false;
	}
	if(!settings->value("info",true).toBool()) {
		ui.infoWidget->hide();
		ui.actionChannel_info->setChecked(false);
	}
	if(settings->value("wheel",false).toBool()) {
		connect(ui.videoWidget, SIGNAL(wheel(bool)), this, SLOT(volumeControl(bool)));
	} else {
		connect(ui.videoWidget, SIGNAL(wheel(bool)), select, SLOT(channel(bool)));
	}
	settings->endGroup();

	settings->beginGroup("Recorder");
	if(settings->value("enabled",true).toBool() && Common::fripExists()) {
		connect(ui.actionRecorder, SIGNAL(triggered(bool)), this, SLOT(recorder(bool)));
		connect(ui.actionRecord, SIGNAL(triggered()), this, SLOT(recordNow()));
	} else {
		ui.buttonRecord->hide();
		ui.menuMedia->removeAction(ui.actionRecord);
		ui.menuFile->removeAction(ui.actionRecorder);
		ui.toolBar->removeAction(ui.actionRecorder);
		if(osdEnabled)
			osd->disableRecorder();
	}
	settings->endGroup();
}

void MainWindow::createConnections()
{
	connect(ui.actionUpdate, SIGNAL(triggered()), update, SLOT(getUpdates()));
	connect(ui.actionAbout, SIGNAL(triggered()), this, SLOT(aboutTano()));
	connect(ui.actionClose, SIGNAL(triggered()), this, SLOT(exit()));

	connect(ui.actionTop, SIGNAL(triggered()), this, SLOT(top()));
	connect(ui.actionLite, SIGNAL(triggered()), this, SLOT(lite()));

	connect(ui.actionOpenToolbar, SIGNAL(triggered()), this, SLOT(menuOpen()));
	connect(ui.actionOpen, SIGNAL(triggered()), this, SLOT(openPlaylist()));
	connect(ui.actionOpenFile, SIGNAL(triggered()), this, SLOT(openFile()));
	connect(ui.actionOpenUrl, SIGNAL(triggered()), this, SLOT(openUrl()));

	connect(ui.actionSettings, SIGNAL(triggered()), this, SLOT(showSettings()));
	connect(ui.actionEditPlaylist, SIGNAL(triggered()), editor, SLOT(open()));
	connect(ui.actionTimers, SIGNAL(triggered()), timers, SLOT(show()));

	connect(ui.actionPlay, SIGNAL(triggered()), backend, SLOT(pause()));
	connect(ui.actionStop, SIGNAL(triggered()), backend, SLOT(stop()));
	connect(ui.actionStop, SIGNAL(triggered()), this, SLOT(stop()));
	connect(ui.actionBack, SIGNAL(triggered()), select, SLOT(back()));
	connect(ui.actionNext, SIGNAL(triggered()), select, SLOT(next()));

	connect(ui.infoBarWidget, SIGNAL(refresh()), epg, SLOT(refresh()));
	connect(ui.infoBarWidget, SIGNAL(open(QString)), epgShow, SLOT(open(QString)));

	connect(ui.playlistWidget, SIGNAL(itemClicked(QTreeWidgetItem*, int)), this, SLOT(playlist(QTreeWidgetItem*)));
	connect(select, SIGNAL(channelSelect(int)), this, SLOT(key(int)));

	connect(trayIcon, SIGNAL(restoreClick()), this, SLOT(tray()));
	connect(ui.actionTray, SIGNAL(triggered()), this, SLOT(tray()));

	connect(ui.videoWidget, SIGNAL(rightClick(QPoint)), this, SLOT(showRightMenu(QPoint)));

	connect(epg, SIGNAL(epgDone(int,QStringList,QString)), this, SLOT(showEpg(int,QStringList,QString)));
	connect(ui.epgToday, SIGNAL(urlClicked(QString)), epgShow, SLOT(open(QString)));
	connect(ui.epgToday_2, SIGNAL(urlClicked(QString)), epgShow, SLOT(open(QString)));
	connect(ui.epgToday_3, SIGNAL(urlClicked(QString)), epgShow, SLOT(open(QString)));
	connect(ui.epgToday_4, SIGNAL(urlClicked(QString)), epgShow, SLOT(open(QString)));
	connect(update, SIGNAL(updatesDone(QStringList)), trayIcon, SLOT(message(QStringList)));

	connect(rightMenu, SIGNAL(aboutToHide()), ui.videoWidget, SLOT(enableMove()));
	connect(rightMenu, SIGNAL(aboutToShow()), ui.videoWidget, SLOT(disableMove()));

	connect(controller, SIGNAL(vlcAction(QString, QList<QAction*>)), this, SLOT(processMenu(QString, QList<QAction*>)));
	connect(controller, SIGNAL(stateChanged(int)), this, SLOT(playingState(int)));
}

void MainWindow::createMenus()
{
	ratioGroup = new QActionGroup(this);
	ratioGroup->addAction(ui.actionRatioOriginal);
	ratioGroup->addAction(ui.actionRatio1_1);
	ratioGroup->addAction(ui.actionRatio4_3);
	ratioGroup->addAction(ui.actionRatio16_9);
	ratioGroup->addAction(ui.actionRatio16_10);
	ratioGroup->addAction(ui.actionRatio2_21_1);
	ratioGroup->addAction(ui.actionRatio5_4);

	cropGroup = new QActionGroup(this);
	cropGroup->addAction(ui.actionCropOriginal);
	cropGroup->addAction(ui.actionCrop1_1);
	cropGroup->addAction(ui.actionCrop4_3);
	cropGroup->addAction(ui.actionCrop16_9);
	cropGroup->addAction(ui.actionCrop16_10);
	cropGroup->addAction(ui.actionCrop1_85_1);
	cropGroup->addAction(ui.actionCrop2_21_1);
	cropGroup->addAction(ui.actionCrop2_35_1);
	cropGroup->addAction(ui.actionCrop2_39_1);
	cropGroup->addAction(ui.actionCrop5_4);
	cropGroup->addAction(ui.actionCrop5_3);

	filterGroup = new QActionGroup(this);
	filterGroup->addAction(ui.actionFilterDisabled);
	filterGroup->addAction(ui.actionFilterDiscard);
	filterGroup->addAction(ui.actionFilterBlend);
	filterGroup->addAction(ui.actionFilterMean);
	filterGroup->addAction(ui.actionFilterBob);
	filterGroup->addAction(ui.actionFilterLinear);
	filterGroup->addAction(ui.actionFilterX);

	rightMenu = new QMenu();
	rightMenu->addAction(ui.actionPlay);
	rightMenu->addAction(ui.actionStop);
	rightMenu->addAction(ui.actionBack);
	rightMenu->addAction(ui.actionNext);
	rightMenu->addSeparator();
	rightMenu->addAction(ui.actionTop);
	rightMenu->addAction(ui.actionLite);
	rightMenu->addAction(ui.actionFullscreen);
	rightMenu->addSeparator();
	rightMenu->addMenu(ui.menuVolume);
	rightMenu->addMenu(ui.menuVideo);
	rightMenu->addSeparator();
	rightMenu->addAction(ui.actionTray);
	rightMenu->addAction(ui.actionClose);

	openMenu = new QMenu();
	openMenu->addAction(ui.actionOpenFile);
	openMenu->addAction(ui.actionOpenUrl);
	openMenu->addAction(ui.actionOpen);

	trayIcon = new TrayIcon(rightMenu);
	trayIcon->show();
}

void MainWindow::createShortcuts()
{
	actions << ui.actionPlay
			<< ui.actionStop
			<< ui.actionNext
			<< ui.actionBack
			<< ui.actionFullscreen
			<< ui.actionMute
			<< ui.actionVolumeUp
			<< ui.actionVolumeDown
			<< ui.actionRecord
			<< ui.actionOpenFile
			<< ui.actionOpenUrl
			<< ui.actionOpen
			<< ui.actionEditPlaylist
			<< ui.actionSettings
			<< ui.actionTop
			<< ui.actionLite
			<< ui.actionAbout;

	shortcuts = new Shortcuts(actions);
}

void MainWindow::createSession()
{
	if(sessionEnabled) {
		settings->beginGroup("Session");
        ui.volumeSlider->setVolume(settings->value("volume",50).toString().toInt());
		if(hasPlaylist)
			key(settings->value("channel",1).toInt());
		settings->endGroup();
	}
}

void MainWindow::aboutTano()
{
	Common::about();
}

//Media controls
void MainWindow::playlist(QTreeWidgetItem* clickedChannel)
{
	Channel *tmp = ui.playlistWidget->channelRead(clickedChannel);
	if (tmp->isCategory() != true) {
		channel = tmp;
		play();
	}
}

void MainWindow::key(int clickedChannel)
{
	Channel *tmp = ui.playlistWidget->channelReadNum(clickedChannel);
	if (tmp->isCategory() != true) {
		channel = tmp;
		play();
	}
}

void MainWindow::playingState(int status)
{
	if(status == 1) {
		ui.actionPlay->setEnabled(true);
		ui.buttonPlay->setEnabled(true);
		ui.actionPlay->setIcon(QIcon(":/icons/images/player_pause.png"));
		ui.buttonPlay->setIcon(QIcon(":/icons/images/player_pause.png"));
		ui.actionPlay->setText(tr("Pause"));
		ui.actionPlay->setToolTip(tr("Pause"));
		ui.buttonPlay->setToolTip(tr("Pause"));
		ui.buttonPlay->setStatusTip(tr("Pause"));
	} else if(status == 0) {
		ui.actionPlay->setEnabled(true);
		ui.buttonPlay->setEnabled(true);
		ui.actionPlay->setIcon(QIcon(":/icons/images/player_play.png"));
		ui.buttonPlay->setIcon(QIcon(":/icons/images/player_play.png"));
		ui.actionPlay->setText(tr("Play"));
		ui.actionPlay->setToolTip(tr("Play"));
		ui.buttonPlay->setToolTip(tr("Play"));
		ui.buttonPlay->setStatusTip(tr("Play"));
	} else if(status == -1) {
		ui.actionPlay->setEnabled(false);
		ui.buttonPlay->setEnabled(false);
		ui.actionPlay->setText(tr("Play"));
		ui.actionPlay->setToolTip(tr("Play"));
		ui.buttonPlay->setToolTip(tr("Play"));
		ui.buttonPlay->setStatusTip(tr("Play"));
	}
}

void MainWindow::play(QString itemFile, QString itemType)
{
	this->stop();

	if(itemFile.isNull()) {
		ui.infoBarWidget->setInfo(channel->name(), channel->language());

		if(osdEnabled) {
			osd->setNumber(channel->num());
			osd->setInfo(channel->name(), channel->language());
		}

		epg->getEpg(channel->epg());

		ui.channelNumber->display(channel->num());

		backend->openMedia(channel->url());
		tooltip(channel->name());
		trayIcon->changeToolTip(channel->name());
	} else if(itemType == "file") {
	    ui.infoWidget->hide();
	    backend->openMedia(fileName);
		tooltip(fileName);
	} else {
		ui.infoWidget->hide();
		backend->openMedia(fileName);
    	tooltip(fileName);
	}
}

void MainWindow::showEpg(int id, QStringList epgValue, QString date)
{
	switch (id) {
		case 0:
			ui.infoBarWidget->setEpg(epgValue.at(0), epgValue.at(1));

			if(osdEnabled)
				osd->setEpg(true, epgValue.at(0), epgValue.at(1));

			break;
		case 1:
			ui.epgTabWidget->setTabText(0,date);
			ui.epgToday->setEpg(epgValue);
			break;
		case 2:
			ui.epgTabWidget->setTabText(1,date);
			ui.epgToday_2->setEpg(epgValue);
			break;
		case 3:
			ui.epgTabWidget->setTabText(2,date);
			ui.epgToday_3->setEpg(epgValue);
			break;
		case 4:
			ui.epgTabWidget->setTabText(3,date);
			ui.epgToday_4->setEpg(epgValue);
			break;
		default:
			break;
	}
}

void MainWindow::stop()
{
	ui.epgToday->epgClear();
	ui.epgToday_2->epgClear();
	ui.epgToday_3->epgClear();
	ui.epgToday_4->epgClear();
	ui.actionRatioOriginal->trigger();
	ui.actionCropOriginal->trigger();
	ui.infoBarWidget->clear();
	if(osdEnabled) {
		osd->setInfo();
		osd->setEpg(false);
	}
	epg->stop();
	tooltip();
	trayIcon->changeToolTip();
}

void MainWindow::openPlaylist(bool start)
{
	if (!start)
    	fileName =
            QFileDialog::getOpenFileName(this, tr("Open Channel list File"),
                                         QDir::homePath(),
                                         tr("Tano TV Channel list Files(*.m3u)"));
	else
		fileName = Common::locateResource(defaultP);

	if (!fileName.isEmpty()) {
	    editor->setFile(fileName);
	    ui.recorder->openPlaylist(fileName);
	    timers->openPlaylist(fileName);
	} else
        return;

	ui.playlistWidget->open(fileName);

    hasPlaylist = true;

    if(select != 0)
    	delete select;

    select = new ChannelSelect(this, ui.channelNumber, ui.playlistWidget->nums());

    ui.channelToolBox->setItemText(0,ui.playlistWidget->name());
}

void MainWindow::openFile()
{
	fileName =
        QFileDialog::getOpenFileName(this, tr("Open File or URL"),
									QDir::homePath(),
									tr("Multimedia files(*)"));

    if (fileName.isEmpty())
        return;

    play(fileName, "file");
}

void MainWindow::openUrl()
{
	bool ok;
	fileName =
		QInputDialog::getText(this, tr("Open URL or stream"),
							 tr("Enter the URL of multimedia file or stream you want to play:"),
							 QLineEdit::Normal, "", &ok);

	if (!ok && fileName.isEmpty())
		return;

	play(fileName,"url");
}


//GUI
void MainWindow::showSettings()
{
    EditSettings s(this, shortcuts);
    s.exec();
}

void MainWindow::tooltip(QString channelNow)
{
	if (channelNow != "stop")
		setWindowTitle(channelNow + " - " + tr("Tano"));
	else
		setWindowTitle(tr("Tano"));
}

void MainWindow::showRightMenu(QPoint pos)
{
	rightMenu->exec(pos);
}

void MainWindow::menuOpen()
{
	openMenu->exec(QCursor::pos());
}

void MainWindow::top()
{
	Qt::WindowFlags top = flags;
	top |= Qt::WindowStaysOnTopHint;
	if(ui.actionTop->isChecked())
		this->setWindowFlags(top);
	else
		this->setWindowFlags(flags);

	this->show();
}

void MainWindow::lite()
{
	if(isLite) {
		ui.infoWidget->show();
		ui.toolBar->show();
		ui.toolBarOsd->show();
		isLite = false;
	} else {
		ui.infoWidget->hide();
		ui.toolBar->hide();
		ui.toolBarOsd->hide();
		isLite = true;
	}
}

void MainWindow::tray()
{
	if (!trayIcon->isVisible())
		return;

	if(this->isHidden()) {
		ui.actionTray->setText(tr("Hide to tray"));
		show();
	} else {
		ui.actionTray->setText(tr("Restore"));
		trayIcon->message(QStringList() << "close");
		hide();
	}
}

void MainWindow::volumeControl(bool type)
{
	if(type)
		ui.actionVolumeUp->trigger();
	else
		ui.actionVolumeDown->trigger();
}

void MainWindow::createOsd()
{
	ui.videoWidget->setOsd(QApplication::desktop()->width(),osd->height(),0,QApplication::desktop()->height()-osd->height());

	connect(osd, SIGNAL(play()), ui.actionPlay, SLOT(trigger()));
	connect(osd, SIGNAL(stop()), ui.actionStop, SLOT(trigger()));
	connect(osd, SIGNAL(back()), ui.actionBack, SLOT(trigger()));
	connect(osd, SIGNAL(next()), ui.actionNext, SLOT(trigger()));
	connect(osd, SIGNAL(mute()), ui.actionMute, SLOT(trigger()));

	connect(ui.actionMute, SIGNAL(triggered(bool)), osd, SLOT(setMuted(bool)));

	connect(ui.videoWidget, SIGNAL(full()), osd, SLOT(hideOsd()));
	connect(ui.videoWidget, SIGNAL(mouseMove()), osd, SLOT(showOsd()));
	connect(ui.videoWidget, SIGNAL(osd(bool)), osd, SLOT(setStatus(bool)));

	connect(osd, SIGNAL(linkActivated(QString)), epgShow, SLOT(open(QString)));
	connect(osd, SIGNAL(linkActivated(QString)), epgShow, SLOT(open(QString)));

	connect(controller, SIGNAL(stateChanged(int)), osd, SLOT(playingState(int)));
}

void MainWindow::recordNow()
{
	ui.recorder->recordNow(ui.channelNumber->value(), channel->url(), channel->name());
}

void MainWindow::recorder(bool enabled)
{
	if(enabled) {
		ui.stackedWidget->setCurrentIndex(1);
		ui.infoWidget->setVisible(false);
		ui.toolBarOsd->setVisible(false);
	} else {
		ui.stackedWidget->setCurrentIndex(0);
		ui.infoWidget->setVisible(true);
		ui.toolBarOsd->setVisible(true);
	}
}

void MainWindow::processMenu(QString type, QList<QAction*> list)
{
	if(type == "sub")
		ui.menuSubtitles->clear();
	else if(type == "audio")
		ui.menuAudio_channel->clear();

	if(list.size()==0) {
		if(type == "sub")
			ui.menuSubtitles->setDisabled(true);
		else if(type == "audio")
			ui.menuAudio_channel->setDisabled(true);

		return;
	} else {
		if(type == "sub")
			ui.menuSubtitles->setDisabled(false);
		else if(type == "audio")
			ui.menuAudio_channel->setDisabled(false);
	}

	for (int i = 0; i < list.size(); ++i) {
		if(type == "sub")
			ui.menuSubtitles->addAction(list.at(i));
		else if(type == "audio")
			ui.menuAudio_channel->addAction(list.at(i));
	}
}
