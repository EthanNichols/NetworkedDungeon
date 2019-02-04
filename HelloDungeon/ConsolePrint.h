#pragma once

#include <stdint.h>
#include <mutex>
#include <Windows.h>

class Console
{
public:
	static void Print(char c, SHORT x, SHORT y);

private:
	static std::mutex consoleMutex;
};