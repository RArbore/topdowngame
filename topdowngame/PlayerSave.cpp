#include "PlayerSave.h"

PlayerSave::PlayerSave() {
	for (int i = 0; i < 35; i++) {
		inventory.push_back(NULL);
	}
	baseStats[0] = 100;
	baseStats[1] = 1;
	baseStats[2] = 1;
	baseStats[3] = 2;
}

PlayerSave::~PlayerSave() {
	for (auto item : inventory) {
		delete item;
	}
}