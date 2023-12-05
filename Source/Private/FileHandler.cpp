#include "FileHandler.h"
#include <fstream>

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
	return tab;
}

bool FileHandler::WriteFile(const std::string fileName, const std::vector<std::string> content) const
{
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
	return false;
}