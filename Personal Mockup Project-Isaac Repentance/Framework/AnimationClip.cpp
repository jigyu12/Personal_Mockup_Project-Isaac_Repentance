#include "pch.h"

bool AnimationClip::loadFromFile(const std::string& filePath)
{
	std::wstring w_filePath = Utils::converter.from_bytes(filePath);
	std::shared_ptr<json> loadAnimationClipPtr = FILE_MGR.LoadByJson(w_filePath);
	if (loadAnimationClipPtr)
	{
		try
		{
			AnimationClip loadAnimationClip = loadAnimationClipPtr->get<AnimationClip>();

			id = loadAnimationClip.id;
			loopType = loadAnimationClip.loopType;
			fps = loadAnimationClip.fps;
			frames = loadAnimationClip.frames;
		}
		catch (const std::exception& ex)
		{
			std::wcerr << L"Invaild AnimationClip data: " << ex.what() << std::endl;

			return false;
		}
	}
	else
	{
		std::wcerr << L"loadAnimationClipPtr was nullptr" << std::endl;

		return false;
	}

	return true;
}