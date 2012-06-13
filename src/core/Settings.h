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

#ifndef TANO_SETTINGS_H_
#define TANO_SETTINGS_H_

#include <QtCore/QSettings>

class Settings : public QSettings
{
public:
    Settings(QObject *parent = 0);
    ~Settings();

    void readSettings();
    void writeSettings();

    // General
    inline QString configurationVersion() { return _configurationVersion; }
    inline void setConfigurationVersion(const QString &s) { _configurationVersion = s; }
    inline bool configured() const { return _configured; }
    inline void setConfigured(const bool &b) { _configured = b; }
    static const bool DEFAULT_CONFIGURED;
    inline bool sessionVolume() const { return _sessionVolume; }
    inline void setSessionVolume(const bool &b) { _sessionVolume = b; }
    static const bool DEFAULT_SESSION_VOLUME;
    inline bool sessionAutoplay() const { return _sessionAutoplay; }
    inline void setSessionAutoplay(const bool &b) { _sessionAutoplay = b; }
    static const bool DEFAULT_SESSION_AUTOPLAY;
    inline QString language() const { return _language; }
    inline void setLanguage(const QString &s) { _language = s; }
    static const QString DEFAULT_LANGUAGE;

    // Playlist
    inline QString playlist() const { return _playlist; }
    inline void setPlaylist(const QString &s) { _playlist = s; }
    static const QString DEFAULT_PLAYLIST;
    inline bool playlistUpdate() const { return _playlistUpdate; }
    inline void setPlaylistUpdate(const bool &b) { _playlistUpdate = b; }
    static const bool DEFAULT_PLAYLIST_UPDATE;
    inline QString playlistUpdateUrl() const { return _playlistUpdateUrl; }
    inline void setPlaylistUpdateUrl(const QString &s) { _playlistUpdateUrl = s; }
    static const QString DEFAULT_PLAYLIST_UPDATE_URL;
    inline QString radioCategory() const { return _radioCategory; }
    inline void setRadioCategory(const QString &s) { _radioCategory = s; }
    static const QString DEFAULT_RADIO_CATEGORY;
    inline bool udpxy() const { return _udpxy; }
    inline void setUdpxy(const bool &b) { _udpxy = b; }
    static const bool DEFAULT_UDPXY;
    inline QString udpxyUrl() const { return _udpxyUrl; }
    inline void setUdpxyUrl(const QString &s) { _udpxyUrl = s; }
    static const QString DEFAULT_UDPXY_URL;
    inline int udpxyPort() const { return _udpxyPort; }
    inline void setUdpxyPort(const int &i) { _udpxyPort = i; }
    static const int DEFAULT_UDPXY_PORT;

    // GUI - start
    inline bool splash() const { return _splash; }
    inline void setSplash(const bool &b) { _splash = b; }
    static const bool DEFAULT_SPLASH;
    inline bool startLite() const { return _startLite; }
    inline void setStartLite(const bool &b) { _startLite = b; }
    static const bool DEFAULT_START_LITE;
    inline bool startOnTop() const { return _startOnTop; }
    inline void setStartOnTop(const bool &b) { _startOnTop = b; }
    static const bool DEFAULT_START_ON_TOP;
    inline bool startControls() const { return _startControls; }
    inline void setStartControls(const bool &b) { _startControls = b; }
    static const bool DEFAULT_START_CONTROLS;
    inline bool startInfo() const { return _startInfo; }
    inline void setStartInfo(const bool &b) { _startInfo = b; }
    static const bool DEFAULT_START_INFO;

    // GUI
    inline bool osd() const { return _osd; }
    inline void setOsd(const bool &b) { _osd = b; }
    static const bool DEFAULT_OSD;
    inline bool info() const { return _info; }
    inline void setInfo(const bool &b) { _info = b; }
    static const bool DEFAULT_INFO;
    inline bool trayEnabled() const { return _trayEnabled; }
    inline void setTrayEnabled(const bool &b) { _trayEnabled = b; }
    static const bool DEFAULT_TRAY_ENABLED;
    inline bool hideToTray() const { return _hideToTray; }
    inline void setHideToTray(const bool &b) { _hideToTray = b; }
    static const bool DEFAULT_HIDE_TO_TRAY;
    inline QString mouseWheel() const { return _mouseWheel; }
    inline void setMouseWheel(const QString &s) { _mouseWheel = s; }
    static const QString DEFAULT_MOUSE_WHEEL;
    inline int toolbarLook() const { return _toolbarLook; }
    inline void setToolbarLook(const int &i) { _toolbarLook = i; }
    static const int DEFAULT_TOOLBAR_LOOK;

