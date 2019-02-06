#pragma once

#include <stdint.h>
#include <vector>
#include <map>

enum TileTypes
{
	WallTile = 0,
	PlayerTile = 1,
	TreasureTile = 2,
};

struct TileData
{
	int x;
	int y;
	int tileType;

	TileData()
	{
		x = 0;
		y = 0;
		tileType = 0;
	}

	TileData(int x, int y, int tileType)
	{
		this->x = x;
		this->y = y;
		this->tileType = tileType;
	}
};

class Dungeon
{
public:

	Dungeon();
	Dungeon(int width, int height, int maxTreasure);
	~Dungeon();

	void SetSize(int width, int height);
	void AddTile(TileData);
	void AddTiles(std::vector<TileData> tiles);
	void AddTiles(TileData* tiles, int amount);
	void RemoveTile(int x, int y);
	void SetTiles(TileData* tiles, int amount);
	void SetTiles(std::vector<TileData> tiles);

	bool Collision(int x, int y);

	int Width() const;
	int Height() const;
	std::vector<TileData> GetTiles();

	void Draw();
	void DrawBorders() const;
	void DrawTiles() const;

private:
	int width;
	int height;

	std::vector<TileData> tiles;
	std::map<int, TileData> tilePositions;
};

