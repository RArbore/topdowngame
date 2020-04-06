#pragma once

#include "Entity.h"
#include "Environment.h"
#include "GameEnvironment.h"
#include <string>
#include <map>
#include <queue>

using namespace std;

class GameEnvironment;

class Player : public Entity
{

public:

	map<string, bool>* keys;

	GameEnvironment* gameEnvironment;
	//ProjectileManager projectileManager;

	Player(GameEnvironment* gameEnvironment, double x, double y, TileMap* tileMap, vector<Entity*>* entityList, map<string, bool>* keys, ResourceManager* resourceManager);

	void tick();	
	void render(sf::RenderWindow* window);
	void movement(int keyX, int keyY);

private:
	// velocity and acceleration
	sf::Vector2f vel;
	sf::Vector2f acc;
	float movementSpeed;
	int lastDirection; // store the last direction (0-7, north going clockwise)

	int attackDelayCounter;
	queue<string> projectileQueue; 

	double mouseX, mouseY; // use these for determining what direction to move in
	double screenX, screenY; // coordinates of player on the actual screen

	void loadAnimations();
};

