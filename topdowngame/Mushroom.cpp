#include "Mushroom.h"

Mushroom::Mushroom(GameEnvironment* gameEnvironment, double x, double y, TileMap* tileMap, vector<Entity*>* entityList, ResourceManager* resourceManager) : //Add pointer to hashmap for input keys
Entity::Entity(x, y, tileMap, entityList, resourceManager)
{
	this->gameEnvironment = gameEnvironment;
	this->loadAnimations();

	h.w = 16;
	h.h = 16;
	health = 100;
	maxHealth = 100;
	setAnimationIndex(0);
	counter = 0;
}

void Mushroom::loadAnimations() {
	sf::Texture* tex = resourceManager->getTexture("mushroom_entity");

	Animation* a = new Animation(3);
	for (int i = 0; i < 3; i++) {
		a->editFrame(i, tex);
		a->editCoords(i, sf::IntRect(0, i*16, 16, 16));
		a->editDelay(i, 10);
	}
	this->pushAnimation(a);

	Animation* b = new Animation(4);
	for (int i = 0; i < 4; i++) {
		b->editFrame(i, tex);
		b->editCoords(i, sf::IntRect(0, i*16+48, 16, 16));
		b->editDelay(i, 15);
	}
	this->pushAnimation(b);
}

void Mushroom::tick(double dt) {
	if (counter < 30) {
		setAnimationIndex(0);
	}
	else {
		setAnimationIndex(1);
		double theta = ((double) (rand() % 360)) / 180 * 3.14159265358979323846;
		double magnitude = ((double)(rand() % 60)) / 100 + 0.4;
		gameEnvironment->visuals.push_back(new Particle(gameEnvironment, h.getCX()+24.0*cos(theta), h.getCY()+24.0*sin(theta), 0, -1000000, tileMap, entityList, resourceManager));
		if ((int) counter % 2 == 0) gameEnvironment->visuals.push_back(new Particle(gameEnvironment, h.getCX()+24.0*cos(theta)*magnitude, h.getCY()+24.0*sin(theta)*magnitude, 0, -1000000, tileMap, entityList, resourceManager));
	}

	this->playCurrentAnimation(dt);
	counter += dt;
}

void Mushroom::render(sf::RenderWindow* window) {
	Entity::render(window);
}