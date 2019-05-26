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
}

void GameDev::Update(float dt)
{
	mario->Update(dt, {});
}
void GameDev::ComposeFrame()
{
	mario->Render();
}

