#include "pch.h"

bool AnimationClip::loadFromFile(const std::string& filePath)
{
	std::wstring w_filePath = Utils::converter.from_bytes(filePath);
	std::shared_ptr<json> loadAnimationClipsPtr = FILE_MGR.LoadByJson(w_filePath);
	if (loadAnimationClipsPtr)
	{
		try
		{
			frames.clear();
			std::vector<AnimationClip> loadAnimationClips = loadAnimationClipsPtr->get<std::vector<AnimationClip>>();
			for (int i = 0; i < loadAnimationClips.size(); i++)
			{
				id = loadAnimationClips[i].id;
				loopType = loadAnimationClips[i].loopType;
				fps = loadAnimationClips[i].fps;
				frames = loadAnimationClips[i].frames;
			}
		}
		catch (const std::exception& ex)
		{
			std::wcerr << L"Invaild AnimationClip data: " << ex.what() << std::endl;

			return false;
		}
	}
	else
	{
		std::wcerr << L"loadAnimationClipsPtr was nullptr" << std::endl;

		return false;
	}

	return true;
}