#pragma once

#include "GameObject.h"

struct AxisInfo
{
	Axis axis;
	std::unordered_map<sf::Keyboard::Key, bool> keyMap;
	float sensitivity = 10.f;
	float value = 0.f;

	void AddKey(sf::Keyboard::Key key, bool isPositive)
	{
		keyMap.insert({key, isPositive});
	}
};

// Isaac ¿ë
struct DrawOrderComparer
{
	bool operator()(std::shared_ptr<GameObject> a, std::shared_ptr<GameObject> b) const
	{
		if (a->sortingLayer != b->sortingLayer)
			return a->sortingLayer > b->sortingLayer;
		return a->GetPosition().y > b->GetPosition().y;
	}
};