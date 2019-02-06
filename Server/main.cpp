#include <iostream>
#include <WS2tcpip.h>
#include <time.h>
#include <vector>
#include "UDPSocket.h"
#include "IPAddress.h"
#include "Winsock.h"
#include "Packets.h"
#include "Dungeon.h"
#include "Player.h"
#include "ConsolePrint.h"

#pragma comment (lib, "ws2_32.lib")

std::vector<Player*> players;
Dungeon map;

void SendUpdatedMap(UDPSocket* serverSocket)
{
	Status sendStatus;

	MapDataPacket mapData = { map.Width(), map.Height() };
	std::vector<TileData> tiles = map.GetTiles();
	mapData.tilesSent = static_cast<int>(tiles.size());
	std::copy(tiles.begin(), tiles.end(), mapData.tiles);

	sendStatus.status = MapData;
	memcpy_s(sendStatus.payload, MAX_PACKET_SIZE, reinterpret_cast<char*>(&mapData), sizeof(mapData));
	for (int i = 0; i < static_cast<int>(players.size()); ++i)
	{
		serverSocket->Send(players[i]->GetClientIP(), &sendStatus, sizeof(sendStatus));
	}
}

void ClientEnterDungeon(IPAddress client)
{
	bool alreadyEntered = false;

	for (int i = 0; i < static_cast<int>(players.size()); ++i)
	{
		if (players[i]->GetClientIP() == client)
		{
			alreadyEntered = true;
			break;
		}
	}
	if (alreadyEntered)
	{
		return;
	}

	Player* newPlayer = new Player(client, &map);
	newPlayer->Spawn();
	players.push_back(newPlayer);
}

void ClientLeaveDungeon(IPAddress client, UDPSocket* serverSocket)
{
	Status sendStatus;
	sendStatus.status = Disconnect;

	for (int i = 0; i < static_cast<int>(players.size()); ++i)
	{
		if (players[i]->GetClientIP() == client)
		{
			map.RemoveTile(players[i]->GetXPosition(), players[i]->GetYPosition());
			delete players[i];
			players.erase(players.begin() + i);
			break;
		}
	}

	serverSocket->Send(client, &sendStatus, sizeof(sendStatus));
}

void ClientMovePlayer(IPAddress client, int x, int y)
{
	for (int i = 0; i < static_cast<int>(players.size()); ++i)
	{
		if (players[i]->GetClientIP() == client)
		{
			players[i]->RelativeMove(x, y);
			return;
		}
	}
}

void ClientGetTreasure(IPAddress client, UDPSocket* serverSocket)
{
	bool treasureFound = false;

	Status sendStatus;
	sendStatus.status = TreasureAMT;

	for (int i = 0; i < static_cast<int>(players.size()); ++i)
	{
		if (players[i]->GetClientIP() == client)
		{
			if (players[i]->PickupTreasure())
			{
				map.SpawnTreasure(1);
				std::string treasureStr = std::to_string(players[i]->GetTreasureAmount());
				strcpy_s(sendStatus.payload, treasureStr.c_str());
				treasureFound = true;
				break;
			}
		}
	}
	if (!treasureFound)
	{
		return;
	}

	SendUpdatedMap(serverSocket);
	serverSocket->Send(client, &sendStatus, sizeof(sendStatus));
}

int main(void)
{
	srand(static_cast<unsigned int>(time(NULL)));

	map = Dungeon(15, 15, 5, 20);
	map.Draw();

	Winsock::Init();

	UDPSocket serverSocket = UDPSocket();
	serverSocket.Open(IPAddress(0, 54000));
	serverSocket.BlockProgram(false);

	IPAddress senderIP;
	Command recvCMD;

	while (true)
	{
		if (serverSocket.Receive(&recvCMD, sizeof(recvCMD), &senderIP) > 0)
		{
			switch (recvCMD.cmd)
			{
			case Move:
				if (strcmp(recvCMD.payload, "UP") == 0)
				{
					ClientMovePlayer(senderIP, 0, -1);
				}
				else if (strcmp(recvCMD.payload, "DOWN") == 0)
				{
					ClientMovePlayer(senderIP, 0, 1);
				}
				else if (strcmp(recvCMD.payload, "RIGHT") == 0)
				{
					ClientMovePlayer(senderIP, 1, 0);
				}
				else if (strcmp(recvCMD.payload, "LEFT") == 0)
				{
					ClientMovePlayer(senderIP, -1, 0);
				}
				break;
			case GetTreasure:
				ClientGetTreasure(senderIP, &serverSocket);
				break;
			case LeaveDungeon:
				ClientLeaveDungeon(senderIP, &serverSocket);
				break;
			case EnterDungeon:
				ClientEnterDungeon(senderIP);
				break;
			default:
				break;
			}
			ZeroMemory(&recvCMD, sizeof(recvCMD));
			SendUpdatedMap(&serverSocket);
			map.Draw();
		}
	}

	serverSocket.Close();
	Winsock::Shutdown();

	return 0;
}