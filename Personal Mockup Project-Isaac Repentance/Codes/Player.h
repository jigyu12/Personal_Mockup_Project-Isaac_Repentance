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
	std::vector<std::wstring> playerBodyAnimationPath;
	std::vector<std::wstring> playerHeadAnimationPath;

	std::shared_ptr<sf::Texture> headTexturePtr;
	std::shared_ptr<sf::Sprite> headSpritePtr;

	sf::Vector2f moveDirection;
	sf::Vector2f attackDirection;
	float speed;

	float attackAccumTime;
	float attackDelay;

	Animator animatorBody;
	Animator animatorHead;

	struct BodyAniClipInfo
	{
		std::wstring idle;
		std::wstring move;
		bool flipX = false;
		sf::Vector2f dirVector;
	};

	struct HeadAniClipInfo
	{
		std::wstring idle;
		std::wstring attack;
		bool flipX = false;
		sf::Vector2f dirVector;
	};

	std::map<std::wstring, std::shared_ptr<AnimationClip>> bodyAniClipMap;
	std::vector<BodyAniClipInfo> bodyAniClipInfos;
	std::shared_ptr<BodyAniClipInfo> currentBodyAniClipInfo;

	std::map<std::wstring, std::shared_ptr<AnimationClip>> headAniClipMap;
	std::vector<HeadAniClipInfo> headAniClipInfos;
	std::shared_ptr<HeadAniClipInfo> currentHeadAniClipInfo;
};