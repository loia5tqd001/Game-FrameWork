#pragma once
#include "GameBase.h"
#include "ISingleton.h"
#include "Mario.h"

class GameDev : public GameBase, ISingleton
{
private:
	void LoadResources () override;
	void Update(float dt) override;
	void ComposeFrame  () override;

	//Mario mario;

private:
	GameDev() : GameBase(), ISingleton(NULL) {}

public:
	static GameDev& Instance()
	{
		static GameDev instance;
		return instance;
	}
};

