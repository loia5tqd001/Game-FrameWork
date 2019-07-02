#pragma once

// Bitmap Font to draw keyCode
class KeyCodeFonts
{
private:
	static LPDIRECT3DTEXTURE9 texture;
	static std::unordered_map<BYTE, Rect> keyCodeFontDictionary;

public:
	static void LoadResources(const Json::Value& root);
	static UINT DrawKeyCode(BYTE keyCode, const Vector2& pos, D3DCOLOR color);
	static void DrawString(const std::string& str, Vector2 pos, D3DCOLOR color);
};

