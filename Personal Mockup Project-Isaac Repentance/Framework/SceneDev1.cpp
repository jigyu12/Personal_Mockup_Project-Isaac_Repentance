#include "pch.h"
#include "SceneDev1.h"

SceneDev1::SceneDev1()
	: Scene(SceneIds::SceneDev1)
{
}

void SceneDev1::Init()
{
	{
		mainTitle = std::make_shared<MainTitle>();

		AddGo(mainTitle);
	}
    {
        selectMode = std::make_shared<SelectMode>();

        AddGo(selectMode);
    }
	Scene::Init();
}

void SceneDev1::Enter()
{
	GAME_MGR.GetWindow().setMouseCursorVisible(false);

	sf::Vector2f windowSize = { (float)GAME_MGR.GetWindowWidth(), (float)GAME_MGR.GetWindowHeight() };

	worldView.setSize(windowSize);
	worldView.setCenter(0.f, 0.f);

	uiView.setSize(windowSize);
	uiView.setCenter(windowSize.x * 0.5f, windowSize.y * 0.5f);

    SOUND_MGR.PlayBgm(L"Music/Main Menu/title screen intro.ogg");
     
	Scene::Enter();

    SOUND_MGR.SetSfxVolume(10.f);
}

void SceneDev1::Update(float deltaTime)
{
    bgmintro += deltaTime;
    if (bgmintro >= bgmintroDelay)
    {
        SOUND_MGR.PlayBgm(L"Music/Main Menu/title screen.ogg");
    }

    if (INPUT_MGR.GetKeyDown(sf::Keyboard::Escape))
    {
        if (worldView.getCenter().y >= -540.f && worldView.getCenter().y <= 540.f)
        {
            GAME_MGR.GetWindow().close();
        }
        else if (worldView.getCenter().y == 1080.f)
        {
            isUp = true;
            moveAccelY = 3000.f;
            isFlyMove = true;
            flySpeed = -flySpeed;
        }
    }
    else if (INPUT_MGR.GetKeyDown(sf::Keyboard::Enter))
    {
        if (worldView.getCenter().y == 0.f)
        {
            isDown = true;
            moveAccelY = 3000.f;
            isFlyMove = true;
            flySpeed = -flySpeed;
        }
        else if (worldView.getCenter().y > 540.f && worldView.getCenter().y <= 1620.f)
        {
            SCENE_MGR.ChangeScene(SceneIds::SceneDev2);
        }
    }

    if (isDown)
    {
        float targetY = 1080.f;
        float distanceToTarget = targetY - worldView.getCenter().y;

        if (distanceToTarget > 5.f)
        {
            moveAccelY = std::max(100.f, moveAccelY * 0.984f);
        }
        else
        {
            moveAccelY = std::max(100.f, moveAccelY * 0.4f);
        }

        moveY += moveAccelY * deltaTime;

        if (moveY >= targetY - 1.f)
        {
            isDown = false;
            moveY = targetY;
            moveAccelY = 1000.f;
        }
    }
    else if (isUp)
    {
        float targetY = 0.f;
        float distanceToTarget = worldView.getCenter().y - targetY;

        if (distanceToTarget > 5.f)
        {
            moveAccelY = std::max(100.f, moveAccelY * 0.984f);
        }
        else
        {
            moveAccelY = std::max(100.f, moveAccelY * 0.4f);
        }

        moveY -= moveAccelY * deltaTime;

        if (moveY <= targetY + 1.f)
        {
            isUp = false;
            moveY = targetY;
            moveAccelY = 1000.f;
        }
    }

    if (isFlyMove)
    {
        flyMove += deltaTime;
        if (flyMove < flyMoveDelay)
        {
            mainTitle->GetSpriteFlyPtr()->setPosition({ mainTitle->GetSpriteFlyPtr()->getPosition().x + flySpeed * deltaTime, mainTitle->GetSpriteFlyPtr()->getPosition().y });
        }
        else
        {
            isFlyMove = false;
            flyMove = 0.f;
        }
    }

    worldView.setCenter({ 0.f, moveY });

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