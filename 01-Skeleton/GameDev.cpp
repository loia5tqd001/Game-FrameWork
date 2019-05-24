#include "GameDev.h"
#include "Textures.h"
#include "Sprites.h"


void GameDev::LoadResources()
{
	static constexpr char* jsonPath = "textures\\sprites.json";

	for (UINT i = 0; i < (UINT)TextureType::Count; i++)
	{
		Textures::Instance().AddTexture(TextureType(i), jsonPath);
	}

	for (UINT i = 0; i < (UINT)SpriteType::Count; i++)
	{
		Sprites::Instance().AddSprite(SpriteType(i), jsonPath);
	}
}

void GameDev::InitObjects()
{
	mario = std::make_unique<Mario>();
	goombas.reserve(3);
	goombas.emplace_back(std::make_unique<Goomba>(D3DXVECTOR3(200.0f, 135.0f, 0.0f)));
	goombas.emplace_back(std::make_unique<Goomba>(D3DXVECTOR3(260.0f, 135.0f, 0.0f)));
	goombas.emplace_back(std::make_unique<Goomba>(D3DXVECTOR3(320.0f, 135.0f, 0.0f)));
}

void GameDev::Update(float dt)
{
	mario->Update(dt, {});
	for (const auto& goomba : goombas)
	{
		goomba->Update(dt, {});
	}
}
void GameDev::ComposeFrame()
{
	mario->Render();
	for (const auto& goomba : goombas)
	{
		goomba->Render();
	}
}

