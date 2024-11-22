#pragma once

class GameObject
{
public:
	GameObject(const std::wstring& name = L"GameObject");
	virtual ~GameObject() = default;

	virtual void Init() = 0;
	virtual void Enter() = 0;

	virtual void Update(float deltaTime) = 0;
	virtual void FixedUpdate(float deltaTime) = 0;

	virtual void Draw(sf::RenderWindow& window) = 0;
	virtual void PostDraw() = 0;

	virtual void Exit() = 0;
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
	SortingLayers GetSortingLayers() const { return sortingLayer; }
	int GetsortingOrderUi() const { return sortingOrderUi; }
	int GetsortingOrderBack() const { return sortingOrderBack; }

	void SetName(const std::wstring& setName) { name = setName; }
	void SetSortingLayers(const SortingLayers setSortingLayer) { sortingLayer = setSortingLayer; }
	void SetSortingOrderUi(const int setSortingOrderUi) { sortingOrderUi = setSortingOrderUi; }
	void SetSortingOrderBack(const int setSortingOrderBack) { sortingOrderBack = setSortingOrderBack; }

	bool IsActive() const { return active; }
	void SetActive(const bool isActive) { active = isActive; }

protected:
	std::wstring name;

	sf::Vector2f position;
	float rotation;
	sf::Vector2f scale;

	sf::Vector2f origin;
	Origins originPreset;
	
	bool active;

	SortingLayers sortingLayer;
	int sortingOrderUi;
	int sortingOrderBack;
};