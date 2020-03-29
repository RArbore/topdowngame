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

void Entity::render(sf::RenderWindow* window) {
	sprite.setTexture(*(mainAnimation.getCurrentFrame()));
	sprite.setTextureRect(mainAnimation.getCurrentCoords());
	sf::IntRect textureCoords = mainAnimation.getCurrentCoords();
	sprite.setPosition(h.getCX() - float(textureCoords.width) / 2.f, h.getCY() - float(textureCoords.height) / 2.f);
	window->draw(sprite);
}