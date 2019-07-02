#pragma once

class InvisibleObject : public GameObject
{
protected:
	UINT width, height;

public:
	InvisibleObject(Vector2 pos, UINT w, UINT h, Vector2 vel = { 0.0f, 0.0f });

	State GetState() const override;
	RectF GetBBox () const override;

	void Update(float dt, const std::vector<GameObject*>& coObjects = {}) override {}
	void Render() const override;
};
