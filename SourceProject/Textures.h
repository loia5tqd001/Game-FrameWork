#pragma once

class Textures 
{
private:
	static std::unordered_map<TextureId, LPDIRECT3DTEXTURE9> textureDictionary;

private:
	static void AddTexture(TextureId id, LPCSTR filePath, D3DCOLOR transparentColor);
	static void AddTexture(TextureId id, const Json::Value& root);
	static const auto& GetTextureInfoFromTextureId(TextureId id, const Json::Value& root);

public:
	static void LoadResources(const Json::Value& root);
	static const LPDIRECT3DTEXTURE9 Get(TextureId id);
};


