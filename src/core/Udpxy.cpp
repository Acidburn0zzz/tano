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

#include "core/Settings.h"
#include "core/Udpxy.h"

Udpxy::Udpxy(const bool &generate)
    : _generate()
{
    createSettings();
}

Udpxy::~Udpxy() { }

void Udpxy::createSettings()
{
    Settings *settings = new Settings();
    _enabled = settings->udpxy();
    _url = settings->udpxyUrl();
    _port = QString::number(settings->udpxyPort());
    delete settings;
}

QString Udpxy::processUrl(const QString &url) const
{
    QString u = url;
    if(_enabled || _generate) {
        if(url.contains("udp://@") && !_url.isEmpty()) {
           QString newUrl = "http://%1:%2/udp/%3";
           newUrl = newUrl.arg(_url, _port, u.replace("udp://@", ""));
           return newUrl;
        } else {
            return u;
        }
    } else {
        return u;
    }
}
