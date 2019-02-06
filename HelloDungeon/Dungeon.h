#pragma once

#include <stdint.h>
#include <vector>
#include <map>

enum TileTypes
{
	WallTile = 0,
	PlayerTile = 1,
	TreasureTile = 2,
	NoneTile,
};

struct Treasure
{
	int minValue = 1;
	int maxValue;

	Treasure()
	{
		minValue = 1;
		maxValue = 1;
	}

	Treasure(int minVal, int maxVal)
	{
		minValue = minVal;
		maxValue = maxVal;
	}

	Treasure(int maxVal)
	{
		minValue = 1;
		maxValue = maxVal;
	}

	int GetValue()
	{
		return rand() % maxValue + minValue;
	}
};

struct TileData
{
	int x;
	int y;
	TileTypes tileType;

	TileData()
	{
		x = 0;
		y = 0;
		tileType = NoneTile;
	}

	TileData(int x, int y, TileTypes tileType)
	{
		this->x = x;
		this->y = y;
		this->tileType = tileType;
	}
};

class Dungeon
{
public:

	Treasure treasure;

	Dungeon();
	Dungeon(int width, int height, int maxTreasureValue, int maxTreasure);
	~Dungeon();

	void SetSize(int width, int height);
	void SpawnTreasure(int amount);
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
	TileTypes GetTileType(int x, int y);

	void Draw();
	void DrawBorders() const;
	void DrawTiles() const;

private:

	int width;
	int height;

	std::vector<TileData> tiles;
	std::map<int, TileData> tilePositions;
};

