#pragma once

class Animator : public std::enable_shared_from_this<Animator>
{
public:
	Animator() : currentAnimationClip(nullptr), target(nullptr), isPlaying(false), currentFrame(0), totalFrame(0), checkFrame(0), frameDuration(0.f), accumTime(0.f), animationSpeed(1.f) {}
	~Animator() = default;

	void Init();

	void Update(float deltaTime);

	void Draw(sf::RenderWindow& window) {}

	void Release() {}

	const std::wstring& GetCurrentClipId() const;
	bool IsPlaying() const { return isPlaying; }
	
	void SetTarget(std::shared_ptr<sf::Sprite> target) { shared_from_this()->target = target; }
	void SetAnimationFrame(const AnimationFrame& animationFrame);
	void SetAnimationSpeed(const float animationSpeed);

	void AddvvAnimationEvent(const std::wstring& animationId, const int frameIndex, const std::function<void()>& vvAction);
	void ClearAnimationEvent() { animationEvents.clear(); }

	void Play(const std::wstring& animationClipId, const bool clearQueue = true);
	void PushPlayQueue(const std::wstring& animationClipId);
	void Stop();

private:
	static const std::wstring none;

	std::unordered_map<std::pair<std::wstring, int>, AnimationEvent, AnimationEventHash> animationEvents;
	std::queue<std::wstring> playAniClipIdQueue;

	std::shared_ptr<AnimationClip> currentAnimationClip;
	std::shared_ptr<sf::Sprite> target;

	bool isPlaying;

	int currentFrame;
	int totalFrame;
	int checkFrame;

	float frameDuration;
	float accumTime;
	float animationSpeed;
};