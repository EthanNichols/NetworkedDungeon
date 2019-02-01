#pragma once

#include <vector>
#include "Treasure.h"

class Map
{
public:
	Map(int width, int height, int maxTreasure);
	~Map();

	void Draw();

private:
	int width;
	int height;

	void PlaceTreasure(int maxTreasure);

	std::vector<Treasure*> treasures;
};

