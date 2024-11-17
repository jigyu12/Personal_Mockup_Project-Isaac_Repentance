#include "pch.h"

TextGameObject::TextGameObject(const std::wstring& name, const std::wstring& fontPath, const std::wstring& stringPath, const std::wstring& stringId)
	: GameObject(name), fontPath(fontPath), stringPath(stringPath), stringId(stringId)
{
}

sf::FloatRect TextGameObject::GetLocalBounds() const
{
	return text.getLocalBounds();
}

sf::FloatRect TextGameObject::GetGlobalBounds() const
{
	return text.getGlobalBounds();
}

void TextGameObject::SetPosition(const sf::Vector2f& position)
{
	this->position = position;
	text.setPosition(position);
}

void TextGameObject::SetOrigin(const Origins originPreset)
{
	if (originPreset == Origins::Custom)
	{
		std::wcerr << L"Cannot assign custom originPreset for text" << std::endl;

		return;
	}
	this->originPreset = originPreset;
	origin = Utils::SetOrigin(text, originPreset);
}

void TextGameObject::SetOrigin(const sf::Vector2f& newOrigin)
{
	originPreset = Origins::Custom;
	origin = newOrigin;
	text.setOrigin(origin);
}

void TextGameObject::SetRotation(float angle)
{
	rotation = angle;
	text.setRotation(angle);
}

void TextGameObject::SetScale(const sf::Vector2f& scale)
{
	this->scale = scale;
	text.setScale(scale);
}

void TextGameObject::SetFont(const std::wstring& fontPath, bool notUnLoadByUnLoadAll)
{
	auto fontPtr = RES_FONT_MGR.Get(fontPath, notUnLoadByUnLoadAll);
	if (!fontPtr)
	{
		std::wcerr << L"fontPtr was nullptr" << std::endl;
	}
	else
	{
		this->fontPath = fontPath;
		this->fontPtr = fontPtr;
		text.setFont(*(this->fontPtr));
	}
}

void TextGameObject::SetTextSize(const int size)
{
	text.setCharacterSize(size);
}

void TextGameObject::SetTextColor(const sf::Color& color)
{
	text.setFillColor(color);
}

void TextGameObject::SetTextStringById(const std::wstring& id, const int index)
{
	auto csvMap = FILE_MGR.LoadByCsv(stringPath);
	if ((*csvMap).find(id) == (*csvMap).end() || index < 0 || index >= (*csvMap)[stringId].size())
	{
		std::wcerr << L"Cannot set text string by id: invaild id or index" << std::endl;

		return;
	}
	else
	{
		stringId = id;
		text.setString((*csvMap)[stringId][index]);
		SetOrigin(originPreset);
	}
}