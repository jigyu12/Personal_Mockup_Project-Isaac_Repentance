#pragma once

class InputManager
{
	DECLARE_SINGLETON(InputManager);

public:
	void Init();

	void Update(float dt);

	void Draw(sf::RenderWindow& window) {}

	void Release() {}

	void UpdateEvent(const sf::Event& ev);

	bool GetKeyDown(const sf::Keyboard::Key key);
	bool GetKeyHold(const sf::Keyboard::Key key);
	bool GetKeyUp(const sf::Keyboard::Key key);

	bool GetMouseDown(const sf::Mouse::Button mouseButton);
	bool GetMouseHold(const sf::Mouse::Button mouseButton);
	bool GetMouseUp(const sf::Mouse::Button mouseButton);
	sf::Vector2i GetMousePosition(const sf::RenderWindow& window) const;

	float GetAxisRaw(Axis axis);
	float GetAxis(Axis axis);

	void Clear();

private:
	sf::Mouse mouse;

	std::list<sf::Keyboard::Key> downKeys;
	std::list<sf::Keyboard::Key> holdKeys;
	std::list<sf::Keyboard::Key> upKeys;

	std::list<sf::Mouse::Button> downMouseButtons;
	std::list<sf::Mouse::Button> holdMouseButtons;
	std::list<sf::Mouse::Button> upMouseButtons;

	std::unordered_map<Axis, AxisInfo> axisInfoMap;

	std::wstring axisFilePath = L"Jsons/axis_info.json";
};