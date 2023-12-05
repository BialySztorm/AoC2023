#pragma once
class Main
{
public:
	Main();
	~Main();
private:
	int option = 0;

	void Menu(const int day);
	void Goodbye();
};
