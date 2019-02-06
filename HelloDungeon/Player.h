#pragma once

#include <stdint.h>
#include "Dungeon.h"
#include "IPAddress.h"

class Player
{
public:
	Player(IPAddress clientIP, Dungeon* map);
	~Player();

	void Spawn();
	IPAddress GetClientIP() const;
	uint8_t GetXPosition() const;
	uint8_t GetYPosition() const;
	uint32_t PickupTreasure();
	uint16_t GetTreasureAmount() const;

	void RelativeMove(uint8_t x, uint8_t y);
	void MoveTo(uint8_t x, uint8_t y);

private:

	IPAddress clientIP;
	Dungeon* map;

	uint8_t x;
	uint8_t y;
	uint16_t treasureAmount;
};

