#pragma once

#include "Entity.h"
#include "Coin.h"
#include "Environment.h"
#include "GameEnvironment.h"
#include <string>

using namespace std;

class GameEnvironment;

class Slime : public Entity
{

public:

	double counter;

	GameEnvironment* gameEnvironment;

	Slime(GameEnvironment* gameEnvironment, double x, double y, TileMap* tileMap);

	void tick(double dt);	
	void render(sf::RenderWindow* window);
	void movement(double dt);

	bool damage(double damage);

private:

	Entity* target;

	sf::Vector2f vel;
	sf::Vector2f acc;
	float movementSpeed;

	double hurtTimer;

	double attackTimer;

	double attackDelayCounter;

	void loadAnimations();

};

