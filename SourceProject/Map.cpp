#include "pch.h"

Map::Map(const Json::Value & root) 
{
	LoadResources(root);
}

void Map::LoadResources(const Json::Value& root)
{
	const Json::Value&   tileMap = root["map"];
	const UINT textureId = tileMap["texture-id"].asUInt();
	const UINT columns   = tileMap["columns"   ].asUInt();
	           tileSize  = tileMap["tilesize"  ].asUInt();
	           height    = tileMap["height"    ].asUInt();
	           width     = tileMap["width"     ].asUInt();

	texture = Textures::Get( (TextureId)textureId );
	worldBoundary = { 0.0f, 0.0f, width * tileSize, height * tileSize };
	tiles.reserve(height * width);

	const Json::Value& data = tileMap["data"];
	for (UINT y = 0; y < height; y++)
	for (UINT x = 0; x < width ; x++)
	{
		Tile tile; tile.position = { x * tileSize, y * tileSize };
		const UINT num = data[y * width + x].asUInt();
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
	if (DebugDraw::IsInDeepDebug()) return;

	const auto& cam = Camera::Instance();
	const auto camBbox = cam.GetBBox();

	const auto xs = UINT(max(0         , camBbox.left   / tileSize));
	const auto xe =	UINT(min(width  - 1, camBbox.right  / tileSize));
	const auto ys =	UINT(max(0         , camBbox.top    / tileSize));
	const auto ye = UINT(min(height - 1, camBbox.bottom / tileSize));

	for (UINT y = ys; y <= ye; y++)
	for (UINT x = xs; x <= xe; x++)
	{
		const auto& tile = tiles[y * width + x];

		if (tile.IsInvisible()) continue;
		
		const auto drawablePos = cam.GetPositionInViewPort(tile.position);
		Game::Instance().Draw(drawablePos, texture, tile.portion);
	}
}
