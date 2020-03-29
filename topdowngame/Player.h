#include "Entity.h"
#include <string>
#include <map>

using namespace std;

class Player : public Entity
{

public:

	map<string, bool>* keys;

	Player(double x, double y, TileMap* tileMap, vector<Entity*>* entityList, map<string, bool>* keys, ResourceManager* resourceManager);

	void tick();	
	void render(sf::RenderWindow* window);
	void updateAnimation(int keyX, int keyY);

private:
	// velocity and acceleration
	sf::Vector2f vel;
	sf::Vector2f acc;
};

