#pragma once

#include <vector>
#include <fstream>
#include <algorithm>

class WorldGenerator {
public:
	WorldGenerator(int cells, int size, int seed);
	void runAll(); // run everything 
	void generateGrid(); // "color" in the grid
	void outputData(); // create output file

private:
	int seed; // used for random number generation
	int _cells, _size; // number of cells, width/height of world (square)
	std::vector<int> px, py; // points for the cells (x and y coords)
	std::vector<int> color; // "color" of the cell (says which region it's in during generation)
	std::vector<std::vector<int>> grid; // stores the "color" of each cell in the world
	std::vector<std::vector<bool>> vis; // visited array for floodfill
	std::pair<int, int> minCoord, maxCoord; // used for floodfill (finding boundaries of each region)

	int dist(int x1, int x2, int y1, int y2); // find Manhattan Distance
	void findBounds(int i, int j, int c); // floodfill for finding each region
};

