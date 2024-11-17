#include "pch.h"

SpriteGameObject::SpriteGameObject(const std::wstring& name, const std::wstring& texturePath)
	: GameObject(name), texturePath(texturePath)
{
}

sf::FloatRect SpriteGameObject::GetLocalBounds() const
{
	return body.getLocalBounds();
}

sf::FloatRect SpriteGameObject::GetGlobalBounds() const
{
	return body.getGlobalBounds();
}

void SpriteGameObject::SetPosition(const sf::Vector2f& position)
{
	this->position = position;
	body.setPosition(position);
}

void SpriteGameObject::SetOrigin(const Origins originPreset)
{
	if (originPreset == Origins::Custom)
	{
		std::wcerr << L"Cannot assign custom originPreset for sprite" << std::endl;
		
		return;
	}
	this->originPreset = originPreset;
	origin = Utils::SetOrigin(body, originPreset);
}

void SpriteGameObject::SetOrigin(const sf::Vector2f& newOrigin)
{
	originPreset = Origins::Custom;
	origin = newOrigin;
	body.setOrigin(origin);
}

void SpriteGameObject::SetRotation(float angle)
{
	rotation = angle;
	body.setRotation(angle);
}

void SpriteGameObject::SetScale(const sf::Vector2f& scale)
{
	this->scale = scale;
	body.setScale(scale);
}

void SpriteGameObject::SetBodyTexture(const std::wstring& texturePath, bool notUnLoadByUnLoadAll)
{
	auto texturePtr = RES_TEXTURE_MGR.Get(texturePath, notUnLoadByUnLoadAll);
	if (!texturePtr)
	{
		std::wcerr << L"texturePtr was nullptr" << std::endl;
	}
	else
	{
		this->texturePath = texturePath;
		bodyTexturePtr = texturePtr;
		body.setTexture(*bodyTexturePtr);
	}
}