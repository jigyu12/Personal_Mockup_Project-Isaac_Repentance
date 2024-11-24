#pragma once

class HitBox;
class HitBoxRect;
class HitBoxCircle;

class Utils
{
public:
	static void Init();

	static int RandomRange(int min, int max);
	static float RandomRange(float min, float max);

	static sf::Vector2f SetOrigin(sf::Transformable& object, Origins originPreset, const sf::FloatRect bound);
	static sf::Vector2f SetOrigin(sf::Shape& object, Origins originPreset);
	static sf::Vector2f SetOrigin(sf::Text& object, Origins originPreset);
	static sf::Vector2f SetOrigin(sf::Sprite& object, Origins originPreset);

	static float Clamp(const float value, const float min, const float max);
	static float Magnitude(const sf::Vector2f& vector);
	static float Distance(const sf::Vector2f& vector1, const sf::Vector2f& vector2);
	static void Normalize(sf::Vector2f& vector);
	static sf::Vector2f GetNormalized(const sf::Vector2f& vector);

	static bool CheckCollision(const std::shared_ptr<HitBox> hitBox1, const std::shared_ptr<HitBox> hitBox2);
	static bool CheckRectCircleCollision(const std::shared_ptr<HitBoxRect> rect, const std::shared_ptr<HitBoxCircle> circle);

	static sf::Vector2f ScreenToWorld(const sf::Vector2i& screenPos, const sf::View& worldView);
	static sf::Vector2i WorldToScreen(const sf::Vector2f& worldPos, const sf::View& worldView);
	static sf::Vector2f ScreenToUi(const sf::Vector2i& screenPos, const sf::View& uiView);
	static sf::Vector2i UiToScreen(const sf::Vector2f& worldPos, const sf::View& uiView);

	static std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;

private:
	static std::mt19937 generator;
	static const float PI;
};