#pragma once

class Game 
{
private:
	LPDIRECT3D9        d3d           = NULL ;						
	LPDIRECT3DDEVICE9  d3ddv         = NULL ;				
	LPDIRECT3DSURFACE9 backBuffer	 = NULL ;		
	LPD3DXSPRITE	   spriteHandler = NULL ;

private:
	void InitDirectDevice();
	void Render();

public:
	~Game(); 
	void InitGame();
	void Run     ();

	inline CONST LPDIRECT3DDEVICE9 GetDirect3DDevice() const { return d3ddv         ; }
	inline CONST LPD3DXSPRITE      GetSpriteHandler () const { return spriteHandler ; }

	void FillColor(D3DCOLOR color) const;
	void DrawSolidRect(const RectF& area, D3DCOLOR color) const;
	void DrawOutLine(const RectF& rect, UINT thickness, D3DCOLOR color) const;
	void Draw(Vector2 pos, LPDIRECT3DTEXTURE9 texture, Rect portion, Vector2 vtScale = { 1.0f, 1.0f }, D3DCOLOR color = 0xFFFFFFFF) const;

private:
	Game() = default;
	Game(const Game&) = delete;

public:
	static Game& Instance();
};