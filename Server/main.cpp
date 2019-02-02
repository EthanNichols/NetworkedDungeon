#include <iostream>
#include <WS2tcpip.h>
#include <time.h>
#include <vector>
#include "UDPSocket.h"
#include "IPAddress.h"
#include "Winsock.h"
#include "Packets.h"
#include "Map.h"

#pragma comment (lib, "ws2_32.lib")

int main(void)
{
	srand(static_cast<unsigned int>(time(NULL)));

	Map map = Map(20, 20, 20);
	map.Draw();

	Winsock::Init();

	UDPSocket serverSocket = UDPSocket();
	serverSocket.Open(IPAddress(0, 54000));
	serverSocket.BlockProgram(false);

	IPAddress senderIP;
	char buf[128];

	MapPacket mapTreasures;
	mapTreasures.width = map.Width();
	mapTreasures.height = map.Height();

	std::vector<Treasure*> treasures = map.GetTreasures();
	ZeroMemory(mapTreasures.tiles, sizeof(mapTreasures.tiles));

	mapTreasures.tilesSent = treasures.size();

	for (uint16_t i = 0; i < treasures.size(); ++i)
	{
		mapTreasures.tiles[i].tileChar = '!';
		mapTreasures.tiles[i].x = treasures[i]->x;
		mapTreasures.tiles[i].y = treasures[i]->y;
	}

	while (true)
	{
		ZeroMemory(buf, 128);

		if (serverSocket.Receive(buf, 128, &senderIP) > 0)
		{
			serverSocket.Send(senderIP, static_cast<const void*>(&mapTreasures), sizeof(mapTreasures));
		}
	}

	serverSocket.Close();
	Winsock::Shutdown();

	getchar();
	return 0;
}