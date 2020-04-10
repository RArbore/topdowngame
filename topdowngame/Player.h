#pragma once

#include "Entity.h"
#include "Environment.h"
#include "GameEnvironment.h"
#include <stdlib.h>
#include <string>
#include <map>
#include <queue>

using namespace std;

class GameEnvironment;

class Player : public Entity
{

public:

	map<string, bool>* keys;

	GameEnvironment* gameEnvironment;
	//ProjectileManager projectileManager;

	Player(GameEnvironment* gameEnvironment, double x, double y, TileMap* tileMap, vector<Entity*>* entityList, map<string, bool>* keys, ResourceManager* resourceManager);

	void tick(double dt);	
	void render(sf::RenderWindow* window);
	void movement(int keyX, int keyY, double dt);

private:
	// velocity and acceleration
	sf::Vector2f vel;
	sf::Vector2f acc;
	float movementSpeed;
	int lastDirection; // store the last direction (0-7, north going clockwise)
	int animationIndexOffset;
	double useDelayCounter; 
	Item* useItem;
	
	// used for sword attacks
	// currentAttackAngle - current angle rotation 
	// endAttackAngle - angle for when to stop the animation (and stop attacking)
	bool isSwordAttacking;
	double currentAttackAngle;
	double endAttackAngle;
	double swordAttackSpeed;
	map<Entity*, bool> alreadyHit;

	double mouseX, mouseY; // use these for determining what direction to move in
	double screenX, screenY; // coordinates of player on the actual screen

	void loadAnimations();
};

