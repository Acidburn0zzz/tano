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

#ifndef TANO_PLAYLISTWIDGET_H_
#define TANO_PLAYLISTWIDGET_H_

#include <QtCore/QModelIndex>
#include <QtGui/QWidget>

#include "ui/core/FileDialogs.h"

class Channel;
class PlaylistFilterModel;
class PlaylistModel;

namespace Ui
{
    class PlaylistDisplayWidget;
}

class PlaylistDisplayWidget : public QWidget
{
Q_OBJECT
public:
    PlaylistDisplayWidget(QWidget *parent = 0);
    ~PlaylistDisplayWidget();

    Channel *currentChannel() { return _current; }
    void setCurrentChannel(Channel *channel);

    void editMode();
    void refreshModel();
    void setModel(PlaylistModel *model);

protected:
    void changeEvent(QEvent *e);

signals:
    void itemClicked(Channel *);

private slots:
    void channelClicked(const QModelIndex &index);
    void processFilters();

private:
    Ui::PlaylistDisplayWidget *ui;

    Channel *_current;
    PlaylistModel *_model;
    PlaylistFilterModel *_filterModel;
    QString _fileName;
};

#endif // TANO_PLAYLISTWIDGET_H_