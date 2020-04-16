#include "Environment.h"

Environment::Environment(sf::RenderWindow* window, Settings* settings, string* transitionEnvironment, PlayerSave* playerSave)
{
	this->window = window;
	this->settings = settings;
	this->transitionEnvironment = transitionEnvironment;
	this->playerSave = playerSave;
}

string Environment::debugText() {
	return "";
}
