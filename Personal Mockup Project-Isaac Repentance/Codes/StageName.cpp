#include "../Framework/pch.h"
#include "StageName.h"

StageName::StageName(const std::wstring& name)
	: TextGameObject(name)
{
}

void StageName::Init()
{
	spriteEffectTexture.loadFromFile("Gfx/UI/effect_024_streak.png");
	spriteEffect.setTexture(spriteEffectTexture);
}

void StageName::Enter()
{
	SetSortingLayers(SortingLayers::Foreground);

	SetFont(L"Font/dalmoori.ttf");
	SetTextSize(50);
	SetTextColor(sf::Color::White);
	textPtr->setString(L"ÁöÇÏ½Ç");

	Utils::SetOrigin(spriteEffect, Origins::MC);
	spriteEffect.setPosition({ -1800.f, -450.f });
	spriteEffect.setScale({ 3.f, 2.f });

	textPtr->setPosition({ spriteEffect.getPosition().x - 40.f ,spriteEffect.getPosition().y - 30.f });
}

void StageName::Update(float deltaTime)
{
	textPtr->setPosition({ spriteEffect.getPosition().x - 40.f ,spriteEffect.getPosition().y - 30.f });
	effectStart += deltaTime;

	if (effectStart < effectDelay)
	{
		spriteEffect.setPosition({ spriteEffect.getPosition().x + 1800.f * deltaTime , spriteEffect.getPosition().y });

		return;
	}

	effectStart2 += deltaTime;

	if (effectStart2 < effectDelay2)
	{
		return;
	}

	effectStart3 += deltaTime;

	if (effectStart3 < effectDelay3)
	{
		spriteEffect.setPosition({ spriteEffect.getPosition().x + 1800.f * deltaTime , spriteEffect.getPosition().y });

		return;
	}

	spriteEffect.setColor(sf::Color::Transparent);
}

void StageName::FixedUpdate(float deltaTime)
{
}

void StageName::Draw(sf::RenderWindow& window)
{
	window.draw(spriteEffect);
	window.draw(*textPtr);
}

void StageName::PostDraw()
{
}

void StageName::Exit()
{
}

void StageName::Release()
{
}
