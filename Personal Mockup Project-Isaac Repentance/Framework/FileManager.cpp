#include "pch.h"

void FileManager::SaveByJson(const json& jsonFile, const std::wstring& filePath) const
{
	std::ofstream outFile(filePath);
	if (!outFile)
	{
		std::wcerr << filePath + L" Save Failed" << std::endl;
	}
	else
	{
		outFile << jsonFile.dump(4);

		std::wcout << filePath + L" Save Success" << std::endl;
	}
	
	outFile.close();
}

std::shared_ptr<json> FileManager::LoadByJson(const std::wstring& filePath) const
{
	std::shared_ptr<json> jsonFile = std::make_shared<json>();

	std::ifstream inFile(filePath);
	if (!inFile)
	{
		std::wcerr << filePath + L" Load Failed" << std::endl;

		inFile.close();

		return nullptr;
	}
	else
	{
		inFile >> *jsonFile;

		std::wcout << filePath + L" Load Success" << std::endl;

		inFile.close();
	}

	return jsonFile;
}

void FileManager::SaveByCsv(const std::vector<std::vector<std::wstring>>& rows, const std::wstring& filePath)
{
	try 
	{
		csv csvFile;

		int rowIndex = -1;
		for (auto& row : rows)
		{
			std::vector<std::string> s_row(row.size());
			for (int i = 0; i < row.size(); i++)
			{
				s_row[i] = Utils::converter.to_bytes(row[i]);
			}
			csvFile.InsertRow(rowIndex, s_row);
			rowIndex++;
		}

		csvFile.Save(Utils::converter.to_bytes(filePath));
	}
	catch (const std::exception& ex) 
	{
		std::wcerr << filePath + L" Save Failed: " << ex.what() << std::endl;

		return;
	}
	
	std::wcout << filePath + L" Save Success" << std::endl;
}

std::shared_ptr<std::unordered_map<std::wstring, std::vector<std::wstring>>> FileManager::LoadByCsv(const std::wstring& filePath) const
{
	try
	{
		std::shared_ptr<std::unordered_map<std::wstring, std::vector<std::wstring>>> csvMap = std::make_shared<std::unordered_map<std::wstring, std::vector<std::wstring>>>();

		csv csvFile(Utils::converter.to_bytes(filePath), rapidcsv::LabelParams(0, -1));
		for (int i = 0; i < csvFile.GetRowCount(); i++)
		{
			std::vector<std::string> row = csvFile.GetRow<std::string>(i);

			std::wstring key = Utils::converter.from_bytes(row[0]);

			std::vector<std::wstring> value;
			for (int j = 1; j < row.size(); j++)
			{
				value.push_back(Utils::converter.from_bytes(row[j]));
			}

			csvMap->insert({ key, value });
		}

		std::wcout << filePath + L" Load Success" << std::endl;

		return csvMap;
	}
	catch (const std::exception& ex)
	{
		std::wcerr << filePath + L" Load Failed: " << ex.what() << std::endl;

		return nullptr;
	}
}