#include "pch.h"

const std::wstring Animator::none = L"Invaild Id";

void Animator::Init()
{
	ClearAnimationEvent();
	while (!playAniClipQueue.empty())
	{
		playAniClipQueue.pop();
	}

	currentAnimationClip = nullptr; 
	target = nullptr;

	isPlaying = false;

	currentFrame = 0;
	totalFrame = 0; 
	checkFrame = 0;

	frameDuration = 0.f; 
	accumTime = 0.f; 
	animationSpeed = 1.f;
}

void Animator::Update(float deltaTime)
{
	if (!isPlaying)
		return;

	accumTime += deltaTime * std::fabs(animationSpeed);
	if (accumTime < frameDuration)
		return;

	currentFrame += animationSpeed > 0.f ? 1 : -1;
	accumTime = 0.f;

	if (currentFrame == checkFrame)
	{
		if (!playAniClipQueue.empty())
		{
			auto clip = playAniClipQueue.front();
			Play(clip, false);
			playAniClipQueue.pop();

			return;
		}

		switch (currentAnimationClip->GetLoopType())
		{
		case AnimationLoopTypes::Single:
			currentFrame = animationSpeed > 0.f ? totalFrame - 1 : 0;
				break;
		case AnimationLoopTypes::Loop:
			currentFrame = animationSpeed > 0.f ? 0 : totalFrame - 1;
				break;
		}
	}

	SetAnimationFrame(currentAnimationClip->GetFrames()[currentFrame]);

	auto find = animationEvents.find({ currentAnimationClip->GetId(), currentFrame});
	if (find != animationEvents.end())
	{
		auto& ev = find->second;
		for (auto& vvAction : ev.vvActions)
		{
			if (vvAction)
			{
				vvAction();
			}
		}
	}
}

const std::wstring& Animator::GetCurrentClipId() const
{
	if (!currentAnimationClip)
		return none;

	return currentAnimationClip->GetId();
}

void Animator::SetAnimationFrame(const AnimationFrame& animationFrame)
{
	target->setTexture(*(RES_TEXTURE_MGR.Get(animationFrame.texturePath)));
	target->setTextureRect({ animationFrame.textureCoord.left, animationFrame.textureCoord.top, animationFrame.textureCoord.width, animationFrame.textureCoord.height });
}

void Animator::SetAnimationSpeed(const float setAnimationSpeed)
{
	animationSpeed = setAnimationSpeed;
	checkFrame = animationSpeed > 0.f ? totalFrame : -1;
}

void Animator::AddvvAnimationEvent(const std::wstring& animationId, const int frameIndex, const std::function<void()>& vvAction)
{
	auto key = std::pair<std::wstring, int>(animationId, frameIndex);
	auto it = animationEvents.find(key);
	if (it == animationEvents.end())
	{
		animationEvents.insert({ key, {animationId, frameIndex} });
	}
	animationEvents[key].vvActions.push_back(vvAction);
}

void Animator::Play(std::shared_ptr<AnimationClip> animationClipPtr, const bool clearQueue)
{
	if (animationClipPtr)
	{
		try
		{
			if (clearQueue)
			{
				while (!playAniClipQueue.empty())
				{
					playAniClipQueue.pop();
				}
			}

			isPlaying = true;

			currentAnimationClip = animationClipPtr;
			totalFrame = (unsigned int)(animationClipPtr->GetFrames().size());
			checkFrame = animationSpeed > 0.f ? totalFrame : -1;
			currentFrame = animationSpeed > 0.f ? 0 : totalFrame - 1;

			frameDuration = 1.f / animationClipPtr->GetFps();
			accumTime = 0.f;

			SetAnimationFrame(currentAnimationClip->GetFrames()[currentFrame]);
		}
		catch (const std::exception& ex)
		{
			std::wcerr << L"Animator play error: " << ex.what() << std::endl;

			return;
		}
	}
	else
	{
		std::wcerr << L"animationClipPtr was nullptr" << std::endl;

		return;
	}
}

void Animator::PushPlayQueue(const std::shared_ptr<AnimationClip>& animationClip)
{
	playAniClipQueue.push(animationClip);
}

void Animator::Stop()
{
	isPlaying = false;
}