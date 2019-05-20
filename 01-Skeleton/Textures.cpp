#include "MyException.h"
#include "Textures.h"
#include "GameDev.h"


void Textures::AddTexture(TextureType id, LPCSTR filePath, D3DCOLOR transparentColor)
{
	D3DXIMAGE_INFO info;
	if (D3DXGetImageInfoFromFile(filePath, &info) != D3D_OK)
	{
		DebugOut("[ERROR] Get image info from file failed: ", filePath, "\n");
		ThrowMyException("Get image info from file failed");
	}

	LPDIRECT3DTEXTURE9 texture;
	HRESULT result = D3DXCreateTextureFromFileEx(
					 GameDev::Instance().GetDirect3DDevice(),
					 filePath,							
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

CONST LPDIRECT3DTEXTURE9 Textures::GetTexture(TextureType id) const
{
	assert(textureDictionary.count(id) == 1);
	return textureDictionary.at(id);
}




