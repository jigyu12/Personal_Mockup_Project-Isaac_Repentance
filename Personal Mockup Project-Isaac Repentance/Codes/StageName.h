#pragma once

#include "../Framework/TextGameObject.h"

class StageName : public TextGameObject
{
public:
	StageName(const std::wstring& name = L"StageName");
	virtual ~StageName() = default;

	void Init() override;
	void Enter() override;

	void Update(float deltaTime) override;
	void FixedUpdate(float deltaTime) override;

	void Draw(sf::RenderWindow& window) override;
	void PostDraw() override;

	void Exit() override;
	void Release() override;

protected:
	sf::Texture spriteEffectTexture;
	sf::Sprite spriteEffect;

	float effectStart = 0.f;
	float effectDelay = 1.f;

	float effectStart2 = 0.f;
	float effectDelay2 = 1.f;

	float effectStart3 = 0.f;
	float effectDelay3 = 1.f;
};