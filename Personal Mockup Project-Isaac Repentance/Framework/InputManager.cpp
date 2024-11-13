#include "pch.h"

void InputManager::Init()
{
	downKeys.clear();
	holdKeys.clear();
	upKeys.clear();

	downMouseButtons.clear();
	holdMouseButtons.clear();
	upMouseButtons.clear();

	axisInfoMap.clear();


	std::ifstream inFile("Jsons/axis_info.json");
	if (!inFile)
	{
		std::wcerr << "axis_info.json Load Failed" << std::endl;
	}
	else
	{
		json jIn;
		inFile >> jIn;

		std::vector<AxisInfo> loadAxisInfos = jIn.get<std::vector<AxisInfo>>();
		for (const auto& axisInfo : loadAxisInfos)
		{
			axisInfoMap.insert({ axisInfo.axis, axisInfo });
		}
	}
	
	inFile.close();
}

void InputManager::Update(float dt)
{
	for (auto& pair : axisInfoMap)
	{
		auto& axisInfo = pair.second;
		float raw = GetAxisRaw(axisInfo.axis);
		float dir = raw;
		if (dir == 0.f && axisInfo.value != 0.f)
		{
			dir = axisInfo.value > 0.f ? -1.f : 1.f;
		}

		axisInfo.value += dir * axisInfo.sensi * dt;
		axisInfo.value = Utils::Clamp(axisInfo.value, -1.f, 1.f);

		float stopThreshold = std::abs(dir * axisInfo.sensi * dt);
		if (raw == 0.f && std::abs(axisInfo.value) < stopThreshold)
		{
			axisInfo.value = 0.f;
		}
	}
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
	auto findIt = axisInfoMap.find(axis);
	if (findIt == axisInfoMap.end())
		return 0.f;

	auto& axisInfo = findIt->second;
	auto it = holdKeys.rbegin();
	while (it != holdKeys.rend())
	{
		sf::Keyboard::Key key = *it;
		auto keyIt = axisInfo.keyMap.find(key);
		if (keyIt != axisInfo.keyMap.end())
		{
			if(keyIt->second)
				return 1.f;
			else
				return -1.f;
		}
		
		++it;
	}

	return 0.0f;
}

float InputManager::GetAxis(Axis axis)
{
	auto findIt = axisInfoMap.find(axis);
	if (findIt == axisInfoMap.end())
		return 0.f;

	return findIt->second.value;
}

void InputManager::Clear()
{
	downKeys.clear();
	upKeys.clear();
	
	downMouseButtons.clear();
	upMouseButtons.clear();
}

void to_json(json& j, const AxisInfo& info)
{
	j = json{
		{"axis", info.axis},
		{"keyMap", info.keyMap},
		{"sensi", info.sensi},
		{"value", info.value}
	};
}

void from_json(const json& j, AxisInfo& info)
{
	j.at("axis").get_to(info.axis);
	j.at("keyMap").get_to(info.keyMap);
	j.at("sensi").get_to(info.sensi);
	j.at("value").get_to(info.value);
}

void to_json(json& j, const sf::Keyboard::Key& key)
{
	j = static_cast<int>(key);
}

void from_json(const json& j, sf::Keyboard::Key& key)
{
	key = static_cast<sf::Keyboard::Key>(j.get<int>());
}