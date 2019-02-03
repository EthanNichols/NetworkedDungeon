#include "Dungeon.h"
#include <Windows.h>
#include <iostream>

#define TILE_WALL static_cast<uint8_t>(219)
#define TILE_TREASURE '$'
#define TILE_PLAYER '@'

Dungeon::Dungeon()
{
}

Dungeon::Dungeon(uint8_t width, uint8_t height, uint8_t maxTreasures)
{
	this->width = width;
	this->height = height;

	tiles.push_back({ 0, 0, 0 });
	tiles.push_back({ 1, 0, 1 });
	tiles.push_back({ 2, 0, 2 });
}


Dungeon::~Dungeon()
{
}

void Dungeon::SetSize(uint8_t width, uint8_t height)
{
	this->width = width;
	this->height = height;
}

void Dungeon::AddTile(TileData tile)
{
	tiles.push_back(tile);
}

void Dungeon::AddTiles(std::vector<TileData> tiles)
{
	this->tiles.insert(this->tiles.end(), tiles.begin(), tiles.end());
}

void Dungeon::AddTiles(TileData* tiles, uint8_t amount)
{
	this->tiles = std::vector<TileData>(tiles, tiles + amount);
}

uint8_t Dungeon::Width() const
{
	return width;
}

uint8_t Dungeon::Height() const
{
	return width;
}

std::vector<TileData> Dungeon::GetTiles() const
{
	return tiles;
}

void Dungeon::Draw() const
{
	DrawBorders();
	DrawTiles();
}

void Dungeon::DrawBorders() const
{
	COORD cord;

	for (int x = 0; x < width + 2; ++x)
	{
		cord = { static_cast<SHORT>(x), static_cast<SHORT>(0) };
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cord);
		printf("%c", TILE_WALL);

		cord = { static_cast<SHORT>(x), static_cast<SHORT>(height + 1) };
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cord);
		printf("%c", TILE_WALL);
	}
	for (int y = 0; y < height + 2; ++y)
	{
		cord = { static_cast<SHORT>(0), static_cast<SHORT>(y) };
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cord);
		printf("%c", TILE_WALL);

		cord = { static_cast<SHORT>(width + 1), static_cast<SHORT>(y) };
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cord);
		printf("%c", TILE_WALL);
	}
}

void Dungeon::DrawTiles() const
{
	COORD cord;
	char tileChar;

	for (int i = 0; i < static_cast<int>(tiles.size()); ++i)
	{
		cord = { static_cast<SHORT>(tiles[i].x + 1), static_cast<SHORT>(tiles[i].y + 1) };
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cord);

		switch (tiles[i].tileType)
		{
		case Wall:
			tileChar = TILE_WALL;
			break;
		case Player:
			tileChar = TILE_PLAYER;
			break;
		case Treasure:
			tileChar = TILE_TREASURE;
			break;
		default:
			continue;
		}

		printf("%c", tileChar);
	}
}
