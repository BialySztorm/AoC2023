#pragma once

#include <string>
#include <vector>
#include <unordered_map>

class FileHandler;

struct TupleHash {
	template <class T1, class T2, class T3>
	std::size_t operator () (const std::tuple<T1, T2, T3>& p) const {
		auto h1 = std::hash<T1>{}(std::get<0>(p));
		auto h2 = std::hash<T2>{}(std::get<1>(p));
		auto h3 = std::hash<T3>{}(std::get<2>(p));

		return h1 ^ h2 ^ h3;
	}
};

class DayHandler
{
public:
	DayHandler(const std::string inputDir, const std::string outputDir);
	void HandleDay(const int day);
	int getCurrentDay() const;
private:
	// private variables
	int currentDay;
	std::vector<void (DayHandler::*)(FileHandler&)> dayFunctions;
	std::vector<std::string> dayNames;
	FileHandler* fileHandler;

	std::unordered_map<std::tuple<long long, long long, long long>, long long, TupleHash> RP;

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
	void Day11(FileHandler& fileHandler);
	void Day12(FileHandler& fileHandler);

	// Additional day functions
	std::vector<std::pair<long long, long long>> Day5ApplyRange(const std::vector<std::pair<long long, long long>> tab, const std::vector<std::vector<long long>> mapping) const;
	int Day7GetType(const std::string type, const bool activeJokers = false) const;
	bool Day10HandlePipe(std::pair<int, int>* previousLocation, std::pair<int, int>* currentLocation, const std::vector<std::string> map) const;
	long long Day12CountOccurencies(const std::string& conditionReport, const std::vector<int>& damagedGroups, long long i = 0, long long gi = 0, long long current = 0);
};