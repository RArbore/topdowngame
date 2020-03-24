#include "Environment.h"
#include "Entity.h"
#include "Player.h"
#include <vector>

using namespace std;

class GameEnvironment : public Environment
{
	
public:

	vector<Entity*> entities;

	Entity* focusEntity;

	TileMap tileMap;

	void tick();
	void render();

	vector<vector<int>>& generateMap();
	sf::Texture* getTileset();

	GameEnvironment();

};

