#include "DayHandler.h"

#include <cctype>
#include <iostream>
#include <sstream>

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
			std::cout << std::stoi(tmp) << std::endl;
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
		std::vector<std::string> lineTab = SplitString(line, ':');
		lineTab[1].erase(0, 1);
		lineTab[1].erase(std::remove_if(lineTab[1].begin(), lineTab[1].end(), [](char c) { return c == ';'; }), lineTab[1].end());
		lineTab[1].erase(std::remove_if(lineTab[1].begin(), lineTab[1].end(), [](char c) { return c == ','; }), lineTab[1].end());
		std::vector<std::string> tmp = SplitString(lineTab[1], ' ');
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
			int id = std::stoi(SplitString(lineTab[0], ' ')[1]);
			//std::cout<<id<<std::endl;
			fairGames += id;
		}
	}
	std::cout << "Part One: " << fairGames << std::endl;

	int sum = 0;
	for (std::string line : tab)
	{
		line = SplitString(line, ':')[1];
		line.erase(0, 1);
		line.erase(std::remove_if(line.begin(), line.end(), [](char c) { return c == ','; }), line.end());
		line.erase(std::remove_if(line.begin(), line.end(), [](char c) { return c == ';'; }), line.end());
		int maxR = 1, maxG = 1, maxB = 1;
		std::vector<std::string> tmp1 = SplitString(line, ' ');
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

std::vector<std::string> DayHandler::SplitString(const std::string& input, char delimiter)
{
	std::vector<std::string> tokens;
	std::stringstream ss(input);
	std::string token;

	while (std::getline(ss, token, delimiter)) {
		tokens.push_back(token);
	}

	return tokens;
}