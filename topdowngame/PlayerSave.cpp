#include "PlayerSave.h"

PlayerSave::PlayerSave() {
	for (int i = 0; i < 35; i++) {
		inventory.push_back(NULL);
	}
}

PlayerSave::~PlayerSave() {
	for (auto item : inventory) {
		delete item;
	}
}