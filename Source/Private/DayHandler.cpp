#include "DayHandler.h"

#include <cctype>
#include <iostream>
#include "FileHandler.h"

DayHandler::DayHandler(int day)
{
	if (day <= currentDay && day > 0)
	{
		if (day == 1)
			day1();
	}
}

void DayHandler::day1()
{
	FileHandler* fileHandler = new FileHandler("Data\\Input\\", "Data\\Output\\");
	std::vector<std::string> tab = fileHandler->ReadFile("day1.txt");

	// Part one
	int calibrationSum = 0;
	for (const std::string line : tab)
	{	
		char numbers[] = {NULL, NULL};
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
	std::cout<<"Part One: "<<calibrationSum<<std::endl;

	calibrationSum = 0;

	// Part two
	std::string numbersDict[] = { "one", "two", "three", "four", "five", "six", "seven", "eight", "nine" };
	for (const std::string line : tab)
	{
		char numbers[] = { NULL, NULL };
		for (int i = 0; i< line.length(); i++)
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
					if(numbersDict[j][0] == line[i] && line.length() - i >= numbersDict[j].length())
						//std::cout<< line.substr(i, numbersDict[j].length())<<std::endl;
						if (line.substr(i, numbersDict[j].length()) == numbersDict[j])
						{
							//std::cout<<j+1<<std::endl;
							if (numbers[0] == NULL)
							{
								numbers[0] = static_cast<char>('0' + j+1);
								numbers[1] = static_cast<char>('0' + j+1);
							}
							else
								numbers[1] = static_cast<char>('0' + j+1);
							break;
						}
				}
			}
		}
		try
		{
			std::string tmp = numbers;
			//std::cout<<tmp<<std::endl;
			std::cout<<std::stoi(tmp)<<std::endl;
			calibrationSum += std::stoi(tmp);
		}
		catch (...)
		{
			std::cerr << "B³¹d: Nieoczekiwany b³¹d." << std::endl;
		}
	}
	std::cout << "Part One: " << calibrationSum << std::endl;
}
