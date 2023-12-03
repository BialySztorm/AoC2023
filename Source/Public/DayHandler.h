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
	int currentDay = 3;
	FileHandler* fileHandler;

	void day1(FileHandler& fileHandler);
	void day2(FileHandler& fileHandler);
	void day3(FileHandler& fileHandler);

	std::vector<std::string> SplitString(const std::string& input, char delimiter);
	bool isWithinRange(const std::pair<int, int> point, const std::pair<std::pair<int, int>, std::pair<int, int>> range);
};
