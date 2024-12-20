#pragma once

#include "../Codes/Room.h"
#include "../Codes/Player.h"
#include "../Codes/Fly.h"
#include "../Codes/StageName.h"

class SceneDev2 : public Scene
{
public:
	SceneDev2();
	~SceneDev2() = default;

	void Init() override;
	void Enter() override;

	void Update(float deltaTime) override;
	void FixedUpdate(float deltaTime) override;

	void Draw(sf::RenderWindow& window) override;
	void PostDraw() override;

	void Exit() override;
	void Release() override;

protected:
	std::vector<std::shared_ptr<Room>> rooms;

	float bgmintro = 0.f;
	float bgmintroDelay = 14.f;
};