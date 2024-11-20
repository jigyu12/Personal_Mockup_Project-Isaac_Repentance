#include "pch.h"

HitBoxCircle::HitBoxCircle(const float radius)
{
	hitBox.setFillColor(sf::Color::Transparent);
	hitBox.setOutlineColor(sf::Color::Green);
	hitBox.setOutlineThickness(1.f);

	hitBox.setRadius(radius);
}

void HitBoxCircle::Draw(sf::RenderWindow& window)
{
	if (Variables::isDrawHitBox)
		window.draw(hitBox);
}

void HitBoxCircle::UpdateHitBox(const sf::Transformable& body)
{
	hitBox.setOrigin(body.getOrigin());
	hitBox.setPosition(body.getPosition());
	hitBox.setScale(body.getScale());
}