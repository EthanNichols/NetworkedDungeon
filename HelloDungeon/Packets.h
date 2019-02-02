#pragma once

#include <stdint.h>

struct Command
{
	unsigned char cmd;
	char payload[256];
};

struct Status
{
	unsigned char status;
	char payload[256];
};

struct TilePacket
{
	uint8_t x;
	uint8_t y;
	char tileChar;
};

struct MapPacket
{
	uint8_t width;
	uint8_t height;
	uint8_t tilesSent;
	TilePacket tiles[256];
};