#include <QtGui/QApplication>
#include <QtGui/QHBoxLayout>
#include <QtGui/QMouseEvent>
#include <QtGui/QToolBar>

#include "VlcInstance.h"
#include "VlcVideoWidget.h"

VlcVideoWidget::VlcVideoWidget(QWidget *parent)
	: QMainWindow(parent)
{
	setMouseTracking(true);

	move = true;

	widget = new QWidget(this);
	setCentralWidget(widget);
	widget->setMouseTracking(true);

	osd = 0;

	_osdWidth = 0;
	_osdHeight = 0;
	_osdPosLeft = 0;
	_osdPosTop = 0;

	timerMouse = new QTimer(this);
	connect(timerMouse, SIGNAL(timeout()), this, SLOT(hideMouse()));
	timerSettings = new QTimer(this);
	connect(timerSettings, SIGNAL(timeout()), this, SLOT(applyPreviousSettings()));

	_currentRatio = "";
	_currentCrop = "";
	_currentFilter = "";
}

VlcVideoWidget::~VlcVideoWidget()
{
	delete timerMouse;
	delete timerSettings;
	delete widget;
}

WId VlcVideoWidget::getWinId()
{
	return widget->winId();
}

void VlcVideoWidget::setOsd(int width, int height, int posLeft, int posTop)
{
	_osdWidth = width;
	_osdHeight = height;
	_osdPosLeft = posLeft;
	_osdPosTop = posTop;
}

void VlcVideoWidget::setToolbar(QToolBar *toolbar)
{
	osd = toolbar;
}

//Events:
void VlcVideoWidget::mouseDoubleClickEvent(QMouseEvent *event)
{
	event->ignore();
	emit full();
}
void VlcVideoWidget::mouseMoveEvent(QMouseEvent *event)
{
	event->ignore();

	if(this->isFullScreen() && move) {
		qApp->setOverrideCursor(Qt::ArrowCursor);

	osd->show();
	timerMouse->start(2000);
	}
}
void VlcVideoWidget::mousePressEvent(QMouseEvent *event)
{
	event->ignore();

	if(event->button() == Qt::RightButton) {
		qApp->setOverrideCursor(Qt::ArrowCursor);
		emit rightClick(event->globalPos());
	}
}
void VlcVideoWidget::wheelEvent(QWheelEvent *event)
{
	event->ignore();

	if(event->delta()>0)
		emit wheel(true);
	else
		emit wheel(false);
}

void VlcVideoWidget::hideMouse()
{
	if(this->isFullScreen() && move) {
		qApp->setOverrideCursor(Qt::BlankCursor);
		timerMouse->stop();
		osd->hide();
	}
}

//Move
void VlcVideoWidget::disableMove() { move = false; }
void VlcVideoWidget::enableMove() {	move = true; }

void VlcVideoWidget::controlFull()
{
	Qt::WindowFlags flags = windowFlags();
	if (!isFullScreen()) {
		flags |= Qt::Window;
		flags ^= Qt::SubWindow;
		setWindowFlags(flags);
#ifdef Q_WS_X11
		// This works around a bug with Compiz
		// as the window must be visible before we can set the state
		show();
		raise();
		setWindowState( windowState() | Qt::WindowFullScreen );
#else
		setWindowState( windowState() | Qt::WindowFullScreen );
		show();
#endif
	} else if (isFullScreen()) {
		flags ^= (Qt::Window | Qt::SubWindow);
		setWindowFlags(flags);
		setWindowState( windowState()  ^ Qt::WindowFullScreen );
		qApp->setOverrideCursor(Qt::ArrowCursor);
		show();
	}

	osd->show();
}

void VlcVideoWidget::teletext()
{
#if VLC_TRUNK
	libvlc_toggle_teletext(_vlcCurrentMediaPlayer);
#else
	libvlc_toggle_teletext(_vlcCurrentMediaPlayer, _vlcException);
#endif

	VlcInstance::checkError();
}
int VlcVideoWidget::teletextPage()
{
#if VLC_TRUNK
	return libvlc_video_get_teletext(_vlcCurrentMediaPlayer);
#else
	return libvlc_video_get_teletext(_vlcCurrentMediaPlayer, _vlcException);
#endif

	VlcInstance::checkError();
}
void VlcVideoWidget::setTeletextPage(const int &page)
{
#if VLC_TRUNK
	libvlc_video_set_teletext(_vlcCurrentMediaPlayer, page);
#else
	libvlc_video_set_teletext(_vlcCurrentMediaPlayer, page, _vlcException);
#endif

	VlcInstance::checkError();
}

