#pragma once

class Scene
{
public:
	Scene(SceneIds sceneId);
	virtual ~Scene() = default;

	virtual void Init();
	virtual void Enter();

	virtual void Update(float deltaTime);
	virtual void FixedUpdate(float deltaTime);

	virtual void Draw(sf::RenderWindow& window);
	virtual void PostDraw();

	virtual void Exit();
	virtual void Release();

	template<typename T>
	std::shared_ptr<T> AddGo(std::shared_ptr<T> object)
	{
		addGameObjects.push_back(object);

		return object;
	}
	void RemoveGo(std::shared_ptr<GameObject> object);
	std::shared_ptr<std::list<std::shared_ptr<GameObject>>> FindAllGoByName(const std::wstring& name, const bool containsInactive = false);

	void ApplyAddGoList();
	void ApplyRemoveGoList();

	SceneIds GetSceneId() const { return sceneId; }

protected:
	const SceneIds sceneId;

	std::list<std::shared_ptr<GameObject>> gameObjects;
	std::list<std::shared_ptr<GameObject>> addGameObjects;
	std::list<std::shared_ptr<GameObject>> removeGameObjects;

	sf::View worldView;
	sf::View uiView;
};