#pragma once

#include "../Framework/SpriteGameObject.h"

class Player : public SpriteGameObject
{
public:
	Player(const std::wstring& name = L"Player");
	virtual ~Player() = default;

	void Init() override;
	void Enter() override;

	void Update(float deltaTime) override;
	void FixedUpdate(float deltaTime) override;

	void Draw(sf::RenderWindow& window) override;
	void PostDraw() override;

	void Exit() override;
	void Release() override;

	void SetPosition(const sf::Vector2f& position) override;
	void SetOrigin(const Origins originPreset) override;
	void SetOrigin(const sf::Vector2f& newOrigin) override;
	void SetRotation(float angle) override;
	void SetScale(const sf::Vector2f& scale) override;

protected:
	std::shared_ptr<sf::Texture> headTexturePtr;
	std::shared_ptr<sf::Sprite> headSpritePtr;

	std::vector<std::wstring> playerBodyAnimationPath;
	std::vector<std::wstring> playerHeadAnimationPath;

	sf::Vector2f direction;
	float speed;

	Animator animatorBody;
	Animator animatorHead;
};