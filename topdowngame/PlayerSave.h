#pragma once

#include "Item.h"

#include <vector>

class PlayerSave
{

public:

	vector<Item*> inventory; //0-4: Accessories   5-7: Armor   8-16: Hotbar   17-34: Inventory

	int playerXP;

	int baseStats[4]; //HP, Attack, Defense, Speed

	PlayerSave();

	~PlayerSave();

};

