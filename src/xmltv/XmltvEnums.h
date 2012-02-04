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

#ifndef TANO_XMLTVENUMS_H_
#define TANO_XMLTVENUMS_H_

#include <QtCore/QString>

namespace Tano
{
    namespace Xmltv
    {
        // Lenght units
        enum LenghtUnits
        {
            Seconds,
            Minutes,
            Hours
        };

        LenghtUnits lenghtUnits(const QString &type);
        QString lenghtUnits(const LenghtUnits &type);
        QString lenghtUnitsShort(const LenghtUnits &type);

        // Crew member types
        enum CrewMemberType
        {
            All,
            Director,
            Actor,
            Writer,
            Adapter,
            Producer,
            Composer,
            Editor,
            Presenter,
            Commentator,
            Guest
        };

        CrewMemberType crewMemberType(const QString &type);
        QString crewMemberType(const CrewMemberType &type);
    }
}

#endif // TANO_XMLTVENUMS_H_
