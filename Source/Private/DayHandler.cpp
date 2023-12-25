#include "DayHandler.h"

#include <cctype>
#include <iostream>
#include <cmath>
#include <thread>
#include <limits>
#include <unordered_map>
#include <queue>
#include <algorithm>
#include <z3++.h>
#include "CustomLib.h"
#include "FileHandler.h"

DayHandler::DayHandler(const std::string inputDir, const std::string outputDir)
{
	fileHandler = new FileHandler(inputDir, outputDir);
	dayNames = fileHandler->ReadJsonFile<std::vector<std::string>>("names.json");
	dayFunctions.emplace_back(&DayHandler::Day1);
	dayFunctions.emplace_back(&DayHandler::Day2);
	dayFunctions.emplace_back(&DayHandler::Day3);
	dayFunctions.emplace_back(&DayHandler::Day4);
	dayFunctions.emplace_back(&DayHandler::Day5);
	dayFunctions.emplace_back(&DayHandler::Day6);
	dayFunctions.emplace_back(&DayHandler::Day7);
	dayFunctions.emplace_back(&DayHandler::Day8);
	dayFunctions.emplace_back(&DayHandler::Day9);
	dayFunctions.emplace_back(&DayHandler::Day10);
	dayFunctions.emplace_back(&DayHandler::Day11);
	dayFunctions.emplace_back(&DayHandler::Day12);
	dayFunctions.emplace_back(&DayHandler::Day13);
	dayFunctions.emplace_back(&DayHandler::Day14);
	dayFunctions.emplace_back(&DayHandler::Day15);
	dayFunctions.emplace_back(&DayHandler::Day16);
	dayFunctions.emplace_back(&DayHandler::Day17);
	dayFunctions.emplace_back(&DayHandler::Day18);
	dayFunctions.emplace_back(&DayHandler::Day19);
	dayFunctions.emplace_back(&DayHandler::Day20);
	dayFunctions.emplace_back(&DayHandler::Day21);
	dayFunctions.emplace_back(&DayHandler::Day22);
	dayFunctions.emplace_back(&DayHandler::Day23);
	dayFunctions.emplace_back(&DayHandler::Day24);
	dayFunctions.emplace_back(&DayHandler::Day25);
	currentDay = dayFunctions.size();
}

void DayHandler::HandleDay(const int day)
{
	if (day <= currentDay && day > 0)
	{
		if (day - 1 < dayNames.size())
			std::cout << dayNames[day - 1] << std::endl << std::endl;
		(this->*dayFunctions[day - 1])(*fileHandler);
		if (day - 1 < dayNames.size())
		{
			std::cout << std::endl;
			for (int i = 0; i < dayNames[day - 1].length(); i++)
				std::cout << "-";
			std::cout << std::endl;
		}
	}
	else
	{
		std::cout << "\nWrong day!\n";
	}
}

int DayHandler::getCurrentDay() const
{
	return currentDay;
}

void DayHandler::Day1(FileHandler& fileHandler)
{
	std::vector<std::string> tab = fileHandler.ReadFile("day1.txt");
	size_t tabSize = tab.size();

	// Part one
	int calibrationSum = 0, element = 0;
	for (const std::string line : tab)
	{
		std::cout << element++ << "/" << tabSize << "\r";
		char numbers[] = { NULL, NULL };
		for (const char ch : line)
		{
			if (std::isdigit(ch))
			{
				if (numbers[0] == NULL)
				{
					numbers[0] = ch;
					numbers[1] = ch;
				}
				else
					numbers[1] = ch;
			}
		}
		try
		{
			std::string tmp = numbers;
			calibrationSum += std::stoi(tmp);
		}
		catch (...)
		{
			std::cerr << "B³¹d: Nieoczekiwany b³¹d." << std::endl;
		}
	}
	std::cout << "Part One: " << calibrationSum << std::endl;

	calibrationSum = element = 0;

	// Part two
	std::string numbersDict[] = { "one", "two", "three", "four", "five", "six", "seven", "eight", "nine" };
	for (const std::string line : tab)
	{
		std::cout << element++ << "/" << tabSize << "\r";
		char numbers[] = { NULL, NULL };
		for (int i = 0; i < line.length(); i++)
		{
			if (std::isdigit(line[i]))
			{
				if (numbers[0] == NULL)
				{
					numbers[0] = line[i];
					numbers[1] = line[i];
				}
				else
					numbers[1] = line[i];
			}
			else
			{
				for (int j = 0; j < 9; j++)
				{
					if (numbersDict[j][0] == line[i] && line.length() - i >= numbersDict[j].length())
						//std::cout<< line.substr(i, numbersDict[j].length())<<std::endl;
						if (line.substr(i, numbersDict[j].length()) == numbersDict[j])
						{
							//std::cout<<j+1<<std::endl;
							if (numbers[0] == NULL)
							{
								numbers[0] = static_cast<char>('0' + j + 1);
								numbers[1] = static_cast<char>('0' + j + 1);
							}
							else
								numbers[1] = static_cast<char>('0' + j + 1);
							break;
						}
				}
			}
		}
		try
		{
			std::string tmp = numbers;
			//std::cout<<tmp<<std::endl;
			//std::cout << std::stoi(tmp) << std::endl;
			calibrationSum += std::stoi(tmp);
		}
		catch (...)
		{
			std::cerr << "B³¹d: Nieoczekiwany b³¹d." << std::endl;
		}
	}
	std::cout << "Part Two: " << calibrationSum << std::endl;
}

void DayHandler::Day2(FileHandler& fileHandler)
{
	std::vector<std::string> tab = fileHandler.ReadFile("day2.txt");
	size_t tabSize = tab.size();

	int fairGames = 0, element = 0;
	for (std::string line : tab)
	{
		std::cout << element++ << "/" << tabSize << "\r";
		bool fairGame = true;
		std::vector<std::string> tmp = CustomLib::SplitString(line, { ' ', ':', ';', ',' }, { 0, 1 });
		for (int i = 0; i < tmp.size() / 2; i++)
		{
			if (tmp[2 * i + 1] == "blue" && std::stoi(tmp[2 * i]) > 14)
			{
				fairGame = false;
				break;
			}
			else if (tmp[2 * i + 1] == "green" && std::stoi(tmp[2 * i]) > 13)
			{
				fairGame = false;
				break;
			}
			else if (tmp[2 * i + 1] == "red" && std::stoi(tmp[2 * i]) > 12)
			{
				fairGame = false;
				break;
			}
		}
		if (fairGame)
		{
			int id = std::stoi(CustomLib::SplitString(line, { ' ', ':', ';', ',' })[1]);
			//std::cout<<id<<std::endl;
			fairGames += id;
		}
	}
	std::cout << "Part One: " << fairGames << std::endl;

	int sum = 0;
	element = 0;
	for (std::string line : tab)
	{
		std::cout << element++ << "/" << tabSize << "\r";
		int maxR = 1, maxG = 1, maxB = 1;
		std::vector<std::string> tmp1 = CustomLib::SplitString(line, { ' ', ':', ';', ',' }, { 0, 1 });
		for (int i = 0; i < tmp1.size() / 2; i++)
		{
			if (tmp1[2 * i + 1] == "blue" && std::stoi(tmp1[2 * i]) > maxB)
			{
				maxB = std::stoi(tmp1[2 * i]);
			}
			else if (tmp1[2 * i + 1] == "green" && std::stoi(tmp1[2 * i]) > maxG)
			{
				maxG = std::stoi(tmp1[2 * i]);
			}
			else if (tmp1[2 * i + 1] == "red" && std::stoi(tmp1[2 * i]) > maxR)
			{
				maxR = std::stoi(tmp1[2 * i]);
			}
		}
		int tmp = maxR * maxG * maxB;
		//std::cout << tmp << std::endl;
		sum += tmp;
	}

	std::cout << "Part Two: " << sum << std::endl;
}

void DayHandler::Day3(FileHandler& fileHandler)
{
	std::vector<std::string> tab = fileHandler.ReadFile("day3.txt");
	size_t tabSize = tab.size();

	std::vector<std::pair<std::pair<int, int>, std::pair<int, int>>> tmp, tmp1;

	for (int i = 0; i < tab.size(); i++)
	{
		std::cout << i << "/" << tabSize << "\r";
		bool isNum = false;
		std::pair<int, int> start, end;
		for (int j = 0; j < tab[i].length(); j++)
		{
			if (isdigit(tab[i][j]) && !isNum)
			{
				start = { i,j };
				isNum = true;
			}
			else if (!isdigit(tab[i][j]) && isNum)
			{
				end = { i,j - 1 };
				isNum = false;
				tmp.push_back({ start,end });
			}
		}
		if (isNum)
		{
			end = { i, tab[i].length() - 1 };
			tmp.push_back({ start,end });
		}
	}
	tabSize = tmp.size();
	int element = 0;
	for (std::pair<std::pair<int, int>, std::pair<int, int>> tmp2 : tmp)
	{
		std::cout << element++ << "/" << tabSize << "\r";
		int min = tmp2.first.second, max = tmp2.second.second, height = tmp2.first.first;
		bool isCorrect = false;
		for (int i = min; i <= max; i++)
		{
			if (i > 0 && !isdigit(tab[height][i - 1]) && tab[height][i - 1] != '.')
			{
				isCorrect = true;
				break;
			}
			if (i > 0 && height > 0 && !isdigit(tab[height - 1][i - 1]) && tab[height - 1][i - 1] != '.')
			{
				isCorrect = true;
				break;
			}
			if (height > 0 && !isdigit(tab[height - 1][i]) && tab[height - 1][i] != '.')
			{
				isCorrect = true;
				break;
			}
			if (i < tab[height].length() - 1 && height > 0 && !isdigit(tab[height - 1][i + 1]) && tab[height - 1][i + 1] != '.')
			{
				isCorrect = true;
				break;
			}
			if (i < tab[height].length() - 1 && !isdigit(tab[height][i + 1]) && tab[height][i + 1] != '.')
			{
				isCorrect = true;
				break;
			}
			if (i < tab[height].length() - 1 && height < tab.size() - 1 && !isdigit(tab[height + 1][i + 1]) && tab[height + 1][i + 1] != '.')
			{
				isCorrect = true;
				break;
			}
			if (height < tab.size() - 1 && !isdigit(tab[height + 1][i]) && tab[height + 1][i] != '.')
			{
				isCorrect = true;
				break;
			}
			if (i > 0 && height < tab.size() - 1 && !isdigit(tab[height + 1][i - 1]) && tab[height + 1][i - 1] != '.')
			{
				isCorrect = true;
				break;
			}
		}
		if (isCorrect)
		{
			tmp1.push_back(tmp2);
		}
	}
	int sum = 0;
	for (std::pair<std::pair<int, int>, std::pair<int, int>> tmp2 : tmp1)
	{
		sum += std::stoi(tab[tmp2.first.first].substr(tmp2.first.second, tmp2.second.second - tmp2.first.second + 1));
	}

	std::cout << "Part One: " << sum << std::endl;

	std::vector<std::pair<int, int>> gearRatios;
	for (int i = 0; i < tab.size(); i++)
		for (int j = 0; j < tab[i].length(); j++)
			if (tab[i][j] == '*')
				gearRatios.push_back({ i,j });

	int ratioSum = 0;
	element = 0;
	tabSize = gearRatios.size();
	for (std::pair<int, int> gearRatio : gearRatios)
	{
		std::cout << element++ << "/" << tabSize << "\r";
		std::pair<int, int> one = { -1,-1 }, two = { -1,-1 };
		int i = gearRatio.second, height = gearRatio.first;
		if (i > 0 && isdigit(tab[height][i - 1]))
		{
			one = { height,i - 1 };
		}
		if (i < tab[height].length() - 1 && isdigit(tab[height][i + 1]))
		{
			if (one.first != -1 && one.second != -1)
			{
				two = { height,i + 1 };
			}
			else {
				one = { height,i + 1 };
			}
		}
		if (height > 0 && isdigit(tab[height - 1][i]) && (two.first == -1 && two.second == -1))
		{
			if (one.first != -1 && one.second != -1)
			{
				two = { height - 1,i };
			}
			else {
				one = { height - 1,i };
			}
		}
		if (height < tab.size() - 1 && isdigit(tab[height + 1][i]) && (two.first == -1 && two.second == -1))
		{
			if (one.first != -1 && one.second != -1)
			{
				two = { height + 1,i };
			}
			else {
				one = { height + 1,i };
			}
		}
		if (i > 0 && height > 0 && isdigit(tab[height - 1][i - 1]) && (two.first == -1 && two.second == -1) && height - 1 != one.first)
		{
			if (one.first != -1 && one.second != -1)
			{
				two = { height - 1,i - 1 };
			}
			else {
				one = { height - 1,i - 1 };
			}
		}
		if (i < tab[height].length() - 1 && height > 0 && isdigit(tab[height - 1][i + 1]) && (two.first == -1 && two.second == -1) && !(height - 1 == one.first && i == one.second))
		{
			if (one.first != -1 && one.second != -1)
			{
				two = { height - 1,i + 1 };
			}
			else {
				one = { height - 1,i + 1 };
			}
		}
		if (i < tab[height].length() - 1 && height < tab.size() - 1 && isdigit(tab[height + 1][i + 1]) && (two.first == -1 && two.second == -1) && height + 1 != one.first)
		{
			if (one.first != -1 && one.second != -1)
			{
				two = { height + 1,i + 1 };
			}
			else {
				one = { height + 1,i + 1 };
			}
		}
		if (i > 0 && height < tab.size() - 1 && isdigit(tab[height + 1][i - 1]) && (two.first == -1 && two.second == -1) && !(height + 1 == one.first && i == one.second))
		{
			if (one.first != -1 && one.second != -1)
			{
				two = { height + 1,i - 1 };
			}
			else {
				one = { height + 1,i - 1 };
			}
		}
		if ((two.first == -1 && two.second == -1))
			continue;
		int tmpRatio = 1;
		for (std::pair<std::pair<int, int>, std::pair<int, int>> tmpTab : tmp)
		{
			if (CustomLib::IsWithinRange(one, tmpTab))
			{
				//std::cout<<tmpTab.first.first<<", "<<tmpTab.first.second<<"; " << tmpTab.second.first << ", " << tmpTab.second.second << " - ";
				tmpRatio *= std::stoi(tab[tmpTab.first.first].substr(tmpTab.first.second, tmpTab.second.second - tmpTab.first.second + 1));
				break;
			}
		}
		for (std::pair<std::pair<int, int>, std::pair<int, int>> tmpTab : tmp)
		{
			if (CustomLib::IsWithinRange(two, tmpTab))
			{
				//std::cout << tmpTab.first.first << ", " << tmpTab.first.second << "; " << tmpTab.second.first << ", " << tmpTab.second.second << "\n";
				tmpRatio *= std::stoi(tab[tmpTab.first.first].substr(tmpTab.first.second, tmpTab.second.second - tmpTab.first.second + 1));
				break;
			}
		}
		//std::cout<<tmpRatio<<std::endl;

		ratioSum += tmpRatio;
	}

	std::cout << "Part Two: " << ratioSum << std::endl;
}

