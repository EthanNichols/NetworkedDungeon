#include "Winsock.h"
#include <WinSock2.h>

bool Winsock::Init()
{
	WSADATA wsaData;
	return WSAStartup(MAKEWORD(2, 2), &wsaData) == NO_ERROR;
}

void Winsock::Shutdown()
{
	WSACleanup();
}