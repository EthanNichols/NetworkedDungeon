#pragma once

#include <stdint.h>
#include "Dungeon.h"

#define MAX_PACKET_SIZE 1400

/// <summary>
/// List of all of the commands that can be sent
/// </summary>
enum Commands
{
	GetMapData,
	EnterDungeon,
	LeaveDungeon,
	Move,
	Inspect,
	GetTreasure,
	TreasureAMT,
};

/// <summary>
/// List of all of the statuses that can be sent
/// </summary>
enum Statuses
{
	MapData,
	Disconnect,
};

/// <summary>
/// Command packet data struct
/// </summary>
struct Command
{
	unsigned char cmd;
	char payload[MAX_PACKET_SIZE];
};

/// <summary>
/// Status packet data struct
/// </summary>
struct Status
{
	unsigned char status;
	char payload[MAX_PACKET_SIZE];
};

/// <summary>
/// Struct that contains information about the map
/// </summary>
struct MapDataPacket
{
	int width;
	int height;
	int tilesSent;
	TileData tiles[64];

	MapDataPacket()
	{
		width = 0;
		height = 0;
		tilesSent = 0;
	}

	MapDataPacket(int width, int height)
	{
		this->width = width;
		this->height = height;
		tilesSent = 0;
	}
};