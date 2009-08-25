#ifndef VLCINSTANCE_H_
#define VLCINSTANCE_H_

#include <QObject>
#include <QWidget>
#include <QTimer>
#include <vlc/vlc.h>

extern libvlc_exception_t *_vlcException;
extern libvlc_instance_t *_vlcInstance;
extern libvlc_media_player_t *_vlcCurrentMediaPlayer;

class VlcInstance : public QObject {
Q_OBJECT
public:
	VlcInstance(WId widget = NULL);
	virtual ~VlcInstance();

	void openMedia(QString media);
	static void checkException();

public slots:
	void pause();
	void stop();
	void mute();

private slots:
	void updateActions();

private:
	void playInternal();
	void unloadMedia();
	bool _isPlaying;
	int _version;

	libvlc_media_player_t * _vlcMediaPlayer;
	libvlc_media_t * _vlcMedia;
	WId _widgetId;

	QTimer *timer;
};

#endif /* VLCINSTANCE_H_ */
