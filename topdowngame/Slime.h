#pragma once

#include "Entity.h"
#include "Environment.h"
#include "GameEnvironment.h"
#include <string>

using namespace std;

class GameEnvironment;

class Slime : public Entity
{

public:

	GameEnvironment* gameEnvironment;

	Slime(GameEnvironment* gameEnvironment, double x, double y, TileMap* tileMap, vector<Entity*>* entityList, map<string, bool>* keys, ResourceManager* resourceManager);

	void tick(double dt);	
	void render(sf::RenderWindow* window);
	void movement(double dt);

private:

	Entity* target;

	sf::Vector2f vel;
	sf::Vector2f acc;
	float movementSpeed;

	double attackDelayCounter;

	void loadAnimations();

};

