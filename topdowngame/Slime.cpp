#include "Slime.h"

Slime::Slime(GameEnvironment* gameEnvironment, double x, double y, TileMap* tileMap, vector<Entity*>* entityList, ResourceManager* resourceManager) :
Entity::Entity(x, y, tileMap, entityList, resourceManager),
vel(0.f, 0.f),
acc(0.f, 0.f)
{
	this->gameEnvironment = gameEnvironment;
	this->loadAnimations();

	h.w = 16;
	h.h = 16;
	movementSpeed = 0.25f;
	health = 100;
	maxHealth = 100;
	attackDelayCounter = 0;
	setAnimationIndex(0);
	hurtTimer = 0;
	attackTimer = 0;
	counter = 0;
}

void Slime::loadAnimations() {
	sf::Texture* tex = resourceManager->getTexture("slime_entity");

	Animation* a = new Animation(2);
	for (int i = 0; i < 2; i++) {
		a->editFrame(i, tex);
		a->editCoords(i, sf::IntRect(0, i*16, 16, 16));
		a->editDelay(i, 30);
	}
	this->pushAnimation(a);

	Animation* b = new Animation(3);
	for (int i = 0; i < 3; i++) {
		b->editFrame(i, tex);
		b->editCoords(i, sf::IntRect(0, i*16+32, 16, 16));
		b->editDelay(i, 20);
	}
	this->pushAnimation(b);

	Animation* c = new Animation(1);
	c->editFrame(0, tex);
	c->editCoords(0, sf::IntRect(0, 80, 16, 16));
	c->editDelay(0, 1e9);
	this->pushAnimation(c);

	Animation* d = new Animation(3);
	for (int i = 0; i < 3; i++) {
		d->editFrame(i, tex);
		d->editCoords(i, sf::IntRect(0, i*16+96, 16, 16));
		d->editDelay(i, 10);
	}
	this->pushAnimation(d);

	Animation* e = new Animation(3);
	for (int i = 0; i < 3; i++) {
		e->editFrame(i, tex);
		e->editCoords(i, sf::IntRect(16, i*16, 16, 16));
		e->editDelay(i, 5);
	}
	this->pushAnimation(e);
}

void Slime::tick(double dt) {
	if (target == NULL) {
		target = gameEnvironment->focusEntity;
	}

	hurtTimer -= dt;

	attackDelayCounter += dt;

	movement(dt);

	this->playCurrentAnimation(dt);
	counter += dt;
}

void Slime::movement(double dt) {
	//cout << h.getCX() << " " << h.getCY() << endl;
	if (health > 0) {
		if (counter > 60) {
			double dx = target->h.getCX() - h.getCX();
			double dy = target->h.getCY() - h.getCY();
			if (h.checkCollision(&target->h) && attackTimer <= 0) {
				setAnimationIndex(4);
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
				double distance = sqrt(dx * dx + dy * dy);
				h.x += dx / distance * mv;
				h.y += dy / distance * mv;
				if (hurtTimer > 0) {
					setAnimationIndex(2);
				}
				else {
					setAnimationIndex(0);
					hurtTimer = 0;
				}
			}
		}
		else {
			setAnimationIndex(1);
		}
	}
	else {
		setAnimationIndex(3);
		if (counter >= 30) {
			for (int i = 0; i < 5; i++) {
				double theta = ((double)(rand() % 360)) / 180 * 3.14159265358979323846;
				gameEnvironment->visuals.push_back(new Particle(gameEnvironment, h.getCX() + 8.0 * cos(theta), h.getCY() + 8.0 * sin(theta), 2, 1000000, tileMap, entityList, resourceManager));
			}
			gameEnvironment->entities.push_back(new Coin(gameEnvironment, h.getCX()-3, h.getCY()-3.5, &gameEnvironment->tileMap, &gameEnvironment->entities, resourceManager));
			removeMe = true;
		}
	}
}

void Slime::render(sf::RenderWindow* window) {
	Entity::render(window);
}

bool Slime::damage(double damage) {
	if (health <= 0) {
		return false;
	}
	health -= damage;
	setAnimationIndex(2);
	hurtTimer = 5;
	if (health <= 0) {
		counter = 0;
	}
	return true;
}