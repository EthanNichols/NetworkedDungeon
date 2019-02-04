#include "Dungeon.h"
#include <Windows.h>
#include <iostream>
#include "ConsolePrint.h"

#define TILE_WALL 219
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
	for (int x = 0; x < width + 2; ++x)
	{
		Console::Print(TILE_WALL, x, 0);
		Console::Print(TILE_WALL, x, height + 1);
	}
	for (int y = 0; y < height + 2; ++y)
	{
		Console::Print(TILE_WALL, 0, y);
		Console::Print(TILE_WALL, width + 1, y);
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

		Console::Print(tileChar, static_cast<uint8_t>(cord.X), static_cast<uint8_t>(cord.Y));
	}
}