    // Backend
    inline bool rememberVideoSettings() const { return _rememberVideoSettings; }
    inline void setRememberVideoSettings(const bool &b) { _rememberVideoSettings = b; }
    static const bool DEFAULT_REMEMBER_VIDEO_SETTINGS;
    inline int aspectRatio() const { return _aspectRatio; }
    inline void setAspectRatio(const int &i) { _aspectRatio = i; }
    static const int DEFAULT_ASPECT_RATIO;
    inline int cropRatio() const { return _cropRatio; }
    inline void setCropRatio(const int &i) { _cropRatio = i; }
    static const int DEFAULT_CROP_RATIO;
    inline int deinterlacing() const { return _deinterlacing; }
    inline void setDeinterlacing(const int &i) { _deinterlacing = i; }
    static const int DEFAULT_DEINTERLACING;
    inline QString audioLanguage() const { return _audioLanguage; }
    inline void setAudioLanguage(const QString &s) { _audioLanguage = s; }
    static const QString DEFAULT_AUDIO_LANGUAGE;
    inline QString subtitleLanguage() const { return _subtitleLanguage; }
    inline void setSubtitleLanguage(const QString &s) { _subtitleLanguage = s; }
    static const QString DEFAULT_SUBTITLE_LANGUAGE;
    inline bool teletext() const { return _teletext; }
    inline void setTeletext(const bool &b) { _teletext = b; }
    static const bool DEFAULT_TELETEXT;

    // Recorder
    inline QString recorderDirectory() const { return _recorderDirectory; }
    inline void setRecorderDirectory(const QString &s) { _recorderDirectory = s; }
    static const QString DEFAULT_RECORDER_DIRECTORY;
    inline QString snapshotsDirectory() const { return _snapshotsDirectory; }
    inline void setSnapshotsDirectory(const QString &s) { _snapshotsDirectory = s; }
    static const QString DEFAULT_SNAPSHOTS_DIRECTORY;

    // Session
    inline int channel() const { return _channel; }
    inline void setChannel(const int &i) { _channel = i; }
    static const int DEFAULT_CHANNEL;
    inline int volume() const { return _volume; }
    inline void setVolume(const int &i) { _volume = i; }
    static const int DEFAULT_VOLUME;

    // Schedule
    inline QString xmltvLocation() const { return _xmltvLocation; }
    inline void setXmltvLocation(const QString &s) { _xmltvLocation = s; }
    static const QString DEFAULT_XMLTV_LOCATION;
    inline bool xmltvUpdate() const { return _xmltvUpdate; }
    inline void setXmltvUpdate(const bool &b) { _xmltvUpdate = b; }
    static const bool DEFAULT_XMLTV_UPDATE;
    inline bool xmltvUpdateGrabber() const { return _xmltvUpdateGrabber; }
    inline void setXmltvUpdateGrabber(const bool &b) { _xmltvUpdateGrabber = b; }
    static const bool DEFAULT_XMLTV_UPDATE_GRABBER;
    inline QString xmltvUpdateUrl() const { return _xmltvUpdateUrl; }
    inline void setXmltvUpdateUrl(const QString &s) { _xmltvUpdateUrl = s; }
    static const QString DEFAULT_XMLTV_UPDATE_URL;
    inline QString xmltvGrabber() const { return _xmltvGrabber; }
    inline void setXmltvGrabber(const QString &s) { _xmltvGrabber = s; }
    static const QString DEFAULT_XMLTV_GRABBER;
    inline QString xmltvGrabberPath() const { return _xmltvGrabberPath; }
    inline void setXmltvGrabberPath(const QString &s) { _xmltvGrabberPath = s; }
    static const QString DEFAULT_XMLTV_GRABBER_PATH;

    // Constants
    static const QString SUPPORT_ADDRESS;

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
    bool _playlistUpdate;
    QString _playlistUpdateUrl;
    QString _radioCategory;
    bool _udpxy;
    QString _udpxyUrl;
    int _udpxyPort;

    // GUI - start
    bool _splash;
    bool _startLite;
    bool _startOnTop;
    bool _startControls;
    bool _startInfo;

    // GUI
    bool _osd;
    bool _info;
    bool _trayEnabled;
    bool _hideToTray;
    QString _mouseWheel;
    int _toolbarLook;

    // Backend
    bool _rememberVideoSettings;
    int _aspectRatio;
    int _cropRatio;
    int _deinterlacing;
    QString _audioLanguage;
    QString _subtitleLanguage;
    bool _teletext;

    // Recorder
    QString _recorderDirectory;
    QString _snapshotsDirectory;

    // Session
    int _channel;
    int _volume;

    // Schedule
    QString _xmltvLocation;
    bool _xmltvUpdate;
    bool _xmltvUpdateGrabber;
    QString _xmltvUpdateUrl;
    QString _xmltvGrabber;
    QString _xmltvGrabberPath;
};

#endif // TANO_SETTINGS_H_
