#include "TileMap.h"

TileMap::TileMap(std::vector<std::vector<int>>& mapDefinition, sf::Texture* tileset) {
	this->tileset = tileset;
	loadMapDefinition(mapDefinition);
	loadVertexArray();
}

TileMap::~TileMap() {
	for (auto t : tiles) {
		delete t;
	}
}

void TileMap::loadMapDefinition(std::vector<std::vector<int>>& map) {
	for (int i = 0; i < map.size(); i++) {
		for (int j = 0; j < map[i].size(); j++) {
			int type = map[i][j];

			// tile coordinates
			int x = i * Tile::TILE_SIZE;
			int y = j * Tile::TILE_SIZE;

			// texture coordinates
			int tx = (type % 16) * Tile::TILE_SIZE;
			int ty = floor(type / 16);

			Tile* t = new Tile(x, y, tx, ty, type);
			tiles.push_back(t);
		}
	}
}

void TileMap::loadVertexArray() {
	// resize vertex array
	vertices.setPrimitiveType(sf::Quads);
	vertices.resize(tiles.size() * 4);

	for (int i = 0; i < tiles.size(); i++) {
		Tile* tile = tiles[i];

		// find position in texture coords
		// TODO: implement this (need to standardize texture file format)
		int tex_x = 0;
		int tex_y = 0;

		// pointer to quad in vertex array
		sf::Vertex* quad = &vertices[(size_t)i * 4];

		// define 4 corners
		quad[0].position = sf::Vector2f(tile->h.x, tile->h.y);
		quad[1].position = sf::Vector2f(tile->h.x + Tile::TILE_SIZE, tile->h.y);
		quad[2].position = sf::Vector2f(tile->h.x + Tile::TILE_SIZE, tile->h.y + Tile::TILE_SIZE);
		quad[3].position = sf::Vector2f(tile->h.x, tile->h.y + Tile::TILE_SIZE);

		// define texture coordinates
		quad[0].texCoords = sf::Vector2f(tile->texture_x, tile->texture_y);
		quad[1].texCoords = sf::Vector2f(tile->texture_x + Tile::TILE_SIZE, tile->texture_y);
		quad[2].texCoords = sf::Vector2f(tile->texture_x + Tile::TILE_SIZE, tile->texture_y + Tile::TILE_SIZE);
		quad[3].texCoords = sf::Vector2f(tile->texture_x, tile->texture_y + Tile::TILE_SIZE);
	}
}

void TileMap::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	states.transform *= getTransform();
	states.texture = tileset;
	target.draw(vertices, states);
}