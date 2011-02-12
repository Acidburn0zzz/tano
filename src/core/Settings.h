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

#ifndef TANO_SETTINGS_H_
#define TANO_SETTINGS_H_

#include <QtCore/QSettings>

class Settings : public QSettings
{
public:
	Settings(QObject * parent = 0);
	~Settings();

	QString path() const;
	void readSettings();
	void writeSettings();

	// Playlists
	static const QString PLAYLIST_AMIS;
	static const QString PLAYLIST_SIOL_MPEG2;
	static const QString PLAYLIST_SIOL_MPEG4;
	static const QString PLAYLIST_T2;
	static const QString PLAYLIST_TUS;
	static const QString PLAYLIST_WORLDTV;

	// General
	QString configurationVersion() { return _configurationVersion; }
	void setConfigurationVersion(const QString &s) { _configurationVersion = s; }
	bool configured() const { return _configured; }
	void setConfigured(const bool &b) { _configured = b; }
	static const bool DEFAULT_CONFIGURED;
	bool sessionVolume() const { return _sessionVolume; }
	void setSessionVolume(const bool &b) { _sessionVolume = b; }
	static const bool DEFAULT_SESSION_VOLUME;
	bool sessionAutoplay() const { return _sessionAutoplay; }
	void setSessionAutoplay(const bool &b) { _sessionAutoplay = b; }
	static const bool DEFAULT_SESSION_AUTOPLAY;
	QString language() const { return _language; }
	void setLanguage(const QString &s) { _language = s; }
	static const QString DEFAULT_LANGUAGE;

	// Channels
	QString playlist() const { return _playlist; }
	void setPlaylist(const QString &s) { _playlist = s; }
	static const QString DEFAULT_PLAYLIST;

	// GUI - start
	bool splash() const { return _splash; }
	void setSplash(const bool &b) { _splash = b; }
	static const bool DEFAULT_SPLASH;
	bool startLite() const { return _startLite; }
	void setStartLite(const bool &b) { _startLite = b; }
	static const bool DEFAULT_START_LITE;
	bool startOnTop() const { return _startOnTop; }
	void setStartOnTop(const bool &b) { _startOnTop = b; }
	static const bool DEFAULT_START_ON_TOP;
	bool startControls() const { return _startControls; }
	void setStartControls(const bool &b) { _startControls = b; }
	static const bool DEFAULT_START_CONTROLS;
	bool startInfo() const { return _startInfo; }
	void setStartInfo(const bool &b) { _startInfo = b; }
	static const bool DEFAULT_START_INFO;

	// GUI
	bool osd() const { return _osd; }
	void setOsd(const bool &b) { _osd = b; }
	static const bool DEFAULT_OSD;
	bool hideToTray() const { return _hideToTray; }
	void setHideToTray(const bool &b) { _hideToTray = b; }
	static const bool DEFAULT_HIDE_TO_TRAY;
	QString mouseWheel() const { return _mouseWheel; }
	void setMouseWheel(const QString &s) { _mouseWheel = s; }
	static const QString DEFAULT_MOUSE_WHEEL;
	int toolbarLook() const { return _toolbarLook; }
	void setToolbarLook(const int &i) { _toolbarLook = i; }
	static const int DEFAULT_TOOLBAR_LOOK;

	// Backend
	bool globalSettings() const { return _globalSettings; }
	void setGlobalSettings(const bool &b) { _globalSettings = b; }
	static const bool DEFAULT_GLOBAL_SETTINGS;
	bool rememberVideoSettings() const { return _rememberVideoSettings; }
	void setRememberVideoSettings(const bool &b) { _rememberVideoSettings = b; }
	static const bool DEFAULT_REMEMBER_VIDEO_SETTINGS;
	QString audioLanguage() const { return _audioLanguage; }
	void setAudioLanguage(const QString &s) { _audioLanguage = s; }
	static const QString DEFAULT_AUDIO_LANGUAGE;
	QString subtitleLanguage() const { return _subtitleLanguage; }
	void setSubtitleLanguage(const QString &s) { _subtitleLanguage = s; }
	static const QString DEFAULT_SUBTITLE_LANGUAGE;

	// Recorder
	bool recorderEnabled() const { return _recorderEnabled; }
	void setRecorderEnabled(const bool &b) { _recorderEnabled = b; }
	static const bool DEFAULT_RECORDER_ENABLED;
	QString recorderDirectory() const { return _recorderDirectory; }
	void setRecorderDirectory(const QString &s) { _recorderDirectory = s; }
	static const QString DEFAULT_RECORDER_DIRECTORY;
	QString recorderBackend() const { return _recorderBackend; }
	void setRecorderBackend(const QString &s) { _recorderBackend = s; }
	static const QString DEFAULT_RECORDER_BACKEND;

	// Session
	int channel() const { return _channel; }
	void setChannel(const int &i) { _channel = i; }
	static const int DEFAULT_CHANNEL;
	int volume() const { return _volume; }
	void setVolume(const int &i) { _volume = i; }
	static const int DEFAULT_VOLUME;

private:
	// General variables
	QString _configurationVersion;
	bool _configured;
	bool _updatesCheck;
	bool _sessionVolume;
	bool _sessionAutoplay;
	QString _language;

	// Channels
	QString _playlist;

	// GUI - start
	bool _splash;
	bool _startLite;
	bool _startOnTop;
	bool _startControls;
	bool _startInfo;

	// GUI
	bool _osd;
	bool _hideToTray;
	QString _mouseWheel;
	int _toolbarLook;

	// Backend
	bool _globalSettings;
	bool _rememberVideoSettings;
	QString _audioLanguage;
	QString _subtitleLanguage;

	// Recorder
	bool _recorderEnabled;
	QString _recorderDirectory;
	QString _recorderBackend;

	// Session
	int _channel;
	int _volume;
};

#endif // TANO_SETTINGS_H_
