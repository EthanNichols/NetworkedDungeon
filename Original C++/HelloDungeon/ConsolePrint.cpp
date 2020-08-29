#include "ConsolePrint.h"

std::mutex Console::consoleMutex;

void Console::Print(char c, SHORT x, SHORT y)
{
	consoleMutex.lock();
	COORD cord = { static_cast<SHORT>(x), static_cast<SHORT>(y) };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cord);
	printf("%c", c);
	consoleMutex.unlock();
}

void Console::Print(const char* c, SHORT x, SHORT y)
{
	consoleMutex.lock();
	COORD cord = { static_cast<SHORT>(x), static_cast<SHORT>(y) };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cord);
	printf("%s", c);
	consoleMutex.unlock();
}