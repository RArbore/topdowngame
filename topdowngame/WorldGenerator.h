#pragma once

#include <vector>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <iomanip>
#include <sstream>
#include <set>
#include <assert.h>

#include "SimplexNoise.h"

using namespace std;

struct AdjInfo {
	int left, right;
	int top, bottom;
};

class WorldGenerator {
public:
	WorldGenerator(int cells, int size, int seed);
	~WorldGenerator();
	void runAll(); // run everything 
	void generateGrid(); // "color" in the grid
	void outputData(); // create output file

	static constexpr double FEATURE_SIZE = 48.f;

private:
	int seed; // used for random number generation
	int _cells, _size; // number of cells, width/height of world (square)
	vector<int> px, py; // points for the cells (x and y coords)
	vector<int> color; // "color" of the cell (says which region it's in during generation)
	vector<vector<int>>* grid; // stores the "color" of each cell in the world
	vector<int> colorToRegion; // map the color to the region index
	vector<vector<bool>>* vis, *vis2; // visited array for floodfill
	pair<int, int> minCoord, maxCoord; // used for floodfill (finding boundaries of each region)
	vector<set<int>> adj; // adjacency matrix of regions


	int dist(int x1, int x2, int y1, int y2); // find Manhattan Distance
	void findBounds(int i, int j, int c); // floodfill for finding each region
	void determineRegionInd(int i, int j, int c);
};

