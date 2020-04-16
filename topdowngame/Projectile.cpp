#include "Projectile.h"

Projectile::Projectile(std::string projType, double x, double y, double vel_x, double vel_y, double acc_x, double acc_y, TileMap* tileMap):
	Entity(x, y, tileMap),
	vel(vel_x, vel_y),
	acc(acc_x, acc_y)
{	
	this->projType = projType;
	durationCounter = 0.f;
	this->loadAnimation();
}

void Projectile::tick(double dt) {
	vel.x += acc.x * dt;
	vel.y += acc.y * dt;
	h.x += vel.x * dt;
	h.y += vel.y * dt;

	durationCounter += dt;
	this->playCurrentAnimation(dt);
}

void Projectile::render(sf::RenderWindow* window) {
	// Entity::render(window);
	Animation* anim = this->getCurrentAnimation();
	sprite.setTexture(*(anim->getCurrentFrame()));
	sprite.setTextureRect(anim->getCurrentCoords());
	sf::IntRect textureCoords = anim->getCurrentCoords();
	sprite.setPosition(h.getCX() - float(textureCoords.width) / 2.f, h.getCY() - float(textureCoords.height) / 2.f);

	// handle projectile rotation
	double PI = 3.14159265;
	double angle = ((double)atan2(vel.y, vel.x)) * 180 / PI;
	sf::Transform transform;
	transform.rotate(angle+90, sf::Vector2f(h.getCX(), h.getCY()));


	window->draw(sprite, transform);
}

void Projectile::loadAnimation() {
	sf::Texture* tex;

	if (projType == "arrow") tex = ResourceManager::getTexture("arrow");
	else tex = ResourceManager::getTexture("DEFUALT_TEXTURE");

	Animation* a = new Animation(1);
	a->editFrame(0, tex);
	a->editCoords(0, sf::IntRect(0, 0, 5, 13));
	a->editDelay(0, 1e9);
	this->pushAnimation(a);
}