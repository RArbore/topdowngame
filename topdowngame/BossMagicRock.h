#pragma once

#include "Entity.h"
#include "Environment.h"
#include "GameEnvironment.h"
#include "Minotaur.h"
#include "MagicRock.h"
#include <string>
#include <stdio.h>

using namespace std;

class GameEnvironment;

class BossMagicRock : public Entity
{

public:

	double counter;

	GameEnvironment* gameEnvironment;

	BossMagicRock(GameEnvironment* gameEnvironment, double x, double y, TileMap* tileMap, ResourceManager* resourceManager);

	void tick(double dt);	
	void render(sf::RenderWindow* window);
	bool damage(double damage);

private:

	int state;

	vector<Entity*> bosses;

	void loadAnimations();

};

