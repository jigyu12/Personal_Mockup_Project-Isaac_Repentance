#include "pch.h"
#include "SceneDev1.h"
#include "SceneDev2.h"

/// <summary>
/// In this function, you can manage the order of startScene and all other scenes.
/// Make sure that the order of all scenes matches the enum: SceneIds.
/// </summary>
void SceneManager::Init()
{
	startSceneId = SceneIds::SceneDev2;
	nextSceneId = SceneIds::None;

	scenes.push_back(std::make_shared<SceneDev1>());
	scenes.push_back(std::make_shared<SceneDev2>());


	for (auto& scene : scenes)
		scene->Init();

	currentSceneId = startSceneId;
	scenes[(int)currentSceneId]->Enter();
}

void SceneManager::Update(float deltaTime)
{
	scenes[(int)currentSceneId]->Update(deltaTime);
}

void SceneManager::FixedUpdate(float deltaTime)
{
	scenes[(int)currentSceneId]->FixedUpdate(deltaTime);
}

void SceneManager::Draw(sf::RenderWindow& window)
{
	scenes[(int)currentSceneId]->Draw(window);
}

void SceneManager::PostDraw()
{
	scenes[(int)currentSceneId]->PostDraw();
	if (nextSceneId != SceneIds::None)
	{
		scenes[(int)currentSceneId]->Exit();
		currentSceneId = nextSceneId;
		nextSceneId = SceneIds::None;
		scenes[(int)currentSceneId]->Enter();
	}
}

void SceneManager::Release()
{
	for (auto& scene : scenes)
	{
		if (currentSceneId == scene->GetSceneId())
			scene->Exit();

		scene->Release();
	}
	scenes.clear();
}

void SceneManager::ChangeScene(const SceneIds sceneId)
{
	if (sceneId == SceneIds::None)
	{
		std::wcerr << L"The sceneId to change cannot be None." << std::endl;

		return;
	}
	else
	{
		nextSceneId = sceneId;
	}
}