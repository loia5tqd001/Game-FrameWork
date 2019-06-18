#pragma once
#include "enums.h"
#include "Sprite.h"


class Sprites : ISingleton
{
private:
	std::unordered_map<SpriteId, Sprite> spriteDictionary;

private:
	void  AddSprite(SpriteId id, const Json::Value& root);

	const Json::Value&       GetSpriteInfoFromSpriteId(SpriteId id, const Json::Value& root) const;
	const LPDIRECT3DTEXTURE9 GetTextureFromSpriteInfo (const Json::Value& spriteInfo       ) const;
	const std::vector<Rect>  GetFramesFromSpriteInfo  (const Json::Value& spriteInfo       ) const;
	const Sprite&            GetSprite                (SpriteId id                         ) const;

public:
	static void Add(SpriteId id, const Json::Value& root);
	static const Sprite& Get(SpriteId id);


private:
	Sprites() : ISingleton(NULL) {}

public:
	static Sprites& Instance()
	{
		static Sprites instance;
		return instance;
	}

};
