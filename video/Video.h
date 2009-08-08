#ifndef VIDEO_H
#define VIDEO_H

#include <phonon/videowidget.h>
#include <phonon/mediaobject.h>
#include <phonon/audiooutput.h>
#include <phonon/mediasource.h>

#include <QTimer>
#include <QPoint>

class Video : public Phonon::VideoWidget
{
    Q_OBJECT

public:
	Video(QWidget *parent = 0);
	~Video();

	void playTv(QString fileName, QString channelName);
	QString currentMedia();

protected:
	void mouseDoubleClickEvent(QMouseEvent *event);
	void mouseMoveEvent(QMouseEvent *event);
	void mousePressEvent(QMouseEvent *event);
	void wheelEvent(QWheelEvent *event);

public slots:
	void controlPlay();
	void controlStop();
	void controlFull();
	void controlMute(bool mute);
	void controlVUp();
	void controlVDown();
	void controlVolume(int vol);
	void controlDuration(int d);

	void ratioOriginal();
	void ratio43();
	void ratio169();
	void ratioDinamic();
	void cropOriginal();
	void cropFit();

	void disableMove();
	void enableMove();

signals:
	void playing(QString);
	void stopped();
	void full();

	void rightClick(QPoint);
	void wheel(bool);
	void mouseMove();

	void volumeChanged(int);

	void osd(bool);

	void tick(qint64);
	void totalTimeChanged(qint64);

private slots:
	void hideMouse();

private:
	Phonon::AudioOutput *audio;
	Phonon::MediaObject *channel;
	Phonon::MediaSource source;

	QString currentChannel;
	QTimer *timer;
	QPoint pos;

	bool move;
	int volumeOld;
        int volume;
};

#endif // VIDEO_H
