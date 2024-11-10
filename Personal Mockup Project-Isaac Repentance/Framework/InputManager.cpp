#include "pch.h"

void InputManager::Init()
{
	downKeys.clear();
	holdKeys.clear();
	upKeys.clear();

	downMouseButtons.clear();
	holdMouseButtons.clear();
	upMouseButtons.clear();
}

void InputManager::Update(float dt)
{
}

void InputManager::UpdateEvent(const sf::Event& ev)
{
	switch (ev.type)
	{
	case sf::Event::KeyPressed:
	{
		if (std::find(holdKeys.begin(), holdKeys.end(), ev.key.code) == holdKeys.end())
		{
			downKeys.push_back(ev.key.code);
			holdKeys.push_back(ev.key.code);
		}
	}
		break;
	case sf::Event::KeyReleased:
	{
		holdKeys.remove(ev.key.code);
		upKeys.push_back(ev.key.code);
	}
		break;
	case sf::Event::MouseButtonPressed:
	{
		if (std::find(holdMouseButtons.begin(), holdMouseButtons.end(), ev.mouseButton.button) == holdMouseButtons.end())
		{
			downMouseButtons.push_back(ev.mouseButton.button);
			holdMouseButtons.push_back(ev.mouseButton.button);
		}
	}
		break;
	case sf::Event::MouseButtonReleased:
	{
		holdMouseButtons.remove(ev.mouseButton.button);
		upMouseButtons.push_back(ev.mouseButton.button);
	}
		break;
	}
}

bool InputManager::GetKeyDown(const sf::Keyboard::Key key)
{
	return std::find(downKeys.begin(), downKeys.end(), key) != downKeys.end();
}

bool InputManager::GetKeyHold(const sf::Keyboard::Key key)
{
	return std::find(holdKeys.begin(), holdKeys.end(), key) != holdKeys.end();
}

bool InputManager::GetKeyUp(const sf::Keyboard::Key key)
{
	return std::find(upKeys.begin(), upKeys.end(), key) != upKeys.end();
}

bool InputManager::GetMouseDown(const sf::Mouse::Button mouseButton)
{
	return std::find(downMouseButtons.begin(), downMouseButtons.end(), mouseButton) != downMouseButtons.end();
}

bool InputManager::GetMouseHold(const sf::Mouse::Button mouseButton)
{
	return std::find(holdMouseButtons.begin(), holdMouseButtons.end(), mouseButton) != holdMouseButtons.end();;
}

bool InputManager::GetMouseUp(const sf::Mouse::Button mouseButton)
{
	return std::find(upMouseButtons.begin(), upMouseButtons.end(), mouseButton) != upMouseButtons.end();
}

sf::Vector2i InputManager::GetMousePosition(const sf::RenderWindow& window) const
{
	return mouse.getPosition(window);
}

float InputManager::GetAxisRaw(Axis axis)
{
	return 0.0f;
}

float InputManager::GetAxis(Axis axis)
{
	return 0.0f;
}

void InputManager::Clear()
{
	downKeys.clear();
	upKeys.clear();
	
	downMouseButtons.clear();
	upMouseButtons.clear();
}