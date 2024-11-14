#pragma once

class FileManager
{
	DECLARE_SINGLETON(FileManager);

public:
	void Init() {}

	void Update(float dt) {}

	void Draw(sf::RenderWindow& window) {}

	void Release() {}

	void SaveByJson(const json& js, const std::wstring filePath) const;
	std::shared_ptr<json> LoadByJson(const std::wstring filePath) const;
};


NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(sf::Vector2f, x, y);

void to_json(json& j, const sf::Keyboard::Key& key);

void from_json(const json& j, sf::Keyboard::Key& key);

NLOHMANN_JSON_SERIALIZE_ENUM(Axis, {
	{Axis::HorizontalMove, "HorizontalMove"},
	{Axis::VerticalMove, "VerticalMove"},
	{Axis::HorizontalAttack , "HorizontalAttack"},
	{Axis::VerticalAttack, "VerticalAttack"},
	})

NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(AxisInfo, axis, keyMap, sensitivity, value)