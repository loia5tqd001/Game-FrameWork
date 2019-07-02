#pragma once

class Texts
{
private:
	static LPDIRECT3DTEXTURE9 texture;
	static std::unordered_map<TextId, Rect> textDictionary;

public:
	static void LoadResources(const Json::Value& root);
	static UINT DrawSymbol(TextId id, const Vector2& drawablePos);
	static void DrawString(const std::string& str, Vector2 drawablePos);
};


