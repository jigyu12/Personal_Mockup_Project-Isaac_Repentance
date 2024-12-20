#pragma once

class TextGameObject : public GameObject
{
public:
	TextGameObject(const std::wstring& name = L"TextGameObject");
	virtual ~TextGameObject() = default;

	virtual void Init() override = 0;
	virtual void Enter() override = 0;

	virtual void Update(float deltaTime) override = 0;
	virtual void FixedUpdate(float deltaTime) override = 0;

	virtual void Draw(sf::RenderWindow& window) override = 0;
	virtual void PostDraw() override = 0;

	virtual void Exit() override = 0;
	virtual void Release() override = 0;

	virtual sf::FloatRect GetLocalBounds() const override;
	virtual sf::FloatRect GetGlobalBounds() const override;

	virtual void SetPosition(const sf::Vector2f& pos) override;
	virtual void SetOrigin(const Origins preset) override;
	virtual void SetOrigin(const sf::Vector2f& newOrigin) override;
	virtual void SetRotation(float angle) override;
	virtual void SetScale(const sf::Vector2f& setScale) override;

	void SetFont(const std::wstring& setFontPath, const bool notUnLoadByUnLoadAll = false);
	void SetTextSize(const int size);
	void SetTextColor(const sf::Color& color);
	void SetTextString(const std::wstring& setStringPath, const std::wstring& id, const int index);

protected:
	std::wstring fontPath;
	std::wstring stringPath;
	std::wstring stringId;

	std::shared_ptr<sf::Text> textPtr;
	std::shared_ptr<sf::Font> fontPtr;
};