#pragma once

#include "TileMap.h"
#include "Tile.h"

class Hitbox
{

public:

	double x;
	double y;
	double w;
	double h;

	Hitbox(double ix, double iy, double iw, double ih);
	double getCX();
	double getCY();
	bool checkCollision(double hx, double hy, double hw, double hh);
	bool checkCollision(Hitbox* h);
	bool checkCollision(TileMap* map, int tileId);

};

