#pragma once

#include <stdint.h>
#include <vector>
#include <map>

/// <summary>
/// The different types of tiles that could be rendered
/// </summary>
enum TileTypes
{
	WallTile = 0,
	PlayerTile = 1,
	TreasureTile = 2,
	NoneTile,
};

/// <summary>
/// Information about treasure on the map
/// </summary>
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

/// <summary>
/// Information about each tile that is on the map
/// </summary>
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
	/// <summary>
	/// Data that all treasure on the map references
	/// </summary>
	Treasure treasure;

	Dungeon();
	/// <summary>
	/// Create a dungeon given the size, treasure to spawn, and value of treasure
	/// </summary>
	/// <param name="width">Width of the dungeon</param>
	/// <param name="height">Height of the dungeon</param>
	/// <param name="maxTreasureValue">The maximum value treasure can be</param>
	/// <param name="maxTreasure">The amount of treasure to spawn</param>
	Dungeon(int width, int height, int maxTreasureValue, int maxTreasure);
	~Dungeon();

	/// <summary>
	/// Set the size of the map
	/// </summary>
	/// <param name="width">Width of the dungeon</param>
	/// <param name="height">Height of the dungeon</param>
	void SetSize(int width, int height);

	/// <summary>
	/// Spawn treasure in the dungeon
	/// </summary>
	/// <param name="height">The amount of treasure to spawn</param>
	void SpawnTreasure(int amount);

	/// <summary>
	/// Add a tile to render on the map
	/// </summary>
	void AddTile(TileData);

	/// <summary>
	/// Add a list of tiles to render on the map
	/// </summary>
	void AddTiles(std::vector<TileData> tiles);
	/// <summary>
	/// Add a list of tiles to render on the map
	/// </summary>
	void AddTiles(TileData* tiles, int amount);
	/// <summary>
	/// Remove a tile to render on the map
	/// </summary>
	void RemoveTile(int x, int y);
	/// <summary>
	/// Set the list of tiles to render on the map
	/// </summary>
	void SetTiles(TileData* tiles, int amount);
	/// <summary>
	/// Set the list of tiles to render on the map
	/// </summary>
	void SetTiles(std::vector<TileData> tiles);

	/// <summary>
	/// Test for an obstruction at a position on the map
	/// </summary>
	bool Collision(int x, int y);

	/// <summary>
	/// Get the width of the map
	/// </summary>
	int Width() const;
	/// <summary>
	/// Get the height of the map
	/// </summary>
	int Height() const;
	/// <summary>
	/// Get all of the tiles on the map
	/// </summary>
	std::vector<TileData> GetTiles();
	/// <summary>
	/// Get the type of tile at a position on the map
	/// </summary>
	TileTypes GetTileType(int x, int y);

	/// <summary>
	/// Call all the functions for drawing the map
	/// </summary>
	void Draw();
	/// <summary>
	/// Draw the borders of the map
	/// </summary>
	void DrawBorders() const;
	/// <summary>
	/// Draw the tiles on the map
	/// </summary>
	void DrawTiles() const;
	/// <summary>
	/// Clear all of the tiles rendered on the map
	/// </summary>
	void ClearDraw() const;

private:

	int width;
	int height;

	std::vector<TileData> tiles;
	std::map<int, TileData> tilePositions;
};

