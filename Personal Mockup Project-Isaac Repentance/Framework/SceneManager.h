#pragma once

class Scene;

class SceneManager
{
	DECLARE_SINGLETON(SceneManager);

public:
	void Init();

	void Update(float deltaTime);
	void FixedUpdate(float deltaTime);

	void Draw(sf::RenderWindow& window);
	void PostDraw();

	void Release();

	std::shared_ptr<Scene> GetCurrentScene() const { return scenes[(int)currentSceneId]; }
	SceneIds GetCurrentSceneId() const { return currentSceneId; }
	void ChangeScene(const SceneIds sceneId);

private:
	std::vector<std::shared_ptr<Scene>> scenes;

	SceneIds startSceneId;
	SceneIds currentSceneId;
	SceneIds nextSceneId;
};