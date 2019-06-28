#pragma once
#include "enums.h"

class AbstractScene
{
public:
	AbstractScene() noexcept = default;
	AbstractScene(const AbstractScene&) = delete;
	virtual ~AbstractScene() = default;

	static Json::Value GetRootJson(LPCSTR jsonPath);
	virtual SoundId GetBgMusic() const { return SoundId::Count; }// invalid music
	bool HasMusic() const { return GetBgMusic() != SoundId::Count; }

	virtual void LoadResources () = 0;
	virtual void Update(float dt) = 0;
	virtual void Draw  (        ) = 0;

	virtual void OnKeyDown(BYTE keyCode) {}
	virtual void OnKeyUp  (BYTE keyCode) {}
};
