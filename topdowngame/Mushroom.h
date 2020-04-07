#pragma once

#include "Entity.h"
#include "Environment.h"
#include "GameEnvironment.h"
#include <string>

using namespace std;

class GameEnvironment;

class Mushroom : public Entity
{

public:

	double counter;

	GameEnvironment* gameEnvironment;

	Mushroom(GameEnvironment* gameEnvironment, double x, double y, TileMap* tileMap, vector<Entity*>* entityList, map<string, bool>* keys, ResourceManager* resourceManager);

	void tick(double dt);	
	void render(sf::RenderWindow* window);

private:

	void loadAnimations();

};
