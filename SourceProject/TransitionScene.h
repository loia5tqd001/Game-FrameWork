#pragma once

class TransitionScene : public AbstractScene
{
private:
	float timePassed = 0.0f;

public:
	void LoadResources() override {}
	void Update(float dt) override;
	void Draw() override;	
};
