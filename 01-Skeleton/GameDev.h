#pragma once
#include "GameBase.h"
#include "ISingleton.h"
#include "Mario.h"
#include <memory>

class GameDev : public GameBase, ISingleton
{
private:
	void LoadResources () override;
	void InitObjects   () override;
	void Update(float dt) override;
	void ComposeFrame  () override;

private:
	std::unique_ptr<Mario> mario;

private:
	GameDev() : ISingleton(NULL) {}

public:
	static GameDev& Instance()
	{
		static GameDev instance;
		return instance;
	}
};

