#pragma once
#include <string>
#include <vector>
class FileHandler
{
private:
	std::string inputDir;
	std::string outputDir;

public:
	FileHandler(std::string inputDir, std::string outputDir);

	std::vector<std::string> ReadFile(std::string fileName) const;
	bool WriteFile(const std::string fileName, const std::vector<std::string> content);

};

