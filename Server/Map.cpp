#include "Map.h"

#include <time.h>
#include <iostream>
#include <Windows.h>

Map::Map(int width, int height, int maxTreasure)
{
	this->width = width;
	this->height = height;

	PlaceTreasure(rand() % maxTreasure + 1);
}

Map::~Map()
{
	treasures.clear();
}

uint8_t Map::Width()
{
	return width;
}

uint8_t Map::Height()
{
	return height;
}

std::vector<Treasure*> Map::GetTreasures() const
{
	return treasures;
}

void Map::PlaceTreasure(int maxTreasure)
{
	bool* occupied = static_cast<bool*>(malloc(sizeof(bool) * width * height));

	for (int i = 0; i < width*height; i++)
	{
		occupied[i] = false;
	}

	for (int i = 0; i < maxTreasure; ++i)
	{
		Treasure* newTreasure = new Treasure(rand() % width, rand() % height, rand() % 5);

		while (*(occupied + newTreasure->y*width + newTreasure->x))
		{
			newTreasure->x++;

			if (newTreasure->x >= width)
			{
				newTreasure->x = 0;
				newTreasure->y++;

				if (newTreasure->y >= height)
				{
					newTreasure->y = 0;
				}
			}
		}

		treasures.push_back(newTreasure);
		*(occupied + newTreasure->y*width + newTreasure->x) = true;
	}

	free(occupied);
}

void Map::Draw()
{
	for (int y = 0; y < height + 2; ++y)
	{
		for (int x = 0; x < width + 2; ++x)
		{
			if (x == 0 || y == 0 ||
				x > width || y > height)
			{
				printf("#");
			}
			else
			{
				printf(" ");
			}
		}
		printf("\n");
	}

	for (int i = 0; i < static_cast<int>(treasures.size()); ++i)
	{
		COORD cord = { static_cast<SHORT>(treasures[i]->x + 1), static_cast<SHORT>(treasures[i]->y + 1) };
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cord);
		printf("!");
	}
}