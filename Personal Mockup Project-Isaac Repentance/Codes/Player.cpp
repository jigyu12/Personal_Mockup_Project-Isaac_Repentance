#include "../Framework/pch.h"
#include "Player.h"
#include "Bullet.h"
#include "../Framework/SceneDev2.h"

Player::Player(const std::wstring& name)
	: SpriteGameObject(name), moveDirection({0.f,0.f}), attackDirection({0.f, 0.f}), speed(500.f), headTexturePtr(std::make_shared<sf::Texture>()), headSpritePtr(std::make_shared<sf::Sprite>()), currentBodyAniClipInfo(nullptr), currentHeadAniClipInfo(nullptr)
{
}

void Player::Init()
{
	playerBodyAnimationPath.clear();
	playerHeadAnimationPath.clear();

	playerBodyAnimationPath.push_back(L"Json/IsaacBodyIdleFrontBack_animation.json");
	playerBodyAnimationPath.push_back(L"Json/IsaacBodyMoveFrontBack_animation.json");
	playerBodyAnimationPath.push_back(L"Json/IsaacBodyMoveRightSide_animation.json");

	playerHeadAnimationPath.push_back(L"Json/IsaacHeadAttackBack_animation.json");
	playerHeadAnimationPath.push_back(L"Json/IsaacHeadAttackFront_animation.json");
	playerHeadAnimationPath.push_back(L"Json/IsaacHeadAttackRightSide_animation.json");
	playerHeadAnimationPath.push_back(L"Json/IsaacHeadIdleMoveFront_animation.json");
	playerHeadAnimationPath.push_back(L"Json/IsaacHeadMoveBack_animation.json");
	playerHeadAnimationPath.push_back(L"Json/IsaacHeadMoveRightSide_animation.json");
}

void Player::Enter()
{
	SetSortingLayers(SortingLayers::Foreground);

	moveDirection = { 0.f, 0.f };
	attackDirection = { 0.f, 0.f };

	attackDelay = 1.f;
	attackAccumTime = attackDelay;

	animatorBody.Init();
	animatorHead.Init();
	
	for (int i = 0; i < playerBodyAnimationPath.size(); i++)
	{
		auto val = RES_ANICLIP_MGR.Get(playerBodyAnimationPath[i]);
		bodyAniClipMap.insert({ val->GetId(), val});
	}

	for (int i = 0; i < playerHeadAnimationPath.size(); i++)
	{
		auto val = RES_ANICLIP_MGR.Get(playerHeadAnimationPath[i]);
		headAniClipMap.insert({ val->GetId(), val });
	}
	
	bodyAniClipInfos.push_back({ L"IsaacBodyIdleFrontBack", L"IsaacBodyMoveFrontBack", false, {0.f, 1.f} });
	bodyAniClipInfos.push_back({ L"IsaacBodyIdleFrontBack", L"IsaacBodyMoveFrontBack", false, {0.f, -1.f} });
	bodyAniClipInfos.push_back({ L"IsaacBodyIdleFrontBack", L"IsaacBodyMoveRightSide", true, {-1.f, 0.f} });
	bodyAniClipInfos.push_back({ L"IsaacBodyIdleFrontBack", L"IsaacBodyMoveRightSide", false, {1.f, 0.f} });

	headAniClipInfos.push_back({ L"IsaacHeadMoveFront", L"IsaacHeadAttackFront", false, {0.f, 1.f} });
	headAniClipInfos.push_back({ L"IsaacHeadMoveBack", L"IsaacHeadAttackBack", false, {0.f, -1.f} });
	headAniClipInfos.push_back({ L"IsaacHeadMoveRightSide", L"IsaacHeadAttackRightSide", true, {-1.f, 0.f} });
	headAniClipInfos.push_back({ L"IsaacHeadMoveRightSide", L"IsaacHeadAttackRightSide", false, {1.f, 0.f} });

	animatorBody.SetTarget(spritePtr);
	animatorHead.SetTarget(headSpritePtr);

	animatorBody.Play(bodyAniClipMap[L"IsaacBodyIdleFrontBack"]);
	animatorHead.Play(headAniClipMap[L"IsaacHeadMoveFront"]);
	currentBodyAniClipInfo = std::make_shared<BodyAniClipInfo>(bodyAniClipInfos[0]);
	currentHeadAniClipInfo = std::make_shared<HeadAniClipInfo>(headAniClipInfos[0]);

	SetScale({ 4.f, 4.f });
	SetOrigin(Origins::MC);
	SetPosition({ 0.f, 0.f });

	hitbox = std::make_shared<HitBoxCircle>(spritePtr->getLocalBounds().width / 4);
}

