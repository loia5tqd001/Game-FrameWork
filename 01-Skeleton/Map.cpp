#include "pch.h"
#include "Map.h"
#include "Camera.h"
#include "GameDev.h"
#include "MyException.h"
#include "Textures.h"


void Map::LoadResources(LPCSTR jsonPath, std::shared_ptr<GameObject>& objects)
{
	std::ifstream jsonFile(jsonPath);
	if (!jsonFile.is_open())
	{
		DebugOut("Can't open json file to load map: ", jsonPath, "\n");
		ThrowMyException("Can't open json file to load map");
	}

	Json::Reader reader;
	Json::Value  root;
	if (!reader.parse(jsonFile, root))
	{
		LPCSTR msg = reader.getFormattedErrorMessages().c_str();
		DebugOut("Parse json file failed: ", msg, "\n");
		ThrowMyException(msg);
	}

	const UINT columns = root["columns" ].asUInt();
	const UINT rows    = root["rows"    ].asUInt();
	          tileSize = root["tilesize"].asUInt();
	          nRows    = root["height"  ].asUInt();
	          nCols    = root["width"   ].asUInt();

	const Json::Value data = root["data"];
	tileSets.reserve(nRows * nCols);
	for (UINT i = 0; i < nRows; i++)
	{
		for (UINT j = 0; j < nCols; j++)
		{
			const UINT tileNumber = data[i * nCols + j].asUInt();
			static RECT tileRect;
			tileRect.left   = i * tileSize;
			tileRect.top    = j * tileSize;
			tileRect.right  = tileRect.left + tileSize;
			tileRect.bottom = tileRect.top  + tileSize;
			tileSets.emplace_back(std::move(tileRect));
		}
	}

}

void Map::Render() const
{
	const RectF camRect = Camera::Instance().GetBBox();

	for (UINT i = 0; i < nRows; i++)
	{
		for (UINT j = 0; j < nCols; j++)
		{
			static D3DXVECTOR3 tilePos;
			tilePos.x = float(j * tileSize);
			tilePos.y = float(i * tileSize);
			tilePos -= D3DXVECTOR3(camRect.left, camRect.top, 0.0f);
			GameDev::Instance().Draw(tilePos, Textures::Get(TextureType::Map), tileSets[i * nCols + j]);
		}
	}
}
