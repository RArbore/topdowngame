#include "Entity.h"

Entity::Entity(double x, double y, TileMap* map, vector<Entity>* entityList):
h(0, 0, 0, 0)
{
	h.x = x;
	h.y = y;
	this->map = map;
	this->entityList = entityList;
}

void Entity::tick() {
	sprite.setPosition(h.x, h.y);
}

void Entity::render(sf::RenderWindow& window) {
	sprite.setTexture(*mainAnimation.getCurrentFrame());
	window.draw(sprite);
}