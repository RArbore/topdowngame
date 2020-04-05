#include "Projectile.h"

Projectile::Projectile(std::string projType, double x, double y, double vel_x, double vel_y, double acc_x, double acc_y, TileMap* tileMap, vector<Entity*>* entityList, ResourceManager* resourceManager, sf::Texture* tex):
	Entity(x, y, tileMap, entityList, resourceManager),
	vel(vel_x, vel_y),
	acc(acc_x, acc_y)
{	
	this->projType = projType;
	this->texture = tex;
	durationCounter = 0;
	this->loadAnimation();
}

void Projectile::tick() {
	vel.x += acc.x;
	vel.y += acc.y;
	h.x += vel.x;
	h.y += vel.y;

	durationCounter += 1;
	this->playCurrentAnimation();
}

void Projectile::render(sf::RenderWindow* window) {
	Entity::render(window);
	//sf::CircleShape shape(50.f);
	//shape.setFillColor(sf::Color(100, 250, 50));
	//shape.setPosition(h.getCX(), h.getCY());
	//window->draw(shape);
}

void Projectile::loadAnimation() {
	Animation a(1);
	a.editFrame(0, texture);
	a.editCoords(0, sf::IntRect(0, 0, 13, 18));
	a.editDelay(0, 1e9);
	this->pushAnimation(a);
}