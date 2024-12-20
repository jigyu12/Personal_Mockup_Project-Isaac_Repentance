#include "pch.h" 

void Game::Init(const std::wstring& windowName)
{
	//std::wcin.imbue(std::locale("korean"));
	//std::wcout.imbue(std::locale("korean"));

	Utils::Init();

	GAME_MGR.Init(windowName);
	INPUT_MGR.Init();
	SOUND_MGR.Init();

	SCENE_MGR.Init();

	SOUND_MGR.SetBgmVolume(30.f);
	SOUND_MGR.SetSfxVolume(10.f);
}

void Game::TotalUpdate()
{
	while (GAME_MGR.GetWindow().isOpen())
	{
		GAME_MGR.CalculateTime();

		INPUT_MGR.Clear();

		sf::Event event;
		while (GAME_MGR.GetWindow().pollEvent(event))
		{
			INPUT_MGR.UpdateEvent(event);
		}

		if (INPUT_MGR.GetKeyDown(sf::Keyboard::F11))
		{
			SwitchDebugMod();
		}

		GAME_MGR.GetWindow().clear();

		Update(GAME_MGR.GetDeltaTime());
		Draw(GAME_MGR.GetWindow());

		GAME_MGR.GetWindow().display();
	}
}

void Game::Update(float deltaTime)
{
	INPUT_MGR.Update(deltaTime);
	SOUND_MGR.Update(deltaTime);

	SCENE_MGR.Update(deltaTime);
	SCENE_MGR.FixedUpdate(deltaTime);
}

void Game::Draw(sf::RenderWindow& window)
{
	SCENE_MGR.Draw(window);
	SCENE_MGR.PostDraw();
}

void Game::Release()
{
	SOUND_MGR.Release();

	SCENE_MGR.Release();
}

void Game::SwitchDebugMod()
{
	Variables::isDrawHitBox = !Variables::isDrawHitBox;
}