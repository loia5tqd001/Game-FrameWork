#pragma once
#include "GameObject.h"

class Map
{
private:
	LPDIRECT3DTEXTURE9 texture;
	UINT nRows, nCols, tileSize;
	std::unique_ptr<RECT[]> tiles;

public:
	Map(const Map&) = delete;
	void LoadResources(LPCSTR jsonPath, std::shared_ptr<GameObject>& objects);
	void Render() const;

	UINT GetMapWidth () const { return nCols * tileSize; }
	UINT GetMapHeight() const { return nRows * tileSize; }
	UINT GetTileSize () const { return         tileSize; }
};