#include "pch.h"
#include "SceneManager.h"

#include "Sounds.h"
#include "Sprites.h"
#include "Texts.h"

#include "GreetingScene.h"
#include "TransitionScene.h"
#include "DemoScene.h"

void SceneManager::LoadResources()
{
	const auto root = AbstractScene::GetRootJson("Resources\\Data\\resources.json");

	Textures::LoadResources(root);
	Sprites::LoadResources(root);
	Sounds::LoadResources(root);
	Texts::LoadResources(root);
}

void SceneManager::SetScene(Scene scene)
{
	switch (scene)
	{
		case Scene::Greeting:
			curScene = std::make_unique<GreetingScene>();
			break;

		case Scene::Transition:
			curScene = std::make_unique<TransitionScene>();
			break;

		case Scene::Demo:
			curScene = std::make_unique<DemoScene>();
			break;

		default:
			ThrowMyException("Failed to change to unknown scene");
	}
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
	switch (keyCode)
	{
		case VK_CONTROL:
			DebugDraw::ToggleDebugMode();
			break;

		case VK_OEM_PLUS:
			Sounds::Instance().VolumeUp();

			break;
		case VK_OEM_MINUS:
			Sounds::Instance().VolumeDown();
			break;
	}	

	curScene->OnKeyDown(keyCode);
}

void SceneManager::OnKeyUp(BYTE keyCode)
{
	curScene->OnKeyUp(keyCode);
}
