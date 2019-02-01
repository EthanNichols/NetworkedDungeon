#include <iostream>
#include <WS2tcpip.h>
#include "UDPSocket.h"
#include "IPAddress.h"
#include "Winsock.h"

#pragma comment (lib, "ws2_32.lib")

int main(void)
{
	Winsock::Init();

	UDPSocket serverSocket = UDPSocket();
	serverSocket.Open(IPAddress(0, 54000));
	serverSocket.BlockProgram(false);

	IPAddress senderIP;
	char buf[128];

	while (true)
	{
		printf("Listen\n");

		ZeroMemory(buf, 128);

		if (serverSocket.Receive(buf, 128, &senderIP) > 0)
		{
			printf("Message recv from %s : %s\n", senderIP.ToString().c_str(), buf);
			serverSocket.Send(senderIP, buf, 128);
			break;
		}
	}

	serverSocket.Close();
	Winsock::Shutdown();

	getchar();
	return 0;
}