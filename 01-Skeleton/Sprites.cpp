#include "pch.h"
#include "Sprites.h"
#include "Textures.h"



const Json::Value & Sprites::GetSpriteInfoFromSpriteId(SpriteType id, const Json::Value & root) const
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

const LPDIRECT3DTEXTURE9 Sprites::GetTextureFromSpriteInfo(const Json::Value & spriteInfo) const
{
	TextureType textureId = (TextureType)spriteInfo[1].asUInt();
	return Textures::Get(textureId);
}

const std::vector<Rect> Sprites::GetFramesFromSpriteInfo(const Json::Value & spriteInfo) const
{
	const auto& arrOfRects = spriteInfo[2];
	const auto& nRects = arrOfRects.size();

	std::vector<Rect> frames; frames.reserve(nRects);

	for (UINT i = 0; i < nRects; i++)
	{
		const auto& rectJson = arrOfRects[i];

		static Rect frame;
		frame.left   = rectJson[0].asInt();
		frame.top    = rectJson[1].asInt();
		frame.right  = rectJson[2].asInt();
		frame.bottom = rectJson[3].asInt();

		frames.emplace_back(std::move(frame));
	}
	return frames;
}

void Sprites::AddSprite(SpriteType id, const Json::Value& root)
{
	assert(spriteDictionary.count(id) == 0);
	
	const auto& spriteInfo = GetSpriteInfoFromSpriteId(id, root);
	const auto  texture    = GetTextureFromSpriteInfo(spriteInfo);
	const auto  frames     = GetFramesFromSpriteInfo(spriteInfo);

	Sprite sprite(texture, std::move(frames));
	spriteDictionary.emplace(id, std::move(sprite));
}

const Sprite & Sprites::GetSprite(SpriteType id) const
{
	assert(spriteDictionary.count(id) == 1);
	return spriteDictionary.at(id);
}
