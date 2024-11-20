#pragma once

class AnimationClip
{
public:
	AnimationClip() {}
	AnimationClip(const std::wstring& id, const AnimationLoopTypes loopType, const int fps, const std::vector<AnimationFrame>& frames) : id(id), loopType(loopType), fps(fps), frames(frames) {}

	bool loadFromFile(const std::string& filePath);

private:
	std::wstring id;
	AnimationLoopTypes loopType;
	int fps;
	std::vector<AnimationFrame> frames;

	friend void to_json(json& j, const AnimationClip& clip);
	friend void from_json(const json& j, AnimationClip& clip);
};