void Player::Update(float deltaTime)
{
	moveDirection.x = INPUT_MGR.GetAxis(Axis::HorizontalMove);
	moveDirection.y = INPUT_MGR.GetAxis(Axis::VerticalMove);

	attackDirection.x = INPUT_MGR.GetAxisRaw(Axis::HorizontalAttack);
	attackDirection.y = INPUT_MGR.GetAxisRaw(Axis::VerticalAttack);

	float magnitude = Utils::Magnitude(moveDirection);
	if (magnitude > 1.f)
	{
		Utils::Normalize(moveDirection);
	}
	SetPosition(position + moveDirection * speed * deltaTime);

	magnitude = Utils::Magnitude(attackDirection);
	if (magnitude > 1.f)
	{
		Utils::Normalize(attackDirection);
	}






	animatorBody.Update(deltaTime);
	animatorHead.Update(deltaTime);

	{
		if (moveDirection.x != 0.f || moveDirection.y != 0.f)
		{
			auto min = std::min_element(bodyAniClipInfos.begin(), bodyAniClipInfos.end(),
				[this](const BodyAniClipInfo& lhs, const BodyAniClipInfo& rhs)
				{
					float d1 = Utils::Distance(moveDirection, lhs.dirVector);
					float d2 = Utils::Distance(moveDirection, rhs.dirVector);

					return d1 < d2;
				}
			);
			currentBodyAniClipInfo = std::make_shared<BodyAniClipInfo>(*min);
		}

		if (currentBodyAniClipInfo->flipX)
		{
			spritePtr->setScale({ std::abs(scale.x) * -1.f, scale.y * 1.f });
		}
		else
		{
			spritePtr->setScale({ std::abs(scale.x) * 1.f, scale.y * 1.f });
		}

		const auto& bodyClipId = (moveDirection.x != 0.f || moveDirection.y != 0.f) ? currentBodyAniClipInfo->move : currentBodyAniClipInfo->idle;

		if (animatorBody.GetCurrentClipId() != bodyClipId)
		{
			animatorBody.Play(bodyAniClipMap[bodyClipId]);
		}
	}
	
	{
		attackAccumTime += deltaTime;

		if (attackDirection.x != 0.f || attackDirection.y != 0.f)
		{
			if (attackAccumTime >= attackDelay)
			{
				Attack();

				attackAccumTime = 0.f;

				auto min = std::min_element(headAniClipInfos.begin(), headAniClipInfos.end(),
					[this](const HeadAniClipInfo& lhs, const HeadAniClipInfo& rhs)
					{
						float d1 = Utils::Distance(attackDirection, lhs.dirVector);
						float d2 = Utils::Distance(attackDirection, rhs.dirVector);

						return d1 < d2;
					}
				);
				currentHeadAniClipInfo = std::make_shared<HeadAniClipInfo>(*min);

				if (currentHeadAniClipInfo->flipX)
				{
					headSpritePtr->setScale({ std::abs(scale.x) * -1.f, scale.y * 1.f });
				}
				else
				{
					headSpritePtr->setScale({ std::abs(scale.x) * 1.f, scale.y * 1.f });
				}

				const auto& headClipId = currentHeadAniClipInfo->attack;

				if (animatorHead.GetCurrentClipId() != headClipId)
				{
					animatorHead.Play(headAniClipMap[headClipId]);
				}
				else
				{
					animatorHead.PushPlayQueue(headAniClipMap[headClipId]);
				}
			}
		}
		else
		{
			if (animatorHead.GetCurrentClipId() != L"IsaacHeadMoveFront")
			{
				animatorHead.PushPlayQueue(headAniClipMap[L"IsaacHeadMoveFront"]);
				currentHeadAniClipInfo = std::make_shared<HeadAniClipInfo>(headAniClipInfos[0]);
			}
		}
	}

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
	bulletPool.ExitAllUnUsedObject();
}

void Player::Release()
{
	bulletPool.ReleaseAllUnUsedObject();
}

void Player::SetPosition(const sf::Vector2f& position)
{
	SpriteGameObject::SetPosition(position);
	sf::Vector2f headPos = { position.x, position.y - (10.f * spritePtr->getScale().y) };
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

void Player::Attack()
{
	SOUND_MGR.PlaySfx(L"Music/tear fire 4.wav");
	bulletPool.Take(SCENE_MGR.GetCurrentScene()->GetAddGameObjects());
}