#pragma once

#include <stdint.h>
#include "Dungeon.h"

#define MAX_PACKET_SIZE 1400

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

enum Statuses
{
	MapData,
	Disconnect,
};

struct Command
{
	unsigned char cmd;
	char payload[MAX_PACKET_SIZE];
};

struct Status
{
	unsigned char status;
	char payload[MAX_PACKET_SIZE];
};

struct MapDataPacket
{
	int width;
	int height;
	int tilesSent;
	TileData tiles[32];

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