/****************************************************************************
* Settings.cpp: Tano settings manager
*****************************************************************************
* Copyright (C) 2008-2010 Tadej Novak
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
*
* This file may be used under the terms of the
* GNU General Public License version 3.0 as published by the
* Free Software Foundation and appearing in the file LICENSE.GPL
* included in the packaging of this file.
*****************************************************************************/

#include <QtCore/QDir>

#include "Settings.h"
#include "Version.h"

// Playlists
const QString Settings::PLAYLIST_SIOL_MPEG2 = "playlists/siol-mpeg2.m3u";
const QString Settings::PLAYLIST_SIOL_MPEG4 = "playlists/siol-mpeg4.m3u";
const QString Settings::PLAYLIST_T2 = "playlists/t-2.m3u";
const QString Settings::PLAYLIST_TUS = "playlists/tus.m3u";
const QString Settings::PLAYLIST_WORLDTV = "playlists/worldtv.m3u";

// Define defaults - General
const bool Settings::DEFAULT_CONFIGURED = false;
const bool Settings::DEFAULT_UPDATES_CHECK = true;
const bool Settings::DEFAULT_SESSION_VOLUME = true;
const bool Settings::DEFAULT_SESSION_AUTOPLAY = true;
const QString Settings::DEFAULT_LANGUAGE = "";
// Channels
const QString Settings::DEFAULT_PLAYLIST = Settings::PLAYLIST_SIOL_MPEG2;
// GUI - start
const bool Settings::DEFAULT_START_LITE = false;
const bool Settings::DEFAULT_START_ON_TOP = false;
const bool Settings::DEFAULT_START_CONTROLS = true;
const bool Settings::DEFAULT_START_INFO = true;
// GUI
const bool Settings::DEFAULT_OSD = true;
const bool Settings::DEFAULT_HIDE_TO_TRAY = true;
const QString Settings::DEFAULT_MOUSE_WHEEL = "volume";
const int Settings::DEFAULT_TOOLBAR_LOOK = Qt::ToolButtonFollowStyle;
// Backend
const bool Settings::DEFAULT_GLOBAL_SETTINGS = false;
const bool Settings::DEFAULT_REMEMBER_VIDEO_SETTINGS = false;
const QString Settings::DEFAULT_SUBTITLE_LANGUAGE = QObject::tr("Disabled");
// Recorder
const bool Settings::DEFAULT_RECORDER_ENABLED = true;
const QString Settings::DEFAULT_RECORDER_DIRECTORY = QDir::homePath();
const QString Settings::DEFAULT_RECORDER_PLUGIN = "Frip";
// Session
const int Settings::DEFAULT_CHANNEL = 1;
const int Settings::DEFAULT_VOLUME = 50;
// Misc
const QString Settings::DEFAULT_EPG_PLUGIN = "EpgSlovenia";

Settings::Settings(QObject *parent)
	: QSettings(QSettings::IniFormat, QSettings::UserScope, "Tano", "Main", parent)
{
	readSettings();
}

Settings::~Settings()
{

}

QString Settings::path() const
{
	return fileName().replace("Main.ini","");
}

void Settings::writeSettings()
{
	setValue("general/version", configurationVersion());
	setValue("general/configured", configured());
	setValue("general/updatescheck", updatesCheck());
	setValue("general/sessionvolume", sessionVolume());
	setValue("general/sessionplay", sessionAutoplay());
	setValue("general/language", language());

	setValue("session/channel", channel());
	setValue("session/volume", volume());

	setValue("channels/playlist", playlist());

	setValue("start/lite", startLite());
	setValue("start/ontop", startOnTop());
	setValue("start/controls", startControls());
	setValue("start/info", startInfo());

	setValue("gui/osd", osd());
	setValue("gui/hidetotray", hideToTray());
	setValue("gui/mousewheel", mouseWheel());
	setValue("gui/toolbarlook", toolbarLook());

	setValue("backend/global", globalSettings());
	setValue("backend/videosettings", rememberVideoSettings());
	setValue("backend/language", subtitleLanguage());

	setValue("recorder/enabled", recorderEnabled());
	setValue("recorder/directory", recorderDirectory());
	setValue("recorder/plugin", recorderPlugin());

	sync();
}

int Settings::readSettings()
{
	setConfigurationVersion(value("general/version", Version::Tano()).toString());
	setConfigured(value("general/configured", DEFAULT_CONFIGURED).toBool());
	setUpdatesCheck(value("general/updatescheck", DEFAULT_UPDATES_CHECK).toBool());
	setSessionVolume(value("general/sessionvolume", DEFAULT_SESSION_VOLUME).toBool());
	setSessionAutoplay(value("general/sessionplay", DEFAULT_SESSION_AUTOPLAY).toBool());
	setLanguage(value("general/language", DEFAULT_LANGUAGE).toString());

	setPlaylist(value("channels/playlist", DEFAULT_PLAYLIST).toString());

	setStartLite(value("start/lite", DEFAULT_START_LITE).toBool());
	setStartOnTop(value("start/ontop", DEFAULT_START_ON_TOP).toBool());
	setStartControls(value("start/controls", DEFAULT_START_CONTROLS).toBool());
	setStartInfo(value("start/info", DEFAULT_START_INFO).toBool());

	setOsd(value("gui/osd", DEFAULT_OSD).toBool());
	setHideToTray(value("gui/hidetotray", DEFAULT_HIDE_TO_TRAY).toBool());
	setMouseWheel(value("gui/mousewheel", DEFAULT_MOUSE_WHEEL).toString());
	setToolbarLook(value("gui/toolbarlook", DEFAULT_TOOLBAR_LOOK).toInt());

	setGlobalSettings(value("backend/global", DEFAULT_GLOBAL_SETTINGS).toBool());
	setRememberVideoSettings(value("backend/videosettings", DEFAULT_REMEMBER_VIDEO_SETTINGS).toBool());
	setSubtitleLanguage(value("backend/language", DEFAULT_SUBTITLE_LANGUAGE).toString());

	setRecorderEnabled(value("recorder/enabled", DEFAULT_RECORDER_ENABLED).toBool());
	setRecorderDirectory(value("recorder/directory", DEFAULT_RECORDER_DIRECTORY).toString());
	setRecorderPlugin(value("recorder/plugin", DEFAULT_RECORDER_PLUGIN).toString());

	setChannel(value("session/channel", DEFAULT_CHANNEL).toInt());
	setVolume(value("session/volume", DEFAULT_VOLUME).toInt());
}
