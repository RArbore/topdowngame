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
	// return -2 if collision with no other region or edge of the world
	// return -1 if collision with the edge of the entire world
	// return region id if there is a collision with an adjacent region
	int checkWorldEdgeCollision(TileMap* map); 
};

