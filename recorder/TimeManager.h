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

#ifndef TANO_TIMEMANAGER_H_
#define TANO_TIMEMANAGER_H_

#include <QtCore/QList>
#include <QtCore/QTimer>

class Timer;

class TimeManager : public QObject
{
Q_OBJECT
public:
	TimeManager();
	~TimeManager();

	void addTimer(Timer *t);
	void removeTimer(Timer *t);

signals:
	void startTimer(Timer *);

private slots:
	void check();

private:
	QTimer *_timer;
	QList<Timer *> _timersList;
};

#endif // TANO_TIMEMANAGER_H_
