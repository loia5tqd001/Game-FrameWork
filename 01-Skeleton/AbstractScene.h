#pragma once

class AbstractScene
{
public:
	AbstractScene() noexcept = default;
	AbstractScene(const AbstractScene&) = delete;
	virtual ~AbstractScene() = default;

	Json::Value GetRootJson() const;

	virtual void LoadResources () = 0;
	virtual void Update(float dt) = 0;
	virtual void Draw  (        ) = 0;

	virtual void OnKeyDown(BYTE keyCode) {}
	virtual void OnKeyUp  (BYTE keyCode) {}
};
