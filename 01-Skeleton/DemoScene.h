#pragma once
#include "AbstractScene.h"
#include "Mario.h"
#include "Map.h"

class DemoScene : public AbstractScene
{
private:
	void LoadResources () override;
	void Update(float dt) override;
	void Draw          () override;

	void LoadObjects();

private:
	std::unique_ptr<Map> map;
	std::unique_ptr<Mario> mario;
	std::vector<std::unique_ptr<GameObject>> goombas;
	std::vector<std::unique_ptr<GameObject>> bricks;

public:
	void OnKeyDown(BYTE keyCode) override { mario->OnKeyDown(keyCode); }
};

