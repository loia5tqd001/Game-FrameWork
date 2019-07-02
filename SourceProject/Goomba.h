#pragma once

class Goomba : public VisibleObject
{
public:
	Goomba(const Vector2& spawnPos, const Vector2& vel);

	RectF GetBBox() const override;
	void SetState(State state) override;

	UINT GetHeight() const;
	void LowDownBody(UINT oldHeight); // recalculate position when lowing down body (height changed)
	
	void Update(float dt, const std::vector<GameObject*>& coObjects) override;
};
