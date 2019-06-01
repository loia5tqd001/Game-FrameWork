#include "pch.h"
#include "Map.h"
#include "Camera.h"
#include "GameDev.h"
#include "MyException.h"


Map::Map(const Json::Value & root, std::vector<std::unique_ptr<GameObject>>& objects)
{
	LoadResources(root, objects);
}

void Map::LoadResources(const Json::Value& root, std::vector<std::unique_ptr<GameObject>>& objects)
{
	const Json::Value&   jsonMap = root["map"];
	const UINT columns = jsonMap["columns" ].asUInt();
	          tileSize = jsonMap["tilesize"].asUInt();
	          height   = jsonMap["height"  ].asUInt();
	          width    = jsonMap["width"   ].asUInt();

	tiles.reserve(height * width);

	const Json::Value& data = jsonMap["data"];
	for (UINT i = 0; i < height; i++)
	{
		for (UINT j = 0; j < width; j++)
		{
			const UINT num = data[i * width + j].asUInt();
			Tile tile; tile.position = { float(j * tileSize), float((height - 1 - i) * tileSize), 0.0f };
			if (num != 0)
			{
				tile.portion.left   = (num - 1) % columns;
				tile.portion.top    = (num - 1) / columns;
				tile.portion.right  = tile.portion.left + tileSize;
				tile.portion.bottom = tile.portion.top  + tileSize;
			}
			tiles.emplace_back(tile);
		}
	}
}

void Map::Render() const
{
	static auto& cam = Camera::Instance();
	for (const auto& t : tiles)
	{
		if (t.portion.right == 0) continue;
		if (t.ToRectF().IsIntersect(cam.GetBBox()))
		{
			const auto topLeftOnScreen = t.position - cam.GetPosition();
			GameDev::Instance().Draw(topLeftOnScreen, texture, t.portion);
		}
	}
}
