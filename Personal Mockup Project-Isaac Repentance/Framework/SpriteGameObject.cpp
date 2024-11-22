#include "pch.h"

SpriteGameObject::SpriteGameObject(const std::wstring& name)
	: GameObject(name), texturePath(L"Invaild texturePath"), spritePtr(std::make_shared<sf::Sprite>()), spriteTexturePtr(nullptr)
{
}

sf::FloatRect SpriteGameObject::GetLocalBounds() const
{
	return spritePtr->getLocalBounds();
}

sf::FloatRect SpriteGameObject::GetGlobalBounds() const
{
	return spritePtr->getGlobalBounds();
}

void SpriteGameObject::SetPosition(const sf::Vector2f& pos)
{
	position = pos;
	spritePtr->setPosition(position);
}

void SpriteGameObject::SetOrigin(const Origins preset)
{
	if (preset == Origins::Custom)
	{
		std::wcerr << L"Cannot assign custom originPreset for sprite." << std::endl;
		
		return;
	}
	originPreset = preset;
	origin = Utils::SetOrigin(*spritePtr, preset);
}

void SpriteGameObject::SetOrigin(const sf::Vector2f& newOrigin)
{
	originPreset = Origins::Custom;
	origin = newOrigin;
	spritePtr->setOrigin(origin);
}

void SpriteGameObject::SetRotation(float angle)
{
	rotation = angle;
	spritePtr->setRotation(angle);
}

void SpriteGameObject::SetScale(const sf::Vector2f& setScale)
{
	scale = setScale;
	spritePtr->setScale(scale);
}

bool SpriteGameObject::SetTexture(const std::wstring& setTexturePath, const bool notUnLoadByUnLoadAll)
{
	auto texturePtr = RES_TEXTURE_MGR.Get(setTexturePath, notUnLoadByUnLoadAll);
	if (!texturePtr)
	{
		std::wcerr << L"texturePtr was nullptr." << std::endl;

		return false;
	}
	else
	{
		texturePath = setTexturePath;
		spriteTexturePtr = texturePtr;

		return true;
	}
}

void SpriteGameObject::SetSpriteTexture(const std::wstring& texturePath, const bool notUnLoadByUnLoadAll)
{
	if(SetTexture(texturePath, notUnLoadByUnLoadAll))
		spritePtr->setTexture(*spriteTexturePtr);
	else
		std::wcerr << L"SetSpriteTexture failed." << std::endl;
}