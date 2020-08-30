#pragma once

#include <stdint.h>
#include "Dungeon.h"
#include "IPAddress.h"

class Player
{
public:

	/// <summary>
	/// Create a player based on the IPAddress passing in the map data
	/// </summary>
	Player(IPAddress clientIP, Dungeon* map);
	~Player();

	/// <summary>
	/// Spawn the player randomly on the map
	/// </summary>
	void Spawn();

	/// <summary>
	/// Get the IP address that controls this player
	/// </summary>
	IPAddress GetClientIP() const;

	int GetXPosition() const;
	int GetYPosition() const;

	/// <summary>
	/// Try to pickup treasure that is adjacent to the player
	/// </summary>
	bool PickupTreasure();

	/// <summary>
	/// Return the amount of treasure this player has
	/// </summary>
	int GetTreasureAmount() const;

	/// <summary>
	/// Move the player relative to their current position
	/// </summary>
	void RelativeMove(int x, int y);

	/// <summary>
	/// Move the player to a specific position on the map
	/// </summary>
	void MoveTo(int x, int y);

private:

	IPAddress clientIP;
	Dungeon* map;

	int x;
	int y;
	int treasureAmount;
};

