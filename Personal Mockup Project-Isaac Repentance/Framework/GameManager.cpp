#include "pch.h"

void GameManager::Init(const std::wstring& windowName)
{
	window.create(sf::VideoMode::getDesktopMode(), windowName, sf::Style::Fullscreen);
	windowWidth = window.getSize().x;
	windowHeight = window.getSize().y;

	time = 0.f;
	deltaTime = 0.f;
	realTime = 0.f;
	realDeltaTime = 0.f;
	timeScale = 1.f;
}

void GameManager::CalculateTime()
{
	sf::Time dt = clock.restart();
	realDeltaTime = deltaTime = dt.asSeconds();

	deltaTime *= timeScale;

	realTime += realDeltaTime;
	time += deltaTime;
}