#include "CustomLib.h"
#include <sstream>

std::vector<std::string> CustomLib::SplitString(const std::string& input, char delimiter)
{
	std::vector<std::string> tokens;
	std::stringstream ss(input);
	std::string token;

	while (std::getline(ss, token, delimiter)) {
		tokens.push_back(token);
	}

	return tokens;
}

bool CustomLib::isWithinRange(const std::pair<int, int> point, const std::pair<std::pair<int, int>, std::pair<int, int>> range)
{
	return (point.first >= range.first.first && point.first <= range.second.first &&
		point.second >= range.first.second && point.second <= range.second.second);
}
