#include "Entity.h"

Entity::Entity(double x, double y, TileMap* tileMap, vector<Entity*>* entityList):
h(0, 0, 0, 0)
{
	h.x = x;
	h.y = y;
	this->tileMap = tileMap;
	this->entityList = entityList;
}

void Entity::tick() {
	sprite.setPosition((float)h.x, (float)h.y);
}

void Entity::render(sf::RenderWindow* window) {
	sprite.setTexture(*mainAnimation.getCurrentFrame());
	window->draw(sprite);
}