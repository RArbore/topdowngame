#include "Hitbox.h"

Hitbox::Hitbox(double ix, double iy, double iw, double ih) {
	x = ix;
	y = iy;
	w = iw;
	h = ih;
}

double Hitbox::getCX() {
	return x + w / 2;
}

double Hitbox::getCY() {
	return y + h / 2;
}

bool Hitbox::checkCollision(double hx, double hy, double hw, double hh) {
	double x1 = x;
	double y1 = y;
	double x2 = x + w;
	double y2 = y + h;
	double x3 = hx;
	double y3 = hy;
	double x4 = hx + hw;
	double y4 = hy + hh;
	return !(x3 >= x2 || x1 >= x4 || y3 >= y2 || y1 >= y4);
}


bool Hitbox::checkCollision(Hitbox* h) {
	return checkCollision(h->x, h->y, h->w, h->h);
}

bool Hitbox::checkCollision(TileMap* map, int tileId) {
	int adjX = (int)(getCX() / 16);
	int adjY = (int)(getCY() / 16);

	int dx = std::ceil(w / 32);
	int dy = std::ceil(h / 32);

	for (int x = adjX - dx; x <= adjX + dx; x++) {
		for (int y = adjY - dy; y <= adjY + dy; y++) {
			Tile* tile = map->getTile(x, y);
			if (tile != NULL && tile->type == tileId) {
				if (checkCollision(x * Tile::TILE_SIZE, y * Tile::TILE_SIZE, Tile::TILE_SIZE, Tile::TILE_SIZE)) {
					return true;
				}
			}
		}
	}
	return false;
}

// return -2 if collision with no other region or edge of the world
// return -1 if collision with the edge of the entire world
// return region id if there is a collision with an adjacent region
int Hitbox::checkWorldEdgeCollision(TileMap* map) {
	int adjX = (int)(getCX() / 16);
	int adjY = (int)(getCY() / 16);

	int dx = std::ceil(w / 32);
	int dy = std::ceil(h / 32);

	/*
	priority in this order:
	adjacent region, world boundary, nothing
	*/
	std::vector<int> collWith;

	for (int x = adjX - dx; x <= adjX + dx; x++) {
		for (int y = adjY - dy; y <= adjY + dy; y++) {
			Tile* tile = map->getTile(x, y);

			if (tile != NULL && tile->type < 0) { // < 0 means that it is an adjacent region
				if (checkCollision(tile->x, tile->y, Tile::TILE_SIZE, Tile::TILE_SIZE)) {
					if (tile->type == -1) collWith.push_back(-1);
					else collWith.push_back(-1 * tile->type - 2);
				}
			}
		}
	}
	
	if (collWith.size() == 0) return -2;

	sort(collWith.begin(), collWith.end(), std::greater<int>());
	if (collWith[0] == -1) return -1;
	else {
		return collWith[0];
	}
}