#pragma once
#include <unordered_map>
#include <d3dx9.h>
#include "ISingleton.h"


class Texture : ISingleton
{
private:
	std::unordered_map<UINT, LPDIRECT3DTEXTURE9> textures;

public:
	LPDIRECT3DTEXTURE9 Get(UINT id) { return textures[id]; }
	void Add(int id, LPCSTR filePath, D3DCOLOR transparentColor);

private:
	Texture() : ISingleton(NULL) {}
public:
	static Texture& Instance()
	{
		static Texture instance;
		return instance;
	}
};