void DayHandler::Day4(FileHandler& fileHandler)
{
	std::vector<std::string> tab = fileHandler.ReadFile("day4.txt");
	std::vector<std::vector<std::string>> tab1;
	for (std::string tmp : tab)
	{
		std::vector<std::string> tmp1 = CustomLib::SplitString(tmp, { ':','|' });
		tab1.push_back(tmp1);
	}
	int points = 0, element = 0;
	size_t tabSize = tab1.size();
	for (std::vector<std::string> tmp : tab1)
	{
		std::cout << element++ << "/" << tabSize << "\r";
		int multiply = 0;
		std::vector<int> winningNumbers, myNumbers;
		for (std::string tmp1 : CustomLib::SplitString(tmp[1], ' '))
		{
			winningNumbers.push_back(std::stoi(tmp1));
		}
		for (std::string tmp1 : CustomLib::SplitString(tmp[2], ' '))
		{
			myNumbers.push_back(std::stoi(tmp1));
		}
		for (int tmp1 : myNumbers)
		{
			for (int tmp2 : winningNumbers)
			{
				if (tmp1 == tmp2)
				{
					multiply++;
					break;
				}
			}
		}
		if (multiply > 0)
		{
			points += std::floor(std::pow(2, multiply - 1));
		}
	}
	std::cout << "Part One: " << points << std::endl;

	tabSize = tab.size();
	int* scratchcards = new int[tabSize];
	for (int i = 0; i < tabSize; i++)
	{
		scratchcards[i] = 1;
	}
	int scratchcardsNum = 0;
	for (int i = 0; i < tabSize; i++)
	{
		std::cout << i << "/" << tabSize << "\r";
		if (scratchcards != nullptr && scratchcards[i] != NULL)
			scratchcardsNum += scratchcards[i];
		//std::cout << i << ", " << scratchcards[i] << std::endl;
		int tmp = 0;
		int cards = 0;
		std::vector<int> winningNumbers, myNumbers;
		for (std::string tmp1 : CustomLib::SplitString(tab1[i][1], ' '))
		{
			winningNumbers.push_back(std::stoi(tmp1));
		}
		for (std::string tmp1 : CustomLib::SplitString(tab1[i][2], ' '))
		{
			myNumbers.push_back(std::stoi(tmp1));
		}
		for (int tmp1 : myNumbers)
		{
			for (int tmp2 : winningNumbers)
			{
				if (tmp1 == tmp2)
				{
					cards++;
					break;
				}
			}
		}
		for (int j = 1; j < cards + 1; j++)
		{
			if (i + j < tab.size())
			{
				scratchcards[i + j] += scratchcards[i];
			}
		}
	}
	delete[] scratchcards;
	std::cout << "Part Two: " << scratchcardsNum << std::endl;
}

void DayHandler::Day5(FileHandler& fileHandler)
{
	std::vector<std::string> tab = fileHandler.ReadFile("day5.txt");
	std::vector<long long> seeds = CustomLib::VectorStringToNumber<long long>(CustomLib::SplitString(CustomLib::SplitString(tab[0], ':')[1], ' '));
	std::vector<int> seedsLevel;
	for (int i = 0; i < seeds.size(); i++)
		seedsLevel.push_back(0);
	int currentLevel = 0, seedsUnderLevel = 0;
	size_t tabSize = tab.size();
	for (int i = 1; i < tabSize; i++)
	{
		std::cout << i << "/" << tabSize << "\r";
		if (tab[i] == "")
		{
			i += 2;
			for (int i = 0; i < seedsLevel.size(); i++)
			{
				seedsLevel[i] = currentLevel;
			}
			currentLevel++;
			seedsUnderLevel = seeds.size();
			//std::cout << currentLevel << std::endl;
		}
		else if (!seedsUnderLevel)
			continue;
		std::vector<long long> map = CustomLib::VectorStringToNumber<long long>(CustomLib::SplitString(tab[i], ' '));
		long long maxRange = map[1] + map[2] - 1;
		for (int j = 0; j < seeds.size(); j++)
		{
			if (seedsLevel[j] < currentLevel && seeds[j] >= map[1] && seeds[j] <= maxRange)
			{
				seeds[j] += map[0] - map[1];
				seedsLevel[j]++;
				seedsUnderLevel--;
			}
		}
	}

	std::cout << "Part One: " << *std::min_element(seeds.begin(), seeds.end()) << std::endl;

	seeds = CustomLib::VectorStringToNumber<long long>(CustomLib::SplitString(CustomLib::SplitString(tab[0], ':')[1], ' '));

	std::vector<std::vector<std::vector<long long>>> mappings;

	{
		std::vector <std::vector<long long>> tmp;
		for (int i = 1; i < tabSize; i++)
		{
			std::cout << i << "/" << tabSize << "\r";
			if (tab[i] == "")
			{
				if (i != 1)
				{
					mappings.push_back(tmp);
					tmp.clear();
				}
				i += 2;
			}
			tmp.push_back(CustomLib::VectorStringToNumber<long long>(CustomLib::SplitString(tab[i], ' ')));
		}
		mappings.push_back(tmp);
	}
	std::vector<long long> locations;
	tabSize = seeds.size();
	for (size_t i = 0; i < tabSize; i += 2) {
		std::cout << i << "/" << tabSize << "\r";
		long long seedStart = seeds[i];
		long long seedSize = seeds[i + 1];
		std::vector<std::pair<long long, long long>> tmp = { { seedStart, seedStart + seedSize } };
		for (std::vector<std::vector<long long>> mapping : mappings)
		{
			tmp = (Day5ApplyRange(tmp, mapping));
		}
		locations.push_back((*std::min_element(tmp.begin(), tmp.end())).first);
	}

	std::cout << "Part Two: " << *std::min_element(locations.begin(), locations.end()) << std::endl;
}

void DayHandler::Day6(FileHandler& fileHandler) {
	std::vector<std::string> tab = fileHandler.ReadFile("day6.txt");
	std::vector<int> times = CustomLib::VectorStringToNumber<int>(CustomLib::SplitString(tab[0], ' ', { 0 }));
	std::vector<int> distances = CustomLib::VectorStringToNumber<int>(CustomLib::SplitString(tab[1], ' ', { 0 }));
	int margin = 1;
	size_t tabSize = times.size();
	for (int i = 0; i < tabSize; i++)
	{
		std::cout << i << "/" << tabSize << "\r";
		int currentMargin = 0;
		for (int j = 1; j < times[i]; j++)
		{
			if ((times[i] - j) * j > distances[i])
				currentMargin++;
		}
		if (margin > 0)
			margin *= currentMargin;
	}

	std::cout << "Part One: " << margin << std::endl;

	long long time = std::stoll(std::accumulate(times.begin(), times.end(), std::string(),
		[](const std::string& a, int b) {
			return a + std::to_string(b);
		}));

	long long distance = std::stoll(std::accumulate(distances.begin(), distances.end(), std::string(),
		[](const std::string& a, int b) {
			return a + std::to_string(b);
		}));

	int newMargin = 0;
	for (int j = 1; j < time; j++)
	{
		if ((time - j) * j > distance)
			newMargin++;
	}

	std::cout << "Part Two: " << newMargin << std::endl;
}

void DayHandler::Day7(FileHandler& fileHandler) {
	std::vector<std::string> tab = fileHandler.ReadFile("day7.txt");
	std::vector<std::pair<std::string, int>> players;
	for (std::string element : tab)
	{
		std::vector<std::string> tmp = CustomLib::SplitString(element, ' ');
		players.push_back({ tmp[0], std::stoi(tmp[1]) });
	}
	std::vector<std::vector<std::pair<int, std::string>>> types = { {},{},{},{},{},{},{} };
	size_t tabSize = players.size();
	for (int i = 0; i < tabSize; i++)
	{
		std::cout << i << "/" << tabSize << "\r";
		int type = Day7GetType(players[i].first);
		types[type - 1].push_back({ i, players[i].first });
	}
	int size = 0, element = 0;
	long long money = 0;
	tabSize = types.size();
	for (std::vector<std::pair<int, std::string>> tmp : types)
	{
		std::cout << element++ << "/" << tabSize << "\r";
		std::vector<std::pair<int, std::string>> tmp1 = tmp;
		CustomLib::QuickSort(tmp1, 0, decltype(0)(tmp1.size() - 1), false, CustomLib::Day7Compare<decltype(tmp1)::value_type>);
		for (std::pair<int, std::string> player : tmp1)
			money += players[player.first].second * ++size;
	}

	std::cout << "Part One: " << money << std::endl;

	types = { {},{},{},{},{},{},{} };
	tabSize = players.size();
	for (int i = 0; i < players.size(); i++)
	{
		std::cout << i << "/" << tabSize << "\r";
		int type = Day7GetType(players[i].first, true);
		types[type - 1].push_back({ i, players[i].first });
	}
	size = 0;
	money = 0;
	element = 0;
	tabSize = types.size();
	for (std::vector<std::pair<int, std::string>> tmp : types)
	{
		std::cout << element++ << "/" << tabSize << "\r";
		std::vector<std::pair<int, std::string>> tmp1 = tmp;
		CustomLib::QuickSort(tmp1, 0, decltype(0)(tmp1.size() - 1), true, CustomLib::Day7Compare<decltype(tmp1)::value_type>);
		for (std::pair<int, std::string> player : tmp1)
			money += players[player.first].second * ++size;
	}

	std::cout << "Part Two: " << money << std::endl;
}

void DayHandler::Day8(FileHandler& fileHandler)
{
	std::vector<std::string> tab = fileHandler.ReadFile("day8.txt");
	std::string route = tab[0];
	std::unordered_map<std::string, std::pair<std::string, std::string>> map;

	for (int i = 2; i < tab.size(); i++)
	{
		std::vector<std::string> tmp = CustomLib::SplitString(tab[i], { '=','(',',',')',' ' });
		map[tmp[0]] = { tmp[1],tmp[2] };
	}

	std::string current = "AAA";
	int step = 0;
	while (current != "ZZZ")
	{
		char direction = route[step % route.size()];
		if (direction == 'L')
		{
			current = map[current].first;
		}
		else
		{
			current = map[current].second;
		}
		step++;
	}

	std::cout << "Part One: " << step << std::endl;

	std::vector<std::string> currents;
	long long stepsProduct = 1;
	step = 0;

	for (const auto& entry : map) {
		const std::string& key = entry.first;
		if (!key.empty() && key.back() == 'A') {
			currents.push_back(key);
		}
	}

	size_t tabSize = currents.size();
	for (int i = 0; i < tabSize; i++)
	{
		std::cout << i << "/" << tabSize << "\r";
		current = currents[i];
		//std::cout << current << " - ";
		step = 0;
		while (current[2] != 'Z')
		{
			char direction = route[step % route.size()];
			if (direction == 'L')
			{
				current = map[current].first;
			}
			else
			{
				current = map[current].second;
			}
			step++;
		}
		//std::cout << step << std::endl;
		stepsProduct = (step * stepsProduct) / std::gcd(step, stepsProduct);
	}

	std::cout << "Part Two: " << stepsProduct << std::endl;
}

void DayHandler::Day9(FileHandler& fileHandler)
{
	std::vector<std::string> tab = fileHandler.ReadFile("day9.txt");
	/*int testSum = 0;
	testSum += CustomLib::Extrapolation<int>({0,3,6,9,12,15},false);
	testSum += CustomLib::Extrapolation<int>({ 1,3,6,10,15,21 },false);
	testSum += CustomLib::Extrapolation<int>({ 10,13,16,21,30,45 },false);

	std::cout << "Test: " << testSum << std::endl;*/
	long long sum = 0;
	size_t tabSize = tab.size();
	int element = 0;
	for (std::string line : tab)
	{
		std::cout << element++ << "/" << tabSize << "\r";
		std::vector<long long> tmp = CustomLib::VectorStringToNumber<long long>(CustomLib::SplitString(line, ' '));
		long long tmp1 = CustomLib::Extrapolation<long long>(tmp);
		sum += tmp1;
	}
	std::cout << "Part One: " << sum << std::endl;

	sum = 0;
	element = 0;
	for (std::string line : tab)
	{
		std::cout << element++ << "/" << tabSize << "\r";
		std::vector<long long> tmp = CustomLib::VectorStringToNumber<long long>(CustomLib::SplitString(line, ' '));
		long long tmp1 = CustomLib::Extrapolation<long long>(tmp, false);
		sum += tmp1;
	}

	std::cout << "Part Two: " << sum << std::endl;
}

