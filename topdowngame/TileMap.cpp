#include "TileMap.h"

TileMap::TileMap() {}

void TileMap::resetTileMap(int index, sf::Texture* tileset) {
	this->tileset = tileset;
	for (auto& t : tiles) delete t.second;
	this->tiles.clear();
	loadRegion(index);
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

void TileMap::loadRegion(int index) {
	// load world data file
	stringstream stream;
	stream << hex << index;
	string filename(stream.str());
	filename = "../world/" + filename;

	cout << "Loading region " << index << " from " << filename << endl;
	ifstream fin(filename);
	int expectedIndex, x1, y1, x2, y2; // use expected index as a way to assert that the region is correct
	// coordinates of upper left and lower right bounds of the region (in the world)
	fin >> expectedIndex >> x1 >> y1 >> x2 >> y2;

	assert(expectedIndex == index);

	// +1 + 2 because there is an extra layer on each side for the purpose
	// of knowing which regions are adjacent to it
	// mapDefinition.resize((size_t)x2 - x1 + 3, vector<int>((size_t)y2 - y1 + 3));
	vector<vector<int>> map(x2 - x1 + 3, vector<int>(y2 - y1 + 3));

	for (int i = 0; i <= x2 - x1 + 2; i++) {
		for (int j = 0; j <= y2 - y1 + 2; j++) {
			fin >> map[i][j];
		}
	}

	fin.close();

	// create tile map from map definition
	for (int i = 0; i < map.size(); i++) {
		for (int j = 0; j < map[i].size(); j++) {
			int noise = map[i][j];

			int type = 0;
			// note this is -1 x (regionId+2)
			if (noise < 0) type = noise;

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
			// subtract 1 from i and j since there are a layer of tiles
			// for the purpose of detecting adjacent regions
			int x = (i - 1) * (int)Tile::TILE_SIZE;
			int y = (j - 1) * (int)Tile::TILE_SIZE;

			// texture coordinates
			int tx, ty;
			if (type >= 0) {
				tx = (type % 16) * (int)Tile::TILE_SIZE;
				ty = ((int)floor(type / 16) * Tile::TILE_SIZE) + Tile::TILE_SIZE;
			}
			else {
				tx = 0, ty = 0;
			}

			Tile* t = new Tile(x, y, tx, ty, type);
			this->tiles.insert(std::pair<std::pair<int, int>, Tile*>(std::pair<int, int>(i - 1, j - 1), t));
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