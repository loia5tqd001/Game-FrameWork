#include "pch.h"
#include "Sounds.h"
#include "Window.h"

bool                                Sounds::isMute           = false;
float                               Sounds::liVolume         = 1.0f ;
CSoundManager                       Sounds::dsound                  ;
std::unordered_map<SoundId, CSound> Sounds::soundDictionary         ;

int Sounds::LinearToLogVol(float fLevel)
{
	if (fLevel <= 0.0f) return DSBVOLUME_MIN;
	if (fLevel >= 1.0f) return DSBVOLUME_MAX;
	return int (-2000 * log10( 1.0f / fLevel ));
}

float Sounds::LogToLinearVol(int iLevel)
{
	if (iLevel <= -9600) return 0.0f;
	if (iLevel >= 0)     return 1.0f;
	return (float) pow(10, double(iLevel) + 2000 / 2000) / 10.0f;
}

LPSTR Sounds::GetWaveFileNameFromSoundId(SoundId id, const Json::Value& root)
{
	static auto matchSoundIdPred = [&](const Json::Value& sound) { return sound[0].asUInt() == (UINT)id; };

	const auto& soundsJson = root["sounds"];
	const auto& found = std::find_if(soundsJson.begin(), soundsJson.end(), matchSoundIdPred);

	if (found == soundsJson.end())
	{
		ThrowMyException("Can't find any wave file name match with id of:", (UINT)id);
	}

	const auto& strWaveFileName = (*found)[1].asCString();
	return const_cast<LPSTR>(strWaveFileName);
}

void Sounds::AddSoundToDict(SoundId id, const Json::Value& root)
{
	assert(soundDictionary.count(id) == 0);

	LPSTR strWaveFileName = GetWaveFileNameFromSoundId(id, root);
	CSound* waveSound;

	if (dsound.Create(&waveSound, strWaveFileName, DSBCAPS_CTRLVOLUME | DSBCAPS_GLOBALFOCUS) != S_OK)
	{
		ThrowMyException("Create CSound failed!");
	}

	soundDictionary.emplace(id, *waveSound);
}

void Sounds::VolumeUp()
{
	liVolume = min(1.0f, liVolume + 0.01f);
	for (auto& [_, sound] : soundDictionary)
		sound.GetBuffer(0)->SetVolume( LinearToLogVol(liVolume) );
}

void Sounds::VolumeDown()
{
	liVolume = max(0.0f, liVolume - 0.01f);
	for (auto& [_, sound] : soundDictionary)
		sound.GetBuffer(0)->SetVolume( LinearToLogVol(liVolume) );
}

void Sounds::Draw()
{
}

bool Sounds::IsPlayingAt(SoundId id)
{
	assert(soundDictionary.count(id) == 1);
	return soundDictionary.at(id).IsSoundPlaying();
}

void Sounds::LoadResources(const Json::Value& root)
{
	if (dsound.Initialize(Window::Instance().GetHWnd(), DSSCL_PRIORITY) != DS_OK)
		ThrowMyException("Init CSoundManager failed");

	if (dsound.SetPrimaryBufferFormat(2, 22050, 16) != DS_OK)
		ThrowMyException("Set primary buffer format for CSoundManager failed");

	for (UINT i = 0; i < (UINT)SoundId::Count; i++)
		AddSoundToDict( SoundId(i), root );
}

void Sounds::PlayAt(SoundId id)
{
	assert(soundDictionary.count(id) == 1);
	if (!isMute) soundDictionary.at(id).Play(0, 0, LinearToLogVol( liVolume ));
}

void Sounds::PlayLoop(SoundId id)
{
	assert(soundDictionary.count(id) == 1);
	if (!isMute) soundDictionary.at(id).Play(0, DSBPLAY_LOOPING, LinearToLogVol( liVolume ));
}

void Sounds::StopAt(SoundId id)
{
	assert(soundDictionary.count(id) == 1);
	soundDictionary.at(id).Stop();
}

void Sounds::StopAll()
{
	for (auto& [_, sound] : soundDictionary)
		sound.Stop();
}




