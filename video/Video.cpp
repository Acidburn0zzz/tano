#include <QMouseEvent>
#include <QDebug>

#include "Video.h"

Video::Video(QWidget *parent)
    : VideoWidget(parent)
{
	channel = new Phonon::MediaObject(parent);
	audio = new Phonon::AudioOutput(Phonon::VideoCategory, parent);
	aslider = new Phonon::VolumeSlider;
	aslider->setIconSize(QSize(32,32));
	aslider->setAudioOutput(audio);
	Phonon::createPath(channel, this);
	Phonon::createPath(channel, audio);

	audio->setVolume(0.5);
	qDebug() << "Volume:" << audio->volume()*100;

	shortcutFull = new QShortcut(QKeySequence(tr("Esc")),
	                          this);
}


Video::~Video()
{

}

void Video::mouseDoubleClickEvent(QMouseEvent *event)
{
	event->ignore();
	controlFull();
}

void Video::mousePressEvent(QMouseEvent *event)
{
	event->ignore();

	if(event->button() == Qt::RightButton)
		emit rightClick(event->globalPos());
}

void Video::wheelEvent(QWheelEvent *event)
{
	event->ignore();

	if(event->delta()>0)
		emit wheel(true);
	else
		emit wheel(false);
}

void Video::playTv(QString fileName, QString channelName)
{
	channel->setCurrentSource(fileName);
	channel->play();

	currentChannel = channelName;
	emit playing(currentChannel);
}

void Video::controlPlay()
{
	channel->play();
	emit playing(currentChannel);
}

void Video::controlStop()
{
	channel->stop();
	emit stopped();
}

void Video::controlFull()
{
	if (this->isFullScreen() == false) {
		this->enterFullScreen();
		connect(shortcutFull, SIGNAL(activated()), this, SLOT(controlFull()));
	}
	else {
		this->exitFullScreen();
		disconnect(shortcutFull, SIGNAL(activated()), this, SLOT(controlFull()));
	}
}

void Video::controlMute()
{
	if(audio->isMuted())
		audio->setMuted(false);
	else
		audio->setMuted(true);
}

void Video::controlVUp()
{
	audio->setVolume(audio->volume()+0.1);
	qDebug() << "Volume:" << audio->volume()*100;
}

void Video::controlVDown()
{
	audio->setVolume(audio->volume()-0.1);
	qDebug() << "Volume:" << audio->volume()*100;
}

Phonon::VolumeSlider *Video::slider()
{
	return aslider;
}

QString Video::currentMedia()
{
	return channel->currentSource().fileName();
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
