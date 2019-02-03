#include <iostream>
#include <WS2tcpip.h>
#include <time.h>
#include <vector>
#include "UDPSocket.h"
#include "IPAddress.h"
#include "Winsock.h"
#include "Packets.h"
#include "Dungeon.h"

#pragma comment (lib, "ws2_32.lib")

int main(void)
{
	srand(static_cast<unsigned int>(time(NULL)));

	Dungeon map = Dungeon(10, 10, 20);
	map.Draw();

	Winsock::Init();

	UDPSocket serverSocket = UDPSocket();
	serverSocket.Open(IPAddress(0, 54000));
	serverSocket.BlockProgram(false);

	IPAddress senderIP;
	Command sendCMD;
	Command recvCMD;

	while (true)
	{
		ZeroMemory(&recvCMD, sizeof(recvCMD));

		if (serverSocket.Receive(&recvCMD, sizeof(recvCMD), &senderIP) > 0)
		{
			switch (recvCMD.cmd)
			{
			case GetMapData:

				MapDataPacket mapData = { map.Width(), map.Height() };
				std::vector<TileData> tiles = map.GetTiles();
				mapData.tilesSent = static_cast<uint8_t>(tiles.size());
				std::copy(tiles.begin(), tiles.end(), mapData.tiles);

				sendCMD.cmd = GetMapData;
				memcpy_s(sendCMD.payload, MAX_PACKET_SIZE, reinterpret_cast<char*>(&mapData), sizeof(mapData));

				serverSocket.Send(senderIP, &sendCMD, sizeof(sendCMD));
			}
		}
	}

	serverSocket.Close();
	Winsock::Shutdown();

	getchar();
	return 0;
}