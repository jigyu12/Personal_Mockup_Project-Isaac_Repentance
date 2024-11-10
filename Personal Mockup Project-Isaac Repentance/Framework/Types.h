#pragma once

struct AxisInfo
{
	Axis axis;
	std::unordered_map<sf::Keyboard::Key, bool> keyMap;
	float sensi = 10.f;
	float value = 0.f;

	void AddKey(sf::Keyboard::Key key, bool isPositive)
	{
		keyMap.insert({key, isPositive});
	}
};