#include "pch.h"

void FileManager::SaveByJson(const json& js, const std::wstring filePath) const
{
	std::ofstream outFile(filePath);
	if (!outFile)
	{
		std::wcerr << filePath + L" Save Failed" << std::endl;
	}
	else
	{
		outFile << js.dump(4);
		std::wcout << filePath + L" Save Success" << std::endl;
	}
	
	outFile.close();
}

std::shared_ptr<json> FileManager::LoadByJson(const std::wstring filePath) const
{
	std::shared_ptr<json> js = std::make_shared<json>();

	std::ifstream inFile(filePath);
	if (!inFile)
	{
		std::wcerr << filePath + L" Load Failed" << std::endl;

		inFile.close();

		return nullptr;
	}
	else
	{
		inFile >> *js;

		std::wcout << filePath + L" Load Success" << std::endl;

		inFile.close();
	}

	return js;
}

void to_json(json& j, const sf::Keyboard::Key& key)
{
	j = static_cast<int>(key);
}

void from_json(const json& j, sf::Keyboard::Key& key)
{
	key = static_cast<sf::Keyboard::Key>(j.get<int>());
}