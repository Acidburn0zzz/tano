/****************************************************************************
* Tano - An Open IP TV Player
* Copyright (C) 2012 Tadej Novak <tadej@tano.si>
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

#include <QtCore/QFile>
#include <QtCore/QTextStream>

#include "Config.h"

#include "Common.h"

QString Tano::name()
{
#if BRANDING && defined(BRAND_NAME)
    return QString(BRAND_NAME);
#else
    return "Tano";
#endif
}

QString Tano::executable()
{
#if BRANDING && defined(BRAND_NAME)
    return QString(BRAND_NAME).toLower();
#else
    return "tano";
#endif
}

QString Tano::version()
{
    QString version;

#ifdef VERSION
    version.append(QString(VERSION));
#else
    version.append("Unknown");
#endif

    return version;
}

QString Tano::email()
{
#ifdef APP_URL
    return QString(APP_EMAIL);
#else
    return "info@tano.si";
#endif
}

QString Tano::url()
{
#ifdef APP_URL
    return QString(APP_URL);
#else
    return "http://projects.tano.si";
#endif
}

QString Tano::changeset()
{
    QString version;

#ifdef VERSION_PATCH
    if(QString(VERSION_PATCH) != "0" && QString(VERSION_PATCH) != "") {
        version.append("(" + QString(VERSION_PATCH) + ")");
    }
#endif

    return version;
}

bool Tano::is64bit()
{
    bool bit = false;

#if VERSION_X64
    bit = true;
#endif

    return bit;
}

QString Tano::uid()
{
#if defined(Q_OS_LINUX)
    QFile file("/var/lib/dbus/machine-id");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return QString("error");

    QTextStream in(&file);
    QString uid = in.readLine();
    return uid;
#endif
}

QString Tano::recordingFileName(const QString &name,
                                const QString &channel,
                                const QDate &date,
                                const QTime &time)
{
    QString f;
    f.append(QString(name).replace(" ", "_"));
    f.append("-");
    f.append(QString(channel).replace(" ", "_"));
    f.append("-");
    f.append(date.toString("yyyyMMdd"));
    f.append("-");
    f.append(time.toString("hhmmss"));

    return f;
}
