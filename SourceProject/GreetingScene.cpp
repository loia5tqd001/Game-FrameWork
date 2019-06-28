#include "pch.h"
#include "GreetingScene.h"
#include "Window.h"
#include "SceneManager.h"
#include "Sounds.h"
#include "Textures.h"

GreetingScene::GreetingScene()
{
	LoadResources();
	Sounds::PlayAt(SoundId::Greeting);
}

void GreetingScene::LoadResources()
{
	const auto& greetingTexture = Textures::Get( TextureId::Greeting );
	static const auto& wnd = Window::Instance();

	std::vector<Rect> frames(1);
	frames.at(0) = { 0u, 0u, wnd.GetWidth(), wnd.GetHeight() };

	rememberNote = std::make_unique<Sprite>(greetingTexture, frames);
}

void GreetingScene::Update(float dt)
{
	if (Sounds::IsPlayingAt(SoundId::Greeting) == false)
		SceneManager::Instance().SetScene(Scene::Transition);
}

void GreetingScene::Draw()
{
	rememberNote->Draw( Vector2{ 0.0f, 0.0f } , 0 );
}

void GreetingScene::OnKeyDown(BYTE keyCode)
{
	switch (keyCode)
	{
		case VK_RETURN:
		case VK_SPACE:
			Sounds::StopAt(SoundId::Greeting);
			break;
	}
}