void DayHandler::Day10(FileHandler& fileHandler)
{
	std::vector<std::string> tab = fileHandler.ReadFile("day10.txt");
	std::vector<std::string> map;
	for (int i = 0; i < tab.size() * 3; i++)
	{
		std::string tmp = "";
		for (int j = 0; j < tab[0].length() * 3; j++)
			tmp += ".";
		map.push_back(tmp);
	}
	std::pair<int, int> sLocation = { -1,-1 };
	for (int i = 0; i < tab.size(); i++)
	{
		for (int j = 0; j < tab[i].length(); j++)
		{
			if (tab[i][j] == 'S')
			{
				sLocation = { i,j };
				break;
			}
		}
		if (sLocation.first != -1)
			break;
	}
	int pipesCurrrentValue = 1;
	std::vector<std::pair<int, int>> pipesCurrrentLocations;
	std::pair<std::vector<std::pair<int, int>>, std::vector<std::pair<int, int>>> Locations;
	std::vector<std::pair<int, int>> pipesPreviousLocations = { {sLocation.first,sLocation.second},{sLocation.first,sLocation.second} };
	if (tab[sLocation.first - 1][sLocation.second] == '|' || tab[sLocation.first - 1][sLocation.second] == '7' || tab[sLocation.first - 1][sLocation.second] == 'F')
		pipesCurrrentLocations.push_back({ sLocation.first - 1 ,sLocation.second });
	if (tab[sLocation.first][sLocation.second + 1] == '-' || tab[sLocation.first][sLocation.second + 1] == '7' || tab[sLocation.first][sLocation.second + 1] == 'J')
		pipesCurrrentLocations.push_back({ sLocation.first ,sLocation.second + 1 });
	if (tab[sLocation.first + 1][sLocation.second] == '|' || tab[sLocation.first + 1][sLocation.second] == 'L' || tab[sLocation.first + 1][sLocation.second] == 'J')
		pipesCurrrentLocations.push_back({ sLocation.first + 1,sLocation.second });
	if (tab[sLocation.first][sLocation.second - 1] == '-' || tab[sLocation.first][sLocation.second - 1] == 'L' || tab[sLocation.first][sLocation.second - 1] == 'F')
		pipesCurrrentLocations.push_back({ sLocation.first ,sLocation.second - 1 });

	map[sLocation.first * 3 + 1][sLocation.second * 3 + 1] = 'S';
	map[sLocation.first * 3][sLocation.second * 3 + 1] = 'O';
	map[sLocation.first * 3 + 1][sLocation.second * 3] = 'O';
	map[sLocation.first * 3 + 2][sLocation.second * 3 + 1] = 'O';
	map[sLocation.first * 3 + 1][sLocation.second * 3 + 2] = 'O';

	for (std::pair<int, int> pipeCurrentLocation : pipesCurrrentLocations)
	{
		//map[pipeCurrentLocation.first][pipeCurrentLocation.second] = tab[pipeCurrentLocation.first][pipeCurrentLocation.second];
		if (tab[pipeCurrentLocation.first][pipeCurrentLocation.second] == '|')
		{
			map[pipeCurrentLocation.first * 3 + 1][pipeCurrentLocation.second * 3 + 1] = 'O';
			map[pipeCurrentLocation.first * 3][pipeCurrentLocation.second * 3 + 1] = 'O';
			map[pipeCurrentLocation.first * 3 + 2][pipeCurrentLocation.second * 3 + 1] = 'O';
		}
		else if (tab[pipeCurrentLocation.first][pipeCurrentLocation.second] == '-')
		{
			map[pipeCurrentLocation.first * 3 + 1][pipeCurrentLocation.second * 3 + 1] = 'O';
			map[pipeCurrentLocation.first * 3 + 1][pipeCurrentLocation.second * 3] = 'O';
			map[pipeCurrentLocation.first * 3 + 1][pipeCurrentLocation.second * 3 + 2] = 'O';
		}
		else if (tab[pipeCurrentLocation.first][pipeCurrentLocation.second] == 'L')
		{
			map[pipeCurrentLocation.first * 3 + 1][pipeCurrentLocation.second * 3 + 1] = 'O';
			map[pipeCurrentLocation.first * 3][pipeCurrentLocation.second * 3 + 1] = 'O';
			map[pipeCurrentLocation.first * 3 + 1][pipeCurrentLocation.second * 3 + 2] = 'O';
		}
		else if (tab[pipeCurrentLocation.first][pipeCurrentLocation.second] == 'J')
		{
			map[pipeCurrentLocation.first * 3 + 1][pipeCurrentLocation.second * 3 + 1] = 'O';
			map[pipeCurrentLocation.first * 3][pipeCurrentLocation.second * 3 + 1] = 'O';
			map[pipeCurrentLocation.first * 3 + 1][pipeCurrentLocation.second * 3] = 'O';
		}
		else if (tab[pipeCurrentLocation.first][pipeCurrentLocation.second] == 'F')
		{
			map[pipeCurrentLocation.first * 3 + 1][pipeCurrentLocation.second * 3 + 1] = 'O';
			map[pipeCurrentLocation.first * 3 + 2][pipeCurrentLocation.second * 3 + 1] = 'O';
			map[pipeCurrentLocation.first * 3 + 1][pipeCurrentLocation.second * 3 + 2] = 'O';
		}
		else if (tab[pipeCurrentLocation.first][pipeCurrentLocation.second] == '7')
		{
			map[pipeCurrentLocation.first * 3 + 1][pipeCurrentLocation.second * 3 + 1] = 'O';
			map[pipeCurrentLocation.first * 3 + 2][pipeCurrentLocation.second * 3 + 1] = 'O';
			map[pipeCurrentLocation.first * 3 + 1][pipeCurrentLocation.second * 3] = 'O';
		}
	}

	while (true)
	{
		if (!Day10HandlePipe(&pipesPreviousLocations[0], &pipesCurrrentLocations[0], tab))
		{
			std::cout << "Wrong data!\n";
			break;
		}
		if (!Day10HandlePipe(&pipesPreviousLocations[1], &pipesCurrrentLocations[1], tab))
		{
			std::cout << "Wrong data!\n";
			break;
		}
		for (std::pair<int, int> pipeCurrentLocation : pipesCurrrentLocations)
		{
			//map[pipeCurrentLocation.first][pipeCurrentLocation.second] = tab[pipeCurrentLocation.first][pipeCurrentLocation.second];
			if (tab[pipeCurrentLocation.first][pipeCurrentLocation.second] == '|')
			{
				map[pipeCurrentLocation.first * 3 + 1][pipeCurrentLocation.second * 3 + 1] = 'O';
				map[pipeCurrentLocation.first * 3][pipeCurrentLocation.second * 3 + 1] = 'O';
				map[pipeCurrentLocation.first * 3 + 2][pipeCurrentLocation.second * 3 + 1] = 'O';
			}
			else if (tab[pipeCurrentLocation.first][pipeCurrentLocation.second] == '-')
			{
				map[pipeCurrentLocation.first * 3 + 1][pipeCurrentLocation.second * 3 + 1] = 'O';
				map[pipeCurrentLocation.first * 3 + 1][pipeCurrentLocation.second * 3] = 'O';
				map[pipeCurrentLocation.first * 3 + 1][pipeCurrentLocation.second * 3 + 2] = 'O';
			}
			else if (tab[pipeCurrentLocation.first][pipeCurrentLocation.second] == 'L')
			{
				map[pipeCurrentLocation.first * 3 + 1][pipeCurrentLocation.second * 3 + 1] = 'O';
				map[pipeCurrentLocation.first * 3][pipeCurrentLocation.second * 3 + 1] = 'O';
				map[pipeCurrentLocation.first * 3 + 1][pipeCurrentLocation.second * 3 + 2] = 'O';
			}
			else if (tab[pipeCurrentLocation.first][pipeCurrentLocation.second] == 'J')
			{
				map[pipeCurrentLocation.first * 3 + 1][pipeCurrentLocation.second * 3 + 1] = 'O';
				map[pipeCurrentLocation.first * 3][pipeCurrentLocation.second * 3 + 1] = 'O';
				map[pipeCurrentLocation.first * 3 + 1][pipeCurrentLocation.second * 3] = 'O';
			}
			else if (tab[pipeCurrentLocation.first][pipeCurrentLocation.second] == 'F')
			{
				map[pipeCurrentLocation.first * 3 + 1][pipeCurrentLocation.second * 3 + 1] = 'O';
				map[pipeCurrentLocation.first * 3 + 2][pipeCurrentLocation.second * 3 + 1] = 'O';
				map[pipeCurrentLocation.first * 3 + 1][pipeCurrentLocation.second * 3 + 2] = 'O';
			}
			else if (tab[pipeCurrentLocation.first][pipeCurrentLocation.second] == '7')
			{
				map[pipeCurrentLocation.first * 3 + 1][pipeCurrentLocation.second * 3 + 1] = 'O';
				map[pipeCurrentLocation.first * 3 + 2][pipeCurrentLocation.second * 3 + 1] = 'O';
				map[pipeCurrentLocation.first * 3 + 1][pipeCurrentLocation.second * 3] = 'O';
			}
		}
		pipesCurrrentValue++;
		if (pipesCurrrentLocations[0].first == pipesCurrrentLocations[1].first && pipesCurrrentLocations[0].second == pipesCurrrentLocations[1].second)
			break;
	}

	fileHandler.WriteFile("Day10Map.txt", map);
	std::cout << "Part One: " << pipesCurrrentValue << std::endl;

	std::vector<std::pair<int, int>> tmp;
	size_t tabSize = map.size();
	for (int i = 0; i < map.size(); i++)
	{
		std::cout << i << "/" << tabSize << "\r";
		for (int j = 0; j < map[i].length(); j++)
		{
			if (map[i][j] == 'O')
			{
				if (map[i + 1][j + 1] != '.')
				{
					std::cout << "Wrong data!\n";
					return;
				}
				map[i + 1][j + 1] = 'I';
				tmp.push_back({ i + 1,j + 1 });
				break;
			}
		}
		if (tmp.size())
			break;
	}
	int i = 0;
	do
	{
		std::pair<int, int> tmp1 = tmp[i];
		if (map[tmp1.first - 1][tmp1.second] == '.')
		{
			map[tmp1.first - 1][tmp1.second] = 'I';
			tmp.push_back({ tmp1.first - 1,tmp1.second });
		}
		if (map[tmp1.first + 1][tmp1.second] == '.')
		{
			map[tmp1.first + 1][tmp1.second] = 'I';
			tmp.push_back({ tmp1.first + 1,tmp1.second });
		}
		if (map[tmp1.first][tmp1.second - 1] == '.')
		{
			map[tmp1.first][tmp1.second - 1] = 'I';
			tmp.push_back({ tmp1.first,tmp1.second - 1 });
		}
		if (map[tmp1.first][tmp1.second + 1] == '.')
		{
			map[tmp1.first][tmp1.second + 1] = 'I';
			tmp.push_back({ tmp1.first,tmp1.second + 1 });
		}
		i++;
	} while (i < tmp.size());
	fileHandler.WriteFile("Day10Map1.txt", map);

	int count = 0;
	for (int i = 0; i < map.size(); i += 3)
	{
		for (int j = 0; j < map[i + 1].length(); j += 3)
		{
			if (map[i][j] == 'I' && map[i + 1][j] == 'I' && map[i - 1][j] == 'I' && map[i][j + 1] == 'I' && map[i][j - 1] == 'I' && map[i + 1][j + 1] == 'I' && map[i - 1][j - 1] == 'I' && map[i + 1][j - 1] == 'I' && map[i - 1][j + 1] == 'I')
				count++;
		}
	}
	std::cout << "Part Two: " << count << std::endl;

	std::cout << "\nGenerating pipe map...\n";

	for (int i = 0; i < map.size(); i += 3)
	{
		for (int j = 0; j < map[i].length(); j += 3)
		{
			// Comment this fragment for get filled inside
			for (int k = 0; k < 3; k++)
			{
				for (int l = 0; l < 3; l++)
				{
					map[i + k][j + l] = '.';
				}
			}
			// end of fragment
			if (tab[i / 3][j / 3] == '|')
			{
				map[i + 1][j + 1] = 'O';
				map[i][j + 1] = 'O';
				map[i + 2][j + 1] = 'O';
			}
			else if (tab[i / 3][j / 3] == '-')
			{
				map[i + 1][j + 1] = 'O';
				map[i + 1][j] = 'O';
				map[i + 1][j + 2] = 'O';
			}
			else if (tab[i / 3][j / 3] == 'L')
			{
				map[i + 1][j + 1] = 'O';
				map[i][j + 1] = 'O';
				map[i + 1][j + 2] = 'O';
			}
			else if (tab[i / 3][j / 3] == 'J')
			{
				map[i + 1][j + 1] = 'O';
				map[i][j + 1] = 'O';
				map[i + 1][j] = 'O';
			}
			else if (tab[i / 3][j / 3] == 'F')
			{
				map[i + 1][j + 1] = 'O';
				map[i + 2][j + 1] = 'O';
				map[i + 1][j + 2] = 'O';
			}
			else if (tab[i / 3][j / 3] == '7')
			{
				map[i + 1][j + 1] = 'O';
				map[i + 2][j + 1] = 'O';
				map[i + 1][j] = 'O';
			}
		}
	}
	bool isMapGenerated = fileHandler.WriteFile("Day10Map2.txt", map);
	if (isMapGenerated)
		std::cout << "Map generated properly to file Day10Map2.txt\n";
	else
		std::cout << "An error occured while trying to save map!\n";
}

