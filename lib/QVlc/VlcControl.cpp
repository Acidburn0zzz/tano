#include "VlcControl.h"
#include "VlcInstance.h"

VlcControl::VlcControl(const QString lang)
{
	audioGroup = 0;
	subGroup = 0;

	manualLanguage = false;
	preferedLanguage = lang.split(" / ");

	timer = new QTimer(this);
	connect(timer, SIGNAL(timeout()), this, SLOT(updateActionsAudio()));
	connect(timer, SIGNAL(timeout()), this, SLOT(updateActionsVideo()));

	check = new QTimer(this);
	connect(check, SIGNAL(timeout()), this, SLOT(checkPlayingState()));

	check->start(300);
	timer->start(2000);
}

VlcControl::~VlcControl()
{
	delete timer;
	delete check;
}

void VlcControl::updateActionsAudio() {
	for(int i=0; i<audioList.size(); i++)
		delete audioList[i];
	audioList.clear();
	audioMap.clear();

	if(audioGroup != 0)
		delete audioGroup;
	audioGroup = new QActionGroup(this);

	if(!_vlcCurrentMediaPlayer)
		return;

	libvlc_state_t state;
	#if VLC_TRUNK
		state = libvlc_media_player_get_state(_vlcCurrentMediaPlayer);
	#else
		state = libvlc_media_player_get_state(_vlcCurrentMediaPlayer, _vlcException);
	#endif

	if(state == 0 || state == 6 || state == 7) {
		emit vlcAction("audio", audioList);
		return;
	}

#if VLC_TRUNK
	if(libvlc_audio_get_track_count(_vlcCurrentMediaPlayer) != 0) {
#else
	if(libvlc_audio_get_track_count(_vlcCurrentMediaPlayer, _vlcException) != 0) {
#endif
		libvlc_track_description_t *desc;
#if VLC_TRUNK
		desc = libvlc_audio_get_track_description(_vlcCurrentMediaPlayer);
#else
		desc = libvlc_audio_get_track_description(_vlcCurrentMediaPlayer, _vlcException);
#endif
		audioMap.insert(QString().fromUtf8(desc->psz_name), 0);
		audioList << new QAction(QString().fromUtf8(desc->psz_name), this);
#if VLC_TRUNK
		if(libvlc_audio_get_track_count(_vlcCurrentMediaPlayer) > 1) {
			for(int i = 1; i < libvlc_audio_get_track_count(_vlcCurrentMediaPlayer); i++) {
				desc = desc->p_next;
				audioMap.insert(QString().fromUtf8(desc->psz_name), i);
				audioList << new QAction(QString().fromUtf8(desc->psz_name), this);
			}
		}
#else
		if(libvlc_audio_get_track_count(_vlcCurrentMediaPlayer, _vlcException) > 1) {
			for(int i = 1; i < libvlc_audio_get_track_count(_vlcCurrentMediaPlayer, _vlcException); i++) {
				desc = desc->p_next;
				audioMap.insert(QString().fromUtf8(desc->psz_name), i);
				audioList << new QAction(QString().fromUtf8(desc->psz_name), this);
			}
		}
#endif
	} else {
		emit vlcAction("audio", audioList);
		return;
	}

	VlcInstance::checkError();

	for (int i = 0; i < audioList.size(); ++i) {
		audioList[i]->setCheckable(true);
		audioGroup->addAction(audioList[i]);
		connect(audioList[i], SIGNAL(triggered()), this, SLOT(updateAudio()));
	}

#if VLC_TRUNK
	audioList[libvlc_audio_get_track(_vlcCurrentMediaPlayer)]->setChecked(true);
#else
	audioList[libvlc_audio_get_track(_vlcCurrentMediaPlayer, _vlcException)]->setChecked(true);
#endif
	VlcInstance::checkError();

	emit vlcAction("audio", audioList);
}

void VlcControl::updateActionsVideo() {
	for(int i=0; i<subList.size(); i++)
		delete subList[i];
	subList.clear();
	subMap.clear();

	if(subGroup != 0)
		delete subGroup;
	subGroup = new QActionGroup(this);

	if(!_vlcCurrentMediaPlayer)
		return;

	libvlc_state_t state;
	#if VLC_TRUNK
		state = libvlc_media_player_get_state(_vlcCurrentMediaPlayer);
	#else
		state = libvlc_media_player_get_state(_vlcCurrentMediaPlayer, _vlcException);
	#endif

	if(state == 0 || state == 6 || state == 7) {
		emit vlcAction("sub", subList);
		return;
	}

#if VLC_TRUNK
	if(libvlc_video_get_spu_count(_vlcCurrentMediaPlayer) != 0) {
#else
	if(libvlc_video_get_spu_count(_vlcCurrentMediaPlayer, _vlcException) != 0) {
#endif
		libvlc_track_description_t *desc;
#if VLC_TRUNK
		desc = libvlc_video_get_spu_description(_vlcCurrentMediaPlayer);
#else
		desc = libvlc_video_get_spu_description(_vlcCurrentMediaPlayer, _vlcException);
#endif
		subMap.insert(QString().fromUtf8(desc->psz_name), 0);
		subList << new QAction(QString().fromUtf8(desc->psz_name), this);
#if VLC_TRUNK
		if(libvlc_video_get_spu_count(_vlcCurrentMediaPlayer) > 1) {
			for(int i = 1; i < libvlc_video_get_spu_count(_vlcCurrentMediaPlayer); i++) {
				desc = desc->p_next;
				subMap.insert(QString().fromUtf8(desc->psz_name), i);
				subList << new QAction(QString().fromUtf8(desc->psz_name), this);
			}
		}
#else
		if(libvlc_video_get_spu_count(_vlcCurrentMediaPlayer, _vlcException) > 1) {
			for(int i = 1; i < libvlc_video_get_spu_count(_vlcCurrentMediaPlayer, _vlcException); i++) {
				desc = desc->p_next;
				subMap.insert(QString().fromUtf8(desc->psz_name), i);
				subList << new QAction(QString().fromUtf8(desc->psz_name), this);
			}
		}
#endif
	} else {
		emit vlcAction("sub", subList);
		return;
	}

	VlcInstance::checkError();

	for (int i = 0; i < subList.size(); ++i) {
		subList[i]->setCheckable(true);
		subGroup->addAction(subList[i]);
		connect(subList[i], SIGNAL(triggered()), this, SLOT(updateSub()));

		if(!manualLanguage)
			for(int j = 0; j < preferedLanguage.size(); ++j)
				if(subList[i]->text().contains(preferedLanguage[j],Qt::CaseInsensitive)) {
					subList[i]->trigger();
					manualLanguage = true;
				}
	}
#if VLC_TRUNK
	subList[libvlc_video_get_spu(_vlcCurrentMediaPlayer)]->setChecked(true);
#else
	subList[libvlc_video_get_spu(_vlcCurrentMediaPlayer, _vlcException)]->setChecked(true);
#endif
	VlcInstance::checkError();

	emit vlcAction("sub", subList);
}

void VlcControl::updateAudio()
{
	int id = audioMap.value(audioGroup->checkedAction()->text());

#if VLC_TRUNK
	libvlc_audio_set_track(_vlcCurrentMediaPlayer, id);
#else
	libvlc_audio_set_track(_vlcCurrentMediaPlayer, id ,_vlcException);
#endif

	VlcInstance::checkError();
}

void VlcControl::updateSub()
{
	int id = subMap.value(subGroup->checkedAction()->text());

#if VLC_TRUNK
	libvlc_video_set_spu(_vlcCurrentMediaPlayer, id);
#else
	libvlc_video_set_spu(_vlcCurrentMediaPlayer, id ,_vlcException);
#endif

	VlcInstance::checkError();
}

void VlcControl::checkPlayingState()
{
	if(!_vlcCurrentMediaPlayer)
		return;

	libvlc_state_t state;
#if VLC_TRUNK
	state = libvlc_media_player_get_state(_vlcCurrentMediaPlayer);
#else
	state = libvlc_media_player_get_state(_vlcCurrentMediaPlayer, _vlcException);
#endif

	if(state == 3) {
		emit stateChanged(1);
	} else {
		emit stateChanged(0);
	}
}

void VlcControl::update()
{
	manualLanguage = false;
}
