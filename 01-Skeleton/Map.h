#pragma once
#include "GameObject.h"
#include "Textures.h"

struct Tile
{
	Point position;  // on world map
	Rect  portion ;  // in texture
	RectF GetBBox() const
	{
		return { position.x, position.y, portion.GetWidth(), portion.GetHeight() };
	}
	bool IsInvisible() const
	{
		return portion.IsNone();
	}
};

class Map
{
private:
	LPDIRECT3DTEXTURE9 texture = Textures::Get(TextureType::Map);
	UINT height, width, tileSize;
	std::vector<Tile> tiles;

public:
	Map(const Map&) = delete;
	Map(const Json::Value& root, std::vector<std::unique_ptr<GameObject>>& objects);

	void LoadResources(const Json::Value& root, std::vector<std::unique_ptr<GameObject>>& objects);
	void Render() const;

	UINT GetMapWidth () const { return width  * tileSize; }
	UINT GetMapHeight() const { return height * tileSize; }
	UINT GetTileSize () const { return          tileSize; }
};