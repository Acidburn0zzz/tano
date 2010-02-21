/****************************************************************************
* Channel.cpp: Channel class
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

#include "Channel.h"

Channel::Channel(const QString &name, const int &number)
	: _name(name), _number(number)
{

}

Channel::~Channel()
{

}

void Channel::setNumber(const int &number)
{
	_number = number;
}
void Channel::setName(const QString &name)
{
	_name = name;
}
void Channel::setEpg(const QString &epg)
{
	_epg = epg;
}
void Channel::setLanguage(const QString &language)
{
	_language = language;
}
void Channel::setUrl(const QString &url)
{
	_url = url;
}
void Channel::setCategories(const QStringList &categories)
{
	_categories = categories;
}
