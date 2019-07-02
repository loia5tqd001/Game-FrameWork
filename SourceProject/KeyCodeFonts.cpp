#include "pch.h"

LPDIRECT3DTEXTURE9             KeyCodeFonts::texture;
std::unordered_map<BYTE, Rect> KeyCodeFonts::keyCodeFontDictionary;

void KeyCodeFonts::LoadResources(const Json::Value& root)
{
	texture = Textures::Get(TextureId::KeyCodeFont);

	const auto& fontsJson = root["keycodefonts"];
	for (const auto& fontJson : fontsJson)
	{
		const BYTE keyCode = fontJson[0].asUInt();

		const Rect frameOfKey = Rect {
			fontJson[1].asUInt(),
			fontJson[2].asUInt(),
			fontJson[3].asUInt(),
			fontJson[4].asUInt()
		};

		keyCodeFontDictionary.emplace(keyCode, frameOfKey);
	}
}

UINT KeyCodeFonts::DrawKeyCode(BYTE keyCode, const Vector2& pos, D3DCOLOR color)
{
	assert(keyCodeFontDictionary.count(keyCode) == 1);
	const Rect& rect = keyCodeFontDictionary.at(keyCode);

	Game::Instance().Draw(pos, texture, rect, { 1.0f, 1.0f }, color);
	return rect.GetWidth();
}

void KeyCodeFonts::DrawString(const std::string& str, Vector2 pos, D3DCOLOR color)
{
	for (UINT i = 0; i < str.size(); i++)
	{
		static int lastWidth = 0;
		if (str[i] != ' ') 
		{
			lastWidth = DrawKeyCode( toupper( str[i] ), pos, color );
		}
		pos.x += lastWidth + 1;
	}
}
