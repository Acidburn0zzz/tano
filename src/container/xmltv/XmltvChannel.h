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

#ifndef TANO_XMLTVCHANNEL_H_
#define TANO_XMLTVCHANNEL_H_

#include <QtCore/QString>

class XmltvChannel
{
public:
	XmltvChannel(const QString &id);
	~XmltvChannel();

	QString id() const { return _id; }
	QString displayName() const { return _displayName; }
	void setDisplayName(const QString &s) { _displayName = s; }
	QString icon() const { return _icon; }
	void setIcon(const QString &s) { _icon = s; }
	QString url() const { return _url; }
	void setUrl(const QString &s) { _url = s; }

private:
	QString _id;
	QString _displayName;
	QString _icon;
	QString _url;
};

#endif // TANO_XMLTVCHANNEL_H_
