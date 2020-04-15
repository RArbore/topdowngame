#include "Minotaur.h"

Minotaur::Minotaur(GameEnvironment* gameEnvironment, double x, double y, TileMap* tileMap, ResourceManager* resourceManager) :
	Entity::Entity(x, y, tileMap, resourceManager)
{
	this->gameEnvironment = gameEnvironment;
	this->loadAnimations();

	h.w = 32;
	h.h = 48;
	movementSpeed = 1.0f;
	health = 500;
	maxHealth = 500;
	setAnimationIndex(0);
	attackTimer = 0;
	counter = 0;
	attackType = 0;
	animOffset = 0;
	healthBarOffsetY = -32;
}

void Minotaur::loadAnimations() {
	sf::Texture* tex = resourceManager->getTexture("minotaur_entity");

	vector<int> frames = { 5, 8, 5, 9, 5, 6, 9, 3, 3, 6 };
	vector<int> delays = { 6, 6, 6, 3, 4, 8, 3, 6, 6, 6 };

	for (int d = 0; d < 2; d++) {
		for (int i = 0; i < 10; i++) {
			Animation* a = new Animation(frames.at(i));
			for (int f = 0; f < frames.at(i); f++) {
				a->editFrame(f, tex);
				a->editCoords(f, sf::IntRect(f * 96, (d * 10 + i) * 96, 96, 96));
				a->editDelay(f, delays.at(i));
			}
			this->pushAnimation(a);
		}
		Animation* a = new Animation(4);
		for (int f = 0; f < 4; f++) {
			a->editFrame(f, tex);
			a->editCoords(f, sf::IntRect(288 + f * 96, 576 + d * 960, 96, 96));
			a->editDelay(f, 3);
		}
		this->pushAnimation(a);
	}
}

void Minotaur::tick(double dt) {
	if (target == NULL) {
		target = gameEnvironment->focusEntity;
	}

	movement(dt);

	this->playCurrentAnimation(dt);
	counter += dt;
}

void Minotaur::movement(double dt) {
	if (health > 0) {
		double dx = target->h.getCX() - h.getCX();
		double dy = target->h.getCY() - h.getCY();
		double distance = sqrt(dx * dx + dy * dy);
		if (attackType != 4 || attackTimer <= 0) {
			if (dx < 0) {
				animOffset = 11;
			}
			else {
				animOffset = 0;
			}
		}

		if (attackTimer <= 0) {
			double mv = dt * movementSpeed;
			moveH(dx / distance * mv, 7);
			moveV(dy / distance * mv, 7);
			int attackAttempt = rand() % 4 + 1;
			attackType = attackAttempt;
			if (attackAttempt == 1 && distance < 24 && abs(dx) > abs(dy)) {
				attackTimer = 27;

				setAnimationIndex(3 + animOffset);
			}
			else if (attackAttempt == 2 && distance < 24 && abs(dx) > abs(dy) * 2) {
				attackTimer = 20;

				setAnimationIndex(4 + animOffset);
			}
			else if (attackAttempt == 3 && distance < 24) {
				attackTimer = 48;

				setAnimationIndex(5 + animOffset);
			}
			else if (attackAttempt == 4 && distance > 160) {
				attackTimer = 27 * 5;

				setAnimationIndex(10 + animOffset);
			}
			else {
				setAnimationIndex(1 + animOffset);
			}
		}
		else {
			attackTimer -= dt;
			if (attackType == 1 && attackTimer <= 24 && abs(dx) > abs(dy) && distance < 24) {
				target->damage(20);
				target->moveH(dx * 1.2, 7);
				target->moveV(dy * 1.2, 7);
			}
			else if (attackType == 2 && attackTimer <= 16 && abs(dx) > abs(dy) * 2 && distance < 24) {
				target->damage(20);
				target->moveH(dx * 1.6, 7);
				target->moveV(dy * 1.6, 7);
			}
			else if (attackType == 3 && attackTimer <= 16) {
				attackType = 0;
				for (int i = 0; i < 50; i++) {
					double theta = ((double)(rand() % 360)) / 180 * 3.14159265358979323846;
					double magnitude = 8.0 * ((double)(rand() % 100)) / 12.0;
					gameEnvironment->visuals.push_back(new Particle(gameEnvironment, h.getCX() + magnitude * cos(theta), h.getCY() + magnitude * sin(theta), 2, -1000000, tileMap, resourceManager));
				}
				if (distance < 64) {
					target->damage(20);
					target->moveH(dx * 2.0, 7);
					target->moveV(dy * 2.0, 7);
				}
			}
			else if (attackType == 4) {
				double mv = dt * movementSpeed * 3;
				moveH(dx / distance * mv, 7);
				moveV(dy / distance * mv, 7);
				if (distance < 36) {
					target->damage(20);
					target->moveH(dx * 1.6, 7);
					target->moveV(dy * 1.6, 7);
				}
			}
		}
	}
	else {
		setAnimationIndex(9 + animOffset);
		if (attackTimer > 0) {
			attackTimer -= dt;
		}
		else {
			for (int i = 0; i < 25; i++) {
				double theta = ((double)(rand() % 360)) / 180 * 3.14159265358979323846;
				double magnitude = 8.0 * ((double)(rand() % 100)) / 50;
				gameEnvironment->visuals.push_back(new Particle(gameEnvironment, h.getCX() + magnitude * cos(theta), h.getCY() + magnitude * sin(theta), 2, 1000000, tileMap, resourceManager));
			}
			gameEnvironment->addEntity(new Coin(gameEnvironment, h.getCX() - 3, h.getCY() - 3.5, &gameEnvironment->tileMap, resourceManager));
			removeMe = true;
		}
	}
}

void Minotaur::render(sf::RenderWindow* window) {
	Entity::render(window);
}

bool Minotaur::damage(double damage) {
	if (health <= 0) {
		return false;
	}
	health -= damage;
	if (health <= 0) {
		attackTimer = 36;
	}
	return true;
}