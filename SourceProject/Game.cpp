#include "pch.h"
#include "Game.h"
#include "Sounds.h"

Game::~Game()
{
	if (spriteHandler != NULL) spriteHandler->Release();
	if (backBuffer != NULL) backBuffer->Release();
	if (lineDraw != NULL) lineDraw->Release();
	if (d3ddv != NULL) d3ddv->Release();
	if (d3d != NULL) d3d->Release();
}

void Game::AdjustFontString(UINT size, LPCSTR font)
{
	if (fontDraw != NULL) fontDraw->Release();
	assert( SUCCEEDED( D3DXCreateFontA(d3ddv, size, 0, FW_NORMAL, 1, FALSE, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, ANTIALIASED_QUALITY, FF_MODERN, font, &fontDraw) ));
}

void Game::DrawString(const std::string& str, const Vector3& pos, D3DCOLOR color) const
{
	static Rect rect;
	SetRect(&rect, (int)pos.x, (int)pos.y, wnd.GetWidth(), wnd.GetHeight());
	fontDraw->DrawText(spriteHandler, str.c_str(), -1, &rect, DT_NOCLIP, color);
}

void Game::DrawLines(const std::vector<Vector2>& points, D3DCOLOR color) const
{
	lineDraw->Begin();
	lineDraw->Draw(points.data(), points.size(), color);
	lineDraw->End();
}

void Game::Draw(Vector3 pos, LPDIRECT3DTEXTURE9 texture, Rect portion, Vector2 vtScale, int alpha) const
{
	Draw(pos, texture, portion, vtScale, D3DCOLOR_ARGB(alpha, 255, 255, 255));
}

void Game::Draw(Vector3 pos, LPDIRECT3DTEXTURE9 texture, Rect portion, Vector2 vtScale, D3DCOLOR color) const
{
	D3DXMATRIX oldMt;
	spriteHandler->GetTransform(&oldMt);

	if (vtScale != Vector2(1.0f, 1.0f))
	{
		const float bboxWidth   = portion.GetWidth () * std::abs(vtScale.x);
		const float bboxHeight  = portion.GetHeight() * std::abs(vtScale.y);
		Vector2 centerScale = { pos.x + bboxWidth / 2, pos.y + bboxHeight / 2 };
		D3DXMATRIX newMt;
		D3DXMatrixTransformation2D(&newMt, &centerScale, 0.0f, &vtScale, NULL, 0.0f, NULL);
		newMt *= oldMt;
		spriteHandler->SetTransform(&newMt);
	}

	//Draw function: https://docs.microsoft.com/en-us/windows/desktop/direct3d9/id3dxsprite--draw
	spriteHandler->Draw(texture, &portion, NULL, &pos, color);
	spriteHandler->SetTransform(&oldMt);
}

void Game::InitGame()
{
	wnd.InitWindow();
	InitDirectDevice();
	Sounds::Instance().InitDirectSound();
	sceneManager.SetScene(Scene::Demo);
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

	assert( SUCCEEDED( D3DXCreateSprite(d3ddv, &spriteHandler) ));
	assert( SUCCEEDED( D3DXCreateLine(d3ddv, &lineDraw)        ));
	assert( SUCCEEDED( D3DXCreateFontA(d3ddv, 13, 0, FW_NORMAL, 1, //AddFontResourceEx( , , ); if need more custom font
									   FALSE, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, ANTIALIASED_QUALITY, FF_MODERN, "Arial", &fontDraw) ));
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

		sceneManager.Update(GameTimer::DeltaTime());
		Render();

		wnd.SetTitleToFps();
	}
}






