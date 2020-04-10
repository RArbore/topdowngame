#pragma once

class Tile {
public:
	Tile(double x, double y, double texture_x, double texture_y, int type);
	static constexpr double TILE_SIZE = 16.f;

	double x;
	double y;

	int type;
	double texture_x, texture_y;
private:
};

