#include "pch.h"
#include "GreetingScene.h"
#include "TransitionScene.h"
#include "DemoScene.h"

void SceneManager::ToggleMuteMode() const
{
	Sounds::SetMute( !Sounds::IsMute() );

	if (!Sounds::IsMute() && !curScene->IsPause() && curScene->HasMusic())
		Sounds::PlayLoop(curScene->GetBgMusic());
}

void SceneManager::ToggleSettingScene() const
{
	curScene->TogglePause();
	settingScene.SetOpening( curScene->IsPause() );

	if (curScene->HasMusic()) // handle music for current main scene
	{
		if (!curScene->IsPause())
			Sounds::PlayLoop(curScene->GetBgMusic());
		else 
			Sounds::StopAt(curScene->GetBgMusic());
	}
}

void SceneManager::LoadResources()
{
	const auto root = AbstractScene::GetRootJson("Resources\\Data\\resources.json");

	Textures     ::LoadResources(root);
	Sprites      ::LoadResources(root);
	Sounds       ::LoadResources(root);
	Texts        ::LoadResources(root);
	KeyCodeFonts ::LoadResources(root);
	Font         ::LoadCustomFonts(root);
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
	if (!curScene->IsPause()) 
		curScene->Update(dt);

	Sounds::HandleInput();
}

void SceneManager::Draw()
{
	curScene->Draw();
	settingScene.Draw();
	Sounds::Draw();
}

void SceneManager::OnKeyDown(BYTE keyCode)
{
	if (settingScene.IsOpening()) 
		settingScene.OnKeyDown(keyCode);
	else                         
		curScene->OnKeyDown(keyCode);

	switch (keyCode)
	{
		case VK_ESCAPE:
			ToggleSettingScene();
			break;

		case 'M':
			ToggleMuteMode();
			break;			
	}	
}

void SceneManager::OnKeyUp(BYTE keyCode)
{
	if (!curScene->IsPause())
		curScene->OnKeyUp(keyCode);
}

SceneManager& SceneManager::Instance()
{
	static SceneManager instance;
	return instance;
}
