#pragma once
#include "GameBase.h"
#include "ISingleton.h"
#include "Mario.h"
#include "Map.h"

class GameDev : public GameBase, ISingleton
{
private:
	void LoadResources () override;
	void Update(float dt) override;
	void ComposeFrame  () override;

	void LoadObjects();
private:
	std::unique_ptr<Map> map;
	std::unique_ptr<Mario> mario;
	std::vector<std::unique_ptr<GameObject>> goombas;
	std::vector<std::unique_ptr<GameObject>> bricks;
	std::vector<std::unique_ptr<GameObject>> objects;

public:
	void OnKeyDown(BYTE keyCode) override { mario->OnKeyDown(keyCode); }

private:
	GameDev() : ISingleton(NULL) {}

public:
	static GameDev& Instance()
	{
		static GameDev instance;
		return instance;
	}
};

