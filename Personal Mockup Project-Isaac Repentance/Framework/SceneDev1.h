#pragma once

#include "../Codes/MainTitle.h"
#include "../Codes/SelectMode.h"

class SceneDev1 : public Scene
{
public:
	SceneDev1();
	~SceneDev1() = default;

	void Init() override;
	void Enter() override;

	void Update(float deltaTime) override;
	void FixedUpdate(float deltaTime) override;

	void Draw(sf::RenderWindow& window) override;
	void PostDraw() override;

	void Exit() override;
	void Release() override;
	
protected:
	std::shared_ptr<MainTitle> mainTitle;
	std::shared_ptr<SelectMode> selectMode;

	float moveY = 0.f;
	float moveAccelY = 1000.f;

	bool isDown = false;
	bool isUp = false;

	bool isFlyMove = false;
	float flyMove = 0.f;
	float flyMoveDelay = 1.f;
	float flySpeed = -750.f;

	float bgmintro = 0.f;
	float bgmintroDelay = 14.f;
};