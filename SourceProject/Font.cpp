#include "pch.h"
#include "Font.h"
#include "Game.h"
#include "enums.h"

Font::Font(UINT size, LPCSTR font) : spriteHandler( Game::Instance().GetSpriteHandler() )
{
	AdjustFont(size, font);
}

Font::~Font()
{
	if (fontDraw != nullptr)
	{
		fontDraw->Release();
		fontDraw = nullptr;
	}
}

void Font::AddCustomFonts()
{
	for (UINT i = 0; i < CustomFonts::nFonts; i++)
	{
		assert( AddFontResourceEx(CustomFonts::fonts[i], FR_PRIVATE, NULL) );
	}
}

void Font::AdjustFont(UINT size, LPCSTR font)
{
	if (fontDraw != NULL) fontDraw->Release();

	//AddFontResourceEx( , , ); if need more custom font
	if( FAILED( D3DXCreateFontA(Game::Instance().GetDirect3DDevice(), size, 0, FW_NORMAL, 1, FALSE, DEFAULT_CHARSET, 
								OUT_DEFAULT_PRECIS, ANTIALIASED_QUALITY, FF_MODERN, font, &fontDraw) ))
		ThrowMyException("Create font", font, "with size of", size, "unsuccessfully");
}

void Font::DrawStringWithin(const std::string& str, const RectF& area, D3DCOLOR color, DWORD format) const
{
	fontDraw->DrawText(spriteHandler, str.c_str(), -1, &(Rect)area, format, color);
}

void Font::DrawString(const std::string& str, const Vector2& pos, D3DCOLOR color) const
{
	static Rect rect;
	SetRect(&rect, (int)pos.x, (int)pos.y, 0, 0);
	fontDraw->DrawText(spriteHandler, str.c_str(), -1, &rect, DT_NOCLIP, color);
}
