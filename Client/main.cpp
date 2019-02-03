#include <iostream>
#include <WS2tcpip.h>
#include "Winsock.h"
#include "UDPSocket.h"
#include "IPAddress.h"
#include "Packets.h"
#include "Dungeon.h"

#pragma comment (lib, "ws2_32.lib")

int main(void)
{
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
			}
		}
	}

	clientSocket.Close();
	Winsock::Shutdown();

	getchar();
	return 0;
}