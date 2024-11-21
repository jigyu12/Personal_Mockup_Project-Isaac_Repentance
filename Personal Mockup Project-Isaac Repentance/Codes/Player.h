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



protected:
	sf::Texture textureHead;
	sf::Sprite head;

	Animator animator;

	sf::Vector2f direction;
	float speed;
};