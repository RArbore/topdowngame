#include "Entity.h"
#include <string>
#include <map>

using namespace std;

class Player : public Entity
{

public:

	map<string, bool>* keys;

	Player(double x, double y, TileMap* tileMap, vector<Entity*>* entityList, map<string, bool>* keys);

	void tick();

};

