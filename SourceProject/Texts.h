#pragma once
#include "enums.h"
#include "Textures.h"

class Texts : ISingleton
{
private:
	const LPDIRECT3DTEXTURE9 texture = Textures::Get(TextureId::Misc);
	std::unordered_map<TextId, Rect> textDictionary;

public:
	static void LoadResources(const Json::Value& root);
	static UINT DrawSymbol(TextId id, const Vector3& drawablePos);
	static void DrawString(const std::string& str, Vector3 drawablePos);

private:
	Texts() : ISingleton(NULL) {}

public:
	static Texts& Instance() 
	{ 
		static Texts instance; 
		return instance; 
	}
};


