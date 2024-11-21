#pragma once

using json = nlohmann::json;
using csv = rapidcsv::Document;

#define ABS(X) ((X) < 0 ? -(X) : (X))
#define EPSILON 0.000001

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
#define SCENE_MGR (SceneManager::GetInstance())
#define SOUND_MGR (SoundManager::GetInstance())

#define RES_TEXTURE_MGR (ResourceManager<sf::Texture>::GetInstance())
#define RES_FONT_MGR (ResourceManager<sf::Font>::GetInstance())
#define RES_SOUNDBUFFER_MGR (ResourceManager<sf::SoundBuffer>::GetInstance())
#define RES_ANICLIP_MGR (ResourceManager<AnimationClip>::GetInstance())