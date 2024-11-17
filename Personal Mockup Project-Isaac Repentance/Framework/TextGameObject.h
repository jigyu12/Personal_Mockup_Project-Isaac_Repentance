#pragma once

class TextGameObject : public GameObject
{
public:
	TextGameObject(const std::wstring& name, const std::wstring& fontPath, const std::wstring& stringPath, const std::wstring& stringId);
	virtual ~TextGameObject() = default;

	virtual void Init() override = 0;

	virtual void Update(float deltaTime) override = 0;

	virtual void Draw(sf::RenderWindow& window) override = 0;

	virtual void Release() override = 0;

	sf::FloatRect GetLocalBounds() const;
	sf::FloatRect GetGlobalBounds() const;

	void SetPosition(const sf::Vector2f& position);
	void SetOrigin(const Origins originPreset);
	void SetOrigin(const sf::Vector2f& newOrigin);
	void SetRotation(float angle);
	void SetScale(const sf::Vector2f& scale);
	void SetFont(const std::wstring& fontPath, bool notUnLoadByUnLoadAll);
	void SetTextSize(const int size);
	void SetTextColor(const sf::Color& color);
	void SetTextStringById(const std::wstring& id, const int index);

protected:
	std::wstring fontPath;
	std::wstring stringPath;
	std::wstring stringId;

	sf::Text text;
	std::shared_ptr<sf::Font> fontPtr;
};