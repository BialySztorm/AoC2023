#pragma once
#include <vector>
#include <string>

class FileHandler;

class DayHandler
{
public:
	DayHandler(std::string inputDir, std::string outputDir);
	void HandleDay(int day);
private:
	int currentDay = 2;
	FileHandler* fileHandler;

	void day1(FileHandler& fileHandler);
	void day2(FileHandler& fileHandler);

	std::vector<std::string> SplitString(const std::string& input, char delimiter);
};
