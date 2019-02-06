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

int Player::PickupTreasure()
{
	return int();
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
