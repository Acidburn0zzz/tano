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

#ifndef TANO_XMLTVCHANNELSFILTERMODEL_H_
#define TANO_XMLTVCHANNELSFILTERMODEL_H_

#if defined(Qt5)
    #include <QtCore/QSortFilterProxyModel>
#elif defined(Qt4)
    #include <QtGui/QSortFilterProxyModel>
#endif

class XmltvChannelsFilterModel : public QSortFilterProxyModel
{
Q_OBJECT
public:
    XmltvChannelsFilterModel(QObject *parent = 0);
    ~XmltvChannelsFilterModel();

protected:
    bool filterAcceptsRow(int sourceRow, const QModelIndex &sourceParent) const;
};

#endif // TANO_XMLTVCHANNELSFILTERMODEL_H_