void DayHandler::Day11(FileHandler& fileHandler)
{
	std::vector<std::string> tab = fileHandler.ReadFile("day11.txt");
	std::vector<int> expansionColumns;
	std::vector<int> expansionRows;

	// Expand X
	for (int i = 0; i < tab[0].length(); i++)
	{
		int count = 0;
		for (int j = 0; j < tab.size(); j++)
		{
			if (tab[j][i] == '#')
				break;
			count++;
		}
		if (count == tab.size())
		{
			expansionColumns.push_back(i);
		}
	}
	// Expand Y
	for (int i = 0; i < tab.size(); i++)
	{
		std::string count = "";
		for (int j = 0; j < tab[i].length(); j++)
		{
			if (tab[i][j] == '#')
				break;
			count += '.';
		}
		if (count.length() == tab[i].length())
		{
			expansionRows.push_back(i);
		}
	}
	// Find all galaxies
	std::vector<std::pair<int, int>> galaxies;
	size_t tabSize = tab.size();
	for (int i = 0; i < tab.size(); i++)
	{
		std::cout << i << "/" << tabSize << "\r";
		for (int j = 0; j < tab[i].length(); j++)
		{
			if (tab[i][j] == '#')
				galaxies.push_back({ i,j });
		}
	}
	// get distance between all galaxies
	long long distanceSum = 0;
	int multiplayer = 2;
	tabSize = galaxies.size();
	for (int i = 0; i < galaxies.size() - 1; i++)
	{
		std::cout << i << "/" << tabSize << "\r";
		for (int j = i + 1; j < galaxies.size(); j++)
		{
			distanceSum += std::abs(galaxies[i].first - galaxies[j].first) + std::abs(galaxies[i].second - galaxies[j].second);
			for (int expansionColumn : expansionColumns)
			{
				if (CustomLib::IsWithinRange(expansionColumn, { galaxies[i].second,galaxies[j].second }))
					distanceSum += 1 * multiplayer - 1;
			}
			for (int expansionRow : expansionRows)
			{
				if (CustomLib::IsWithinRange(expansionRow, { galaxies[i].first,galaxies[j].first }))
					distanceSum += 1 * multiplayer - 1;
			}
		}
	}

	std::cout << "Part One: " << distanceSum << std::endl;
	// get distance between all galaxies
	distanceSum = 0;
	if(tab.size() > 20)
		multiplayer = 1000000;
	else
		multiplayer = 100;
	for (int i = 0; i < galaxies.size() - 1; i++)
	{
		std::cout << i << "/" << tabSize << "\r";
		for (int j = i + 1; j < galaxies.size(); j++)
		{
			distanceSum += std::abs(galaxies[i].first - galaxies[j].first) + std::abs(galaxies[i].second - galaxies[j].second);
			for (int expansionColumn : expansionColumns)
			{
				if (CustomLib::IsWithinRange(expansionColumn, { galaxies[i].second,galaxies[j].second }))
					distanceSum += 1 * multiplayer - 1;
			}
			for (int expansionRow : expansionRows)
			{
				if (CustomLib::IsWithinRange(expansionRow, { galaxies[i].first,galaxies[j].first }))
					distanceSum += 1 * multiplayer - 1;
			}
		}
	}

	std::cout << "Part Two: " << distanceSum << std::endl;
}

void DayHandler::Day12(FileHandler& fileHandler)
{
	std::vector<std::string> tab = fileHandler.ReadFile("day12.txt");
	long long count = 0;
	size_t tabSize = tab.size();

	for (int i = 0; i < tabSize; i++)
	{
		std::cout << i << "/" << tabSize << "\r";
		std::vector<std::string> tmp = CustomLib::SplitString(tab[i], ' ');
		std::string conditionReport = tmp[0];
		std::vector<int> damagedGroups = CustomLib::VectorStringToNumber<int>(CustomLib::SplitString(tmp[1], ','));
		RP.clear();
		count += Day12CountOccurencies(conditionReport, damagedGroups);
	}

	std::cout << "Part One: " << count << std::endl;

	count = 0;

	for (int i = 0; i < tabSize; i++)
	{
		std::cout << i << "/" << tabSize << "\r";
		std::vector<std::string> tmp = CustomLib::SplitString(tab[i], ' ');
		std::string conditionReport = tmp[0] + "?" + tmp[0] + "?" + tmp[0] + "?" + tmp[0] + "?" + tmp[0];
		std::vector<int> tmpdamagedGroups = CustomLib::VectorStringToNumber<int>(CustomLib::SplitString(tmp[1], ','));
		std::vector<int> damagedGroups;
		for (int i = 0; i < 5; ++i) {
			damagedGroups.insert(damagedGroups.end(), tmpdamagedGroups.begin(), tmpdamagedGroups.end());
		}
		RP.clear();
		count += Day12CountOccurencies(conditionReport, damagedGroups);
		//Day12CountOccurencies(conditionReport, damagedGroups);
	}

	std::cout << "Part Two: " << count << std::endl;
}

void DayHandler::Day13(FileHandler& fileHandler)
{
	std::vector<std::string> tab = fileHandler.ReadFile("day13.txt");
	std::vector<std::vector<std::string>> patterns;
	long long count = 0;
	std::vector<long long> counts;
	patterns.push_back({});
	{
		int i = 0;
		for (std::string line : tab)
		{
			if (line == "")
			{
				patterns.push_back({});
				i++;
			}
			else
			{
				patterns[i].push_back(line);
			}
		}
	}
	size_t tabSize = patterns.size();
	for (int i = 0; i < tabSize; i++)
	{
		std::cout << i << "/" << tabSize << "\r";
		std::vector<std::string> pattern = patterns[i];
		bool mirrorFound = false;
		for (int j = 0; j < pattern.size() - 1; j++)
		{
			if (pattern[j] == pattern[j + 1])
			{
				mirrorFound = true;
				for (int k = 1; k < std::min(j + 1, static_cast<int>(pattern.size() - j - 1)); k++)
				{
					if (pattern[j - k] != pattern[j + 1 + k])
					{
						mirrorFound = false;
						break;
					}
				}
			}
			if (mirrorFound)
			{
				count += (j + 1) * 100;
				counts.push_back((j + 1) * 100);
				break;
			}
		}
		if (mirrorFound)
			continue;

		for (int j = 0; j < pattern[0].length() - 1; j++)
		{
			bool arePatternsEqual = true;
			for (int k = 0; k < pattern.size(); k++)
			{
				if (pattern[k][j] != pattern[k][j + 1])
				{
					arePatternsEqual = false;
					break;
				}
			}
			if (arePatternsEqual == true)
			{
				mirrorFound = true;
				for (int k = 1; k < std::min(j + 1, static_cast<int>(pattern[0].length() - j - 1)); k++)
				{
					for (std::string line : pattern)
					{
						if (line[j - k] != line[j + k + 1])
						{
							mirrorFound = false;
							break;
						}
					}
					if (!mirrorFound)
						break;
				}
				if (mirrorFound)
				{
					count += (j + 1);
					counts.push_back(j + 1);
					break;
				}
			}
		}
	}

	std::cout << "Part One: " << count << std::endl;
	count = 0;

	for (int i = 0; i < tabSize; i++)
	{
		std::cout << i << "/" << tabSize << "\r";
		std::vector<std::string> pattern = patterns[i];
		bool mirrorFound = false;
		for (int j = 0; j < pattern.size() - 1; j++)
		{
			int smudges = 0;
			bool arePatternsEqual = true;
			// pattern[j] == pattern[j + 1]
			for (int k = 0; k < pattern[j].length(); k++)
			{
				if (pattern[j][k] != pattern[j + 1][k])
				{
					smudges++;
					if (smudges > 1)
					{
						arePatternsEqual = false;
						break;
					}
				}
			}
			if (arePatternsEqual)
			{
				mirrorFound = true;
				for (int k = 1; k < std::min(j + 1, static_cast<int>(pattern.size() - j - 1)); k++)
				{
					for (int l = 0; l < pattern[j - k].length(); l++)
					{
						if (pattern[j - k][l] != pattern[j + 1 + k][l])
						{
							smudges++;
							if (smudges > 1)
							{
								mirrorFound = false;
								break;
							}
						}
					}
					if (!mirrorFound)
						break;
				}
			}
			if (mirrorFound)
			{
				if (counts[i] == (j + 1) * 100)
					mirrorFound = false;
				else
				{
					count += ((j + 1) * 100);
					break;
				}
			}
		}
		if (mirrorFound)
			continue;
		for (int j = 0; j < pattern[0].length() - 1; j++)
		{
			bool arePatternsEqual = true;
			int smudges = 0;
			for (int k = 0; k < pattern.size(); k++)
			{
				if (pattern[k][j] != pattern[k][j + 1])
				{
					smudges++;
					if (smudges > 1)
					{
						arePatternsEqual = false;
						break;
					}
				}
			}
			if (arePatternsEqual == true)
			{
				mirrorFound = true;
				for (int k = 1; k < std::min(j + 1, static_cast<int>(pattern[0].length() - j - 1)); k++)
				{
					for (std::string line : pattern)
					{
						if (line[j - k] != line[j + k + 1])
						{
							smudges++;
							if (smudges > 1)
							{
								mirrorFound = false;
								break;
							}
						}
					}
					if (!mirrorFound)
						break;
				}
				if (mirrorFound)
				{
					if (counts[i] == (j + 1))
						mirrorFound = false;
					else
					{
						count += (j + 1);
						break;
					}
				}
			}
		}
	}

	std::cout << "Part Two: " << count << std::endl;
}

void DayHandler::Day14(FileHandler& fileHandler)
{
	std::vector<std::string> tab = fileHandler.ReadFile("day14.txt");
	std::vector<std::string> tab1 = tab;
	std::vector<std::string> tab2 = tab;
	size_t tabSize = tab1[0].length();
	for (int i = 0; i < tab1[0].length(); i++)
	{
		std::cout << i << "/" << tabSize << "\r";
		for (int j = 0; j < tab1.size(); j++)
		{
			if (tab1[j][i] == 'O')
			{
				if (j != 0)
					tab1[j][i] = '.';
				for (int k = j - 1; k >= 0; k--)
				{
					if (tab1[k][i] == 'O' || tab1[k][i] == '#')
					{
						tab1[k + 1][i] = 'O';
						break;
					}
					else if (k == 0)
						tab1[k][i] = 'O';
				}
			}
		}
	}
	//fileHandler.WriteFile("Day14Map.txt", tab);
	tabSize = tab1.size();
	long long count = 0;
	for (int i = 0; i < tab1.size(); i++)
	{
		std::cout << i << "/" << tabSize << "\r";
		for (int j = 0; j < tab1[i].length(); j++)
		{
			if (tab1[i][j] == 'O')
				count += tabSize - i;
		}
	}

	std::cout << "Part One: " << count << std::endl;

	std::vector<std::vector<std::string>> previousTabs;
	previousTabs.push_back(tab2);
	long long lastRollIndex = 0, previousTabLastRollIndex = 0;
	for (int i = 0; i < 1000000000; i++)
	{
		std::cout << i << "/1000000000\r";
		for (int j = 0; j < tab2[0].length(); j++)
		{
			for (int k = 0; k < tab2.size(); k++)
			{
				if (tab2[k][j] == 'O')
				{
					if (k != 0)
						tab2[k][j] = '.';
					for (int l = k - 1; l >= 0; l--)
					{
						if (tab2[l][j] == 'O' || tab2[l][j] == '#')
						{
							tab2[l + 1][j] = 'O';
							break;
						}
						else if (l == 0)
							tab2[l][j] = 'O';
					}
				}
			}
		}
		for (int j = 0; j < tab2.size(); j++)
		{
			for (int k = 0; k < tab2[j].length(); k++)
			{
				if (tab2[j][k] == 'O')
				{
					if (k != 0)
						tab2[j][k] = '.';
					for (int l = k - 1; l >= 0; l--)
					{
						if (tab2[j][l] == 'O' || tab2[j][l] == '#')
						{
							tab2[j][l + 1] = 'O';
							break;
						}
						else if (l == 0)
							tab2[j][l] = 'O';
					}
				}
			}
		}
		for (int j = tab2[0].length() - 1; j >= 0; j--)
		{
			for (int k = tab2.size() - 1; k >= 0; k--)
			{
				if (tab2[k][j] == 'O')
				{
					if (k != tab2.size() - 1)
						tab2[k][j] = '.';
					for (int l = k + 1; l < tab2.size(); l++)
					{
						if (tab2[l][j] == 'O' || tab2[l][j] == '#')
						{
							tab2[l - 1][j] = 'O';
							break;
						}
						else if (l == tab2.size() - 1)
							tab2[l][j] = 'O';
					}
				}
			}
		}
		for (int j = tab2.size() - 1; j >= 0; j--)
		{
			for (int k = tab2[j].length() - 1; k >= 0; k--)
			{
				if (tab2[j][k] == 'O')
				{
					if (k != tab2[j].length() - 1)
						tab2[j][k] = '.';
					for (int l = k + 1; l < tab2[j].length(); l++)
					{
						if (tab2[j][l] == 'O' || tab2[j][l] == '#')
						{
							tab2[j][l - 1] = 'O';
							break;
						}
						else if (l == tab2[j].length() - 1)
							tab2[j][l] = 'O';
					}
				}
			}
		}
		bool tabExists = false;
		for (int j = 0; j < previousTabs.size(); j++)
		{
			if (previousTabs[j] == tab2)
			{
				previousTabLastRollIndex = j;
				tabExists = true;
				break;
			}
		}
		if (tabExists)
		{
			lastRollIndex = i;
			break;
		}
		previousTabs.push_back(tab2);
	}
	tab2 = previousTabs[previousTabLastRollIndex + (1000000000 - lastRollIndex - 1) % (previousTabs.size() - previousTabLastRollIndex)];

	tabSize = tab2.size();
	count = 0;
	for (int i = 0; i < tab2.size(); i++)
	{
		std::cout << i << "/" << tabSize << "\r";
		for (int j = 0; j < tab2[i].length(); j++)
		{
			if (tab2[i][j] == 'O')
				count += tabSize - i;
		}
	}

	std::cout << "Part Two: " << count << std::endl;
}

