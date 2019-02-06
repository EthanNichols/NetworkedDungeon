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

#pragma comment (lib, "ws2_32.lib")

std::vector<Player*> players;
Dungeon map;

void SendUpdatedMap(UDPSocket* serverSocket)
{
	Status sendStatus;

	MapDataPacket mapData = { map.Width(), map.Height() };
	std::vector<TileData> tiles = map.GetTiles();
	mapData.tilesSent = static_cast<uint8_t>(tiles.size());
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

	printf("%d", players.size());

	serverSocket->Send(client, &sendStatus, sizeof(sendStatus));
}

int main(void)
{
	srand(static_cast<unsigned int>(time(NULL)));

	map = Dungeon(10, 10, 20);
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
				if (recvCMD.payload == "UP")
				{

				}
				else if (recvCMD.payload == "DOWN")
				{

				}
				else if (recvCMD.payload == "RIGHT")
				{

				}
				else if (recvCMD.payload == "LEFT")
				{

				}
			case LeaveDungeon:
				ClientLeaveDungeon(senderIP, &serverSocket);
				SendUpdatedMap(&serverSocket);
				break;
			case EnterDungeon:

				ClientEnterDungeon(senderIP);
				SendUpdatedMap(&serverSocket);
				break;
			}
			ZeroMemory(&recvCMD, sizeof(recvCMD));
			//map.Draw();
		}
	}

	serverSocket.Close();
	Winsock::Shutdown();

	return 0;
}