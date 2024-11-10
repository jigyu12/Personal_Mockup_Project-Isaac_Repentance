#pragma once

class Game
{
	DECLARE_SINGLETON(Game);

public:
	void Init(const std::wstring& windowName);

	void TotalUpdate();

	void Release();

private:
	void Update(float dt);

	void Draw(sf::RenderWindow& window);
};