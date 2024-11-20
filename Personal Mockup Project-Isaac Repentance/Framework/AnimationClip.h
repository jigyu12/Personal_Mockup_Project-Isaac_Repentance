#pragma once

class AnimationClip
{
public:
	AnimationClip() : id(L"Invaild Id"), loopType(AnimationLoopTypes::None), fps(0) {}
	AnimationClip(const std::wstring& id, const AnimationLoopTypes loopType, const int fps, const std::vector<AnimationFrame>& frames) : id(id), loopType(loopType), fps(fps), frames(frames) {}

	bool loadFromFile(const std::string& filePath);
	
	const std::wstring& GetId() const { return id; }
	AnimationLoopTypes GetLoopType() const { return loopType; }
	int GetFps() const { return fps; }
	const std::vector<AnimationFrame>& GetFrames() const { return frames; }

	void SetId(const std::wstring& id) { this->id = id; }
	void SetLoopType(const AnimationLoopTypes loopType) { this->loopType = loopType; }
	void SetFps(const int fps) { this->fps = fps; }
	void SetFrames(const std::vector<AnimationFrame>& frames) { this->frames = frames; }

private:
	std::wstring id;
	AnimationLoopTypes loopType;
	int fps;
	std::vector<AnimationFrame> frames;

	friend void to_json(json& j, const AnimationClip& clip);
	friend void from_json(const json& j, AnimationClip& clip);
};