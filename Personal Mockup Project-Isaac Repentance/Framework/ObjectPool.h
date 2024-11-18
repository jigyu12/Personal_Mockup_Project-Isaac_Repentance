#pragma once

/// <summary>
/// This class automatically calls the AddGo function of the Scene class.
/// If you use object pooling to create a specific object, do not create it in any other way.
/// </summary>
/// <typeparam name="T"></typeparam>
template<typename T>
class ObjectPool
{
public:
	ObjectPool(int initSize = 10)
	{
		for (int i = 0; i < initSize; i++)
		{
			auto objectPtr = std::make_shared<T>();

			objectPtr->Init();

			unusedList.push_back(objectPtr);
		}
	}

	~ObjectPool()
	{
		for (auto& unusedObject : unusedList)
		{
			unusedObject->Exit();
			unusedObject->Release();
		}
		for (auto& usedObject : usedList)
		{
			usedObject->Exit();
			usedObject->Release();
		}
	}

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

	void Return(std::shared_ptr<T> objectPtr)
	{
		auto findIt = std::find(usedList.begin(), usedList.end(), objectPtr);
		if (findIt == usedList.end())
		{
			std::wcerr << L"Invalid object is returned to the ObjectPool." << std::endl;

			return;
		}

		usedList.erase(findIt);

		unusedList.push_back(objectPtr);
		objectPtr->SetActive(false);
	}

private:
	std::list<std::shared_ptr<T>> unusedList;
	std::list<std::shared_ptr<T>> usedList;
};