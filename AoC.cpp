#include "Source/Main.h"
#include <Windows.h>

int main()
{
	SetConsoleTitle(TEXT("Advent of Code 2023"));
	Main* obj = new Main();
	delete(obj);
}