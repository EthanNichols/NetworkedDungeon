#include "Player.h"
#include <time.h>

Player::Player(IPAddress clientIP, Dungeon* map)
{
	this->clientIP = clientIP;
	this->map = map;
}


Player::~Player()
{
}

void Player::Spawn()
{
	x = rand() % map->Width();
	y = rand() % map->Height();

	while (map->Collision(x, y))
	{
		x++;
		if (x >= map->Width())
		{
			y++;
			x = 0;

			if (y >= map->Height())
			{
				y = 0;
			}
		}
	}
	map->AddTile(TileData(x, y, TileTypes::PlayerTile));
}

IPAddress Player::GetClientIP() const
{
	return clientIP;
}

int Player::GetXPosition() const
{
	return x;
}

int Player::GetYPosition() const
{
	return y;
}

bool Player::PickupTreasure()
{
	bool treasureFound = false;

	for (int x = -1; x <= 1; ++x)
	{
		if (treasureFound)
		{
			break;
		}

		for (int y = -1; y <= 1; ++y)
		{
			if ((x != 0 && y != 0) ||
				(x == 0 && y == 0))
			{
				continue;
			}
			else
			{
				if (map->GetTileType(this->x + x, this->y + y) == TreasureTile)
				{
					map->RemoveTile(this->x + x, this->y + y);
					treasureFound = true;
					treasureAmount += map->treasure.GetValue();
					break;
				}
			}
		}
	}

	return treasureFound;
}

int Player::GetTreasureAmount() const
{
	return treasureAmount;
}

void Player::RelativeMove(int x, int y)
{
	if (map->Collision(this->x + x, this->y + y))
	{
		return;
	}
	else
	{
		map->RemoveTile(this->x, this->y);
		this->x += x;
		this->y += y;
		map->AddTile(TileData(this->x, this->y, PlayerTile));
	}
}

void Player::MoveTo(int x, int y)
{
	if (map->Collision(x, y))
	{
		return;
	}
	else
	{
		this->x = x;
		this->y = y;
	}
}
