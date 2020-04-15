#include "BossMagicRock.h"

BossMagicRock::BossMagicRock(GameEnvironment* gameEnvironment, double x, double y, TileMap* tileMap) :
	Entity::Entity(x, y, tileMap)
{
	this->gameEnvironment = gameEnvironment;
	this->loadAnimations();

	h.w = 29;
	h.h = 21;
	counter = 0;
	state = -1;
}

void BossMagicRock::loadAnimations() {
	sf::Texture* tex = ResourceManager::getTexture("boss_magic_rock_entity");

	for (int i = 0; i < 10; i++) {
		Animation* a = new Animation(1);
		a->editFrame(0, tex);
		a->editCoords(0, sf::IntRect(i * 29, 0, 29, 21));
		a->editDelay(0, 1e9);
		this->pushAnimation(a);
	}
}

void BossMagicRock::tick(double dt) {
	double dx = gameEnvironment->player->h.getCX() - h.getCX();
	double dy = gameEnvironment->player->h.getCY() - h.getCY();
	double distance = sqrt(dx * dx + dy * dy);

	bool check = false;

	if (state == -1) {
		for (Entity* e : gameEnvironment->getEntities()) {
			if (MagicRock* mr = dynamic_cast<MagicRock*>(e)) {
				if (mr->state != 2) {
					check = true;
				}
			}
			if (check) break;
		}
		if (!check) state = 0;
	}

	if (distance < 512) {
		if (state == 0) {
			double theta = ((double)(rand() % 360)) / 180 * 3.14159265358979323846;
			double magnitude = 0.1 * ((double)(rand() % 100));
			magnitude *= magnitude;
			gameEnvironment->visuals.push_back(new Particle(gameEnvironment, h.getCX() + magnitude * cos(theta), h.getCY() + magnitude * sin(theta), 3, -1000000, tileMap));
		}
		else if (state == 1) {
			double theta = ((double)(rand() % 360)) / 180 * 3.14159265358979323846;
			double magnitude = 0.1 * ((double)(rand() % 100));
			magnitude *= magnitude;
			gameEnvironment->visuals.push_back(new Particle(gameEnvironment, h.getCX() + magnitude * cos(theta), h.getCY() + magnitude * sin(theta), 4, -1000000, tileMap));
			for (int i = 0; i < 5; i++) {
				double theta = ((double)(rand() % 360)) / 180 * 3.14159265358979323846;
				double magnitude = 16 * 16;
				gameEnvironment->visuals.push_back(new Particle(gameEnvironment, h.getCX() + magnitude * cos(theta), h.getCY() + magnitude * sin(theta), 4, -1000000, tileMap));
			}
			bool check = false;
			for (Entity* boss : bosses) {
				if (!boss->removeMe) {
					check = true;
				}
				if (check) break;
			}
			if (!check) {
				state = 2;
				for (int i = bosses.size() - 1; i >= 0; i--) {
					bosses.erase(bosses.begin() + i);
				}
			}
		}
		else if (state == 2) {
			double theta = ((double)(rand() % 360)) / 180 * 3.14159265358979323846;
			double magnitude = 0.1 * ((double)(rand() % 100));
			magnitude *= magnitude;
			gameEnvironment->visuals.push_back(new Particle(gameEnvironment, h.getCX() + magnitude * cos(theta), h.getCY() + magnitude * sin(theta), 5, -1000000, tileMap));
		}
	}

	this->playCurrentAnimation(dt);
	counter += dt;
}

bool BossMagicRock::damage(double damage) {
	if (state == 0) {
		state = 1;
		counter = 120;
		double theta = ((double)(rand() % 360)) / 180 * 3.14159265358979323846;
		double magnitude = 2.56 * ((double)(rand() % 100));
		Entity* boss = new Minotaur(gameEnvironment, h.getCX() + magnitude * cos(theta) - 16, h.getCY() + magnitude * sin(theta) - 16, tileMap);
		gameEnvironment->addEntity(boss);
		bosses.push_back(boss);
	}
	return false;
}

void BossMagicRock::render(sf::RenderWindow* window) {
	setAnimationIndex(0);
	Entity::render(window);
	if (state != -1) {
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
}