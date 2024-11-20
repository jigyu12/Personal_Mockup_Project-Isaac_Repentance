#include "pch.h"

void to_json(json& j, const sf::Keyboard::Key& key)
{
	j = static_cast<int>(key);
}

void from_json(const json& j, sf::Keyboard::Key& key)
{
	key = static_cast<sf::Keyboard::Key>(j.get<int>());
}

void to_json(json& j, const AnimationClip& animationClip) 
{
    j = json
    {
        {"id", animationClip.id},
        {"loopType", animationClip.loopType},
        {"fps", animationClip.fps},
        {"frames", animationClip.frames}
    };
}

void from_json(const json& j, AnimationClip& animationClip) 
{
    j.at("id").get_to(animationClip.id);
    j.at("loopType").get_to(animationClip.loopType);
    j.at("fps").get_to(animationClip.fps);
    j.at("frames").get_to(animationClip.frames);
}