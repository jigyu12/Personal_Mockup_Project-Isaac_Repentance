#pragma once

class SpriteGameObject : public GameObject
{
public:
	SpriteGameObject(const std::wstring& name = L"SpriteGameObject");
	virtual ~SpriteGameObject() = default;

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

	virtual bool SetTexture(const std::wstring& setTexturePath, const bool notUnLoadByUnLoadAll = false);
	virtual void SetSpriteTexture(const std::wstring& texturePath, const bool notUnLoadByUnLoadAll = false);

	std::shared_ptr<HitBox> GetHitBox() const { return hitbox; }
	
protected:
	std::wstring texturePath;

	std::shared_ptr<sf::Sprite> spritePtr;
	std::shared_ptr<sf::Texture> spriteTexturePtr;

	std::shared_ptr<HitBox> hitbox;
};