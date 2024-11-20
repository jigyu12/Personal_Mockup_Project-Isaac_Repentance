#pragma once

class SoundManager
{
	DECLARE_SINGLETON(SoundManager);

public:
	void Init(int totalChannels = 64);

	void Update(float deltaTime);

	void Draw(sf::RenderWindow& window) {}

	void Release();

	float GetBgmVolume() const { return bgmVolume; }
	float GetSfxVolume() const { return sfxVolume; }

	void SetBgmVolume(const float volume);
	void SetSfxVolume(const float volume);

	void PlayBgm(const std::wstring& path, const bool loop = true);
	void PauseBgm();
	void StopBgm();

	void PlaySfx(const std::wstring& path, const bool loop = false);

private:
	std::shared_ptr<sf::Sound> bgm;
	std::wstring bgmPath;

	std::list<std::shared_ptr<sf::Sound>> playingSfxs;
	std::list<std::shared_ptr<sf::Sound>> waitingSfxs;

	float bgmVolume;
	float sfxVolume;

	std::wstring volumeFilePath = L"Json/volume_info.json";
};