#pragma once
#include "Sprite.h"
#include "States.h"
#include "ISingleton.h"
#include <cassert>
#include <unordered_map>


class Sprites : ISingleton
{
private:
	std::unordered_map<States, Sprite> spriteDictionary;

public:
	void AddSprite(States id, LPDIRECT3DTEXTURE9 texture, RECT portion, bool isFlipX)
	{
		assert(texture != nullptr);
		assert(spriteDictionary.count(id) == 0);
		spriteDictionary.emplace(id, Sprite(texture, portion, isFlipX));
	}

	Sprite& GetSprite(States id)
	{
		assert(spriteDictionary.count(id) == 1);
		return spriteDictionary.at(id);
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


