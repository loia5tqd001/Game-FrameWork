#pragma once
#include "MainWindow.h"
#include "GameObject.h"

class Game
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
	virtual ~Game(); 

	virtual void OnKeyDown(BYTE keyCode){}
	virtual void OnKeyUp  (BYTE keyCode){}

	void Draw(float x, float y, LPDIRECT3DTEXTURE9 pTexture, RECT portion);
	LPDIRECT3DDEVICE9 GetDirect3DDevice() const { return d3ddv; }
};