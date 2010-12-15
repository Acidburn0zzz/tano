/****************************************************************************
* Tano - An Open IP TV Player
* Copyright (C) 2008-2010 Tadej Novak <tadej@tano.si>
*
* This program is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with this program.  If not, see <http://www.gnu.org/licenses/>.
*****************************************************************************/

#include "container/Timer.h"

Timer::Timer(const QString &name,
			 const QString &channel,
			 const QString &playlist,
			 const int &num,
			 const QString &url)
	: _name(name),
	_channel(channel),
	_playlist(playlist),
	_num(num),
	_url(url)
{
	_date = QDate::currentDate();
	_startTime = QTime::currentTime().addSecs(300);
	_endTime = QTime::currentTime().addSecs(3900);
	_disabled = false;
}

Timer::~Timer() { }
