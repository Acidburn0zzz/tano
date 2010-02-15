#ifndef QVLC_VLCVIDEOWIDGET_H_
#define QVLC_VLCVIDEOWIDGET_H_

#include <QtCore/QTimer>
#include <QtGui/QMainWindow>

class VlcVideoWidget : public QMainWindow
{
    Q_OBJECT

public:
    VlcVideoWidget(QWidget *parent = 0);
    ~VlcVideoWidget();

	WId getWinId();
	void setOsd(int width, int height, int posLeft, int posTop);
	void setToolbar(QToolBar *toolbar);

protected:
	void mouseDoubleClickEvent(QMouseEvent *event);
	void mouseMoveEvent(QMouseEvent *event);
	void mousePressEvent(QMouseEvent *event);
	void wheelEvent(QWheelEvent *event);

signals:
	void full();
	void rightClick(QPoint);
	void wheel(bool);
	void mouseMove();

public slots:
	void disableMove();
	void enableMove();
	void controlFull();

	void teletext();
	int teletextPage();
	void setTeletextPage(const int &page);

	void setPreviousSettings();

	void setRatioOriginal();
	void setRatio1_1();
	void setRatio4_3();
	void setRatio16_9();
	void setRatio16_10();
	void setRatio2_21_1();
	void setRatio5_4();

	void setCropOriginal();
	void setCrop16_9();
	void setCrop16_10();
	void setCrop1_85_1();
	void setCrop2_21_1();
	void setCrop2_35_1();
	void setCrop2_39_1();
	void setCrop5_4();
	void setCrop5_3();
	void setCrop4_3();
	void setCrop1_1();

	void setFilterDisabled();
	void setFilterDiscard();
	void setFilterBlend();
	void setFilterMean();
	void setFilterBob();
	void setFilterLinear();
	void setFilterX();

private slots:
	void hideMouse();
	void applyPreviousSettings();

private:
	QWidget *widget;
	QTimer *timerMouse;
	QTimer *timerSettings;
	bool move;

	int _osdWidth;
	int _osdHeight;
	int _osdPosLeft;
	int _osdPosTop;

	QString _currentRatio;
	QString _currentCrop;
	QString _currentFilter;

	QToolBar *osd;
};

#endif // QVLC_VLCVIDEOWIDGET_H_
