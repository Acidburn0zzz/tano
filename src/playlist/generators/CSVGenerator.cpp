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

#include "container/core/Channel.h"
#include "playlist/PlaylistModel.h"
#include "CSVGenerator.h"

CSVGenerator::CSVGenerator(const QString &file)
{
    _file = new QFile(file);
}

CSVGenerator::~CSVGenerator()
{
    delete _file;
}

bool CSVGenerator::write(PlaylistModel *model)
{
    if (!_file->open(QFile::WriteOnly | QFile::Text))
        return false;

    _out.setDevice(_file);
    _out.setCodec("UTF-8");
    _out << QObject::tr("Number") << ";"
         << QObject::tr("Channel") << ";"
         << QObject::tr("URL") << ";"
         << QObject::tr("Categories") << ";"
         << QObject::tr("Language") << ";"
         << QObject::tr("EPG ID") << "\n";

    for (int i = 0; i < model->rowCount(); i++) {
        generateItem(model->row(i));
    }
    return true;
}

void CSVGenerator::generateItem(Channel *channel)
{
    _out << channel->numberString() << ";"
         << channel->name() << ";"
         << channel->url() << ";"
         << channel->categories().join(",") << ";"
         << channel->language() << ";"
         << channel->epg();
    _out << "\n";
}
