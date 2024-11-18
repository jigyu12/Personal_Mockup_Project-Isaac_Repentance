#pragma once

#include "GameObject.h"
#include "FileManager.h"

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
struct DrawOrderComparerSprite
{
	bool operator()(std::shared_ptr<GameObject> object1, std::shared_ptr<GameObject> object2) const
	{
		if (object1->GetSortingLayers() != object2->GetSortingLayers())
			return object1->GetSortingLayers() > object2->GetSortingLayers();

		return object1->GetPosition().y > object2->GetPosition().y;
	}
};

struct DrawOrderComparerUI
{
	bool operator()(std::shared_ptr<GameObject> object1, std::shared_ptr<GameObject> object2) const
	{
		if (object1->GetSortingLayers() != object2->GetSortingLayers())
			return object1->GetSortingLayers() > object2->GetSortingLayers();

		return object1->GetsortingOrderUi() > object2->GetsortingOrderUi();
	}
};

struct AnimationFrame
{
	std::wstring texturePath;
	sf::IntRect textureCoord;
};

struct AnimationClip
{
	std::wstring id;
	AnimationLoopTypes loopType;
	int fps;
	std::vector<AnimationFrame> frames;

	bool loadFromFile(const std::string& filePath)
	{
		
	}
};