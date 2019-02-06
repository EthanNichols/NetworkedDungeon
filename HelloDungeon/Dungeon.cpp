#include "Dungeon.h"
#include <Windows.h>
#include <iostream>
#include "ConsolePrint.h"

#define TILE_WALL static_cast<unsigned char>(219)
#define TILE_TREASURE '$'
#define TILE_PLAYER '@'

Dungeon::Dungeon()
{
}

Dungeon::Dungeon(uint8_t width, uint8_t height, uint8_t maxTreasures)
{
	this->width = width;
	this->height = height;

	tilePositions.insert(std::pair<uint16_t, TileData>(0, TileData(0, 0, 0)));
	tilePositions.insert(std::pair<uint16_t, TileData>(1, TileData(1, 0, 1)));
	tilePositions.insert(std::pair<uint16_t, TileData>(2, TileData(2, 0, 2)));
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
	tilePositions.insert(std::pair<uint16_t, TileData>(tile.x + tile.y * width, tile));
}

void Dungeon::AddTiles(std::vector<TileData> tiles)
{
	for (int i = 0; i < static_cast<int>(tiles.size()); ++i)
	{
		tilePositions.insert(std::pair<uint16_t, TileData>(tiles[i].x + tiles[i].y * width, tiles[i]));
	}
}

void Dungeon::AddTiles(TileData* tiles, uint8_t amount)
{
	for (int i = 0; i < amount; ++i)
	{
		tilePositions.insert(std::pair<uint16_t, TileData>(tiles[i].x + tiles[i].y * width, tiles[i]));
	}
}

void Dungeon::RemoveTile(uint8_t x, uint8_t y)
{
	tilePositions.erase(tilePositions.find(x + y * width));
	Console::Print(' ', x+1, y+1);
}

bool Dungeon::Collision(uint8_t x, uint8_t y)
{
	if (x <= 0 || x >= width ||
		y <= 0 || y >= height)
	{
		return true;
	}

	return tilePositions.count(x + y * width);
}

uint8_t Dungeon::Width() const
{
	return width;
}

uint8_t Dungeon::Height() const
{
	return width;
}

std::vector<TileData> Dungeon::GetTiles()
{
	std::map<uint16_t, TileData>::const_iterator it;

	tiles.clear();

	for (it = tilePositions.begin(); it != tilePositions.end(); ++it)
	{
		tiles.push_back(it->second);
	}

	return tiles;
}

void Dungeon::Draw()
{
	GetTiles();
	system("CLS");
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

	for (int i=0; i<static_cast<int>(tiles.size()); ++i)
	{
		cord = { static_cast<SHORT>(tiles[i].x + 1), static_cast<SHORT>(tiles[i].y + 1) };
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cord);
	
		switch (tiles[i].tileType)
		{
		case WallTile:
			tileChar = TILE_WALL;
			break;
		case PlayerTile:
			tileChar = TILE_PLAYER;
			break;
		case TreasureTile:
			tileChar = TILE_TREASURE;
			break;
		default:
			continue;
		}

		Console::Print(tileChar, static_cast<uint8_t>(cord.X), static_cast<uint8_t>(cord.Y));
	}
}
