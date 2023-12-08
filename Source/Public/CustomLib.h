#pragma once
#include <string>
#include <vector>
#include <sstream>
#include <map>

class CustomLib
{
public:
	static std::vector<std::string> SplitString(const std::string& input, const char delimiter);
	static std::vector<std::string> SplitString(const std::string& input, const char delimiter, std::vector<int> unnecesaryColumns);
	static std::vector<std::string> SplitString(const std::string& input, const std::vector<char> delimiters);
	static std::vector<std::string> SplitString(const std::string& input, const std::vector<char> delimiters, std::vector<int> unnecesaryColumns);
	static bool IsWithinRange(const std::pair<int, int> point, const std::pair<std::pair<int, int>, const std::pair<int, int>> range);
	static bool IsNumber(const std::string& s);
	template <typename T>
	static std::vector<T> VectorStringToNumber(const std::vector<std::string>& stringVector);
private:
	static void PushError(const std::string e);
	static bool StringSplitCompare(const int a, const int b);
	template <typename T, typename U, typename CompareFunction>
	static U Partition(std::vector<T>& arr, U low, U high, bool type, CompareFunction compare);
	template <typename T>
	static bool Compare(T a, T b, bool type);
public:
	template <typename T>
	static bool Day7Compare(T a, T b, bool type);
	template <typename T, typename U, typename CompareFunction>
	static void QuickSort(std::vector<T>& arr, U low, U high, bool type = false, CompareFunction compare = Compare<T>);
};

template<typename T>
inline std::vector<T> CustomLib::VectorStringToNumber(const std::vector<std::string>& stringVector)
{
	std::vector<T> convertedVector;
	for (const std::string str : stringVector) {
		std::istringstream iss(str);
		T convertedValue;

		// Próba przekszta³cenia stringa do typu T
		if (iss >> convertedValue) {
			convertedVector.push_back(convertedValue);
		}
		else {
			try {
				// Próba u¿ycia std::stoll dla long long
				convertedValue = std::stoll(str);
				convertedVector.push_back(convertedValue);
			}
			catch (const std::out_of_range& e) {
				// Obs³uga b³êdów, np. przekroczenie zakresu
				PushError("B³¹d konwersji dla: " + str + " - " + e.what());
			}
			catch (const std::invalid_argument& e) {
				// Obs³uga innych b³êdów konwersji
				PushError("B³¹d konwersji dla: " + str + " - " + e.what());
			}
		}
	}
	return convertedVector;
}

template<typename T, typename U, typename CompareFunction>
inline void CustomLib::QuickSort(std::vector<T>& arr, U low, U high, bool type, CompareFunction compare)
{
	if (low < high) {
		U pi = Partition(arr, low, high, type, compare);

		QuickSort(arr, low, pi - 1, type, compare);
		QuickSort(arr, pi + 1, high, type, compare);
	}
}

template<typename T>
inline bool CustomLib::Compare(T a, T b, bool type)
{
	return a < b;
}

template<typename T>
inline bool CustomLib::Day7Compare(T a, T b, bool type)
{
	return false;
}

template<>
inline bool CustomLib::Day7Compare<std::pair<int, std::string>>(std::pair<int, std::string> a, std::pair<int, std::string> b, bool type)
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
inline U CustomLib::Partition(std::vector<T>& arr, U low, U high, bool type, CompareFunction compare)
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
