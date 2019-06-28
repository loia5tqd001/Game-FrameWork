#pragma once
#include "enums.h"

class Sounds
{
private:
	static bool isMute;
	static float liVolume; // linear volume/ratio/scale
	static CSoundManager dsound;
	static std::unordered_map<SoundId, CSound> soundDictionary;

private:
	// Learn more at: http://bit.ly/set-volume-the-right-way:
	static int LinearToLogVol(float fLevel);
	static float LogToLinearVol(int iLevel);

	static LPSTR GetWaveFileNameFromSoundId(SoundId id, const Json::Value& root);
	static void  AddSoundToDict            (SoundId id, const Json::Value& root);

public:
	static void LoadResources(const Json::Value& root);

	static void PlayAt     (SoundId id);
	static void PlayLoop   (SoundId id);
	static void StopAt     (SoundId id);
	static void StopAll    (          );
	static bool IsPlayingAt(SoundId id);	

	static void VolumeUp();
	static void VolumeDown();

	inline static void SetMute(bool ismute) { isMute = ismute; }
	inline static bool IsMute (           ) { return   isMute; }

	static void Draw();
};



