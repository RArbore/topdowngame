#pragma once

#include "Entity.h"
#include "Environment.h"
#include "GameEnvironment.h"
#include <string>

using namespace std;

class GameEnvironment;
class JungleTree;

class Particle : public Entity
{

public:

	double counter;

	int timeAlive;

	GameEnvironment* gameEnvironment;

	Particle(GameEnvironment* gameEnvironment, double x, double y, int particleType, TileMap* tileMap, ResourceManager* resourceManager);
	Particle(GameEnvironment* gameEnvironment, double x, double y, int particleType, double renderOrderOffset, TileMap* tileMap, ResourceManager* resourceManager);
	Particle(GameEnvironment* gameEnvironment, double x, double y, string visual, int timeAlive, double renderOrderOffset, TileMap* tileMap, ResourceManager* resourceManager);

	void tick(double dt);	
	void render(sf::RenderWindow* window);

private:

	int particleType;

	string visual;

	virtual void loadAnimations();

};

