#pragma once
#include <vector>
#include <string>

class FileHandler
{
private:
	std::string inputDir;
	std::string outputDir;

public:
	FileHandler(const std::string inputDir, const std::string outputDir);

	std::vector<std::string> ReadFile(const std::string fileName) const;
	bool WriteFile(const std::string fileName, const std::vector<std::string> content) const;
};
