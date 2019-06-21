#pragma once
#include "enums.h"

enum class Action { PlayOnce, PlayLoop, StopOnce, StopAll };

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
				  
	void PlayOnce (SoundId id);
	void PlayLoop (SoundId id);
	void StopAt   (SoundId id);
	void StopAll  ();

public:
	void InitDirectSound();
	static void LoadResources(const Json::Value& root);
	static void Invoke(Action action, SoundId id = SoundId::Count); // ::Count indicates invalid SoundId (case SoundId is needless)
	static void SetMuteMode(bool isMute);
	static bool IsMute();
	static bool IsPlayingAt(SoundId id);

private:
	Sounds() : ISingleton(NULL) {}

public:
	static Sounds& Instance()
	{
		static Sounds instance;
		return instance;
	}
};

