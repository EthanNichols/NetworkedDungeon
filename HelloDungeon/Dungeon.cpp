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

Dungeon::Dungeon(int width, int height, int maxTreasures)
{
	this->width = width;
	this->height = height;

	tilePositions.insert(std::pair<int, TileData>(0, TileData(0, 0, 0)));
	tilePositions.insert(std::pair<int, TileData>(1, TileData(1, 0, 1)));
	tilePositions.insert(std::pair<int, TileData>(2, TileData(2, 0, 2)));
}


Dungeon::~Dungeon()
{
}

void Dungeon::SetSize(int width, int height)
{
	this->width = width;
	this->height = height;
}

void Dungeon::AddTile(TileData tile)
{
	tilePositions.insert(std::pair<int, TileData>(tile.x + tile.y * width, tile));
}

void Dungeon::AddTiles(std::vector<TileData> tiles)
{
	for (int i = 0; i < static_cast<int>(tiles.size()); ++i)
	{
		tilePositions.insert(std::pair<int, TileData>(tiles[i].x + tiles[i].y * width, tiles[i]));
	}
}

void Dungeon::AddTiles(TileData* tiles, int amount)
{
	for (int i = 0; i < amount; ++i)
	{
		tilePositions.insert(std::pair<int, TileData>(tiles[i].x + tiles[i].y * width, tiles[i]));
	}
}

void Dungeon::SetTiles(TileData* tiles, int amount)
{
	tilePositions.clear();
	AddTiles(tiles, amount);
}

void Dungeon::SetTiles(std::vector<TileData> tiles)
{
	tilePositions.clear();
	AddTiles(tiles);
}

void Dungeon::RemoveTile(int x, int y)
{
	tilePositions.erase(tilePositions.find(x + y * width));
}

bool Dungeon::Collision(int x, int y)
{
	if (x < 0 || x >= width ||
		y < 0 || y >= height)
	{
		return true;
	}

	return tilePositions.count(x + y * width);
}

int Dungeon::Width() const
{
	return width;
}

int Dungeon::Height() const
{
	return width;
}

std::vector<TileData> Dungeon::GetTiles()
{
	std::map<int, TileData>::const_iterator it;

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

		Console::Print(tileChar, static_cast<int>(cord.X), static_cast<int>(cord.Y));
	}
}
