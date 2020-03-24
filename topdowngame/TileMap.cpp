#include "TileMap.h"

TileMap::TileMap(std::vector<std::vector<int>>& mapDefinition, sf::Texture* tileset) {
	this->tileset = tileset;
	loadMapDefinition(mapDefinition);
	loadVertexArray();
}

void TileMap::loadMapDefinition(std::vector<std::vector<int>>& mapDefinition) {
	// TODO: implement based on how the map is going to be passed in
}

void TileMap::loadVertexArray() {
	// resize vertex array
	vertices.setPrimitiveType(sf::Quads);
	vertices.resize(tiles.size() * 4);

	for (int i = 0; i < tiles.size(); i++) {
		Tile& tile = tiles[i];

		// find position in texture coords
		// TODO: implement this (need to standardize texture file format)
		int tex_x = 0;
		int tex_y = 0;

		// pointer to quad in vertex array
		sf::Vertex* quad = &vertices[(size_t)i * 4];

		// define 4 corners
		quad[0].position = sf::Vector2f(tile.h.x, tile.h.y);
		quad[1].position = sf::Vector2f(tile.h.x + Tile::TILE_SIZE, tile.h.y);
		quad[2].position = sf::Vector2f(tile.h.x + Tile::TILE_SIZE, tile.h.y + Tile::TILE_SIZE);
		quad[3].position = sf::Vector2f(tile.h.x, tile.h.y + Tile::TILE_SIZE);

		// define texture coordinates
		// TODO: implement this (need to standardize texture file format)
	}
}

void TileMap::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	states.transform *= getTransform();
	states.texture = tileset;
	target.draw(vertices, states);
}