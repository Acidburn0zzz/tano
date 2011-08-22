/****************************************************************************
* Slovenian EPG - Tano EPG Plugin
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

#ifndef TANOPLUGIN_SLOVENIACREATOR_H_
#define TANOPLUGIN_SLOVENIACREATOR_H_

#include <QtCore/QObject>
#include <QtCore/QtPlugin>

#include "EpgPlugin.h"

class SloveniaCreator : public QObject, public EpgPluginCreator
{
Q_OBJECT
Q_INTERFACES(EpgPluginCreator)
Q_CLASSINFO("PLUGINTYPE", "Epg")
Q_CLASSINFO("PLUGINNAME", "Slovenia")

public:
    EpgPlugin *createInstance();
};

#endif // TANOPLUGIN_SLOVENIACREATOR_H_
