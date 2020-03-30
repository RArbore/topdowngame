#include "Environment.h"

Environment::Environment(sf::RenderWindow* window, Settings* settings, string* transitionEnvironment) :
	resourceManager()
{
	this->window = window;
	this->settings = settings;
	this->transitionEnvironment = transitionEnvironment;
}
