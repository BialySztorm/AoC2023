#include "Main.h"
#include <iostream>
#include <cstdlib>
#include "FileHandler.h"
#include "DayHandler.h"

Main::Main()
{
	DayHandler* dayHandler = new DayHandler("Data\\Input\\", "Data\\Output\\");
	do
	{
		Menu();
		std::cin >> option;
		dayHandler->HandleDay(option);
		system("pause");
		system("cls");
	} while (option > 0);
}

Main::~Main()
{
}

void Main::Menu()
{
	std::cout << "Select day 1-24: ";
}