void DayHandler::Day15(FileHandler& fileHandler)
{
	std::vector<std::string> tab = fileHandler.ReadFile("day15.txt");
	tab = CustomLib::SplitString(tab[0], ',');

	long long sum = 0;
	for (std::string text : tab)
	{
		long long hash = 0;
		for (char tmp : text)
		{
			hash += tmp;
			hash *= 17;
			hash %= 256;
		}
		sum += hash;
	}

	std::cout << "Part One: " << sum << std::endl;

	std::vector<std::vector<std::pair<std::string, int>>> container;
	for (int i = 0; i < 256; i++)
		container.push_back({});
	for (std::string text : tab)
	{
		if (text[text.length() - 1] == '-')
		{
			std::string tmp = text.substr(0, text.length() - 1);
			long long hash = 0;
			for (char tmp1 : tmp)
			{
				hash += tmp1;
				hash *= 17;
				hash %= 256;
			}
			for (int i = 0; i < container[hash].size(); i++)
			{
				if (container[hash][i].first == tmp)
				{
					container[hash].erase(container[hash].begin() + i);
					break;
				}
			}
		}
		else
		{
			std::string tmp = text.substr(0, text.length() - 2);
			long long hash = 0;
			bool isChanged = false;
			for (char tmp1 : tmp)
			{
				hash += tmp1;
				hash *= 17;
				hash %= 256;
			}
			for (int i = 0; i < container[hash].size(); i++)
			{
				if (container[hash][i].first == tmp)
				{
					container[hash][i].second = std::stoi(text.substr(text.length() - 1, 1));
					isChanged = true;
					break;
				}
			}
			if (!isChanged)
				container[hash].push_back({ tmp,std::stoi(text.substr(text.length() - 1, 1)) });
		}
	}

	long long focusingPower = 0;
	for (int i = 0; i < container.size(); i++)
	{
		for (int j = 0; j < container[i].size(); j++)
		{
			focusingPower += (i + 1) * (j + 1) * container[i][j].second;
		}
	}

	std::cout << "Part Two: " << focusingPower << std::endl;
}

void DayHandler::Day16(FileHandler& fileHandler)
{
	std::vector<std::string> tab = fileHandler.ReadFile("day16.txt");
	std::vector<std::string> map = tab;

	Day16DrawMap(map, tab);
	long int count = 0;

	//fileHandler.WriteFile("Day16Map.txt", map);

	for (std::string line : map)
		for (char tmp : line)
			if (tmp == '#')
				count++;

	std::cout << "Part One: " << count << std::endl;
	count = 0;
	size_t tabSize = tab.size() * 2 + tab[0].length() * 2;

	for (int i = 0; i < tab.size(); i++)
	{
		std::cout << i * 2 << "/" << tabSize << "\r";
		std::vector<std::string> tmp1 = tab;
		Day16DrawMap(tmp1, tab, i, 0, 0, 1);
		long int tmpCount = 0;
		for (std::string line : tmp1)
			for (char tmp : line)
				if (tmp == '#')
					tmpCount++;
		count = std::max(count, tmpCount);
		tmpCount = 0;

		std::cout << i * 2 + 1 << "/" << tabSize << "\r";
		std::vector<std::string> tmp2 = tab;
		Day16DrawMap(tmp2, tab, i, tmp2.size() - 1, 0, -1);
		for (std::string line : tmp2)
			for (char tmp : line)
				if (tmp == '#')
					tmpCount++;
		count = std::max(count, tmpCount);
	}
	for (int i = 0; i < tab[0].length(); i++)
	{
		std::cout << i * 2 + tab.size() * 2 << "/" << tabSize << "\r";
		std::vector<std::string> tmp1 = tab;
		Day16DrawMap(tmp1, tab, 0, i);
		long int tmpCount = 0;
		for (std::string line : tmp1)
			for (char tmp : line)
				if (tmp == '#')
					tmpCount++;
		count = std::max(count, tmpCount);
		tmpCount = 0;

		std::cout << i * 2 + tab.size() * 2 + 1 << "/" << tabSize << "\r";
		std::vector<std::string> tmp2 = tab;
		Day16DrawMap(tmp2, tab, tmp2[0].length() - 1, i, -1);
		for (std::string line : tmp2)
			for (char tmp : line)
				if (tmp == '#')
					tmpCount++;
		count = std::max(count, tmpCount);
	}

	std::cout << "Part Two: " << count << std::endl;
}

struct State {
	int distance, height, width, direction, indirection;
	bool operator<(const State& o) const {
		return distance > o.distance;
	}
};

void DayHandler::Day17(FileHandler& fileHandler)
{
	std::vector<std::string> tab = fileHandler.ReadFile("day17.txt");
	std::vector<std::vector<int>> map;
	for (std::string line : tab)
	{
		map.push_back({});
		for (char tmp : line)
			map[map.size() - 1].push_back(tmp - '0');
	}

	size_t mapHeight = map.size();
	size_t mapWidth = map[0].size();
	std::priority_queue<State> queue;
	queue.push({ 0, 0, 0, -1, -1 });
	std::unordered_map<std::string, int> distancemap;

	while (!queue.empty())
	{
		State s = queue.top();
		queue.pop();
		std::string  key = std::to_string(s.height) + "," + std::to_string(s.width) + "," + std::to_string(s.direction) + "," + std::to_string(s.indirection);
		if (distancemap.find(key) != distancemap.end())
			continue;
		distancemap[key] = s.distance;
		std::vector<std::vector<int>> directions = { {-1,0},{0,1},{1,0},{0,-1} };
		for (int i = 0; i < directions.size(); i++)
		{
			int height = s.height + directions[i][0];
			int width = s.width + directions[i][1];
			int newDirection = i;
			int newIndirection = (newDirection != s.direction) ? 1 : s.indirection + 1;

			bool isNotReverse = ((newDirection + 2) % 4 != s.direction);
			bool isValid = (newIndirection <= 3);

			if (0 <= height && height < mapHeight && 0 <= width && width < mapWidth && isNotReverse && isValid)
			{
				int cost = map[height][width];
				queue.push({ s.distance + cost, height, width, newDirection, newIndirection });
			}
		}
	}

	long long minHeatLoss = std::numeric_limits<long long>::max();
	for (auto& key : distancemap)
	{
		std::vector<int> tmp = CustomLib::VectorStringToNumber<int>(CustomLib::SplitString(key.first, ','));
		if (tmp[0] == mapHeight - 1 && tmp[1] == mapWidth - 1)
			minHeatLoss = std::min(minHeatLoss, static_cast<long long>(key.second));
	}

	std::cout << "Part One: " << minHeatLoss << std::endl;

	queue = std::priority_queue<State>();
	queue.push({ 0, 0, 0, -1, -1 });
	distancemap.clear();

	while (!queue.empty())
	{
		State s = queue.top();
		queue.pop();
		std::string  key = std::to_string(s.height) + "," + std::to_string(s.width) + "," + std::to_string(s.direction) + "," + std::to_string(s.indirection);
		if (distancemap.find(key) != distancemap.end())
			continue;
		distancemap[key] = s.distance;
		std::vector<std::vector<int>> directions = { {-1,0},{0,1},{1,0},{0,-1} };
		for (int i = 0; i < directions.size(); i++)
		{
			int height = s.height + directions[i][0];
			int width = s.width + directions[i][1];
			int newDirection = i;
			int newIndirection = (newDirection != s.direction) ? 1 : s.indirection + 1;

			bool isNotReverse = ((newDirection + 2) % 4 != s.direction);
			bool isValid = (newIndirection <= 10 && (newDirection == s.direction || s.indirection >= 4 || s.indirection == -1));

			if (0 <= height && height < mapHeight && 0 <= width && width < mapWidth && isNotReverse && isValid)
			{
				int cost = map[height][width];
				queue.push({ s.distance + cost, height, width, newDirection, newIndirection });
			}
		}
	}

	minHeatLoss = std::numeric_limits<long long>::max();
	for (auto& key : distancemap)
	{
		std::vector<int> tmp = CustomLib::VectorStringToNumber<int>(CustomLib::SplitString(key.first, ','));
		if (tmp[0] == mapHeight - 1 && tmp[1] == mapWidth - 1)
			minHeatLoss = std::min(minHeatLoss, static_cast<long long>(key.second));
	}

	std::cout << "Part Two: " << minHeatLoss << std::endl;
}

void DayHandler::Day18(FileHandler& fileHandler)
{
	std::vector<std::string> tab = fileHandler.ReadFile("day18.txt");
	std::vector<std::vector<std::string>> digPlan = CustomLib::SplitString(tab, ' ');
	std::vector<std::vector<char>> map = { {'#'} };
	std::pair<int, int> current = { 0,0 }, start = { 0,0 };
	for (std::vector<std::string> instruction : digPlan)
	{
		if (instruction[0] == "R")
		{
			for (int i = 0; i < std::stoi(instruction[1]); i++)
			{
				current.first++;
				if (current.first >= map[current.second].size())
				{
					for (int j = 0; j < map.size(); j++)
						map[j].push_back('.');
				}
				map[current.second][current.first] = '#';
			}
		}
		else if (instruction[0] == "D")
		{
			for (int i = 0; i < std::stoi(instruction[1]); i++)
			{
				current.second++;
				if (current.second >= map.size())
				{
					map.push_back({});
					for (int j = 0; j < map[0].size(); j++)
						map[map.size() - 1].push_back('.');
				}
				map[current.second][current.first] = '#';
			}
		}
		else if (instruction[0] == "L")
		{
			for (int i = 0; i < std::stoi(instruction[1]); i++)
			{
				current.first--;
				if (current.first < 0)
				{
					for (int j = 0; j < map.size(); j++)
						map[j].insert(map[j].begin(), '.');
					current.first++;
					start.first++;
				}
				map[current.second][current.first] = '#';
			}
		}
		else if (instruction[0] == "U")
		{
			for (int i = 0; i < std::stoi(instruction[1]); i++)
			{
				current.second--;
				if (current.second < 0)
				{
					std::vector<char> tmp;
					for (int j = 0; j < map[0].size(); j++)
						tmp.push_back('.');
					map.insert(map.begin(), tmp);
					current.second++;
					start.second++;
				}
				map[current.second][current.first] = '#';
			}
		}
	}
	std::cout << "Generating map..." << std::endl;
	if (fileHandler.WriteFile("Day18Map.txt", map))
		std::cout << "Map generated properly to file Day18Map.txt" << std::endl;
	else
		std::cout << "Map generation failed" << std::endl;

	std::vector<std::vector<char>> map1 = map;
	{
		std::vector<std::pair<int, int>> tmp;
		for (int i = 0; i < map1.size(); i++)
		{
			for (int j = 0; j < map1[i].size(); j++)
				if (map1[i][j] == '#' && map1[i + 1][j + 1] == '.')
				{
					tmp.push_back({ i + 1,j + 1 });
					break;
				}
			if (tmp.size())
				break;
		}

		int i = 0;
		while (i < tmp.size())
		{
			std::pair<int, int> tmp1 = tmp[i];
			if (map1[tmp1.first - 1][tmp1.second] == '.')
			{
				map1[tmp1.first - 1][tmp1.second] = '#';
				tmp.push_back({ tmp1.first - 1,tmp1.second });
			}
			if (map1[tmp1.first + 1][tmp1.second] == '.')
			{
				map1[tmp1.first + 1][tmp1.second] = '#';
				tmp.push_back({ tmp1.first + 1,tmp1.second });
			}
			if (map1[tmp1.first][tmp1.second - 1] == '.')
			{
				map1[tmp1.first][tmp1.second - 1] = '#';
				tmp.push_back({ tmp1.first,tmp1.second - 1 });
			}
			if (map1[tmp1.first][tmp1.second + 1] == '.')
			{
				map1[tmp1.first][tmp1.second + 1] = '#';
				tmp.push_back({ tmp1.first,tmp1.second + 1 });
			}
			i++;
		}
	}

	std::cout << "Generating map..." << std::endl;
	if (fileHandler.WriteFile("Day18Map1.txt", map1))
		std::cout << "Map generated properly to file Day18Map1.txt" << std::endl;
	else
		std::cout << "Map generation failed" << std::endl;

	long long count = 0;
	for (std::vector<char> line : map1)
		for (char tmp : line)
			if (tmp == '#')
				count++;

	std::cout << "Part One: " << count << std::endl;

	std::vector<std::vector<std::string>> digPlan1;
	for (std::vector<std::string> instruction : digPlan)
	{
		std::string direction = instruction[2].substr(instruction[2].length() - 2, 1);
		std::string distance = instruction[2].substr(2, instruction[2].length() - 4);
		distance = std::to_string(std::stoi(distance, nullptr, 16));
		if (direction == "0")
			direction = "R";
		else if (direction == "1")
			direction = "D";
		else if (direction == "2")
			direction = "L";
		else if (direction == "3")
			direction = "U";
		digPlan1.push_back({ direction,distance });
	}

	std::vector<std::pair<long long, long long>> points;
	points.push_back({ 0,0 });

	for (std::vector<std::string> instruction : digPlan1)
	{
		if (instruction[0] == "U")
			points.push_back({ points.back().first,points.back().second - std::stoi(instruction[1]) });
		else if (instruction[0] == "D")
			points.push_back({ points.back().first,points.back().second + std::stoi(instruction[1]) });
		else if (instruction[0] == "L")
			points.push_back({ points.back().first - std::stoi(instruction[1]),points.back().second });
		else if (instruction[0] == "R")
			points.push_back({ points.back().first + std::stoi(instruction[1]),points.back().second });
	}
	points.pop_back();
	std::cout << "Part Two: " << std::to_string(static_cast<long long>(CustomLib::CalculatePolygonArea(points) + std::round(static_cast<long double>(CustomLib::CalculatePolygonPerimeter(points) + 1) / 2))) << std::endl;
}

