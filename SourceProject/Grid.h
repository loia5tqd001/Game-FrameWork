#pragma once

struct Cell
{
	RectF boundingBox;
	std::unordered_set<GameObject*> staticObjects; 
	std::unordered_set<GameObject*> movingObjects; // objects moving around from cells to cells
	const RectF& GetBBox() const { return boundingBox; }
};

struct Area { UINT xs, xe, ys, ye; };

class Grid 
{
private:
	UINT cellSize, width, height;
	std::vector<Cell> cells;
	std::vector<std::unique_ptr<GameObject>> objectHolder; // responsible for deleting objects, use this to avoid using slow and complicated shared_ptr
	std::vector<GameObject*> curObjectsInViewPort; // being recalculated every frame 

private:
	Grid(const Grid&) = delete;
	Area CalcCollidableArea(const RectF& bbox) const;
	Area GetVicinityAreaOfViewPort() const;

	auto LoadObjects(const Json::Value& grid);
	void LoadResources(const Json::Value& root);
	void RemoveDestroyedObjects();
	void RecalculateObjectsInViewPort();

public:
	Grid(const Json::Value& root);

	void UpdateCells(); // NOTE: This grid will not update objects being too far away from viewport
	void RenderCells() const;

	void SpawnObject(std::unique_ptr<GameObject> obj); // add objects to grid (used by spwaner object)
	inline const auto& GetObjectsInViewPort() const { return curObjectsInViewPort; }

	std::vector<GameObject*> GetObjectsNear(GameObject* objectInInterest) const;

};