void VlcVideoWidget::setPreviousSettings()
{
	timerSettings->start(500);
}
void VlcVideoWidget::applyPreviousSettings()
{
	if(_currentRatio == "" && _currentCrop == "" && _currentFilter == "") {
		timerSettings->stop();
		return;
	}

	QString success = "";
	if (_vlcCurrentMediaPlayer) {
#if VLC_TRUNK
		if(QString(libvlc_video_get_aspect_ratio(_vlcCurrentMediaPlayer)) != _currentRatio)
			libvlc_video_set_aspect_ratio(_vlcCurrentMediaPlayer, _currentRatio.toAscii().data());
		else
			success.append("+");
		if(QString(libvlc_video_get_crop_geometry(_vlcCurrentMediaPlayer)) != _currentCrop)
			libvlc_video_set_crop_geometry(_vlcCurrentMediaPlayer, _currentCrop.toAscii().data());
		else
			success.append("+");

		libvlc_video_set_deinterlace(_vlcCurrentMediaPlayer, _currentFilter.toAscii().data());
#else
		if(QString(libvlc_video_get_aspect_ratio(_vlcCurrentMediaPlayer, _vlcException)) != _currentRatio)
			libvlc_video_set_aspect_ratio(_vlcCurrentMediaPlayer, _currentRatio.toAscii().data(), _vlcException);
		else
			success.append("+");
		if(QString(libvlc_video_get_crop_geometry(_vlcCurrentMediaPlayer, _vlcException)) != _currentCrop)
			libvlc_video_set_crop_geometry(_vlcCurrentMediaPlayer, _currentCrop.toAscii().data(), _vlcException);
		else
			success.append("+");
#endif
	}

	if(success == "++")
		timerSettings->stop();

	VlcInstance::checkError();
}

void VlcVideoWidget::setRatioOriginal()
{
	if (_vlcCurrentMediaPlayer) {
		_currentRatio = "";
#if VLC_TRUNK
		libvlc_video_set_aspect_ratio(_vlcCurrentMediaPlayer, QString("").toAscii().data());
#else
		libvlc_video_set_aspect_ratio(_vlcCurrentMediaPlayer, QString("").toAscii().data(), _vlcException);
#endif

		VlcInstance::checkError();
	}
}
void VlcVideoWidget::setRatio1_1()
{
	if (_vlcCurrentMediaPlayer) {
		_currentRatio = "1:1";
#if VLC_TRUNK
		libvlc_video_set_aspect_ratio(_vlcCurrentMediaPlayer, QString("1:1").toAscii().data());
#else
		libvlc_video_set_aspect_ratio(_vlcCurrentMediaPlayer, QString("1:1").toAscii().data(), _vlcException);
#endif

		VlcInstance::checkError();
	}
}
void VlcVideoWidget::setRatio4_3()
{
	if (_vlcCurrentMediaPlayer) {
		_currentRatio = "4:3";
#if VLC_TRUNK
		libvlc_video_set_aspect_ratio(_vlcCurrentMediaPlayer, QString("4:3").toAscii().data());
#else
		libvlc_video_set_aspect_ratio(_vlcCurrentMediaPlayer, QString("4:3").toAscii().data(), _vlcException);
#endif

		VlcInstance::checkError();
	}
}
void VlcVideoWidget::setRatio16_9()
{
	if (_vlcCurrentMediaPlayer) {
		_currentRatio = "16:9";
#if VLC_TRUNK
		libvlc_video_set_aspect_ratio(_vlcCurrentMediaPlayer, QString("16:9").toAscii().data());
#else
		libvlc_video_set_aspect_ratio(_vlcCurrentMediaPlayer, QString("16:9").toAscii().data(), _vlcException);
#endif

		VlcInstance::checkError();
	}
}
void VlcVideoWidget::setRatio16_10()
{
	if (_vlcCurrentMediaPlayer) {
		_currentRatio = "16:10";
#if VLC_TRUNK
		libvlc_video_set_aspect_ratio(_vlcCurrentMediaPlayer, QString("16:10").toAscii().data());
#else
		libvlc_video_set_aspect_ratio(_vlcCurrentMediaPlayer, QString("16:10").toAscii().data(), _vlcException);
#endif

		VlcInstance::checkError();
	}
}
void VlcVideoWidget::setRatio2_21_1()
{
	if (_vlcCurrentMediaPlayer) {
		_currentRatio = "221:100";
#if VLC_TRUNK
		libvlc_video_set_aspect_ratio(_vlcCurrentMediaPlayer, QString("221:100").toAscii().data());
#else
		libvlc_video_set_aspect_ratio(_vlcCurrentMediaPlayer, QString("221:100").toAscii().data(), _vlcException);
#endif

		VlcInstance::checkError();
	}
}
void VlcVideoWidget::setRatio5_4()
{
	if (_vlcCurrentMediaPlayer) {
		_currentRatio = "5:4";
#if VLC_TRUNK
		libvlc_video_set_aspect_ratio(_vlcCurrentMediaPlayer, QString("5:4").toAscii().data());
#else
		libvlc_video_set_aspect_ratio(_vlcCurrentMediaPlayer, QString("5:4").toAscii().data(), _vlcException);
#endif

		VlcInstance::checkError();
	}
}

