#include "Entity.h"

Entity::Entity(double x, double y, TileMap* tileMap, vector<Entity*>* entityList, ResourceManager* resourceManager):
h(0, 0, 0, 0)
{
	h.x = x;
	h.y = y;
	this->tileMap = tileMap;
	this->entityList = entityList;
	this->resourceManager = resourceManager;
}

void Entity::tick() {
	sprite.setPosition((float)h.x, (float)h.y);
}

void Entity::render(sf::RenderWindow* window) {
	sprite.setTexture(*(mainAnimation.getCurrentFrame()));
	sprite.setTextureRect(mainAnimation.getCurrentCoords());
	window->draw(sprite);
}