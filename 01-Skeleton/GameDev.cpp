#include "GameDev.h"
#include "Textures.h"
#include "Frames.h"


void GameDev::LoadResources()
{
	Textures& textures = Textures::Instance();
	textures.AddTexture(TextureType::Mario, "textures\\mario.png", D3DCOLOR_XRGB(255, 255, 255));
	textures.AddTexture(TextureType::Misc, "textures\\misc.png", D3DCOLOR_XRGB(176, 224, 248));
	textures.AddTexture(TextureType::Enemy, "textures\\enemies.png", D3DCOLOR_XRGB(3, 26, 110));
	textures.AddTexture(TextureType::Bbox, "textures\\bbox.png", D3DCOLOR_XRGB(255, 255, 255));

	Frames& frames = Frames::Instance();
	frames.AddFrames(AnimationType::Mario_Die         , "textures\\ani_mario_die.txt");
	frames.AddFrames(AnimationType::Mario_BigIdle     , "textures\\ani_mario_bigidle.txt");
	frames.AddFrames(AnimationType::Mario_BigWalking  , "textures\\ani_mario_bigwalking.txt");
	frames.AddFrames(AnimationType::Mario_SmallIdle   , "textures\\ani_mario_smallidle.txt");
	frames.AddFrames(AnimationType::Mario_SmallWalking, "textures\\ani_mario_smallwalking.txt");
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

