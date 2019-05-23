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
	MainWindow&        wnd           = MainWindow::Instance();

private:
	void InitDirectDevice();
	void Render();

protected:
	virtual ~GameBase(); 
	virtual void LoadResources () = 0;
	virtual void InitObjects   () = 0;
	virtual void Update(float dt) = 0;
	virtual void ComposeFrame  () = 0;

public:
	void InitGame();
	void Run     ();

	virtual void OnKeyDown(BYTE keyCode){}
	virtual void OnKeyUp  (BYTE keyCode){}

	CONST LPDIRECT3DDEVICE9 GetDirect3DDevice() const { return d3ddv; }
	void Draw(
		const D3DXVECTOR3& pos, 
		const LPDIRECT3DTEXTURE9 texture, 
		const RECT& portion, 
		const D3DXVECTOR2& vtScale = { 1.0f, 1.0f }, 
		const int alpha = 255) 
		const;
};