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

#ifndef TANO_SETTINGSUI_H_
#define TANO_SETTINGSUI_H_

#include <QtGui/QWidget>

namespace Ui
{
    class SettingsUi;
}

class SettingsUi : public QWidget
{
Q_OBJECT
public:
    SettingsUi(QWidget *parent = 0);
    ~SettingsUi();

    bool osd() const;
    void setOsd(const bool &enabled);
    bool osdPlaylist() const;
    void setOsdPlaylist(const bool &enabled);
    bool tray() const;
    void setTray(const bool &enabled);
    bool trayHide() const;
    void setTrayHide(const bool &enabled);
    QString wheel() const;
    void setWheel(const QString &wheel);
    int toolbar() const;
    void setToolbar(const int &id);

    bool splash() const;
    void setSplash(const bool &enabled);
    bool lite() const;
    void setLite(const bool &enabled);
    bool top() const;
    void setTop(const bool &enabled);
    bool controls() const;
    void setControls(const bool &enabled);
    bool info() const;
    void setInfo(const bool &enabled);

protected:
    void changeEvent(QEvent *e);

private:
    Ui::SettingsUi *ui;
};

#endif // TANO_SETTINGSUI_H_
