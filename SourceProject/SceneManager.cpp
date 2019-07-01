#include "pch.h"
#include "SceneManager.h"
#include "Sounds.h"
#include "Sprites.h"
#include "Texts.h"
#include "GreetingScene.h"
#include "TransitionScene.h"
#include "DemoScene.h"

void SceneManager::ToggleMuteMode() const
{
	Sounds::SetMute( !Sounds::IsMute() );

	if (!Sounds::IsMute() && curScene->HasMusic())
		Sounds::PlayLoop(curScene->GetBgMusic());
}

void SceneManager::LoadResources()
{
	const auto root = AbstractScene::GetRootJson("Resources\\Data\\resources.json");

	Textures::LoadResources(root);
	Sprites::LoadResources(root);
	Sounds::LoadResources(root);
	Texts::LoadResources(root);
	Font::AddCustomFonts();
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
	Sounds::HandleInput();
}

void SceneManager::Draw()
{
	curScene->Draw();
	Sounds::Draw();
}

void SceneManager::OnKeyDown(BYTE keyCode)
{
	switch (keyCode)
	{
		case VK_CONTROL:
			DebugDraw::ToggleDebugMode();
			break;

		case 'M':
			ToggleMuteMode();
			break;			
	}	

	curScene->OnKeyDown(keyCode);
}

void SceneManager::OnKeyUp(BYTE keyCode)
{
	curScene->OnKeyUp(keyCode);
}

SceneManager& SceneManager::Instance()
{
	static SceneManager instance;
	return instance;
}
