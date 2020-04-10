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
	health = 0;
	maxHealth = 0;
	renderOrderOffset = 0;
}

Entity::~Entity() {
	for (auto a : animations) delete a;
}

void Entity::render(sf::RenderWindow* window) {
	Animation* anim = this->getCurrentAnimation();
	sprite.setTexture(*(anim->getCurrentFrame()));
	sprite.setTextureRect(anim->getCurrentCoords());
	sf::IntRect textureCoords = anim->getCurrentCoords();
	sprite.setPosition(h.getCX() - float(textureCoords.width) / 2.f, h.getCY() - float(textureCoords.height) / 2.f);
	window->draw(sprite);
}

void Entity::pushAnimation(Animation* a) {
	animations.push_back(a);
}

Animation* Entity::getCurrentAnimation() {
	return animations[animationIndex];
}

void Entity::playCurrentAnimation(double dt) {
	animations[animationIndex]->play(dt);
}

void Entity::setAnimationIndex(int index) {
	if (index >= animations.size()) {	
		std::cout << "ERROR: Could not set animation index due to an out of bounds error." << std::endl;
		return;
	}
	animationIndex = index;
}

bool Entity::damage(double damage) {
	return false;
}

bool Entity::moveH(double dx, int tileId) {
	bool everTouchedWall = false;
	if (dx == 0) {
		return true;
	}
	else if (dx > 0) {
		double remainder = dx - (int)dx;
		for (int i = 0; i < (int)dx; i++) {
			h.x++;
			if (h.checkCollision(tileMap, tileId)) {
				everTouchedWall = true;
				h.x = (int)h.x;
				while (h.checkCollision(tileMap, tileId)) {
					h.x--;
				}
			}
		}
		h.x += remainder;
		if (h.checkCollision(tileMap, tileId)) {
			everTouchedWall = true;
			h.x = (int)h.x;
			while (h.checkCollision(tileMap, tileId)) {
				h.x--;
			}
		}
	}
	else {
		dx *= -1;
		double remainder = dx - (int)dx;
		for (int i = 0; i < (int)dx; i++) {
			h.x--;
			if (h.checkCollision(tileMap, tileId)) {
				everTouchedWall = true;
				h.x = (int)h.x;
				while (h.checkCollision(tileMap, tileId)) {
					h.x++;
				}
			}
		}
		h.x -= remainder;
		if (h.checkCollision(tileMap, tileId)) {
			everTouchedWall = true;
			h.x = (int)h.x;
			while (h.checkCollision(tileMap, tileId)) {
				h.x++;
			}
		}
	}

	return !everTouchedWall;
}

bool Entity::moveV(double dy, int tileId) {
	bool everTouchedWall = false;
	if (dy == 0) {
		return true;
	}
	else if (dy > 0) {
		double remainder = dy - (int)dy;
		for (int i = 0; i < (int)dy; i++) {
			h.y++;
			if (h.checkCollision(tileMap, tileId)) {
				everTouchedWall = true;
				h.y = (int)h.y;
				while (h.checkCollision(tileMap, tileId)) {
					h.y--;
				}
			}
		}
		h.y += remainder;
		if (h.checkCollision(tileMap, tileId)) {
			everTouchedWall = true;
			h.y = (int)h.y;
			while (h.checkCollision(tileMap, tileId)) {
				h.y--;
			}
		}
	}
	else {
		dy *= -1;
		double remainder = dy - (int)dy;
		for (int i = 0; i < (int)dy; i++) {
			h.y--;
			if (h.checkCollision(tileMap, tileId)) {
				everTouchedWall = true;
				h.y = (int)h.y;
				while (h.checkCollision(tileMap, tileId)) {
					h.y++;
				}
			}
		}
		h.y -= remainder;
		if (h.checkCollision(tileMap, tileId)) {
			everTouchedWall = true;
			h.y = (int)h.y;
			while (h.checkCollision(tileMap, tileId)) {
				h.y++;
			}
		}
	}

	return !everTouchedWall;
}

