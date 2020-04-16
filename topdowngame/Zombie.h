#pragma once

#include "Entity.h"
#include "Coin.h"
#include "Environment.h"
#include "GameEnvironment.h"
#include <string>

using namespace std;

class GameEnvironment;

class Zombie : public Entity
{

public:

	double counter;

	GameEnvironment* gameEnvironment;

	Zombie(GameEnvironment* gameEnvironment, double x, double y, TileMap* tileMap);

	void tick(double dt);	
	void render(sf::RenderWindow* window);
	void movement(double dt);

	bool damage(double damage);

private:

	Entity* target;

	float movementSpeed;
	int lastDirection;

	double attackTimer;

	void loadAnimations();

};

