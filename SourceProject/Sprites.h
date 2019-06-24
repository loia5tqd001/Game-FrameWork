#pragma once
#include "enums.h"
#include "Sprite.h"


class Sprites : ISingleton
{
private:
	std::unordered_map<SpriteId, Sprite> spriteDictionary;

private:
	void  AddSprite(SpriteId id, const Json::Value& root);
	const auto& GetSpriteInfoFromSpriteId(SpriteId id, const Json::Value& root) const;
	const auto  GetTextureFromSpriteInfo (const Json::Value& spriteInfo       ) const;
	const auto  GetFramesFromSpriteInfo  (const Json::Value& spriteInfo       ) const;
	const auto& GetSprite                (SpriteId id                         ) const;

public:
	static void LoadResources(const Json::Value& root);
	static const Sprite& Get(SpriteId id);

private:
	Sprites() : ISingleton(NULL) {}
	static Sprites& Instance()
	{
		static Sprites instance;
		return instance;
	}

};
