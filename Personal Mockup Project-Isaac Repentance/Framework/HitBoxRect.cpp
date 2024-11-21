#include "pch.h"

HitBoxRect::HitBoxRect(const sf::Vector2f& rectSize)
{
	hitBox.setFillColor(sf::Color::Transparent);
	hitBox.setOutlineColor(sf::Color::Green);
	hitBox.setOutlineThickness(1.f);

	hitBox.setSize(rectSize);

	Utils::SetOrigin(hitBox, Origins::MC);
}

void HitBoxRect::Draw(sf::RenderWindow& window)
{
	if (Variables::isDrawHitBox)
		window.draw(hitBox);
}

void HitBoxRect::UpdateHitBox(const sf::Transformable& body)
{
	hitBox.setPosition(body.getPosition());
	hitBox.setScale(body.getScale());
}