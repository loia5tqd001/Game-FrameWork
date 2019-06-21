#include "pch.h"
#include "Texts.h"
#include "Game.h"

void Texts::LoadResources(const Json::Value& root)
{
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

		Instance().textDictionary.emplace(id, frameOfText);
	}
}

void Texts::DrawString(const std::string& str, Vector3 drawablePos)
{
	for (UINT i = 0; i < str.size(); i++)
	{
		static UINT lastWidth = 0;
		if (str[i] != ' ') 
		{
			lastWidth = DrawSymbol( (TextId) std::toupper( str[i] ), drawablePos );
		}
		drawablePos.x += lastWidth + 1;
	}
}

UINT Texts::DrawSymbol(TextId id, const Vector3& drawablePos)
{
	assert(Instance().textDictionary.count(id) == 1);
	const Rect& rect = Instance().textDictionary.at(id);

	Game::Instance().Draw(drawablePos, Instance().texture, rect);
	return rect.GetWidth();
}
