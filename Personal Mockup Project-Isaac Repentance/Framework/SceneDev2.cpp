#include "pch.h"
#include "SceneDev2.h"

SceneDev2::SceneDev2()
	: Scene(SceneIds::SceneDev2)
{
}

void SceneDev2::Init()
{
	Scene::Init();
}

void SceneDev2::Enter()
{
	Scene::Enter();
}

void SceneDev2::Update(float deltaTime)
{
	Scene::Update(deltaTime);
}

void SceneDev2::FixedUpdate(float deltaTime)
{
	Scene::FixedUpdate(deltaTime);
}

void SceneDev2::Draw(sf::RenderWindow& window)
{
	Scene::Draw(window);
}

void SceneDev2::PostDraw()
{
	Scene::PostDraw();
}

void SceneDev2::Exit()
{
	Scene::Exit();
}

void SceneDev2::Release()
{
	Scene::Release();
}