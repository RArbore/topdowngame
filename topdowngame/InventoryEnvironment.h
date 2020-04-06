#pragma once

#include "Environment.h"
#include "GameEnvironment.h"
#include "Item.h"

class InventoryEnvironment : public Environment
{

public:

	int counter;

	bool releasedR;

	Environment* background;

	void tick(double dt);
	void render();

	void eventHandler(sf::Event& event);

	InventoryEnvironment(sf::RenderWindow* window, Settings* settings, string* transitionEnvironment, Environment* background, PlayerSave* playerSave);
	~InventoryEnvironment();

};