void VlcVideoWidget::setCropOriginal()
{
	if (_vlcCurrentMediaPlayer) {
		_currentCrop = "";
#if VLC_TRUNK
		libvlc_video_set_crop_geometry(_vlcCurrentMediaPlayer, QString("").toAscii().data());
#else
		libvlc_video_set_crop_geometry(_vlcCurrentMediaPlayer, QString("").toAscii().data(), _vlcException);
#endif

		VlcInstance::checkError();
	}
}
void VlcVideoWidget::setCrop16_9()
{
	if (_vlcCurrentMediaPlayer) {
		_currentCrop = "16:9";
#if VLC_TRUNK
		libvlc_video_set_crop_geometry(_vlcCurrentMediaPlayer, QString("16:9").toAscii().data());
#else
		libvlc_video_set_crop_geometry(_vlcCurrentMediaPlayer, QString("16:9").toAscii().data(), _vlcException);
#endif

		VlcInstance::checkError();
	}
}
void VlcVideoWidget::setCrop16_10()
{
	if (_vlcCurrentMediaPlayer) {
		_currentCrop = "16:10";
#if VLC_TRUNK
		libvlc_video_set_crop_geometry(_vlcCurrentMediaPlayer, QString("16:10").toAscii().data());
#else
		libvlc_video_set_crop_geometry(_vlcCurrentMediaPlayer, QString("16:10").toAscii().data(), _vlcException);
#endif

		VlcInstance::checkError();
	}
}
void VlcVideoWidget::setCrop1_85_1()
{
	if (_vlcCurrentMediaPlayer) {
		_currentCrop = "185:100";
#if VLC_TRUNK
		libvlc_video_set_crop_geometry(_vlcCurrentMediaPlayer, QString("185:100").toAscii().data());
#else
		libvlc_video_set_crop_geometry(_vlcCurrentMediaPlayer, QString("185:100").toAscii().data(), _vlcException);
#endif

		VlcInstance::checkError();
	}
}
void VlcVideoWidget::setCrop2_21_1()
{
	if (_vlcCurrentMediaPlayer) {
		_currentCrop = "221:100";
#if VLC_TRUNK
		libvlc_video_set_crop_geometry(_vlcCurrentMediaPlayer, QString("221:100").toAscii().data());
#else
		libvlc_video_set_crop_geometry(_vlcCurrentMediaPlayer, QString("221:100").toAscii().data(), _vlcException);
#endif

		VlcInstance::checkError();
	}
}
void VlcVideoWidget::setCrop2_35_1()
{		_currentCrop = "235:100";
	if (_vlcCurrentMediaPlayer) {

#if VLC_TRUNK
		libvlc_video_set_crop_geometry(_vlcCurrentMediaPlayer, QString("235:100").toAscii().data());
#else
		libvlc_video_set_crop_geometry(_vlcCurrentMediaPlayer, QString("235:100").toAscii().data(), _vlcException);
#endif

		VlcInstance::checkError();
	}
}
void VlcVideoWidget::setCrop2_39_1()
{
	if (_vlcCurrentMediaPlayer) {
		_currentCrop = "239:100";
#if VLC_TRUNK
		libvlc_video_set_crop_geometry(_vlcCurrentMediaPlayer, QString("239:100").toAscii().data());
#else
		libvlc_video_set_crop_geometry(_vlcCurrentMediaPlayer, QString("239:100").toAscii().data(), _vlcException);
#endif

		VlcInstance::checkError();
	}
}
void VlcVideoWidget::setCrop5_4()
{
	if (_vlcCurrentMediaPlayer) {
		_currentCrop = "5:4";
#if VLC_TRUNK
		libvlc_video_set_crop_geometry(_vlcCurrentMediaPlayer, QString("5:4").toAscii().data());
#else
		libvlc_video_set_crop_geometry(_vlcCurrentMediaPlayer, QString("5:4").toAscii().data(), _vlcException);
#endif

		VlcInstance::checkError();
	}
}
void VlcVideoWidget::setCrop5_3()
{
	if (_vlcCurrentMediaPlayer) {
		_currentCrop = "5:3";
#if VLC_TRUNK
		libvlc_video_set_crop_geometry(_vlcCurrentMediaPlayer, QString("5:3").toAscii().data());
#else
		libvlc_video_set_crop_geometry(_vlcCurrentMediaPlayer, QString("5:3").toAscii().data(), _vlcException);
#endif

		VlcInstance::checkError();
	}
}
void VlcVideoWidget::setCrop4_3()
{
	if (_vlcCurrentMediaPlayer) {
		_currentCrop = "4:3";
#if VLC_TRUNK
		libvlc_video_set_crop_geometry(_vlcCurrentMediaPlayer, QString("4:3").toAscii().data());
#else
		libvlc_video_set_crop_geometry(_vlcCurrentMediaPlayer, QString("4:3").toAscii().data(), _vlcException);
#endif

		VlcInstance::checkError();
	}
}
void VlcVideoWidget::setCrop1_1()
{
	if (_vlcCurrentMediaPlayer) {
		_currentCrop = "1:1";
#if VLC_TRUNK
		libvlc_video_set_crop_geometry(_vlcCurrentMediaPlayer, QString("1:1").toAscii().data());
#else
		libvlc_video_set_crop_geometry(_vlcCurrentMediaPlayer, QString("1:1").toAscii().data(), _vlcException);
#endif

		VlcInstance::checkError();
	}
}

