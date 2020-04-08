#pragma once

#include<stdlib.h>
#include<stdio.h>
#include<math.h>
#include<string>
#include <fstream>
#include <iostream>
#include <vector>
using namespace std;

class PerlinNoise {
public:
	PerlinNoise(const char* fileName); // load file with 256 ints in range [0, 255]
	double noise(double x, double y, double z);

private:
	vector<int> p;

	double fade(double t);
	double lerp(double t, double a, double b);
	double grad(int hash, double x, double y, double z);
};