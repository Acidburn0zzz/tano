#ifndef VLCINSTANCE_H_
#define VLCINSTANCE_H_

#include <QObject>
#include <QWidget>

#include <vlc/vlc.h>

extern libvlc_exception_t *_vlcException;
extern libvlc_instance_t *_vlcInstance;
extern libvlc_media_player_t *_vlcCurrentMediaPlayer;

class VlcInstance : public QObject {
Q_OBJECT
public:
	VlcInstance(bool settings = false, WId widget = NULL, QString iface = "");
	virtual ~VlcInstance();

	void openMedia(QString media);
	static void checkException();
	static QString version();

public slots:
	void init();
	void pause();
	void stop();
	void mute();

private:
	int fatalError();
	void playInternal();
	void unloadMedia();
	bool _isPlaying;

	libvlc_media_player_t * _vlcMediaPlayer;
	libvlc_media_t * _vlcMedia;
	WId _widgetId;
	QString _networkInterface;
};

#endif /* VLCINSTANCE_H_ */
