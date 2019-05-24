#include "MyException.h"
#include "Textures.h"
#include "GameDev.h"
#include <algorithm>
#include <fstream>
#include <json/json.h>


void Textures::AddTexture(TextureType id, LPCSTR texturePath, D3DCOLOR transparentColor)
{
	assert(textureDictionary.count(id) == 0);

	D3DXIMAGE_INFO info;
	if (D3DXGetImageInfoFromFile(texturePath, &info) != D3D_OK)
	{
		DebugOut("[ERROR] Get image info from file failed: ", texturePath, "\n");
		ThrowMyException("Get image info from file failed");
	}

	LPDIRECT3DTEXTURE9 texture;
	HRESULT result = D3DXCreateTextureFromFileEx(
					 GameDev::Instance().GetDirect3DDevice(),
					 texturePath,
					 info.Width,
					 info.Height,
					 D3DX_DEFAULT,
					 D3DUSAGE_DYNAMIC,
					 D3DFMT_UNKNOWN,
					 D3DPOOL_DEFAULT,
					 D3DX_DEFAULT,
					 D3DX_DEFAULT,
					 transparentColor,
					 &info,
					 NULL,
					 &texture);

	if (result != D3D_OK) ThrowMyException("Create texture from file failed");
	textureDictionary.emplace(id, texture);
}

// Learn more about jsoncpp: https://github.com/open-source-parsers/jsoncpp
void Textures::AddTexture(TextureType id, LPCSTR jsonPath)
{
	assert(textureDictionary.count(id) == 0);

	std::ifstream jsonFile(jsonPath);
	if (!jsonFile.is_open())
	{
		DebugOut("Can't open json file to add texture: ", jsonPath, "\n");
		ThrowMyException("Can't open json file to add texture");
	}

	Json::Reader reader;
	Json::Value  root;
	if (!reader.parse(jsonFile, root))
	{
		const std::string msg = reader.getFormattedErrorMessages();
		DebugOut("Parse json file failed: ", msg, "\n");
		ThrowMyException(msg.c_str());
	}

	static auto getTextureInfo = [](const Json::Value& root, TextureType id)
	{
		const Json::Value& textures = root["textures"];
		static auto matchTextureIdPred = [&id](const Json::Value& txt) { return txt[0].asUInt() == (UINT)id; };
		auto found = std::find_if(textures.begin(), textures.end(), matchTextureIdPred);
		if (found == textures.end())
		{
			DebugOut("Can't find texture match with id of: ", (UINT)id, "\n");
			ThrowMyException("Can't find any texture match with particular id");
		}
		return *found;
	};

	const Json::Value& textureInfo          = getTextureInfo(root, id);
	LPCSTR             texturePath          = textureInfo[1].asCString();
	const Json::Value& transparentColorJson = textureInfo[2];
	D3DCOLOR transparentColor;
	if (transparentColorJson.isNumeric()) {
		transparentColor = 0;
	} else {
		const UINT r = transparentColorJson[0].asUInt();
		const UINT g = transparentColorJson[1].asUInt();
		const UINT b = transparentColorJson[2].asUInt();
		transparentColor = D3DCOLOR_XRGB(r, g, b);
	}

	AddTexture(id, texturePath, transparentColor);
}

const LPDIRECT3DTEXTURE9 Textures::GetTexture(TextureType id) const
{
	assert(textureDictionary.count(id) == 1);
	return textureDictionary.at(id);
}




