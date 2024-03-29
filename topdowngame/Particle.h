#pragma once

#include "Entity.h"
#include "Environment.h"
#include "GameEnvironment.h"
#include <string>
#include <stdlib.h>

using namespace std;

class GameEnvironment;
class JungleTree;

class Particle : public Entity
{

public:

	double counter;

	int timeAlive;

	GameEnvironment* gameEnvironment;

	Particle(GameEnvironment* gameEnvironment, double x, double y, int particleType, TileMap* tileMap);
	Particle(GameEnvironment* gameEnvironment, double x, double y, int particleType, double renderOrderOffset, TileMap* tileMap);
	Particle(GameEnvironment* gameEnvironment, double x, double y, string visual, int timeAlive, double renderOrderOffset, TileMap* tileMap);

	void tick(double dt);	
	void render(sf::RenderWindow* window);

private:

	int particleType;

	string visual;

	virtual void loadAnimations();

};

