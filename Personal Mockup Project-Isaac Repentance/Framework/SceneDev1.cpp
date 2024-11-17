#include "pch.h"
#include "SceneDev1.h"

SceneDev1::SceneDev1()
	: Scene(SceneIds::SceneDev1)
{
}

void SceneDev1::Init()
{
	Scene::Init();
}

void SceneDev1::Enter()
{
	Scene::Enter();
}

void SceneDev1::Update(float deltaTime)
{
	Scene::Update(deltaTime);
}

void SceneDev1::FixedUpdate(float deltaTime)
{
	Scene::FixedUpdate(deltaTime);
}

void SceneDev1::Draw(sf::RenderWindow& window)
{
	Scene::Draw(window);
}

void SceneDev1::PostDraw()
{
	Scene::PostDraw();
}

void SceneDev1::Exit()
{
	Scene::Exit();
}

void SceneDev1::Release()
{
	Scene::Release();
}