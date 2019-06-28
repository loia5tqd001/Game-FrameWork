#pragma once
#include "AbstractScene.h"
#include "Sprite.h"

class GreetingScene : public AbstractScene
{
private:
	std::unique_ptr<Sprite> rememberNote;

public:
	GreetingScene();
	void LoadResources() override;
	void Update(float dt) override;
	void Draw() override;	
	void OnKeyDown(BYTE keyCode) override;
};

