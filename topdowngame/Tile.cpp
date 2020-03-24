#include "Tile.h"

Tile::Tile(double x, double y, double texture_x, double texture_y, int type)
	: h(x, y, Tile::TILE_SIZE, Tile::TILE_SIZE)
{
	this->type = type;
	this->texture_x = texture_x;
	this->texture_y = texture_y;
}
