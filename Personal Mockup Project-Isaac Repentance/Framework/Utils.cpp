#include "pch.h"

std::wstring_convert<std::codecvt_utf8<wchar_t>> Utils::converter;

sf::Vector2f Utils::SetOrigin(sf::Transformable& object, Origins originPreset, const sf::FloatRect bound)
{
    sf::Vector2f newOrigin(bound.width, bound.height);

    newOrigin.x *= ((int)originPreset % 3) * 0.5f;
    newOrigin.y *= ((int)originPreset / 3) * 0.5f;

    object.setOrigin(newOrigin);

    return newOrigin;
}

sf::Vector2f Utils::SetOrigin(sf::Shape& object, Origins originPreset)
{
    return SetOrigin(object, originPreset, object.getLocalBounds());
}

sf::Vector2f Utils::SetOrigin(sf::Text& object, Origins originPreset)
{
    return SetOrigin(object, originPreset, object.getLocalBounds());
}

sf::Vector2f Utils::SetOrigin(sf::Sprite& object, Origins originPreset)
{
    return SetOrigin(object, originPreset, object.getLocalBounds());
}

float Utils::Clamp(const float value, const float min, const float max)
{
    if (value < min)
        return min;

    if (value > max)
        return max;

    return value;
}

float Utils::Magnitude(const sf::Vector2f& vector)
{
    return std::sqrtf(vector.x * vector.x + vector.y * vector.y);
}

float Utils::Distance(const sf::Vector2f& vector1, const sf::Vector2f& vector2)
{
    return Magnitude(vector2 - vector1);
}

bool Utils::CheckCollision(const std::shared_ptr<HitBox> hitBox1, const std::shared_ptr<HitBox> hitBox2)
{
    // 사각형 vs 사각형 충돌
    if (auto rect1 = std::dynamic_pointer_cast<HitBoxRect>(hitBox1)) 
    {
        if (auto rect2 = std::dynamic_pointer_cast<HitBoxRect>(hitBox2)) 
        {
            return rect1->GetHitBox().getGlobalBounds().intersects(rect2->GetHitBox().getGlobalBounds());
        }
    }

    // 원 vs 원 충돌
    if (auto circle1 = std::dynamic_pointer_cast<HitBoxCircle>(hitBox1)) 
    {
        if (auto circle2 = std::dynamic_pointer_cast<HitBoxCircle>(hitBox2)) 
        {
            sf::Vector2f cirCenter1 = circle1->GetHitBox().getPosition();
            sf::Vector2f cirCenter2 = circle2->GetHitBox().getPosition();

            float distance = Distance(cirCenter1, cirCenter2);
            float radiusSum = circle1->GetHitBox().getRadius() + circle2->GetHitBox().getRadius();

            return distance < radiusSum;
        }
    }

    // 사각형 vs 원 충돌
    if (auto rect = std::dynamic_pointer_cast<HitBoxRect>(hitBox1)) 
    {
        if (auto circle = std::dynamic_pointer_cast<HitBoxCircle>(hitBox2)) 
        {
            return CheckRectCircleCollision(rect, circle);
        }
    }
    else if (auto circle = std::dynamic_pointer_cast<HitBoxCircle>(hitBox1)) 
    {
        if (auto rect = std::dynamic_pointer_cast<HitBoxRect>(hitBox2)) 
        {
            return CheckRectCircleCollision(rect, circle);
        }
    }

    std::wcerr << L"collision Error!" << std::endl;
    return false;
}

bool Utils::CheckRectCircleCollision(const std::shared_ptr<HitBoxRect> rect, const std::shared_ptr<HitBoxCircle> circle)
{
    sf::FloatRect rectBounds = rect->GetHitBox().getGlobalBounds();
    sf::Vector2f circleCenter = circle->GetHitBox().getPosition();
    float circleRadius = circle->GetHitBox().getRadius();

    // 원의 중심을 사각형의 경계로 클램프
    float closestX = Utils::Clamp(circleCenter.x, rectBounds.left, rectBounds.left + rectBounds.width);
    float closestY = Utils::Clamp(circleCenter.y, rectBounds.top, rectBounds.top + rectBounds.height);

    // 원의 중심과 클램프된 점 사이의 거리가 원의 반지름보다 작으면 충돌
    float distance = Distance(circleCenter, sf::Vector2f(closestX, closestY));

    return distance < circleRadius;
}