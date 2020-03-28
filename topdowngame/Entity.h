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

	TileMap* tileMap;

	vector<Entity*>* entityList;
	
	Entity(double x, double y, TileMap* tileMap, vector<Entity*>* entityList);

	bool moveH();
	bool moveV();

	void tick();

	void render(sf::RenderWindow* window);

	Animation mainAnimation;

protected:
	sf::Sprite sprite;
};

