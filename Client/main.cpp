#include <iostream>
#include <WS2tcpip.h>
#include <thread>
#include <conio.h>
#include <string>
#include "Winsock.h"
#include "UDPSocket.h"
#include "IPAddress.h"
#include "Packets.h"
#include "Dungeon.h"
#include "ConsolePrint.h"

#pragma comment (lib, "ws2_32.lib")

uint8_t inputLine = 0;
bool stopThreads = false;
#define ENTER_KEY 13

void SendCommand(char* command)
{

}

void ProcessInput()
{
	std::string input;

	while (!stopThreads)
	{
		if (_kbhit())
		{
			char c = _getch();
			if (c == ENTER_KEY)
			{
				input += '\0';

				for (int i = 0; i < input.length(); ++i)
				{
					Console::Print(' ', i, inputLine);
				}

				Console::Print('\r', -1, inputLine);
				input.clear();
			}
			else
			{
				Console::Print('\r', 0, inputLine);
				input += c;
				printf("%s", input.c_str());
			}
		}
	}
}

int main(void)
{
	std::thread inputThread(ProcessInput);

	Winsock::Init();

	IPAddress serverIP = IPAddress(127, 0, 0, 1, 54000);
	UDPSocket clientSocket = UDPSocket();
	clientSocket.BlockProgram(false);

	Dungeon map;

	Command sendCMD;
	Command recvCMD;
	sendCMD.cmd = GetMapData;

	clientSocket.Send(serverIP, &sendCMD, MAX_PACKET_SIZE);

	while (true)
	{
		ZeroMemory(&recvCMD, sizeof(recvCMD));

		if (clientSocket.Receive(&recvCMD, sizeof(recvCMD), NULL) > 0)
		{
			switch (recvCMD.cmd)
			{
			case GetMapData:
				MapDataPacket mapData = *(reinterpret_cast<MapDataPacket*>(recvCMD.payload));
				map.SetSize(mapData.width, mapData.height);
				map.AddTiles(mapData.tiles, mapData.tilesSent);
				map.Draw();

				inputLine = mapData.height + 4;
			}
		}
	}

	inputThread.join();
	clientSocket.Close();
	Winsock::Shutdown();

	getchar();
	return 0;
}