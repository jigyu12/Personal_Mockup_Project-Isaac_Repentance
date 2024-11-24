#pragma once

class HitBoxCircle : public HitBox
{
public:
	HitBoxCircle(const float radius);

	void Draw(sf::RenderWindow& window) override;
	void UpdateHitBox(const sf::Transformable& body) override;
	void SetOutlineColor(const sf::Color& color) override { hitBox.setOutlineColor(color); }

	sf::CircleShape GetHitBox() const { return hitBox; }
	sf::FloatRect GetHitBoxGlobalRect() const { return hitBox.getGlobalBounds(); }
	float GetRadius() const { return hitBox.getRadius(); }

	void SetRadius(float r) { hitBox.setRadius(r); }

protected:
	sf::CircleShape hitBox;
};