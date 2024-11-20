#pragma once

#include "GameObject.h"

struct IntegerRect
{
	int left;
	int top;
	int width;
	int height;
	
	IntegerRect() : left(0), top(0), width(0), height(0) {}
	IntegerRect(const int left, const int top, const int width, const int height) : left(left), top(top), width(width), height(height) {}
};

struct AxisInfo
{
	Axis axis;
	std::unordered_map<sf::Keyboard::Key, bool> keyMap;
	float sensitivity;
	float value;

	AxisInfo() : axis(Axis::None), sensitivity(0.f), value(0.f) {}

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

struct DrawOrderComparerBack
{
	bool operator()(std::shared_ptr<GameObject> object1, std::shared_ptr<GameObject> object2) const
	{
		if (object1->GetSortingLayers() != object2->GetSortingLayers())
			return object1->GetSortingLayers() > object2->GetSortingLayers();

		return object1->GetsortingOrderBack() > object2->GetsortingOrderBack();
	}
};

struct AnimationFrame
{
	std::wstring texturePath;
	IntegerRect textureCoord;

	AnimationFrame() : texturePath(L"Invaild path"), textureCoord(0,0,0,0) {}
	AnimationFrame(const std::wstring& texturePath, const IntegerRect& textureCoord) : texturePath(texturePath), textureCoord(textureCoord) {}
};

struct AnimationEvent
{
	std::wstring animationId;
	int frameIndex;
	std::vector<std::function<void()>> vvActions;

	bool operator==(const AnimationEvent& other) const
	{
		return (animationId == other.animationId) && (frameIndex == other.frameIndex);
	}
};

struct AnimationEventHash
{
	std::size_t operator()(const std::pair<std::wstring, int>& pair) const
	{
		std::size_t h1 = std::hash<std::wstring>()(pair.first);
		std::size_t h2 = std::hash<int>()(pair.second);

		return h1 ^ (h2 << 1);
	}
};