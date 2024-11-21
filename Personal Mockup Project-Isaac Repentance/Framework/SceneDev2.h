#pragma once

#include "../Codes/Room.h"
#include "../Codes/Player.h"

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
	std::shared_ptr<Player> player;
};