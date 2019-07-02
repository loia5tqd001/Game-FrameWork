#include "pch.h"

LPDIRECT3DTEXTURE9               Texts::texture;
std::unordered_map<TextId, Rect> Texts::textDictionary;

void Texts::LoadResources(const Json::Value& root)
{
	texture = Textures::Get(TextureId::Misc);

	const auto& textsJson = root["texts"];
	for (const auto& textJson : textsJson)
	{
		const TextId id = (TextId)textJson[0].asUInt();

		const Rect frameOfText = Rect {
			textJson[1].asUInt(),
			textJson[2].asUInt(),
			textJson[3].asUInt(),
			textJson[4].asUInt()
		};

		textDictionary.emplace(id, frameOfText);
	}
}

void Texts::DrawString(const std::string& str, Vector2 drawablePos)
{
	for (UINT i = 0; i < str.size(); i++)
	{
		static UINT lastWidth = 0;
		if (str[i] != ' ') 
		{
			lastWidth = DrawSymbol( (TextId) toupper( str[i] ), drawablePos );
		}
		drawablePos.x += lastWidth + 1;
	}
}

UINT Texts::DrawSymbol(TextId id, const Vector2& drawablePos)
{
	assert(textDictionary.count(id) == 1);
	const Rect& rect = textDictionary.at(id);

	Game::Instance().Draw(drawablePos, texture, rect);
	return rect.GetWidth();
}
