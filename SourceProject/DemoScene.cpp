#include "pch.h"
#include "DemoScene.h"

static auto& cam = Camera::Instance();

DemoScene::DemoScene()
{
	LoadResources();

	if (!IsPause()) 
		Sounds::PlayLoop(SoundId::MarioMusic);
}

void DemoScene::LoadResources()
{
	const auto root = GetRootJson("Resources\\Data\\demo.json");

	map = std::make_unique<Map>( root );
	grid = std::make_unique<Grid>( root );
	mario = std::make_unique<Mario>( Vector2(10.0f, 10.0f) );
}

void DemoScene::Update(float dt)
{
	grid->UpdateCells();

	mario->Update(dt, grid->GetObjectsInViewPort());

	cam.CenterTo( mario->GetBBox().GetCenter() );
	cam.ClampWithin( map->GetWorldBoundary() );
	mario->ClampWithin( map->GetWorldBoundary() );

	for (auto& obj : grid->GetObjectsInViewPort())
	{
		obj->Update(dt);
	}
}

void DemoScene::Draw()
{
	map->Render();
	mario->Render();

	for (auto& obj : grid->GetObjectsInViewPort())
	{
		obj->Render();
	}

	grid->RenderCells();
}

void DemoScene::OnKeyDown(BYTE keyCode)
{
	switch (keyCode)
	{
		case VK_CONTROL:
			DebugDraw::ToggleDebugMode();
			break;
	}

	mario->OnKeyDown(keyCode);
}


