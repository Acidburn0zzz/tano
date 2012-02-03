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

#ifndef TANO_PLAYLISTFILTERMODEL_H_
#define TANO_PLAYLISTFILTERMODEL_H_

#include <QtGui/QSortFilterProxyModel>

#include "core/Enums.h"

class PlaylistFilterModel : public QSortFilterProxyModel
{
Q_OBJECT
public:
    PlaylistFilterModel(QObject *parent = 0);
    ~PlaylistFilterModel();

    QString category() const { return _category; }
    void setCategory(const QString &category);

    QString language() const { return _language; }
    void setLanguage(const QString &language);

    Tano::ChannelType type() const { return _type; }
    void setType(const Tano::ChannelType &type);

protected:
    bool filterAcceptsRow(int sourceRow, const QModelIndex &sourceParent) const;

private:
    QString _category;
    QString _language;
    Tano::ChannelType _type;
};

#endif // TANO_PLAYLISTFILTERMODEL_H_
