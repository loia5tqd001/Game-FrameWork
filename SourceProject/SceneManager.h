#pragma once

class SceneManager
{
private:
	std::unique_ptr<AbstractScene> curScene;
	Settings& settingScene = Settings::Instance();

public:
	void ToggleMuteMode() const;
	void ToggleSettingScene() const;

	void LoadResources();
	void SetScene(Scene scene);
	void Update(float dt);
	void Draw();

	void OnKeyDown(BYTE keyCode);
	void OnKeyUp(BYTE keyCode);

private:
	SceneManager() = default;
	SceneManager(const SceneManager&) = delete;

public:
	static SceneManager& Instance();
};

