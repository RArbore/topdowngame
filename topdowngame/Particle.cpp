#include "Particle.h"

Particle::Particle(GameEnvironment* gameEnvironment, double x, double y, int particleType, TileMap* tileMap, vector<Entity*>* entityList, map<string, bool>* keys, ResourceManager* resourceManager) : //Add pointer to hashmap for input keys
Entity::Entity(x, y, tileMap, entityList, resourceManager)
{
	this->gameEnvironment = gameEnvironment;
	this->loadAnimations();

	h.w = 0;
	h.h = 0;
	health = 0;
	maxHealth = 0;
	counter = 0;
	this->particleType = particleType;
	setAnimationIndex(0);
}

void Particle::loadAnimations() {
	sf::Texture* tex = resourceManager->getTexture("particle_entity");

	Animation* a = new Animation(4);
	for (int i = 0; i < 4; i++) {
		a->editFrame(i, tex);
		a->editCoords(i, sf::IntRect(0, i*4, 4, 4));
		a->editDelay(i, 15);
	}
	this->pushAnimation(a);
}

void Particle::tick(double dt) {
	this->playCurrentAnimation(dt);
	counter += dt;
}

void Particle::render(sf::RenderWindow* window) {
	Entity::render(window);
}