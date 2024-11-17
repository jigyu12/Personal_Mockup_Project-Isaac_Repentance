#pragma once

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

};