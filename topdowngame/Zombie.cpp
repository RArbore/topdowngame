#include "Zombie.h"

Zombie::Zombie(GameEnvironment* gameEnvironment, double x, double y, TileMap* tileMap, ResourceManager* resourceManager) :
Entity::Entity(x, y, tileMap, resourceManager)
{
	this->gameEnvironment = gameEnvironment;
	this->loadAnimations();

	h.w = 16;
	h.h = 16;
	movementSpeed = 0.4f;
	health = 100;
	maxHealth = 100;
	setAnimationIndex(0);
	attackTimer = 0;
	counter = 0;
	lastDirection = 4;
}

void Zombie::loadAnimations() {
	sf::Texture* tex = resourceManager->getTexture("zombie_entity");

	for (int j = 0; j < 8; j++) {
		Animation* a = new Animation(1);
		a->editFrame(0, tex);
		a->editCoords(0, sf::IntRect(13 * j, 0, 13, 18));
		a->editDelay(0, 1e9);
		this->pushAnimation(a);
	}

	for (int j = 0; j < 8; j++) {
		Animation* a = new Animation(6);
		for (int i = 0; i < 6; i++) {
			a->editFrame(i, tex);
			a->editCoords(i, sf::IntRect(13 * j, 18 * i, 13, 18));
			a->editDelay(i, 10);
		}
		this->pushAnimation(a);
	}

	Animation* a = new Animation(12);
	for (int i = 0; i < 12; i++) {
		a->editFrame(i, tex);
		a->editCoords(i, sf::IntRect(i*16, 18*6, 16, 16));
		a->editDelay(i, 8);
	}
	this->pushAnimation(a);
}

void Zombie::tick(double dt) {
	if (target == NULL) {
		target = gameEnvironment->focusEntity;
	}

	movement(dt);

	this->playCurrentAnimation(dt);
	counter += dt;
}

void Zombie::movement(double dt) {
	if (health > 0) {
		if (counter > 96) {
			double dx = target->h.getCX() - h.getCX();
			double dy = target->h.getCY() - h.getCY();
			double distance = sqrt(dx * dx + dy * dy);
			if (distance < 384) {
				if (h.checkCollision(&target->h) && attackTimer <= 0) {
					target->damage(20);
					target->moveH(dx, 7);
					target->moveV(dy, 7);
					attackTimer = 15;
				}
				else if (attackTimer > 0) {
					attackTimer -= dt;
				}
				else {
					attackTimer = 0;
					double mv = dt * movementSpeed;
					moveH(dx / distance * mv, 7);
					moveV(dy / distance * mv, 7);
				}

				double PI = 3.14159265;
				double angle = (int)(atan2(dy, dx) * 180.f / PI);

				int baseIndex = 0;
				if (angle > -112.5 && angle <= -67.5) baseIndex = 0;
				else if (angle > -67.5 && angle <= -22.5) baseIndex = 1;
				else if (angle > -22.5 && angle <= 22.5) baseIndex = 2;
				else if (angle > 22.5 && angle <= 67.5) baseIndex = 3;
				else if (angle > 67.5 && angle <= 112.5) baseIndex = 4;
				else if (angle > 112.5 && angle <= 157.5) baseIndex = 5;
				else if ((angle > 157.5 && angle <= 180) || (angle >= -180 && angle <= -157.5)) baseIndex = 6;
				else if (angle > -157.5 && angle <= -112.5) baseIndex = 7;

				baseIndex += 8;
				lastDirection = baseIndex - 8;
				setAnimationIndex(baseIndex);
			}
			else {
				setAnimationIndex(lastDirection);
			}
		}
		else {
			setAnimationIndex(16);
		}
	}
	else {
		for (int i = 0; i < 5; i++) {
			double theta = ((double)(rand() % 360)) / 180 * 3.14159265358979323846;
			gameEnvironment->visuals.push_back(new Particle(gameEnvironment, h.getCX() + 8.0 * cos(theta), h.getCY() + 8.0 * sin(theta), 2, 1000000, tileMap, resourceManager));
		}
		gameEnvironment->addEntity(new Coin(gameEnvironment, h.getCX()-3, h.getCY()-3.5, &gameEnvironment->tileMap, resourceManager));
		removeMe = true;
	}
}

void Zombie::render(sf::RenderWindow* window) {
	Entity::render(window);
}

bool Zombie::damage(double damage) {
	if (health <= 0) {
		return false;
	}
	health -= damage;
	return true;
}