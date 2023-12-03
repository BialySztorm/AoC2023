#pragma once
#include <string>
#include <vector>

class CustomLib
{
public:
	static std::vector<std::string> SplitString(const std::string& input, char delimiter);
	static bool isWithinRange(const std::pair<int, int> point, const std::pair<std::pair<int, int>, std::pair<int, int>> range);
};