void DayHandler::Day19(FileHandler& fileHandler)
{
	std::vector<std::string> tab = fileHandler.ReadFile("day19.txt");
	std::unordered_map < std::string, std::vector<Instruction>> workflows;
	std::vector<std::unordered_map<std::string, int>> parts;
	{
		int i = 0;
		while (tab[i] != "")
		{
			std::vector<std::string> tmp = CustomLib::SplitString(tab[i], { '{','}' });
			std::string key = tmp[0];
			std::vector<std::string> tmp1 = CustomLib::SplitString(tmp[1], ',');
			std::vector<Instruction> tmp2;
			for (std::string tmp3 : tmp1)
			{
				std::vector<std::string> tmp4 = CustomLib::SplitString(tmp3, { '<','>',':' });
				if (tmp4.size() <= 1)
					tmp2.push_back({ '=',{tmp4[0]} });
				else
				{
					char type;
					if (tmp3.find('<') != std::string::npos)
						type = '<';
					else if (tmp3.find('>') != std::string::npos)
						type = '>';
					tmp2.push_back({ type,tmp4 });
				}
			}
			workflows.emplace(key, tmp2);
			i++;
		}
		while (++i < tab.size())
		{
			std::vector<std::string> tmp = CustomLib::SplitString(tab[i], { '{','}','=',',' });
			std::unordered_map<std::string, int> tmp1;
			for (int i = 0; i < tmp.size(); i += 2)
				tmp1.emplace(tmp[i], std::stoi(tmp[i + 1]));
			parts.push_back(tmp1);
		}
	}
	long long sum = 0;
	for (std::unordered_map<std::string, int>& part : parts)
	{
		if (Day19HandleInstructions(workflows, part) == 'A')
		{
			for (auto& tmp : part)
				sum += tmp.second;
		}
	}
	std::cout << "Part One: " << sum << std::endl;

	std::vector<std::pair<std::unordered_map<std::string, int>, std::unordered_map<std::string, int>> > ranges = Day19GetAllRanges(workflows, workflows.at("in"), { {"x" , 1},{"m",1},{"a",1},{"s",1} }, { {"x" , 4000},{"m",4000},{"a",4000},{"s",4000} });
	long long count = 0;
	std::map<int, std::string> map = { {0,"x"} ,{1,"m"},{2,"a"},{3,"s"} };
	for (auto& tmp : ranges)
	{
		long long tmpCount = 1;
		for (int i = 0; i < 4; i++)
		{
			tmpCount *= tmp.second.at(map[i]) - tmp.first.at(map[i]) + 1;
		}
		count += tmpCount;
	}

	std::cout << "Part Two: " << count << std::endl;
}

void DayHandler::Day20(FileHandler& fileHandler)
{
	std::vector<std::string> tab = fileHandler.ReadFile("day20.txt");
	std::unordered_map<std::string, std::pair<std::vector<std::string>, char>> moduleConfiguration;
	std::unordered_map<std::string, bool> flipFlopPulses;
	std::unordered_map<std::string, std::unordered_map<std::string, bool>> conjuctionPulses;
	for (std::string line : tab)
	{
		std::string key;
		std::pair<std::vector<std::string>, char> values;
		std::vector<std::string> tmp = CustomLib::SplitString(line, { '-','>' });
		key = tmp[0].substr(0, tmp[0].length() - 1);
		if (key[0] == '%')
			flipFlopPulses.emplace(key.substr(1), false);
		if (key[0] != 'b')
		{
			values.second = key[0];
			key = key.substr(1);
		}
		else
			values.second = '#';
		values.first = CustomLib::SplitString(tmp[1], { ',',' ' });
		moduleConfiguration.emplace(key, values);
	}
	for (auto& tmp : moduleConfiguration)
	{
		if (tmp.second.second == '&')
		{
			std::unordered_map<std::string, bool> tmp1;
			for (auto& tmp2 : moduleConfiguration)
			{
				auto tmp3 = std::find(tmp2.second.first.begin(), tmp2.second.first.end(), tmp.first);
				if (tmp3 != tmp2.second.first.end())
					tmp1.emplace(tmp2.first, false);
			}
			conjuctionPulses.emplace(tmp.first, tmp1);
		}
	}
	std::pair<long long, long long> pulseCount = Day20CountPulses(moduleConfiguration, flipFlopPulses, conjuctionPulses);
	std::cout << "Part One: " << pulseCount.first * pulseCount.second << std::endl;
	pulseCount = Day20CountPulses(moduleConfiguration, flipFlopPulses, conjuctionPulses, std::pow<long long>(10, 16), true);
	std::cout << "Part Two: " << pulseCount.first << std::endl;
}

void DayHandler::Day21(FileHandler& fileHandler)
{
	std::vector<std::string> tab = fileHandler.ReadFile("day21.txt");
	std::vector<std::pair<int, int>> steps;
	for (int i = 0; i < tab.size(); i++)
		for (int j = 0; j < tab[i].length(); j++)
			if (tab[i][j] == 'S')
			{
				steps.push_back({ j,i });
				break;
			}
	int stepsAmount = 64;
	if(tab.size()< 15)
		stepsAmount = 6;
	for (int i = 0; i < stepsAmount; i++)
	{
		std::cout << i << "/64\r";
		std::vector<std::pair<int, int>> tmp;
		for (auto& step : steps)
		{
			std::pair<int, int> tmp1 = step;
			if (step.first > 0 && tab[step.second][step.first - 1] == '.' || tab[step.second][step.first - 1] == 'S')
			{
				tmp1 = { step.first - 1,step.second };
				if (std::find(tmp.begin(), tmp.end(), tmp1) == tmp.end())
					tmp.push_back(tmp1);
			}
			if (step.second > 0 && tab[step.second - 1][step.first] == '.' || tab[step.second - 1][step.first] == 'S')
			{
				tmp1 = { step.first,step.second - 1 };
				if (std::find(tmp.begin(), tmp.end(), tmp1) == tmp.end())
					tmp.push_back(tmp1);
			}
			if (step.first < tab[step.second].length() - 1 && tab[step.second][step.first + 1] == '.' || tab[step.second][step.first + 1] == 'S')
			{
				tmp1 = { step.first + 1,step.second };
				if (std::find(tmp.begin(), tmp.end(), tmp1) == tmp.end())
					tmp.push_back(tmp1);
			}
			if (step.second < tab.size() - 1 && tab[step.second + 1][step.first] == '.' || tab[step.second + 1][step.first] == 'S')
			{
				tmp1 = { step.first,step.second + 1 };
				if (std::find(tmp.begin(), tmp.end(), tmp1) == tmp.end())
					tmp.push_back(tmp1);
			}
		}
		steps = tmp;
	}
	std::cout << "Part One: " << steps.size() << std::endl;

	std::pair<int, int> start;
	for (int i = 0; i < tab.size(); i++)
		for (int j = 0; j < tab[i].length(); j++)
			if (tab[i][j] == 'S')
			{
				start = { j,i };
				break;
			}

	int ySize = tab.size();
	int xSize = tab[0].length();

	std::unordered_map<std::string, long long> distanceMap;
	std::deque<std::tuple<long long, long long, long long, long long, long long>> queue = { {0,0,start.second,start.first,0} };
	while (queue.size())
	{
		auto [tempY, tempX, y, x, dist] = queue.front();
		queue.pop_front();
		if (y < 0)
		{
			tempY -= 1;
			y += ySize;
		}
		if (y >= ySize)
		{
			tempY += 1;
			y -= ySize;
		}
		if (x < 0)
		{
			tempX -= 1;
			x += xSize;
		}
		if (x >= xSize)
		{
			tempX += 1;
			x -= xSize;
		}
		if (!(0 <= y && y < ySize && 0 <= x && x < xSize && tab[y][x] != '#'))
			continue;
		std::string key = std::to_string(tempY) + "," + std::to_string(tempX) + "," + std::to_string(y) + "," + std::to_string(x);
		if (distanceMap.find(key) != distanceMap.end())
			continue;
		if (std::abs(tempY) > 4 || std::abs(tempX) > 4)
			continue;
		distanceMap[key] = dist;
		for (auto [dy, dx] : std::vector<std::pair<int, int>>{ {-1, 0}, {0, 1}, {1, 0}, {0, -1} })
			queue.push_back({ tempY,tempX ,y + dy,x + dx,dist + 1 });
	}

	long long limit = 26501365;
	if (tab.size() < 15)
		limit = 5000;
	long long ans = 0;
	std::map<std::string, long long> solveMap;
	for (int y = 0; y < ySize; y++)
	{
		for (int x = 0; x < xSize; x++)
		{
			std::cout << y << "/" << ySize << ", " << x << "/" << xSize << " \r";
			std::cout.flush();
			std::string key = "0,0," + std::to_string(y) + "," + std::to_string(x);
			if (distanceMap.find(key) != distanceMap.end())
			{
				std::vector<int> options = { -3,-2,-1,0,1,2,3 };
				for (auto& tempY : options)
				{
					for (auto& tempX : options)
					{
						std::string key = std::to_string(tempY) + "," + std::to_string(tempX) + "," + std::to_string(y) + "," + std::to_string(x);
						long long dist = distanceMap[key];
						if (dist % 2 == limit % 2 && dist <= limit)
							ans++;
						if ((tempY == *std::min_element(options.begin(), options.end()) || tempY == *std::max_element(options.begin(), options.end())) && (tempX == *std::min_element(options.begin(), options.end()) || tempX == *std::max_element(options.begin(), options.end())))
						{
							long long amount = (limit - dist) / ySize;
							std::string key = std::to_string(dist) + ",2," + std::to_string(limit);
							if (solveMap.find(key) != solveMap.end())
							{
								ans += solveMap[key];
								continue;
							}
							long long ret = 0;
							for (int i = 1; i <= amount; i++)
							{
								if (dist + ySize * i <= limit && (dist + ySize * i) % 2 == limit % 2)
									ret += i + 1;
							}
							ans += ret;
						}
						else if ((tempY == *std::min_element(options.begin(), options.end()) || tempY == *std::max_element(options.begin(), options.end())) || (tempX == *std::min_element(options.begin(), options.end()) || tempX == *std::max_element(options.begin(), options.end())))
						{
							long long amount = (limit - dist) / ySize;
							std::string key = std::to_string(dist) + ",1," + std::to_string(limit);
							if (solveMap.find(key) != solveMap.end())
							{
								ans += solveMap[key];
								continue;
							}
							long long ret = 0;
							for (int i = 1; i <= amount; i++)
							{
								if (dist + ySize * i <= limit && (dist + ySize * i) % 2 == limit % 2)
									ret++;
							}
							ans += ret;
						}
					}
				}
			}
		}
	}

	std::cout << "Part Two: " << ans << std::endl;
}

void DayHandler::Day22(FileHandler& fileHandler)
{
	std::vector< std::string> tab = fileHandler.ReadFile("day22.txt");
	std::vector<Brick> bricks;
	for (int i = 0; i < tab.size(); i++)
	{
		std::vector<int> tmp = CustomLib::VectorStringToNumber<int>(CustomLib::SplitString(tab[i], { ',','~' }));
		bricks.push_back({ i,{tmp[0],tmp[3]},{tmp[1],tmp[4]},{tmp[2],tmp[5]} });
	}
	Day22PrintMap(bricks);

	bool loopEnd = false;
	int updatedZ = 0;
	while (!loopEnd)
	{
		std::cout << updatedZ << "/500\r";
		int tmpUpdatedZ = -1;
		loopEnd = true;
		for (Brick& brick : bricks)
		{
			bool brickCanMove = true;
			if (brick.z.first <= 1)
				continue;
			if (updatedZ > brick.z.first)
				continue;
			for (const Brick& brick1 : bricks)
			{
				if (brick1.id == brick.id)
					continue;
				const std::vector<std::tuple<int, int, int>>& tmp = brick.getBottomCoordinates();
				const std::vector<std::tuple<int, int, int>>& tmp1 = brick1.getTopCoordinates();
				if (std::find_first_of(tmp.begin(), tmp.end(), tmp1.begin(), tmp1.end()) != tmp.end())
				{
					brickCanMove = false;
					break;
				}
			}
			if (brickCanMove)
			{
				if (!brick.moveDown())
				{
					loopEnd = true;
					CustomLib::PushError("Brick " + std::to_string(brick.id) + " can't move down");
					break;
				}
				loopEnd = false;
				if (tmpUpdatedZ > brick.z.first || tmpUpdatedZ == -1)
					tmpUpdatedZ = brick.z.first;
			}
		}
		updatedZ = tmpUpdatedZ;
	}
	Day22PrintMap(bricks, "Day22Map1.txt");
	for (auto& brick : bricks)
	{
		for (auto& brick1 : bricks)
		{
			if (brick.id == brick1.id)
				continue;
			const auto& tmp = brick.getTopCoordinates();
			const auto& tmp1 = brick1.getBottomCoordinates();
			if (std::find_first_of(tmp.begin(), tmp.end(), tmp1.begin(), tmp1.end()) != tmp.end())
			{
				brick.supports.push_back(brick1.id);
				brick1.supportedBy.push_back(brick.id);
			}
		}
	}
	long long count = 0;
	for (const auto& brick : bricks)
	{
		if (!brick.supports.size())
			count++;
		else
		{
			bool canBeDeleted = true;
			for (const auto& tmp : brick.supports)
			{
				if (bricks[tmp].supportedBy.size() <= 1)
				{
					canBeDeleted = false;
					break;
				}
			}
			if (canBeDeleted)
				count++;
		}
	}
	std::cout << "Part One: " << count << std::endl;

	count = 0;
	for (const auto& brick : bricks)
	{
		std::vector<int> tmp1 = { brick.id };
		for (const auto& tmp : brick.supports)
		{
			count += Day22GenerateChainReaction(bricks, tmp, tmp1);
		}
	}
	std::cout << "Part Two: " << count << std::endl;
}

