#pragma once
#include "AbstractScene.h"
#include "enums.h"

class SceneManager : ISingleton
{
private:
	std::unique_ptr<AbstractScene> curScene;

public:
	void LoadResources();
	void SetScene(Scene scene);
	void Update(float dt);
	void Draw();

	void OnKeyDown(BYTE keyCode);
	void OnKeyUp(BYTE keyCode);

private:
	SceneManager() : ISingleton(NULL) {}

public:
	static SceneManager& Instance()
	{
		static SceneManager instance;
		return instance;
	}
};

