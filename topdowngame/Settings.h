#pragma once

#include <map>
#include <string>

using namespace std;

struct Settings {

	map<string, int> keyBindings = { 
		{"Move Up", 22}, 
		{"Move Left", 0}, 
		{"Move Down", 18}, 
		{"Move Right", 3},
		{"Inventory", 17},
		{"Debug", 87},
		{"Slot 1", 27},
		{"Slot 2", 28},
		{"Slot 3", 29},
		{"Slot 4", 30},
		{"Slot 5", 31},
		{"Slot 6", 32},
		{"Slot 7", 33},
		{"Slot 8", 34},
		{"Slot 9", 35},
	};

};