void VlcVideoWidget::setFilterDisabled()
{
	if (_vlcCurrentMediaPlayer) {
		_currentFilter = "";
#if VLC_TRUNK
		libvlc_video_set_deinterlace(_vlcCurrentMediaPlayer, QString("").toAscii().data());
#endif

		VlcInstance::checkError();
	}
}
void VlcVideoWidget::setFilterDiscard()
{
	if (_vlcCurrentMediaPlayer) {
		_currentFilter = "discard";
#if VLC_TRUNK
		libvlc_video_set_deinterlace(_vlcCurrentMediaPlayer, QString("discard").toAscii().data());
#endif

		VlcInstance::checkError();
	}
}
void VlcVideoWidget::setFilterBlend()
{
	if (_vlcCurrentMediaPlayer) {
		_currentFilter = "blend";
#if VLC_TRUNK
		libvlc_video_set_deinterlace(_vlcCurrentMediaPlayer, QString("blend").toAscii().data());
#endif

		VlcInstance::checkError();
	}
}
void VlcVideoWidget::setFilterMean()
{
	if (_vlcCurrentMediaPlayer) {
		_currentFilter = "mean";
#if VLC_TRUNK
		libvlc_video_set_deinterlace(_vlcCurrentMediaPlayer, QString("mean").toAscii().data());
#endif

		VlcInstance::checkError();
	}
}
void VlcVideoWidget::setFilterBob()
{
	if (_vlcCurrentMediaPlayer) {
		_currentFilter = "bob";
#if VLC_TRUNK
		libvlc_video_set_deinterlace(_vlcCurrentMediaPlayer, QString("bob").toAscii().data());
#endif

		VlcInstance::checkError();
	}
}
void VlcVideoWidget::setFilterLinear()
{
	if (_vlcCurrentMediaPlayer) {
		_currentFilter = "linear";
#if VLC_TRUNK
		libvlc_video_set_deinterlace(_vlcCurrentMediaPlayer, QString("linear").toAscii().data());
#endif

		VlcInstance::checkError();
	}
}
void VlcVideoWidget::setFilterX()
{
	if (_vlcCurrentMediaPlayer) {
		_currentFilter = "x";
#if VLC_TRUNK
		libvlc_video_set_deinterlace(_vlcCurrentMediaPlayer, QString("x").toAscii().data());
#endif

		VlcInstance::checkError();
	}
}
