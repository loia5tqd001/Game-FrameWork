#include "GameDevelopment.h"
#include "Texture.h"


void GameDev::LoadResources()
{
	Texture * textures = &Texture::Instance();

	textures->Add(ID_TEX_MARIO, "textures\\mario.png", D3DCOLOR_XRGB(176, 224, 248));


	CSprites * sprites = CSprites::GetInstance();
	CAnimations * animations = CAnimations::GetInstance();

	LPDIRECT3DTEXTURE9 texMario = textures->Get(ID_TEX_MARIO);


	sprites->Add(10001, 246, 154, 259, 181, texMario);
	sprites->Add(10002, 275, 154, 290, 181, texMario);
	sprites->Add(10003, 304, 154, 321, 181, texMario);

	sprites->Add(10011, 186, 154, 199, 181, texMario);
	sprites->Add(10012, 155, 154, 170, 181, texMario);
	sprites->Add(10013, 125, 154, 140, 181, texMario);


	LPANIMATION ani;

	ani = new CAnimation(100);
	ani->Add(10001);
	ani->Add(10002);
	ani->Add(10003);
	animations->Add(500, ani);

	ani = new CAnimation(100);
	ani->Add(10011);
	ani->Add(10012);
	ani->Add(10013);
	animations->Add(501, ani);


	mario = new GameObject();
	mario->AddAnimation(500);
	mario->AddAnimation(501);

	mario->SetPosition(10.0f, 100.0f);
}

void GameDev::Update(float dt)
{
	mario->Update(dt);
}
void GameDev::ComposeFrame()
{
	mario->Render();
}

