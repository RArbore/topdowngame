#pragma once

#include <iostream>
#include <vector>
#include <iomanip>
#include <sstream>
#include <fstream>
#include <assert.h>

#include <SFML/Graphics.hpp>

#include "Tile.h"

using namespace std;

class TileMap : public sf::Drawable, public sf::Transformable {
public:
	TileMap();
	// TODO: implement an offset so we can use multiple tilemaps (one for each region)

	~TileMap();

	Tile* getTile(int x, int y);

	std::map<std::pair<int, int>, Tile*> tiles;
	
	void resetTileMap(int index, sf::Texture* tileset);

private:
	sf::Texture* tileset; // texture of all the tile sprites

	sf::VertexArray vertices;

	// note: sprites stored in rows of 16 
	void loadVertexArray();

	// use window.draw(TileMap object) in render loop
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	void loadRegion(int index);
};

