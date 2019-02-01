#pragma once

#include "Treasure.h"

struct Treasure
{
	int x;
	int y;
	int value;

	Treasure(int x, int y, int value)
	{
		this->x = x;
		this->y = y;
		this->value = value;
	}
};