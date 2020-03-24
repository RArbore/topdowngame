#pragma once
#include "Entity.h"
class Player : public Entity
{

public:

	Player(double x, double y, TileMap* map, vector<Entity*>* entityList);

	void tick();

};

