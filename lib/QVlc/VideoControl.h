/****************************************************************************
* QVlc - Qt and libVLC connector library
* VideoControl.h: Video and subtitles controller
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

#ifndef QVLC_VIDEOCONTROL_H_
#define QVLC_VIDEOCONTROL_H_

#include <QtCore/QList>
#include <QtCore/QMap>
#include <QtCore/QTimer>
#include <QtGui/QAction>
#include <QtGui/QActionGroup>

namespace QVlc
{
	class VideoControl : public QObject
	{
	Q_OBJECT
	public:
		VideoControl(const QString &lang = "", QObject *parent = 0);
		~VideoControl();

		void mediaChange();

	private slots:
		void updateActions();
		void update();

	signals:
		void subtitlesActions(const QString, QList<QAction*>);

	private:
		QTimer *_timer;

		QList<QAction*> _actionList;
		QMap<QString,int> _map;
		QActionGroup *_actionGroup;

		bool _manualLanguage;
		QStringList _preferedLanguage;
	};
};

#endif // QVLC_VIDEOCONTROL_H_
