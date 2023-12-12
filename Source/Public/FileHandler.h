#pragma once
#include <vector>
#include <string>
#include <json.hpp>

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
	nlohmann::json ReadJsonFileStruct(const std::string fileName) const;
	// requires nlohmann/json.hpp
	template <typename T>
	T ReadJsonFile(const std::string& fileName) const;
};

template<typename T>
inline T FileHandler::ReadJsonFile(const std::string& fileName) const
{
	nlohmann::json jsonData = ReadJsonFileStruct(fileName);
	return jsonData.get<T>();
}

template<>
inline nlohmann::json FileHandler::ReadJsonFile<nlohmann::json>(const std::string& fileName) const
{
	nlohmann::json jsonData = ReadJsonFileStruct(fileName);
	return jsonData;
}

