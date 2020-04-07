#include "Slime.h"

Slime::Slime(GameEnvironment* gameEnvironment, double x, double y, TileMap* tileMap, vector<Entity*>* entityList, map<string, bool>* keys, ResourceManager* resourceManager) : //Add pointer to hashmap for input keys
Entity::Entity(x, y, tileMap, entityList, resourceManager),
vel(0.f, 0.f),
acc(0.f, 0.f)
{
	this->gameEnvironment = gameEnvironment;
	this->loadAnimations();

	h.w = 16;
	h.h = 16;
	movementSpeed = 0.5f;
	health = 100;
	maxHealth = 100;
	attackDelayCounter = 0;
	setAnimationIndex(0);
}

void Slime::loadAnimations() {
	sf::Texture* tex = resourceManager->getTexture("slime_entity");

	Animation* a = new Animation(2);
	for (int i = 0; i < 2; i++) {
		a->editFrame(i, tex);
		a->editCoords(i, sf::IntRect(0, i*16, 16, 16));
		a->editDelay(i, 1e9);
	}
	this->pushAnimation(a);

	Animation* b = new Animation(3);
	for (int i = 0; i < 2; i++) {
		b->editFrame(i, tex);
		b->editCoords(i, sf::IntRect(0, i*16+32, 16, 16));
		b->editDelay(i, 1e9);
	}
	this->pushAnimation(b);

	Animation* c = new Animation(1);
	for (int i = 0; i < 2; i++) {
		c->editFrame(i, tex);
		c->editCoords(i, sf::IntRect(0, i*16+80, 16, 16));
		c->editDelay(i, 1e9);
	}
	this->pushAnimation(c);
}

void Slime::tick(double dt) {
	if (target == NULL) {
		target = gameEnvironment->focusEntity;
	}

	attackDelayCounter += dt;

	movement(dt);

	this->playCurrentAnimation(dt);
}

void Slime::movement(double dt) {
	double mv = dt * movementSpeed;

	double dx = target->h.getCX() - h.getCX();
	double dy = target->h.getCY() - h.getCY();
	double distance = sqrt(dx * dx + dy * dy);

	h.x += dx / distance * mv;
	h.y += dy / distance * mv;
}

void Slime::render(sf::RenderWindow* window) {
	Entity::render(window);
}