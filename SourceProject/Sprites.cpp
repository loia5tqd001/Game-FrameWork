#include "pch.h"

std::unordered_map<SpriteId, Sprite> Sprites::spriteDictionary;

const auto & Sprites::GetSpriteInfoFromSpriteId(SpriteId id, const Json::Value & root)
{
	static auto matchSpriteIdPred = [&](const Json::Value& sprite) { return sprite[0].asUInt() == (UINT)id; };

	const auto& sprites = root["sprites"];
	const auto& found   = std::find_if(sprites.begin(), sprites.end(), matchSpriteIdPred);
	if (found == sprites.end())
	{
		ThrowMyException("Can't find any sprite match with id of:", (UINT)id);
	}
	return *found;
}

const auto Sprites::GetTextureFromSpriteInfo(const Json::Value & spriteInfo)
{
	TextureId textureId = (TextureId)spriteInfo[1].asUInt();
	return Textures::Get(textureId);
}

const auto Sprites::GetFramesFromSpriteInfo(const Json::Value & spriteInfo)
{
	const LONG left         = spriteInfo[2].asInt ();
	const LONG top          = spriteInfo[3].asInt ();
	const UINT spriteWidth  = spriteInfo[4].asUInt();
	const UINT spriteHeight = spriteInfo[5].asUInt();
	const UINT nRects       = spriteInfo[6].asUInt();
	const UINT margin       = spriteInfo[7].asUInt();

	std::vector<Rect> frames; frames.reserve(nRects);

	for (UINT i = 0; i < nRects; i++)
	{
		static Rect frame;
		frame.left   = left + (spriteWidth + margin) * i;
		frame.top    = top;
		frame.right  = frame.left + spriteWidth;
		frame.bottom = frame.top + spriteHeight;

		frames.emplace_back(frame);
	}

	return frames;
}

void Sprites::AddSprite(SpriteId id, const Json::Value& root)
{
	assert(spriteDictionary.count(id) == 0);
	
	const auto& spriteInfo = GetSpriteInfoFromSpriteId(id, root);
	const auto  texture    = GetTextureFromSpriteInfo(spriteInfo);
	const auto  frames     = GetFramesFromSpriteInfo(spriteInfo);

	Sprite sprite(texture, std::move(frames));
	spriteDictionary.emplace(id, std::move(sprite));
}

void Sprites::LoadResources(const Json::Value& root)
{
	for (UINT i = 0; i < (UINT)SpriteId::Count; i++)
		AddSprite( SpriteId(i), root );
}

const Sprite & Sprites::Get(SpriteId id)
{
	assert(spriteDictionary.count(id) == 1);
	return spriteDictionary.at(id);
}

