#include "Sprites.h"
#include "MyException.h"
#include "Textures.h"
#include <assert.h>
#include <fstream>
#include <algorithm>



const Json::Value & Sprites::GetSpriteInfoFromSpriteId(SpriteType id, const Json::Value & root) const
{
	static auto matchSpriteIdPred = [&](const Json::Value& sprite) { return sprite[0].asUInt() == (UINT)id; };

	const Json::Value& sprites = root["sprites"];
	auto               found   = std::find_if(sprites.begin(), sprites.end(), matchSpriteIdPred);
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
	return Textures::Instance().GetTexture(textureId);
}

const std::vector<RECT> Sprites::GetFramesFromSpriteInfo(const Json::Value & spriteInfo) const
{
	const Json::Value& arrOfRects = spriteInfo[2];
	const UINT         nRects = arrOfRects.size();

	std::vector<RECT> frames;
	frames.reserve(nRects);

	for (UINT i = 0; i < nRects; i++)
	{
		const Json::Value& Rect = arrOfRects[i];

		RECT tmp;
		tmp.left   = Rect[0].asInt();
		tmp.top    = Rect[1].asInt();
		tmp.right  = Rect[2].asInt();
		tmp.bottom = Rect[3].asInt();

		frames.emplace_back(std::move(tmp));
	}
	return frames;
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
