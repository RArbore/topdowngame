#include "Coin.h"

Coin::Coin(GameEnvironment* gameEnvironment, double x, double y, TileMap* tileMap, ResourceManager* resourceManager) : //Add pointer to hashmap for input keys
Entity::Entity(x, y, tileMap, resourceManager)
{
	this->gameEnvironment = gameEnvironment;
	this->loadAnimations();

	h.w = 6;
	h.h = 7;
	setAnimationIndex(0);
	counter = 0;
}

void Coin::loadAnimations() {
	sf::Texture* tex = resourceManager->getTexture("coin_entity");

	Animation* a = new Animation(4);
	for (int i = 0; i < 4; i++) {
		a->editFrame(i, tex);
		a->editCoords(i, sf::IntRect(0, i*7, 6, 7));
		a->editDelay(i, 15);
	}
	this->pushAnimation(a);
}

void Coin::tick(double dt) {
	this->playCurrentAnimation(dt);
	counter += dt;
}

void Coin::render(sf::RenderWindow* window) {
	Entity::render(window);
}