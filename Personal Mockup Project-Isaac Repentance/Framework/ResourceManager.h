#pragma once

template<typename T>
class ResourceManager
{
	DECLARE_SINGLETON(ResourceManager);

public:													
	void Init() {}

	void Update(float deltaTime) {}

	void Draw(sf::RenderWindow& window) {}

	void Release() {}

	std::shared_ptr<T> Get(const std::wstring& path, bool notUnLoadByUnLoadAll = false)
	{
		auto it = resources.find(path);
		if (it == resources.end() && !Load(path, notUnLoadByUnLoadAll))
		{
			return nullptr;
		}
		return resources[path].first;
	}

	bool UnLoadForce(const std::wstring& path)
	{
		auto it = resources.find(path);
		if (it == resources.end())
			return false;

		resources.erase(it);

		return true;
	}

	void UnLoadAll()
	{
		auto it = resources.begin();
		while (it != resources.end())
		{
			if (!it->second.second)
			{
				it = resources.erase(it);
			}
			else
			{
				++it;
			}
		}
	}

private:		
	bool Load(const std::wstring& path, bool notUnLoadByUnLoadAll)
	{
		if (resources.find(path) != resources.end())
			return false;

		std::shared_ptr<T> resource = std::make_shared<T>();

		std::string s_path = Utils::converter.to_bytes(path);

		bool isSuccess = resource->loadFromFile(s_path);
		if (isSuccess)
			resources.insert({ path, std::make_pair(resource, notUnLoadByUnLoadAll) });
		else
			std::wcerr << L"Failed to load resource" << std::endl;

		return isSuccess;
	}

	std::unordered_map<std::wstring, std::pair<std::shared_ptr<T>, bool>> resources;
};