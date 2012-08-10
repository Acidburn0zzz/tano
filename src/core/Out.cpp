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

#include <QtCore/QTextCodec>

#include "core/Common.h"
#include "Out.h"

Out::Out(const bool &error)
    : QTextStream(error ? stderr : stdout, QIODevice::WriteOnly) { }

Out::~Out() { }

Out& Out::operator<<(const QString &string)
{
    QTextStream::operator<<(string);

    flush();

    return *this;
}

void Out::welcome()
{
    Out() << QString("Tano %1 - An Open IP TV Player").arg(Tano::version()) << endl
          << "Copyright (C) 2012 Tadej Novak" << endl << endl;
}

void Out::help()
{
    Out() << QObject::tr("Usage: %1 [options]").arg(Tano::executable()) << endl << endl;

    Out() << QObject::tr("IP TV playback:") << endl
          << "  " << "-c, --channel <number>" << "\t" << QObject::tr("Play channel by number") << endl
          << "  " << "-p, --playlist <file>" << "\t\t" << QObject::tr("Use playlist file") << endl
          << "  " << "-x, --xmltv <file>" << "\t\t" << QObject::tr("Use XMLTV file") << endl
          << endl;

    Out() << QObject::tr("Open:") << endl
          << "  " << "-f, --file <file>" << "\t\t" << QObject::tr("Open file") << endl
          << "  " << "-u, --url <url>" << "\t\t" << QObject::tr("Open URL") << endl
          << endl;

    Out() << QObject::tr("Playback options:") << endl
          << "  " << "-a, --aout <name>" << "\t\t" << QObject::tr("Set audio output") << endl
          << "  " << "-v, --vout <name>" << "\t\t" << QObject::tr("Set video output") << endl
          << endl;
}

void Out::errorGeneric()
{
    Out() << QObject::tr("Try '%1' for more information.").arg("tano --help") << endl;
}

void Out::errorMissing(const QString &arg)
{
    Out() << QObject::tr("Missing mandatory argument for '%1'.").arg(arg) << endl;
    Out::errorGeneric();
}

void Out::errorUnknown(const QString &arg)
{
    Out() << QObject::tr("Unknown option '%1'.").arg(arg) << endl;
    Out::errorGeneric();
}
