#include "TileMap.h"

TileMap::TileMap(std::vector<std::vector<int>>& mapDefinition, sf::Texture* tileset) {
	this->tileset = tileset;
	loadMapDefinition(mapDefinition);
	loadVertexArray();
}

TileMap::~TileMap() {
	for (std::pair<std::pair<int, int>, Tile*> t : tiles) {
		delete t.second;
	}
}

Tile* TileMap::getTile(int x, int y) {
	if (tiles.count(std::pair<int, int>(x, y))) {
		return tiles.at(std::pair<int, int>(x, y));
	}
	return NULL;
}

void TileMap::loadMapDefinition(std::vector<std::vector<int>>& map) {
	for (int i = 0; i < map.size(); i++) {
		for (int j = 0; j < map[i].size(); j++) {
			int noise = map[i][j];

			int type = 0;
			if (noise == -1) type = -1;

			// Map from [0, 100] to type (index of the sprite)
			if (noise >= 0 && noise < 10) type = 12;
			if (noise >= 10 && noise < 15) type = 8;
			if (noise >= 15 && noise < 18.33) type = 13;
			if (noise >= 18.33 && noise < 21.67) type = 14;
			if (noise >= 21.67 && noise < 25) type = 15;
			if (noise >= 25 && noise < 50) type = 0;
			if (noise >= 50 && noise < 75) type = 6;
			if (noise >= 75) type = 7;

			// tile coordinates
			int x = i * (int)Tile::TILE_SIZE;
			int y = j * (int)Tile::TILE_SIZE;

			// texture coordinates
			int tx, ty;
			if (type != -1) {
				tx = (type % 16) * (int)Tile::TILE_SIZE;
				ty = ((int)floor(type / 16) * Tile::TILE_SIZE) + Tile::TILE_SIZE;
			}
			else {
				tx = 0, ty = 0;
			}

			Tile* t = new Tile(x, y, tx, ty, type);
			this->tiles.insert(std::pair<std::pair<int, int>, Tile*>(std::pair<int, int>(i, j), t));
		}
	}
}

void TileMap::loadVertexArray() {
	// resize vertex array
	vertices.setPrimitiveType(sf::Quads);
	vertices.resize(tiles.size() * 4);

	int i = 0;

	for (std::pair<std::pair<int, int>, Tile*> t : tiles) {
		Tile* tile = t.second;

		// find position in texture coords
		// TODO: implement this (need to standardize texture file format)
		int tex_x = 0;
		int tex_y = 0;

		// pointer to quad in vertex array
		sf::Vertex* quad = &vertices[(size_t)i * 4];

		// define 4 corners
		quad[0].position = sf::Vector2f((float)tile->x, (float)tile->y);
		quad[1].position = sf::Vector2f((float)(tile->x + Tile::TILE_SIZE), (float)tile->y);
		quad[2].position = sf::Vector2f((float)(tile->x + Tile::TILE_SIZE), (float)(tile->y + Tile::TILE_SIZE));
		quad[3].position = sf::Vector2f((float)(tile->x), (float)(tile->y + Tile::TILE_SIZE));

		// define texture coordinates
		quad[0].texCoords = sf::Vector2f((float)(tile->texture_x), (float)(tile->texture_y));
		quad[1].texCoords = sf::Vector2f((float)(tile->texture_x + Tile::TILE_SIZE), (float)tile->texture_y);
		quad[2].texCoords = sf::Vector2f((float)(tile->texture_x + Tile::TILE_SIZE), (float)(tile->texture_y + Tile::TILE_SIZE));
		quad[3].texCoords = sf::Vector2f((float)tile->texture_x, (float)(tile->texture_y + Tile::TILE_SIZE));
		i++;
	}
}

void TileMap::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	states.transform *= getTransform();
	states.texture = tileset;
	target.draw(vertices, states);
}