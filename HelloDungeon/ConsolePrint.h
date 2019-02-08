#pragma once

#include <stdint.h>
#include <mutex>
#include <Windows.h>

/// <summary>
/// Class that only allows one printf function to run in
/// a multithreaded program. Which allows the position
/// of the print to be set without messing up.
/// </summary>
class Console
{
public:
	/// <summary>
	/// Locked printf of a character at a position within the console
	/// </summary>
	static void Print(char c, SHORT x, SHORT y);
	/// <summary>
	/// Locked printf of a string at a position within the console
	/// </summary>
	static void Print(const char* c, SHORT x, SHORT y);

private:
	static std::mutex consoleMutex;
};