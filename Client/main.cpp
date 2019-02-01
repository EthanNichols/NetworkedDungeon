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

	const char s[] = "Tezting Bullshit";
	clientSocket.Send(serverIP, s, sizeof(s));

	clientSocket.Open(IPAddress(0, 54000));

	char buf[256];
	clientSocket.Receive(buf, sizeof(buf), NULL);
	printf("%s", buf);

	clientSocket.Close();
	Winsock::Shutdown();

	getchar();
	return 0;
}