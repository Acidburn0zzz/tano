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

#include "MenuCore.h"

MenuCore::MenuCore(QWidget *parent)
    : QMenu(parent)
{
    _group = new QActionGroup(this);
    _next = new QAction(this);
    connect(_next, SIGNAL(triggered()), this, SLOT(next()));

    addAction(_next);
}

MenuCore::~MenuCore()
{
    foreach (QAction *action, _group->actions())
        delete action;

    delete _group;
    delete _next;
}

void MenuCore::addItem(QAction *action)
{
    action->setCheckable(true);
    _group->addAction(action);
    insertAction(_next, action);
}

void MenuCore::next()
{
    if (_group->actions().isEmpty())
        return;

    if (_group->actions().indexOf(_group->checkedAction()) == _group->actions().size()-1) {
        _group->actions()[0]->trigger();
    } else {
        _group->actions()[_group->actions().indexOf(_group->checkedAction())+1]->trigger();
    }
}

void MenuCore::setActions(const QList<QAction *> &actions,
                          const Vlc::ActionsType &type)
{
    if (type != _type)
        return;

    if (actions.isEmpty() && type != Vlc::Subtitles) {
        setDisabled(true);
    } else {
        setEnabled(true);
        foreach (QAction *action, actions) {
            addItem(action);
        }
    }
}
