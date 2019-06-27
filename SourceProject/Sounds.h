#pragma once
#include "enums.h"

enum class Action { PlayOnce, PlayLoop, StopAt, StopAll, SetMuteMode };

class Sounds : ISingleton
{
private:
	bool isMute = false;
	CSoundManager dsound;
	std::unordered_map<SoundId, CSound> soundDictionary;

private:
	LPSTR GetWaveFileNameFromSoundId(SoundId id, const Json::Value& root) const;
	void AddSound (SoundId id, const Json::Value& root);
	bool IsPlaying(SoundId id);				  

public:
	static void LoadResources(const Json::Value& root);
	static void Invoke(Action action, std::any arg = NULL); 

	inline static bool IsMute     (          ) { return Instance().isMute       ; }
	inline static bool IsPlayingAt(SoundId id) { return Instance().IsPlaying(id); }

private:
	Sounds() : ISingleton(NULL) {}
	static Sounds& Instance()
	{
		static Sounds instance;
		return instance;
	}
};

// SetVolume module: I gave up on calculating amplitude percentage. Some resources:
// https://www.gamedev.net/forums/topic/358422-converting-decibel-to-percent/
// https://stackoverflow.com/questions/6571894/calculate-decibel-from-amplitude-android-media-recorder

