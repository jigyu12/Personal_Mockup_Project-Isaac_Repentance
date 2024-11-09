#pragma once

class GameManager
{
	DECLARE_SINGLETON(GameManager);

public:
	void Init(const std::wstring& windowName);

	void Update() {}

	void Draw(sf::RenderWindow& window) {}
	
	void Release() {}

	sf::RenderWindow& GetWindow() { return window; }
	unsigned int GetWindowWidth() const { return windowWidth; }
	unsigned int GetWindowHeight() const { return windowHeight; }

	void CalculateTime();

	float GetTime() const { return time; }
	float GetDeltaTime() const { return deltaTime; }
	float GetRealTime() const { return realTime; }
	float GetRealDeltaTime() const { return realDeltaTime; }
	float GetTimeScale() const { return timeScale; }

	void SetTimeScale(const float newTimeScale) { timeScale = newTimeScale; }

private:
	sf::RenderWindow window;

	sf::Clock clock;

	unsigned int windowWidth;
	unsigned int windowHeight;

	float time;
	float deltaTime;
	float realTime;
	float realDeltaTime;
	float timeScale;
};