#pragma once

#include "Entity.h"
#include "Coin.h"
#include "Environment.h"
#include "GameEnvironment.h"
#include <string>
#include <stdio.h>

using namespace std;

class GameEnvironment;

class Minotaur : public Entity
{

public:

	double counter;

	GameEnvironment* gameEnvironment;

	Minotaur(GameEnvironment* gameEnvironment, double x, double y, TileMap* tileMap);

	void tick(double dt);	
	void render(sf::RenderWindow* window);
	void movement(double dt);

	bool damage(double damage);

private:

	Entity* target;

	double vx;
	double vy;

	float movementSpeed;

	double attackTimer;

	int attackType;

	int animOffset;

	void loadAnimations();

};

