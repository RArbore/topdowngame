#include "Projectile.h"

Projectile::Projectile(std::string projType, double x, double y, double vel_x, double vel_y, double acc_x, double acc_y, TileMap* tileMap, vector<Entity*>* entityList, ResourceManager* resourceManager):
	Entity(x, y, tileMap, entityList, resourceManager),
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
	Entity::render(window);
	//sf::CircleShape shape(50.f);
	//shape.setFillColor(sf::Color(100, 250, 50));
	//shape.setPosition(h.getCX(), h.getCY());
	//window->draw(shape);
}

void Projectile::loadAnimation() {
	sf::Texture* tex = resourceManager->getTexture("player_entity");
	Animation a(1);
	a.editFrame(0, tex);
	a.editCoords(0, sf::IntRect(0, 0, 13, 18));
	a.editDelay(0, 1e9);
	this->pushAnimation(a);
}