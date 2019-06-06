#pragma once
#include "enums.h"
#include "Sprite.h"


class Sprites : ISingleton
{
private:
	std::unordered_map<SpriteType, Sprite> spriteDictionary;

private:
	void  AddSprite(SpriteType id, const Json::Value& root);

	const Json::Value&       GetSpriteInfoFromSpriteId(SpriteType id, const Json::Value& root) const;
	const LPDIRECT3DTEXTURE9 GetTextureFromSpriteInfo (const Json::Value& spriteInfo         ) const;
	const std::vector<Rect>  GetFramesFromSpriteInfo  (const Json::Value& spriteInfo         ) const;
	const Sprite&            GetSprite                (SpriteType id                         ) const;

public:
	static void Add(SpriteType id, const Json::Value& root) 
	{
		Instance().AddSprite(id, root);
	}
	static const Sprite& Get(SpriteType id) 
	{
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
