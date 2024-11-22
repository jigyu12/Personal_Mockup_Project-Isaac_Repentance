#include "../Framework/pch.h"
#include "Bullet.h"

Bullet::Bullet(const std::wstring& name)
	: SpriteGameObject(name), moveDirection({ 0.f,0.f }), speed({0.f, 0.f}), accelSpeed(2.f), damage(0), currentBulletAniClipInfo(nullptr)
{
}

void Bullet::Init()
{
	bulletAnimationPath.clear();

	bulletAnimationPath.push_back(L"Json/BulletIdle_animation.json");
	bulletAnimationPath.push_back(L"Json/BulletDestroy_animation.json");
}

void Bullet::Enter()
{
	SetSortingLayers(SortingLayers::Foreground);

	auto playerList = SCENE_MGR.GetCurrentScene()->FindAllGoByName(L"Player");
	player = std::dynamic_pointer_cast<Player>(playerList->front());
	moveDirection.x = player->GetAttackDirection().x;
	moveDirection.y = player->GetAttackDirection().y;

	idleDelay = 0.7f;
	idleAccumTime = 0.f;

	destroyDelay = 0.3f;
	destroyAccumTime = 0.f;
	
	accelSpeed = 2.f;

	if (ABS(player->GetAttackDirection().x - player->GetMoveDirection().x) < EPSILON && ABS(player->GetAttackDirection().y - player->GetMoveDirection().y) < EPSILON)
	{
		speed = { player->GetMoveDirSpeed().x * 0.3f + player->GetAttackDirSpeed().x, player->GetMoveDirSpeed().y * 0.3f + player->GetAttackDirSpeed().y };
	}
	else
	{
		speed = { player->GetAttackDirSpeed().x, player->GetAttackDirSpeed().y };
	}
	

	animator.Init();

	for (int i = 0; i < bulletAnimationPath.size(); i++)
	{
		auto val = RES_ANICLIP_MGR.Get(bulletAnimationPath[i]);
		bulletAniClipMap.insert({ val->GetId(), val });
	}

	bulletAniClipInfos.push_back({ L"BulletIdle", L"BulletDestory", false, {0.f, 1.f} });
	bulletAniClipInfos.push_back({ L"BulletIdle", L"BulletDestory", false, {0.f, -1.f} });
	bulletAniClipInfos.push_back({ L"BulletIdle", L"BulletDestory", false, {-1.f, 0.f} });
	bulletAniClipInfos.push_back({ L"BulletIdle", L"BulletDestory", false, {1.f, 0.f} });

	animator.SetTarget(spritePtr);

	animator.Play(bulletAniClipMap[L"BulletIdle"]);
	currentBulletAniClipInfo = std::make_shared<BulletAniClipInfo>(bulletAniClipInfos[0]);

	SetScale({ player->GetScale().x * 2.f / 3.f, player->GetScale().y * 2.f / 3.f });
	SetOrigin(Origins::MC);
	SetPosition({ player->GetPosition().x - 17,  player->GetPosition().y - 17 });

	hitbox = std::make_shared<HitBoxCircle>(spritePtr->getLocalBounds().width / 9);
}

void Bullet::Update(float deltaTime)
{
	float magnitude = Utils::Magnitude(moveDirection);
	if (magnitude > 1.f)
	{
		Utils::Normalize(moveDirection);
	}
	SetPosition(position + speed * accelSpeed * deltaTime);

	std::dynamic_pointer_cast<HitBoxCircle>(hitbox)->UpdateHitBox(*spritePtr);




	animator.Update(deltaTime);

	{
		idleAccumTime += deltaTime;

		if (idleAccumTime < idleDelay)
			return;

		auto min = std::min_element(bulletAniClipInfos.begin(), bulletAniClipInfos.end(),
			[this](const BulletAniClipInfo& lhs, const BulletAniClipInfo& rhs)
			{
				float d1 = Utils::Distance(moveDirection, lhs.dirVector);
				float d2 = Utils::Distance(moveDirection, rhs.dirVector);

				return d1 < d2;
			}
		);
		currentBulletAniClipInfo = std::make_shared<BulletAniClipInfo>(*min);

		if (currentBulletAniClipInfo->flipX)
		{
			spritePtr->setScale({ std::abs(scale.x) * -1.f, scale.y * 1.f });
		}
		else
		{
			spritePtr->setScale({ std::abs(scale.x) * 1.f, scale.y * 1.f });
		}

		const auto& bulletClipId = currentBulletAniClipInfo->destroy;

		if (animator.GetCurrentClipId() != bulletClipId)
		{
			animator.Play(bulletAniClipMap[bulletClipId]);
		}

		destroyAccumTime += deltaTime;

		accelSpeed = Utils::Clamp(accelSpeed - 3.f * deltaTime, 0.f, 1.f);

		if (destroyAccumTime < destroyDelay)
			return;

		player->GetBulletPool().Return(SCENE_MGR.GetCurrentScene()->GetRemoveGameObjects(), shared_from_this());
	}
}

void Bullet::FixedUpdate(float deltaTime)
{
}

void Bullet::Draw(sf::RenderWindow& window)
{
	window.draw(*spritePtr);

	std::dynamic_pointer_cast<HitBoxCircle>(hitbox)->Draw(window);
}

void Bullet::PostDraw()
{
}

void Bullet::Exit()
{
}

void Bullet::Release()
{
}

// Example of Save Load Bullet Animation by FileManager(Json)
	/*{
		{
			AnimationClip temp;
			temp.id = L"BulletIdle";
			temp.loopType = AnimationLoopTypes::Loop;
			temp.fps = 10;
			temp.frames.push_back({ L"Gfx/bulletatlas.png" , {256,256,64,64} });
			json jArray = temp;
			FILE_MGR.SaveByJson(jArray, L"Json/BulletIdle_animation.json");
		}
		{
			AnimationClip temp;
			temp.id = L"BulletDestory";
			temp.loopType = AnimationLoopTypes::Single;
			temp.fps = 15;
			IntegerRect rect = { 192,192,64,64 };
			for (int i = 0; i < 15; i++)
			{
				if (i % 4 == 0)
				{
					rect.left = 192;
					rect.left += 64;
					rect.top += 64;
				}
				else
				{
					rect.left += 64;
				}
				temp.frames.push_back({ L"Gfx/bulletatlas.png" , rect });
				std::wcout << temp.frames[i].textureCoord.left << " " << temp.frames[i].textureCoord.top << " " << temp.frames[i].textureCoord.width << " " << temp.frames[i].textureCoord.height << std::endl;
			}
			json jArray = temp;
			FILE_MGR.SaveByJson(jArray, L"Json/BulletDestroy_animation.json");
		}
	}
	{
		std::shared_ptr<json> loadBulletAniPtr = FILE_MGR.LoadByJson(L"Json/BulletDestroy_animation.json");
		if (loadBulletAniPtr)
		{
			try
			{
				AnimationClip loadBulletAniInfos = loadBulletAniPtr->get<AnimationClip>();
			}
			catch (const std::exception& ex)
			{
				std::wcerr << L"Invaild loadBulletAniInfo data: " << ex.what() << std::endl;

				return;
			}
		}
		else
		{
			std::wcerr << L"loadBulletAniPtr was nullptr" << std::endl;

			return;
		}
	}*/