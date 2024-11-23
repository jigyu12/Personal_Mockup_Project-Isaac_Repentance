#include "../Framework/pch.h"
#include "Fly.h"
#include "Bullet.h"

Fly::Fly(const std::wstring& name)
	: SpriteGameObject(name)
{
}

void Fly::Init()
{
	flyAnimationPath.clear();

	flyAnimationPath.push_back(L"Json/FlyMove_animation.json");
	flyAnimationPath.push_back(L"Json/FlyDead_animation.json");
}

void Fly::Enter()
{
	SetSortingLayers(SortingLayers::Foreground);

	auto playerList = SCENE_MGR.GetCurrentScene()->FindAllGoByName(L"Player");
	player = std::dynamic_pointer_cast<Player>(playerList->front());
	moveDirection = { 0.f, 0.f };

	deadDelay = 0.3f;
	deadAccumTime = 0.f;
	isDead = false;

	hitAccumTime = 0.f;
	hitDelay = 0.5f;
	isHit = false;

	hp = 30;

	originColor = spritePtr->getColor();

	speed = Utils::RandomRange(150.f, 250.f);

	animator.Init();

	for (int i = 0; i < flyAnimationPath.size(); i++)
	{
		auto val = RES_ANICLIP_MGR.Get(flyAnimationPath[i]);
		flyAniClipMap.insert({ val->GetId(), val });
	}

	flyAniClipInfos.push_back({ L"FlyMove", L"FlyDead", false, {0.f, 1.f} });
	flyAniClipInfos.push_back({ L"FlyMove", L"FlyDead", false, {0.f, -1.f} });
	flyAniClipInfos.push_back({ L"FlyMove", L"FlyDead", false, {-1.f, 0.f} });
	flyAniClipInfos.push_back({ L"FlyMove", L"FlyDead", false, {1.f, 0.f} });

	animator.SetTarget(spritePtr);

	animator.Play(flyAniClipMap[L"FlyMove"]);
	currenFlyAniClipInfo = std::make_shared<FlyAniClipInfo>(flyAniClipInfos[(int)Utils::RandomRange(0,1)]);

	SetScale({ 3.f, 3.f});
	SetOrigin(Origins::MC);
	//SetPosition({0.f, 0.f});

	hitbox = std::make_shared<HitBoxCircle>(spritePtr->getLocalBounds().width / 4);
}

void Fly::Update(float deltaTime)
{
	moveDirection = player->GetPosition() - position;
	float magnitude = Utils::Magnitude(moveDirection);
	if (magnitude > 1.f)
	{
		Utils::Normalize(moveDirection);
	}
	SetPosition(position + moveDirection * speed * deltaTime);

	std::dynamic_pointer_cast<HitBoxCircle>(hitbox)->UpdateHitBox(*spritePtr);


	animator.Update(deltaTime);
	{
		if (isHit)
		{
			hitAccumTime += deltaTime;
			spritePtr->setColor(sf::Color::Red);

			if (hitAccumTime >= hitDelay)
			{
				hitAccumTime = 0.f;
				spritePtr->setColor(originColor);
				isHit = false;
			}
		}

		if (hp > 0)
			return;

		std::dynamic_pointer_cast<HitBoxCircle>(hitbox)->SetRadius(0.f);

		if (!isDead)
		{
			isDead = true;
			SetPosition({ position.x - 64.f, position.y - 64.f });
		}	

		const auto& flyClipId = currenFlyAniClipInfo->dead;

		if (animator.GetCurrentClipId() != flyClipId)
		{
			animator.Play(flyAniClipMap[flyClipId]);
		}

		deadAccumTime += deltaTime;

		if (deadAccumTime < deadDelay)
			return;

		SetActive(false);
	}
}

void Fly::FixedUpdate(float deltaTime)
{
	auto bulletList = SCENE_MGR.GetCurrentScene()->FindAllGoByName(L"Bullet");
	for (auto iter = bulletList->begin(); iter != bulletList->end(); iter++)
	{
		auto bullet = std::dynamic_pointer_cast<Bullet>(*iter);
		if (Utils::CheckCollision(bullet->GetHitBox(), hitbox))
		{
			bullet->SetIdleAccumTimeMax();
			bullet->SetAccelSpeed(0.f);

			if (std::dynamic_pointer_cast<HitBoxCircle>(bullet->GetHitBox())->GetRadius() != 0.f)
			{
				hp -= 10;
				if (hp > 0)
				{
					SetPosition({ position.x - Utils::GetNormalized(bullet->GetPosition() - position).x * 20.f, position.y - Utils::GetNormalized(bullet->GetPosition() - position).y * 20.f });
					isHit = true;
				}
			}
				

			std::dynamic_pointer_cast<HitBoxCircle>(bullet->GetHitBox())->SetRadius(0.f);
		}
	}
}

void Fly::Draw(sf::RenderWindow& window)
{
	window.draw(*spritePtr);

	std::dynamic_pointer_cast<HitBoxCircle>(hitbox)->Draw(window);
}

void Fly::PostDraw()
{
}

void Fly::Exit()
{
}

void Fly::Release()
{
}
