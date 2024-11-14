#pragma once

using json = nlohmann::json;

#define DECLARE_SINGLETON(classname)                    \
public:													\
	static classname& GetInstance()						\
	{													\
		static classname instance;						\
		return instance;								\
	}													\
														\
private:												\
	classname() {}										\
	classname(const classname&) {}						\
	classname& operator=(const classname&) {}			\
	~classname() {}										
	

#define GAME (Game::GetInstance())
#define GAME_MGR (GameManager::GetInstance())
#define INPUT_MGR (InputManager::GetInstance())
#define FILE_MGR (FileManager::GetInstance())

#define RES_TEXTURE_MGR (ResourceManager<sf::Texture>::GetInstance())
#define RES_FONT_MGR (ResourceManager<sf::Font>::GetInstance())