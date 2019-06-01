#include "pch.h"
#include "Sprites.h"
#include "MyException.h"
#include "Textures.h"
#include "RectF.h"



const Json::Value & Sprites::GetSpriteInfoFromSpriteId(SpriteType id, const Json::Value & root) const
{
	static auto matchSpriteIdPred = [&](const Json::Value& sprite) { return sprite[0].asUInt() == (UINT)id; };

	const Json::Value& sprites = root["sprites"];
	const auto&        found   = std::find_if(sprites.begin(), sprites.end(), matchSpriteIdPred);
	if (found == sprites.end())
	{
		DebugOut("Can't find any sprite match with id of: ", (UINT)id, "\n");
		ThrowMyException("Can't find any sprite match with particular id");
	}
	return *found;
}

const LPDIRECT3DTEXTURE9 Sprites::GetTextureFromSpriteInfo(const Json::Value & spriteInfo) const
{
	TextureType textureId = (TextureType)spriteInfo[1].asUInt();
	return Textures::Get(textureId);
}

const std::vector<RECT> Sprites::GetFramesFromSpriteInfo(const Json::Value & spriteInfo) const
{
	const Json::Value& arrOfRects = spriteInfo[2];
	const UINT         nRects = arrOfRects.size();

	std::vector<RECT> frames;
	frames.reserve(nRects);

	for (UINT i = 0; i < nRects; i++)
	{
		const Json::Value& rectJson = arrOfRects[i];

		static RECT frame;
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
	
	const Json::Value&       spriteInfo = GetSpriteInfoFromSpriteId(id, root);
	const LPDIRECT3DTEXTURE9 texture    = GetTextureFromSpriteInfo(spriteInfo);
	const std::vector<RECT>  frames     = GetFramesFromSpriteInfo(spriteInfo);

	Sprite sprite(texture, std::move(frames));
	spriteDictionary.emplace(id, std::move(sprite));
}

const Sprite & Sprites::GetSprite(SpriteType id) const
{
	assert(spriteDictionary.count(id) == 1);
	return spriteDictionary.at(id);
}

void Sprites::AddSprite(SpriteType id, LPCSTR jsonPath)
{
	assert(spriteDictionary.count(id) == 0);

	std::ifstream jsonFile(jsonPath);
	if (!jsonFile.is_open())
	{
		DebugOut("Can't open json file to add sprite: ", jsonPath, "\n");
		ThrowMyException("Can't open json file to add sprite");
	}

	Json::Reader reader;
	Json::Value  root;
	if (!reader.parse(jsonFile, root))
	{
		LPCSTR msg = reader.getFormattedErrorMessages().c_str();
		DebugOut("Parse json file failed: ", msg, "\n");
		ThrowMyException(msg);
	}

	const Json::Value&       spriteInfo = GetSpriteInfoFromSpriteId(id, root);
	const LPDIRECT3DTEXTURE9 texture = GetTextureFromSpriteInfo(spriteInfo);
	const std::vector<RECT>  frames = GetFramesFromSpriteInfo(spriteInfo);

	Sprite sprite(texture, std::move(frames));
	spriteDictionary.emplace(id, std::move(sprite));
}
