#pragma once
#include "AbstractScene.h"
#include "enums.h"

class SceneManager
{
private:
	std::unique_ptr<AbstractScene> curScene;

private:
	void ToggleMuteMode() const;

public:
	void LoadResources();
	void SetScene(Scene scene);
	void Update(float dt);
	void Draw();

	void OnKeyDown(BYTE keyCode);
	void OnKeyUp(BYTE keyCode);

private:
	SceneManager() = default;
	SceneManager(const SceneManager&) = delete;

public:
	static SceneManager& Instance();
};

