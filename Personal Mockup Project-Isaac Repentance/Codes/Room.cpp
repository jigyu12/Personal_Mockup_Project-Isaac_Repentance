#include "../Framework/pch.h"
#include "Room.h"

Room::Room(const std::wstring& name)
	: SpriteGameObject(name), roomTextureCsvPath(L"Invaild Path")
{
}

void Room::Init()
{
    roomTextureCsvPath = L"Csv/room_texture_path.csv";
}

void Room::Enter()
{
    isDrawspriteControl = false;

    if (auto csvRoomPathMap = FILE_MGR.LoadByCsv(roomTextureCsvPath))
    {
        std::string s_path = Utils::converter.to_bytes((*csvRoomPathMap)[L"1類"][0]);
        spriteControlTexture.loadFromFile(s_path);
        spriteControl.setTexture(spriteControlTexture);

        SpriteGameObject::SetSpriteTexture((*csvRoomPathMap)[L"1類"][1]);
    }
    else
        std::wcerr << L"csvRoomPathMap was nullptr" << std::endl;
    
    spriteControl.setTextureRect({ 0, 0, 163, 90 });
    Utils::SetOrigin(spriteControl, Origins::MC);
    spriteControl.setPosition({0.f, 0.f});
    spriteControl.setScale({ ((float)GAME_MGR.GetWindowWidth() / spriteControl.getGlobalBounds().width) / 3, ((float)GAME_MGR.GetWindowHeight() / spriteControl.getGlobalBounds().height) / 3});

    sprite.setTextureRect({0, 0, 234, 156});
    SpriteGameObject::SetOrigin(Origins::BR);
    SpriteGameObject::SetPosition({ 0.f, 0.f });
    SpriteGameObject::SetScale({ ((float)GAME_MGR.GetWindowWidth() / SpriteGameObject::GetGlobalBounds().width) / 2, ((float)GAME_MGR.GetWindowHeight() / SpriteGameObject::GetGlobalBounds().height) / 2 });

    sprite2.setTexture(*sprite.getTexture());
    sprite2.setTextureRect({ 0, 0, 234, 156 });
    Utils::SetOrigin(sprite2, Origins::BR);
    sprite2.setPosition({ 0.f, 0.f });
    sprite2.setScale({ -((float)GAME_MGR.GetWindowWidth() / sprite2.getGlobalBounds().width) / 2, ((float)GAME_MGR.GetWindowHeight() / sprite2.getGlobalBounds().height) / 2});

    sprite3.setTexture(*sprite.getTexture());
    sprite3.setTextureRect({ 0, 0, 234, 156 });
    Utils::SetOrigin(sprite3, Origins::BR);
    sprite3.setPosition({ 0.f, 0.f });
    sprite3.setScale({ -((float)GAME_MGR.GetWindowWidth() / sprite3.getGlobalBounds().width) / 2, -((float)GAME_MGR.GetWindowHeight() / sprite3.getGlobalBounds().height) / 2 });

    sprite4.setTexture(*sprite.getTexture());
    sprite4.setTextureRect({ 0, 0, 234, 156 });
    Utils::SetOrigin(sprite4, Origins::BR);
    sprite4.setPosition({ 0.f, 0.f });
    sprite4.setScale({ ((float)GAME_MGR.GetWindowWidth() / sprite4.getGlobalBounds().width) / 2, -((float)GAME_MGR.GetWindowHeight() / sprite4.getGlobalBounds().height) / 2 });

    movableBoundRect = { (-(float)GAME_MGR.GetWindowWidth() / 2) * (7.f / 9.f) , (-(float)GAME_MGR.GetWindowHeight() / 2) * (7.f / 9.f) , (float)GAME_MGR.GetWindowWidth() * (7.f / 9.f), (float)GAME_MGR.GetWindowHeight() * (7.f / 9.f) };
}

void Room::Update(float deltaTime)
{
}

void Room::FixedUpdate(float deltaTime)
{
}

void Room::Draw(sf::RenderWindow& window)
{
    window.draw(sprite);
    window.draw(sprite2);
    window.draw(sprite3);
    window.draw(sprite4);

    if (isDrawspriteControl)
        window.draw(spriteControl);
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