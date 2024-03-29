#pragma once

#include "Entity.h"
#include "Particle.h"
#include "Environment.h"
#include "GameEnvironment.h"
#include <string>
#include <stdlib.h>

using namespace std;

class GameEnvironment;

class Mushroom : public Entity
{

public:

	double counter;

	GameEnvironment* gameEnvironment;

	Mushroom(GameEnvironment* gameEnvironment, double x, double y, TileMap* tileMap);

	void tick(double dt);	
	void render(sf::RenderWindow* window);

	bool damage(double damage);

private:

	void loadAnimations();

};
