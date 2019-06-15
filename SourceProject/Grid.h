#pragma once
#include "GameObject.h"

struct Cell
{
	RectF boundingBox;
	std::unordered_set<LPCGAMEOBJECT> staticObjects;
	std::unordered_set<LPCGAMEOBJECT> movingObjects;
	const RectF& GetBoundingBox() const { return boundingBox; }
};

struct Area 
{ 
	UINT xs, xe, ys, ye; 
};

class Grid
{
private:
	UINT cellSize, width, height;
	std::vector<Cell> cells;
	std::vector<std::unique_ptr<GameObject>> objectHolder; // responsible for deleting objects

private:
	Grid(const Grid&) = delete;
	Area CalcCollidableArea(const RectF& bbox) const;
	Area GetVicinityAreaOfViewPort() const;

	auto LoadObjects(const Json::Value& root);
	void LoadResources(const Json::Value& root);
	void RemoveDestroyedObjects();
	void UpdateCells();

public:
	Grid(const Json::Value& root);
	void SpawnObject(std::unique_ptr<GameObject> obj); // add objects to grid (used by spwaner object)
	std::vector<LPCGAMEOBJECT> GetObjectsInViewPort();
	void RenderCells() const;


	template<typename T, typename Pred>
	static void RemoveIf(std::vector<T>& container, Pred remove_condition)
	{
		auto newEnd = std::remove_if(container.begin(), container.end(), remove_condition);
		container.erase(newEnd, container.end());
	}

	template<typename T, typename Pred>
	static void RemoveIf(std::unordered_set<T>& container, Pred remove_condition) 
	{
		for (auto it = container.begin(), end = container.end(); it != end; ) 
		{
			if (remove_condition(*it)) it = container.erase(it);
			else                       it++;
		}
	}
};

