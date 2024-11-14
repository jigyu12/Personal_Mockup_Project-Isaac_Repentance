#pragma once

template<typename T>
class ResourceManager
{
	DECLARE_SINGLETON(ResourceManager);

public:													
	void Init() {}

	void Update(float dt) {}

	void Draw(sf::RenderWindow& window) {}

	void Release() {}

	std::shared_ptr<T> Get(const std::wstring& id, bool notUnloadByUnloadAll = false)
	{
		auto it = resources.find(id);
		if (it == resources.end() && !Load(id, notUnloadByUnloadAll))
		{
			return None;
		}
		return resources[id].first;
	}

	bool UnLoadForce(const std::wstring& id)
	{
		auto it = resources.find(id);
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
	bool Load(const std::wstring& id, bool notUnloadByUnloadAll)
	{
		if (resources.find(id) != resources.end())
			return false;

		std::shared_ptr<T> resource = std::make_shared<T>();

		std::string s_id;
		s_id.assign(id.begin(), id.end());

		bool success = resource->loadFromFile(s_id);
		if (success)
		{
			resources.insert({ id, std::make_pair(resource, notUnloadByUnloadAll) });
		}

		return success;
	}

	static std::shared_ptr<T> None;

	std::unordered_map<std::wstring, std::pair<std::shared_ptr<T>, bool>> resources;
};

template<typename T>
std::shared_ptr<T> ResourceManager<T>::None = std::make_shared<T>();