#pragma once
#include "GameObject.h"
#include "Textures.h"

struct Tile
{
	D3DXVECTOR3 position;  // in world map
	RECT portion = { 0, 0, 0, 0};  // of texture
	RectF ToRectF() const
	{
		const float left   = position.x;
		const float right  = left + (portion.right - portion.left);
		const float bottom = position.y;
		const float top    = bottom + (portion.bottom - portion.top);
		return { left, top, right, bottom };
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