#pragma once
#include "define.h"
#include "Sprite.h"
#include <unordered_map>
#include <json/json.h>


class Sprites
{
private:
	std::unordered_map<SpriteType, Sprite> spriteDictionary;

	const Json::Value&       GetSpriteInfoFromSpriteId(SpriteType id, const Json::Value& root) const;
	const LPDIRECT3DTEXTURE9 GetTextureFromSpriteInfo (const Json::Value& spriteInfo         ) const;
	const std::vector<RECT>  GetFramesFromSpriteInfo  (const Json::Value& spriteInfo         ) const;

public:
	void AddSprite(SpriteType id, LPCSTR jsonPath);
	const Sprite& GetSprite(SpriteType id) const;

};
