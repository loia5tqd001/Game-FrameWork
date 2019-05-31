#pragma once
#include "enums.h"
#include "Map.h"

class Scene
{
private:
	std::unique_ptr<Map> map;
	std::vector<std::shared_ptr<GameObject>> objects;
	std::unique_ptr<Mario> mario;

public:
	Scene(LPCSTR jsonPath);
	void LoadResources();
	void ChangeScene();
	void Update(float dt);
	void ComposeFrame();
	void OnKeyDown(BYTE keyCode);
	void OnKeyUp  (BYTE keyCode);
};

