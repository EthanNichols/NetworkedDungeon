#include "Player.h"



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
	do
	{
		x = rand() % map->Width();
		y = rand() % map->Height();
	} while (map->Collision(x, y));

	map->AddTile({ x, y, TileTypes::PlayerTile });
}

IPAddress Player::GetClientIP() const
{
	return clientIP;
}

uint8_t Player::GetXPosition() const
{
	return x;
}

uint8_t Player::GetYPosition() const
{
	return y;
}

uint32_t Player::PickupTreasure()
{
	return uint32_t();
}

uint16_t Player::GetTreasureAmount() const
{
	return treasureAmount;
}

void Player::RelativeMove(uint8_t x, uint8_t y)
{
	if (map->Collision(this->x + x, this->y + y))
	{
		return;
	}
	else
	{
		this->x += x;
		this->y += y;
	}
}

void Player::MoveTo(uint8_t x, uint8_t y)
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
