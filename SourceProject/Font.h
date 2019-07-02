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

	static void LoadCustomFonts(const Json::Value& root);

	void AdjustFont(UINT size, LPCSTR font);
	void DrawStringWithin(const std::string& str, const RectF& area, D3DCOLOR color, DWORD format = DT_CENTER) const;
	void DrawString(const std::string& str, const Vector2& pos, D3DCOLOR color) const;
};

