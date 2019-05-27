#pragma once
#include "enums.h"
#include "ISingleton.h"
#include "Sprite.h"


class Sprites : ISingleton
{
private:
	std::unordered_map<SpriteType, Sprite> spriteDictionary;

	void  AddSprite(SpriteType id, LPCSTR jsonPath);
	const Json::Value&       GetSpriteInfoFromSpriteId(SpriteType id, const Json::Value& root) const;
	const LPDIRECT3DTEXTURE9 GetTextureFromSpriteInfo (const Json::Value& spriteInfo         ) const;
	const std::vector<RECT>  GetFramesFromSpriteInfo  (const Json::Value& spriteInfo         ) const;
	const Sprite&            GetSprite                (SpriteType id                         ) const;

public:
	static void Add(SpriteType id, LPCSTR jsonPath) {
		Instance().AddSprite(id, jsonPath);
	}
	static const Sprite& Get(SpriteType id) {
		return Instance().GetSprite(id);
	}

private:
	Sprites() : ISingleton(NULL) {}

public:
	static Sprites& Instance()
	{
		static Sprites instance;
		return instance;
	}

};
