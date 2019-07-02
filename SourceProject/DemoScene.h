#pragma once
#include "Mario.h"

class DemoScene : public AbstractScene
{
private:
	std::unique_ptr<Grid>  grid; // holding map objects
	std::unique_ptr<Map>   map; // responsible for drawing map background
	std::unique_ptr<Mario> mario;

public:
	DemoScene();
	void LoadResources () override;
	void Update(float dt) override;
	void Draw          () override;

	void OnKeyDown(BYTE keyCode) override;
	SoundId GetBgMusic() const override { return SoundId::MarioMusic; }
};

