#pragma once

class HitBox;
class HitBoxRect;
class HitBoxCircle;

class Utils
{
public:
	static sf::Vector2f SetOrigin(sf::Transformable& object, Origins originPreset, const sf::FloatRect bound);
	static sf::Vector2f SetOrigin(sf::Shape& object, Origins originPreset);
	static sf::Vector2f SetOrigin(sf::Text& object, Origins originPreset);
	static sf::Vector2f SetOrigin(sf::Sprite& object, Origins originPreset);

	static float Clamp(const float value, const float min, const float max);
	static float Magnitude(const sf::Vector2f& vector);
	static float Distance(const sf::Vector2f& vector1, const sf::Vector2f& vector2);
	
	static bool CheckCollision(const std::shared_ptr<HitBox> hitBox1, const std::shared_ptr<HitBox> hitBox2);
	static bool CheckRectCircleCollision(const std::shared_ptr<HitBoxRect> rect, const std::shared_ptr<HitBoxCircle> circle);

	static std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;
};