/****************************************************************************
* Tano - An Open IP TV Player
* Copyright (C) 2011 Tadej Novak <tadej@tano.si>
*
* This program is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with this program. If not, see <http://www.gnu.org/licenses/>.
*****************************************************************************/

#ifndef TANO_RECORDERMAIN_H_
#define TANO_RECORDERMAIN_H_

#include <QtCore/QObject>

#include "recorder/RecorderCore.h"
#include "recorder/RecorderTimeManager.h"

class RecorderMain : public QObject
{
Q_OBJECT
public:
	RecorderMain(QObject *parent = 0);
	~RecorderMain();

	bool isRecording() const { return _core->isRecording(); }
	bool isTimer() const { return _core->isTimer(); }
	QString output() const { return _core->output(); }
	void record(const QString &channel,
				const QString &url,
				const QString &path) { _core->record(channel, url, path); }
	void record(Timer *timer) { _core->record(timer); }
	void refreshSettings() { _core->settings(); }
	void refreshTimers() { _time->updateTimers(); }
	void stop() { _core->stop(); }
	QString timerEndTime() const { return _core->timerEndTime(); }
	void timerInfo() { _core->timerInfo(); }

signals:
	void elapsed(const int &);
	void timer(const QString &,
			   const QString &);
	void timerStop();

private:
	RecorderCore *_core;
	RecorderTimeManager *_time;
};

#endif // TANO_RECORDERMAIN_H_
