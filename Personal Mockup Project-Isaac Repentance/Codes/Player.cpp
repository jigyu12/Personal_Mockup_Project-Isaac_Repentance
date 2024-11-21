#include "../Framework/pch.h"
#include "Player.h"

Player::Player(const std::wstring& name)
	: SpriteGameObject(name), direction({0.f,0.f}), speed(400.f), headTexturePtr(std::make_shared<sf::Texture>()), headSpritePtr(std::make_shared<sf::Sprite>())
{
}

void Player::Init()
{
	playerBodyAnimationPath.clear();
	playerHeadAnimationPath.clear();

	playerBodyAnimationPath.push_back(L"Json/IsaacBodyMoveFrontBack_animation.json");
	playerBodyAnimationPath.push_back(L"Json/IsaacBodyMoveRightSide_animation.json");

	playerHeadAnimationPath.push_back(L"Json/IsaacHeadAttackBack_animation.json");
	playerHeadAnimationPath.push_back(L"Json/IsaacHeadAttackFront_animation.json");
	playerHeadAnimationPath.push_back(L"Json/IsaacHeadAttackRightSide_animation.json");
	playerHeadAnimationPath.push_back(L"Json/IsaacHeadMoveBack_animation.json");
	playerHeadAnimationPath.push_back(L"Json/IsaacHeadMoveFront_animation.json");
	playerHeadAnimationPath.push_back(L"Json/IsaacHeadMoveRightSide_animation.json");

	animatorBody.Init();
	animatorHead.Init();
}

void Player::Enter()
{
	SetSortingLayers(SortingLayers::Foreground);

	SetPosition({0.f, 0.f});
	SetOrigin(Origins::MC);

	std::shared_ptr<AnimationClip> temp = RES_ANICLIP_MGR.Get(playerBodyAnimationPath[0]);

	animatorBody.SetTarget(spritePtr);
	animatorHead.SetTarget(headSpritePtr);

	hitbox = std::make_shared<HitBoxCircle>(50.f);
}

void Player::Update(float deltaTime)
{
	std::dynamic_pointer_cast<HitBoxCircle>(hitbox)->UpdateHitBox(*spritePtr);
}

void Player::FixedUpdate(float deltaTime)
{
}

void Player::Draw(sf::RenderWindow& window)
{
	window.draw(*spritePtr);
	window.draw(*headSpritePtr);

	std::dynamic_pointer_cast<HitBoxCircle>(hitbox)->Draw(window);
}

void Player::PostDraw()
{
}

void Player::Exit()
{
}

void Player::Release()
{
}

void Player::SetPosition(const sf::Vector2f& position)
{
	SpriteGameObject::SetPosition(position);
	sf::Vector2f headPos = { position.x, position.y - 16.f };
	headSpritePtr->setPosition(headPos);
}

void Player::SetOrigin(const Origins originPreset)
{
	SpriteGameObject::SetOrigin(originPreset);

	if (originPreset == Origins::Custom)
	{
		std::wcerr << L"Cannot assign custom originPreset for sprite." << std::endl;

		return;
	}
	Utils::SetOrigin(*headSpritePtr, originPreset);
}

void Player::SetOrigin(const sf::Vector2f& newOrigin)
{
	SpriteGameObject::SetOrigin(newOrigin);
	headSpritePtr->setOrigin(newOrigin);
}

void Player::SetRotation(float angle)
{
	SpriteGameObject::SetRotation(angle);
	headSpritePtr->setRotation(angle);
}

void Player::SetScale(const sf::Vector2f& scale)
{
	SpriteGameObject::SetScale(scale);
	headSpritePtr->setScale(scale);
}