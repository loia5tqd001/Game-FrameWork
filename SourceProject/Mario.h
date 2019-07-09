#pragma once

class Mario : public VisibleObject
{
public:
	static constexpr float WALKING_SPEED      =  100.0f;
	static constexpr float JUMP_SPEED         =  400.0f;
	static constexpr float GRAVITY            = 1000.0f;
	static constexpr float JUMP_DEFLECT_SPEED =   50.0f;

private:
	bool _isJumping = true;
	void ProcessInput();
	void HandleNoCollisions(float dt);
	void HandleCollisions(float dt, const std::vector<GameObject*>& coObjects);

	void OnFlashing(std::optional<bool> setFlashing = {});

public:
	Mario(const Vector2 & spawnPos);

	RectF GetBBox() const override;

	void OnKeyDown(BYTE keyCode);
	void SetState(State state) override;

	void Update(float dt, const std::vector<GameObject*>& coObjects) override;
	void Render() const override;
};

