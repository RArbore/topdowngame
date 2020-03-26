#ifndef Settings_HEADER
#define Settings_HEADER

#include <map>
#include <string>

using namespace std;

class Settings {

public:

	Settings();

	map<string, int> keyBindings = { 
		{"Move Up", 22}, 
		{"Move Left", 0}, 
		{"Move Down", 18}, 
		{"Move Right", 3} };

};

#endif