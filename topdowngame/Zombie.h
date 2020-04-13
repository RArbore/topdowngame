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

	Zombie(GameEnvironment* gameEnvironment, double x, double y, TileMap* tileMap, ResourceManager* resourceManager);

	void tick(double dt);	
	void render(sf::RenderWindow* window);
	void movement(double dt);

	bool damage(double damage);

private:

	Entity* target;

	sf::Vector2f vel;
	sf::Vector2f acc;
	float movementSpeed;
	int lastDirection;

	double attackTimer;

	double attackDelayCounter;

	void loadAnimations();

};

