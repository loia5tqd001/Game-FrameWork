#include "GameBase.h"
#include "MyException.h"
#include "GameTimer.h"


GameBase::~GameBase()
{
	if (spriteHandler != NULL) spriteHandler->Release();
	if (backBuffer != NULL) backBuffer->Release();
	if (d3ddv != NULL) d3ddv->Release();
	if (d3d != NULL) d3d->Release();
}

void GameBase::Draw(const D3DXVECTOR3& pos, LPDIRECT3DTEXTURE9 texture, const RECT& portion, bool isFlipX, int alpha) const
{
	D3DXMATRIX oldMt;
	spriteHandler->GetTransform(&oldMt);

	if (isFlipX)
	{
		D3DXVECTOR2 vtScaleFlipX = D3DXVECTOR2(-1.0f, 1.0f);
		D3DXVECTOR2 centerScale = D3DXVECTOR2(pos.x, pos.y);
		D3DXMATRIX newMt;
		D3DXMatrixTransformation2D(&newMt, &centerScale, 0.0f, &vtScaleFlipX, NULL, 0.0f, NULL);
		D3DXMATRIX finalMt = newMt * oldMt;
		spriteHandler->SetTransform(&finalMt);
	}

	// 'pos' is the position of the entity owns the sprite, which anchors to the center of that enity.
	// by default we will draw from the position at the top left of the sprite, not the center.
	// so we calculate starting drawing position by offsetting to the top left direction from 'pos'

	float xDraw = pos.x - float(portion.right - portion.left) / 2;
	float yDraw = pos.y - float(portion.bottom - portion.top) / 2;
	D3DXVECTOR3 drawPos(xDraw, yDraw, 0.0f);
	spriteHandler->Draw(texture, &portion, NULL, &drawPos, D3DCOLOR_ARGB(alpha, 255, 255, 255));

	//Draw function: https://docs.microsoft.com/en-us/windows/desktop/direct3d9/id3dxsprite--draw

	spriteHandler->SetTransform(&oldMt);
}

void GameBase::InitGame()
{
	wnd.InitWindow();
	InitDirectDevice();
	LoadResources();
	InitObjects();
}

void GameBase::InitDirectDevice()
{
	D3DPRESENT_PARAMETERS d3dpp;
	ZeroMemory(&d3dpp, sizeof(d3dpp));
	d3dpp.Windowed		   = TRUE;
	d3dpp.SwapEffect	   = D3DSWAPEFFECT_DISCARD;
	d3dpp.BackBufferFormat = D3DFMT_X8R8G8B8;
	d3dpp.BackBufferCount  = 1;
	d3dpp.BackBufferHeight = wnd.GetHeight();
	d3dpp.BackBufferWidth  = wnd.GetWidth();

	LPDIRECT3D9 d3d = Direct3DCreate9(D3D_SDK_VERSION);
	d3d->CreateDevice(
		 D3DADAPTER_DEFAULT,
		 D3DDEVTYPE_HAL,
		 wnd.GetHWnd(),
		 D3DCREATE_SOFTWARE_VERTEXPROCESSING,
		 &d3dpp,
		 &d3ddv);

	if (d3ddv == nullptr) ThrowMyException("Create DirectX Device failed");

	d3ddv->GetBackBuffer(0, 0, D3DBACKBUFFER_TYPE_MONO, &backBuffer);
	D3DXCreateSprite(d3ddv, &spriteHandler);
}

void GameBase::Render()
{
	if (d3ddv->BeginScene())	
	{
		d3ddv->ColorFill(backBuffer, NULL, D3DCOLOR_XRGB(255, 0, 0)); // TODO: When having texture background, color background is needless
		spriteHandler->Begin(D3DXSPRITE_ALPHABLEND);
		ComposeFrame(); // actual development render
		spriteHandler->End();
		d3ddv->EndScene();
	}

	d3ddv->Present(NULL, NULL, NULL, NULL);
}

void GameBase::Run()
{
	while (wnd.ProcessMessage())
	{
		GameTimer::BeginFrame();
		Update(GameTimer::DeltaTime());
		Render();
	}
}






