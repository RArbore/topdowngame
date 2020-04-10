#pragma once

#include <vector>

#include <SFML/Graphics.hpp>

#include "Tile.h"

class TileMap : public sf::Drawable, public sf::Transformable {
public:
	TileMap(std::vector<std::vector<int>>& mapDefinition, sf::Texture* tileset);
	// TODO: implement an offset so we can use multiple tilemaps (one for each region)

	~TileMap();

private:
	std::map<std::pair<int, int>, Tile*> tiles; 
	sf::Texture* tileset; // texture of all the tile sprites

	sf::VertexArray vertices;

	// note: sprites stored in rows of 16 
	void loadMapDefinition(std::vector<std::vector<int>>& mapDefintion);
	void loadVertexArray();

	// use window.draw(TileMap object) in render loop
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};

