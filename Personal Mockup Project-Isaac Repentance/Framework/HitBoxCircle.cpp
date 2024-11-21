#include "pch.h"

HitBoxCircle::HitBoxCircle(const float radius)
{
	hitBox.setFillColor(sf::Color::Transparent);
	hitBox.setOutlineColor(sf::Color::Green);
	hitBox.setOutlineThickness(1.f);

	hitBox.setRadius(radius);

	Utils::SetOrigin(hitBox, Origins::MC);
}

void HitBoxCircle::Draw(sf::RenderWindow& window)
{
	if (Variables::isDrawHitBox)
		window.draw(hitBox);
}

void HitBoxCircle::UpdateHitBox(const sf::Transformable& body)
{
	hitBox.setPosition(body.getPosition());
	hitBox.setScale(body.getScale());
}