#pragma once

#include "AnimationClip.h"

NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(sf::Vector2f, x, y);

NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(IntegerRect, left, top, width, height);

void to_json(json& j, const sf::Keyboard::Key& key);

void from_json(const json& j, sf::Keyboard::Key& key);

NLOHMANN_JSON_SERIALIZE_ENUM(Axis,
	{
		{Axis::HorizontalMove, L"HorizontalMove"},
		{Axis::VerticalMove, L"VerticalMove"},
		{Axis::HorizontalAttack , L"HorizontalAttack"},
		{Axis::VerticalAttack, L"VerticalAttack"},
	}
);

NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(AxisInfo, axis, keyMap, sensitivity, value);

NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(AnimationFrame, texturePath, textureCoord);

void to_json(json& j, const AnimationClip& animationClip);

void from_json(const json& j, AnimationClip& animationClip);