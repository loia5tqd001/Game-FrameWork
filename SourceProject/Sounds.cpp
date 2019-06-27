#include "pch.h"
#include "Sounds.h"
#include "Window.h"

LPSTR Sounds::GetWaveFileNameFromSoundId(SoundId id, const Json::Value& root) const
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

void Sounds::AddSound(SoundId id, const Json::Value& root)
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

bool Sounds::IsPlaying(SoundId id)
{
	assert(soundDictionary.count(id) == 1);
	return soundDictionary.at(id).IsSoundPlaying();
}

int Sounds::LinearToLogVol(float fLevel)
{
	if (fLevel <= 0.0f) 
		return DSBVOLUME_MIN;
	else if (fLevel >= 1.0f)
		return DSBVOLUME_MAX;
	return int (-2000 * log10( 1.0f / fLevel ));
}

float Sounds::LogToLinearVol(int iLevel)
{
	if (iLevel <= -9600)
		return 0.0f;
	else if (iLevel >= 0)
		return 1.0f;
	return (float) pow(10, double(iLevel) + 2000 / 2000) / 10.0f;
}

void Sounds::LoadResources(const Json::Value& root)
{
	if (Instance().dsound.Initialize(Window::Instance().GetHWnd(), DSSCL_PRIORITY) != DS_OK)
		ThrowMyException("Init CSoundManager failed");

	if (Instance().dsound.SetPrimaryBufferFormat(2, 22050, 16) != DS_OK)
		ThrowMyException("Set primary buffer format for CSoundManager failed");

	for (UINT i = 0; i < (UINT)SoundId::Count; i++)
		Instance().AddSound( SoundId(i), root );
}

void Sounds::Invoke(Action action, std::any arg)
{
	static auto& soundDict = Instance().soundDictionary;
	static SoundId id;

	if (arg.type() == typeid(SoundId))
	{
		id = std::any_cast<SoundId>( arg );
		assert(soundDict.count( id ) == 1);
	}

	switch (action)
	{
		case Action::PlayOnce:
			if (!IsMute()) soundDict.at(id).Play(0, 0, LinearToLogVol(Instance().liVolume) );
			break;

		case Action::PlayLoop:
			if (!IsMute()) soundDict.at(id).Play(0, DSBPLAY_LOOPING, LinearToLogVol(Instance().liVolume) );
			break;

		case Action::StopAt:
			soundDict.at(id).Stop();
			break;

		case Action::StopAll:
			for (auto& [_, sound] : soundDict) sound.Stop();
			break;

		case Action::SetMuteMode:
			Instance().isMute = std::any_cast<bool>(arg);
			break;

	}
}
