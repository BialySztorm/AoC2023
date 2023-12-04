#include "DayHandler.h"

#include <cctype>
#include <iostream>
#include <cmath>

#include "CustomLib.h"
#include "FileHandler.h"

DayHandler::DayHandler(std::string inputDir, std::string outputDir)
{
	fileHandler = new FileHandler(inputDir, outputDir);
}

void DayHandler::HandleDay(int day)
{
	if (day <= currentDay && day > 0)
	{
		if (day == 1)
			day1(*fileHandler);
		else if (day == 2)
			day2(*fileHandler);
		else if (day == 3)
			day3(*fileHandler);
		else if (day == 4)
			day4(*fileHandler);
	}
	else if (day > currentDay)
	{
		std::cout<<"\nWrong day!\n";
	}
}

void DayHandler::day1(FileHandler& fileHandler)
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

void DayHandler::day2(FileHandler& fileHandler)
{
	std::vector<std::string> tab = fileHandler.ReadFile("day2.txt");

	int fairGames = 0;
	for (std::string line : tab)
	{
		bool fairGame = true;
		std::vector<std::string> lineTab = CustomLib::SplitString(line, ':');
		lineTab[1].erase(std::remove_if(lineTab[1].begin(), lineTab[1].end(), [](char c) { return c == ';'; }), lineTab[1].end());
		lineTab[1].erase(std::remove_if(lineTab[1].begin(), lineTab[1].end(), [](char c) { return c == ','; }), lineTab[1].end());
		std::vector<std::string> tmp = CustomLib::SplitString(lineTab[1], ' ');
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
			int id = std::stoi(CustomLib::SplitString(lineTab[0], ' ')[1]);
			//std::cout<<id<<std::endl;
			fairGames += id;
		}
	}
	std::cout << "Part One: " << fairGames << std::endl;

	int sum = 0;
	for (std::string line : tab)
	{
		line = CustomLib::SplitString(line, ':')[1];
		line.erase(0, 1);
		line.erase(std::remove_if(line.begin(), line.end(), [](char c) { return c == ','; }), line.end());
		line.erase(std::remove_if(line.begin(), line.end(), [](char c) { return c == ';'; }), line.end());
		int maxR = 1, maxG = 1, maxB = 1;
		std::vector<std::string> tmp1 = CustomLib::SplitString(line, ' ');
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

void DayHandler::day3(FileHandler& fileHandler)
{
	std::vector<std::string> tab = fileHandler.ReadFile("day3.txt");

	std::vector<std::pair<std::pair<int, int>, std::pair<int, int>>> tmp, tmp1;

	for (int i = 0; i< tab.size(); i++)
	{
		bool isNum = false;
		std::pair<int,int> start, end;
		for (int j = 0; j < tab[i].length(); j++)
		{
			if (isdigit(tab[i][j]) && !isNum)
			{
				start = {i,j};
				isNum = true;
			}
			else if(!isdigit(tab[i][j]) && isNum)
			{
				end = {i,j-1};
				isNum = false;
				tmp.push_back({start,end});
			}
		}
		if (isNum)
		{
			end = { i, tab[i].length()-1 };
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
			if ( i > 0 && height > 0 && !isdigit(tab[height-1][i - 1]) && tab[height-1][i - 1] != '.')
			{
				isCorrect = true;
				break;
			}
			if (height > 0 && !isdigit(tab[height - 1][i]) && tab[height - 1][i] != '.')
			{
				isCorrect = true;
				break;
			}
			if (i < tab[height].length()-1 && height > 0 && !isdigit(tab[height - 1][i+1]) && tab[height - 1][i+1] != '.')
			{
				isCorrect = true;
				break;
			}
			if (i < tab[height].length()-1 && !isdigit(tab[height][i + 1]) && tab[height][i + 1] != '.')
			{
				isCorrect = true;
				break;
			}
			if (i < tab[height].length()-1 && height < tab.size()-1 && !isdigit(tab[height + 1][i + 1]) && tab[height + 1][i + 1] != '.')
			{
				isCorrect = true;
				break;
			}
			if (height < tab.size()-1 && !isdigit(tab[height + 1][i]) && tab[height + 1][i] != '.')
			{
				isCorrect = true;
				break;
			}
			if (i > 0 && height < tab.size()-1 && !isdigit(tab[height + 1][i - 1]) && tab[height + 1][i - 1] != '.')
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
		sum+= std::stoi(tab[tmp2.first.first].substr(tmp2.first.second, tmp2.second.second - tmp2.first.second + 1));
	}

	std::cout<< "Part One: "<< sum << std::endl;

	std::vector<std::pair<int,int>> gearRatios;
	for (int i = 0; i < tab.size(); i++)
		for (int j = 0; j < tab[i].length(); j++)
			if(tab[i][j] == '*')
				gearRatios.push_back({i,j});

	int ratioSum = 0;
	for (std::pair<int, int> gearRatio : gearRatios)
	{
		std::pair<int,int> one = {-1,-1}, two = {-1,-1};
		int i = gearRatio.second, height = gearRatio.first;
		if (i > 0 && isdigit(tab[height][i - 1]) )
		{
			one = {height,i-1};
		}
		if (i < tab[height].length() - 1 && isdigit(tab[height][i + 1]))
		{
			if (one.first != -1 && one.second != -1)
			{
				two = { height,i+1 };
			}
			else {
				one = { height,i+1 };
			}
		}
		if (height > 0 && isdigit(tab[height - 1][i]) && (two.first == -1 && two.second == -1))
		{
			if (one.first != -1 && one.second != -1)
			{
				two = { height-1,i };
			}
			else {
				one = { height-1,i };
			}
		}
		if (height < tab.size() - 1 && isdigit(tab[height + 1][i]) && (two.first == -1 && two.second == -1))
		{
			if (one.first != -1 && one.second != -1)
			{
				two = { height+1,i };
			}
			else {
				one = { height+1,i };
			}
		}
		if (i > 0 && height > 0 && isdigit(tab[height - 1][i - 1]) && (two.first == -1 && two.second == -1) && height-1 != one.first)
		{
			if (one.first != -1 && one.second != -1)
			{
				two = { height - 1,i - 1 };
			}
			else {
				one = { height - 1,i - 1 };
			}
		}
		if (i < tab[height].length() - 1 && height > 0 && isdigit(tab[height - 1][i + 1]) && (two.first == -1 && two.second == -1) && !(height - 1 == one.first  && i == one.second))
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
		if((two.first == -1 && two.second == -1))
			continue;
		int tmpRatio = 1;
		for (std::pair<std::pair<int, int>, std::pair<int, int>> tmpTab : tmp)
		{
			if (CustomLib::isWithinRange(one, tmpTab))
			{
				//std::cout<<tmpTab.first.first<<", "<<tmpTab.first.second<<"; " << tmpTab.second.first << ", " << tmpTab.second.second << " - ";
				tmpRatio *= std::stoi(tab[tmpTab.first.first].substr(tmpTab.first.second, tmpTab.second.second - tmpTab.first.second + 1));
				break;
			}
		}
		for (std::pair<std::pair<int, int>, std::pair<int, int>> tmpTab : tmp)
		{
			if (CustomLib::isWithinRange(two, tmpTab))
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

void DayHandler::day4(FileHandler& fileHandler)
{
	std::vector<std::string> tab = fileHandler.ReadFile("day4.txt");
	std::vector<std::vector<std::string>> tab1;
	for (std::string tmp : tab)
	{
		std::vector<std::string> tmp1 = CustomLib::SplitString(tmp, ':');
		std::vector<std::string> tmp2 = CustomLib::SplitString(tmp1[1], '|');
		tmp1[1] = tmp2[0];
		tmp1.push_back(tmp2[1]);
		tab1.push_back(tmp1);
	}
	int points = 0;
	for (std::vector<std::string> tmp : tab1)
	{
		int multiply = 0;
		std::vector<int> winningNumbers, myNumbers;
		for (std::string tmp1 : CustomLib::SplitString(tmp[1],' '))
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
	std::cout << "Part One: "<< points << std::endl;

	int* scratchcards = new int[tab.size()];
	for (int i = 0; i < tab.size(); i++)
	{
		scratchcards[i] = 1;
	}
	int scratchcardsNum = 0;
	for (int i = 0; i < tab.size(); i++)
	{
		if(scratchcards[i] != NULL)
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
		for (int j = 1; j < cards +1; j++)
		{
			if (i + j < tab.size())
			{
				scratchcards[i + j]+= scratchcards[i];
			}
		}

	}
	delete[] scratchcards;
	std::cout << "Part Two: " << scratchcardsNum<< std::endl;
}