void DayHandler::Day23(FileHandler& fileHandler)
{
	std::vector<std::string> tab = fileHandler.ReadFile("day23.txt");
	std::pair<int, int> start = { 1,0 }, end = { tab[0].length() - 2, tab.size() - 1 };
	std::vector<std::vector<std::pair<int, int>>> paths = Day23GetAllPaths(tab, start, end);
	long long maxSteps = 0;
	int maxStepsIndex = 0;
	for (int i = 0; i < paths.size(); i++)
	{
		if (paths[i].size() > maxSteps)
		{
			maxSteps = paths[i].size();
			maxStepsIndex = i;
		}
	}
	std::vector<std::string> map = tab;
	for (const auto& tmp : paths[maxStepsIndex])
		map[tmp.second][tmp.first] = 'O';
	fileHandler.WriteFile("Day23Map.txt", map);

	std::cout << "Part One: " << maxSteps - 1 << std::endl;

	long long maxSteps1 = 0;
	Day23MaxPathsSteps(tab, start, end, maxSteps1, true);

	std::cout << "Part Two: " << maxSteps1 - 1 << std::endl;
}

void DayHandler::Day24(FileHandler& fileHandler)
{
	std::vector<std::string> tab = fileHandler.ReadFile("day24.txt");
	std::vector<HailStone> hailStones;
	for (const auto& line : tab)
	{
		hailStones.push_back(HailStone(CustomLib::VectorStringToNumber<long double>(CustomLib::SplitString(line, { '@',',',' ' }))));
	}
	long long count = 0;
	long double min = 200000000000000, max = 400000000000000;
	if(tab.size() < 10)
	{
		min = 7;
		max = 27;
	}
	for (int i = 0; i < hailStones.size() - 1; i++)
		for (int j = i + 1; j < hailStones.size(); j++)
			if (hailStones[i].WillIntersect2D({ hailStones[j] }, min, max))
				count++;

	std::cout << "Part One: " << count << std::endl;

	z3::context c;
	z3::solver solve(c);

	z3::expr x = c.real_const("x");
	z3::expr y = c.real_const("y");
	z3::expr z = c.real_const("z");
	z3::expr vx = c.real_const("vx");
	z3::expr vy = c.real_const("vy");
	z3::expr vz = c.real_const("vz");

	int n = hailStones.size();
	std::vector<z3::expr> T;

	for (int i = 0; i < n; i++)
		T.push_back(c.real_const(("T" + std::to_string(i)).c_str()));

	for (int i = 0; i < n; i++) {
		solve.add(x + T[i] * vx - c.real_val((long long)hailStones[i].x) - T[i] * c.real_val((long long)hailStones[i].vx) == 0);
		solve.add(y + T[i] * vy - c.real_val((long long)hailStones[i].y) - T[i] * c.real_val((long long)hailStones[i].vy) == 0);
		solve.add(z + T[i] * vz - c.real_val((long long)hailStones[i].z) - T[i] * c.real_val((long long)hailStones[i].vz) == 0);
	}

	if (solve.check() == z3::sat) {
		z3::model m = solve.get_model();
		std::cout << "Part Two: " << m.eval(x + y + z).get_numeral_int64() << std::endl;
	}
}

void DayHandler::Day25(FileHandler& fileHandler)
{
	system("python day25.py Data/Input/day25.txt Data/Output/Day25Map.png");
}

std::vector<std::pair<long long, long long>> DayHandler::Day5ApplyRange(const std::vector<std::pair<long long, long long>> tab, const std::vector<std::vector<long long>> mapping) const
{
	std::vector<std::pair<long long, long long>> tmp, tab1 = tab;
	for (int i = 0; i < mapping.size(); i++)
	{
		long long destination = mapping[i][0];
		long long source = mapping[i][1];
		long long size = mapping[i][2];
		long long sourceEnd = source + size;
		std::vector<std::pair<long long, long long>> newTab;
		while (tab1.size())
		{
			std::pair<long long, long long>& tmp1 = tab1.back();
			tab1.pop_back();
			std::pair<long long, long long> before = { tmp1.first, std::min(tmp1.second, source) };
			std::pair<long long, long long> inter = { std::max(tmp1.first, source), std::min(sourceEnd, tmp1.second) };
			std::pair<long long, long long> after = { std::max(sourceEnd, tmp1.first), tmp1.second };
			if (before.second > before.first)
				newTab.push_back(before);
			if (inter.second > inter.first)
				tmp.push_back({ inter.first - source + destination, inter.second - source + destination });
			if (after.second > after.first)
				newTab.push_back(after);
		}
		tab1 = newTab;
	}
	tmp.insert(tmp.end(), tab1.begin(), tab1.end());
	return tmp;
}

int DayHandler::Day7GetType(const std::string type, const bool activeJokers) const
{
	std::vector<char> labels, repeatingLabels;
	int repeats = 0;
	for (char tmp : type)
	{
		bool isInLabels = false;
		for (char tmp1 : labels)
		{
			if (tmp1 == tmp)
			{
				repeats += 1;
				isInLabels = true;
				break;
			}
		}
		if (!isInLabels)
		{
			labels.push_back(tmp);
		}
		else
		{
			bool isInRepeatingLabels = false;
			for (char tmp1 : repeatingLabels)
			{
				if (tmp1 == tmp)
				{
					isInRepeatingLabels = true;
					break;
				}
			}
			if (!isInRepeatingLabels)
			{
				repeatingLabels.push_back(tmp);
				repeats++;
			}
		}
	}
	if (activeJokers)
	{
		if (repeatingLabels.size() > 1)
		{
			if (repeatingLabels[0] == 'J')
				repeatingLabels.erase(repeatingLabels.begin());
			else if (repeatingLabels[1] == 'J')
				repeatingLabels.erase(repeatingLabels.begin() + 1);
			else
			{
				for (char tmp : type)
				{
					if (tmp == 'J')
					{
						repeats++;
						break;
					}
				}
			}
		}
		else if (repeatingLabels.size() > 0)
		{
			if (repeatingLabels[0] == 'J')
			{
				if (repeats < 5)
					repeats++;
			}
			else if (repeats < 5)
			{
				for (char tmp : type)
				{
					if (tmp == 'J')
					{
						repeats++;
						break;
					}
				}
			}
		}
		else
		{
			for (char tmp : type)
			{
				if (tmp == 'J')
				{
					repeats += 2;
					repeatingLabels.push_back(tmp);
					break;
				}
			}
		}
	}
	if (repeats == 5 && repeatingLabels.size() == 1)
		return 7;
	else if (repeats == 4 && repeatingLabels.size() == 1)
		return 6;
	else if (repeats == 5 && repeatingLabels.size() == 2)
		return 5;
	else if (repeats == 3 && repeatingLabels.size() == 1)
		return 4;
	else if (repeats == 4 && repeatingLabels.size() == 2)
		return 3;
	else if (repeats == 2 && repeatingLabels.size() == 1)
		return 2;
	return 1;
}

bool DayHandler::Day10HandlePipe(std::pair<int, int>* previousLocation, std::pair<int, int>* currentLocation, const std::vector<std::string> map) const
{
	std::pair<int, int> nextLocation;
	if (map[currentLocation->first][currentLocation->second] == '|')
	{
		if (previousLocation->first == currentLocation->first - 1)
			nextLocation = { currentLocation->first + 1,currentLocation->second };
		else if (previousLocation->first == currentLocation->first + 1)
			nextLocation = { currentLocation->first - 1,currentLocation->second };
		else
			return false;
	}
	else if (map[currentLocation->first][currentLocation->second] == '-')
	{
		if (previousLocation->second == currentLocation->second - 1)
			nextLocation = { currentLocation->first ,currentLocation->second + 1 };
		else if (previousLocation->second == currentLocation->second + 1)
			nextLocation = { currentLocation->first ,currentLocation->second - 1 };
		else
			return false;
	}
	else if (map[currentLocation->first][currentLocation->second] == 'F')
	{
		if (previousLocation->first == currentLocation->first + 1)
			nextLocation = { currentLocation->first ,currentLocation->second + 1 };
		else if (previousLocation->second == currentLocation->second + 1)
			nextLocation = { currentLocation->first + 1,currentLocation->second };
		else
			return false;
	}
	else if (map[currentLocation->first][currentLocation->second] == '7')
	{
		if (previousLocation->first == currentLocation->first + 1)
			nextLocation = { currentLocation->first ,currentLocation->second - 1 };
		else if (previousLocation->second == currentLocation->second - 1)
			nextLocation = { currentLocation->first + 1,currentLocation->second };
		else
			return false;
	}
	else if (map[currentLocation->first][currentLocation->second] == 'J')
	{
		if (previousLocation->first == currentLocation->first - 1)
			nextLocation = { currentLocation->first ,currentLocation->second - 1 };
		else if (previousLocation->second == currentLocation->second - 1)
			nextLocation = { currentLocation->first - 1,currentLocation->second };
		else
			return false;
	}
	else if (map[currentLocation->first][currentLocation->second] == 'L')
	{
		if (previousLocation->first == currentLocation->first - 1)
			nextLocation = { currentLocation->first ,currentLocation->second + 1 };
		else if (previousLocation->second == currentLocation->second + 1)
			nextLocation = { currentLocation->first - 1,currentLocation->second };
		else
			return false;
	}
	else
		return false;

	previousLocation->first = currentLocation->first;
	previousLocation->second = currentLocation->second;
	currentLocation->first = nextLocation.first;
	currentLocation->second = nextLocation.second;
	return true;
}

long long DayHandler::Day12CountOccurencies(const std::string& conditionReport, const std::vector<int>& damagedGroups, long long i, long long gi, long long current)
{
	std::tuple<long long, long long, long long> key = std::make_tuple(i, gi, current);
	if (RP.find(key) != RP.end()) {
		return RP[key];
	}

	if (i == conditionReport.length()) {
		if (gi == damagedGroups.size() && current == 0) {
			return 1;
		}
		else if (gi == damagedGroups.size() - 1 && damagedGroups[gi] == current) {
			return 1;
		}
		else {
			return 0;
		}
	}

	long long ans = 0;
	for (char c : {'.', '#'}) {
		if (conditionReport[i] == c || conditionReport[i] == '?') {
			if (c == '.' && current == 0) {
				ans += Day12CountOccurencies(conditionReport, damagedGroups, i + 1, gi, 0);
			}
			else if (c == '.' && current > 0 && gi < damagedGroups.size() && damagedGroups[gi] == current) {
				ans += Day12CountOccurencies(conditionReport, damagedGroups, i + 1, gi + 1, 0);
			}
			else if (c == '#') {
				ans += Day12CountOccurencies(conditionReport, damagedGroups, i + 1, gi, current + 1);
			}
		}
	}

	RP[key] = ans;
	return ans;
}

void DayHandler::Day16DrawMap(std::vector<std::string>& map, const std::vector<std::string> tab, int x, int y, int dx, int dy)
{
	while (true)
	{
		if (x < 0 || x >= map[0].length() || y < 0 || y >= map.size())
			return;
		if (tab[y][x] == '.')
		{
			map[y][x] = '#';
			x += dx;
			y += dy;
		}
		else if (tab[y][x] == '/')
		{
			map[y][x] = '#';
			if (dx == 1)
			{
				dx = 0;
				dy = -1;
			}
			else if (dx == -1)
			{
				dx = 0;
				dy = 1;
			}
			else if (dy == 1)
			{
				dx = -1;
				dy = 0;
			}
			else if (dy == -1)
			{
				dx = 1;
				dy = 0;
			}
			x += dx;
			y += dy;
		}
		else if (tab[y][x] == '\\')
		{
			map[y][x] = '#';
			if (dx == 1)
			{
				dx = 0;
				dy = 1;
			}
			else if (dx == -1)
			{
				dx = 0;
				dy = -1;
			}
			else if (dy == 1)
			{
				dx = 1;
				dy = 0;
			}
			else if (dy == -1)
			{
				dx = -1;
				dy = 0;
			}
			x += dx;
			y += dy;
		}
		else if (tab[y][x] == '-')
		{
			if (map[y][x] == '#' && ((y > 0 && map[y - 1][x] == '#') || (y < map.size() - 1 && map[y + 1][x] == '#')))
				return;
			map[y][x] = '#';
			if (dy == 0)
				x += dx;
			else
			{
				Day16DrawMap(map, tab, x + 1, y, 1, 0);
				Day16DrawMap(map, tab, x - 1, y, -1, 0);
				return;
			}
		}
		else if (tab[y][x] == '|')
		{
			if (map[y][x] == '#' && ((x > 0 && map[y][x - 1] == '#') || (x < map[0].length() - 1 && map[y][x + 1] == '#')))
				return;
			map[y][x] = '#';
			if (dx == 0)
				y += dy;
			else
			{
				Day16DrawMap(map, tab, x, y + 1, 0, 1);
				Day16DrawMap(map, tab, x, y - 1, 0, -1);
				return;
			}
		}
		else
			std::cout << "ERROR" << std::endl;
	}
}

char DayHandler::Day19HandleInstructions(const std::unordered_map<std::string, std::vector<Instruction>>& worklows, const std::unordered_map<std::string, int>& part)
{
	std::string currentWorklow = "in";
	while (currentWorklow != "R" && currentWorklow != "A")
	{
		if (worklows.find(currentWorklow) == worklows.end())
		{
			std::cout << "ERROR: Workflow not found" << std::endl;
			break;
		}
		for (Instruction instruction : worklows.at(currentWorklow))
		{
			if (instruction.type == '=')
			{
				currentWorklow = instruction.arguments[0];
				break;
			}
			else if (instruction.type == '<')
			{
				if (part.find(instruction.arguments[0]) == part.end())
				{
					std::cout << "ERROR: Part not found" << std::endl;
					break;
				}
				if (part.at(instruction.arguments[0]) < std::stoi(instruction.arguments[1]))
				{
					currentWorklow = instruction.arguments[2];
					break;
				}
			}
			else if (instruction.type == '>')
			{
				if (part.find(instruction.arguments[0]) == part.end())
				{
					std::cout << "ERROR: Part not found" << std::endl;
					break;
				}
				if (part.at(instruction.arguments[0]) > std::stoi(instruction.arguments[1]))
				{
					currentWorklow = instruction.arguments[2];
					break;
				}
			}
			else
				std::cout << "ERROR" << std::endl;
		}
	}
	return currentWorklow[0];
}

