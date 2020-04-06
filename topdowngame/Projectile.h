#pragma once

#include <string>

#include "Entity.h"

class Projectile : public Entity {
public:
	Projectile(std::string type, double x, double y, double vel_x, double vel_y, double acc_x, double acc_y, TileMap* tileMap, vector<Entity*>* entityList, ResourceManager* resourceManager);
	void tick(double dt);
	void render(sf::RenderWindow* window);

	std::string projType;
	double durationCounter;

private:
	sf::Vector2f vel, acc;

	void loadAnimation();
};

