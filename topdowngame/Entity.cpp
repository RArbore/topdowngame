#include "Entity.h"

Entity::Entity(double x, double y, TileMap* tileMap, vector<Entity*>* entityList, ResourceManager* resourceManager):
h(0, 0, 0, 0)
{
	h.x = x;
	h.y = y;
	this->tileMap = tileMap;
	this->entityList = entityList;
	this->resourceManager = resourceManager;
	animationIndex = 0;
}

void Entity::render(sf::RenderWindow* window) {
	Animation anim = this->getCurrentAnimation();
	sprite.setTexture(*(anim.getCurrentFrame()));
	sprite.setTextureRect(anim.getCurrentCoords());
	sf::IntRect textureCoords = anim.getCurrentCoords();
	sprite.setPosition(h.getCX() - float(textureCoords.width) / 2.f, h.getCY() - float(textureCoords.height) / 2.f);
	window->draw(sprite);
}

void Entity::pushAnimation(Animation a) {
	animations.push_back(a);
}

Animation Entity::getCurrentAnimation() {
	return animations[animationIndex];
}

void Entity::playCurrentAnimation() {
	animations[animationIndex].play();
}

void Entity::setAnimationIndex(int index) {
	if (index >= animations.size()) {
		std::cout << "ERROR: Could not set animation index due to an out of bounds error." << std::endl;
		return;
	}
	animationIndex = index;
}