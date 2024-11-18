#pragma once

/// <summary>
/// This class automatically calls the AddGo, RemoveGo function of the Scene class.
/// If you use object pooling to create a specific object, do not create it in any other way.
/// Do not use this class as a local variable. use it as a member variable instead.
/// Note that when the Scene's Exit and Release functions are called, the Exit and Release of the object pool must also be called.
/// </summary>
/// <typeparam name="T"></typeparam>
template<typename T>
class ObjectPool
{
public:
	ObjectPool() = default;

	~ObjectPool() = default;

	std::shared_ptr<T> Take(std::list<std::shared_ptr<GameObject>>& addGameObjects)
	{
		if (unusedList.empty())
		{
			auto objectPtr = std::make_shared<T>();

			objectPtr->Init();
			objectPtr->Enter();

			addGameObjects.push_back(objectPtr);
			usedList.push_back(objectPtr);

			return objectPtr;
		}

		auto objectPtr = unusedList.front();

		unusedList.pop_front();

		addGameObjects.push_back(objectPtr);
		usedList.push_back(objectPtr);

		objectPtr->Enter();
		objectPtr->SetActive(true);

		return objectPtr;
	}

	void Return(std::list<std::shared_ptr<GameObject>>& removeGameObjects, std::shared_ptr<T> objectPtr)
	{
		auto findIt = std::find(usedList.begin(), usedList.end(), objectPtr);
		if (findIt == usedList.end())
		{
			std::wcerr << L"Invalid object is returned to the ObjectPool." << std::endl;

			return;
		}

		removeGameObjects.push_back(objectPtr);

		usedList.erase(findIt);

		unusedList.push_back(objectPtr);
		objectPtr->SetActive(false);
	}

	void ExitAllUnUsedObject()
	{
		for (auto& unusedObject : unusedList)
			unusedObject->Exit();
	}

	void ReleaseAllUnUsedObject()
	{
		for (auto& unusedObject : unusedList)
			unusedObject->Release();
	}

private:
	std::list<std::shared_ptr<T>> unusedList;
	std::list<std::shared_ptr<T>> usedList;
};