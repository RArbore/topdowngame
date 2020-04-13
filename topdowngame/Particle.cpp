#include "Particle.h"

Particle::Particle(GameEnvironment* gameEnvironment, double x, double y, int particleType, TileMap* tileMap, ResourceManager* resourceManager) :
Entity::Entity(x, y, tileMap, resourceManager)
{
	this->gameEnvironment = gameEnvironment;
	this->particleType = particleType;
	this->loadAnimations();

	h.w = 0;
	h.h = 0;
	health = 0;
	maxHealth = 0;
	counter = 0;
	timeAlive = 60;
	setAnimationIndex(0);
}

Particle::Particle(GameEnvironment* gameEnvironment, double x, double y, int particleType, double renderOrderOffset, TileMap* tileMap, ResourceManager* resourceManager) :
Entity::Entity(x, y, tileMap, resourceManager)
{
	this->gameEnvironment = gameEnvironment;
	this->particleType = particleType;
	this->loadAnimations();

	h.w = 0;
	h.h = 0;
	health = 0;
	maxHealth = 0;
	counter = 0;
	timeAlive = 60;
	setAnimationIndex(0);
	this->renderOrderOffset = renderOrderOffset;
}

Particle::Particle(GameEnvironment* gameEnvironment, double x, double y, string visual, int timeAlive, double renderOrderOffset, TileMap* tileMap, ResourceManager* resourceManager) :
Entity::Entity(x, y, tileMap, resourceManager)
{
	this->gameEnvironment = gameEnvironment;
	this->visual = visual;
	this->loadAnimations();

	h.w = 0;
	h.h = 0;
	health = 0;
	maxHealth = 0;
	counter = 0;
	this->timeAlive = timeAlive;
	setAnimationIndex(0);
	this->renderOrderOffset = renderOrderOffset;
}

void Particle::loadAnimations() {
	if (visual == "") {
		sf::Texture* tex = resourceManager->getTexture("particle_entity");

		Animation* a = new Animation(4);
		for (int i = 0; i < 4; i++) {
			a->editFrame(i, tex);
			a->editCoords(i, sf::IntRect(4 * particleType, i * 4, 4, 4));
			a->editDelay(i, 15);
		}
		this->pushAnimation(a);
	}
	else {
		sf::Texture* tex = resourceManager->getTexture(visual);
		Animation* a = new Animation(1);
		a->editFrame(0, tex);
		a->editCoords(0, sf::IntRect(0, 0, 80, 176));
		a->editDelay(0, 1e9);
		this->pushAnimation(a);
	}
}

void Particle::tick(double dt) {
	this->playCurrentAnimation(dt);
	counter += dt;
}

void Particle::render(sf::RenderWindow* window) {
	Entity::render(window);
}

