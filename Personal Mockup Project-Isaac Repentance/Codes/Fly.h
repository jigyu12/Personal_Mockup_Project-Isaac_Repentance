#pragma once

#include "../Framework/SpriteGameObject.h"
#include "Player.h"

class Fly : public SpriteGameObject
{
public:
	Fly(const std::wstring& name = L"Fly");
	virtual ~Fly() = default;

	void Init() override;
	void Enter() override;

	void Update(float deltaTime) override;
	void FixedUpdate(float deltaTime) override;

	void Draw(sf::RenderWindow& window) override;
	void PostDraw() override;

	void Exit() override;
	void Release() override;

protected:
	std::vector<std::wstring> flyAnimationPath;

	sf::Vector2f moveDirection;
	float speed;

	int hp;

	float deadAccumTime;
	float deadDelay;
	bool isDead;

	float hitAccumTime;
	float hitDelay;
	bool isHit;

	sf::Color originColor;

	Animator animator;

	struct FlyAniClipInfo
	{
		std::wstring move;
		std::wstring dead;
		bool flipX = false;
		sf::Vector2f dirVector;
	};

	std::shared_ptr<Player> player;

	std::unordered_map<std::wstring, std::shared_ptr<AnimationClip>> flyAniClipMap;
	std::vector<FlyAniClipInfo> flyAniClipInfos;
	std::shared_ptr<FlyAniClipInfo> currenFlyAniClipInfo;
};