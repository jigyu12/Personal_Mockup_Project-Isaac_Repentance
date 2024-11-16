#include "pch.h"

GameObject::GameObject(const std::wstring& name)
	: name(name), position({ 0.f, 0.f }), rotation(0.f), scale({ 1.f, 1.f }), origin({0.f, 0.f}), originPreset(Origins::TL), active(true)
{
}