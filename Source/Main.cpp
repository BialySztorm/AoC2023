#include "Main.h"
#include <iostream>
#include <cstdlib>
#include "FileHandler.h"
#include "DayHandler.h"

Main::Main()
{
	do
	{
		Menu();
		std::cin>>option;
		DayHandler dayHandler(option);
		system("pause");
		system("cls");

	}while (option > 0);
}

Main::~Main()
{
}

void Main::Menu()
{
	std::cout<<"Select day 1-24: ";
}

