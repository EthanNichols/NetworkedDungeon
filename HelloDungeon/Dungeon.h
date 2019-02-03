#pragma once

#include <stdint.h>
#include <vector>

enum TileTypes
{
	Wall = 0,
	Player = 1,
	Treasure = 2,
};

struct TileData
{
	uint8_t x;
	uint8_t y;
	uint8_t tileType;
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

	uint8_t Width() const;
	uint8_t Height() const;
	std::vector<TileData> GetTiles() const;

	void Draw() const;
	void DrawBorders() const;
	void DrawTiles() const;

private:
	int width;
	int height;

	std::vector<TileData> tiles;
};

