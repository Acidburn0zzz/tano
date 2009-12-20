#ifndef TANO_MAINWINDOW_H
#define TANO_MAINWINDOW_H

#include <QtGui/QMainWindow>
#include <QCloseEvent>
#include <QTime>
#include <QSettings>
#include <QErrorMessage>

#include "libvlc/VlcInstance.h"
#include "libvlc/VlcControl.h"
#include "ui_MainWindow.h"
#include "Updates.h"
#include "xml/tanohandler.h"
#include "channels/Channel.h"
#include "channels/EditPlaylist.h"
#include "ui/EditSettings.h"
#include "ui/TrayIcon.h"
#include "ui/Osd.h"
#include "control/ChannelSelect.h"
#include "control/Shortcuts.h"
#include "epg/Epg.h"
#include "epg/EpgShow.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

protected:
	void closeEvent(QCloseEvent *event);

private slots:
	void exit();

    void aboutTano();
    void playlist(QTreeWidgetItem* clickedChannel);
    void key(int clickedChannel);

    void play(QString itemFile = 0, QString itemType = 0);
    void pause();
    void stop();

    void playingState(int status);

    void openPlaylist(bool start = false);
    void openFile();
    void openUrl();
    void showSettings();

    void showEpg(int id, QStringList epgValue, QString date);

    void processUpdates(QString updates);

    void tooltip(QString channelNow = "stop");

    void rightMenu(QPoint pos);
    void menuOpen();
    void top();
    void lite();

    void recordNow();
    void recorder(bool enabled);
    void volumeControl(bool type);
    void processMenu(QString type, QList<QAction*> list);

signals:
    void setVolume(int);

private:
    Ui::MainWindow ui;
    Qt::WindowFlags flags;

    VlcInstance *backend;
    VlcControl *controller;

    Updates *update;
    Osd *osd;
    QSettings *settings;

    TanoHandler *handler;
    Channel *channel;
	QString fileName;
	QString defaultP;
	QString lastChannel;

	TrayIcon *trayIcon;
	Epg *epg;
	EpgShow *epgShow;
	EditPlaylist *editor;

	Shortcuts *shortcuts;
	ChannelSelect *select;

	QMenu *right;
	QMenu *open;
	QMenu *tray;
	QActionGroup *ratioGroup;
	QActionGroup *cropGroup;
	QActionGroup *filterGroup;
	QList<QAction*> actions;

	QTime timeNow;

	QErrorMessage *errorHandler;

	bool isLite;
	bool osdEnabled;
	bool sessionEnabled;
	bool hasPlaylist;

    void createConnections();
    void createMenus();
    void createShortcuts();
    void createSettings();
    void createSession();
    void createOsd();
};

#endif // TANO_MAINWINDOW_H
