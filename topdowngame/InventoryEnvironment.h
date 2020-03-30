#pragma once
#include "Environment.h"
#include "GameEnvironment.h"
class InventoryEnvironment : public Environment
{

public:

	int counter;

	bool releasedR;

	Environment* background;

	void tick();
	void render();

	void eventHandler(sf::Event& event);

	InventoryEnvironment(sf::RenderWindow* window, Settings* settings, string* transitionEnvironment, Environment* background);
	~InventoryEnvironment();

};

