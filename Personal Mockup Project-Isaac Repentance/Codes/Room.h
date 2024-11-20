#pragma once

#include "../Framework/SpriteGameObject.h"

class Room : public SpriteGameObject
{
public:
	Room(const std::wstring& name = L"Room");
	virtual ~Room() = default;

	void Init() override;
	void Enter() override;

	void Update(float deltaTime) override;
	void FixedUpdate(float deltaTime) override;

	void Draw(sf::RenderWindow& window) override;
	void PostDraw() override;

	void Exit() override;
	void Release() override;

	void SetIsDrawspriteControl(const bool isDraw) { isDrawspriteControl = isDraw; }

protected:
	sf::Sprite sprite2;
	sf::Sprite sprite3;
	sf::Sprite sprite4;

	sf::Texture spriteControlTexture;
	sf::Sprite spriteControl;

	sf::FloatRect movableBoundRect;

	std::wstring roomTextureCsvPath;

	bool isDrawspriteControl;
};