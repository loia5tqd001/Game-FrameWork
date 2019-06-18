#include "pch.h"
#include "DemoScene.h"
#include "Camera.h"

#include "Textures.h"
#include "Sprites.h"
#include "Sounds.h"

#include "Brick.h"
#include "Goomba.h"


DemoScene::DemoScene()
{
	LoadResources();
	Sounds::Invoke(Action::PlayLoop, SoundId::Test);
}

void DemoScene::LoadResources()
{
	const auto root = GetRootJson("Resources\\db.json");

	for (UINT i = 0; i < (UINT)TextureId::Count; i++)
		Textures::Add( TextureId(i), root );

	for (UINT i = 0; i < (UINT)SpriteId::Count; i++)
		Sprites::Add( SpriteId(i), root );

	for (UINT i = 0; i < (UINT)SoundId::Count; i++)
		Sounds::Add( SoundId(i), root );

	map = std::make_unique<Map>( root );
	grid = std::make_unique<Grid>( root );
	mario = std::make_unique<Mario>( Vector3(10.0f, 10.0f, 0.0f) );
}

void DemoScene::Update(float dt)
{
	grid->UpdateCells();

	mario->Update(dt, grid->GetObjectsInViewPort());

	Camera::Instance().CenterTo( mario->GetBoundingBox().GetCenter() );

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
		Sounds::Invoke(Action::PlayLoop, SoundId::Test);
}

void DemoScene::OnKeyDown(BYTE keyCode)
{
	mario->OnKeyDown(keyCode);

	if (keyCode == 'M')
		ToggleMuteMode();
}


