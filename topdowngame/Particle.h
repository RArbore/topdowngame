#pragma once

#include "Entity.h"
#include "Environment.h"
#include "GameEnvironment.h"
#include <string>

using namespace std;

class GameEnvironment;

class Particle : public Entity
{

public:

	double counter;

	GameEnvironment* gameEnvironment;

	Particle(GameEnvironment* gameEnvironment, double x, double y, int particleType, TileMap* tileMap, vector<Entity*>* entityList, map<string, bool>* keys, ResourceManager* resourceManager);

	void tick(double dt);	
	void render(sf::RenderWindow* window);

private:

	int particleType;

	void loadAnimations();

};

