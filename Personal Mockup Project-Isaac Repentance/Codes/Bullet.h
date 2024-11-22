#pragma once

#include "../Framework/SpriteGameObject.h"
#include "Player.h"

class Bullet : public SpriteGameObject, public std::enable_shared_from_this<Bullet>
{
public:
	Bullet(const std::wstring& name = L"Bullet");
	virtual ~Bullet() = default;

	void Init() override;
	void Enter() override;

	void Update(float deltaTime) override;
	void FixedUpdate(float deltaTime) override;

	void Draw(sf::RenderWindow& window) override;
	void PostDraw() override;

	void Exit() override;
	void Release() override;

	void SetIdleAccumTimeMax() { idleAccumTime = idleDelay; }
	void SetAccelSpeed(float accelVal) { accelSpeed = accelVal; }

protected:
	std::vector<std::wstring> bulletAnimationPath;

	sf::Vector2f moveDirection;

	float idleAccumTime;
	float idleDelay;

	float destroyAccumTime;
	float destroyDelay;

	sf::Vector2f speed;
	float accelSpeed;
	int damage;

	std::shared_ptr<Player> player;

	Animator animator;

	struct BulletAniClipInfo
	{
		std::wstring idle;
		std::wstring destroy;
		bool flipX = false;
		sf::Vector2f dirVector;
	};

	std::unordered_map<std::wstring, std::shared_ptr<AnimationClip>> bulletAniClipMap;
	std::vector<BulletAniClipInfo> bulletAniClipInfos;
	std::shared_ptr<BulletAniClipInfo> currentBulletAniClipInfo;
};