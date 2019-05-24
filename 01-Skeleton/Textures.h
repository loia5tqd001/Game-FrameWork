#pragma once
#include "enums.h"
#include "ISingleton.h"
#include <d3dx9.h>
#include <unordered_map>

class Textures : ISingleton
{
private:
	std::unordered_map<TextureType, LPDIRECT3DTEXTURE9> textureDictionary;

	void Add(TextureType id, LPCSTR filePath, D3DCOLOR transparentColor);
	void Add(TextureType id, LPCSTR jsonPath);
	const LPDIRECT3DTEXTURE9 Get(TextureType id) const;

public:
	static void AddTexture(TextureType id, LPCSTR jsonPath)	{
		Instance().Add(id, jsonPath);
	}
	static const LPDIRECT3DTEXTURE9 GetTexture(TextureType id) {
		return Instance().Get(id);
	}

private:
	Textures() : ISingleton(NULL) {}

public:
	static Textures& Instance()
	{
		static Textures instance;
		return instance;
	}
};


