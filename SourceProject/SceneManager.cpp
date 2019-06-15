#include "pch.h"
#include "SceneManager.h"
#include "DemoScene.h"
#include "DebugDraw.h"

void SceneManager::SetScene(Scene scene)
{
	switch (scene)
	{
		case Scene::Demo:
			curScene = std::make_unique<DemoScene>();
			break;

		default:
			ThrowMyException("Failed to change to unknown scene");
	}

	curScene->LoadResources();
}

void SceneManager::Update(float dt)
{
	curScene->Update(dt);
}

void SceneManager::Draw()
{
	curScene->Draw();
}

void SceneManager::OnKeyDown(BYTE keyCode)
{
	if (keyCode == VK_CONTROL) 
		DebugDraw::ToggleDebugMode();
	curScene->OnKeyDown(keyCode);
}

void SceneManager::OnKeyUp(BYTE keyCode)
{
	curScene->OnKeyUp(keyCode);
}
