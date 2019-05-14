#pragma once
#include "ISingleton.h"
#include "TextureType.h"
#include <d3dx9.h>
#include <unordered_map>

class Textures : ISingleton
{
private:
	std::unordered_map<TextureType, LPDIRECT3DTEXTURE9> textureDictionary;

public:
	void AddTexture(TextureType id, LPCSTR filePath, D3DCOLOR transparentColor);
	CONST LPDIRECT3DTEXTURE9 GetTexture(TextureType id);

private:
	Textures() : ISingleton(NULL) {}

public:
	static Textures& Instance()
	{
		static Textures instance;
		return instance;
	}
};


