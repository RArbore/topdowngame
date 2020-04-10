#include "WorldGenerator.h"

WorldGenerator::WorldGenerator(int cells, int size, int seed) {
	this->seed = seed;
	_cells = cells;
	_size = size;
	px.resize(_cells);
	py.resize(_cells);
	color.resize(_cells);
	this->grid = new vector<vector<int>>(_size, std::vector<int>(_size));
	this->vis = new vector<vector<bool>>(_size, std::vector<bool>(_size));
	this->vis2 = new vector<vector<bool>>(_size, vector<bool>(_size));
	adj.resize(cells + 1);
	colorToRegion.resize(cells+1);
}

WorldGenerator::~WorldGenerator() {
	delete grid;
	delete vis;
	delete vis2;
}

void WorldGenerator::runAll() {
	this->generateGrid();
	this->outputData();
}

void WorldGenerator::generateGrid() {
	srand(seed);
	int n;
	int colorCnt = 1;
	for (int i = 0; i < _cells; i++) {
		px[i] = (rand() % _size) + 1;
		py[i] = (rand() % _size) + 1;
		color[i] = colorCnt++;
	}

	for (int x = 0; x < _size; x++) {
		for (int y = 0; y < _size; y++) {
			n = 0;
			for (int i = 0; i < _cells; i++) {
				if (dist(px[i], x, py[i], y) < dist(px[n], x, py[n], y)) {
					n = i;
				}
			}
			grid->at(x).at(y) = color[n];
		}
	}
}

void WorldGenerator::outputData() {
	/*
	FORMAT OF WORLD DATA
	World Files:
		- labeled using hexadecimal string of region index - [0, _cells)
		- coords of bounding box
		- each cell either has:
			- noise value (positive value from 0 to 100)
			- -1 x (region+2) if it belongs to another region
			- -1 if it is the edge of the world
	Adjacency File:
		- number of cells (_cell)
		- each line thereafter lists all the regions it is connected to
	*/

	SimplexNoise noise;

	// generate colorToRegion for use with adjacency list (found in next set of loops)
	int cnt = 0;
	for (int i = 0; i < _size; i++) {
		for (int j = 0; j < _size; j++) {
			if (vis2->at(i).at(j)) continue;
			colorToRegion[grid->at(i).at(j)] = cnt;
			determineRegionInd(i, j, grid->at(i).at(j));
			cnt++;
		}
	}

	// output world data and create adjacency list
	cnt = 0;
	for (int i = 0; i < _size; i++) {
		for (int j = 0; j < _size; j++) {
			if (vis->at(i).at(j)) continue;
			minCoord = { 1e9, 1e9 };
			maxCoord = { -1e9, -1e9 };
			findBounds(i, j, grid->at(i).at(j));

			// output to file (named by hexadecimal string of region #)
			stringstream stream;
			stream << hex << cnt;
			string filename(stream.str());
			filename = "../world/" + filename;

			ofstream fout(filename);

			fout << cnt << std::endl;
			assert(cnt == colorToRegion[grid->at(i).at(j)]);
			fout << minCoord.first << " " << minCoord.second << std::endl;
			fout << maxCoord.first << " " << maxCoord.second << std::endl;
			for (int x = minCoord.first-1; x <= maxCoord.first+1; x++) {
				for (int y = minCoord.second-1; y <= maxCoord.second+1; y++) {
					if (x < 0 || x >= _size || y < 0 || y >= _size) { // edge of the world
						fout << -1 << " ";
						continue;
					}

					if (grid->at(x).at(y) != grid->at(i).at(j)) {
						fout << -1 * (colorToRegion[grid->at(x).at(y)]+2) << " ";
					}
					else {
						double xi = x / FEATURE_SIZE;
						double yi = y / FEATURE_SIZE;
						double n = noise.noise(xi, yi);
						n += 1.f;
						n *= 50.f;
						fout << (int)n << " ";
					}
				}
				fout << endl;
			}
			cnt++;
			fout.close();
		}
	}

	// output adjacency list
	ofstream fout("../world/adj");
	fout << _cells << endl;
	for (int i = 0; i < _cells; i++) {
		for (auto& j : adj[i]) fout << j << " ";
		fout << endl;
	}
	fout.close();
}


int WorldGenerator::dist(int x1, int x2, int y1, int y2) {
	return abs(x1 - x2) + abs(y1 - y2);
}

void WorldGenerator::findBounds(int i, int j, int c) {
	vis->at(i).at(j) = true;
	maxCoord.first = std::max(maxCoord.first, i);
	maxCoord.second = std::max(maxCoord.second, j);
	minCoord.first = std::min(minCoord.first, i);
	minCoord.second = std::min(minCoord.second, j);
	int dx[4] = { 0, 0, 1, -1 };
	int dy[4] = { 1, -1, 0, 0 };
	for (int a = 0; a < 4; a++) {
		int ni = i + dx[a];
		int nj = j + dy[a];
		if (ni < 0 || ni >= _size || nj < 0 || nj >= _size) continue;
		if (grid->at(ni).at(nj) != c) {
			adj[colorToRegion[c]].insert(colorToRegion[grid->at(ni).at(nj)]);
			adj[colorToRegion[grid->at(ni).at(nj)]].insert(colorToRegion[c]);
			continue;
		}
		if (vis->at(ni).at(nj)) continue;
		findBounds(ni, nj, c);
	}
}

void WorldGenerator::determineRegionInd(int i, int j, int c) {
	// just floodfill and visit so we know we visited these cells
	vis2->at(i).at(j) = true;
	int dx[4] = { 0, 0, 1, -1 };
	int dy[4] = { 1, -1, 0, 0 };
	for (int a = 0; a < 4; a++) {
		int ni = i + dx[a];
		int nj = j + dy[a];
		if (ni < 0 || ni >= _size || nj < 0 || nj >= _size) continue;
		if (vis2->at(ni).at(nj)) continue;
		if (grid->at(ni).at(nj) != c) continue;
		determineRegionInd(ni, nj, c);
	}
}