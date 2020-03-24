#pragma once

#include "Hitbox.h"

#include <SFML/Graphics.hpp>

#include "Animation.h"

#include "TileMap.h"

#include <vector>

using namespace std;

class Entity
{

public:

	~Entity() = default;

	Hitbox h;

	TileMap* map;

	vector<Entity*>* entityList;
	
	Entity(double x, double y, TileMap* map, vector<Entity*>* entityList);

	bool moveH();
	bool moveV();

	void tick();

	void render(sf::RenderWindow& window);

private:
	sf::Sprite sprite;
	Animation mainAnimation;
};

