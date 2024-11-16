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

	void SaveByCsv(const std::vector<std::vector<std::string>>& rows, const std::wstring& filePath);
	std::shared_ptr<std::unordered_map<std::wstring, std::wstring>> LoadByCsv(const std::wstring& filePath) const;
};


NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(sf::Vector2f, x, y);

void to_json(json& j, const sf::Keyboard::Key& key);

void from_json(const json& j, sf::Keyboard::Key& key);

NLOHMANN_JSON_SERIALIZE_ENUM(Axis, {
	{Axis::HorizontalMove, L"HorizontalMove"},
	{Axis::VerticalMove, L"VerticalMove"},
	{Axis::HorizontalAttack , L"HorizontalAttack"},
	{Axis::VerticalAttack, L"VerticalAttack"},
	})

NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(AxisInfo, axis, keyMap, sensitivity, value)