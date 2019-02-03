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
	uint8_t width;
	uint8_t height;
	uint8_t tilesSent;
	TileData tiles[256];
};