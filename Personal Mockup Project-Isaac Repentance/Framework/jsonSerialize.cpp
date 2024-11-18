#include "pch.h"

void to_json(json& j, const sf::Keyboard::Key& key)
{
	j = static_cast<int>(key);
}

void from_json(const json& j, sf::Keyboard::Key& key)
{
	key = static_cast<sf::Keyboard::Key>(j.get<int>());
}