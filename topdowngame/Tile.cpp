#include "Tile.h"

Tile::Tile(double x, double y, double texture_x, double texture_y, int type)
{
	this->x = x;
	this->y = y;
	this->type = type;
	this->texture_x = texture_x;
	this->texture_y = texture_y;
}
