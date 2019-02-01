#include <iostream>
#include <WS2tcpip.h>

#include "Winsock.h"
#include "UDPSocket.h"
#include "IPAddress.h"

#pragma comment (lib, "ws2_32.lib")

int main(void)
{
	Winsock::Init();

	IPAddress serverIP = IPAddress(127, 0, 0, 1, 54000);
	UDPSocket clientSocket = UDPSocket();
	clientSocket.BlockProgram(false);

	const char s[] = "Testing";
	clientSocket.Send(serverIP, s, sizeof(s));

	while (true)
	{
		char buf[256];
		if (clientSocket.Receive(buf, sizeof(buf), NULL) > 0)
		{
			printf("%s", buf);
			break;
		}
	}

	clientSocket.Close();
	Winsock::Shutdown();

	getchar();
	return 0;
}