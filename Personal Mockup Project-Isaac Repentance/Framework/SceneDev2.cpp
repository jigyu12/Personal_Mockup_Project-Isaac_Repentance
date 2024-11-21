#include "pch.h"
#include "SceneDev2.h"

SceneDev2::SceneDev2()
	: Scene(SceneIds::SceneDev2)
{
}

void SceneDev2::Init()
{
	{
		std::shared_ptr<Room> basicRoom = std::make_shared<Room>(L"basicRoom");

		rooms.push_back(AddGo(basicRoom));
	}
	{
		std::shared_ptr<Player> player = std::make_shared<Player>();

		AddGo(player);
	}
	Scene::Init();
}

void SceneDev2::Enter()
{
	GAME_MGR.GetWindow().setMouseCursorVisible(true);

	sf::Vector2f windowSize = { (float)GAME_MGR.GetWindowWidth(), (float)GAME_MGR.GetWindowHeight() };

	worldView.setSize(windowSize);
	worldView.setCenter(0.f, 0.f);

	uiView.setSize(windowSize);
	uiView.setCenter(windowSize.x * 0.5f, windowSize.y * 0.5f);

	Scene::Enter();

	rooms[0]->SetIsDrawspriteControl(true);
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