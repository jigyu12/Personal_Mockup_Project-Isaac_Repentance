#pragma once

class HitBox
{
protected:
	virtual void Draw(sf::RenderWindow& window) = 0;
	virtual void SetOutlineColor(const sf::Color& color) = 0;
	virtual void UpdateHitBox(const sf::Transformable& body) = 0;
};