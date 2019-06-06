#include "pch.h"
#include "Map.h"
#include "Camera.h"
#include "GameDev.h"


Map::Map(const Json::Value & root, std::vector<std::unique_ptr<GameObject>>& objects)
{
	LoadResources(root, objects);
}

void Map::LoadResources(const Json::Value& root, std::vector<std::unique_ptr<GameObject>>& objects)
{
	const Json::Value&   tileMap = root["map"];
	const UINT columns = tileMap["columns" ].asUInt();
	          tileSize = tileMap["tilesize"].asUInt();
	          height   = tileMap["height"  ].asUInt();
	          width    = tileMap["width"   ].asUInt();

	tiles.reserve(height * width);

	const Json::Value& data = tileMap["data"];
	for (UINT i = 0; i < height; i++)
	for (UINT j = 0; j < width ; j++)
	{
		Tile tile; tile.position = { j * tileSize, i * tileSize, 0.0f };
		const UINT num = data[i * width + j].asUInt();
		if (num != 0)
		{
			tile.portion.left   = ((num - 1) % columns) * tileSize;
			tile.portion.top    = ((num - 1) / columns) * tileSize;
			tile.portion.right  = tile.portion.left + tileSize;
			tile.portion.bottom = tile.portion.top  + tileSize;
		}
		tiles.emplace_back(tile);
	}
}

void Map::Render() const
{
	const auto camRect = Camera::Instance().GetBBox();

	for (const auto& tile : tiles)
	{
		if (tile.IsInvisible()) continue;

		const auto tileBBox = tile.GetBBox();
		if (camRect.IsIntersect(tileBBox))
		{
			Point drawablePos = { tileBBox.left - camRect.left, camRect.top - tileBBox.top, 0.0f };
			GameDev::Instance().Draw(drawablePos, texture, tile.portion);
		}
	}
}
