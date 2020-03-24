#pragma once

#include <vector>

#include <SFML/Graphics.hpp>

#include "Tile.h"

class TileMap : public sf::Drawable, public sf::Transformable {
public:
	TileMap(std::vector<std::vector<int>>& mapDefinition, sf::Texture* tileset);

private:
	std::vector<Tile> tiles; 
	sf::Texture* tileset; // texture of all the tile sprites

	sf::VertexArray vertices;

	void loadMapDefinition(std::vector<std::vector<int>>& mapDefintion);
	void loadVertexArray();

	// use window.draw(TileMap object) in render loop
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};

