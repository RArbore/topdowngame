#include "Environment.h"

Environment::Environment(sf::RenderWindow* window, Settings* settings) :
	resourceManager()
{
	this->window = window;
	this->settings = settings;
}
