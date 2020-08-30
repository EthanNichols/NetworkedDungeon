#pragma once
class Winsock
{
public:

	/// <summary>
	/// Initialize winsockets
	/// </summary>
	static bool Init();

	/// <summary>
	/// Shutdown winsockets
	/// </summary>
	static void Shutdown();
};

