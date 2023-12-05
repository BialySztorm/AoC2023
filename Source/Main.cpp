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
		Menu(dayHandler->getCurrentDay());
		std::cin >> option;
		if(option <= 0 || option > 25)
		{
			system("cls");
			continue;
		}
		dayHandler->HandleDay(option);
		system("pause");
		system("cls");
	} while (option > 0);
	Goodbye();
}

Main::~Main()
{
}

void Main::Menu(const int day)
{
	
	std::cout << " _______     _                                   ___    _______          _       " << std::endl;
	std::cout << "(_______)   | |                   _             / __)  (_______)        | |      " << std::endl;
	std::cout << " _______  __| |_   _ _____ ____ _| |_     ___ _| |__    _       ___   __| |_____ " << std::endl;
	std::cout << "|  ___  |/ _  | | | | ___ |  _ (_   _)   / _ (_   __)  | |     / _ \\ / _  | ___ |" << std::endl;
	std::cout << "| |   | ( (_| |\\ V /| ____| | | || |_   | |_| || |     | |____| |_| ( (_| | ____|" << std::endl;
	std::cout << "|_|   |_|\\____| \\_/ |_____)_| |_| \\__)   \\___/ |_|      \\______)___/ \\____|_____)" << std::endl;
	std::cout << "                                                                   by WhiteStorm "<< std::endl;
	std::cout << "\n\nSelect Day from 1-" << day << ", or 0 to end the program: ";
}

void Main::Goodbye()
{
	std::cout << "                       * Happy Christmas! *\n\n";
	std::cout << "                                 |L   " << std::endl;
	std::cout << "                                ,' `  " << std::endl;
	std::cout << "                               /.o `,    " << std::endl;
	std::cout << "                               `, |-`,   " << std::endl;
	std::cout << "                              -',    '   " << std::endl;
	std::cout << "                             `,'_)   '\\  " << std::endl;
	std::cout << "                             ,'    `-`,  " << std::endl;
	std::cout << "                            _`o,-   (_)/ " << std::endl;
	std::cout << "                           '_ '    o  `-," << std::endl;
	std::cout << "                           /   ,-L   `-' " << std::endl;
	std::cout << "                          _`-`_     ,  `'." << std::endl;
	std::cout << "                         ;.  (,'  `| `.-. \\" << std::endl;
	std::cout << "                         ,``_'    (_)  o `'" << std::endl;
	std::cout << "                        ,` '_  ,|\\   o   _ \\ " << std::endl;
	std::cout << "                       /..-(_)' |','..-`(_)-`" << std::endl;
	std::cout << "                                |  |        " << std::endl;
	std::cout << "                              --'  `--" << std::endl;
}
