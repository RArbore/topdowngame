#include <map>
#include <string>

using namespace std;

struct Settings {

	map<string, int> keyBindings = { 
		{"Move Up", 22}, 
		{"Move Left", 0}, 
		{"Move Down", 18}, 
		{"Move Right", 3} };

};