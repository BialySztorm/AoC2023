#pragma once

#include <string>
#include <vector>

class FileHandler;

class DayHandler
{
public:
	DayHandler(std::string inputDir, std::string outputDir);
	void HandleDay(int day);
	int getCurrentDay();
private:
	// private variables
	int currentDay;
	std::vector<void (DayHandler::*)(FileHandler&)> dayFunctions;
	FileHandler* fileHandler;

	// Main day functions
	void Day1(FileHandler& fileHandler);
	void Day2(FileHandler& fileHandler);
	void Day3(FileHandler& fileHandler);
	void Day4(FileHandler& fileHandler);
	void Day5(FileHandler& fileHandler);
	void Day6(FileHandler& fileHandler);
	void Day7(FileHandler& fileHandler);
	void Day8(FileHandler& fileHandler);
	void Day9(FileHandler& fileHandler);
	void Day10(FileHandler& fileHandler);

	// Additional day functions
	std::vector<std::pair<long long, long long>> Day5ApplyRange(std::vector<std::pair<long long, long long>> tab, std::vector<std::vector<long long>> mapping);
	int Day7GetType(std::string type, bool activeJokers = false) const;
	bool Day10HandlePipe(std::pair<int, int>* previousLocation, std::pair<int, int>* currentLocation, const std::vector<std::string> map);
};