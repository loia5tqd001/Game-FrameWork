#pragma once
#include "AbstractScene.h"
#include "Mario.h"
#include "Map.h"
#include "Grid.h"

class DemoScene : public AbstractScene
{
private:
	std::unique_ptr<Grid>  grid; // holding map objects
	std::unique_ptr<Map>   map; // responsible for drawing map background
	std::unique_ptr<Mario> mario;

	std::vector<LPCGAMEOBJECT> objectsInViewPort; // being calculated every frame by grid

public:
	void LoadResources () override;
	void Update(float dt) override;
	void Draw          () override;

	void OnKeyDown(BYTE keyCode) override { mario->OnKeyDown(keyCode); }
};

