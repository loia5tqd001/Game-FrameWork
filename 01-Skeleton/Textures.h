#pragma once
#include "enums.h"
#include "ISingleton.h"
#include <d3dx9.h>
#include <unordered_map>

class Textures : ISingleton
{
private:
	std::unordered_map<TextureType, LPDIRECT3DTEXTURE9> textureDictionary;

	void AddTexture(TextureType id, LPCSTR filePath, D3DCOLOR transparentColor);

public:
	void AddTexture(TextureType id, LPCSTR jsonPath);
	const LPDIRECT3DTEXTURE9 GetTexture(TextureType id) const;

private:
	Textures() : ISingleton(NULL) {}

public:
	static Textures& Instance()
	{
		static Textures instance;
		return instance;
	}
};


