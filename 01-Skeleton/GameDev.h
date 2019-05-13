#pragma once
#include "GameInit.h"

class GameDev : public GameInit, public ISingleton
{
private:
	static constexpr char* MARIO_TEXTURE_PATH = "mario.png";
	static constexpr int   ID_TEX_MARIO       = 0          ;

	GameObject *mario;

	void LoadResources () override;
	void Update(float dt) override;
	void ComposeFrame  () override;

private:
	GameDev() : ISingleton(NULL) {}
public:
	static GameDev& Instance()
	{
		static GameDev instance;
		return instance;
	}
};

