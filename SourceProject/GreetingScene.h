#pragma once

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

