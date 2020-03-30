#include "InventoryEnvironment.h"

InventoryEnvironment::InventoryEnvironment(sf::RenderWindow* window, Settings* settings, string* transitionEnvironment, Environment* background) :
	Environment(window, settings, transitionEnvironment)
{
	this->background = background;
	counter = 0;
	releasedR = false;
}

InventoryEnvironment::~InventoryEnvironment() {

}

void InventoryEnvironment::tick() {
	counter++;
}

void InventoryEnvironment::render() {
	background->render();
	window->setView(window->getDefaultView());

	sf::Vector2u size = window->getSize();

	sf::RectangleShape shade(sf::Vector2f(float(size.x), float(size.y)));
	shade.setPosition(sf::Vector2f(0, 0));
	shade.setFillColor(sf::Color(0, 0, 0, 100));

	window->draw(shade);
}

void InventoryEnvironment::eventHandler(sf::Event& event) {
	if (event.type == sf::Event::KeyPressed) {
		if (event.key.code == settings->keyBindings.at("Inventory") && releasedR) {
			*transitionEnvironment = "Game Environment";
			releasedR = false;
		}
	}
	else if (event.type == sf::Event::KeyReleased) {
		if (event.key.code == settings->keyBindings.at("Inventory")) {
			releasedR = true;
		}
	}
}