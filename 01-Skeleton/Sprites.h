#pragma once
#include "enums.h"
#include "ISingleton.h"
#include "Sprite.h"
#include <unordered_map>
#include <json/json.h>


class Sprites : ISingleton
{
private:
	std::unordered_map<SpriteType, Sprite> spriteDictionary;

	void Add(SpriteType id, LPCSTR jsonPath);
	const Json::Value&       GetSpriteInfoFromSpriteId(SpriteType id, const Json::Value& root) const;
	const LPDIRECT3DTEXTURE9 GetTextureFromSpriteInfo (const Json::Value& spriteInfo         ) const;
	const std::vector<RECT>  GetFramesFromSpriteInfo  (const Json::Value& spriteInfo         ) const;
	const Sprite&            Get                      (SpriteType id                         ) const;

public:
	static void AddSprite(SpriteType id, LPCSTR jsonPath) {
		Instance().Add(id, jsonPath);
	}
	static const Sprite& GetSprite(SpriteType id) {
		return Instance().Get(id);
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
