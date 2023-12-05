#include "CustomLib.h"
#include <algorithm>
#include <iostream>

std::vector<std::string> CustomLib::SplitString(const std::string& input, char delimiter)
{
	std::vector<std::string> tokens;
	std::stringstream ss(input);
	std::string token;

	while (std::getline(ss, token, delimiter)) {
		if(!token.empty())
			tokens.push_back(token);
	}

	return tokens;
}

bool CustomLib::IsWithinRange(const std::pair<int, int> point, const std::pair<std::pair<int, int>, std::pair<int, int>> range)
{
	return (point.first >= range.first.first && point.first <= range.second.first &&
		point.second >= range.first.second && point.second <= range.second.second);
}

bool CustomLib::IsNumber(const std::string& s)
{
	return !s.empty() && std::all_of(s.begin(), s.end(), ::isdigit);
}

void CustomLib::PushError(std::string e)
{
	std::cerr << e << std::endl;
}
