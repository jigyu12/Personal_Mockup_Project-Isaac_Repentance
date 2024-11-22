#include "../Framework/pch.h"
#include "Room.h"

Room::Room(const std::wstring& name)
    : SpriteGameObject(name), roomTextureCsvPath(L"Invaild Path"), sprite2Ptr(std::make_shared<sf::Sprite>()), sprite3Ptr(std::make_shared<sf::Sprite>()), sprite4Ptr(std::make_shared<sf::Sprite>()), spriteControlTexturePtr(std::make_shared<sf::Texture>()), spriteControlPtr(std::make_shared<sf::Sprite>()), movableBoundRect({0.f,0.f,0.f,0.f}), isDrawspriteControl(false)
{
}

void Room::Init()
{
    roomTextureCsvPath = L"Csv/room_texture_path.csv";
}

void Room::Enter()
{
    SetSortingLayers(SortingLayers::Background);
    SetSortingOrderBack(0);

    isDrawspriteControl = false;

    if (auto csvRoomPathMap = FILE_MGR.LoadByCsv(roomTextureCsvPath))
    {
        std::string s_path = Utils::converter.to_bytes((*csvRoomPathMap)[L"1類"][0]);
        spriteControlTexturePtr->loadFromFile(s_path);
        spriteControlPtr->setTexture(*spriteControlTexturePtr);

        SpriteGameObject::SetSpriteTexture((*csvRoomPathMap)[L"1類"][1]);
    }
    else
        std::wcerr << L"csvRoomPathMap was nullptr" << std::endl;
    
    spriteControlPtr->setTextureRect({ 0, 0, 163, 90 });
    Utils::SetOrigin(*spriteControlPtr, Origins::MC);
    spriteControlPtr->setPosition({0.f, 0.f});
    spriteControlPtr->setScale({ ((float)GAME_MGR.GetWindowWidth() / spriteControlPtr->getGlobalBounds().width) / 3, ((float)GAME_MGR.GetWindowHeight() / spriteControlPtr->getGlobalBounds().height) / 3});

    spritePtr->setTextureRect({0, 0, 234, 156});
    SpriteGameObject::SetOrigin(Origins::BR);
    SpriteGameObject::SetPosition({ 0.f, 0.f });
    SpriteGameObject::SetScale({ ((float)GAME_MGR.GetWindowWidth() / SpriteGameObject::GetGlobalBounds().width) / 2, ((float)GAME_MGR.GetWindowHeight() / SpriteGameObject::GetGlobalBounds().height) / 2 });

    sprite2Ptr->setTexture(*spritePtr->getTexture());
    sprite2Ptr->setTextureRect({ 0, 0, 234, 156 });
    Utils::SetOrigin(*sprite2Ptr, Origins::BR);
    sprite2Ptr->setPosition({ 0.f, 0.f });
    sprite2Ptr->setScale({ -((float)GAME_MGR.GetWindowWidth() / sprite2Ptr->getGlobalBounds().width) / 2, ((float)GAME_MGR.GetWindowHeight() / sprite2Ptr->getGlobalBounds().height) / 2});

    sprite3Ptr->setTexture(*spritePtr->getTexture());
    sprite3Ptr->setTextureRect({ 0, 0, 234, 156 });
    Utils::SetOrigin(*sprite3Ptr, Origins::BR);
    sprite3Ptr->setPosition({ 0.f, 0.f });
    sprite3Ptr->setScale({ -((float)GAME_MGR.GetWindowWidth() / sprite3Ptr->getGlobalBounds().width) / 2, -((float)GAME_MGR.GetWindowHeight() / sprite3Ptr->getGlobalBounds().height) / 2 });

    sprite4Ptr->setTexture(*spritePtr->getTexture());
    sprite4Ptr->setTextureRect({ 0, 0, 234, 156 });
    Utils::SetOrigin(*sprite4Ptr, Origins::BR);
    sprite4Ptr->setPosition({ 0.f, 0.f });
    sprite4Ptr->setScale({ ((float)GAME_MGR.GetWindowWidth() / sprite4Ptr->getGlobalBounds().width) / 2, -((float)GAME_MGR.GetWindowHeight() / sprite4Ptr->getGlobalBounds().height) / 2 });

    movableBoundRect = { (-(float)GAME_MGR.GetWindowWidth() / 2) * (7.f / 9.f) + spritePtr->getPosition().x , (-(float)GAME_MGR.GetWindowHeight() / 2) * (2.f / 3.f) + spritePtr->getPosition().y , (float)GAME_MGR.GetWindowWidth() * (7.f / 9.f), (float)GAME_MGR.GetWindowHeight() * (2.f / 3.f)};
}

void Room::Update(float deltaTime)
{
}

void Room::FixedUpdate(float deltaTime)
{
    auto playerList = SCENE_MGR.GetCurrentScene()->FindAllGoByName(L"Player");
    auto player = std::dynamic_pointer_cast<Player>(playerList->front());
    auto pHitBoxrect = std::dynamic_pointer_cast<HitBoxCircle>(player->GetHitBox())->GetHitBoxGlobalRect();
    if (pHitBoxrect.left < movableBoundRect.left)
    {
        player->SetPosition({ movableBoundRect.left + pHitBoxrect.width / 2.f, player->GetPosition().y});
    }
    if (pHitBoxrect.top < movableBoundRect.top)
    {
        player->SetPosition({ player->GetPosition().x , movableBoundRect.top + pHitBoxrect.height / 2.f });
    }
    if (pHitBoxrect.left + pHitBoxrect.width > movableBoundRect.left + movableBoundRect.width)
    {
        player->SetPosition({ movableBoundRect.left + movableBoundRect.width - pHitBoxrect.width / 2.f , player->GetPosition().y });
    }
    if (pHitBoxrect.top + pHitBoxrect.height > movableBoundRect.top + movableBoundRect.height)
    {
        player->SetPosition({ player->GetPosition().x ,movableBoundRect.top + movableBoundRect.height -pHitBoxrect.height / 2.f });
    }
}

void Room::Draw(sf::RenderWindow& window)
{
    window.draw(*spritePtr);
    window.draw(*sprite2Ptr);
    window.draw(*sprite3Ptr);
    window.draw(*sprite4Ptr);

    if (isDrawspriteControl)
        window.draw(*spriteControlPtr);
}

void Room::PostDraw()
{
}

void Room::Exit()
{
}

void Room::Release()
{
}

// Example of Save Isaac StringMapPathInfo by FileManager(Csv)
    /*std::vector<std::vector<std::wstring>> rows;
    std::vector<std::wstring> row;

    row.clear();
    row.push_back(L"ID");
    row.push_back(L"Room Texture Path~");
    rows.push_back(row);

    row.clear();
    row.push_back(L"1類");
    row.push_back(L"Gfx/Backdrop/01_basement.png");
    row.push_back(L"Gfx/Backdrop/01_basement_nfloor.png");
    row.push_back(L"Gfx/Backdrop/01_lbasementfloor.png");
    rows.push_back(row);

    FILE_MGR.SaveByCsv(rows, L"Csv/room_texture_path.csv");

    if (auto csvMap = FILE_MGR.LoadByCsv(L"Csv/room_texture_path.csv"))
        std::wcout << (*csvMap)[L"1類"][0] << std::endl;
    else
        std::wcerr << L"csvMap was nullptr" << std::endl;*/