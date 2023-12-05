#pragma once
#include <string>
#include <vector>
#include <sstream>

class CustomLib
{
public:
	static std::vector<std::string> SplitString(const std::string& input, const char delimiter);
	static bool IsWithinRange(const std::pair<int, int> point, const std::pair<std::pair<int, int>, const std::pair<int, int>> range);
	template <typename T>
	static std::vector<T> VectorStringToNumber(const std::vector<std::string>& stringVector);
	static bool IsNumber(const std::string& s);
private:
	static void PushError(const std::string e);
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
