#include "MagicRock.h"

MagicRock::MagicRock(GameEnvironment* gameEnvironment, double x, double y, TileMap* tileMap, ResourceManager* resourceManager) :
	Entity::Entity(x, y, tileMap, resourceManager)
{
	this->gameEnvironment = gameEnvironment;
	this->loadAnimations();

	h.w = 16;
	h.h = 16;
	counter = 0;
	lastCounter = 0;
	state = 0;
	renderOrderOffset = -3;
}

void MagicRock::loadAnimations() {
	sf::Texture* tex = resourceManager->getTexture("magic_rock_entity");

	for (int i = 0; i < 10; i++) {
		Animation* a = new Animation(1);
		a->editFrame(0, tex);
		a->editCoords(0, sf::IntRect(i * 16, 0, 16, 16));
		a->editDelay(0, 1e9);
		this->pushAnimation(a);
	}
}

void MagicRock::tick(double dt) {
	double dx = gameEnvironment->player->h.getCX() - h.getCX();
	double dy = gameEnvironment->player->h.getCY() - h.getCY();
	double distance = sqrt(dx * dx + dy * dy);
	if (distance < 512) {
		if (state == 0) {
			double theta = ((double)(rand() % 360)) / 180 * 3.14159265358979323846;
			double magnitude = 0.08 * ((double)(rand() % 100));
			magnitude *= magnitude;
			gameEnvironment->visuals.push_back(new Particle(gameEnvironment, h.getCX() + magnitude * cos(theta), h.getCY() + magnitude * sin(theta), 3, -1000000, tileMap, resourceManager));
		}
		else if (state == 1) {
			double theta = ((double)(rand() % 360)) / 180 * 3.14159265358979323846;
			double magnitude = 0.08 * ((double)(rand() % 100));
			magnitude *= magnitude;
			gameEnvironment->visuals.push_back(new Particle(gameEnvironment, h.getCX() + magnitude * cos(theta), h.getCY() + magnitude * sin(theta), 4, -1000000, tileMap, resourceManager));
			for (int i = 0; i < 5; i++) {
				double theta = ((double)(rand() % 360)) / 180 * 3.14159265358979323846;
				double magnitude = 16 * 16;
				gameEnvironment->visuals.push_back(new Particle(gameEnvironment, h.getCX() + magnitude * cos(theta), h.getCY() + magnitude * sin(theta), 4, -1000000, tileMap, resourceManager));
			}
			if (distance <= 256) {
				health -= dt;
			}
			if (health <= 0) {
				state = 2;
			}
			if ((int)counter % 600 >= 120 && (int)lastCounter % 600 < 120) {
				if (true) { //Check region type
					int enemyType = rand() % 3;
					for (int i = 0; i < 5; i++) {
						double theta = ((double)(rand() % 360)) / 180 * 3.14159265358979323846;
						double magnitude = 2.56 * ((double)(rand() % 100));
						if (enemyType == 0) {
							gameEnvironment->addEntity(new Slime(gameEnvironment, h.getCX() + magnitude * cos(theta), h.getCY() + magnitude * sin(theta), tileMap, resourceManager));
						}
						else if (enemyType == 1) {
							gameEnvironment->addEntity(new Zombie(gameEnvironment, h.getCX() + magnitude * cos(theta), h.getCY() + magnitude * sin(theta), tileMap, resourceManager));
						}
						else if (enemyType == 2) {
							gameEnvironment->addEntity(new Mushroom(gameEnvironment, h.getCX() + magnitude * cos(theta), h.getCY() + magnitude * sin(theta), tileMap, resourceManager));
						}
					}
				}
			}
		}
		else {
			double theta = ((double)(rand() % 360)) / 180 * 3.14159265358979323846;
			double magnitude = 0.08 * ((double)(rand() % 100));
			magnitude *= magnitude;
			gameEnvironment->visuals.push_back(new Particle(gameEnvironment, h.getCX() + magnitude * cos(theta), h.getCY() + magnitude * sin(theta), 5, -1000000, tileMap, resourceManager));
		}
	}

	this->playCurrentAnimation(dt);
	lastCounter = counter;
	counter += dt;
}

bool MagicRock::damage(double damage) {
	if (state == 0) {
		state = 1;
		maxHealth = 7200;
		health = maxHealth;
		counter = 120;
	}
	return false;
}

void MagicRock::render(sf::RenderWindow* window) {
	setAnimationIndex(0);
	Entity::render(window);
	int textType = ((int)(counter / 240)) % 3;
	setAnimationIndex(state * 3 + textType + 1);
	Animation* anim = this->getCurrentAnimation();
	sprite.setTexture(*(anim->getCurrentFrame()));
	sprite.setTextureRect(anim->getCurrentCoords());
	sf::IntRect textureCoords = anim->getCurrentCoords();
	sprite.setPosition((float)(h.getCX() - (float)textureCoords.width / 2.f), (float)(h.getCY() - (float)textureCoords.height / 2.f));
	sprite.setColor(sf::Color(255, 255, 255, (int)(255.0 * sin(((double)((int)(counter) % 240)) * 3.14159265358979323846 / 240.0))));
	window->draw(sprite);
	sprite.setColor(sf::Color(255, 255, 255));
	setAnimationIndex(0);
}