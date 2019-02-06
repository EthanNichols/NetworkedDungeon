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
	uint8_t x;
	uint8_t y;
	uint8_t tileType;

	TileData()
	{
		x = 0;
		y = 0;
		tileType = 0;
	}

	TileData(uint8_t x, uint8_t y, uint8_t tileType)
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
	Dungeon(uint8_t width, uint8_t height, uint8_t maxTreasure);
	~Dungeon();

	void SetSize(uint8_t width, uint8_t height);
	void AddTile(TileData);
	void AddTiles(std::vector<TileData> tiles);
	void AddTiles(TileData* tiles, uint8_t amount);
	void RemoveTile(uint8_t x, uint8_t y);

	bool Collision(uint8_t x, uint8_t y);

	uint8_t Width() const;
	uint8_t Height() const;
	std::vector<TileData> GetTiles();

	void Draw();
	void DrawBorders() const;
	void DrawTiles() const;

private:
	int width;
	int height;

	std::vector<TileData> tiles;
	std::map<uint16_t, TileData> tilePositions;
};

