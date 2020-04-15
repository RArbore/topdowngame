#pragma once

#include "Entity.h"
#include "Coin.h"
#include "Environment.h"
#include "GameEnvironment.h"
#include "Slime.h"
#include "Zombie.h"
#include "Mushroom.h"
#include <string>
#include <stdio.h>

using namespace std;

class GameEnvironment;

class MagicRock : public Entity
{

public:

	double counter;

	GameEnvironment* gameEnvironment;

	MagicRock(GameEnvironment* gameEnvironment, double x, double y, TileMap* tileMap, ResourceManager* resourceManager);

	void tick(double dt);	
	void render(sf::RenderWindow* window);
	bool damage(double damage);

private:

	int state;

	void loadAnimations();

};

