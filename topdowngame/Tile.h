#pragma once

#include "Hitbox.h"

class Tile {
public:
	Tile();
	static constexpr double TILE_SIZE = 50;

	int type;
	Hitbox h;

private:
};

