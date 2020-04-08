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
}

WorldGenerator::~WorldGenerator() {
	delete grid;
	delete vis;
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
	PerlinNoise pn("../extra/perm.txt"); // TODO: generate permutation randomly
	int cnt = 0;
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
			fout << minCoord.first << " " << minCoord.second << std::endl;
			fout << maxCoord.first << " " << maxCoord.second << std::endl;
			for (int x = minCoord.first; x <= maxCoord.first; x++) {
				for (int y = minCoord.second; y <= maxCoord.second; y++) {
					if (grid->at(x).at(y) != grid->at(i).at(j)) fout << -1 << " ";
					else {
						double n = pn.noise((double)x / 100, (double)y / 100, (double)cnt+6.9420);
						n += sqrt(0.5);
						n /= 2.f * sqrt(0.5);
						n *= 29;
						fout << (int)n << " ";
						//fout << (int)(rand() % 29) << " ";
					}
				}
				fout << endl;
			}
			cnt++;
			fout.close();
		}
	}
}

vector<vector<int>> WorldGenerator::sampleRegion() {
	PerlinNoise pn("../extra/perm.txt");
	vector<vector<int>> map(100, vector<int>(100));
	for (int i = 0; i < 100; i++) {
		for (int j = 0; j < 100; j++) {
			double n = pn.noise((double)i/100, (double)j/100, 6.9420);
			n += sqrt(0.5);
			n /= 2.f * sqrt(0.5);
			n *= 29;
			map[i][j] = (int)n;
		}
	}
	return map;
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
		if (vis->at(ni).at(nj)) continue;
		if (grid->at(ni).at(nj) != c) continue;
		findBounds(ni, nj, c);
	}
}