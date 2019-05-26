#include "pch.h"
#include "GameDev.h"
#include "Textures.h"
#include "Sprites.h"
#include "Brick.h"
#include "Goomba.h"


void GameDev::LoadResources()
{
	static constexpr char* jsonPath = "textures\\sprites.json";

	for (UINT i = 0; i < (UINT)TextureType::Count; i++)
	{
		Textures::Add(TextureType(i), jsonPath);
	}

	for (UINT i = 0; i < (UINT)SpriteType::Count; i++)
	{
		Sprites::Add(SpriteType(i), jsonPath);
	}
}

void GameDev::InitObjects()
{
	mario = std::make_unique<Mario>();

	goombas.reserve(3);
	goombas.emplace_back(std::make_unique<Goomba>(D3DXVECTOR3(200.0f, 185.0f, 0.0f)));
	goombas.emplace_back(std::make_unique<Goomba>(D3DXVECTOR3(260.0f, 185.0f, 0.0f)));
	goombas.emplace_back(std::make_unique<Goomba>(D3DXVECTOR3(320.0f, 185.0f, 0.0f)));

	bricks.reserve(35);
	for (UINT i = 0; i < 20; i++)
	{
		bricks.emplace_back(std::make_unique<Brick>(D3DXVECTOR3(16.0f * i, 200.0f, 0.0f)));
	}
	for (UINT i = 0; i < 5; i++)
	{
		bricks.emplace_back(std::make_unique<Brick>(D3DXVECTOR3(80.0f + i * 48.0f, 124.0f, 0.0f)));
		bricks.emplace_back(std::make_unique<Brick>(D3DXVECTOR3(80.0f + i * 48.0f, 140.0f, 0.0f)));
		bricks.emplace_back(std::make_unique<Brick>(D3DXVECTOR3(64.0f + i * 48.0f, 140.0f, 0.0f)));
	}
}

void GameDev::Update(float dt)
{
	static auto getCollidableObjects = [this]()
	{
		std::vector<LPCGAMEOBJECT> coObjects;
		coObjects.reserve(goombas.size() + bricks.size());
		for (const auto& goomba : goombas)
		{
			coObjects.emplace_back(goomba.get());
		}
		for (const auto& brick : bricks)
		{
			coObjects.emplace_back(brick.get());
		}
		return coObjects;
	};

	mario->Update(dt, getCollidableObjects());
	for (const auto& goomba : goombas)
	{
		goomba->Update(dt, {});
	}
	for (const auto& brick : bricks)
	{
		brick->Update(dt, {});
	}
}
void GameDev::ComposeFrame()
{
	mario->Render();
	for (const auto& goomba : goombas)
	{
		goomba->Render();
	}
	for (const auto& brick : bricks)
	{
		brick->Render();
	}
}


