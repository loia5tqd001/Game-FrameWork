#include "pch.h"

static auto& wnd = Window::Instance();
static auto& sceneManager = SceneManager::Instance();

Game::~Game()
{
	if (spriteHandler != NULL) spriteHandler->Release();
	if (backBuffer != NULL) backBuffer->Release();
	if (d3ddv != NULL) d3ddv->Release();
	if (d3d != NULL) d3d->Release();
}

void Game::FillColor(D3DCOLOR color) const
{
	d3ddv->ColorFill(backBuffer, NULL, color); 
}

void Game::DrawSolidRect(const RectF& area, D3DCOLOR color) const
{
	static const auto bboxTexture = Textures::Get(TextureId::Bbox);
	Game::Instance().Draw(area.GetTopLeft(), bboxTexture, area.GetOriginRect(), { 1.0f, 1.0f }, color);
}

void Game::DrawOutLine(const RectF& rect, UINT thickness, D3DCOLOR color) const
{
	const RectF left   = { rect.left             , rect.top               , rect.left  + thickness, rect.bottom - thickness };
	const RectF top    = { rect.left  + thickness, rect.top               , rect.right            , rect.top    + thickness };
	const RectF right  = { rect.right - thickness, rect.top    + thickness, rect.right            , rect.bottom             };
	const RectF bottom = { rect.left             , rect.bottom - thickness, rect.right - thickness, rect.bottom             };

	DrawSolidRect(left  , color);
	DrawSolidRect(top   , color);
	DrawSolidRect(right , color);
	DrawSolidRect(bottom, color);	
}

void Game::Draw(Vector2 pos, LPDIRECT3DTEXTURE9 texture, Rect portion, Vector2 vtScale, D3DCOLOR color) const
{
	static D3DXMATRIX oldMt;
	spriteHandler->GetTransform(&oldMt);
	const auto rasPos = pos.ToRasterizablePos();

	if (vtScale != Vector2(1.0f, 1.0f))
	{
		const float bboxWidth   = portion.GetWidth () * std::abs(vtScale.x);
		const float bboxHeight  = portion.GetHeight() * std::abs(vtScale.y);
		Vector2 centerScale = { rasPos.x + bboxWidth / 2, rasPos.y + bboxHeight / 2 };
		D3DXMATRIX newMt;
		D3DXMatrixTransformation2D(&newMt, &centerScale, 0.0f, &vtScale, NULL, 0.0f, NULL);
		newMt *= oldMt;
		spriteHandler->SetTransform(&newMt);
	}

	//Draw function: https://docs.microsoft.com/en-us/windows/desktop/direct3d9/id3dxsprite--draw
	spriteHandler->Draw(texture, &portion, NULL, &rasPos, color);
	spriteHandler->SetTransform(&oldMt);
}

Game& Game::Instance()
{ 
	static Game instance; 
	return instance; 
}

void Game::InitGame()
{
	wnd.InitWindow();
	InitDirectDevice();
	sceneManager.LoadResources();
	sceneManager.SetScene(Scene::Greeting);
}

void Game::InitDirectDevice()
{
	D3DPRESENT_PARAMETERS d3dpp;
	ZeroMemory(&d3dpp, sizeof(d3dpp));
	d3dpp.Windowed         = TRUE;
	d3dpp.SwapEffect       = D3DSWAPEFFECT_DISCARD;
	d3dpp.BackBufferFormat = D3DFMT_X8R8G8B8;
	d3dpp.BackBufferCount  = 1;
	d3dpp.BackBufferHeight = wnd.GetHeight();
	d3dpp.BackBufferWidth  = wnd.GetWidth();
	//d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE; //to turn off vsync, don't do this now, will cause weird behaviors

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

	if ( FAILED( D3DXCreateSprite(d3ddv, &spriteHandler) )) 
		ThrowMyException("Create direct device failed");
}

void Game::Render()
{
	d3ddv->BeginScene();
	d3ddv->ColorFill(backBuffer, NULL, D3DCOLOR_XRGB(200, 200, 200)); // TODO: When having texture background, color background is needless
	spriteHandler->Begin(D3DXSPRITE_ALPHABLEND);

	sceneManager.Draw();

	spriteHandler->End();
	d3ddv->EndScene();
	d3ddv->Present(NULL, NULL, NULL, NULL);
}

void Game::Run()
{
	while (wnd.ProcessMessage())
	{
		GameTimer::BeginFrame();

		sceneManager.Update(GameTimer::Dt());
		Render();

		wnd.SetTitleToFps();
	}
}






