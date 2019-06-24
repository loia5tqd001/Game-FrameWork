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

	if (dsound.Create(&waveSound, strWaveFileName) != S_OK)
	{
		ThrowMyException("Create CSound failed!");
	}

	soundDictionary.emplace(id, *waveSound);
}

void Sounds::PlayOnce(SoundId id)
{
	assert(soundDictionary.count(id) == 1);
	if (!isMute) soundDictionary.at(id).Play();
}

void Sounds::PlayLoop(SoundId id)
{
	assert(soundDictionary.count(id) == 1);
	if (!isMute) soundDictionary.at(id).Play(0, DSBPLAY_LOOPING);
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

bool Sounds::IsPlaying(SoundId id)
{
	assert(soundDictionary.count(id) == 1);
	return soundDictionary.at(id).IsSoundPlaying();
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

void Sounds::Invoke(Action action, SoundId id)
{
	switch (action)
	{
		case Action::PlayOnce:
			Instance().PlayOnce(id);
			break;

		case Action::PlayLoop:
			Instance().PlayLoop(id);
			break;

		case Action::StopOnce:
			Instance().StopAt(id);
			break;

		case Action::StopAll:
			assert(id == SoundId::Count);
			Instance().StopAll();
			break;
	}
}

void Sounds::SetMuteMode(bool isMute)
{
	Instance().isMute = isMute;
}

bool Sounds::IsMute()
{
	return Instance().isMute;
}

bool Sounds::IsPlayingAt(SoundId id)
{
	return Instance().IsPlaying(id);
}
