#include "pch.h"

void SoundManager::Init(int totalChannels)
{
	playingSfxs.clear();
	waitingSfxs.clear();

	bgm = std::make_shared<sf::Sound>();

	std::shared_ptr<json> loadVolumeInfoPtr = FILE_MGR.LoadByJson(volumeFilePath);
	if (loadVolumeInfoPtr)
	{
		try
		{
			auto loadVolumeInfo = loadVolumeInfoPtr->get<std::vector<float>>();
			bgmVolume = loadVolumeInfo[0];
			sfxVolume = loadVolumeInfo[1];
		}
		catch (const std::exception& ex)
		{
			std::wcerr << L"Invaild loadVolumeInfo data: " << ex.what() << std::endl;

			return;
		}
	}
	else
	{
		std::wcerr << L"loadVolumeInfoPtr was nullptr" << std::endl;

		return;
	}

	bgm = std::make_shared<sf::Sound>();
	bgmPath = L"Invaild bgmPath";
	for (int i = 0; i < totalChannels; i++)
	{
		waitingSfxs.push_back(std::make_shared<sf::Sound>());
	}
}

void SoundManager::Update(float deltaTime)
{
	auto it = playingSfxs.begin();
	while (it != playingSfxs.end())
	{
		if ((*it)->getStatus() == sf::Sound::Stopped)
		{
			waitingSfxs.push_back(*it);
			it = playingSfxs.erase(it);
		}
		else
		{
			it++;
		}
	}
}

void SoundManager::Release()
{
	playingSfxs.clear();
	waitingSfxs.clear();
}

void SoundManager::SetBgmVolume(const float volume)
{
	if (volume < 0.f || volume > 100.f)
	{
		std::wcerr << L"BgmVolume out of range." << std::endl;

		return;
	}
	
	bgmVolume = volume;
	bgm->setVolume(bgmVolume);

	float bVolume = bgmVolume;
	float sVolume = sfxVolume;
	json jArrayVol = { bVolume, sVolume };
	FILE_MGR.SaveByJson(jArrayVol, volumeFilePath);
}

void SoundManager::SetSfxVolume(const float volume)
{
	if (volume < 0.f || volume > 100.f)
	{
		std::wcerr << L"SfxVolume out of range." << std::endl;

		return;
	}
	
	sfxVolume = volume;
	for (auto& pSfx : playingSfxs)
	{
		pSfx->setVolume(sfxVolume);
	}

	float bVolume = bgmVolume;
	float sVolume = sfxVolume;
	json jArrayVol = { bVolume, sVolume };
	FILE_MGR.SaveByJson(jArrayVol, volumeFilePath);
}

void SoundManager::PlayBgm(const std::wstring& path, const bool loop)
{
	std::shared_ptr<sf::SoundBuffer> buffer = RES_SOUNDBUFFER_MGR.Get(path);
	if (!buffer)
	{
		std::wcerr << L"Invaild bgm buffer." << std::endl;

		return;
	}

	if (bgmPath == path)
	{
		if(bgm->getStatus() != sf::Sound::Playing)
			bgm->play();
	}
	else
	{
		bgmPath = path;

		StopBgm();

		SetBgmVolume(bgmVolume);
		bgm->setLoop(loop);
		bgm->setBuffer(*buffer);
		bgm->play();
	}
}

void SoundManager::PauseBgm()
{
	bgm->pause();
}

void SoundManager::StopBgm()
{
	bgm->stop();
}

void SoundManager::PlaySfx(const std::wstring& path, const bool loop)
{
	std::shared_ptr<sf::SoundBuffer> buffer = RES_SOUNDBUFFER_MGR.Get(path);
	if (!buffer)
	{
		std::wcerr << L"Invaild sfx buffer." << std::endl;

		return;
	}

	std::shared_ptr<sf::Sound> sfx = nullptr;

	if (waitingSfxs.empty())
	{
		sfx = playingSfxs.front();
		playingSfxs.pop_front();
		sfx->stop();
	}
	else
	{
		sfx = waitingSfxs.front();
		waitingSfxs.pop_front();
	}

	SetSfxVolume(sfxVolume);
	sfx->setLoop(loop);
	sfx->setBuffer(*buffer);
	sfx->play();
	playingSfxs.push_back(sfx);
}

// Example of Save Isaac volume by FileManager(Json)
//float bVolume = 100.f;
//float sVolume = 100.f;
//json jArrayVol = { bVolume, sVolume };
//FILE_MGR.SaveByJson(jArrayVol, volumeFilePath);