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

#ifndef TANO_OUT_H_
#define TANO_OUT_H_

#include <QtCore/QTextStream>

class Out : public QTextStream
{
public:
    Out(const bool &error = false);
    ~Out();

    Out& operator<<(const QString &string);

    static void welcome();

    static void help();

    static void errorGeneric();
    static void errorMissing(const QString &arg);
    static void errorUnknown(const QString &arg);
};

#endif // TANO_OUT_H_
