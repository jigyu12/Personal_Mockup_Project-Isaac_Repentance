#pragma once

#include "../Framework/SpriteGameObject.h"

class MainTitle : public SpriteGameObject
{
public:
	MainTitle(const std::wstring& name = L"MainTitle");
	virtual ~MainTitle() = default;

	void Init() override;
	void Enter() override;

	void Update(float deltaTime) override;
	void FixedUpdate(float deltaTime) override;

	void Draw(sf::RenderWindow& window) override;
	void PostDraw() override;

	void Exit() override;
	void Release() override;
	
	std::shared_ptr<sf::Sprite>& GetSpriteFlyPtr() { return spriteFlyPtr; }

protected:
	std::shared_ptr<sf::Texture> spriteStartTexturePtr;
	std::shared_ptr<sf::Sprite> spriteStartPtr;

	std::shared_ptr<sf::Texture> spriteLogoTexturePtr;
	std::shared_ptr<sf::Sprite> spriteLogoPtr;

	std::shared_ptr<sf::Texture> spriteLogoShadowTexturePtr;
	std::shared_ptr<sf::Sprite> spriteLogoShadowPtr;

	std::shared_ptr<sf::Texture> spriteFlyTexturePtr;
	std::shared_ptr<sf::Sprite> spriteFlyPtr;

	std::wstring titleTextureCsvPath;

	float switchStart = 0.f;
	float switchStartDelay = 0.2f;

	float udLogo = 0.f;
	float udLogoDelay = 1.f;
	float logoSpeed = -100.f;
	float upTime = 0.f;

	float switchFlyStart = 0.f;
	float switchFlyStartDelay = 0.02f;
};