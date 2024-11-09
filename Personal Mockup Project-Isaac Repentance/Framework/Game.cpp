#include "pch.h"

void Game::Init(const std::wstring& windowName)
{
    std::wcin.imbue(std::locale("korean"));
    std::wcout.imbue(std::locale("korean"));

    GAME_MGR.Init(windowName);
}

void Game::TotalUpdate()
{
    while (GAME_MGR.GetWindow().isOpen())
    {
        GAME_MGR.CalculateTime();

        // GET_SINGLETON(InputManager).Clear();

        sf::Event event;
        while (GAME_MGR.GetWindow().pollEvent(event))
        {
            // InputManager�� ��ü ��� (esc ���� �̻��ϸ� updateEvent�� ȣ���ϸ� �� ��)
            if (event.type == sf::Event::KeyPressed)
            {
                if(event.key.code == sf::Keyboard::Escape)
                    GAME_MGR.GetWindow().close();
            }
            // �������
        }

        GAME_MGR.GetWindow().clear();
        
        Update(GAME_MGR.GetDeltaTime());
        Draw(GAME_MGR.GetWindow());

        GAME_MGR.GetWindow().display();
    }
}

void Game::Update(float dt)
{
    
}

void Game::Draw(sf::RenderWindow& window)
{
    
}

void Game::Release()
{
    
}