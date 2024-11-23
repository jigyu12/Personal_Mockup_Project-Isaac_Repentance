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
	{
		std::shared_ptr<Fly> fly1 = std::make_shared<Fly>();
		fly1->SetPosition({ -300.f, -300.f });

		AddGo(fly1);

		std::shared_ptr<Fly> fly2 = std::make_shared<Fly>();
		fly2->SetPosition({ 300.f, -300.f });

		AddGo(fly2);

		std::shared_ptr<Fly> fly3 = std::make_shared<Fly>();
		fly3->SetPosition({ -300.f, 300.f });

		AddGo(fly3);

		std::shared_ptr<Fly> fly4 = std::make_shared<Fly>();
		fly4->SetPosition({ 300.f, 300.f });

		AddGo(fly4);
	}
	Scene::Init();
}

void SceneDev2::Enter()
{
	GAME_MGR.GetWindow().setMouseCursorVisible(false);

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