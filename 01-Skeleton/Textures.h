#pragma once
#include "enums.h"
#include "ISingleton.h"

class Textures : ISingleton
{
private:
	std::unordered_map<TextureType, LPDIRECT3DTEXTURE9> textureDictionary;

	void AddTexture(TextureType id, LPCSTR filePath, D3DCOLOR transparentColor);
	void AddTexture(TextureType id, const Json::Value& root);
	void AddTexture(TextureType id, LPCSTR jsonPath);
	const Json::Value&       GetTextureInfoFromTextureId(TextureType id, const Json::Value& root) const;
	const LPDIRECT3DTEXTURE9 GetTexture(TextureType id) const;

public:
	static void Add(TextureType id, const Json::Value& root)	
	{
		Instance().AddTexture(id, root);
	}
	static void Add(TextureType id, LPCSTR jsonPath) 
	{
		Instance().AddTexture(id, jsonPath);
	}
	static const LPDIRECT3DTEXTURE9 Get(TextureType id) 
	{
		return Instance().GetTexture(id);
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


