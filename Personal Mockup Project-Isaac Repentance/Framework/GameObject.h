#pragma once

class GameObject
{
public:
	GameObject(const std::wstring& name);
	virtual ~GameObject() = default;

	virtual void Init() = 0;

	virtual void Update(float deltaTime) = 0;

	virtual void Draw(sf::RenderWindow& window) = 0;

	virtual void Release() = 0;

	virtual sf::FloatRect GetLocalBounds() const = 0;
	virtual sf::FloatRect GetGlobalBounds() const = 0;

	virtual void SetPosition(const sf::Vector2f& position) = 0;
	virtual void SetOrigin(const Origins originPreset) = 0;
	virtual void SetOrigin(const sf::Vector2f& newOrigin) = 0;
	virtual void SetRotation(float angle) = 0;
	virtual void SetScale(const sf::Vector2f& scale) = 0;

	// const를 붙이면 string 래퍼런스로 반환 가능
	const std::wstring& GetName() const { return name; }
	sf::Vector2f GetPosition() const { return position; }
	sf::Vector2f GetOrigin() const { return origin; }
	float GetRotation() const { return rotation; }
	sf::Vector2f GetScale() const { return scale; }

	void SetName(const std::wstring& name) { this->name = name; }

	bool IsActive() const { return active; }
	void SetActive(const bool isActive) { active = isActive; }

	SortingLayers sortingLayer = SortingLayers::None;

protected:
	std::wstring name;

	sf::Vector2f position;
	float rotation;
	sf::Vector2f scale;

	sf::Vector2f origin;
	Origins originPreset;
	
	bool active;
};