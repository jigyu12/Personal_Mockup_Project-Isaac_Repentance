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

void SpriteGameObject::SetPosition(const sf::Vector2f& position)
{
	std::dynamic_pointer_cast<SpriteGameObject>(shared_from_this())->position = position;
	spritePtr->setPosition(position);
}

void SpriteGameObject::SetOrigin(const Origins originPreset)
{
	if (originPreset == Origins::Custom)
	{
		std::wcerr << L"Cannot assign custom originPreset for sprite." << std::endl;
		
		return;
	}
	std::dynamic_pointer_cast<SpriteGameObject>(shared_from_this())->originPreset = originPreset;
	origin = Utils::SetOrigin(*spritePtr, originPreset);
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

void SpriteGameObject::SetScale(const sf::Vector2f& scale)
{
	std::dynamic_pointer_cast<SpriteGameObject>(shared_from_this())->scale = scale;
	spritePtr->setScale(scale);
}

bool SpriteGameObject::SetTexture(const std::wstring& texturePath, const bool notUnLoadByUnLoadAll)
{
	auto texturePtr = RES_TEXTURE_MGR.Get(texturePath, notUnLoadByUnLoadAll);
	if (!texturePtr)
	{
		std::wcerr << L"texturePtr was nullptr." << std::endl;

		return false;
	}
	else
	{
		std::dynamic_pointer_cast<SpriteGameObject>(shared_from_this())->texturePath = texturePath;
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