#pragma once
#include "MainWindow.h"
#include <d3dx9.h>

class GameBase
{
private:
	LPDIRECT3D9		   d3d			 = NULL;						
	LPDIRECT3DDEVICE9  d3ddv		 = NULL;				
	LPDIRECT3DSURFACE9 backBuffer	 = NULL;		
	LPD3DXSPRITE	   spriteHandler = NULL;			
	
	MainWindow& wnd = MainWindow::Instance();
	void InitDirectDevice();
	void Render();

protected:
	virtual void LoadResources () = 0;
	virtual void Update(float dt) = 0;
	virtual void ComposeFrame  () = 0;

public:
	void InitGame();
	void Run     ();
	GameBase() { InitGame(); }
	virtual ~GameBase(); 

	virtual void OnKeyDown(BYTE keyCode){}
	virtual void OnKeyUp  (BYTE keyCode){}

	LPDIRECT3DDEVICE9 GetDirect3DDevice() const { return d3ddv        ; }
	LPD3DXSPRITE	  GetSpriteHandler () const { return spriteHandler; }
};