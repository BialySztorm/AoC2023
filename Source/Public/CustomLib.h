#pragma once
#include <string>
#include <vector>
#include <sstream>
#include <map>
#include <bitset>
#include <numeric>

class CustomLib
{
public:
	static std::vector<std::string> SplitString(const std::string& input, const char delimiter);
	static std::vector<std::string> SplitString(const std::string& input, const char delimiter, std::vector<int> unnecesaryColumns);
	static std::vector<std::string> SplitString(const std::string& input, const std::vector<char> delimiters);
	static std::vector<std::string> SplitString(const std::string& input, const std::vector<char> delimiters, std::vector<int> unnecesaryColumns);
	static std::vector<std::vector<std::string>> SplitString(const std::vector<std::string>& input, const char delimiter);
	static std::vector<std::vector<std::string>> SplitString(const std::vector<std::string>& input, const char delimiter, std::vector<int> unnecesaryColumns);
	static std::vector<std::vector<std::string>> SplitString(const std::vector<std::string>& input, const std::vector<char> delimiters);
	static std::vector<std::vector<std::string>> SplitString(const std::vector<std::string>& input, const std::vector<char> delimiters, std::vector<int> unnecesaryColumns);
	static bool IsWithinRange(const int point, const std::pair<int, int> range);
	static bool IsWithinRange(const std::pair<int, int> point, const std::pair<std::pair<int, int>, std::pair<int, int>> range);
	static long long CalculatePolygonArea(const std::vector<std::pair<long long, long long>>& points);
	static long long CalculatePolygonPerimeter(const std::vector<std::pair<long long, long long>>& points);
	static bool IsNumber(const std::string& s);
	static int CountOccurences(const std::string& str, const char target);
	static void PushError(const std::string e);
	static void SetConsoleColor(const int color);
	template <typename T>
	static std::vector<T> VectorStringToNumber(const std::vector<std::string>& stringVector);
	template <typename T>
	static std::string DecToBin(const T decimalNumber);
	template <typename T>
	static T BinToDec(const std::string& binaryString);
	template <typename T>
	static T LCM(const std::vector<T>& values);
private:
	template <typename T, typename U, typename CompareFunction>
	static U Partition(std::vector<T>& arr, const U low, const U high, const bool type, const CompareFunction compare);
	template <typename T>
	static bool Compare(const T a, const T b, const bool type);
	template <typename T>
	static bool CheckTab(const std::vector<T> tab);
public:
	template <typename T>
	static bool Day7Compare(const T a, const T b, const bool type);
	template <typename T, typename U, typename CompareFunction>
	static void QuickSort(std::vector<T>& arr, const U low, const U high, const bool type = false, const CompareFunction compare = Compare<T>);
	template <typename T>
	static int Extrapolation(const std::vector<T>& values, const bool direction = true);
};

template<typename T>
inline std::vector<T> CustomLib::VectorStringToNumber(const std::vector<std::string>& stringVector)
{
	std::vector<T> convertedVector;
	for (const std::string str : stringVector) {
		std::istringstream iss(str);
		T convertedValue;

		// Pr�ba przekszta�cenia stringa do typu T
		if (iss >> convertedValue) {
			convertedVector.push_back(convertedValue);
		}
		else {
			try {
				// Pr�ba u�ycia std::stoll dla long long
				convertedValue = std::stoll(str);
				convertedVector.push_back(convertedValue);
			}
			catch (const std::out_of_range& e) {
				// Obs�uga b��d�w, np. przekroczenie zakresu
				PushError("B��d konwersji dla: " + str + " - " + e.what());
			}
			catch (const std::invalid_argument& e) {
				// Obs�uga innych b��d�w konwersji
				PushError("B��d konwersji dla: " + str + " - " + e.what());
			}
		}
	}
	return convertedVector;
}

template <typename T>
inline std::string CustomLib::DecToBin(const T decimalNumber)
{
	std::bitset<sizeof(T) * 8> binaryRepresentation(decimalNumber);
	return binaryRepresentation.to_string();
}
template <typename T>
inline T CustomLib::BinToDec(const std::string& binaryString)
{
	std::bitset<sizeof(T) * 8> binaryRepresentation(binaryString);
	return static_cast<T>(binaryRepresentation.to_ulong());
}

