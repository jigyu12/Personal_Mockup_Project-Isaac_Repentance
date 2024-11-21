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

void TextGameObject::SetPosition(const sf::Vector2f& position)
{
	std::dynamic_pointer_cast<TextGameObject>(shared_from_this())->position = position;
	textPtr->setPosition(position);
}

void TextGameObject::SetOrigin(const Origins originPreset)
{
	if (originPreset == Origins::Custom)
	{
		std::wcerr << L"Cannot assign custom originPreset for text." << std::endl;

		return;
	}
	std::dynamic_pointer_cast<TextGameObject>(shared_from_this())->originPreset = originPreset;
	origin = Utils::SetOrigin(*textPtr, originPreset);
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

void TextGameObject::SetScale(const sf::Vector2f& scale)
{
	std::dynamic_pointer_cast<TextGameObject>(shared_from_this())->scale = scale;
	textPtr->setScale(scale);
}

void TextGameObject::SetFont(const std::wstring& fontPath, const bool notUnLoadByUnLoadAll)
{
	auto fontPtr = RES_FONT_MGR.Get(fontPath, notUnLoadByUnLoadAll);
	if (!fontPtr)
	{
		std::wcerr << L"fontPtr was nullptr." << std::endl;

		return;
	}
	else
	{
		std::dynamic_pointer_cast<TextGameObject>(shared_from_this())->fontPath = fontPath;
		std::dynamic_pointer_cast<TextGameObject>(shared_from_this())->fontPtr = fontPtr;
		textPtr->setFont(*(std::dynamic_pointer_cast<TextGameObject>(shared_from_this())->fontPtr));
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

void TextGameObject::SetTextString(const std::wstring& stringPath, const std::wstring& id, const int index)
{
	auto csvMapPtr = FILE_MGR.LoadByCsv(stringPath);
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
	
	std::dynamic_pointer_cast<TextGameObject>(shared_from_this())->stringPath = stringPath;
	stringId = id;
	textPtr->setString((*csvMapPtr)[stringId][index]);
	SetOrigin(originPreset);
}