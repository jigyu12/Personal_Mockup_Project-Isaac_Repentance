#include "pch.h"

void Game::Init(const std::wstring& windowName)
{
    //std::wcin.imbue(std::locale("korean"));
    //std::wcout.imbue(std::locale("korean"));
    
    GAME_MGR.Init(windowName);
    INPUT_MGR.Init();
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
        
        // ���߿� ���ǿ� �°� ���� ��� (���� �ӽ� �ڵ�)
        if(INPUT_MGR.GetKeyDown(sf::Keyboard::Space))
            GAME_MGR.GetWindow().close();
        // ���߿� ���ǿ� �°� ���� ��� (���� �ӽ� �ڵ�)

        if (INPUT_MGR.GetKeyDown(sf::Keyboard::F12))
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
}

void Game::Draw(sf::RenderWindow& window)
{
    
}

void Game::Release()
{

}

void Game::SwitchDebugMod()
{
    Variables::isDrawHitBox = !Variables::isDrawHitBox;
}