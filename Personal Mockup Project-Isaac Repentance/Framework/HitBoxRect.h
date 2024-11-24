#pragma once

class HitBoxRect : public HitBox
{
public:
	HitBoxRect(const sf::Vector2f& rectSize);

	void Draw(sf::RenderWindow& window) override;
	void UpdateHitBox(const sf::Transformable& body) override;
	void SetOutlineColor(const sf::Color& color) override { hitBox.setOutlineColor(color); }

	sf::RectangleShape GetHitBox() const { return hitBox; }
	sf::FloatRect GetHitBoxGlobalRect() const { return hitBox.getGlobalBounds(); }

protected:
	sf::RectangleShape hitBox;
};