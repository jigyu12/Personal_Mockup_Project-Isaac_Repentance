#include "../Framework/pch.h"
#include "SelectMode.h"

SelectMode::SelectMode(const std::wstring& name)
	: SpriteGameObject(name), spriteNewPtr(std::make_shared<sf::Sprite>()), spriteMenuPtr(std::make_shared<sf::Sprite>()), spriteNewTexturePtr(std::make_shared<sf::Texture>()), spriteMenuTexturePtr(std::make_shared<sf::Texture>())
{
}

void SelectMode::Init()
{
	menuTextureCsvPath = L"Csv/selectMode_texture_path.csv";
}

void SelectMode::Enter()
{
	SetSortingLayers(SortingLayers::Background);
	SetSortingOrderBack(0);

    if (auto csvMenuPathMap = FILE_MGR.LoadByCsv(menuTextureCsvPath))
    {
        SpriteGameObject::SetSpriteTexture((*csvMenuPathMap)[L"모드 선택"][0]);

        std::string s_path = Utils::converter.to_bytes((*csvMenuPathMap)[L"모드 선택"][1]);
        spriteNewTexturePtr->loadFromFile(s_path);
        spriteNewPtr->setTexture(*spriteNewTexturePtr);

        s_path = Utils::converter.to_bytes((*csvMenuPathMap)[L"모드 선택"][1]);
        spriteMenuTexturePtr->loadFromFile(s_path);
        spriteMenuPtr->setTexture(*spriteMenuTexturePtr);
    }
    else
        std::wcerr << L"csvRoomPathMap was nullptr" << std::endl;

    spritePtr->setTextureRect({ 0, 0, 480, 270 });
    SpriteGameObject::SetOrigin(Origins::MC);
    SpriteGameObject::SetPosition({ 0.f, 1080.f });
    SpriteGameObject::SetScale({ ((float)GAME_MGR.GetWindowWidth() / SpriteGameObject::GetGlobalBounds().width), ((float)GAME_MGR.GetWindowHeight() / SpriteGameObject::GetGlobalBounds().height) });

    spriteNewPtr->setTextureRect({ 0, 0, 480, 270 });
    Utils::SetOrigin(*spriteNewPtr, Origins::MC);
    spriteNewPtr->setPosition({ 0.f, 1080.f });
    spriteNewPtr->setScale({ ((float)GAME_MGR.GetWindowWidth() / spriteNewPtr->getGlobalBounds().width), ((float)GAME_MGR.GetWindowHeight() / spriteNewPtr->getGlobalBounds().height)});

    spriteMenuPtr->setTextureRect({ 0, 275, 160, 55 });
    Utils::SetOrigin(*spriteMenuPtr, Origins::MC);
    spriteMenuPtr->setPosition({ 0.f, 780.f });
    spriteMenuPtr->setScale({ ((float)GAME_MGR.GetWindowWidth() / spriteMenuPtr->getGlobalBounds().width) / 3.f, ((float)GAME_MGR.GetWindowHeight() / spriteMenuPtr->getGlobalBounds().height) / 4.f });
}

void SelectMode::Update(float deltaTime)
{
}

void SelectMode::FixedUpdate(float deltaTime)
{
}

void SelectMode::Draw(sf::RenderWindow& window)
{
    window.draw(*spritePtr);
    window.draw(*spriteNewPtr);
    window.draw(*spriteMenuPtr);
}

void SelectMode::PostDraw()
{
}

void SelectMode::Exit()
{
}

void SelectMode::Release()
{
}
