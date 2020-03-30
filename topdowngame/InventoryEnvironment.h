#pragma once
#include "Environment.h"
class InventoryEnvironment : public Environment
{

public:

	void tick();
	void render();

	void eventHandler(sf::Event& event);

	InventoryEnvironment(sf::RenderWindow* window, Settings* settings, string* transitionEnvironment);
	~InventoryEnvironment();

};

