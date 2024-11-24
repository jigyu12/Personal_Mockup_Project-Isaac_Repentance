#pragma once

#include "../Framework/SpriteGameObject.h"

class SelectMode : public SpriteGameObject
{
public:
	SelectMode(const std::wstring& name = L"SelectMode");
	virtual ~SelectMode() = default;

	void Init() override;
	void Enter() override;

	void Update(float deltaTime) override;
	void FixedUpdate(float deltaTime) override;

	void Draw(sf::RenderWindow& window) override;
	void PostDraw() override;

	void Exit() override;
	void Release() override;

protected:
	std::shared_ptr<sf::Texture> spriteNewTexturePtr;
	std::shared_ptr<sf::Sprite> spriteNewPtr;

	std::shared_ptr<sf::Texture> spriteMenuTexturePtr;
	std::shared_ptr<sf::Sprite> spriteMenuPtr;

	std::wstring menuTextureCsvPath;
};