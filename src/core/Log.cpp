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

#include <QtCore/QDateTime>
#include <QtCore/QDebug>
#include <QtCore/QFile>
#include <QtCore/QTextCodec>
#include <QtCore/QTextStream>

#include "core/Common.h"
#include "core/Log.h"
#include "core/Resources.h"
#include "core/Unicode.h"

QTextStream *out;

void Tano::Log::output(QtMsgType type, const char *msg)
{
    QString debugdate = QDateTime::currentDateTime().toString("yyyy.MM.dd hh:mm:ss");
    QTextCodec *codec = QTextCodec::codecForName("UTF-8");
    QString msgstr = codec->toUnicode(codec->toUnicode(msg).toAscii());
    switch (type)
    {
    case QtDebugMsg:
        debugdate += " [D]";
        break;
    case QtWarningMsg:
        debugdate += " [W]";
        break;
    case QtCriticalMsg:
        debugdate += " [C]";
        break;
    case QtFatalMsg:
        debugdate += " [F]";
    }
    (*out) << debugdate << " " << msgstr << endl;

#ifdef QT_DEBUG
    utf8_fprintf(stderr, "%s %s\n", debugdate.toUtf8().constData(), msgstr.toUtf8().constData());
#endif

    if (QtFatalMsg == type) {
        abort();
    }
}

void Tano::Log::setup()
{
    QString fileName = Tano::Resources::settingsPath() + "/" + Tano::executable() + ".log";
    QFile *log = new QFile(fileName);
    if (log->open(QIODevice::WriteOnly | QIODevice::Append | QIODevice::Text)) {
        out = new QTextStream(log);
        qInstallMsgHandler(output);
    } else {
        qDebug() << "Error opening log file '" << fileName << "'. All debug output redirected to console.";
    }
}
