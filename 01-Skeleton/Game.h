#pragma once
#include "MainWindow.h"
#include "Scene.h"

class Game : ISingleton
{
private:
	LPDIRECT3D9        d3d           = NULL                    ;						
	LPDIRECT3DDEVICE9  d3ddv		 = NULL                    ;				
	LPDIRECT3DSURFACE9 backBuffer	 = NULL                    ;		
	LPD3DXSPRITE	   spriteHandler = NULL                    ;	
	MainWindow&        wnd           = MainWindow  ::Instance();

	std::unique_ptr<Scene> curScene;

private:
	void InitDirectDevice();
	void Render          ();

public:
	        ~Game();
	void InitGame();
	void Run     ();

	void OnKeyDown(BYTE keyCode) { curScene->OnKeyDown(keyCode); }
	void OnKeyUp  (BYTE keyCode) { curScene->OnKeyUp  (keyCode); }

	void ChangeScene(SceneType sceneId);
	CONST LPDIRECT3DDEVICE9 GetDirect3DDevice() const { return d3ddv; }
	void Draw(
		const D3DXVECTOR3& pos, 
		const LPDIRECT3DTEXTURE9 texture, 
		const RECT& portion, 
		const D3DXVECTOR2& vtScale = { 1.0f, 1.0f }, 
		const int alpha = 255) 
		const;

private:
	Game() : ISingleton(NULL) {}

public:
	static Game& Instance()
	{
		static Game instance;
		return instance;
	}
};