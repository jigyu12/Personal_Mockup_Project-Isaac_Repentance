#pragma once

#include "../Framework/SpriteGameObject.h"
#include "Player.h"

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
	std::shared_ptr<sf::Sprite> sprite2Ptr;
	std::shared_ptr<sf::Sprite> sprite3Ptr;
	std::shared_ptr<sf::Sprite> sprite4Ptr;

	std::shared_ptr<sf::Texture> spriteControlTexturePtr;
	std::shared_ptr<sf::Sprite> spriteControlPtr;

	sf::FloatRect movableBoundRect;

	std::wstring roomTextureCsvPath;

	bool isDrawspriteControl;
};