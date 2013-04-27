/****************************************************************************
* Tano - An Open IP TV Player
* Copyright (C) 2013 Tadej Novak <tadej@tano.si>
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

#ifndef TANO_TIMERSFILTERMODEL_H_
#define TANO_TIMERSFILTERMODEL_H_

#include <QtCore/QtGlobal>

#if QT_VERSION >= 0x050000
    #include <QtCore/QSortFilterProxyModel>
#else
    #include <QtGui/QSortFilterProxyModel>
#endif

#include "CoreSharedExport.h"

class TimersModel;

/*!
    \class TimersFilterModel TimersFilterModel.h core/timers/models/TimersFilterModel.h
    \brief Timers Filter model

    Reimplemented QSortFilterProxyModel to be able to filter Timers
*/
class TANO_CORE_EXPORT TimersFilterModel : public QSortFilterProxyModel
{
Q_OBJECT
public:
    TimersFilterModel(QObject *parent = 0);
    ~TimersFilterModel();

protected:
    /*!
        \brief Reimplemented filter function
        \param sourceRow row to process (int)
        \param sourceParent parent index (QModelIndex)
        \return true, if item to be displayed (bool)
    */
    bool filterAcceptsRow(int sourceRow,
                          const QModelIndex &sourceParent) const;

public slots:
    /*!
        \brief Set Timers model to filter
        \param model Timers model (TimersModel)
    */
    void setTimersModel(TimersModel *model);

private:
    TimersModel *_model;
};

#endif // TANO_TIMERSFILTERMODEL_H_
