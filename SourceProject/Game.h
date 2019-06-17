#pragma once
#include "Window.h"
#include "SceneManager.h"

class Game : ISingleton
{
private:
	LPDIRECT3D9        d3d           = NULL                    ;						
	LPDIRECT3DDEVICE9  d3ddv         = NULL                    ;				
	LPDIRECT3DSURFACE9 backBuffer	 = NULL                    ;		
	LPD3DXSPRITE	   spriteHandler = NULL                    ;	
	LPD3DXLINE         lineDraw      = NULL                    ;
	Window&            wnd           = Window::Instance()      ;
	SceneManager&      sceneManager  = SceneManager::Instance();

private:
	void InitDirectDevice();
	void Render();

public:
	~Game(); 
	void InitGame();
	void Run     ();

	CONST LPDIRECT3DDEVICE9 GetDirect3DDevice() const { return d3ddv; }

	void DrawLines(const std::vector<Vector2>& points, D3DCOLOR color) const;
	void Draw(Vector3 pos, LPDIRECT3DTEXTURE9 texture, Rect portion, Vector2 vtScale = { 1.0f, 1.0f }, int alpha = 255) const;

private:
	Game() : ISingleton(NULL) {}

public:
	static Game& Instance() 
	{ 
		static Game instance; 
		return instance; 
	}
};