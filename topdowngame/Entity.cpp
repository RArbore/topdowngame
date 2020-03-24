#include "Entity.h"

Entity::Entity(double x, double y): // Add map pointer to constructor
h(0, 0, 0, 0)
{
	h.x = x;
	h.y = y;
}

void Entity::tick() {
	sprite.setPosition(h.x, h.y);
}

void Entity::render(sf::RenderWindow& window) {
	sprite.setTexture(*mainAnimation.getCurrentFrame());
	window.draw(sprite);
}