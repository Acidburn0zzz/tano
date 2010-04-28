/****************************************************************************
* QVlc - Qt and libVLC connector library
* VolumeSlider.h: Volume manager and slider
*****************************************************************************
* Copyright (C) 2008-2010 Tadej Novak
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
*
* This file may be used under the terms of the
* GNU General Public License version 3.0 as published by the
* Free Software Foundation and appearing in the file LICENSE.GPL
* included in the packaging of this file.
*****************************************************************************/

#ifndef QVLC_VOLUMESLIDER_H_
#define QVLC_VOLUMESLIDER_H_

#include <QtCore/QTimer>
#include <QtGui/QLabel>
#include <QtGui/QSlider>
#include <QtGui/QWidget>

namespace QVlc
{
	/*! \class VolumeSlider VolumeSlider.h QVlc/VolumeSlider.h
		\brief Volume slider widget

		This is one of QVlc GUI classes.
		It provides main volume control and also visual display of current volume.
	*/
	class VolumeSlider : public QWidget
	{
	Q_OBJECT
	public:
		/*!
			VolumeSlider constructor
			\param parent volume slider's parent GUI widget
		*/
		VolumeSlider(QWidget *parent = 0);

		/*!
			VolumeSlider destructor
		*/
		~VolumeSlider();


		/*!
			Returns current volume of active instance
			\return current volume
		*/
		int volume() const {return _currentVolume;};

	public slots:
		/*!
			Set volume for current instance
			\param volume number from 0 to 200
		*/
		void setVolume(const int &volume);

		/*!
			Toggle mute
		*/
		void mute();

		/*!
			Increases volume for 1. This function is provided for convenience.
			\sa volumeControl()
		*/
		void volumeUp() {volumeControl(true);};

		/*!
			Decreases volume for 1. This function is provided for convenience.
			\sa volumeControl()
		*/
		void volumeDown() {volumeControl(false);};

		/*!
			Decreases or increases volume for 1, depending on the parameter.
			Limits from 0 to 200 apply to this function.
			\param up if true increases the volume
		*/
		void volumeControl(const bool &up);


	private slots:
		void updateVolume();

	private:
		int _currentVolume;

		QSlider *_slider;
		QLabel *_label;
		QTimer *_timer;
	};
};

#endif // QVLC_VOLUMESLIDER_H_
