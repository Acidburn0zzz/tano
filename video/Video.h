#ifndef VIDEO_H
#define VIDEO_H

#include <phonon/videowidget.h>
#include <phonon/mediaobject.h>
#include <phonon/audiooutput.h>
#include <phonon/volumeslider.h>
#include <QShortcut>

class Video : public Phonon::VideoWidget
{
    Q_OBJECT

public:
	Video(QWidget *parent = 0);
	~Video();

	void playTv(QString fileName, QString channelName);

	Phonon::VolumeSlider *slider();
	QString currentMedia();

public slots:
	void controlPlay();
	void controlStop();
	void controlFull();

signals:
	void playing(QString);
	void stopped();

private:
	Phonon::AudioOutput *audio;
	Phonon::MediaObject *channel;
	Phonon::VolumeSlider *aslider;

	QShortcut *shortcutFull;
	QString currentChannel;
};

#endif // VIDEO_H
