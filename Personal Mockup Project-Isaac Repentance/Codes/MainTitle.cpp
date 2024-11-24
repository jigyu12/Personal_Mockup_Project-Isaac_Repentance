#include "../Framework/pch.h"
#include "MainTitle.h"

MainTitle::MainTitle(const std::wstring& name)
	: SpriteGameObject(name), spriteLogoShadowPtr(std::make_shared<sf::Sprite>()), spriteLogoPtr(std::make_shared<sf::Sprite>()), spriteFlyPtr(std::make_shared<sf::Sprite>()), spriteStartPtr(std::make_shared<sf::Sprite>()), spriteLogoTexturePtr(std::make_shared<sf::Texture>()), spriteFlyTexturePtr(std::make_shared<sf::Texture>()), spriteStartTexturePtr(std::make_shared<sf::Texture>()), spriteLogoShadowTexturePtr(std::make_shared<sf::Texture>())
{
}

void MainTitle::Init()
{
	titleTextureCsvPath = L"Csv/mainTitle_texture_path.csv";
}

void MainTitle::Enter()
{
	SetSortingLayers(SortingLayers::Background);
	SetSortingOrderBack(0);

    if (auto csvTitlePathMap = FILE_MGR.LoadByCsv(titleTextureCsvPath))
    {
        SpriteGameObject::SetSpriteTexture((*csvTitlePathMap)[L"타이틀"][0]);

        std::string s_path = Utils::converter.to_bytes((*csvTitlePathMap)[L"타이틀"][0]);
        spriteStartTexturePtr->loadFromFile(s_path);
        spriteStartPtr->setTexture(*spriteStartTexturePtr);

        s_path = Utils::converter.to_bytes((*csvTitlePathMap)[L"타이틀"][1]);
        spriteLogoTexturePtr->loadFromFile(s_path);
        spriteLogoPtr->setTexture(*spriteLogoTexturePtr);

        s_path = Utils::converter.to_bytes((*csvTitlePathMap)[L"타이틀"][1]);
        spriteLogoShadowTexturePtr->loadFromFile(s_path);
        spriteLogoShadowPtr->setTexture(*spriteLogoShadowTexturePtr);

        s_path = Utils::converter.to_bytes((*csvTitlePathMap)[L"타이틀"][2]);
        spriteFlyTexturePtr->loadFromFile(s_path);
        spriteFlyPtr->setTexture(*spriteFlyTexturePtr);
    }
    else
        std::wcerr << L"csvRoomPathMap was nullptr" << std::endl;

    spritePtr->setTextureRect({ 0, 0, 480, 270 });
    SpriteGameObject::SetOrigin(Origins::MC);
    SpriteGameObject::SetPosition({ 0.f, 0.f });
    SpriteGameObject::SetScale({ ((float)GAME_MGR.GetWindowWidth() / SpriteGameObject::GetGlobalBounds().width), ((float)GAME_MGR.GetWindowHeight() / SpriteGameObject::GetGlobalBounds().height) });

    spriteStartPtr->setTextureRect({ 0, 405, 160, 135 });
    Utils::SetOrigin(*spriteStartPtr, Origins::MC);
    spriteStartPtr->setPosition({ 0.f, 150.f });
    spriteStartPtr->setScale({ ((float)GAME_MGR.GetWindowWidth() / spriteStartPtr->getGlobalBounds().width) / 3, ((float)GAME_MGR.GetWindowHeight() / spriteStartPtr->getGlobalBounds().height) / 2 });

    spriteLogoPtr->setTextureRect({ 0, 0, 480, 160 });
    Utils::SetOrigin(*spriteLogoPtr, Origins::MC);
    spriteLogoPtr->setPosition({ 0.f, -130.f });
    spriteLogoPtr->setScale({ ((float)GAME_MGR.GetWindowWidth() / spriteLogoPtr->getGlobalBounds().width), ((float)GAME_MGR.GetWindowHeight() / spriteLogoPtr->getGlobalBounds().height) / 1.5f});

    spriteLogoShadowPtr->setTextureRect({ 0, 160, 480, 160 });
    Utils::SetOrigin(*spriteLogoShadowPtr, Origins::MC);
    spriteLogoShadowPtr->setPosition({ 0.f, -280.f });
    spriteLogoShadowPtr->setScale({ ((float)GAME_MGR.GetWindowWidth() / spriteLogoShadowPtr->getGlobalBounds().width), ((float)GAME_MGR.GetWindowHeight() / spriteLogoShadowPtr->getGlobalBounds().height) / 1.5f });

    spriteFlyPtr->setTextureRect({ 330, 370, 105, 85 });
    Utils::SetOrigin(*spriteFlyPtr, Origins::MC);
    spriteFlyPtr->setPosition({  600.f, 100.f });
    spriteFlyPtr->setScale({ ((float)GAME_MGR.GetWindowWidth() / spriteFlyPtr->getGlobalBounds().width) / 4, ((float)GAME_MGR.GetWindowHeight() / spriteFlyPtr->getGlobalBounds().height) / 3.f });
}

void MainTitle::Update(float deltaTime)
{
    switchStart += deltaTime;
    if (switchStart >= switchStartDelay && spriteStartPtr->getTextureRect().left == 0)
    {
        switchStart = 0.f;
        spriteStartPtr->setTextureRect({160, 405, 160, 135});
    }
    else if (switchStart >= switchStartDelay && spriteStartPtr->getTextureRect().left == 160)
    {
        switchStart = 0.f;
        spriteStartPtr->setTextureRect({ 0, 405, 160, 135 });
    }

    udLogo += deltaTime;
    upTime += deltaTime;
    if (upTime >= 0.25f)
    {
        upTime = 0.f;
        spriteLogoPtr->setPosition({ spriteLogoPtr->getPosition().x, spriteLogoPtr->getPosition().y + logoSpeed * deltaTime * 3});
    }
    if (udLogo >= udLogoDelay && spriteLogoPtr->getPosition().y >= -130.f)
    {
        udLogo = 0.f;
        logoSpeed = -logoSpeed;
    }
    else if (udLogo >= udLogoDelay && spriteLogoPtr->getPosition().y <= -30.f)
    {
        udLogo = 0.f;
        logoSpeed = -logoSpeed;
    }

    switchFlyStart += deltaTime;
    if (switchFlyStart >= switchFlyStartDelay && spriteFlyPtr->getTextureRect().top == 455)
    {
        switchFlyStart = 0.f;
        spriteFlyPtr->setPosition({ spriteFlyPtr->getPosition().x, 100.f });
        spriteFlyPtr->setTextureRect({ 330, 370, 105, 85 });
    }
    else if (switchFlyStart >= switchFlyStartDelay && spriteFlyPtr->getTextureRect().top == 370)
    {
        switchFlyStart = 0.f;
        spriteFlyPtr->setPosition({ spriteFlyPtr->getPosition().x, spriteFlyPtr->getPosition().y + 22.f });
        spriteFlyPtr->setTextureRect({ 330, 455, 105, 85 });
    }
}

void MainTitle::FixedUpdate(float deltaTime)
{
}

void MainTitle::Draw(sf::RenderWindow& window)
{
    window.draw(*spritePtr);
    window.draw(*spriteStartPtr);
    window.draw(*spriteLogoShadowPtr);
    window.draw(*spriteLogoPtr);
    window.draw(*spriteFlyPtr);
}

void MainTitle::PostDraw()
{
}

void MainTitle::Exit()
{
}

void MainTitle::Release()
{
}
