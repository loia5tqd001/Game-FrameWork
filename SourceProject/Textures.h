#pragma once
#include "enums.h"

class Textures : ISingleton
{
private:
	std::unordered_map<TextureId, LPDIRECT3DTEXTURE9> textureDictionary;

private:
	void AddTexture(TextureId id, LPCSTR filePath, D3DCOLOR transparentColor);
	void AddTexture(TextureId id, const Json::Value& root);
	const Json::Value&       GetTextureInfoFromTextureId(TextureId id, const Json::Value& root) const;
	const LPDIRECT3DTEXTURE9 GetTexture(TextureId id) const;

public:
	static void LoadResources(const Json::Value& root);
	static const LPDIRECT3DTEXTURE9 Get(TextureId id);

private:
	Textures() : ISingleton(NULL) {}

public:
	static Textures& Instance()
	{
		static Textures instance;
		return instance;
	}
};


