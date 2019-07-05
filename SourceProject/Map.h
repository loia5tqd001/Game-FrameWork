#pragma once

struct Tile
{
	Vector2 position;  // on world map
	Rect  portion ;  // in texture
	RectF GetBBox() const { return { position.x, position.y, portion.GetWidth(), portion.GetHeight() }; }
	bool IsInvisible() const { return portion.IsNone(); }
};

class Map
{
private:
	LPDIRECT3DTEXTURE9 texture;
	UINT height, width, tileSize;
	std::vector<Tile> tiles;

public:
	Map(const Map&) = delete;
	Map(const Json::Value& root);

	void LoadResources(const Json::Value& root);
	void Render() const;

	inline RectF GetWorldBoundary() const { return { 0.0f, 0.0f, GetMapWidth(), GetMapHeight() }; }
	inline UINT  GetMapWidth     () const { return width  * tileSize; }
	inline UINT  GetMapHeight    () const { return height * tileSize; }
	inline UINT  GetTileSize     () const { return          tileSize; }
};