template<typename T>
inline T CustomLib::LCM(const std::vector<T>& values)
{
	T tmp = 1;
	for (T value : values)
	{
		tmp = (tmp * value) / std::gcd(tmp, value);
	}
	return tmp;
}

template<typename T, typename U, typename CompareFunction>
inline void CustomLib::QuickSort(std::vector<T>& arr, const U low, const U high, const bool type, const CompareFunction compare)
{
	if (low < high) {
		U pi = Partition(arr, low, high, type, compare);

		QuickSort(arr, low, pi - 1, type, compare);
		QuickSort(arr, pi + 1, high, type, compare);
	}
}

template<typename T>
inline bool CustomLib::Compare(const T a, const T b, const bool type)
{
	if (!type)
		return a < b;
	else
		return a > b;
}

template<typename T>
inline bool CustomLib::CheckTab(const std::vector<T> tab)
{
	for (T element : tab)
		if (element != 0)
			return true;
	return false;
}

template<typename T>
inline bool CustomLib::Day7Compare(const T a, const T b, const bool type)
{
	return false;
}

template<>
inline bool CustomLib::Day7Compare<std::pair<int, std::string>>(const std::pair<int, std::string> a, const std::pair<int, std::string> b, const bool type)
{
	std::map<char, int> cardValues;
	if (!type)
	{
		cardValues = {
		{'2', 2},
		{'3', 3},
		{'4', 4},
		{'5', 5},
		{'6', 6},
		{'7', 7},
		{'8', 8},
		{'9', 9},
		{'T', 10},
		{'J', 11},
		{'Q', 12},
		{'K', 13},
		{'A', 14}
		};
	}
	else
	{
		cardValues = {
		{'J', 1},
		{'2', 2},
		{'3', 3},
		{'4', 4},
		{'5', 5},
		{'6', 6},
		{'7', 7},
		{'8', 8},
		{'9', 9},
		{'T', 10},
		{'Q', 11},
		{'K', 12},
		{'A', 13}
		};
	}
	for (int i = 0; i < 5; i++)
	{
		if (cardValues[a.second[i]] < cardValues[b.second[i]])
			return true;
		else if (cardValues[a.second[i]] > cardValues[b.second[i]])
			return false;
	}
	return false;
}

template<typename T, typename U, typename CompareFunction>
inline U CustomLib::Partition(std::vector<T>& arr, const U low, const U high, const bool type, const CompareFunction compare)
{
	T pivot = arr[high];
	U i = low - 1;

	for (U j = low; j <= high - 1; j++) {
		if (compare(arr[j], pivot, type)) {
			i++;
			std::swap(arr[i], arr[j]);
		}
	}

	std::swap(arr[i + 1], arr[high]);
	return i + 1;
}

template<typename T>
inline int CustomLib::Extrapolation(const std::vector<T>& values, const bool direction)
{
	std::vector<std::vector<T>> tab;
	tab.push_back(values);

	while (CheckTab<T>(tab[tab.size() - 1]))
	{
		std::vector<T> tmp;
		long long index = tab.size() - 1;
		for (long long i = 0; i < tab[index].size() - 1; i++)
		{
			tmp.push_back(tab[index][i + 1] - tab[index][i]);
		}
		tab.push_back(tmp);
	}
	tab[tab.size() - 1].push_back(0);

	if (direction)
	{
		for (long long i = tab.size() - 2; i >= 0; i--)
		{
			tab[i].push_back(tab[i + 1][tab[i + 1].size() - 1] + tab[i][tab[i].size() - 1]);
		}
		return tab[0][tab[0].size() - 1];
	}
	else
	{
		for (long long i = tab.size() - 2; i >= 0; i--)
		{
			tab[i].insert(tab[i].begin(), (tab[i][0] - tab[i + 1][0]));
		}
		return tab[0][0];
	}
	/*for (std::vector<T> tmp : tab)
	{
		std::string tmp2 = "";
		for (T tmp1 : tmp)
		{
			tmp2 += std::to_string(tmp1) + ", ";
		}
		PushError(tmp2);
	}
	PushError("");*/

	return 0;
}
