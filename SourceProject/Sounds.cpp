#include "pch.h"

bool                                Sounds::isMute            = false;
float                               Sounds::liVolume          = 1.0f ;
float                               Sounds::displayTimeRemain = 0.0f ;
CSoundManager                       Sounds::dsound                   ;
std::unordered_map<SoundId, CSound> Sounds::soundDictionary          ;

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
	assert(soundDictionary.count(id) == 1);
}

bool Sounds::CheckHoldingVolume()
{
	displayTimeRemain = 2.0f; // reset display volume bar time remain to 2 seconds every when pressing +/-

	static float timePressed = 0.0f; // time period has holded +/- 
	timePressed += GameTimer::Dt();

	static constexpr float thresholdHoldingTime = 0.05f;
	if (timePressed < thresholdHoldingTime) return false; // avoid holding +/- lead to volume fluctuating too fast
	else timePressed -= thresholdHoldingTime; return true;
}

void Sounds::VolumeUp()
{
	if (CheckHoldingVolume() == false) return; // avoid holding (+) too fast
	liVolume = min(1.0f, liVolume + 0.01f);

	if (!isMute) {
		for (auto& [_, sound] : soundDictionary)
			sound.GetBuffer(0)->SetVolume( LinearToLogVol(liVolume) );
	}
}

void Sounds::VolumeDown()
{
	if (CheckHoldingVolume() == false) return; // avoid holding (-) too fast
	liVolume = max(0.0f, liVolume - 0.01f);

	if (!isMute) {
		for (auto& [_, sound] : soundDictionary)
			sound.GetBuffer(0)->SetVolume( LinearToLogVol(liVolume) );
	}
}

void Sounds::SetMute(bool ismute)
{
	isMute = ismute;
	if (isMute) 
	{
		for (auto& [_, sound] : soundDictionary)
			sound.GetBuffer(0)->SetVolume(DSBVOLUME_MIN);
	}

	CheckHoldingVolume();
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

void Sounds::HandleInput()
{
	static auto& wnd = Window::Instance();

	if (wnd.IsKeyPressed(VK_OEM_PLUS) || wnd.IsKeyPressed(VK_ADD)) {
		Sounds::VolumeUp();
	}
	else if (wnd.IsKeyPressed(VK_OEM_MINUS) || wnd.IsKeyPressed(VK_SUBTRACT)) {
		Sounds::VolumeDown();
	}
}

void Sounds::Draw()
{
	if (displayTimeRemain <= 0.0f) return;
	displayTimeRemain -= GameTimer::Dt();

	static Font fontDraw(8, "Segoe MDL2 Assets Regular");
	static auto texture = Textures::Get(TextureId::Bbox);	
	static const RectF bgArea       = { 286.0f, 50.0f, 300.0f, 100.0f }; // gray background of displaying volume
	static const RectF volBarArea   = { 290.0f, 52.0f, 296.0f, 92.0f  }; // white background of displaying volume bar
	static const RectF bgNumberArea = { 286.0f, 92.0f, 300.0f, 100.0f }; // area of displaying volume number

	const float yPartition = floor(50.0f + 42 - liVolume * 40.0f);
	const RectF fullPart   = { 290.0f, yPartition, 296.0f, 92.0f };
	const auto colorFullPart = isMute ? Colors::DimRed : Colors::DimBlue;
	const auto colorNumber   = isMute ? Colors::DimRed : Colors::White;

	Game::Instance().DrawSolidRect(bgArea    , Colors::DimGray); // gray background of displaying volume
	Game::Instance().DrawSolidRect(volBarArea, Colors::White  ); // white background of displaying volume bar
	Game::Instance().DrawSolidRect(fullPart  , colorFullPart  ); // display how full volume bar

	fontDraw.DrawStringWithin( std::to_string(int(liVolume * 100)), bgNumberArea, colorNumber ); // area of displaying volume number
}



