#include "DayHandler.h"

#include <cctype>
#include <iostream>
#include <cmath>
#include <thread>
#include <numeric>
#include <unordered_map>

#include "CustomLib.h"
#include "FileHandler.h"

DayHandler::DayHandler(std::string inputDir, std::string outputDir)
{
	fileHandler = new FileHandler(inputDir, outputDir);
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
	currentDay = dayFunctions.size();
}

void DayHandler::HandleDay(int day)
{
	if (day <= currentDay && day > 0)
	{
		(this->*dayFunctions[day - 1])(*fileHandler);
	}
	else
	{
		std::cout << "\nWrong day!\n";
	}
}

int DayHandler::getCurrentDay()
{
	return currentDay;
}

void DayHandler::Day1(FileHandler& fileHandler)
{
	std::vector<std::string> tab = fileHandler.ReadFile("day1.txt");

	// Part one
	int calibrationSum = 0;
	for (const std::string line : tab)
	{
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

	calibrationSum = 0;

	// Part two
	std::string numbersDict[] = { "one", "two", "three", "four", "five", "six", "seven", "eight", "nine" };
	for (const std::string line : tab)
	{
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

	int fairGames = 0;
	for (std::string line : tab)
	{
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
	for (std::string line : tab)
	{
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

	std::vector<std::pair<std::pair<int, int>, std::pair<int, int>>> tmp, tmp1;

	for (int i = 0; i < tab.size(); i++)
	{
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

	for (std::pair<std::pair<int, int>, std::pair<int, int>> tmp2 : tmp)
	{
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
	for (std::pair<int, int> gearRatio : gearRatios)
	{
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
	int points = 0;
	for (std::vector<std::string> tmp : tab1)
	{
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
			points += std::pow(2, multiply - 1);
		}
	}
	std::cout << "Part One: " << points << std::endl;

	int* scratchcards = new int[tab.size()];
	for (int i = 0; i < tab.size(); i++)
	{
		scratchcards[i] = 1;
	}
	int scratchcardsNum = 0;
	for (int i = 0; i < tab.size(); i++)
	{
		if (scratchcards[i] != NULL)
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
	for (int i = 1; i < tab.size(); i++)
	{
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
		for (int i = 1; i < tab.size(); i++)
		{
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

	for (size_t i = 0; i < seeds.size(); i += 2) {
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
	for (int i = 0; i < times.size(); i++)
	{
		int currentMargin = 0;
		for (int j = 1; j < times[i]; j++)
		{
			if ((times[i] - j) * j > distances[i])
				currentMargin++;
		}
		if (margin > 0);
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
	for (int i = 0; i < players.size(); i++)
	{
		int type = Day7GetType(players[i].first);
		types[type - 1].push_back({ i, players[i].first });
	}
	int size = 0;
	long long money = 0;
	for (std::vector<std::pair<int, std::string>> tmp : types)
	{
		std::vector<std::pair<int, std::string>> tmp1 = tmp;
		CustomLib::QuickSort(tmp1, 0, decltype(0)(tmp1.size() - 1), false, CustomLib::Day7Compare<decltype(tmp1)::value_type>);
		for (std::pair<int, std::string> player : tmp1)
			money += players[player.first].second * ++size;
	}

	std::cout << "Part One: " << money << std::endl;

	types = { {},{},{},{},{},{},{} };
	for (int i = 0; i < players.size(); i++)
	{
		int type = Day7GetType(players[i].first, true);
		types[type - 1].push_back({ i, players[i].first });
	}
	size = 0;
	money = 0;
	for (std::vector<std::pair<int, std::string>> tmp : types)
	{
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

	for (int i = 0; i < currents.size(); i++)
	{
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
	//int size = tab.size(), i = 0;
	for (std::string line : tab)
	{
		std::vector<long long> tmp = CustomLib::VectorStringToNumber<long long>(CustomLib::SplitString(line, ' '));
		long long tmp1 = CustomLib::Extrapolation<long long>(tmp);
		sum += tmp1;
		//std::cout << ++i << "/" << size << " - " <<sum<<", " << tmp1 << std::endl;
	}
	std::cout << "Part One: " << sum << std::endl;

	sum = 0;
	for (std::string line : tab)
	{
		std::vector<long long> tmp = CustomLib::VectorStringToNumber<long long>(CustomLib::SplitString(line, ' '));
		long long tmp1 = CustomLib::Extrapolation<long long>(tmp, false);
		sum += tmp1;
		//std::cout << ++i << "/" << size << " - " <<sum<<", " << tmp1 << std::endl;
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
	for (int i = 0; i < map.size(); i++)
	{
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
}

std::vector<std::pair<long long, long long>> DayHandler::Day5ApplyRange(std::vector<std::pair<long long, long long>> tab, std::vector<std::vector<long long>> mapping)
{
	std::vector<std::pair<long long, long long>> tmp;
	for (int i = 0; i < mapping.size(); i++)
	{
		long long destination = mapping[i][0];
		long long source = mapping[i][1];
		long long size = mapping[i][2];
		long long sourceEnd = source + size;
		std::vector<std::pair<long long, long long>> newTab;
		while (tab.size())
		{
			std::pair<long long, long long>& tmp1 = tab.back();
			tab.pop_back();
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
		tab = newTab;
	}
	tmp.insert(tmp.end(), tab.begin(), tab.end());
	return tmp;
}

int DayHandler::Day7GetType(std::string type, bool activeJokers) const
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

bool DayHandler::Day10HandlePipe(std::pair<int, int>* previousLocation, std::pair<int, int>* currentLocation, const std::vector<std::string> map)
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