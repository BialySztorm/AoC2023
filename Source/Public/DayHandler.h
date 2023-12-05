#pragma once
#include <vector>
#include <string>
#include <mutex>

class FileHandler;
using ProgressCallback = void(*)(int,int);

class DayHandler
{
public:
	DayHandler(std::string inputDir, std::string outputDir);
	void HandleDay(int day);
private:
	int currentDay = 5;
	FileHandler* fileHandler;

	void Day1(FileHandler& fileHandler);
	void Day2(FileHandler& fileHandler);
	void Day3(FileHandler& fileHandler);
	void Day4(FileHandler& fileHandler);
	void Day5(FileHandler& fileHandler);

	std::vector<std::pair<long long, long long>> Day5ApplyRange(std::vector<std::pair<long long, long long>> tab, std::vector<std::vector<long long>> mapping);
};
