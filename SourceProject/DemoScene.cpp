#include "pch.h"
#include "DemoScene.h"
#include "Textures.h"
#include "Sprites.h"
#include "Brick.h"
#include "Goomba.h"
#include "Camera.h"


void DemoScene::LoadResources()
{
	const auto root = GetRootJson("Resources\\db.json");

	for (UINT i = 0; i < (UINT)TextureType::Count; i++)
		Textures::Add( TextureType(i), root );

	for (UINT i = 0; i < (UINT)SpriteType::Count; i++)
		Sprites::Add( SpriteType(i), root );

	map = std::make_unique<Map>( root );
	grid = std::make_unique<Grid>( root );
	mario = std::make_unique<Mario>( Point(10.0f, 10.0f, 0.0f) );
}

void DemoScene::Update(float dt)
{
	objectsInViewPort = grid->GetObjectsInViewPort();

	mario->Update(dt, objectsInViewPort);

	Camera::Instance().CenterTo( mario->GetCenter() );

	for (auto& obj : objectsInViewPort)
	{
		const_cast<LPGAMEOBJECT>( obj )->Update(dt);
	}
}

void DemoScene::Draw()
{
	map->Render();
	mario->Render();

	for (auto& obj : objectsInViewPort)
	{
		obj->Render();
	}
}


