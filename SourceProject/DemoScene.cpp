#include "pch.h"
#include "DemoScene.h"
#include "Textures.h"
#include "Sprites.h"
#include "Brick.h"
#include "Goomba.h"
#include "Camera.h"
#include "Sound.h"


void DemoScene::LoadResources()
{
	const auto root = GetRootJson("Resources\\db.json");

	//Sound::getInstance()->loadSound("Resources\\man1.wav", "man1");
	//Sound::getInstance()->play("man1", true, 1);

	for (UINT i = 0; i < (UINT)TextureType::Count; i++)
		Textures::Add( TextureType(i), root );

	for (UINT i = 0; i < (UINT)SpriteType::Count; i++)
		Sprites::Add( SpriteType(i), root );

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

void DemoScene::OnKeyDown(BYTE keyCode)
{
	mario->OnKeyDown(keyCode);
}


