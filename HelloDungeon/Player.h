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
	int GetXPosition() const;
	int GetYPosition() const;
	int PickupTreasure();
	int GetTreasureAmount() const;

	void RelativeMove(int x, int y);
	void MoveTo(int x, int y);

private:

	IPAddress clientIP;
	Dungeon* map;

	int x;
	int y;
	int treasureAmount;
};