std::vector<std::pair<std::unordered_map<std::string, int>, std::unordered_map<std::string, int>> > DayHandler::Day19GetAllRanges(const std::unordered_map<std::string, std::vector<Instruction>>& workflows, std::vector<Instruction> currentInstruction, std::unordered_map<std::string, int> min, std::unordered_map<std::string, int> max)
{
	std::vector<std::pair<std::unordered_map<std::string, int>, std::unordered_map<std::string, int>> > tmp = {};
	for (Instruction instruction : currentInstruction)
	{
		if (instruction.type == '<')
		{
			if (min.at(instruction.arguments[0]) < std::stoi(instruction.arguments[1]))
			{
				std::unordered_map<std::string, int> max1 = max;
				if (std::stoi(instruction.arguments[1]) < max[instruction.arguments[0]])
					max1[instruction.arguments[0]] = std::stoi(instruction.arguments[1]) - 1;
				if (instruction.arguments[2] == "A")
					tmp.push_back({ min,max1 });
				else if (instruction.arguments[2] != "R")
				{
					std::vector<std::pair<std::unordered_map<std::string, int>, std::unordered_map<std::string, int>> > tmp1 = Day19GetAllRanges(workflows, workflows.at(instruction.arguments[2]), min, max1);
					tmp.insert(tmp.end(), tmp1.begin(), tmp1.end());
				}
				min[instruction.arguments[0]] = max1[instruction.arguments[0]] + 1;
			}
		}
		else if (instruction.type == '>')
		{
			if (max.at(instruction.arguments[0]) > std::stoi(instruction.arguments[1]))
			{
				std::unordered_map<std::string, int> min1 = min;
				if (std::stoi(instruction.arguments[1]) > min[instruction.arguments[0]])
					min1[instruction.arguments[0]] = std::stoi(instruction.arguments[1]) + 1;
				if (instruction.arguments[2] == "A")
					tmp.push_back({ min1,max });
				else if (instruction.arguments[2] != "R")
				{
					std::vector<std::pair<std::unordered_map<std::string, int>, std::unordered_map<std::string, int>> > tmp1 = Day19GetAllRanges(workflows, workflows.at(instruction.arguments[2]), min1, max);
					tmp.insert(tmp.end(), tmp1.begin(), tmp1.end());
				}
				max[instruction.arguments[0]] = min1[instruction.arguments[0]] - 1;
			}
		}
		else if (instruction.type == '=')
		{
			if (instruction.arguments[0] == "A")
				tmp.push_back({ min,max });
			else if (instruction.arguments[0] != "R")
			{
				std::vector<std::pair<std::unordered_map<std::string, int>, std::unordered_map<std::string, int>> > tmp1 = Day19GetAllRanges(workflows, workflows.at(instruction.arguments[0]), min, max);
				tmp.insert(tmp.end(), tmp1.begin(), tmp1.end());
			}
		}
		else
			std::cout << "ERROR" << std::endl;
	}

	return tmp;
}

std::pair<long long, long long> DayHandler::Day20CountPulses(const std::unordered_map<std::string, std::pair<std::vector<std::string>, char>>& moduleConfiguration, std::unordered_map<std::string, bool> flipFlopPulses, std::unordered_map<std::string, std::unordered_map<std::string, bool>> conjuctionPulses, const long long& buttonRepeats, const bool& part2)
{
	std::pair<long long, long long> pulsesCount = { 0,0 };
	std::unordered_map < std::string, long long> countOccurencies;
	std::unordered_map < std::string, long long> previousOccurencies;
	std::vector<long long> LCMTab;
	std::vector<std::string> modulesToWatch;
	if (part2)
	{
		std::string lastModule = "rx";
		for (auto& tmp : moduleConfiguration)
		{
			for (auto& tmp1 : tmp.second.first)
				if (tmp1 == "rx")
				{
					lastModule = tmp.first;
					break;
				}
			if (lastModule != "rx")
				break;
		}
		for (auto& tmp : moduleConfiguration)
		{
			for (auto& tmp1 : tmp.second.first)
				if (tmp1 == lastModule)
				{
					modulesToWatch.push_back(tmp.first);
					//std::cout << tmp.first << std::endl;
					break;
				}
		}
	}
	for (int i = 1; i <= buttonRepeats; i++)
	{
		std::cout << i << "/" << buttonRepeats << "\r";
		std::cout.flush();
		std::vector<std::pair<std::vector<std::string>, char>> currentModules = std::vector< std::pair<std::vector<std::string>, char>>({ moduleConfiguration.at("broadcaster") });
		std::vector<std::pair<std::string, std::string>> currentModulesNames = { {"button","broadcaster"} };
		std::vector<bool> pulses = { false };
		pulsesCount.first++;
		while (currentModules.size())
		{
			if (part2)
			{
				if (!pulses[0])
				{
					auto it = previousOccurencies.find(currentModulesNames[0].second);
					auto it1 = std::find(modulesToWatch.begin(), modulesToWatch.end(), currentModulesNames[0].second);
					if (it != previousOccurencies.end() && countOccurencies[currentModulesNames[0].second] == 2 && it1 != modulesToWatch.end())
					{
						LCMTab.push_back(i - it->second);
					}
					previousOccurencies[currentModulesNames[0].second] = i;
					countOccurencies[currentModulesNames[0].second]++;
				}
				if (LCMTab.size() == modulesToWatch.size())
					return { CustomLib::LCM(LCMTab),0 };
			}
			if (currentModules[0].second == '#')
			{
				for (auto& module : currentModules[0].first)
				{
					pulsesCount.first++;
					currentModules.push_back(moduleConfiguration.at(module));
					pulses.push_back(false);
					currentModulesNames.push_back({ currentModulesNames[0].second,module });
				}
			}
			else if (currentModules[0].second == '%')
			{
				if (!pulses[0])
				{
					flipFlopPulses[currentModulesNames[0].second] = !flipFlopPulses[currentModulesNames[0].second];
					for (auto& module : currentModules[0].first)
					{
						if (flipFlopPulses[currentModulesNames[0].second])
							pulsesCount.second++;
						else
							pulsesCount.first++;
						currentModules.push_back(moduleConfiguration.at(module));
						pulses.push_back(flipFlopPulses[currentModulesNames[0].second]);
						currentModulesNames.push_back({ currentModulesNames[0].second,module });
					}
				}
			}
			else if (currentModules[0].second == '&')
			{
				bool isHeightPulse = true;
				conjuctionPulses[currentModulesNames[0].second][currentModulesNames[0].first] = pulses[0];
				for (auto& pulse : conjuctionPulses.at(currentModulesNames[0].second))
					if (!pulse.second)
					{
						isHeightPulse = false;
						break;
					}
				for (auto& module : currentModules[0].first)
				{
					if (isHeightPulse)
						pulsesCount.first++;
					else
						pulsesCount.second++;
					if (moduleConfiguration.find(module) != moduleConfiguration.end())
					{
						pulses.push_back(!isHeightPulse);
						currentModules.push_back(moduleConfiguration.at(module));
						currentModulesNames.push_back({ currentModulesNames[0].second,module });
					}
					else
					{
						if (isHeightPulse)
						{
							return { i,0 };
						}
					}
				}
			}
			else
				std::cout << "ERROR" << std::endl;
			currentModulesNames.erase(currentModulesNames.begin());
			currentModules.erase(currentModules.begin());
			pulses.erase(pulses.begin());
		}
		//std::cout << pulsesCount.first << "," << pulsesCount.second << std::endl;
	}
	return pulsesCount;
}

void DayHandler::Day22PrintMap(const std::vector<Brick>& bricks, std::string filename) const
{
	int maxX = 0, maxY = 0, maxZ = 0;
	for (const auto& brick : bricks)
	{
		if (brick.x.second > maxX)
			maxX = brick.x.second;
		if (brick.y.second > maxY)
			maxY = brick.y.second;
		if (brick.z.second > maxZ)
			maxZ = brick.z.second;
	}
	std::vector<std::vector<int>> mapX = std::vector<std::vector<int>>(maxZ + 1, std::vector<int>(maxX + 1, 0));
	std::vector<std::vector<int>> mapY = std::vector<std::vector<int>>(maxZ + 1, std::vector<int>(maxY + 1, 0));

	for (const auto& brick : bricks)
	{
		for (const auto& tmp : brick.getCoordinates())
		{
			mapX[std::get<2>(tmp)][std::get<0>(tmp)]++;
			mapY[std::get<2>(tmp)][std::get<1>(tmp)]++;
		}
	}

	std::vector<std::string> map;
	for (int i = 0; i < mapX.size(); i++)
	{
		std::string tmp = "";
		for (int j = 0; j < mapX[i].size(); j++)
		{
			tmp += std::to_string(mapX[i][j]) + "\t";
		}
		tmp += "\t\t";
		for (int j = 0; j < mapY[i].size(); j++)
		{
			tmp += std::to_string(mapY[i][j]) + "\t";
		}
		map.push_back(tmp);
	}
	std::reverse(map.begin(), map.end());

	fileHandler->WriteFile(filename, map);
}

int DayHandler::Day22GenerateChainReaction(const std::vector<Brick>& bricks, int currentBrick, std::vector<int>& fallen)
{
	int count = 0;
	if (bricks[currentBrick].supportedBy.size() == 1 && std::find(fallen.begin(), fallen.end(), currentBrick) == fallen.end())
	{
		count++;
		fallen.push_back(currentBrick);
		for (const auto& tmp : bricks[currentBrick].supports)
		{
			count += Day22GenerateChainReaction(bricks, tmp, fallen);
		}
	}
	else if (bricks[currentBrick].supportedBy.size() > 1)
	{
		bool isGonnaFall = true;
		for (const auto& tmp : bricks[currentBrick].supportedBy)
		{
			if (std::find(fallen.begin(), fallen.end(), tmp) == fallen.end())
			{
				isGonnaFall = false;
				break;
			}
		}
		if (isGonnaFall)
		{
			count++;
			fallen.push_back(currentBrick);
			for (const auto& tmp : bricks[currentBrick].supports)
			{
				count += Day22GenerateChainReaction(bricks, tmp, fallen);
			}
		}
	}
	return count;
}

std::vector<std::vector<std::pair<int, int>>> DayHandler::Day23GetAllPaths(const std::vector<std::string>& map, const std::pair<int, int>& start, const std::pair<int, int>& end, const bool canClimbSlopes, std::vector<std::pair<int, int>> currentPath)
{
	std::vector<std::vector<std::pair<int, int>>> paths;
	currentPath.push_back(start);
	while (currentPath.back() != end)
	{
		std::pair<int, int> currentLocation = currentPath.back();
		std::vector<std::pair<int, int>> directions = { {0,1},{1,0},{0,-1},{-1,0} };
		std::vector<std::pair<int, int>> nextLocations;
		for (auto& direction : directions)
		{
			std::pair<int, int> nextLocation = { currentLocation.first + direction.first, currentLocation.second + direction.second };
			if (0 <= nextLocation.second && nextLocation.second < map.size() && 0 <= nextLocation.first && nextLocation.first < map[0].length() && map[nextLocation.second][nextLocation.first] != '#' && std::find(currentPath.begin(), currentPath.end(), nextLocation) == currentPath.end())
			{
				char nextChar = map[nextLocation.second][nextLocation.first];
				if (canClimbSlopes)
					nextLocations.push_back(nextLocation);
				else if (nextChar == '.' || nextChar == '>' && direction.first == 1 || nextChar == '<' && direction.first == -1 || nextChar == 'v' && direction.second == 1 || nextChar == '^' && direction.second == -1)
					nextLocations.push_back(nextLocation);
			}
		}
		if (nextLocations.size() >= 1)
		{
			for (int i = 1; i < nextLocations.size(); i++)
			{
				std::vector<std::vector<std::pair<int, int>>> tmpPaths = Day23GetAllPaths(map, nextLocations[i], end, canClimbSlopes, currentPath);
				paths.insert(paths.end(), tmpPaths.begin(), tmpPaths.end());
			}
			currentPath.push_back(nextLocations[0]);
		}
		else
		{
			return paths;
		}
	}
	paths.push_back(currentPath);
	return paths;
}

void DayHandler::Day23MaxPathsSteps(const std::vector<std::string>& map, const std::pair<int, int>& start, const std::pair<int, int>& end, long long& maxSteps, const bool canClimbSlopes, std::unordered_set<std::pair<int, int>, pair_hash> currentPath)
{
	currentPath.insert(start);
	std::pair<int, int> currentLocation = start;
	while (currentLocation != end)
	{
		std::vector<std::pair<int, int>> directions = { {0,1},{1,0},{0,-1},{-1,0} };
		std::vector<std::pair<int, int>> nextLocations;
		for (auto& direction : directions)
		{
			std::pair<int, int> nextLocation = { currentLocation.first + direction.first, currentLocation.second + direction.second };
			if (0 <= nextLocation.second && nextLocation.second < map.size() && 0 <= nextLocation.first && nextLocation.first < map[0].length() && map[nextLocation.second][nextLocation.first] != '#' && currentPath.find(nextLocation) == currentPath.end())
			{
				char nextChar = map[nextLocation.second][nextLocation.first];
				if (canClimbSlopes)
					nextLocations.emplace_back(nextLocation);
				else if (nextChar == '.' || nextChar == '>' && direction.first == 1 || nextChar == '<' && direction.first == -1 || nextChar == 'v' && direction.second == 1 || nextChar == '^' && direction.second == -1)
					nextLocations.emplace_back(nextLocation);
			}
		}
		if (nextLocations.size() >= 1)
		{
			for (int i = 1; i < nextLocations.size(); i++)
				Day23MaxPathsSteps(map, nextLocations[i], end, maxSteps, canClimbSlopes, currentPath);
			currentLocation = nextLocations[0];
			currentPath.insert(currentLocation);
		}
		else
		{
			return;
		}
	}
	if (currentPath.size() > maxSteps)
		maxSteps = currentPath.size();
	std::cout << "Curr max: " << maxSteps << "\r";
}