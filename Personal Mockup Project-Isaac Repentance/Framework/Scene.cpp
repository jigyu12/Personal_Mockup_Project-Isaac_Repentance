#include "pch.h"

Scene::Scene(SceneIds sceneId)
	: sceneId(sceneId)
{
}

void Scene::Init()
{
	ApplyAddGoList();
	ApplyRemoveGoList();

	for (auto& obj : gameObjects)
		obj->Init();
}

void Scene::Enter()
{
	for (auto& obj : gameObjects)
		obj->Enter();
}

void Scene::Update(float deltaTime)
{
	for (auto& obj : gameObjects)
	{
		if (!obj->IsActive())
			continue;

		obj->Update(deltaTime);
	}
}

void Scene::FixedUpdate(float deltaTime)
{
	for (auto& obj : gameObjects)
	{
		if (!obj->IsActive())
			continue;

		obj->FixedUpdate(deltaTime);
	}
}

void Scene::Draw(sf::RenderWindow& window)
{
	std::priority_queue<std::shared_ptr<GameObject>, std::vector<std::shared_ptr<GameObject>>, DrawOrderComparerSprite> drawQueue;
	std::priority_queue<std::shared_ptr<GameObject>, std::vector<std::shared_ptr<GameObject>>, DrawOrderComparerUI> drawUiQueue;

	for (auto& obj : gameObjects)
	{
		if (!obj->IsActive())
			continue;

		if (obj->GetSortingLayers() >= SortingLayers::UI)
			drawUiQueue.push(obj);
		else
			drawQueue.push(obj);
	}


	const sf::View& saveView = window.getView();

	window.setView(worldView);
	while (!drawQueue.empty())
	{
		std::shared_ptr<GameObject> obj = drawQueue.top();
		obj->Draw(window);
		drawQueue.pop();
	}

	window.setView(uiView);
	while (!drawUiQueue.empty())
	{
		std::shared_ptr<GameObject> obj = drawUiQueue.top();
		obj->Draw(window);
		drawUiQueue.pop();
	}

	window.setView(saveView);
}

void Scene::PostDraw()
{
	ApplyAddGoList();
	ApplyRemoveGoList();

	for (auto& obj : gameObjects)
	{
		if (!obj->IsActive())
			continue;

		obj->PostDraw();
	}
}

void Scene::Exit()
{
	ApplyAddGoList();
	ApplyRemoveGoList();

	for (auto& obj : gameObjects)
		obj->Exit();

	RES_TEXTURE_MGR.UnLoadAll();
	RES_FONT_MGR.UnLoadAll();
	RES_SOUNDBUFFER_MGR.UnLoadAll();
	RES_ANICLIP_MGR.UnLoadAll();
}

void Scene::Release()
{
	for (auto& obj : gameObjects)
		obj->Release();

	gameObjects.clear();
}

void Scene::RemoveGo(std::shared_ptr<GameObject> object)
{
	removeGameObjects.push_back(object);
}

std::shared_ptr<std::list<std::shared_ptr<GameObject>>> Scene::FindAllGoByName(const std::wstring& name, const bool containsInactive)
{
	std::shared_ptr<std::list<std::shared_ptr<GameObject>>> allGoList = std::make_shared<std::list<std::shared_ptr<GameObject>>>();
	for (auto& obj : gameObjects)
	{
		if (obj->GetName() == name)
		{
			if (containsInactive)
				allGoList->push_back(obj);
			else
			{
				if (!obj->IsActive())
					continue;

				allGoList->push_back(obj);
			}
		}
	}
	return allGoList;
}

void Scene::ApplyAddGoList()
{
	for (auto& addObj : addGameObjects)
	{
		if (std::find(gameObjects.begin(), gameObjects.end(), addObj) == gameObjects.end())
			gameObjects.push_back(addObj);
	}

	addGameObjects.clear();
}

void Scene::ApplyRemoveGoList()
{
	for (auto& removeObj : removeGameObjects)
		gameObjects.remove(removeObj);

	removeGameObjects.clear();
}