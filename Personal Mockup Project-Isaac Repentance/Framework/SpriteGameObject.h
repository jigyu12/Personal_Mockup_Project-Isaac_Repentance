#pragma once

class SpriteGameObject : public GameObject
{
public:
	SpriteGameObject(const std::wstring& name, const std::wstring& texturePath);
	virtual ~SpriteGameObject() = default;

	virtual void Init() override = 0;

	virtual void Update(float deltaTime) override = 0;

	virtual void Draw(sf::RenderWindow& window) override = 0;

	virtual void Release() override = 0;

	sf::FloatRect GetLocalBounds() const;
	sf::FloatRect GetGlobalBounds() const;
	std::shared_ptr<HitBox> GetHitBox() const { return hitbox; }

	void SetPosition(const sf::Vector2f& position);
	void SetOrigin(const Origins originPreset);
	void SetOrigin(const sf::Vector2f& newOrigin);
	void SetRotation(float angle);
	void SetScale(const sf::Vector2f& scale);

protected:
	std::wstring texturePath;

	sf::Sprite body;

	std::shared_ptr<HitBox> hitbox;
};