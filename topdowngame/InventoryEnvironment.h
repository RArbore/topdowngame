#pragma once

#include "Environment.h"
#include "GameEnvironment.h"
#include "Item.h"

class InventoryEnvironment : public Environment
{

public:

	int counter;

	int selectedSlot;

	int heldSlot;

	bool releasedR;

	bool releasedMouse;

	Environment* background;

	sf::Font font;

	void tick(double dt);
	void render(double dt);

	void eventHandler(sf::Event& event);

	InventoryEnvironment(sf::RenderWindow* window, Settings* settings, string* transitionEnvironment, Environment* background, PlayerSave* playerSave);
	~InventoryEnvironment();

};

