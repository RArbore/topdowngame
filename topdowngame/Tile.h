#pragma once

#include "Hitbox.h"

class Tile {
public:
	Tile(double x, double y, double texture_x, double texture_y, int type);
	static constexpr double TILE_SIZE = 16.f;

	int type;
	Hitbox h;
	double texture_x, texture_y;
private:
};

