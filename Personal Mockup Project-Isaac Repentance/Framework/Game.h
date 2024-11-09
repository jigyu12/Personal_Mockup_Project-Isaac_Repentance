#pragma once

class Game
{
	DECLARE_SINGLETON(Game);

public:
	void Init(const std::wstring& windowName);

	void TotalUpdate();
	void Update(float dt);

	void Release();

private:
	void Draw(sf::RenderWindow& window);
};