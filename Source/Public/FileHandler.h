#pragma once
#include <vector>
#include <string>

class FileHandler
{
private:
	std::string inputDir;
	std::string outputDir;
	bool CreateDirectory(const std::string& path) const;


public:
	FileHandler(const std::string inputDir, const std::string outputDir);

	std::vector<std::string> ReadFile(const std::string fileName) const;
	bool WriteFile(const std::string fileName, const std::vector<std::string> content) const;
	bool WriteFile(const std::string fileName, const std::vector<std::vector<char>> content) const;

};
