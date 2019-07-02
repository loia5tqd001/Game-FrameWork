#pragma once

class Sprites 
{
private:
	static std::unordered_map<SpriteId, Sprite> spriteDictionary;

private:
	static void  AddSprite(SpriteId id, const Json::Value& root);
	static const auto& GetSpriteInfoFromSpriteId(SpriteId id, const Json::Value& root);
	static const auto  GetTextureFromSpriteInfo (const Json::Value& spriteInfo       );
	static const auto  GetFramesFromSpriteInfo  (const Json::Value& spriteInfo       );

public:
	static void LoadResources(const Json::Value& root);
	static const Sprite& Get(SpriteId id);
};
