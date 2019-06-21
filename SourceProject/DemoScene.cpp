#include "pch.h"
#include "DemoScene.h"
#include "Camera.h"

#include "Textures.h"
#include "Sprites.h"
#include "Sounds.h"
#include "Texts.h"

#include "Brick.h"
#include "Goomba.h"


DemoScene::DemoScene()
{
	LoadResources();
	Sounds::Invoke(Action::PlayLoop, SoundId::MarioMusic);
}

void DemoScene::LoadResources()
{
	const auto root = GetRootJson("Resources\\db.json");

	Textures::LoadResources(root);
	Sprites::LoadResources(root);
	Sounds::LoadResources(root);
	Texts::LoadResources(root);

	map = std::make_unique<Map>( root );
	grid = std::make_unique<Grid>( root );
	mario = std::make_unique<Mario>( Vector3(10.0f, 10.0f, 0.0f) );
}

void DemoScene::Update(float dt)
{
	grid->UpdateCells();

	mario->Update(dt, grid->GetObjectsInViewPort());

	Camera::Instance().CenterTo( mario->GetBBox().GetCenter() );

	for (auto& obj : grid->GetObjectsInViewPort())
	{
		obj->Update(dt);
	}
}

void DemoScene::Draw()
{
	map->Render();
	grid->RenderCells();
	mario->Render();

	for (auto& obj : grid->GetObjectsInViewPort())
	{
		obj->Render();
	}
}

void DemoScene::ToggleMuteMode() const
{
	Sounds::SetMuteMode( !Sounds::IsMute() );

	if (Sounds::IsMute()) 
		Sounds::Invoke(Action::StopAll);
	else                  
		Sounds::Invoke(Action::PlayLoop, SoundId::MarioMusic);
}

void DemoScene::OnKeyDown(BYTE keyCode)
{
	mario->OnKeyDown(keyCode);

	if (keyCode == 'M')
		ToggleMuteMode();
}


