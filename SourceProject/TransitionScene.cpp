#include "pch.h"
#include "TransitionScene.h"
#include "Game.h"
#include "SceneManager.h"

void TransitionScene::Update(float dt)
{
	timePassed += GameTimer::Dt();
	if (timePassed >= 0.5f)
		SceneManager::Instance().SetScene(Scene::Demo);
}

void TransitionScene::Draw()
{
	Game::Instance().FillColor(0); // 0: black
}
