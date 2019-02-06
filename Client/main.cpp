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

int treasureCount = 0;
int inputLine = 0;
bool stopThreads = false;
#define ENTER_KEY 13
#define BACKSPACE_KEY 8

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
	else if (strcmp(command.substr(0, 4).c_str(), "MOVE") == 0)
	{
		sendCMD.cmd = Move;
		int splitPos = static_cast<int>(command.find(' '));

		if (splitPos == std::string::npos)
		{
			return;
		}

		strcpy_s(sendCMD.payload, sizeof(sendCMD.payload), command.substr(splitPos+1, command.length()).c_str());
	}
	else if (strcmp(command.c_str(), "GET TREASURE") == 0)
	{
		sendCMD.cmd = GetTreasure;
	}
	else if (strcmp(command.c_str(), "TREASURE AMOUNT") == 0)
	{
		sendCMD.cmd = TreasureAMT;
	}
	else
	{
		return;
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

				SendCommand(input);
				input.clear();
			}
			else if (c == BACKSPACE_KEY)
			{
				Console::Print(' ', static_cast<int>(input.length()) - 1, inputLine);
				input = input.substr(0, input.length() - 1);
			}
			else
			{
				input += c;
			}

			Console::Print(input.c_str(), 0, inputLine);

		}
	}
}

int main(void)
{
	std::thread inputThread(ProcessInput);

	std::string collectTreasureString = "Treasure Collected: ";

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
			switch (recvStatus.status)
			{
			case MapData:
				mapData = *(reinterpret_cast<MapDataPacket*>(recvStatus.payload));
				map.SetSize(mapData.width, mapData.height);
				map.SetTiles(mapData.tiles, mapData.tilesSent);
				map.Draw();

				inputLine = mapData.height + 4;
				break;
			case Disconnect:
				disconnect = true;
				stopThreads = true;
				break;
			case TreasureAMT:
				collectTreasureString = "Treasure Collected: ";
				treasureCount += std::stoi(recvStatus.payload, nullptr, 10);
				collectTreasureString += std::to_string(treasureCount);
				Console::Print(collectTreasureString.c_str(), 0, inputLine - 2);
				break;
			default:
				break;
			}
			Console::Print(' ', 0, inputLine);
		}
	}

	inputThread.join();
	clientSocket.Close();
	Winsock::Shutdown();
	return 0;
}