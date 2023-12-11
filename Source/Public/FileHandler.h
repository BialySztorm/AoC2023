#pragma once
#include <vector>
#include <string>
#include <json.hpp>
#include <fstream>

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
	template <typename T>
	T ReadJsonFile(const std::string& fileName);
};

template<typename T>
inline T FileHandler::ReadJsonFile(const std::string& fileName)
{
	std::ifstream file(inputDir + fileName);
	if (!file.is_open()) {
		throw std::runtime_error("Unable to open file: " + inputDir + fileName);
	}

	nlohmann::json jsonData;
	file >> jsonData;
	file.close();

	return jsonData.get<T>();
}
