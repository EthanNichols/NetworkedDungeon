#include <iostream>
#include <WS2tcpip.h>
#include <thread>
#include <conio.h>
#include <string>
#include <locale>
#include "Winsock.h"
#include "UDPSocket.h"
#include "IPAddress.h"
#include "Packets.h"
#include "Dungeon.h"
#include "ConsolePrint.h"

#pragma comment (lib, "ws2_32.lib")

UDPSocket* localSocket;
IPAddress serverIP;

uint8_t inputLine = 0;
bool stopThreads = false;
#define ENTER_KEY 13

void SendCommand(std::string command)
{
	Command sendCMD;
	std::locale loc;

	for (int i = 0; i < static_cast<int>(command.length()); ++i)
	{
		command[i] = std::toupper(command[i], loc);
	}

	if (strcmp(command.c_str(), "ENTER DUNGEON") == 0)
	{
		sendCMD.cmd = EnterDungeon;
	}
	else if (strcmp(command.c_str(), "LEAVE DUNGEON") == 0)
	{
		sendCMD.cmd = LeaveDungeon;
	}
	else if (strcmp(command.substr(0, command.find(' ')).c_str(), "MOVE") == 0)
	{
		sendCMD.cmd = Move;
		int splitPos = command.find(' ');

		if (strcmp(command.substr(splitPos, command.length() - splitPos).c_str(), "UP"))
		{
			*sendCMD.payload = MoveUp;
		}
		else if (strcmp(command.substr(splitPos, command.length() - splitPos).c_str(), "DOWN"))
		{
			*sendCMD.payload = MoveDown;
		}
		else if (strcmp(command.substr(splitPos, command.length() - splitPos).c_str(), "LEFT"))
		{
			*sendCMD.payload = MoveLeft;
		}
		else if (strcmp(command.substr(splitPos, command.length() - splitPos).c_str(), "RIGHT"))
		{
			*sendCMD.payload = MoveRight;
		}
	}
	else if (strcmp(command.c_str(), "GET TREASURE") == 0)
	{
		sendCMD.cmd = GetTreasure;
	}
	else if (strcmp(command.c_str(), "TREASURE AMOUNT") == 0)
	{
		sendCMD.cmd = TreasureAMT;
	}

	localSocket->Send(serverIP, &sendCMD, MAX_PACKET_SIZE);
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

				for (int i = 0; i < static_cast<int>(input.length()); ++i)
				{
					Console::Print(' ', i, inputLine);
				}

				Console::Print('\r', -1, inputLine);
				SendCommand(input);
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

	serverIP = IPAddress(127, 0, 0, 1, 54000);
	UDPSocket clientSocket = UDPSocket();
	localSocket = &clientSocket;
	clientSocket.BlockProgram(false);

	Dungeon map;
	MapDataPacket mapData;

	Command sendCMD;
	Status recvStatus;
	sendCMD.cmd = EnterDungeon;

	bool disconnect = false;

	while (!disconnect)
	{
		ZeroMemory(&recvStatus, sizeof(recvStatus));

		if (clientSocket.Receive(&recvStatus, sizeof(recvStatus), NULL) > 0)
		{
			printf("recieved");

			switch (recvStatus.status)
			{
			case GetMapData:
				mapData = *(reinterpret_cast<MapDataPacket*>(recvStatus.payload));
				map.SetSize(mapData.width, mapData.height);
				map.AddTiles(mapData.tiles, mapData.tilesSent);
				map.Draw();

				inputLine = mapData.height + 4;
				break;
			case Disconnect:
				printf("Leaving");
				disconnect = true;
				stopThreads = true;
				break;
			}
		}
	}

	inputThread.join();
	clientSocket.Close();
	Winsock::Shutdown();

	getchar();
	return 0;
}