#include "CustomLib.h"
#include <algorithm>
#include <iostream>
#include <Windows.h>

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
	std::sort(unnecesaryColumns.begin(), unnecesaryColumns.end(), [](int a, int b) { return (a >= 0 && b >= 0) ? a < b : a > b; });
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
	std::vector<std::string> tmp = { input };
	for (char delimiter : delimiters)
	{
		std::vector<std::string> tmp1;
		for (std::string tmp2 : tmp)
		{
			std::vector<std::string> tmp3 = SplitString(tmp2, delimiter);
			tmp1.insert(tmp1.end(), tmp3.begin(), tmp3.end());
		}
		tmp = tmp1;
	}
	return tmp;
}

std::vector<std::string> CustomLib::SplitString(const std::string& input, const std::vector<char> delimiters, std::vector<int> unnecesaryColumns)
{
	std::vector<std::string> tmp = SplitString(input, delimiters);
	std::sort(unnecesaryColumns.begin(), unnecesaryColumns.end(), [](int a, int b) { return (a >= 0 && b >= 0) ? a > b : a < b; });
	for (int i : unnecesaryColumns)
	{
		if (i < 0)
			tmp.erase(tmp.end() + i);
		else
			tmp.erase(tmp.begin() + i);
	}
	return tmp;
}

std::vector<std::vector<std::string>> CustomLib::SplitString(const std::vector<std::string>& input, const char delimiter)
{
	std::vector<std::vector<std::string>> tmp;
	for (std::string str : input)
		tmp.push_back(SplitString(str, delimiter));
	return tmp;
}

std::vector<std::vector<std::string>> CustomLib::SplitString(const std::vector<std::string>& input, const char delimiter, std::vector<int> unnecesaryColumns)
{
	std::vector<std::vector<std::string>> tmp;
	for (std::string str : input)
		tmp.push_back(SplitString(str, delimiter, unnecesaryColumns));
	return tmp;
}

std::vector<std::vector<std::string>> CustomLib::SplitString(const std::vector<std::string>& input, const std::vector<char> delimiters)
{
	std::vector<std::vector<std::string>> tmp;
	for (std::string str : input)
		tmp.push_back(SplitString(str, delimiters));
	return tmp;
}

std::vector<std::vector<std::string>> CustomLib::SplitString(const std::vector<std::string>& input, const std::vector<char> delimiters, std::vector<int> unnecesaryColumns)
{
	std::vector<std::vector<std::string>> tmp;
	for (std::string str : input)
		tmp.push_back(SplitString(str, delimiters, unnecesaryColumns));
	return tmp;
}

bool CustomLib::IsWithinRange(const int point, const std::pair<int, int> range)
{
	return (point >= range.first && point <= range.second || point <= range.first && point >= range.second);
}

bool CustomLib::IsWithinRange(const std::pair<int, int> point, const std::pair<std::pair<int, int>, std::pair<int, int>> range)
{
	return (point.first >= range.first.first && point.first <= range.second.first &&
		point.second >= range.first.second && point.second <= range.second.second);
}

long long CustomLib::CalculatePolygonArea(const std::vector<std::pair<long long, long long>>& points)
{
	long long n = points.size();
	if (n < 3) {
		return 0;
	}

	long long area = 0;
	for (long long i = 0; i < n; ++i)
	{
		long long next = (i + 1) % n;
		area += (points[i].first + points[next].first) * (points[i].second - points[next].second);
	}

	return std::abs(area) / 2.0;
}

long long CustomLib::CalculatePolygonPerimeter(const std::vector<std::pair<long long, long long>>& points)
{
	int n = points.size();
	if (n < 3) {
		return 0.0;
	}

	long long perimeter = 0;
	for (long long i = 0; i < n; ++i) {
		long long next = (i + 1) % n;
		long long dx = points[next].first - points[i].first;
		long long dy = points[next].second - points[i].second;
		perimeter += std::abs(dx) + std::abs(dy);
	}

	return perimeter;
}

bool CustomLib::IsNumber(const std::string& s)
{
	return !s.empty() && std::all_of(s.begin(), s.end(), ::isdigit);
}

int CustomLib::CountOccurences(const std::string& str, const char target)
{
	int count = 0;

	for (char ch : str) {
		if (ch == target) {
			count++;
		}
	}

	return count;
}

void CustomLib::PushError(const std::string e)
{
	SetConsoleColor(12);
	std::cerr << e << std::endl;
	SetConsoleColor(14);
}

void CustomLib::SetConsoleColor(const int color)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}