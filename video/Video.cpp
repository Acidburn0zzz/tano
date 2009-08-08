#include <QMouseEvent>
#include <QDebug>
#include <QApplication>
#include <QDesktopWidget>

#include "Video.h"

Video::Video(QWidget *parent)
    : VideoWidget(parent)
{
	channel = new Phonon::MediaObject(parent);
	channel->setTickInterval(1000);
	audio = new Phonon::AudioOutput(Phonon::VideoCategory, parent);
	Phonon::createPath(channel, this);
	Phonon::createPath(channel, audio);

	timer = new QTimer(this);
	connect(timer, SIGNAL(timeout()), this, SLOT(hideMouse()));

	connect(channel, SIGNAL(tick(qint64)), this, SIGNAL(tick(qint64)));
	connect(channel, SIGNAL(totalTimeChanged(qint64)), this, SIGNAL(totalTimeChanged(qint64)));

	audio->setVolume(0.5);
	pos = QPoint();
	move = true;
}


Video::~Video()
{

}

//Events:
void Video::mouseDoubleClickEvent(QMouseEvent *event)
{
	event->ignore();
	emit full();
}
void Video::mouseMoveEvent(QMouseEvent *event)
{
	event->ignore();

	int h = QApplication::desktop()->height();

	if(this->isFullScreen() && event->globalPos() != pos && move) {
		qApp->setOverrideCursor(Qt::ArrowCursor);
		//emit mouseMove();
		pos = event->globalPos();

		if(event->globalPos().y() > h-105) {
			emit osd(false);
			timer->stop();
		} else {
			emit osd(true);
			timer->start(1000);
		}
	}
}
void Video::mousePressEvent(QMouseEvent *event)
{
	event->ignore();

	if(event->button() == Qt::RightButton) {
		qApp->setOverrideCursor(Qt::ArrowCursor);
		emit rightClick(event->globalPos());
	}
}
void Video::wheelEvent(QWheelEvent *event)
{
	event->ignore();

	if(event->delta()>0)
		emit wheel(true);
	else
		emit wheel(false);
}

void Video::hideMouse()
{
	if(this->isFullScreen() && move) {
		qApp->setOverrideCursor(Qt::BlankCursor);
		timer->stop();
	}
}

//Public functions:
void Video::playTv(QString fileName, QString channelName)
{
	channel->setCurrentSource(fileName);
	channel->play();

	currentChannel = channelName;
	emit playing(currentChannel);
}
QString Video::currentMedia()
{
	return channel->currentSource().fileName();
}

//Controls:
void Video::controlPlay()
{
	channel->setCurrentSource(source);
	channel->play();
	emit playing(currentChannel);
}
void Video::controlStop()
{
	channel->stop();
	source = channel->currentSource();
	channel->setCurrentSource(QString("udp://"));
	emit stopped();
}
void Video::controlFull()
{
	if (this->isFullScreen() == false) {
		this->enterFullScreen();
	}
	else {
		qApp->setOverrideCursor(Qt::ArrowCursor);
		this->exitFullScreen();
	}
}
void Video::controlMute(bool mute)
{
	if(!mute) {
		audio->setMuted(false);
		emit volumeChanged(volumeOld);
	} else {
                volumeOld = volume;
		audio->setMuted(true);
		emit volumeChanged(0);
	}
}
void Video::controlVUp()
{
    if(volume+1 <= 200) {
        volume++;
        emit volumeChanged(volume);
    } else {
        volume = 200;
        emit volumeChanged(volume);
    }
}
void Video::controlVDown()
{
    if(volume-1 >= 0) {
        volume--;
        emit volumeChanged(volume);
    } else {
        volume = 0;
        emit volumeChanged(volume);
    }
}
void Video::controlVolume(int vol)
{
        volume = vol;
        qreal v = vol;
	qreal n = v/100;
	audio->setVolume(n);

	if(this->isFullScreen()) {
		timer->start(1000);
		emit mouseMove();
	}
}
void Video::controlDuration(int d)
{
	qint64 tm = d;
	channel->seek(tm);
}

//Ratio
void Video::ratioOriginal()
{
	this->setAspectRatio(Phonon::VideoWidget::AspectRatioAuto);
}
void Video::ratio43()
{
	this->setAspectRatio(Phonon::VideoWidget::AspectRatio4_3);
}
void Video::ratio169()
{
	this->setAspectRatio(Phonon::VideoWidget::AspectRatio16_9);
}
void Video::ratioDinamic()
{
	this->setAspectRatio(Phonon::VideoWidget::AspectRatioWidget);
}


//Crop
void Video::cropOriginal()
{
	this->setScaleMode(Phonon::VideoWidget::FitInView);
}
void Video::cropFit()
{
	this->setScaleMode(Phonon::VideoWidget::ScaleAndCrop);
}

//Move
void Video::disableMove()
{
	move = false;
}
void Video::enableMove()
{
	move = true;
}
