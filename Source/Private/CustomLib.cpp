#include "CustomLib.h"
#include <algorithm>
#include <iostream>

std::vector<std::string> CustomLib::SplitString(const std::string& input, const char delimiter)
{
	std::vector<std::string> tokens;
	std::stringstream ss(input);
	std::string token;

	while (std::getline(ss, token, delimiter)) {
		if (!token.empty())
			tokens.push_back(token);
	}

	return tokens;
}

std::vector<std::string> CustomLib::SplitString(const std::string& input, const char delimiter, std::vector<int> unnecesaryColumns)
{
	std::vector<std::string> tmp = SplitString(input, delimiter);
	std::sort(unnecesaryColumns.begin(), unnecesaryColumns.end(), StringSplitCompare);
	for (int i : unnecesaryColumns)
	{
		if (i < 0)
			tmp.erase(tmp.end() + i);
		else
			tmp.erase(tmp.begin() + i);
	}
	return tmp;
}

std::vector<std::string> CustomLib::SplitString(const std::string& input, const std::vector<char> delimiters)
{
	std::vector<std::string> tmp = {input};
	for (char delimiter : delimiters)
	{
		std::vector<std::string> tmp1;
		for (std::string tmp2 : tmp)
		{
			std::vector<std::string> tmp3 = SplitString(tmp2, delimiter);
			tmp1.insert(tmp1.end(),tmp3.begin(),tmp3.end());
		}
		tmp = tmp1;
	}
	return tmp;
}

std::vector<std::string> CustomLib::SplitString(const std::string& input, const std::vector<char> delimiters, std::vector<int> unnecesaryColumns)
{
	std::vector<std::string> tmp = SplitString(input, delimiters);
	std::sort(unnecesaryColumns.begin(), unnecesaryColumns.end(), StringSplitCompare);
	for (int i : unnecesaryColumns)
	{
		if (i < 0)
			tmp.erase(tmp.end() + i);
		else
			tmp.erase(tmp.begin() + i);
	}
	return tmp;
}

bool CustomLib::IsWithinRange(const std::pair<int, int> point, const std::pair<std::pair<int, int>, const std::pair<int, int>> range)
{
	return (point.first >= range.first.first && point.first <= range.second.first &&
		point.second >= range.first.second && point.second <= range.second.second);
}

bool CustomLib::IsNumber(const std::string& s)
{
	return !s.empty() && std::all_of(s.begin(), s.end(), ::isdigit);
}

void CustomLib::PushError(const std::string e)
{
	std::cerr << e << std::endl;
}

bool CustomLib::StringSplitCompare(const int a, const int b)
{
	return (a > 0 && b > 0) ? a < b : a > b;
}
