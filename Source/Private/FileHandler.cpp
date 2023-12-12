#include "FileHandler.h"
#include <filesystem>
#include <iostream>
#include <fstream>

#include "CustomLib.h"

bool FileHandler::CreateDirectory(const std::string& path) const
{
	std::string outputDir = path.substr(0, path.find_last_of("/\\") + 1);
	try {
		if (!std::filesystem::exists(outputDir)) {
			std::filesystem::create_directory(outputDir);
		}
		return true;
	}
	catch (const std::exception& e) {
		CustomLib::PushError("Error while creating directory: " + outputDir);
		return false;
	}
	CustomLib::PushError("Unknown exception while creating directory: " + outputDir);
	return false;
}

FileHandler::FileHandler(const std::string inputDir, const std::string outputDir)
{
	this->inputDir = inputDir;
	this->outputDir = outputDir;
}

std::vector<std::string> FileHandler::ReadFile(const std::string fileName) const
{
	std::ifstream file(inputDir + fileName);
	std::vector<std::string> tab;
	std::string Line;

	if (file.is_open())
	{
		while (std::getline(file, Line))
		{
			tab.push_back(Line);
		}
		file.close();
	}
	else
		CustomLib::PushError("Error while opening file: " + inputDir + fileName);
	return tab;
}

bool FileHandler::WriteFile(const std::string fileName, const std::vector<std::string> content) const
{
	if (!CreateDirectory(outputDir + fileName))
		return false;
	std::ofstream file(outputDir + fileName);
	if (file.is_open())
	{
		for (const std::string line : content)
		{
			file << line << std::endl;
		}
		file.close();
		return true;
	}

	CustomLib::PushError("Error while creating file: " + outputDir + fileName);
	return false;
}

bool FileHandler::WriteFile(const std::string fileName, const std::vector<std::vector<char>> content) const
{
	if (!CreateDirectory(outputDir + fileName))
		return false;
	std::ofstream file(outputDir + fileName);
	if (file.is_open())
	{
		for (const std::vector<char> line : content)
		{
			for (const char ch : line)
			{
				file << ch;
			}
			file << std::endl;
		}
		file.close();
		return true;
	}
	CustomLib::PushError("Error while creating file: " + outputDir + fileName);
	return false;
}

nlohmann::json FileHandler::ReadJsonFileStruct(const std::string fileName) const
{
	std::ifstream file(inputDir + fileName);
	if (!file.is_open()) {
		throw std::runtime_error("Unable to open file: " + inputDir + fileName);
	}

	nlohmann::json jsonData;
	file >> jsonData;
	file.close();

	return jsonData;
}
