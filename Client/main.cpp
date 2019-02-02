#include <iostream>
#include <WS2tcpip.h>
#include "Winsock.h"
#include "UDPSocket.h"
#include "IPAddress.h"
#include "Packets.h"

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
		MapPacket buf;
		if (clientSocket.Receive(&buf, sizeof(buf), NULL) > 0)
		{
			for (int i = 0; i < buf.tilesSent; ++i)
			{
				COORD cord = { static_cast<SHORT>(buf.tiles[i].x + 1), static_cast<SHORT>(buf.tiles[i].y + 1) };
				SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cord);
				printf("%c", buf.tiles[i].tileChar);
			}
			break;
		}
	}

	clientSocket.Close();
	Winsock::Shutdown();

	getchar();
	return 0;
}