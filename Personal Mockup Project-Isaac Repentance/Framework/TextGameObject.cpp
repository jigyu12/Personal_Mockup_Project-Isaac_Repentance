#include "pch.h"

TextGameObject::TextGameObject(const std::wstring& name)
	: GameObject(name), fontPath(L"Invaild fontPath"), stringPath(L"Invaild stringPath"), stringId(L"Invaild stringId"), textPtr(std::make_shared<sf::Text>()), fontPtr(nullptr)
{
}

sf::FloatRect TextGameObject::GetLocalBounds() const
{
	return textPtr->getLocalBounds();
}

sf::FloatRect TextGameObject::GetGlobalBounds() const
{
	return textPtr->getGlobalBounds();
}

void TextGameObject::SetPosition(const sf::Vector2f& pos)
{
	position = pos;
	textPtr->setPosition(position);
}

void TextGameObject::SetOrigin(const Origins preset)
{
	if (preset == Origins::Custom)
	{
		std::wcerr << L"Cannot assign custom originPreset for text." << std::endl;

		return;
	}
	originPreset = preset;
	origin = Utils::SetOrigin(*textPtr, preset);
}

void TextGameObject::SetOrigin(const sf::Vector2f& newOrigin)
{
	originPreset = Origins::Custom;
	origin = newOrigin;
	textPtr->setOrigin(origin);
}

void TextGameObject::SetRotation(float angle)
{
	rotation = angle;
	textPtr->setRotation(angle);
}

void TextGameObject::SetScale(const sf::Vector2f& setScale)
{
	scale = setScale;
	textPtr->setScale(setScale);
}

void TextGameObject::SetFont(const std::wstring& setFontPath, const bool notUnLoadByUnLoadAll)
{
	auto setFontPtr = RES_FONT_MGR.Get(setFontPath, notUnLoadByUnLoadAll);
	if (!setFontPtr)
	{
		std::wcerr << L"setFontPtr was nullptr." << std::endl;

		return;
	}
	else
	{
		fontPath = setFontPath;
		fontPtr = setFontPtr;
		textPtr->setFont(*fontPtr);
	}
}

void TextGameObject::SetTextSize(const int size)
{
	textPtr->setCharacterSize(size);
}

void TextGameObject::SetTextColor(const sf::Color& color)
{
	textPtr->setFillColor(color);
}

void TextGameObject::SetTextString(const std::wstring& setStringPath, const std::wstring& id, const int index)
{
	auto csvMapPtr = FILE_MGR.LoadByCsv(setStringPath);
	if (!csvMapPtr)
	{
		std::wcerr << L"csvMapPtr was nullptr." << std::endl;

		return;
	}
	
	if ((*csvMapPtr).find(id) == (*csvMapPtr).end() || index < 0 || index >= (*csvMapPtr)[stringId].size())
	{
		std::wcerr << L"Cannot set text string by id: invaild id or index." << std::endl;

		return;
	}
	
	stringPath = setStringPath;
	stringId = id;
	textPtr->setString((*csvMapPtr)[stringId][index]);
	SetOrigin(originPreset);
}