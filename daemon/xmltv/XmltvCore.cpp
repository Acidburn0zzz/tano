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

#include <QtCore/QDebug>

#include <QtCore/QProcess>
#include <QtCore/QTextCodec>
#include <QtCore/QTextStream>

#include "core/Settings.h"
#include "daemon/xmltv/XmltvCore.h"

XmltvCore::XmltvCore(QObject *parent)
    : QObject(parent)
{
    settings();
}

XmltvCore::~XmltvCore()
{

}

QStringList XmltvCore::grabbers()
{
    QProcess p;
    p.start("tv_find_grabbers");
    p.waitForFinished(-1);

    QStringList list;
    QTextStream in(&p);
    in.setCodec(QTextCodec::codecForName("UTF-8"));
    while (!in.atEnd()) {
        list << in.readLine();
    }

    return list;
}

void XmltvCore::settings()
{
    Settings *settings = new Settings(this);

    delete settings;
}
