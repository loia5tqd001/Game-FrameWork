#pragma once

class Font
{
private:
	LPD3DXSPRITE spriteHandler = nullptr ;
	LPD3DXFONT   fontDraw      = nullptr ;

public:
	Font(UINT size, LPCSTR font);
	Font(const Font&) = delete;
	~Font();

	void AdjustFont(UINT size, LPCSTR font);
	void DrawString(const std::string& str, const Vector2& pos, D3DCOLOR color) const;
};

