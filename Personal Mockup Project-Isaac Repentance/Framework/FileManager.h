#pragma once

class FileManager
{
	DECLARE_SINGLETON(FileManager);

public:
	void Init() {}

	void Update(float deltaTime) {}

	void Draw(sf::RenderWindow& window) {}

	void Release() {}

	void SaveByJson(const json& jsonFile, const std::wstring& filePath) const;
	std::shared_ptr<json> LoadByJson(const std::wstring& filePath) const;

	void SaveByCsv(const std::vector<std::vector<std::wstring>>& rows, const std::wstring& filePath);
	std::shared_ptr<std::unordered_map<std::wstring, std::vector<std::wstring>>> LoadByCsv(const std::wstring& filePath) const;
};