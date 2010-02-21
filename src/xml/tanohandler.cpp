/****************************************************************************
* tanohandler.cpp: Old reader and handler of tano playlist format
* This file is also part of the example classes of the Qt Toolkit.
*****************************************************************************
* Copyright (C) 2008-2010 Tadej Novak
*
* Copyright (C) 2008 Nokia Corporation and/or its subsidiary(-ies).
* Contact: Qt Software Information (qt-info@nokia.com)
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

#include <QtCore/QDebug>

#include "tanohandler.h"

TanoHandler::TanoHandler()
	: _num(0), _cat(0), _metTanoTag(false),
	_playlistName(QObject::tr("Channel list")), _category("")
{

}

bool TanoHandler::startElement(const QString & /* namespaceURI */,
							   const QString & /* localName */,
							   const QString &qName,
							   const QXmlAttributes &attributes)
{
	if (!_metTanoTag && qName != "tano") {
		_errorStr = QObject::tr("The file is not a Tano TV channel list file.");
		return false;
	}

	if (qName == "tano") {
		QString version = attributes.value("version");
		if (!version.isEmpty() && !(version == "1.1" || version == "1.2" || version == "1.3")) {
			_errorStr = QObject::tr("The file is not a Tano TV channel list 1.1 or later.");
			return false;
		}
		_metTanoTag = true;
	} else if (qName == "category") {
		if (attributes.value("type") == "main") {
			_cat++;
			_num = channelNumSync(_cat);
		}
		_channel = new Channel("",0);
	} else if (qName == "channel") {
		_num++;
		_channel = new Channel(QObject::tr("Unknown title"), _num);
		_channelList << _channel;
	}

	_currentText.clear();
	return true;
}

bool TanoHandler::endElement(const QString & /* namespaceURI */,
							 const QString & /* localName */,
							 const QString &qName)
{
	if (qName == "title") {
		if (_channel) {
			if(_channel->number() == 0)
				_category = _currentText;
			_channel->setName(_currentText);
			_channel->setCategories(QStringList() << _category);
		}
	} else if (qName == "epg") {
		if (_channel) {
			_channel->setEpg(_currentText);
		}
	} else if (qName == "language") {
		if (_channel) {
			_channel->setLanguage(_currentText);
		}
	} else if (qName == "url") {
		if (_channel) {
			_channel->setUrl(_currentText);
		}
	} else if (qName == "playlist") {
		_playlistName = _currentText;
	}
	return true;
}

bool TanoHandler::characters(const QString &str)
{
	_currentText += str;
	return true;
}

bool TanoHandler::fatalError(const QXmlParseException &exception)
{
	qDebug() << QString("Parse error at line %1, column %2: %3")
							 .arg(exception.lineNumber())
							 .arg(exception.columnNumber())
							 .arg(exception.message());
	return false;
}

int TanoHandler::channelNumSync(const int &c)
{
	if(c>1) {
		int i=c*100;
		while(i<_num)
			i+=100;
		return i-1;
	} else {
		return 0;
	}
}
